960
%{
#include "StdH.h"
#include "EntitiesMP/Player.h"
#include "EntitiesJoJo/jojo_events.h"
#include "EntitiesJoJo/TheWorld.h"
%}

%{

#define EPF_STAND ( \
  EPF_MOVABLE | EPF_ABSOLUTETRANSLATE | EPF_ORIENTEDBYGRAVITY)

%}

class CDioPosing : CMovableModelEntity
{
name      "HOHO";
thumbnail "";
features "CanBePredictable";

properties:
  1 CEntityPointer m_penOwner,
  2 BOOL           m_isActive = TRUE,

{
CPlacement3D m_plLast;
}

components:

functions:

  CPlacement3D GetLerpedPlacement() const
  {
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

  CModelObject* GetModelForRendering()
  {
    GetModelObject()->Synchronize(*m_penOwner->GetModelObject());
    // Add flames
    GetModelObject()->GetAttachmentModel(1)->amo_moModelObject.StretchModel(FLOAT3D(1.0f, 1.0f, 1.0f));
    return GetModelObject();
  }

  CPlacement3D GetDesiredPlacement() const
  {
    const CPlayer& player = ((CPlayer&)*(m_penOwner.ep_pen->GetPredictionTail()));
    const CPlacement3D view_rotation(FLOAT3D(0.0f, 0.0f, 0.0f), ANGLE3D(player.en_plViewpoint.pl_OrientationAngle(1), 0.0f, 0.0f));

    CPlacement3D stand_offset(FLOAT3D(0.0f, 0.0f, 2.0f), ANGLE3D(0.0f, 0.0f, 0.0f));
    stand_offset.RelativeToAbsoluteSmooth(view_rotation);
    stand_offset.RelativeToAbsoluteSmooth(player.GetPlacement());

    return stand_offset;
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
    if (distance_to_dest > 4.0f) {
      curr_placement.pl_PositionVector += vToDestination * (distance_to_dest - 4.0f);
    } else {
      FLOAT coeff = distance_to_dest * 0.25f;
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

    if (aToDestinationH == 0.0f) {
      ForceFullStop();
    } else {
      SetDesiredRotation(ANGLE3D(aToDestinationH, 0.0f, 0.0f));
    }
  }
  
  void PreMoving()
  {
    MoveToPlayer();
    CMovableModelEntity::PreMoving();
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
          AddToMovers();
          resume;
        }
        on (ETimer) : { stop; }
        on (EDisconnected) :
        {
          m_isActive = FALSE;
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
    SetCollisionFlags(ECF_TOUCHMODEL);
    SetFlags(GetFlags() | ENF_SEETHROUGH);

    GetModelObject()->Copy(*m_penOwner->GetModelObject());
    ModelChangeNotify();

    autocall Alive() EEnd;

    Destroy();
    return;
  }
};
