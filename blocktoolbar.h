#ifndef H_BLOCKTOOLBAR
#define H_BLOCKTOOLBAR

#include <string>
#include <vector>
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include "entityid_accessor.h"
#include "terminalblock.h"

using namespace rapidxml;

class BlockToolbar
{
    private:
        struct Slot
        {
            uint8_t Index;
            //Item???
            std::string Action;
            std::shared_ptr<uint64_t> BlockEntityId;
        };
        enum TOOLBAR_TYPE {TOOLBAR_CHARACTER};

        TOOLBAR_TYPE ToolbarType;
        //SelectedSlot???
        std::vector<Slot> Slots;

    public:
        BlockToolbar();
        ~BlockToolbar();

        void AppendAttributes(rapidxml::xml_node<>* block);

        void AddEntry(uint8_t index, std::string action, std::shared_ptr<uint64_t> blockEntityId);
        void AddEntry(uint8_t index, std::string action, ITerminalBlock* cubeblock);
        void AddEntry(uint8_t index, std::string action, ITerminalBlock& cubeblock);
        void RemoveEntry(uint8_t index);
};

#endif // H_BLOCKTOOLBAR
