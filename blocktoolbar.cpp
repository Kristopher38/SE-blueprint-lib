#include "blocktoolbar.h"

using namespace rapidxml;

const uint8_t BlockToolbar::MaxSlots = 90;

BlockToolbar::BlockToolbar()
{
    this->ToolbarType = TOOLBAR_CHARACTER;
}

BlockToolbar::~BlockToolbar() {}

void BlockToolbar::AppendAttributes(rapidxml::xml_node<>* block)
{
    rapidxml::xml_document<>* doc = block->document();
    block->append_node(doc->allocate_node(node_element, "Toolbar"));
    block = block->last_node();
    switch(ToolbarType)
    {
        case TOOLBAR_CHARACTER:
            block->append_node(doc->allocate_node(node_element, "ToolbarType", "Character"));
            break;
    }
    block->append_node(doc->allocate_node(node_element, "SelectedSlot"));
    block = block->last_node();
    block->append_attribute(doc->allocate_attribute("xsi:nil", "true"));
    block = block->parent();
    block->append_node(doc->allocate_node(node_element, "Slots"));
    block = block->last_node();
    for (std::size_t i = 0; i < Slots.size(); ++i)
    {
        block->append_node(doc->allocate_node(node_element, "Slot"));
        block = block->last_node();
        block->append_node(doc->allocate_node(node_element, "Index", doc->allocate_string(std::to_string(Slots[i].Index).c_str())));
        block->append_node(doc->allocate_node(node_element, "Item"));
        block->append_node(doc->allocate_node(node_element, "Data"));
        block = block->last_node();
        block->append_attribute(doc->allocate_attribute("xsi:type", "MyObjectBuilder_ToolbarItemTerminalBlock"));
        block->append_node(doc->allocate_node(node_element, "Action", doc->allocate_string(Slots[i].Action.c_str())));
        block->append_node(doc->allocate_node(node_element, "BlockEntityId", doc->allocate_string(std::to_string(*Slots[i].BlockEntityId).c_str())));
        block = block->parent()->parent();
    }
}

void BlockToolbar::AddEntry(std::string action, EntityId blockEntityId, int8_t index)
{
    Slot item;

    if (index > -1)   // range check
    {
        if (index < MaxSlots)
            item.Index = index;
        else
            throw std::out_of_range("Toolbar index out of range");
    }
    else
        item.Index = this->FirstEmptySlot();

    item.Action = action;
    item.BlockEntityId = blockEntityId;
    Slots.push_back(item);
}

void BlockToolbar::AddEntry(std::string action, ITerminalBlock* cubeblock, int8_t index)
{
    this->AddEntry(action, cubeblock->entityId, index);
}

void BlockToolbar::AddEntry(std::string action, const ITerminalBlock& cubeblock, int8_t index)
{
    this->AddEntry(action, cubeblock.entityId, index);
}

void BlockToolbar::RemoveEntry(int8_t index)
{
    Slots.erase(Slots.begin()+index);
}

uint8_t BlockToolbar::FirstEmptySlot()
{
    if (Slots.size())
    {
        uint8_t max_index = Slots[0].Index;
        for (std::vector<Slot>::iterator it = Slots.begin()+1; it != Slots.end(); ++it)
        {
            if (it->Index > max_index)
                max_index = it->Index;
        }
        if (max_index+1 < MaxSlots)     // range check
            return max_index+1;
        else throw std::out_of_range("No empty slots in toolbar");
    }
    return 0;
}

inline std::string BlockToolbar::PrintIndent(unsigned indent)
{
    std::string tabs;
    for (unsigned i = 0; i < indent; i++, tabs+="\t");
    return tabs;
}

void BlockToolbar::DebugPrint(unsigned indent)
{
    std::cout<<PrintIndent(indent)<<"std::vector<Slot> Slots"<<std::endl;
    for (std::size_t i = 0; i < Slots.size(); i++)
    {
        std::cout<<PrintIndent(indent+1)<<"Slots["<<i<<"]:"<<std::endl;
        std::cout<<PrintIndent(indent+2)<<"Index: "<<static_cast<int>(Slots[i].Index)<<std::endl;
        std::cout<<PrintIndent(indent+2)<<"Action: "<<Slots[i].Action<<std::endl;
        std::cout<<PrintIndent(indent+2)<<"EntityId ptr address: "<<Slots[i].BlockEntityId.get()<<std::endl;
    }
}
