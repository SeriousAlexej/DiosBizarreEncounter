951
%{
#include "StdH.h"
#include "EntitiesJoJo/entitycast.h"
#include "EntitiesMP/BasicEffects.h"
%}

event ELaunchRodaRolla
{
  CEntityPointer penLauncher,
};

%{
#define EPF_RODA_ROLLA ( \
  EPF_PUSHABLE|EPF_MOVABLE|EPF_TRANSLATEDBYGRAVITY|EPF_ORIENTEDBYGRAVITY)

#define ECF_RODA_ROLLA ( \
  ((ECBI_MODEL|ECBI_BRUSH|ECBI_PROJECTILE_MAGIC|ECBI_PROJECTILE_SOLID|ECBI_ITEM|ECBI_MODEL_HOLDER|ECBI_CORPSE_SOLID)<<ECB_TEST) |\
  ((ECBI_MODEL)<<ECB_IS) | \
  ((ECBI_ENEMY)<<ECB_PASS))

void CRodaRollaDa_OnPrecache(CDLLEntityClass* pdec, INDEX iUser) 
{
  pdec->PrecacheTexture(TEX_SPEC_MEDIUM);
  pdec->PrecacheTexture(TEX_REFL_LIGHTMETAL01);
  pdec->PrecacheModel(MODEL_RODA_ROLLA_DA);
  pdec->PrecacheTexture(TEXTURE_RODA_ROLLA_DA);
  pdec->PrecacheClass(CLASS_BASIC_EFFECT, BET_DUST_FALL);
  pdec->PrecacheClass(CLASS_BASIC_EFFECT, BET_CANNONSHOCKWAVE);
}
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

components:
  1 model   MODEL_RODA_ROLLA_DA       "Models\\RODAROLLADA\\RODAROLLADA.mdl",
  2 texture TEXTURE_RODA_ROLLA_DA     "Models\\RODAROLLADA\\WRYYYYYY.tex",
  3 texture TEX_SPEC_MEDIUM           "Models\\SpecularTextures\\Medium.tex",
  4 texture TEX_REFL_LIGHTMETAL01     "Models\\ReflectionTextures\\LightMetal01.tex",
  5 class   CLASS_BASIC_EFFECT        "Classes\\BasicEffect.ecl",

functions:

void RenderParticles(void)
{
  FLOAT fSpeedRatio = Min(en_vCurrentTranslationAbsolute.Length()/20.0f, 1.0f);
  INDEX ctFireParticles = INDEX( (Max( fSpeedRatio-0.5f, 0.0f)*2.0f)*128);
  Particles_BeastBigProjectileTrail(this, 7.0f, 2.0f, 1.0f, ctFireParticles);
  Particles_BeastBigProjectileTrail(this, 7.0f, -2.0f, 1.0f, ctFireParticles);
}

void DamageEntity(CEntity* to_damage)
{
  if (to_damage != m_penOwner && entity_cast(to_damage, CMovableModelEntity))
  {
    FLOAT3D vDir = en_vCurrentTranslationAbsolute;
    vDir.Normalize();
    FLOAT3D vHit = GetPlacement().pl_PositionVector;
    InflictDirectDamage(to_damage, m_penOwner, DMT_CLOSERANGE, 750.0f, vHit, vDir);
  }
}

BOOL HasStopped() const
{
  return (en_vCurrentTranslationAbsolute.Length() < 1.0f) ? TRUE : FALSE;
}

void SpawnEffect(BasicEffectType eEffectType)
{
  CPlacement3D plSmoke=GetPlacement();
  FLOATmatrix3D m;
  MakeRotationMatrixFast(m, plSmoke.pl_OrientationAngle);
  ESpawnEffect ese;
  ese.colMuliplier = C_WHITE|CT_OPAQUE;
  ese.vStretch = FLOAT3D(4.0f, 4.0f, 2.0f);
  ese.vNormal = FLOAT3D(m(1,2), m(2,2), m(3,2));
  ese.betType = eEffectType;
  plSmoke.pl_PositionVector+=FLOAT3D(0,0.2f*ese.vStretch(2),0);
  CEntityPointer penFX = CreateEntity(plSmoke, CLASS_BASIC_EFFECT);
  penFX->Initialize(ese);
  penFX->SetParent(this);
}

void HitSound()
{
  CPrintF("BAAAAAM!\n");
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
            ((CMovableEntity*)&*m_penOwner)->ForceFullStop();
          } else if (m_loopProtectionCounter == 1) {
            ((CMovableEntity*)&*m_penOwner)->GiveImpulseTranslationAbsolute(m_launchDir);
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
          SpawnEffect(BET_DUST_FALL);
          SpawnEffect(BET_CANNONSHOCKWAVE);
          resume;
        }
        on (ETimer) :
        {
          stop;
        }
        otherwise() : { resume; }
      }
    }

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
    ForceFullStop();

    autowait(10.0f);

    Destroy();
    return;
  }
};