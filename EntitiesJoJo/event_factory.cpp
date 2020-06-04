#include "StdH.h"
#include "jojo_events.h"
#include <Engine/Templates/Stock_CModelData.h>
#include <Engine/Templates/Stock_CTextureData.h>

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

/*********************************/

void WriteSingleEvent(CTStream* strm, CEntityEvent* event)
{
  *strm<<event->ee_slEvent;

  switch(event->ee_slEvent)
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
      WriteEventMember(strm, ((ETouch*)event)->penOther);
      WriteEventMember(strm, ((ETouch*)event)->bThisMoved);
      WriteEventMember(strm, ((ETouch*)event)->plCollision);
      break;
    }
  case EVENTCODE_EPass:
    {
      WriteEventMember(strm, ((EPass*)event)->penOther);
      WriteEventMember(strm, ((EPass*)event)->bThisMoved);
      break;
    }
  case EVENTCODE_EBlock:
    {
      WriteEventMember(strm, ((EBlock*)event)->penOther);
      WriteEventMember(strm, ((EBlock*)event)->plCollision);
      break;
    }
  case EVENTCODE_EPreLevelChange:
    {
      WriteEventMember(strm, ((EPreLevelChange*)event)->iUserData);
      break;
    }
  case EVENTCODE_EPostLevelChange:
    {
      WriteEventMember(strm, ((EPostLevelChange*)event)->iUserData);
      break;
    }
  case EVENTCODE_EDamage:
    {
      WriteEventMember(strm, ((EDamage*)event)->penInflictor);
      WriteEventMember(strm, ((EDamage*)event)->vDirection);
      WriteEventMember(strm, ((EDamage*)event)->vHitPoint);
      WriteEventMember(strm, ((EDamage*)event)->fAmount);
      INDEX ei = ((EDamage*)event)->dmtType;
      WriteEventMember(strm, ei);
      break;
    }
  case EVENTCODE_EDeath:
    {
      WriteEventMember(strm, ((EDeath*)event)->eLastDamage.penInflictor);
      WriteEventMember(strm, ((EDeath*)event)->eLastDamage.vDirection);
      WriteEventMember(strm, ((EDeath*)event)->eLastDamage.vHitPoint);
      WriteEventMember(strm, ((EDeath*)event)->eLastDamage.fAmount);
      INDEX ei = ((EDeath*)event)->eLastDamage.dmtType;
      WriteEventMember(strm, ei);
      break;
    }
  case EVENTCODE_ETakingBreath:
    {
      WriteEventMember(strm, ((ETakingBreath*)event)->fBreathDelay);
      break;
    }
  default:
    {
      ((CJoJoEvent*)event)->Write(strm);
      break;
    }
  }
}

/*********************************/

CEntityEvent* ReadSignleEvent(CTStream* strm)
{
  SLONG event_type;
  *strm>>event_type;
  CEntityEvent* event = NULL;

  switch(event_type)
  {
  case EVENTCODE_EInternal:
    {
      event = new EInternal();
      break;
    }
  case EVENTCODE_EVoid:
    {
      event = new EVoid();
      break;
    }
  case EVENTCODE_EReturn:
    {
      event = new EReturn();
      break;
    }
  case EVENTCODE_EBegin:
    {
      event = new EBegin();
      break;
    }
  case EVENTCODE_ETimer:
    {
      event = new ETimer();
      break;
    }
  case EVENTCODE_EWouldFall:
    {
      event = new EWouldFall();
      break;
    }
  case EVENTCODE_ETeleport:
    {
      event = new ETeleport();
      break;
    }
  case EVENTCODE_EFirstWorldBase:
    {
      event = new EFirstWorldBase();
      break;
    }
  case EVENTCODE_ETouch:
    {
      event = new ETouch();
      ReadEventMember(strm, ((ETouch*)event)->penOther);
      ReadEventMember(strm, ((ETouch*)event)->bThisMoved);
      ReadEventMember(strm, ((ETouch*)event)->plCollision);
      break;
    }
  case EVENTCODE_EPass:
    {
      event = new EPass();
      ReadEventMember(strm, ((EPass*)event)->penOther);
      ReadEventMember(strm, ((EPass*)event)->bThisMoved);
      break;
    }
  case EVENTCODE_EBlock:
    {
      event = new EBlock();
      ReadEventMember(strm, ((EBlock*)event)->penOther);
      ReadEventMember(strm, ((EBlock*)event)->plCollision);
      break;
    }
  case EVENTCODE_EPreLevelChange:
    {
      event = new EPreLevelChange();
      ReadEventMember(strm, ((EPreLevelChange*)event)->iUserData);
      break;
    }
  case EVENTCODE_EPostLevelChange:
    {
      event = new EPostLevelChange();
      ReadEventMember(strm, ((EPostLevelChange*)event)->iUserData);
      break;
    }
  case EVENTCODE_EDamage:
    {
      event = new EDamage();
      ReadEventMember(strm, ((EDamage*)event)->penInflictor);
      ReadEventMember(strm, ((EDamage*)event)->vDirection);
      ReadEventMember(strm, ((EDamage*)event)->vHitPoint);
      ReadEventMember(strm, ((EDamage*)event)->fAmount);
      INDEX ei;
      ReadEventMember(strm, ei);
      ((EDamage*)event)->dmtType = (DamageType)ei;
      break;
    }
  case EVENTCODE_EDeath:
    {
      event = new EDeath();
      ReadEventMember(strm, ((EDeath*)event)->eLastDamage.penInflictor);
      ReadEventMember(strm, ((EDeath*)event)->eLastDamage.vDirection);
      ReadEventMember(strm, ((EDeath*)event)->eLastDamage.vHitPoint);
      ReadEventMember(strm, ((EDeath*)event)->eLastDamage.fAmount);
      INDEX ei;
      ReadEventMember(strm, ei);
      ((EDeath*)event)->eLastDamage.dmtType = (DamageType)ei;
      break;
    }
  case EVENTCODE_ETakingBreath:
    {
      event = new ETakingBreath();
      ReadEventMember(strm, ((ETakingBreath*)event)->fBreathDelay);
      break;
    }
  default:
    {
      EventFactoryItem* factory;
      HASH_FIND_INT(g_eventFactory, &event_type, factory);
      event = factory->p_creator();
      ((CJoJoEvent*)event)->Read(strm);
      break;
    }
  }
  return event;
}

/*********************************/

void ResolveSingleEvent(CEntityEvent* event)
{
  switch(event->ee_slEvent)
  {
  case EVENTCODE_EInternal:
  case EVENTCODE_EVoid:
  case EVENTCODE_EReturn:
  case EVENTCODE_EBegin:
  case EVENTCODE_ETimer:
  case EVENTCODE_EWouldFall:
  case EVENTCODE_ETeleport:
  case EVENTCODE_EPreLevelChange:
  case EVENTCODE_EPostLevelChange:
  case EVENTCODE_EFirstWorldBase:
  case EVENTCODE_ETakingBreath:
    {
      break;
    }
  case EVENTCODE_ETouch:
    {
      ResolveEntityPointer(((ETouch*)event)->penOther);
      break;
    }
  case EVENTCODE_EPass:
    {
      ResolveEntityPointer(((EPass*)event)->penOther);
      break;
    }
  case EVENTCODE_EBlock:
    {
      ResolveEntityPointer(((EBlock*)event)->penOther);
      break;
    }
  case EVENTCODE_EDamage:
    {
      ResolveEntityPointer(((EDamage*)event)->penInflictor);
      break;
    }
  case EVENTCODE_EDeath:
    {
      ResolveEntityPointer(((EDeath*)event)->eLastDamage.penInflictor);
      break;
    }
  default:
    {
      ((CJoJoEvent*)event)->ResolvePointers();
      break;
    }
  }
}

/*********************************/

void WriteEventMember(CTStream* strm, FLOAT &f)
{
  *strm<<f;
}
void WriteEventMember(CTStream* strm, INDEX &i)
{
  *strm<<i;
}
void WriteEventMember(CTStream* strm, BOOL &b)
{
  *strm<<b;
}
void WriteEventMember(CTStream* strm, CEntity* pen)
{
  if (g_shouldResolveEvents == TRUE)
  {
    *strm<<(INDEX)pen; // not yet resolved, so this is already index
    return;
  }
  if (pen==NULL)
  {
    *strm<<(INDEX)-1;
  } else {
    *strm<<(pen->en_ulID);
  }
}
void WriteEventMember(CTStream* strm, CEntityPointer &pen)
{
  WriteEventMember(strm, pen.ep_pen);
}
void WriteEventMember(CTStream* strm, CTString &str)
{
  INDEX len = str.Length();
  if (len > 1024)
  {
    len = 1024;
  }
  *strm<<len;
  strm->Write_t(str.str_String, len);
}
void WriteEventMember(CTStream* strm, FLOATplane3D &pl)
{
  *strm<<pl.pl_distance;
  *strm<<pl.vector[0];
  *strm<<pl.vector[1];
  *strm<<pl.vector[2];
}
void WriteEventMember(CTStream* strm, FLOAT3D &v)
{
  *strm<<v.vector[0];
  *strm<<v.vector[1];
  *strm<<v.vector[2];
}
void WriteEventMember(CTStream* strm, COLOR &c)
{
  *strm<<c;
}
void WriteEventMember(CTStream* strm, CModelData *&pmd)
{
  WriteEventMember(strm, pmd->ser_FileName);
}
void WriteEventMember(CTStream* strm, CTextureData *&pmt)
{
  WriteEventMember(strm, pmt->ser_FileName);
}
void WriteEventMember(CTStream* strm, FLOATmatrix3D& m)
{
  *strm<<m;
}

/*********************************/

void ReadEventMember(CTStream* strm, FLOAT &f)
{
  *strm>>f;
}
void ReadEventMember(CTStream* strm, INDEX &i)
{
  *strm>>i;
}
void ReadEventMember(CTStream* strm, BOOL &b)
{
  *strm>>b;
}
void ReadEventMember(CTStream* strm, CEntity*& pen)
{
  INDEX iPointedEntity;
  *strm>>iPointedEntity;
  pen = (CEntity*)iPointedEntity; // must be resolved later
}
void ReadEventMember(CTStream* strm, CEntityPointer &pen)
{
  ReadEventMember(strm, pen.ep_pen);
}
void ResolveEntityPointer(CEntityPointer& pen)
{
  ResolveRawEntityPointer(pen.ep_pen);
  if (pen.ep_pen != NULL)
    pen.ep_pen->AddReference();
}
void ResolveRawEntityPointer(CEntity*& pen)
{
  if ((INDEX)pen == -1)
    pen = NULL;
  else
    pen = _pNetwork->ga_World.EntityFromID((INDEX)pen);
}
void ReadEventMember(CTStream* strm, CTString &str)
{
  INDEX len;
  *strm>>len;
  char buff[1025];
  buff[len] = 0;
  strm->Read_t(buff, len);
  str = buff;
}
void ReadEventMember(CTStream* strm, FLOATplane3D &pl)
{
  *strm>>pl.pl_distance;
  *strm>>pl.vector[0];
  *strm>>pl.vector[1];
  *strm>>pl.vector[2];
}
void ReadEventMember(CTStream* strm, FLOAT3D &v)
{
  *strm>>v.vector[0];
  *strm>>v.vector[1];
  *strm>>v.vector[2];
}
void ReadEventMember(CTStream* strm, COLOR &c)
{
  *strm>>c;
}
void ReadEventMember(CTStream* strm, CModelData *&pmd)
{
  CTFileName model_resource;
  ReadEventMember(strm, model_resource);
  pmd = _pModelStock->Obtain_t(model_resource);
}
void ReadEventMember(CTStream* strm, CTextureData *&pmt)
{
  CTFileName texture_resource;
  ReadEventMember(strm, texture_resource);
  pmt = _pTextureStock->Obtain_t(texture_resource);
}
void ReadEventMember(CTStream* strm, FLOATmatrix3D& m)
{
  *strm>>m;
}
