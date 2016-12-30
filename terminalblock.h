#ifndef H_TERMINALBLOCK
#define H_TERMINALBLOCK

#include <string>
#include <rapidxml/rapidxml.hpp>
#include "cubeblock.h"
#include "entityid_accessor.h"

using namespace rapidxml;

class ITerminalBlock : public ICubeBlock // shows in terminal
{
    protected:
        std::string CustomName;
        virtual void AppendAttributes(rapidxml::xml_node<>* block);

    public:
        enum SHARE_MODE {SHARE_NONE, SHARE_FACTION, SHARE_ALL};

        bool ShowOnHUD;
        bool ShowInTerminal;
        bool ShowInToolbarConfig;
        bool ShowInInventory;
        class entityId EntityId;

        bool HasOwnership;
        uint64_t Owner;
        SHARE_MODE ShareMode;

        ITerminalBlock();
        virtual ~ITerminalBlock();
};

#endif // H_TERMINALBLOCK
