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

extern void ClearFrozenEntities();
extern void FreezeEntityInZaWarudo(CEntity* p_entity);

extern void WriteBackupEvents(CTStream* strm);
extern void ReadBackupEvents(CTStream* strm);

extern void ClearBackupEvents();
extern void JoJoHandleSentEvents();

extern CStaticStackArray<CSentEvent>* _paseSentEvents;
extern BOOL g_shouldResolveEvents;

#define ZA_WARUDO_DURATION 9.0f

#endif
