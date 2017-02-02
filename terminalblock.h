#ifndef H_TERMINALBLOCK
#define H_TERMINALBLOCK

#include <string>
#include <memory>
#include <rapidxml/rapidxml.hpp>
#include "cubeblock.h"

using namespace rapidxml;

typedef std::shared_ptr<uint64_t> EntityId;

class ITerminalBlock : public ICubeBlock // shows in terminal
{
    friend class BlockToolbar;
    friend class Blueprint;

    protected:
        virtual void AppendAttributes(rapidxml::xml_node<>* block);
        EntityId entityId;

    public:
        enum SHARE_MODE {SHARE_NONE, SHARE_FACTION, SHARE_ALL};

        Accessor<bool> ShowOnHUD = true;
        Accessor<bool> ShowInTerminal = true;
        Accessor<bool> ShowInToolbarConfig = true;
        Accessor<bool> ShowInInventory = true;
        Accessor<bool> HasOwnership = false;
        Accessor<uint64_t> Owner = 0;
        Accessor<SHARE_MODE> ShareMode = SHARE_NONE;
        Accessor<std::string> CustomName = std::string();

        ITerminalBlock();
        virtual ~ITerminalBlock();

        virtual bool operator==(ITerminalBlock& rhs)
        {
            bool ret = ICubeBlock::operator==(*dynamic_cast<ICubeBlock*>(&rhs));
            return (this->ShowOnHUD == rhs.ShowOnHUD &&
                    this->ShowInTerminal == rhs.ShowInTerminal &&
                    this->ShowInToolbarConfig == rhs.ShowInToolbarConfig &&
                    this->ShowInInventory == rhs.ShowInInventory &&
                    //this->EntityId == rhs.EntityId &&
                    this->HasOwnership == rhs.HasOwnership &&
                    this->Owner == rhs.Owner &&
                    this->ShareMode == rhs.ShareMode &&
                    ret);
        }
        virtual bool operator!=(ITerminalBlock& rhs)
        {
            return !(*this==rhs);
        }
};

#endif // H_TERMINALBLOCK
