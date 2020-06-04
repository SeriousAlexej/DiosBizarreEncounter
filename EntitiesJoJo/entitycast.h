#ifndef ENTITY_CAST_H
#define ENTITY_CAST_H

#define entity_cast(ptr, target_class)\
  ((target_class*)EntityCast(ptr, target_class##_DLLClass.dec_iID))
CEntity* EntityCast(CEntity* p_entity, int entity_id);

#endif
