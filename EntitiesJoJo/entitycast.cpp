#include "StdH.h"
#include "entitycast.h"

CEntity* EntityCast(CEntity* p_entity, int entity_id)
{
  if (p_entity == NULL)
    return NULL;

  CDLLEntityClass* p_entity_class = p_entity->en_pecClass->ec_pdecDLLClass;
  while (p_entity_class != NULL)
  {
    if (p_entity_class->dec_iID == entity_id)
      return p_entity;
    p_entity_class = p_entity_class->dec_pdecBase;
  }
  return NULL;
}
