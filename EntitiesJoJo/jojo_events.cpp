#include "StdH.h"
#include "jojo_events.h"
#include "entitycast.h"
#include "EntitiesJoJo/RodaRollaDa.h"
#include "EntitiesMP/MusicHolder.h"
#include "EntitiesMP/EnemyBase.h"
#include "EntitiesMP/CannonBall.h"
#include "EntitiesMP/DevilProjectile.h"
#include "EntitiesMP/LarvaOffspring.h"
 
CStaticStackArray<CSentEvent>* _paseSentEvents = NULL;

void FreezeEntityInZaWarudo(CMusicHolder* p_mh, const CEntityPointer& pen)
{
  if (p_mh->IsEntityFrozen(pen) == TRUE)
    return;

  p_mh->FreezeEntity(pen);
  CEntity* p_entity = pen.ep_pen;

  EZaWarudoRestore restore_event;
  restore_event.restore_movement = FALSE;
  restore_event.restore_physics = FALSE;

  if (p_entity->en_RenderType == CEntity::RT_MODEL)
    p_entity->en_pmoModelObject->PauseAnim();

  CMovableEntity* p_movable = entity_cast(p_entity, CMovableEntity);
  if (p_movable != NULL)
  {
    restore_event.restore_movement = TRUE;
    restore_event.en_vDesiredTranslationRelative = p_movable->en_vDesiredTranslationRelative;
    restore_event.en_vCurrentTranslationAbsolute = p_movable->en_vCurrentTranslationAbsolute;
    restore_event.en_vAppliedTranslation = p_movable->en_vAppliedTranslation;
    restore_event.en_aDesiredRotationRelative = p_movable->en_aDesiredRotationRelative;
    restore_event.en_aCurrentRotationAbsolute = p_movable->en_aCurrentRotationAbsolute;
    restore_event.en_mAppliedRotation = p_movable->en_mAppliedRotation;
    p_movable->ForceFullStop();
  }

  if (entity_cast(p_entity, CEnemyBase) ||
      entity_cast(p_entity, CProjectile) ||
      entity_cast(p_entity, CFlame) ||
      entity_cast(p_entity, CCannonBall) ||
      entity_cast(p_entity, CDevilProjectile) ||
      entity_cast(p_entity, CLarvaOffspring) ||
      entity_cast(p_entity, CDebris) ||
      entity_cast(p_entity, CRodaRollaDa))
  {
    restore_event.physics_flags = p_entity->GetPhysicsFlags();
    restore_event.collision_flags = p_entity->GetCollisionFlags();

    if (restore_event.collision_flags != ECF_IMMATERIAL &&
        restore_event.collision_flags != ECF_CORPSE &&
        restore_event.collision_flags != (ECF_CORPSE&~((ECBI_PROJECTILE_MAGIC|ECBI_PROJECTILE_SOLID)<<ECB_TEST)))
    {
      p_entity->SetPhysicsFlags(EPF_MODEL_FIXED);

      ULONG collision_flags = ECF_MODEL_HOLDER;
      if (restore_event.collision_flags & (IDENTIFY_AS_ENEMY | IDENTIFY_AS_PROJECTILE))
        collision_flags |= IDENTIFY_AS_ENEMY; //projectiles are treated as 'enemy' to make road roller pass through them

      p_entity->SetCollisionFlags(collision_flags);
      restore_event.restore_physics = TRUE;
    }
  }
  if (restore_event.restore_physics == TRUE ||
      restore_event.restore_movement == TRUE)
  {
    p_entity->SendEvent(restore_event);
  }
}

/******************************/
/* Handle all sent events.    */
/******************************/
void PopAllEvents()
{
  CStaticStackArray<CSentEvent>& _aseSentEvents = *_paseSentEvents;
  for (INDEX iee = 0; iee < _aseSentEvents.Count(); iee++) {
    CSentEvent& se = _aseSentEvents[iee];
    se.se_penEntity = NULL;
    delete se.se_peeEvent;
    se.se_peeEvent = NULL;
  }
  _aseSentEvents.PopAll();
}

void HandleStopTime(CMusicHolder* p_mh)
{
  {FOREACHINDYNAMICCONTAINER(p_mh->GetWorld()->wo_cenEntities, CEntity, iten)
  {
    CEntity* p_entity = iten;
    p_entity = p_entity->GetPredictionTail();
    if (p_entity->en_ulFlags & ENF_DELETED)
      continue;
    if (p_mh->IsDioOrRelated(p_entity))
      continue;

    CRationalEntity* p_rational = entity_cast(p_entity, CRationalEntity);
    if (p_rational != NULL)
      if (p_rational->en_timeTimer != THINKTIME_NEVER)
        p_rational->SetTimerAt(p_rational->en_timeTimer + ZA_WARUDO_DURATION);

    FreezeEntityInZaWarudo(p_mh, p_entity);
  }}
}

void HandleStartTime(CMusicHolder* p_mh)
{
  // for each entity in the world
  {FOREACHINDYNAMICCONTAINER(p_mh->GetWorld()->wo_cenEntities, CEntity, iten)
  {
    CEntity* p_entity = iten;
    p_entity = p_entity->GetPredictionTail();
    if (p_mh->IsDioOrRelated(p_entity))
      continue;

    if (p_entity->en_RenderType == CEntity::RT_MODEL)
      p_entity->en_pmoModelObject->ContinueAnim();
  }}

  p_mh->ClearFrozenEntities();
  p_mh->SetDio(NULL);
  p_mh->PopStoredEvents();
}

void JoJoHandleSentEvents()
{
  CMusicHolder* p_mh = GetMusicHolder();
  if (p_mh != NULL && p_mh->IsZaWarudo() && _pNetwork->IsPredicting())
  {
    PopAllEvents();
    return;
  }

  CSetFPUPrecision FPUPrecision(FPT_24BIT);

  CStaticStackArray<CSentEvent>& _aseSentEvents = *_paseSentEvents;

  // while there are any unhandled events
  INDEX iFirstEvent = 0;
  while (iFirstEvent<_aseSentEvents.Count())
  {
    CSentEvent &se = _aseSentEvents[iFirstEvent];

    // if not allowed to execute now
    if (se.se_penEntity == NULL || !se.se_penEntity->IsAllowedForPrediction())
    {
      // skip it
      iFirstEvent++;
      continue;
    }

    if (!(se.se_penEntity->en_ulFlags&ENF_DELETED))
    {
      if (p_mh != NULL &&
          p_mh->IsZaWarudo() &&
          !p_mh->IsDioOrRelated(se.se_penEntity.ep_pen) &&
          entity_cast(se.se_penEntity.ep_pen, CItem) == NULL)
      {
        if (se.se_peeEvent->ee_slEvent != EVENTCODE_ETouch ||
            entity_cast(se.se_penEntity.ep_pen, CProjectile) == NULL ||
            !p_mh->IsDioOrRelated(((ETouch*)se.se_peeEvent)->penOther))
        {
          p_mh->StoreEvent(se);
          FreezeEntityInZaWarudo(p_mh, se.se_penEntity);
        }
      } else {
        if (se.se_peeEvent->ee_slEvent == EVENTCODE_EHandleStopTime)
        {
          HandleStopTime(p_mh);
        }
        else if (se.se_peeEvent->ee_slEvent == EVENTCODE_EHandleStartTime)
        {
          HandleStartTime(p_mh);
        }
        else if (se.se_peeEvent->ee_slEvent == EVENTCODE_EZaWarudoRestore)
        {
          EZaWarudoRestore* p_restore = (EZaWarudoRestore*)se.se_peeEvent;
          if (p_restore->restore_movement == TRUE)
          {
            CMovableEntity* p_movable = (CMovableEntity*)se.se_penEntity.ep_pen;
            p_movable->en_vDesiredTranslationRelative = p_restore->en_vDesiredTranslationRelative;
            p_movable->en_vCurrentTranslationAbsolute = p_restore->en_vCurrentTranslationAbsolute;
            p_movable->en_vAppliedTranslation = p_restore->en_vAppliedTranslation;
            p_movable->en_aDesiredRotationRelative = p_restore->en_aDesiredRotationRelative;
            p_movable->en_aCurrentRotationAbsolute = p_restore->en_aCurrentRotationAbsolute;
            p_movable->en_mAppliedRotation = p_restore->en_mAppliedRotation;
            p_movable->AddToMovers();
          }
          if (p_restore->restore_physics == TRUE)
          {
            se.se_penEntity->SetPhysicsFlags(p_restore->physics_flags);
            se.se_penEntity->SetCollisionFlags(p_restore->collision_flags);
          }
        }
        else
        {
          se.se_penEntity->HandleEvent(*se.se_peeEvent);
        }
      }
    }
    // go to next event
    iFirstEvent++;
  }

  PopAllEvents();
}
