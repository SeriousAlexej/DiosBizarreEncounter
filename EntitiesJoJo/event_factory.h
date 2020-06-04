#ifndef EVENT_FACTORY_H
#define EVENT_FACTORY_H
#include "EntitiesJoJo/uthash/uthash.h"

class DECL_DLL CJoJoEvent : public CEntityEvent
{
public:
  CJoJoEvent(SLONG event_code)
    : CEntityEvent(event_code)
  {
  }
  virtual ~CJoJoEvent() {}
  virtual void Write(CTStream* strm) = 0;
  virtual void Read(CTStream* strm) = 0;
  virtual void ResolvePointers() = 0;
};

typedef CEntityEvent*(*TEntityCreator)(void);
struct EventFactoryItem
{
  SLONG event_code;
  TEntityCreator p_creator;
  UT_hash_handle hh;
};
extern EventFactoryItem* g_eventFactory;

extern void ClearEventFactory();
extern void AddToFactory(SLONG event_code, TEntityCreator p_creator);

extern void WriteSingleEvent(CTStream* strm, CEntityEvent* event);
extern CEntityEvent* ReadSignleEvent(CTStream* strm);
extern void ResolveSingleEvent(CEntityEvent* event);

extern void ResolveEntityPointer(CEntityPointer& pen);
extern void ResolveRawEntityPointer(CEntity*& pen);

extern void WriteEventMember(CTStream* strm, FLOAT &f);
extern void WriteEventMember(CTStream* strm, INDEX &i);
extern void WriteEventMember(CTStream* strm, BOOL &b);
extern void WriteEventMember(CTStream* strm, CEntity* pen);
extern void WriteEventMember(CTStream* strm, CEntityPointer &pen);
extern void WriteEventMember(CTStream* strm, CTString &str);
extern void WriteEventMember(CTStream* strm, FLOATplane3D &pl);
extern void WriteEventMember(CTStream* strm, FLOAT3D &v);
extern void WriteEventMember(CTStream* strm, COLOR &c);
extern void WriteEventMember(CTStream* strm, CModelData *&pmd);
extern void WriteEventMember(CTStream* strm, CTextureData *&pmt);
extern void WriteEventMember(CTStream* strm, FLOATmatrix3D& m);

extern void ReadEventMember(CTStream* strm, FLOAT &f);
extern void ReadEventMember(CTStream* strm, INDEX &i);
extern void ReadEventMember(CTStream* strm, BOOL &b);
extern void ReadEventMember(CTStream* strm, CEntity*& pen);
extern void ReadEventMember(CTStream* strm, CEntityPointer &pen);
extern void ReadEventMember(CTStream* strm, CTString &str);
extern void ReadEventMember(CTStream* strm, FLOATplane3D &pl);
extern void ReadEventMember(CTStream* strm, FLOAT3D &v);
extern void ReadEventMember(CTStream* strm, COLOR &c);
extern void ReadEventMember(CTStream* strm, CModelData *&pmd);
extern void ReadEventMember(CTStream* strm, CTextureData *&pmt);
extern void ReadEventMember(CTStream* strm, FLOATmatrix3D& m);

#endif
