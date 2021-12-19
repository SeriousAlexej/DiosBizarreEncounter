#include "StdH.h"
#include "jojo_events.h"

extern EventFactoryItem* g_eventFactory = NULL;

/*********************************/

void ClearEventFactory()
{
  EventFactoryItem* current;
  EventFactoryItem* tmp;

  HASH_ITER(hh, g_eventFactory, current, tmp)
  {
    HASH_DEL(g_eventFactory, current);
    delete current;
  }
}

void AddToFactory(SLONG event_code, TEntityCreator p_creator)
{
  EventFactoryItem* p_new_item = new EventFactoryItem();
  p_new_item->event_code = event_code;
  p_new_item->p_creator = p_creator;
  HASH_ADD_INT(g_eventFactory, event_code, p_new_item);
}

CEntityEvent* CreateFromFactory(SLONG event_code)
{
  EventFactoryItem* factory;
  HASH_FIND_INT(g_eventFactory, &event_code, factory);
  return factory->p_creator();
}
