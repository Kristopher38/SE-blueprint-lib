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
        static const uint8_t MaxSlots;

        TOOLBAR_TYPE ToolbarType;
        //SelectedSlot???
        std::vector<Slot> Slots;

    public:
        BlockToolbar();
        ~BlockToolbar();

        void AppendAttributes(rapidxml::xml_node<>* block);

        void AddEntry(std::string action, EntityId blockEntityId, int8_t index = -1);
        void AddEntry(std::string action, ITerminalBlock* cubeblock, int8_t index = -1);
        void AddEntry(std::string action, const ITerminalBlock& cubeblock, int8_t index = -1);
        void RemoveEntry(int8_t index);
        uint8_t FirstEmptySlot();
        void DebugPrint(unsigned indent);
        std::string PrintIndent(unsigned indent);
};

class Toolbar
{
    public:
        BlockToolbar toolbar;
};

#endif // H_BLOCKTOOLBAR
