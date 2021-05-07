#include "StdH.h"
#include "jojo_events.h"
#include "entitycast.h"
#include "EntitiesJoJo/RodaRollaDa.h"
#include "EntitiesMP/MusicHolder.h"
#include "EntitiesMP/EnemyBase.h"
#include "EntitiesMP/CannonBall.h"
#include "EntitiesMP/DevilProjectile.h"
#include "EntitiesMP/LarvaOffspring.h"
extern BOOL g_shouldResolveEvents = FALSE;
static CStaticStackArray<CSentEvent> _aseSentEventsBackup;
CStaticStackArray<CSentEvent>* _paseSentEvents = NULL;

extern CMusicHolder* g_musicHolder = NULL;

/*
Event is mandatory, if it passed the prediction check and must be executed
During ZaWarudo on the other hand, event execution is postponed
By marking event as mandatory, we make sure it will be executed
Even after time restores its movement when prediction check is passed

This is required in network game
It appears, that events that fail prediction check, are not required for network game
*/
struct MandatoryEvent
{
  ULONG p_event;
  UT_hash_handle hh;
};
MandatoryEvent* g_mandatoryEvents = NULL;

BOOL IsEventMandatory(CEntityEvent* p_event)
{
  if (p_event == NULL)
    return FALSE;

  MandatoryEvent* m = NULL;
  HASH_FIND_INT(g_mandatoryEvents, (ULONG*)&p_event, m);
  return m == NULL ? FALSE : TRUE;
}

void MarkEventMandatory(CEntityEvent* p_event)
{
  if (IsEventMandatory(p_event))
    return;

  MandatoryEvent* m = new MandatoryEvent();
  m->p_event = (ULONG)p_event;
  HASH_ADD_INT(g_mandatoryEvents, p_event, m);
}

void RemoveEventFromMandatory(CEntityEvent* p_event)
{
  MandatoryEvent* m = NULL;
  HASH_FIND_INT(g_mandatoryEvents, (ULONG*)&p_event, m);
  if (m != NULL)
  {
    HASH_DEL(g_mandatoryEvents, m);
    delete m;
  }
}

void ClearMandatoryEvents()
{
  MandatoryEvent* current;
  MandatoryEvent* tmp;

  HASH_ITER(hh, g_mandatoryEvents, current, tmp)
  {
    HASH_DEL(g_mandatoryEvents, current);
    delete current;
  }
}

/*
Frozen actually, but nvm
Entity is marked as frozen in ZaWarudo for optimization purposes
If entity is already frozen, nothing is done to it
*/
struct FreezedEntity
{
  ULONG id;
  CEntity* p_entity;
  UT_hash_handle hh;
};
FreezedEntity* g_freezedEntities = NULL;

void ClearFrozenEntities()
{
  FreezedEntity* current;
  FreezedEntity* tmp;

  HASH_ITER(hh, g_freezedEntities, current, tmp)
  {
    HASH_DEL(g_freezedEntities, current);
    delete current;
  }
}

BOOL IsEntityInZaWarudo(CEntity* p_entity)
{
  FreezedEntity* freezed = NULL;
  HASH_FIND_INT(g_freezedEntities, &p_entity->en_ulID, freezed);
  return freezed == NULL ? FALSE : TRUE;
}

void MarkEntityAsInZaWarudo(CEntity* p_entity, ULONG id)
{
  FreezedEntity* freezed = new FreezedEntity();
  freezed->id = id;
  freezed->p_entity = p_entity;
  HASH_ADD_INT(g_freezedEntities, id, freezed);
}

void MarkEntityAsInZaWarudo(CEntity* p_entity)
{
  p_entity = p_entity->GetPredictionTail();
  MarkEntityAsInZaWarudo(p_entity, p_entity->en_ulID);
}

void FreezeEntityInZaWarudo(CEntity* p_entity)
{
  p_entity = p_entity->GetPredictionTail();
  if (IsEntityInZaWarudo(p_entity) == TRUE)
    return;

  MarkEntityAsInZaWarudo(p_entity);

  EZaWarudoRestore restore_event;
  restore_event.restore_movement = FALSE;
  restore_event.restore_physics = FALSE;
  restore_event.restore_mass = FALSE;

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
    EntityInfo* p_info = (EntityInfo*)p_movable->GetEntityInfo();
    if (p_info != NULL)
    {
      restore_event.restore_mass = TRUE;
      restore_event.mass = p_info->fMass;
      p_info->fMass = 10000.0f;
    }
  }

  if (entity_cast(p_entity, CEnemyBase) ||
      entity_cast(p_entity, CProjectile) ||
      entity_cast(p_entity, CFlame) ||
      entity_cast(p_entity, CCannonBall) ||
      entity_cast(p_entity, CDevilProjectile) ||
      entity_cast(p_entity, CLarvaOffspring) ||
      //entity_cast(p_entity, CPlayer) ||
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

    CEntityEvent* p_last_inserted_event = (*_paseSentEvents)[_paseSentEvents->Count()-1].se_peeEvent;
    MarkEventMandatory(p_last_inserted_event);
  }
}

/*
Save backup events to stream for Save/Load cycle
*/
void WriteBackupEvents(CTStream* strm)
{
  INDEX num_events = _aseSentEventsBackup.Count();
  *strm<<num_events;
  for (INDEX iee = 0; iee < num_events; iee++)
  {
    CSentEvent& se = _aseSentEventsBackup[iee];
    BOOL is_mandatory = IsEventMandatory(se.se_peeEvent);
    *strm<<is_mandatory;
    WriteEventMember(strm, se.se_penEntity);
    WriteSingleEvent(strm, se.se_peeEvent);
  }

  INDEX num_entities_in_za_warudo = HASH_COUNT(g_freezedEntities);
  *strm<<num_entities_in_za_warudo;
  FreezedEntity* current;
  FreezedEntity* tmp;
  HASH_ITER(hh, g_freezedEntities, current, tmp)
  {
    WriteEventMember(strm, current->p_entity);
  }
}

/*
Load backup events from stream for Save/Load cycle
*/
void ReadBackupEvents(CTStream* strm)
{
  ClearBackupEvents();

  INDEX num_events;
  *strm>>num_events;

  INDEX allocated_size = (num_events / _paseSentEvents->sa_ctAllocationStep) * _paseSentEvents->sa_ctAllocationStep;
  if (allocated_size < num_events)
    allocated_size += _paseSentEvents->sa_ctAllocationStep;
  if (_paseSentEvents->sa_Count > allocated_size)
  {
    allocated_size = _paseSentEvents->sa_Count;
    _paseSentEvents->Delete();
    _paseSentEvents->New(num_events);
  }

  _aseSentEventsBackup.Delete();
  _aseSentEventsBackup.New(allocated_size);
  for (INDEX iee = 0; iee < num_events; iee++)
  {
    CSentEvent& se = _aseSentEventsBackup.Push();
    BOOL is_mandatory;
    *strm>>is_mandatory;
    ReadEventMember(strm, se.se_penEntity);
    se.se_peeEvent = ReadSignleEvent(strm);
    if (is_mandatory == TRUE)
      MarkEventMandatory(se.se_peeEvent);
  }

  ClearFrozenEntities();
  INDEX num_entities_in_za_warudo;
  *strm>>num_entities_in_za_warudo;
  for (INDEX ezw = 0; ezw < num_entities_in_za_warudo; ezw++)
  {
    CEntity* ent;
    ReadEventMember(strm, ent);
    MarkEntityAsInZaWarudo(ent, (ULONG)ent);
  }
  g_shouldResolveEvents = TRUE;
}

/*
Resolving is required because pointers to entities always have different
values. But entities that we point to, always have same unique ID. By that ID
we can and must restore the pointer value. This is used in network game and
during Save/Load cycle
*/
void ResolveJoJoEvents()
{
  for (INDEX iee = 0; iee < _aseSentEventsBackup.Count(); iee++)
  {
    CSentEvent& se = _aseSentEventsBackup[iee];
    ResolveEntityPointer(se.se_penEntity);
    ResolveSingleEvent(se.se_peeEvent);
  }
  FreezedEntity* current;
  FreezedEntity* tmp;
  HASH_ITER(hh, g_freezedEntities, current, tmp)
  {
    ResolveRawEntityPointer(current->p_entity);
  }
}

void ClearBackupEvents()
{
  ClearMandatoryEvents();

  for (INDEX iee = 0; iee < _aseSentEventsBackup.Count(); iee++)
  {
    CSentEvent& se = _aseSentEventsBackup[iee];
    se.se_penEntity = NULL;
    if (se.se_peeEvent != NULL)
      delete se.se_peeEvent;
    se.se_peeEvent = NULL;
  }
  _aseSentEventsBackup.PopAll();
  
  CStaticStackArray<CSentEvent>& _aseSentEvents = *_paseSentEvents;
  for (INDEX iee2 = 0; iee2 < _aseSentEvents.Count(); iee2++)
  {
    CSentEvent& se = _aseSentEvents[iee2];
    se.se_penEntity = NULL;
    if (se.se_peeEvent != NULL)
      delete se.se_peeEvent;
    se.se_peeEvent = NULL;
  }
  _aseSentEvents.PopAll();
}

/******************************/
/* Handle all sent events.    */
/******************************/
void JoJoHandleSentEvents()
{
  if (g_shouldResolveEvents == TRUE)
  {
    ResolveJoJoEvents();
    g_shouldResolveEvents = FALSE;
  }

  CStaticStackArray<CSentEvent>& _aseSentEvents = *_paseSentEvents;
  for (INDEX i = 0; i < _aseSentEventsBackup.Count(); ++i)
  {
    CSentEvent& se = _aseSentEvents.Push();
    CSentEvent& seBackup = _aseSentEventsBackup[i];
    se.se_penEntity.ep_pen = seBackup.se_penEntity.ep_pen;
    seBackup.se_penEntity.ep_pen = NULL;
    se.se_peeEvent = seBackup.se_peeEvent;
    seBackup.se_peeEvent = NULL;
  }
  _aseSentEventsBackup.PopAll();

  CSetFPUPrecision FPUPrecision(FPT_24BIT);

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
    // if the entity is not destroyed
    if (!(se.se_penEntity->en_ulFlags&ENF_DELETED))
    {
      if (g_musicHolder != NULL &&
          g_musicHolder->IsZaWarudo() &&
          !g_musicHolder->IsDioOrRelated(se.se_penEntity.ep_pen) &&
          entity_cast(se.se_penEntity.ep_pen, CItem) == NULL)
      {
        if (se.se_peeEvent->ee_slEvent != EVENTCODE_ETouch ||
            entity_cast(se.se_penEntity.ep_pen, CProjectile) == NULL ||
            !g_musicHolder->IsDioOrRelated(((ETouch*)se.se_peeEvent)->penOther))
        {
          CSentEvent& seBackup = _aseSentEventsBackup.Push();
          seBackup.se_penEntity.ep_pen = se.se_penEntity.ep_pen;
          se.se_penEntity.ep_pen = NULL;
          seBackup.se_peeEvent = se.se_peeEvent;
          se.se_peeEvent = NULL;

          if (seBackup.se_penEntity.ep_pen != NULL)
            FreezeEntityInZaWarudo(seBackup.se_penEntity.ep_pen);

          MarkEventMandatory(seBackup.se_peeEvent);
        }
        iFirstEvent++;
        continue;
      } else {
        // handle the current event
        CEntityEvent* peeEventWeirdBackup = se.se_peeEvent;
        if (se.se_peeEvent->ee_slEvent == EVENTCODE_EZaWarudoRestore)
        {
          // this event is purely custom, so handle it manually
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
            if (p_restore->restore_mass == TRUE)
            {
              EntityInfo* p_info = (EntityInfo*)p_movable->GetEntityInfo();
              p_info->fMass = p_restore->mass;
            }
          }
          if (p_restore->restore_physics == TRUE)
          {
            se.se_penEntity->SetPhysicsFlags(p_restore->physics_flags);
            se.se_penEntity->SetCollisionFlags(p_restore->collision_flags);
          }
        } else {
          se.se_penEntity->HandleEvent(*se.se_peeEvent);
        }
        se.se_peeEvent = peeEventWeirdBackup;
        RemoveEventFromMandatory(se.se_peeEvent);
      }
    }
    // go to next event
    iFirstEvent++;
  }

  // for each event
  for(INDEX iee=0; iee<_aseSentEvents.Count(); iee++)
  {
    CSentEvent &se = _aseSentEvents[iee];

    // if event is mandatory (i.e. it passed prediction check at some point)
    // but was not handled, leave it for the next tick and do not delete it
    if (IsEventMandatory(se.se_peeEvent))
    {
      CSentEvent& seBackup = _aseSentEventsBackup.Push();      
      seBackup.se_penEntity.ep_pen = se.se_penEntity.ep_pen;
      se.se_penEntity.ep_pen = NULL;
      seBackup.se_peeEvent = se.se_peeEvent;
      se.se_peeEvent = NULL;
    }

    // release the entity and destroy the event
    se.se_penEntity = NULL;
    if (se.se_peeEvent != NULL)
      delete se.se_peeEvent;
    se.se_peeEvent = NULL;
  }

  // flush all events
  _aseSentEvents.PopAll();
}
