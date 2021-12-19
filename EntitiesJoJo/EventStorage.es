968
%{
#include "StdH.h"
#include "EntitiesJoJo/EventEntity.h"
%}

uses "EntitiesJoJo/jojo_events";

class EventStorage : CEntity {
  name "EventStorage";
  thumbnail "Thumbnails\\Marker.tbn";
  features "IsImportant";

properties:
  1 CEntityPointer m_penEvent001,
  2 CEntityPointer m_penEvent002,
  3 CEntityPointer m_penEvent003,
  4 CEntityPointer m_penEvent004,
  5 CEntityPointer m_penEvent005,
  6 CEntityPointer m_penEvent006,
  7 CEntityPointer m_penEvent007,
  8 CEntityPointer m_penEvent008,
  9 CEntityPointer m_penEvent009,
 10 CEntityPointer m_penEvent010,
 11 CEntityPointer m_penEvent011,
 12 CEntityPointer m_penEvent012,
 13 CEntityPointer m_penEvent013,
 14 CEntityPointer m_penEvent014,
 15 CEntityPointer m_penEvent015,
 16 CEntityPointer m_penEvent016,
 17 CEntityPointer m_penEvent017,
 18 CEntityPointer m_penEvent018,
 19 CEntityPointer m_penEvent019,
 20 CEntityPointer m_penEvent020,
 21 CEntityPointer m_penEvent021,
 22 CEntityPointer m_penEvent022,
 23 CEntityPointer m_penEvent023,
 24 CEntityPointer m_penEvent024,
 25 CEntityPointer m_penEvent025,
 26 CEntityPointer m_penEvent026,
 27 CEntityPointer m_penEvent027,
 28 CEntityPointer m_penEvent028,
 29 CEntityPointer m_penEvent029,
 30 CEntityPointer m_penEvent030,
 31 CEntityPointer m_penEvent031,
 32 CEntityPointer m_penEvent032,
 33 CEntityPointer m_penEvent033,
 34 CEntityPointer m_penEvent034,
 35 CEntityPointer m_penEvent035,
 36 CEntityPointer m_penEvent036,
 37 CEntityPointer m_penEvent037,
 38 CEntityPointer m_penEvent038,
 39 CEntityPointer m_penEvent039,
 40 CEntityPointer m_penEvent040,
 41 CEntityPointer m_penEvent041,
 42 CEntityPointer m_penEvent042,
 43 CEntityPointer m_penEvent043,
 44 CEntityPointer m_penEvent044,
 45 CEntityPointer m_penEvent045,
 46 CEntityPointer m_penEvent046,
 47 CEntityPointer m_penEvent047,
 48 CEntityPointer m_penEvent048,
 49 CEntityPointer m_penEvent049,
 50 CEntityPointer m_penEvent050,
 51 CEntityPointer m_penEvent051,
 52 CEntityPointer m_penEvent052,
 53 CEntityPointer m_penEvent053,
 54 CEntityPointer m_penEvent054,
 55 CEntityPointer m_penEvent055,
 56 CEntityPointer m_penEvent056,
 57 CEntityPointer m_penEvent057,
 58 CEntityPointer m_penEvent058,
 59 CEntityPointer m_penEvent059,
 60 CEntityPointer m_penEvent060,
 61 CEntityPointer m_penEvent061,
 62 CEntityPointer m_penEvent062,
 63 CEntityPointer m_penEvent063,
 64 CEntityPointer m_penEvent064,
 65 CEntityPointer m_penEvent065,
 66 CEntityPointer m_penEvent066,
 67 CEntityPointer m_penEvent067,
 68 CEntityPointer m_penEvent068,
 69 CEntityPointer m_penEvent069,
 70 CEntityPointer m_penEvent070,
 71 CEntityPointer m_penEvent071,
 72 CEntityPointer m_penEvent072,
 73 CEntityPointer m_penEvent073,
 74 CEntityPointer m_penEvent074,
 75 CEntityPointer m_penEvent075,
 76 CEntityPointer m_penEvent076,
 77 CEntityPointer m_penEvent077,
 78 CEntityPointer m_penEvent078,
 79 CEntityPointer m_penEvent079,
 80 CEntityPointer m_penEvent080,
 81 CEntityPointer m_penEvent081,
 82 CEntityPointer m_penEvent082,
 83 CEntityPointer m_penEvent083,
 84 CEntityPointer m_penEvent084,
 85 CEntityPointer m_penEvent085,
 86 CEntityPointer m_penEvent086,
 87 CEntityPointer m_penEvent087,
 88 CEntityPointer m_penEvent088,
 89 CEntityPointer m_penEvent089,
 90 CEntityPointer m_penEvent090,
 91 CEntityPointer m_penEvent091,
 92 CEntityPointer m_penEvent092,
 93 CEntityPointer m_penEvent093,
 94 CEntityPointer m_penEvent094,
 95 CEntityPointer m_penEvent095,
 96 CEntityPointer m_penEvent096,
 97 CEntityPointer m_penEvent097,
 98 CEntityPointer m_penEvent098,
 99 CEntityPointer m_penEvent099,
100 CEntityPointer m_penEvent100,
101 CEntityPointer m_penNext,
102 INDEX m_used = 0,

components:
  1 class CLASS_EVENT_ENTITY  "Classes\\EventEntity.ecl",
  2 class CLASS_EVENT_STORAGE "Classes\\EventStorage.ecl",

functions:

  void StoreEvent(CSentEvent& se)
  {
    if (m_used < 100) {
      CEntityPointer& penFree = *(&m_penEvent001 + m_used);
      if (!penFree) {
        penFree = CreateEntity(GetPlacement(), CLASS_EVENT_ENTITY);
        penFree->Initialize();
      }
      ((EventEntity*)penFree.ep_pen)->InitFromEvent(se);
      ++m_used;
    } else {
      if (!m_penNext) {
        m_penNext = CreateEntity(GetPlacement(), CLASS_EVENT_STORAGE);
        m_penNext->Initialize();
      }
      ((EventStorage*)m_penNext.ep_pen)->StoreEvent(se);
    }
  }

  void PopEvents()
  {
    for (INDEX i = 0; i < m_used; ++i) {
      CEntityPointer& penEvent = *(&m_penEvent001 + i);
      ((EventEntity*)penEvent.ep_pen)->SendToTarget();
    }
    m_used = 0;

    if (m_penNext) {
      ((EventStorage*)m_penNext.ep_pen)->PopEvents();
    }
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
