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
