#include "entityid_accessor.h"

entityId& entityId::operator=(const uint64_t& rhs)
{
    EntityId = rhs;
    sprintf(entityIdStr, "%I64d", EntityId);
    return *this;
}
char* entityId::EntityIdStr()
{
    return entityIdStr;
}
entityId& entityId::operator()()
{
    return *this;
}

entityId::entityId(uint64_t id) : EntityId(id) {sprintf(entityIdStr, "%I64d", id);}
