951
%{
#include "StdH.h"
#include "EntitiesJoJo/entitycast.h"
#include "EntitiesJoJo/jojo_events.h"
#include "EntitiesJoJo/RodaRollaDebris.h"
#include "EntitiesMP/MusicHolder.h"
#include "EntitiesMP/Player.h"
#include "EntitiesMP/PlayerWeapons.h"
#include "EntitiesMP/BackgroundViewer.h"
#include "EntitiesMP/WorldSettingsController.h"
#include "Models/RODAROLLADA/RODAROLLADA.h"
%}

uses "EntitiesMP/BasicEffects";

event ELaunchRodaRolla
{
  CEntityPointer penLauncher,
};

event ERodaRollaSaidFULLSTOP
{
};

%{
static const INDEX g_randomDebrisShuffles[24][4] =
{
  {0, 1, 2, 3},
  {0, 1, 3, 2},
  {0, 2, 1, 3},
  {0, 2, 3, 1},
  {0, 3, 1, 2},
  {0, 3, 2, 1},
  {1, 0, 2, 3},
  {1, 0, 3, 2},
  {1, 2, 0, 3},
  {1, 2, 3, 0},
  {1, 3, 0, 2},
  {1, 3, 2, 0},
  {2, 1, 0, 3},
  {2, 1, 3, 0},
  {2, 0, 1, 3},
  {2, 0, 3, 1},
  {2, 3, 1, 0},
  {2, 3, 0, 1},
  {3, 1, 2, 0},
  {3, 1, 0, 2},
  {3, 2, 1, 0},
  {3, 2, 0, 1},
  {3, 0, 1, 2},
  {3, 0, 2, 1}
};

#define EPF_RODA_ROLLA ( \
  EPF_PUSHABLE|EPF_MOVABLE|EPF_TRANSLATEDBYGRAVITY|EPF_ORIENTEDBYGRAVITY)

#define ECF_RODA_ROLLA ( \
  ((ECBI_MODEL|ECBI_PROJECTILE_MAGIC|ECBI_PROJECTILE_SOLID|ECBI_BRUSH|ECBI_MODEL_HOLDER|ECBI_CORPSE_SOLID)<<ECB_TEST) |\
  ((ECBI_MODEL)<<ECB_IS) | \
  ((ECBI_ENEMY|ECBI_ITEM)<<ECB_PASS))

void CRodaRollaDa_OnPrecache(CDLLEntityClass* pdec, INDEX iUser) 
{
  pdec->PrecacheTexture(TEX_SPEC_MEDIUM);
  pdec->PrecacheTexture(TEX_REFL_LIGHTMETAL01);
  pdec->PrecacheModel(MODEL_RODA_ROLLA_DA);
  pdec->PrecacheTexture(TEXTURE_RODA_ROLLA_DA);
  pdec->PrecacheTexture(TEXTURE_RODA_ROLLA_DA_LOW);
  pdec->PrecacheTexture(TEXTURE_RODA_ROLLA_DA_MED);
  pdec->PrecacheTexture(TEXTURE_RODA_ROLLA_DA_HI);
  pdec->PrecacheClass(CLASS_BASIC_EFFECT, BET_CANNON);
  pdec->PrecacheClass(CLASS_BASIC_EFFECT, BET_CANNONEXPLOSIONSTAIN);
  pdec->PrecacheClass(CLASS_BASIC_EFFECT, BET_CANNONSHOCKWAVE);
  pdec->PrecacheClass(CLASS_RODA_ROLLA_DEBRIS);
  pdec->PrecacheSound(SOUND_IMPACT_1);
  pdec->PrecacheSound(SOUND_IMPACT_2);
}

#define MAX_EXPLOSION_DAMAGE 6000.0f
#define BASE_EXPLOSION_DAMAGE 2000.0f
#define STRETCH_3  FLOAT3D(5.0f,5.0f,5.0f)
#define STRETCH_4  FLOAT3D(6.0f,6.0f,6.0f)
%}

class CRodaRollaDa : CMovableModelEntity
{
name      "RODA ROLLA DAAAAAAA";
thumbnail "";
features  "ImplementsOnPrecache";

properties:
  1 CEntityPointer m_penOwner,
  2 BOOL           m_isFlying = TRUE,
  3 INDEX          m_loopProtectionCounter = 0,
  4 FLOAT3D        m_launchDir = FLOAT3D(0.0f, 0.0f, 0.0f),
  5 FLOAT          m_explosionTime = 0.0f,
  6 FLOAT          m_explosionAccumulatedDamage = BASE_EXPLOSION_DAMAGE,
  7 CSoundObject   m_soundImpact,

components:
  1 model   MODEL_RODA_ROLLA_DA       "Models\\RODAROLLADA\\RODAROLLADA.mdl",
  2 texture TEXTURE_RODA_ROLLA_DA     "Models\\RODAROLLADA\\WRYYYYYY.tex",
  3 texture TEXTURE_RODA_ROLLA_DA_LOW "Models\\RODAROLLADA\\WRYYYYYY_01.tex",
  4 texture TEXTURE_RODA_ROLLA_DA_MED "Models\\RODAROLLADA\\WRYYYYYY_02.tex",
  5 texture TEXTURE_RODA_ROLLA_DA_HI  "Models\\RODAROLLADA\\WRYYYYYY_03.tex",
  6 texture TEX_SPEC_MEDIUM           "Models\\SpecularTextures\\Medium.tex",
  7 texture TEX_REFL_LIGHTMETAL01     "Models\\ReflectionTextures\\LightMetal01.tex",
  8 class   CLASS_BASIC_EFFECT        "Classes\\BasicEffect.ecl",
  9 class   CLASS_RODA_ROLLA_DEBRIS   "Classes\\RodaRollaDebris.ecl",
 10 sound   SOUND_IMPACT_1            "Sounds\\RodaRolla\\impact_1.wav",
 11 sound   SOUND_IMPACT_2            "Sounds\\RodaRolla\\impact_2.wav",

functions:

void RenderParticles()
{
  FLOAT fSpeedRatio = Min(en_vCurrentTranslationAbsolute.Length()/20.0f, 1.0f);
  INDEX ctFireParticles = INDEX( (Max( fSpeedRatio-0.5f, 0.0f)*2.0f)*128);
  Particles_BeastBigProjectileTrail(this, 7.0f, 2.0f, 1.0f, ctFireParticles);
  Particles_BeastBigProjectileTrail(this, 7.0f, -2.0f, 1.0f, ctFireParticles);
}

void ShakeIt()
{
  CWorldSettingsController *pwsc = NULL;
  CBackgroundViewer *penBcgViewer = (CBackgroundViewer *) GetWorld()->GetBackgroundViewer();

  if (penBcgViewer != NULL && penBcgViewer->m_penWorldSettingsController != NULL)
  {
    pwsc = (CWorldSettingsController*)&*penBcgViewer->m_penWorldSettingsController;
    pwsc->m_tmShakeStarted = _pTimer->CurrentTick();
    pwsc->m_vShakePos = GetPlacement().pl_PositionVector;
    pwsc->m_fShakeFalloff = 40.0f;
    pwsc->m_fShakeFade = 4.0f;
    pwsc->m_fShakeIntensityZ = 0.0f;
    pwsc->m_tmShakeFrequencyZ = 5.0f;
    pwsc->m_fShakeIntensityY = 0.1f;
    pwsc->m_tmShakeFrequencyY = 5.0f;
    pwsc->m_fShakeIntensityB = 30.0f;
    pwsc->m_tmShakeFrequencyB = 20.0f;
    pwsc->m_bShakeFadeIn = FALSE;
  }
}

void DamageEntity(CEntity* to_damage)
{
  if (to_damage != m_penOwner && entity_cast(to_damage, CMovableModelEntity))
  {
    FLOAT3D vDir = en_vCurrentTranslationAbsolute;
    vDir.Normalize();
    FLOAT3D vHit = GetPlacement().pl_PositionVector;
    InflictDirectDamage(to_damage, this, DMT_IMPACT, 1000.0f, vHit, vDir);
  }
}

BOOL HasStopped() const
{
  return (en_vCurrentTranslationAbsolute.Length() < 1.0f) ? TRUE : FALSE;
}

FLOAT FRndRange(FLOAT fMin, FLOAT fMax)
{
  return FRnd()*(fMax - fMin) + fMin;
}

void SpawnDebris()
{
  ANGLE3D angle_1 = ANGLE3D(FRndRange(-180.0f, 180.0f), FRndRange(-180.0f, 180.0f), FRndRange(-180.0f, 180.0f));
  ANGLE3D angle_2 = ANGLE3D(FRndRange(-180.0f, 180.0f), FRndRange(-180.0f, 180.0f), FRndRange(-180.0f, 180.0f));
  ANGLE3D angle_3 = ANGLE3D(FRndRange(-180.0f, 180.0f), FRndRange(-180.0f, 180.0f), FRndRange(-180.0f, 180.0f));
  ANGLE3D angle_4 = ANGLE3D(FRndRange(-180.0f, 180.0f), FRndRange(-180.0f, 180.0f), FRndRange(-180.0f, 180.0f));

  CPlacement3D plDebri_1(FLOAT3D(0.0f, 4.0f, 0.0f), angle_1);
  CPlacement3D plDebri_2(FLOAT3D(0.0f, 4.0f, 0.0f), angle_2);
  CPlacement3D plDebri_3(FLOAT3D(0.0f, 4.0f, 0.0f), angle_3);
  CPlacement3D plDebri_4(FLOAT3D(0.0f, 4.0f, 0.0f), angle_4);
  plDebri_1.RelativeToAbsolute(GetPlacement());
  plDebri_2.RelativeToAbsolute(GetPlacement());
  plDebri_3.RelativeToAbsolute(GetPlacement());
  plDebri_4.RelativeToAbsolute(GetPlacement());

  INDEX shuffleChoice = IRnd()%24;
  FLOAT baseImpulse = 20.0f;
  ELaunchRodaRollaDebris eLaunch;
  eLaunch.penLauncher = m_penOwner;
  CEntityPointer penDebris;

  penDebris = CreateEntity(plDebri_1, CLASS_RODA_ROLLA_DEBRIS);
  eLaunch.iType = g_randomDebrisShuffles[shuffleChoice][0];
  penDebris->Initialize(eLaunch);
  ((CRodaRollaDebris*)&*penDebris)->GiveImpulseTranslationRelative(
    FLOAT3D(baseImpulse + FRndRange(-7.0f, 7.0f), baseImpulse + FRndRange(-7.0f, 7.0f), baseImpulse + FRndRange(-7.0f, 7.0f)));
  ((CRodaRollaDebris*)&*penDebris)->SetDesiredRotation(angle_1);

  penDebris = CreateEntity(plDebri_2, CLASS_RODA_ROLLA_DEBRIS);
  eLaunch.iType = g_randomDebrisShuffles[shuffleChoice][1];
  penDebris->Initialize(eLaunch);
  ((CRodaRollaDebris*)&*penDebris)->GiveImpulseTranslationRelative(
    FLOAT3D(baseImpulse + FRndRange(-7.0f, 7.0f), baseImpulse + FRndRange(-7.0f, 7.0f), -baseImpulse + FRndRange(-7.0f, 7.0f)));
  ((CRodaRollaDebris*)&*penDebris)->SetDesiredRotation(angle_2);
  
  penDebris = CreateEntity(plDebri_3, CLASS_RODA_ROLLA_DEBRIS);
  eLaunch.iType = g_randomDebrisShuffles[shuffleChoice][2];
  penDebris->Initialize(eLaunch);
  ((CRodaRollaDebris*)&*penDebris)->GiveImpulseTranslationRelative(
    FLOAT3D(-baseImpulse + FRndRange(-7.0f, 7.0f), baseImpulse + FRndRange(-7.0f, 7.0f), baseImpulse + FRndRange(-7.0f, 7.0f)));
  ((CRodaRollaDebris*)&*penDebris)->SetDesiredRotation(angle_3);

  penDebris = CreateEntity(plDebri_4, CLASS_RODA_ROLLA_DEBRIS);
  eLaunch.iType = g_randomDebrisShuffles[shuffleChoice][3];
  penDebris->Initialize(eLaunch);
  ((CRodaRollaDebris*)&*penDebris)->GiveImpulseTranslationRelative(
    FLOAT3D(-baseImpulse + FRndRange(-7.0f, 7.0f), baseImpulse + FRndRange(-7.0f, 7.0f), -baseImpulse + FRndRange(-7.0f, 7.0f)));
  ((CRodaRollaDebris*)&*penDebris)->SetDesiredRotation(angle_4);
}

void SpawnEffect(const CPlacement3D& plEffect, const ESpawnEffect& eSpawnEffect)
{
  CEntityPointer penEffect = CreateEntity(plEffect, CLASS_BASIC_EFFECT);
  penEffect->SetParent(this);
  penEffect->Initialize(eSpawnEffect);
}

void HitSound()
{
  m_soundImpact.Set3DParameters(200.0f, 50.0f, 3.0f, 1.0f + FRndRange(-0.2f, 0.2f));
  PlaySound(m_soundImpact, SOUND_IMPACT_1 + (IRnd()%2), SOF_3D);
}

void RangeDamage()
{
  FLOAT hotSpot = 1.0f;
  FLOAT fallOff = 32.0f;
  InflictRangeDamage(this, DMT_CANNONBALL_EXPLOSION, m_explosionAccumulatedDamage,
      GetPlacement().pl_PositionVector, hotSpot, fallOff);
}

void Explosion(FLOAT3D vCenter,
               const FLOAT3D &vStretchExplosion,
               const FLOAT3D &vStretchShockwave,
               const FLOAT3D &vStretchStain,
               BOOL bHasExplosion,
               BOOL bHasShockWave,
               BOOL bHasStain,
               BOOL bHasLight)
{
  ESpawnEffect ese;
  FLOAT3D vOnPlane;
  FLOATplane3D vPlaneNormal;
  FLOAT fDistanceToEdge;
  
  // explosion
  if( bHasExplosion)
  {
    ese.colMuliplier = C_WHITE|CT_OPAQUE;
    if( bHasLight)
    {
      ese.betType = BET_CANNON;
    }
    else
    {
      ese.betType = BET_CANNON_NOLIGHT;
    }
    ese.vStretch = vStretchExplosion;
    CPlacement3D plHandle = GetPlacement();
    plHandle.pl_PositionVector+=vCenter;
    SpawnEffect(plHandle, ese);
  }
  // on plane
  if (GetNearestPolygon(vOnPlane, vPlaneNormal, fDistanceToEdge)) {
    if ((vOnPlane-GetPlacement().pl_PositionVector).Length() < 3.5f) {
      if( bHasStain)
      {
        // wall stain
        ese.colMuliplier = C_WHITE|CT_OPAQUE;
        ese.betType = BET_CANNONEXPLOSIONSTAIN;
        ese.vNormal = FLOAT3D(vPlaneNormal);
        ese.vStretch = vStretchShockwave;
        SpawnEffect(CPlacement3D(vOnPlane, ANGLE3D(0, 0, 0)), ese);
      }
      if( bHasShockWave)
      {
        // shock wave horizontal
        ese.colMuliplier = C_WHITE|CT_OPAQUE;
        ese.betType = BET_CANNONSHOCKWAVE;
        ese.vNormal = FLOAT3D(vPlaneNormal);
        ese.vStretch = vStretchShockwave;
        SpawnEffect(CPlacement3D(vOnPlane, ANGLE3D(0, 0, 0)), ese);
      }
    }
  }

}

procedures:

  Fly()
  {
    CEntity* pObstacle;
    if (CheckForCollisionNow(0, &pObstacle))
    {
      m_isFlying = FALSE;
      DamageEntity(pObstacle);
    }

    while (m_isFlying)
    {
      wait (0.1f)
      {
        on (EBegin) :
        {
          AddToMovers();
          if (m_loopProtectionCounter == 0) {
            m_launchDir = FLOAT3D(0.0f, 0.0f, -50.0f) * en_mRotation;
            GiveImpulseTranslationAbsolute(m_launchDir);
            m_penOwner->SendEvent(ERodaRollaSaidFULLSTOP());
          } else if (m_loopProtectionCounter == 1) {
            EDioInstantKick e;
            e.dir = m_launchDir;
            m_penOwner->SendEvent(e);
          } else if (m_loopProtectionCounter > 120 || HasStopped()) {
            m_isFlying = FALSE;
          }
          m_loopProtectionCounter++;
          resume;
        }
        on (EPass ePass) :
        {
          DamageEntity(ePass.penOther);
          resume;
        }
        on (ETouch eTouch) :
        {
          DamageEntity(eTouch.penOther);
          HitSound();
          Explosion(FLOAT3D(0.0f,0.0f,0.0f), STRETCH_3, STRETCH_3, STRETCH_4, FALSE, TRUE,  TRUE, FALSE);
          resume;
        }
        on (ETimer) :
        {
          stop;
        }
        otherwise() : { resume; }
      }
    }

    ShakeIt();
    return EEnd();
  }

  WaitForExplosion()
  {
    CPlayer& pl = *((CPlayer*)&*m_penOwner);
    CMusicHolder& mh = *((CMusicHolder*)&*pl.m_penMainMusicHolder);
    FLOAT time_1 = mh.m_timeZaWarudoStart + ZA_WARUDO_DURATION + 3.0f;
    FLOAT time_2 = _pTimer->CurrentTick() + 3.0f;
    if (time_1 > time_2) {
      m_explosionTime = time_1;
    } else {
      m_explosionTime = time_2;
    }

    while (m_explosionTime > _pTimer->CurrentTick())
    {
      wait (0.1f)
      {
        on (EBegin) :
        {
          AddToMovers();
          resume;
        }
        on (EDamage eDamage) :
        {
          m_explosionAccumulatedDamage = ClampUp(
            m_explosionAccumulatedDamage + eDamage.fAmount,
            MAX_EXPLOSION_DAMAGE);
          
          FLOAT gained_percentage = (m_explosionAccumulatedDamage - BASE_EXPLOSION_DAMAGE) / (MAX_EXPLOSION_DAMAGE - BASE_EXPLOSION_DAMAGE);
          if (gained_percentage <= 0.33f) {
            GetModelObject()->PlayAnim(RODAROLLADA_ANIM_DMGLOW, AOF_NORESTART);
            SetModelMainTexture(TEXTURE_RODA_ROLLA_DA_LOW);
          } else if (gained_percentage <= 0.66f) {
            GetModelObject()->PlayAnim(RODAROLLADA_ANIM_DMGMED, AOF_NORESTART);
            SetModelMainTexture(TEXTURE_RODA_ROLLA_DA_MED);
          } else {
            GetModelObject()->PlayAnim(RODAROLLADA_ANIM_DMGHI, AOF_NORESTART);
            SetModelMainTexture(TEXTURE_RODA_ROLLA_DA_HI);
          }
          //CPrintF("DAMAGE WILL BE %f\n", m_explosionAccumulatedDamage);
          resume;
        }
        on (ETimer) :
        {
          stop;
        }
        otherwise() : { resume; }
      }
    }

    ForceFullStop();
    SwitchToEditorModel();
    return EEnd();
  }

  Main(ELaunchRodaRolla eLaunch)
  {
    m_penOwner = eLaunch.penLauncher;
    InitAsModel();
    SetPhysicsFlags(EPF_RODA_ROLLA);
    SetCollisionFlags(ECF_RODA_ROLLA);
    SetModel(MODEL_RODA_ROLLA_DA);
    SetModelMainTexture(TEXTURE_RODA_ROLLA_DA);
    SetModelReflectionTexture(TEX_REFL_LIGHTMETAL01);
    SetModelSpecularTexture(TEX_SPEC_MEDIUM);

    autowait(0.1f);
    autocall Fly() EEnd;
    autocall WaitForExplosion() EEnd;

    RangeDamage();
    Explosion(FLOAT3D(0.0f,0.0f,0.0f),   STRETCH_3, STRETCH_3, STRETCH_4, TRUE, TRUE,  TRUE, TRUE);
    Explosion(FLOAT3D(1.0f,1.5f,1.5f),   STRETCH_3, STRETCH_3, STRETCH_4, TRUE, FALSE, FALSE, FALSE);
    Explosion(FLOAT3D(-2.0f,1.0f,-1.5f), STRETCH_3, STRETCH_3, STRETCH_4, TRUE, FALSE, FALSE, FALSE);
    Explosion(FLOAT3D(-1.0f,0.5f,1.0f),  STRETCH_4, STRETCH_4, STRETCH_4, TRUE, FALSE, FALSE, FALSE);

    extern CMusicHolder* g_musicHolder;
    if (g_musicHolder == NULL || !g_musicHolder->IsZaWarudo())
    {
      SpawnDebris();
      ShakeIt();
    }

    SetPhysicsFlags(EPF_MODEL_IMMATERIAL);
    SetCollisionFlags(ECF_IMMATERIAL);
    autowait(ZA_WARUDO_DURATION * 2.0f);
    Destroy();
    return;
  }
};