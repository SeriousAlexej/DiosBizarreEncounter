#ifndef EVENT_FACTORY_H
#define EVENT_FACTORY_H
#include "EntitiesJoJo/uthash/uthash.h"

class DECL_DLL CJoJoEvent : public CEntityEvent
{
public:
  CJoJoEvent(SLONG event_code)
    : CEntityEvent(event_code)
    , m_numProps(0)
  {
    memset(m_properties, NULL, sizeof(PropPtr) * 30);
    memset(m_propTypes, 0, sizeof(INDEX) * 30);
  }
  virtual ~CJoJoEvent() {}
  virtual void SetupProperties() = 0;
  typedef void* PropPtr;
  PropPtr m_properties[30];
  INDEX m_propTypes[30];
  INDEX m_numProps;
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
extern CEntityEvent* CreateFromFactory(SLONG event_code);

#endif
