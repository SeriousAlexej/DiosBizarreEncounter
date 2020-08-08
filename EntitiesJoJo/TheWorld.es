950
%{
#include "StdH.h"
#include "EntitiesMP/Player.h"
#include "EntitiesMP/PlayerWeapons.h"
#include "EntitiesMP/Reminder.h"
#include "EntitiesJoJo/jojo_events.h"

#include "Models/ZAWARUDO/ZaWarudo.h"
%}

event ESpawnStand
{
  CEntityPointer penOwner,
};

enum StandMode
{
  0 STAND_PASSIVE "", // follow player
  1 STAND_ENGAGED "", // controlled by player
};

%{
void CTheWorld_Precache()
{
  CDLLEntityClass* pdec = &CTheWorld_DLLClass;
  pdec->PrecacheModel(MODEL_ZAWARUDO);
  pdec->PrecacheModel(MODEL_LEFT_HAND);
  pdec->PrecacheModel(MODEL_RIGHT_HAND);
  pdec->PrecacheModel(MODEL_RIGHT_LEG);
  pdec->PrecacheTexture(TEXTURE_ZAWARUDO);
  pdec->PrecacheTexture(TEXTURE_ZAWARUDO_OPAQUE);
  pdec->PrecacheTexture(TEXTURE_REFLECT);
  pdec->PrecacheTexture(TEXTURE_SPECULAR);
}

#define ECF_STAND ( \
  ((ECBI_PROJECTILE_MAGIC|ECBI_PROJECTILE_SOLID)<<ECB_TEST) |\
  ((ECBI_MODEL)<<ECB_IS))

#define EPF_STAND ( \
  EPF_MOVABLE | EPF_ABSOLUTETRANSLATE | EPF_ORIENTEDBYGRAVITY)

#define ATTACHMENT_HANDS 0x1
#define ATTACHMENT_LEG   0x2

#define ZAWARUDO_START 42
#define ZAWARUDO_END   43
%}

class CTheWorld : CMovableModelEntity
{
name      "The World";
thumbnail "";
features "CanBePredictable";

properties:
  1 CEntityPointer m_penOwner,
  2 FLOAT          m_timeSpawned      = 0.0f,
  3 FLOAT          m_offsetX          = 2.0f,
  4 FLOAT          m_offsetZ          = -2.0f,
  5 BOOL           m_isActive         = TRUE,
  6 INDEX          m_addedAttachments = 0x0,
  7 BOOL           m_isTimeStopped    = FALSE,
  8 FLOAT          m_moveSpeed        = 1.0f,
  9 BOOL           m_isDying          = FALSE

{
CPlacement3D m_plLast;
TIME         m_tmParticlesActive;
FLOAT        m_particlesOpacityPrev;
FLOAT        m_particlesOpacity;
}

components:
  1 model   MODEL_ZAWARUDO          "Models\\ZAWARUDO\\ZaWarudo.mdl",
  2 texture TEXTURE_ZAWARUDO        "Models\\ZAWARUDO\\ZaWarudo.tex",
  3 texture TEXTURE_REFLECT         "Models\\ReflectionTextures\\Purple01.tex",
  4 texture TEXTURE_SPECULAR        "Models\\SpecularTextures\\Medium.tex",
  5 model   MODEL_LEFT_HAND         "Models\\ZAWARUDO\\ZaWarudoHand_Left.mdl",
  6 model   MODEL_RIGHT_HAND        "Models\\ZAWARUDO\\ZaWarudoHand_Right.mdl",
  7 model   MODEL_RIGHT_LEG         "Models\\ZAWARUDO\\ZaWarudoLeg_Right.mdl",
  8 texture TEXTURE_ZAWARUDO_OPAQUE "Models\\ZAWARUDO\\ZaWarudo_Opaque.tex"

functions:

  CPlacement3D GetLerpedPlacement() const
  {
    if (m_penOwner && (((CPlayer*)m_penOwner.ep_pen)->m_mode == STAND_ENGAGED && m_isActive)) {
      return m_penOwner->GetLerpedPlacement();
    }

    FLOAT fLerpFactor;
    if (IsPredictor()) {
      fLerpFactor = _pTimer->GetLerpFactor();
    } else {
      fLerpFactor = _pTimer->GetLerpFactor2();
    }
    CPlacement3D plLerped;
    plLerped.Lerp(m_plLast, en_plPlacement, fLerpFactor);
    return plLerped;
  }

  CPlacement3D GetDesiredPlacement() const
  {
    const CPlayer& player = ((CPlayer&)*(m_penOwner.ep_pen->GetPredictionTail()));
    const CPlacement3D view_rotation(FLOAT3D(0.0f, 0.0f, 0.0f), ANGLE3D(player.en_plViewpoint.pl_OrientationAngle(1), 0.0f, 0.0f));

    CPlacement3D stand_offset_1(FLOAT3D(m_offsetX, 0.0f, m_offsetZ), ANGLE3D(10.0f, 0.0f, 0.0f));
    stand_offset_1.RelativeToAbsoluteSmooth(view_rotation);
    stand_offset_1.RelativeToAbsoluteSmooth(player.GetPlacement());
    
    CPlacement3D stand_offset_2(FLOAT3D(-m_offsetX, 0.0f, m_offsetZ), ANGLE3D(-10.0f, 0.0f, 0.0f));
    stand_offset_2.RelativeToAbsoluteSmooth(view_rotation);
    stand_offset_2.RelativeToAbsoluteSmooth(player.GetPlacement());

    FLOAT3D to_pos_1 = GetPlacement().pl_PositionVector - stand_offset_1.pl_PositionVector;
    FLOAT3D to_pos_2 = GetPlacement().pl_PositionVector - stand_offset_2.pl_PositionVector;

    FLOAT distance2_1 = to_pos_1(1)*to_pos_1(1) + to_pos_1(2)*to_pos_1(2) + to_pos_1(3)*to_pos_1(3);
    FLOAT distance2_2 = to_pos_2(1)*to_pos_2(1) + to_pos_2(2)*to_pos_2(2) + to_pos_2(3)*to_pos_2(3);

    if (distance2_1 < distance2_2) {
      return stand_offset_1;
    }
    return stand_offset_2;
  }

  void MoveToPlayer()
  {
    static const float ROTATION_EPSILON = 0.05f;

    CPlacement3D curr_placement = GetPlacement();
    m_plLast = curr_placement;
    const CPlacement3D dest_placement = GetDesiredPlacement();

    FLOAT3D vToDestination = dest_placement.pl_PositionVector - curr_placement.pl_PositionVector;
    FLOAT distance_to_dest = vToDestination.Length();
    vToDestination.SafeNormalize();
    if (distance_to_dest > 4.0f * m_moveSpeed) {
      curr_placement.pl_PositionVector += vToDestination * (distance_to_dest - 4.0f);
    } else {
      FLOAT coeff = distance_to_dest * 0.25f * m_moveSpeed;
      curr_placement.pl_PositionVector += vToDestination * coeff;
    }
    SetPlacement(curr_placement);

    CPlacement3D dest_view_shift(FLOAT3D(0.0f, 0.0f, -1.0f), ANGLE3D(0.0f, 0.0f, 0.0f));
    dest_view_shift.RelativeToAbsoluteSmooth(dest_placement);
    ANGLE aToDestinationH = GetRelativeHeading(dest_view_shift.pl_PositionVector - dest_placement.pl_PositionVector);
    aToDestinationH = NormalizeAngle(aToDestinationH);

    FLOAT rotation_speed = 270.0f;
    if (aToDestinationH < -rotation_speed*_pTimer->TickQuantum) {
      aToDestinationH = -rotation_speed;
    } else if (aToDestinationH > rotation_speed*_pTimer->TickQuantum) {
      aToDestinationH = +rotation_speed;
    } else {
      aToDestinationH = aToDestinationH / _pTimer->TickQuantum;
    }
    if (Abs(aToDestinationH) < ROTATION_EPSILON) {
      aToDestinationH = 0.0f;
    }

    if (vToDestination(1) == 0.0f && vToDestination(2) == 0.0f && vToDestination(3) == 0.0f && aToDestinationH == 0.0f) {
      ForceFullStop();
    } else {
      SetDesiredRotation(ANGLE3D(aToDestinationH, 0.0f, 0.0f));
    }
  }
  
  void PreMoving()
  {
    if (m_penOwner && (((CPlayer*)m_penOwner.ep_pen)->m_mode == STAND_PASSIVE || !m_isActive)) {
      MoveToPlayer();
    }
    CMovableModelEntity::PreMoving();
  }
  
  void AdjustMipFactor(FLOAT& fMipFactor)
  {
    CModelObject* pmo = GetModelObject();

    if (pmo->GetAnim() == ZAWARUDO_ANIM_EMERGE)
    {
      FLOAT fFade = (_pTimer->GetLerpedCurrentTick() - m_timeSpawned) / pmo->GetAnimLength(ZAWARUDO_ANIM_EMERGE);
      pmo->mo_colBlendColor = (pmo->mo_colBlendColor&~255)|UBYTE(255*fFade);
    }
    else if (m_isDying)
    {
      FLOAT fFade = ClampUp((_pTimer->GetLerpedCurrentTick() - m_timeSpawned) / pmo->GetAnimLength(ZAWARUDO_ANIM_DIE), 1.0f);
      pmo->mo_colBlendColor = (pmo->mo_colBlendColor&~255)|UBYTE(255*(1.0f - fFade));
    }
    else if (m_penOwner && ((CPlayer*)m_penOwner.ep_pen)->m_iViewState == PVT_PLAYEREYES)
    {
      FLOAT fDistance = (GetPlacement().pl_PositionVector - m_penOwner->GetPlacement().pl_PositionVector).Length();
      fDistance = ClampUp(fDistance, 1.0f);
      if (fDistance < 1.0f) {
        fDistance = fDistance*fDistance*0.5f;
      }
      pmo->mo_colBlendColor = (pmo->mo_colBlendColor&~255)|UBYTE(255*fDistance);
    } else {
      pmo->mo_colBlendColor = pmo->mo_colBlendColor|UBYTE(255);
    }
  }

  void AddAttachmentModel(INDEX iAttachment, ULONG ulIDModel)
  {
    AddAttachmentToModel(this, *GetModelObject(), iAttachment, ulIDModel, TEXTURE_ZAWARUDO, 0, 0, 0);
  }

  void RemoveAttachments(INDEX iToRemove)
  {
    if (iToRemove & ATTACHMENT_HANDS) {
      GetModelObject()->RemoveAttachmentModel(ZAWARUDO_ATTACHMENT_RIGHT_1);
      GetModelObject()->RemoveAttachmentModel(ZAWARUDO_ATTACHMENT_RIGHT_2);
      GetModelObject()->RemoveAttachmentModel(ZAWARUDO_ATTACHMENT_RIGHT_3);
      GetModelObject()->RemoveAttachmentModel(ZAWARUDO_ATTACHMENT_LEFT_1);
      GetModelObject()->RemoveAttachmentModel(ZAWARUDO_ATTACHMENT_LEFT_2);
      GetModelObject()->RemoveAttachmentModel(ZAWARUDO_ATTACHMENT_LEFT_3);
    }
    if (iToRemove & ATTACHMENT_LEG) {
      GetModelObject()->RemoveAttachmentModel(ZAWARUDO_ATTACHMENT_RIGHTLEG_1);
      GetModelObject()->RemoveAttachmentModel(ZAWARUDO_ATTACHMENT_RIGHTLEG_2);
      GetModelObject()->RemoveAttachmentModel(ZAWARUDO_ATTACHMENT_RIGHTLEG_3);
    }
    m_addedAttachments &= ~iToRemove;
  }

  BOOL CanPlayAnim()
  {
    return GetModelObject()->GetAnim() != ZAWARUDO_ANIM_STOPTIME;
  }

  void IdleAnim()
  {
    RemoveAttachments(~0);

    if (CanPlayAnim()) {
      GetModelObject()->PlayAnim(ZAWARUDO_ANIM_IDLE, AOF_LOOPING|AOF_NORESTART);
    }
  }

  void HandsAnim()
  {
    RemoveAttachments(~ATTACHMENT_HANDS);

    if (CanPlayAnim()) {
      GetModelObject()->PlayAnim(ZAWARUDO_ANIM_ATTACKHANDS, AOF_LOOPING|AOF_NORESTART);
      if (!(m_addedAttachments & ATTACHMENT_HANDS)) {
        m_tmParticlesActive = _pTimer->CurrentTick() + 3.0f;
        m_addedAttachments |= ATTACHMENT_HANDS;
        AddAttachmentModel(ZAWARUDO_ATTACHMENT_RIGHT_1, MODEL_RIGHT_HAND);
        AddAttachmentModel(ZAWARUDO_ATTACHMENT_RIGHT_2, MODEL_RIGHT_HAND);
        AddAttachmentModel(ZAWARUDO_ATTACHMENT_RIGHT_3, MODEL_RIGHT_HAND);
        AddAttachmentModel(ZAWARUDO_ATTACHMENT_LEFT_1, MODEL_LEFT_HAND);
        AddAttachmentModel(ZAWARUDO_ATTACHMENT_LEFT_2, MODEL_LEFT_HAND);
        AddAttachmentModel(ZAWARUDO_ATTACHMENT_LEFT_3, MODEL_LEFT_HAND);
      }
    }
  }

  void LegsAnim()
  {
    RemoveAttachments(~ATTACHMENT_LEG);

    if (CanPlayAnim()) {
      GetModelObject()->PlayAnim(ZAWARUDO_ANIM_ATTACKLEG, AOF_LOOPING|AOF_NORESTART);
      if (!(m_addedAttachments & ATTACHMENT_LEG)) {
        m_tmParticlesActive = _pTimer->CurrentTick() + 3.0f;
        m_addedAttachments |= ATTACHMENT_LEG;
        AddAttachmentModel(ZAWARUDO_ATTACHMENT_RIGHTLEG_1, MODEL_RIGHT_LEG);
        AddAttachmentModel(ZAWARUDO_ATTACHMENT_RIGHTLEG_2, MODEL_RIGHT_LEG);
        AddAttachmentModel(ZAWARUDO_ATTACHMENT_RIGHTLEG_3, MODEL_RIGHT_LEG);
      }
    }
  }

  void ThrowAnim()
  {
    RemoveAttachments(~0);

    if (CanPlayAnim()) {
      GetModelObject()->PlayAnim(ZAWARUDO_ANIM_THROW_KNIVES_1 + IRnd()%2, 0);
    }
  }

  void RenderParticles()
  {
    if (m_particlesOpacity > 0.0f) {
      Particles_Menacing(this, Lerp(m_particlesOpacityPrev, m_particlesOpacity, _pTimer->GetLerpFactor()));
    }
  }

procedures:

  Alive()
  {
    while (m_isActive)
    {
      wait (0.05f)
      {
        on (EBegin) :
        {
          m_particlesOpacityPrev = m_particlesOpacity;
          if (m_tmParticlesActive > _pTimer->CurrentTick()) {
            m_particlesOpacity = ClampUp(m_particlesOpacity + 0.025f, 1.0f);
          } else {
            m_particlesOpacity = ClampDn(m_particlesOpacity - 0.025f, 0.0f);
          }
          AddToMovers();
          resume;
        }
        on (EReminder eReminder) :
        {
          if (!IsPredictor())
          {
            if (eReminder.iValue == ZAWARUDO_START)
            {
              extern BOOL g_shouldInverse;
              g_shouldInverse = (rand() & 1) ? TRUE : FALSE;
              EZaWarudo za_warudo;
              za_warudo.penDio = m_penOwner->GetPredictionTail();
              CPlayer& player = (CPlayer&)*za_warudo.penDio.ep_pen;
              player.m_penMainMusicHolder->SendEvent(za_warudo);
              SpawnReminder(this, ZA_WARUDO_DURATION, ZAWARUDO_END);
            }
            else if (eReminder.iValue == ZAWARUDO_END)
            {
              m_isTimeStopped = FALSE;
            }
            else if (eReminder.iValue == GetModelObject()->GetAnim()) 
            {
              m_offsetX = 2.0f;
              m_offsetZ = -2.0f;
              m_moveSpeed = 1.0f;
              RemoveAttachments(~0);
              GetModelObject()->PlayAnim(ZAWARUDO_ANIM_IDLE, AOF_LOOPING|AOF_NORESTART);
            }
          }
          resume;
        }
        on (EStart) :
        {
          if (m_isTimeStopped == FALSE)
          {
            m_isTimeStopped = TRUE;
            m_offsetX = 1.0f;
            m_offsetZ = -4.0f;
            m_moveSpeed = 2.0f;
            RemoveAttachments(~0);
            GetModelObject()->PlayAnim(ZAWARUDO_ANIM_STOPTIME, AOF_NORESTART);
            SpawnReminder(this, GetModelObject()->GetAnimLength(ZAWARUDO_ANIM_STOPTIME) + 1.0f, ZAWARUDO_ANIM_STOPTIME);
            SpawnReminder(this, GetModelObject()->GetAnimLength(ZAWARUDO_ANIM_STOPTIME)*0.8f, ZAWARUDO_START);
          }
          resume;
        }
        on (ETimer) : { stop; }
        on (EDisconnected) :
        {
          m_isActive = FALSE;
          m_penOwner = NULL;
          stop;
        }
        on (EStop) :
        {
          m_isActive = FALSE;
          stop;
        }
        otherwise() : { resume; }
      }
    }
    return EEnd();
  }

  Main(ESpawnStand eSpawnStand)
  {
    m_penOwner = eSpawnStand.penOwner;

    SetPredictable(TRUE);
    InitAsModel();
    SetPhysicsFlags(EPF_STAND);
    SetCollisionFlags(ECF_STAND);
    SetFlags(GetFlags() | ENF_SEETHROUGH);

    SetModel(MODEL_ZAWARUDO);
    SetModelMainTexture(TEXTURE_ZAWARUDO_OPAQUE);
    SetModelReflectionTexture(TEXTURE_REFLECT);
    SetModelSpecularTexture(TEXTURE_SPECULAR);

    m_tmParticlesActive = _pTimer->CurrentTick() + 3.0f;
    m_particlesOpacity = 0.0f;
    m_particlesOpacityPrev = 0.0f;
    m_timeSpawned = _pTimer->CurrentTick();
    GetModelObject()->PlayAnim(ZAWARUDO_ANIM_EMERGE, 0);
    SpawnReminder(this, GetModelObject()->GetAnimLength(ZAWARUDO_ANIM_EMERGE), ZAWARUDO_ANIM_EMERGE);

    autocall Alive() EEnd;

    m_tmParticlesActive = 0.0f;
    m_particlesOpacity = 0.0f;
    m_particlesOpacityPrev = 0.0f;

    RemoveAttachments(~0);
    m_timeSpawned = _pTimer->CurrentTick();
    m_offsetX = 0.0f;
    m_offsetZ = 0.0f;
    m_moveSpeed = 1.0f;
    m_isDying = TRUE;
    GetModelObject()->PlayAnim(ZAWARUDO_ANIM_DIE, 0);
    autowait(GetModelObject()->GetAnimLength(ZAWARUDO_ANIM_DIE));

    Destroy();
    return;
  }
};
