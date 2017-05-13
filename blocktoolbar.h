#ifndef H_BLOCKTOOLBAR
#define H_BLOCKTOOLBAR

#include <string>
#include <vector>
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include <memory>
#include "terminalblock.h"
#include "blockgroup.h"

using namespace rapidxml;

struct Slot
{
    uint8_t Index;
    //Item???
    std::string Action;
    EntityId BlockEntityId;

    Slot() {}
    virtual ~Slot() {}
    virtual void AppendXml(rapidxml::xml_node<>* slot);
};

struct GroupSlot : public Slot
{
    std::string groupName;
    EntityId gridEntityId;

    GroupSlot() {}
    ~GroupSlot() {}
    void AppendXml(rapidxml::xml_node<>* group_slot) override;
};

class BlockToolbar
{
    friend class CubeGrid;
    private:
        enum TOOLBAR_TYPE {TOOLBAR_CHARACTER};
        static const uint8_t MaxSlots;

        TOOLBAR_TYPE ToolbarType;
        //SelectedSlot???
        std::vector<std::shared_ptr<Slot>> Slots;

        int8_t GetIndex(int8_t index);
    public:
        BlockToolbar();
        ~BlockToolbar();

        void AppendAttributes(rapidxml::xml_node<>* block);

        void AddEntry(std::string action, EntityId blockEntityId, int8_t index = -1);
        void AddEntry(std::string action, ITerminalBlock* cubeblock, int8_t index = -1);
        void AddEntry(std::string action, const ITerminalBlock& cubeblock, int8_t index = -1);
        void AddEntry(std::string action, const BlockGroup& blockgroup, int8_t index = -1);
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
