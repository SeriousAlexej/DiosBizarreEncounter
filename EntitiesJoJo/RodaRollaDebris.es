952
%{
#include "StdH.h"
#include "EntitiesJoJo/jojo_events.h"
#include "EntitiesJoJo/entitycast.h"
#include "EntitiesMP/BackgroundViewer.h"
#include "EntitiesMP/WorldSettingsController.h"
%}

uses "EntitiesMP/BasicEffects";

event ELaunchRodaRollaDebris
{
  CEntityPointer penLauncher,
  INDEX iType,
};

%{
#define EPF_RODAROLLA_DEBRIS ( \
  EPF_ONBLOCK_BOUNCE|EPF_PUSHABLE|EPF_MOVABLE|EPF_TRANSLATEDBYGRAVITY|EPF_ABSOLUTETRANSLATE)

#define ECF_RODAROLLA_DEBRIS ( \
  ((ECBI_MODEL|ECBI_BRUSH|ECBI_PROJECTILE_MAGIC|ECBI_PROJECTILE_SOLID|ECBI_ITEM|ECBI_MODEL_HOLDER|ECBI_CORPSE_SOLID)<<ECB_TEST) |\
  ((ECBI_MODEL|ECBI_ENEMY)<<ECB_IS) | \
  ((ECBI_ENEMY)<<ECB_PASS))

void CRodaRollaDebris_OnPrecache(CDLLEntityClass* pdec, INDEX iUser) 
{
  pdec->PrecacheModel(MODEL_DEBRI_1);
  pdec->PrecacheModel(MODEL_DEBRI_2);
  pdec->PrecacheModel(MODEL_DEBRI_3);
  pdec->PrecacheModel(MODEL_DEBRI_4);
  pdec->PrecacheTexture(TEXTURE_RODA_ROLLA_DA);
  pdec->PrecacheTexture(TEX_SPEC_MEDIUM);
  pdec->PrecacheTexture(TEX_REFL_LIGHTMETAL01);
  pdec->PrecacheClass(CLASS_BASIC_EFFECT, BET_CANNON);
  pdec->PrecacheClass(CLASS_BASIC_EFFECT, BET_CANNONEXPLOSIONSTAIN);
  pdec->PrecacheClass(CLASS_BASIC_EFFECT, BET_CANNONSHOCKWAVE);
  pdec->PrecacheSound(SOUND_BALL_BOUNCE);
}

#define STRETCH_3  FLOAT3D(2.0f,2.0f,2.0f)
#define STRETCH_4  FLOAT3D(3.0f,3.0f,3.0f)
%}

class CRodaRollaDebris : CMovableModelEntity
{
name      "Roda Rolla Debris";
thumbnail "";
features  "ImplementsOnPrecache";

properties:
  1 CEntityPointer m_penOwner,
  2 INDEX          m_iNextChannel = 0,
  3 CSoundObject   m_soBounce0,
  4 CSoundObject   m_soBounce1,
  5 CSoundObject   m_soBounce2,
  6 CSoundObject   m_soBounce3,
  7 CSoundObject   m_soBounce4,

components:
  1 model   MODEL_DEBRI_1          "Models\\RODAROLLADA\\Debris\\01.mdl",
  2 model   MODEL_DEBRI_2          "Models\\RODAROLLADA\\Debris\\02.mdl",
  3 model   MODEL_DEBRI_3          "Models\\RODAROLLADA\\Debris\\03.mdl",
  4 model   MODEL_DEBRI_4          "Models\\RODAROLLADA\\Debris\\04.mdl",
  5 texture TEXTURE_RODA_ROLLA_DA  "Models\\RODAROLLADA\\WRYYYYYY.tex",
  6 texture TEX_SPEC_MEDIUM        "Models\\SpecularTextures\\Medium.tex",
  7 texture TEX_REFL_LIGHTMETAL01  "Models\\ReflectionTextures\\LightMetal01.tex",
  8 class   CLASS_BASIC_EFFECT     "Classes\\BasicEffect.ecl",
  9 sound   SOUND_BALL_BOUNCE      "Models\\Weapons\\Cannon\\Sounds\\Bounce.wav",

functions:

void SpawnEffect(const CPlacement3D& plEffect, const ESpawnEffect& eSpawnEffect)
{
  CEntityPointer penEffect = CreateEntity(plEffect, CLASS_BASIC_EFFECT);
  penEffect->SetParent(this);
  penEffect->Initialize(eSpawnEffect);
}

void RangeDamage()
{
  FLOAT hotSpot = 1.0f;
  FLOAT fallOff = 16.0f;
  InflictRangeDamage(this, DMT_CANNONBALL_EXPLOSION, 500.0f,
      GetPlacement().pl_PositionVector, hotSpot, fallOff);
}

void DamageEntity(CEntity* to_damage)
{
  if (to_damage != m_penOwner && entity_cast(to_damage, CMovableModelEntity))
  {
    FLOAT3D vDir = en_vCurrentTranslationAbsolute;
    vDir.Normalize();
    FLOAT3D vHit = GetPlacement().pl_PositionVector;
    InflictDirectDamage(to_damage, this, DMT_IMPACT, 200.0f, vHit, vDir);
  }
}

void BounceSound(FLOAT fSpeed)
{
  FLOAT fVolume = Clamp(fSpeed, 0.0f, 1.0f);
  if (fVolume<0.1f) {
    return;
  }
  CSoundObject &so = (&m_soBounce0)[m_iNextChannel];
  m_iNextChannel = (m_iNextChannel+1)%5;
  so.Set3DParameters(70.0f, 10.0f, fVolume, 1.0f);
  PlaySound(so, SOUND_BALL_BOUNCE, SOF_3D);
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

void ShakeIt()
{
  CWorldSettingsController *pwsc = NULL;
  CBackgroundViewer *penBcgViewer = (CBackgroundViewer *) GetWorld()->GetBackgroundViewer();

  if (penBcgViewer != NULL && penBcgViewer->m_penWorldSettingsController != NULL)
  {
    pwsc = (CWorldSettingsController*)&*penBcgViewer->m_penWorldSettingsController;
    pwsc->m_tmShakeStarted = _pTimer->CurrentTick();
    pwsc->m_vShakePos = GetPlacement().pl_PositionVector;
    pwsc->m_fShakeFalloff = 12.0f;
    pwsc->m_fShakeFade = 3.0f;
    pwsc->m_fShakeIntensityZ = 0.0f;
    pwsc->m_tmShakeFrequencyZ = 5.0f;
    pwsc->m_fShakeIntensityY = 0.1f;
    pwsc->m_tmShakeFrequencyY = 5.0f;
    pwsc->m_fShakeIntensityB = 15.0f;
    pwsc->m_tmShakeFrequencyB = 7.0f;
    pwsc->m_bShakeFadeIn = FALSE;
  }
}

procedures:

  Main(ELaunchRodaRollaDebris eLaunch)
  {
    m_penOwner = eLaunch.penLauncher;
    InitAsModel();
    SetPhysicsFlags(EPF_RODAROLLA_DEBRIS);
    SetCollisionFlags(ECF_RODAROLLA_DEBRIS);
    SetFlags(GetFlags() | ENF_SEETHROUGH);

    switch (eLaunch.iType)
    {
    case 0:
      SetModel(MODEL_DEBRI_1);
      break;
    case 1:
      SetModel(MODEL_DEBRI_2);
      break;
    case 2:
      SetModel(MODEL_DEBRI_3);
      break;
    case 3:
      SetModel(MODEL_DEBRI_4);
      break;
    }
    SetModelMainTexture(TEXTURE_RODA_ROLLA_DA);
    SetModelReflectionTexture(TEX_REFL_LIGHTMETAL01);
    SetModelSpecularTexture(TEX_SPEC_MEDIUM);

    wait(2.0f + FRnd() * 3.0f)
    {
      on (ETouch e) :
      {
        DamageEntity(e.penOther);
        BounceSound(((FLOAT3D&)e.plCollision) % en_vCurrentTranslationAbsolute);
        resume;
      }
      on (EPass e) :
      {
        DamageEntity(e.penOther);
        resume;
      }
      on (ETimer)   : { stop; }
      otherwise()   : { resume; }
    }

    ForceFullStop();
    SwitchToEditorModel();
    ShakeIt();
    RangeDamage();
    Explosion(FLOAT3D(0.0f,0.0f,0.0f),   STRETCH_3, STRETCH_3, STRETCH_4, TRUE, TRUE,  TRUE, TRUE);
    Explosion(FLOAT3D(1.0f,1.5f,1.5f),   STRETCH_3, STRETCH_3, STRETCH_4, TRUE, FALSE, FALSE, FALSE);
    Explosion(FLOAT3D(-2.0f,1.0f,-1.5f), STRETCH_3, STRETCH_3, STRETCH_4, TRUE, FALSE, FALSE, FALSE);
    Explosion(FLOAT3D(-1.0f,0.5f,1.0f),  STRETCH_4, STRETCH_4, STRETCH_4, TRUE, FALSE, FALSE, FALSE);

    SetPhysicsFlags(EPF_MODEL_IMMATERIAL);
    SetCollisionFlags(ECF_IMMATERIAL);
    autowait(ZA_WARUDO_DURATION * 2.0f);
    Destroy();
    return;
  }
};

