#ifndef JOJO_EVENTS_H
#define JOJO_EVENTS_H

class CSentEvent
{
public:
  CEntityPointer se_penEntity;
  CEntityEvent* se_peeEvent;
  inline void Clear(void)
  {
    se_penEntity = NULL;
  }
};

extern void JoJoHandleSentEvents();

extern CStaticStackArray<CSentEvent>* _paseSentEvents;

#define ZA_WARUDO_DURATION 9.0f
#define MAX_ULTIMATE_CHARGE 50000

#endif
