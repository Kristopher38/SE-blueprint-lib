#ifndef H_ENTITYID_ACCESSOR
#define H_ENTITYID_ACCESSOR

#include <cstdint>
#include <stdio.h>

class entityId
{
    private:
        char entityIdStr[20];
        uint64_t EntityId;
    public:
        entityId& operator=(const uint64_t& rhs);
        char* EntityIdStr();
        entityId& operator()();
};

#endif // H_ENTITYID_ACCESSOR

