#ifndef H_BLOCKTOOLBAR
#define H_BLOCKTOOLBAR

#include <string>
#include <vector>
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include "terminalblock.h"

using namespace rapidxml;

class BlockToolbar
{
    friend class CubeGrid;
    private:
        struct Slot
        {
            uint8_t Index;
            //Item???
            std::string Action;
            EntityId BlockEntityId;
        };
        enum TOOLBAR_TYPE {TOOLBAR_CHARACTER};

        TOOLBAR_TYPE ToolbarType;
        //SelectedSlot???
        std::vector<Slot> Slots;

    public:
        BlockToolbar();
        ~BlockToolbar();

        void AppendAttributes(rapidxml::xml_node<>* block);

        void AddEntry(uint8_t index, std::string action, EntityId blockEntityId);
        void AddEntry(uint8_t index, std::string action, ITerminalBlock* cubeblock);
        void AddEntry(uint8_t index, std::string action, ITerminalBlock& cubeblock);
        void RemoveEntry(uint8_t index);
        uint8_t FirstEmptySlot();
};

class Toolbar
{
    public:
        BlockToolbar toolbar;
};

#endif // H_BLOCKTOOLBAR
