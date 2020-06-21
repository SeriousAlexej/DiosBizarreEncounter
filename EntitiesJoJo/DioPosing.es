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

components:

functions:

  CModelObject* GetModelForRendering()
  {
    GetModelObject()->Synchronize(*m_penOwner->GetModelObject());
    return GetModelObject();
  }

  CPlacement3D GetDesiredPlacement() const
  {
    const CPlayer& player = ((CPlayer&)*(m_penOwner.ep_pen->GetPredictionTail()));
    const CPlacement3D view_rotation(FLOAT3D(0.0f, 0.0f, 0.0f), ANGLE3D(player.en_plViewpoint.pl_OrientationAngle(1), 0.0f, 0.0f));

    CPlacement3D stand_offset(FLOAT3D(0.0f, 0.0f, 0.0f), ANGLE3D(0.0f, 0.0f, 0.0f));
    stand_offset.RelativeToAbsoluteSmooth(view_rotation);
    stand_offset.RelativeToAbsoluteSmooth(player.GetPlacement());

    return stand_offset;
  }

  void MoveToPlayer()
  {
    static const float TRANSLATION_EPSILON = 0.05f;
    static const float ROTATION_EPSILON = 0.05f;

    const CPlacement3D curr_placement = GetPlacement();
    const CPlacement3D dest_placement = GetDesiredPlacement();

    FLOAT3D vToDestination = dest_placement.pl_PositionVector - curr_placement.pl_PositionVector;
    FLOAT distance_to_dest = vToDestination.Length();
    vToDestination.SafeNormalize();
    vToDestination *= distance_to_dest * 5.0f;

    for (INDEX i = 1; i <= 3; ++i) {
      if (Abs(vToDestination(i)) < TRANSLATION_EPSILON) {
        vToDestination(i) = 0.0f;
      }
    }

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
      SetDesiredTranslation(vToDestination);
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
      wait (0.25f)
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
    SetCollisionFlags(ECF_IMMATERIAL);
    SetFlags(GetFlags() | ENF_SEETHROUGH);

    GetModelObject()->Copy(*m_penOwner->GetModelObject());
    ModelChangeNotify();

    autocall Alive() EEnd;

    Destroy();
    return;
  }
};
