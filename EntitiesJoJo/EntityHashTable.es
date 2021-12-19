969
%{
#include "StdH.h"

struct FrozenEntity
{
  ULONG id;
  CEntity* p_entity;
  UT_hash_handle hh;
};

%}

uses "EntitiesJoJo/HashDecl";

class EntityHashTable : CEntity {
  name "EntityHashTable";
  thumbnail "Thumbnails\\Marker.tbn";
  features "IsImportant";

properties:
  1 CEntityPointer m_penEntity001,
  2 CEntityPointer m_penEntity002,
  3 CEntityPointer m_penEntity003,
  4 CEntityPointer m_penEntity004,
  5 CEntityPointer m_penEntity005,
  6 CEntityPointer m_penEntity006,
  7 CEntityPointer m_penEntity007,
  8 CEntityPointer m_penEntity008,
  9 CEntityPointer m_penEntity009,
 10 CEntityPointer m_penEntity010,
 11 CEntityPointer m_penEntity011,
 12 CEntityPointer m_penEntity012,
 13 CEntityPointer m_penEntity013,
 14 CEntityPointer m_penEntity014,
 15 CEntityPointer m_penEntity015,
 16 CEntityPointer m_penEntity016,
 17 CEntityPointer m_penEntity017,
 18 CEntityPointer m_penEntity018,
 19 CEntityPointer m_penEntity019,
 20 CEntityPointer m_penEntity020,
 21 CEntityPointer m_penEntity021,
 22 CEntityPointer m_penEntity022,
 23 CEntityPointer m_penEntity023,
 24 CEntityPointer m_penEntity024,
 25 CEntityPointer m_penEntity025,
 26 CEntityPointer m_penEntity026,
 27 CEntityPointer m_penEntity027,
 28 CEntityPointer m_penEntity028,
 29 CEntityPointer m_penEntity029,
 30 CEntityPointer m_penEntity030,
 31 CEntityPointer m_penEntity031,
 32 CEntityPointer m_penEntity032,
 33 CEntityPointer m_penEntity033,
 34 CEntityPointer m_penEntity034,
 35 CEntityPointer m_penEntity035,
 36 CEntityPointer m_penEntity036,
 37 CEntityPointer m_penEntity037,
 38 CEntityPointer m_penEntity038,
 39 CEntityPointer m_penEntity039,
 40 CEntityPointer m_penEntity040,
 41 CEntityPointer m_penEntity041,
 42 CEntityPointer m_penEntity042,
 43 CEntityPointer m_penEntity043,
 44 CEntityPointer m_penEntity044,
 45 CEntityPointer m_penEntity045,
 46 CEntityPointer m_penEntity046,
 47 CEntityPointer m_penEntity047,
 48 CEntityPointer m_penEntity048,
 49 CEntityPointer m_penEntity049,
 50 CEntityPointer m_penEntity050,
 51 CEntityPointer m_penEntity051,
 52 CEntityPointer m_penEntity052,
 53 CEntityPointer m_penEntity053,
 54 CEntityPointer m_penEntity054,
 55 CEntityPointer m_penEntity055,
 56 CEntityPointer m_penEntity056,
 57 CEntityPointer m_penEntity057,
 58 CEntityPointer m_penEntity058,
 59 CEntityPointer m_penEntity059,
 60 CEntityPointer m_penEntity060,
 61 CEntityPointer m_penEntity061,
 62 CEntityPointer m_penEntity062,
 63 CEntityPointer m_penEntity063,
 64 CEntityPointer m_penEntity064,
 65 CEntityPointer m_penEntity065,
 66 CEntityPointer m_penEntity066,
 67 CEntityPointer m_penEntity067,
 68 CEntityPointer m_penEntity068,
 69 CEntityPointer m_penEntity069,
 70 CEntityPointer m_penEntity070,
 71 CEntityPointer m_penEntity071,
 72 CEntityPointer m_penEntity072,
 73 CEntityPointer m_penEntity073,
 74 CEntityPointer m_penEntity074,
 75 CEntityPointer m_penEntity075,
 76 CEntityPointer m_penEntity076,
 77 CEntityPointer m_penEntity077,
 78 CEntityPointer m_penEntity078,
 79 CEntityPointer m_penEntity079,
 80 CEntityPointer m_penEntity080,
 81 CEntityPointer m_penEntity081,
 82 CEntityPointer m_penEntity082,
 83 CEntityPointer m_penEntity083,
 84 CEntityPointer m_penEntity084,
 85 CEntityPointer m_penEntity085,
 86 CEntityPointer m_penEntity086,
 87 CEntityPointer m_penEntity087,
 88 CEntityPointer m_penEntity088,
 89 CEntityPointer m_penEntity089,
 90 CEntityPointer m_penEntity090,
 91 CEntityPointer m_penEntity091,
 92 CEntityPointer m_penEntity092,
 93 CEntityPointer m_penEntity093,
 94 CEntityPointer m_penEntity094,
 95 CEntityPointer m_penEntity095,
 96 CEntityPointer m_penEntity096,
 97 CEntityPointer m_penEntity097,
 98 CEntityPointer m_penEntity098,
 99 CEntityPointer m_penEntity099,
100 CEntityPointer m_penEntity100,
101 CEntityPointer m_penNext,
102 INDEX m_used = 0,

{
FrozenEntity* m_cache;
}

components:
  1 class CLASS_EVENT_HASH_TABLE "Classes\\EntityHashTable.ecl",

functions:
  void EntityHashTable()
  {
    m_cache = NULL;
  }

  void ~EntityHashTable()
  {
    ClearCache();
  }

  void ClearCache()
  {
    FrozenEntity* current;
    FrozenEntity* tmp;

    HASH_ITER(hh, m_cache, current, tmp)
    {
      HASH_DEL(m_cache, current);
      delete current;
    }
  }

  void AddInternal(CEntity* pen)
  {
    FrozenEntity* freezed = new FrozenEntity();
    freezed->id = pen->en_ulID;
    freezed->p_entity = pen;
    HASH_ADD_INT(m_cache, id, freezed);
  }

  BOOL Contains(CEntity* pen)
  {
    FrozenEntity* found = NULL;
    HASH_FIND_INT(m_cache, &pen->en_ulID, found);
    if (found != NULL) {
      return TRUE;
    }
    if (m_penNext) {
      return ((EntityHashTable*)m_penNext.ep_pen)->Contains(pen);
    }
    return FALSE;
  }

  virtual void Copy(CEntity& enOther, ULONG ulFlags)
  {
    CEntity::Copy(enOther, ulFlags);
    ClearCache();

    for (INDEX i = 0; i < m_used; ++i) {
      CEntityPointer& pen = *(&m_penEntity001 + i);
      AddInternal(pen.ep_pen);
    }
  }

  virtual void Read_t(CTStream* istr)
  {
    CEntity::Read_t(istr);
    ClearCache();

    for (INDEX i = 0; i < m_used; ++i) {
      CEntityPointer& pen = *(&m_penEntity001 + i);
      AddInternal(pen.ep_pen);
    }
  }

  void Add(const CEntityPointer& pen)
  {
    if (m_used < 100) {
      CEntityPointer& penFree = *(&m_penEntity001 + m_used);
      penFree = pen;
      AddInternal(pen.ep_pen);
      ++m_used;
    } else {
      if (!m_penNext) {
        m_penNext = CreateEntity(GetPlacement(), CLASS_EVENT_HASH_TABLE);
        m_penNext->Initialize();
      }
      ((EntityHashTable*)m_penNext.ep_pen)->Add(pen);
    }
  }

  void Clear()
  {
    ClearCache();
    for (INDEX i = 0; i < m_used; ++i) {
      CEntityPointer& penEntity = *(&m_penEntity001 + i);
      penEntity = NULL;
    }
    m_used = 0;

    if (m_penNext) {
      ((EntityHashTable*)m_penNext.ep_pen)->Clear();
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
