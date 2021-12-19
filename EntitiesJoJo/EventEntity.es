966
%{
#include "StdH.h"
#include "EntitiesJoJo/EventProperty.h"
%}

uses "EntitiesJoJo/jojo_events";

class EventEntity : CEntity {
  name "EventEntity";
  thumbnail "Thumbnails\\Marker.tbn";
  features "IsImportant";

properties:
  1 CEntityPointer m_penProp01,
  2 CEntityPointer m_penProp02,
  3 CEntityPointer m_penProp03,
  4 CEntityPointer m_penProp04,
  5 CEntityPointer m_penProp05,
  6 CEntityPointer m_penProp06,
  7 CEntityPointer m_penProp07,
  8 CEntityPointer m_penProp08,
  9 CEntityPointer m_penProp09,
 10 CEntityPointer m_penProp10,
 11 CEntityPointer m_penProp11,
 12 CEntityPointer m_penProp12,
 13 CEntityPointer m_penProp13,
 14 CEntityPointer m_penProp14,
 15 CEntityPointer m_penProp15,
 16 CEntityPointer m_penProp16,
 17 CEntityPointer m_penProp17,
 18 CEntityPointer m_penProp18,
 19 CEntityPointer m_penProp19,
 20 CEntityPointer m_penProp20,
 21 CEntityPointer m_penProp21,
 22 CEntityPointer m_penProp22,
 23 CEntityPointer m_penProp23,
 24 CEntityPointer m_penProp24,
 25 CEntityPointer m_penProp25,
 26 CEntityPointer m_penProp26,
 27 CEntityPointer m_penProp27,
 28 CEntityPointer m_penProp28,
 29 CEntityPointer m_penProp29,
 30 CEntityPointer m_penProp30,
 31 CEntityPointer m_penTarget,
 32 INDEX m_eventType = 0,

components:
  1 class   CLASS_EVENT_PROPERTY "Classes\\EventProperty.ecl"

functions:

  void WriteEventMember(INDEX i, void* val, INDEX type)
  {
    CEntityPointer& ptr = *(&m_penProp01 + i);
    if (!ptr) {
      ptr = CreateEntity(GetPlacement(), CLASS_EVENT_PROPERTY);
      ptr->Initialize();
    }
    ((EventProperty*)ptr.ep_pen)->FromProperty(val, type);
  }

  void ReadEventMember(INDEX i, void* val, INDEX type)
  {
    CEntityPointer& ptr = *(&m_penProp01 + i);
    ((EventProperty*)ptr.ep_pen)->ToProperty(val, type);
  }

  void InitFromEvent(CSentEvent& se)
  {
    m_penTarget = se.se_penEntity;
    m_eventType = se.se_peeEvent->ee_slEvent;
    CEntityEvent* e = se.se_peeEvent;

    switch (m_eventType)
    {
    case EVENTCODE_EInternal:
    case EVENTCODE_EVoid:
    case EVENTCODE_EReturn:
    case EVENTCODE_EBegin:
    case EVENTCODE_ETimer:
    case EVENTCODE_EWouldFall:
    case EVENTCODE_ETeleport:
    case EVENTCODE_EFirstWorldBase:
    {
      break;
    }
    case EVENTCODE_ETouch:
    {
      WriteEventMember(0, &((ETouch*)e)->penOther, EVENTPROP_CEntityPointer);
      WriteEventMember(1, &((ETouch*)e)->bThisMoved, EVENTPROP_BOOL);
      WriteEventMember(2, &((ETouch*)e)->plCollision, EVENTPROP_FLOATplane3D);
      break;
    }
    case EVENTCODE_EPass:
    {
      WriteEventMember(0, &((EPass*)e)->penOther, EVENTPROP_CEntityPointer);
      WriteEventMember(1, &((EPass*)e)->bThisMoved, EVENTPROP_BOOL);
      break;
    }
    case EVENTCODE_EBlock:
    {
      WriteEventMember(0, &((EBlock*)e)->penOther, EVENTPROP_CEntityPointer);
      WriteEventMember(1, &((EBlock*)e)->plCollision, EVENTPROP_FLOATplane3D);
      break;
    }
    case EVENTCODE_EPreLevelChange:
    {
      WriteEventMember(0, &((EPreLevelChange*)e)->iUserData, EVENTPROP_INDEX);
      break;
    }
    case EVENTCODE_EPostLevelChange:
    {
      WriteEventMember(0, &((EPostLevelChange*)e)->iUserData, EVENTPROP_INDEX);
      break;
    }
    case EVENTCODE_EDamage:
    {
      WriteEventMember(0, &((EDamage*)e)->penInflictor, EVENTPROP_CEntityPointer);
      WriteEventMember(1, &((EDamage*)e)->vDirection, EVENTPROP_FLOAT3D);
      WriteEventMember(2, &((EDamage*)e)->vHitPoint, EVENTPROP_FLOAT3D);
      WriteEventMember(3, &((EDamage*)e)->fAmount, EVENTPROP_FLOAT);
      WriteEventMember(4, &((EDamage*)e)->dmtType, EVENTPROP_INDEX);
      break;
    }
    case EVENTCODE_EDeath:
    {
      WriteEventMember(0, &((EDeath*)e)->eLastDamage.penInflictor, EVENTPROP_CEntityPointer);
      WriteEventMember(1, &((EDeath*)e)->eLastDamage.vDirection, EVENTPROP_FLOAT3D);
      WriteEventMember(2, &((EDeath*)e)->eLastDamage.vHitPoint, EVENTPROP_FLOAT3D);
      WriteEventMember(3, &((EDeath*)e)->eLastDamage.fAmount, EVENTPROP_FLOAT);
      WriteEventMember(4, &((EDeath*)e)->eLastDamage.dmtType, EVENTPROP_INDEX);
      break;
    }
    case EVENTCODE_ETakingBreath:
    {
      WriteEventMember(0, &((ETakingBreath*)e)->fBreathDelay, EVENTPROP_FLOAT);
      break;
    }
    default:
    {
      CJoJoEvent* j = (CJoJoEvent*)e;
      for (INDEX i = 0; i < j->m_numProps; ++i) {
        WriteEventMember(i, j->m_properties[i], j->m_propTypes[i]);
      }
      break;
    }
    }
  }

  void SendToTarget()
  {
    if (!m_penTarget) {
      return;
    }

    CEntityEvent* e = NULL;

    switch (m_eventType)
    {
    case EVENTCODE_EInternal:
    {
      e = new EInternal();
      break;
    }
    case EVENTCODE_EVoid:
    {
      e = new EVoid();
      break;
    }
    case EVENTCODE_EReturn:
    {
      e = new EReturn();
      break;
    }
    case EVENTCODE_EBegin:
    {
      e = new EBegin();
      break;
    }
    case EVENTCODE_ETimer:
    {
      e = new ETimer();
      break;
    }
    case EVENTCODE_EWouldFall:
    {
      e = new EWouldFall();
      break;
    }
    case EVENTCODE_ETeleport:
    {
      e = new ETeleport();
      break;
    }
    case EVENTCODE_EFirstWorldBase:
    {
      e = new EFirstWorldBase();
      break;
    }
    case EVENTCODE_ETouch:
    {
      e = new ETouch();
      ReadEventMember(0, &((ETouch*)e)->penOther, EVENTPROP_CEntityPointer);
      ReadEventMember(1, &((ETouch*)e)->bThisMoved, EVENTPROP_BOOL);
      ReadEventMember(2, &((ETouch*)e)->plCollision, EVENTPROP_FLOATplane3D);
      break;
    }
    case EVENTCODE_EPass:
    {
      e = new EPass();
      ReadEventMember(0, &((EPass*)e)->penOther, EVENTPROP_CEntityPointer);
      ReadEventMember(1, &((EPass*)e)->bThisMoved, EVENTPROP_BOOL);
      break;
    }
    case EVENTCODE_EBlock:
    {
      e = new EBlock();
      ReadEventMember(0, &((EBlock*)e)->penOther, EVENTPROP_CEntityPointer);
      ReadEventMember(1, &((EBlock*)e)->plCollision, EVENTPROP_FLOATplane3D);
      break;
    }
    case EVENTCODE_EPreLevelChange:
    {
      e = new EPreLevelChange();
      ReadEventMember(0, &((EPreLevelChange*)e)->iUserData, EVENTPROP_INDEX);
      break;
    }
    case EVENTCODE_EPostLevelChange:
    {
      e = new EPostLevelChange();
      ReadEventMember(0, &((EPostLevelChange*)e)->iUserData, EVENTPROP_INDEX);
      break;
    }
    case EVENTCODE_EDamage:
    {
      e = new EDamage();
      ReadEventMember(0, &((EDamage*)e)->penInflictor, EVENTPROP_CEntityPointer);
      ReadEventMember(1, &((EDamage*)e)->vDirection, EVENTPROP_FLOAT3D);
      ReadEventMember(2, &((EDamage*)e)->vHitPoint, EVENTPROP_FLOAT3D);
      ReadEventMember(3, &((EDamage*)e)->fAmount, EVENTPROP_FLOAT);
      ReadEventMember(4, &((EDamage*)e)->dmtType, EVENTPROP_INDEX);
      break;
    }
    case EVENTCODE_EDeath:
    {
      e = new EDeath();
      ReadEventMember(0, &((EDeath*)e)->eLastDamage.penInflictor, EVENTPROP_CEntityPointer);
      ReadEventMember(1, &((EDeath*)e)->eLastDamage.vDirection, EVENTPROP_FLOAT3D);
      ReadEventMember(2, &((EDeath*)e)->eLastDamage.vHitPoint, EVENTPROP_FLOAT3D);
      ReadEventMember(3, &((EDeath*)e)->eLastDamage.fAmount, EVENTPROP_FLOAT);
      ReadEventMember(4, &((EDeath*)e)->eLastDamage.dmtType, EVENTPROP_INDEX);
      break;
    }
    case EVENTCODE_ETakingBreath:
    {
      e = new ETakingBreath();
      ReadEventMember(0, &((ETakingBreath*)e)->fBreathDelay, EVENTPROP_FLOAT);
      break;
    }
    default:
    {
      CJoJoEvent* j = (CJoJoEvent*)CreateFromFactory(m_eventType);
      for (INDEX i = 0; i < j->m_numProps; ++i) {
        ReadEventMember(i, j->m_properties[i], j->m_propTypes[i]);
      }
      e = j;
    }
    }
    m_penTarget->SendEvent(*e);
    delete e;
    m_penTarget = NULL;
  }

procedures:
  Main()
  {
    InitAsVoid();
    SetPhysicsFlags(EPF_MODEL_IMMATERIAL);
    SetCollisionFlags(ECF_IMMATERIAL);
    return;
  }
};
