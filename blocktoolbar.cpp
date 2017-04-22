#include "blocktoolbar.h"

using namespace rapidxml;

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

void BlockToolbar::AddEntry(uint8_t index, std::string action, EntityId blockEntityId)
{
    Slot item;
    item.Index = index;
    item.Action = action;
    item.BlockEntityId = blockEntityId;
    Slots.push_back(item);
}

void BlockToolbar::AddEntry(uint8_t index, std::string action, ITerminalBlock* cubeblock)
{
    this->AddEntry(index, action, cubeblock->entityId);
}

void BlockToolbar::AddEntry(uint8_t index, std::string action, ITerminalBlock& cubeblock)
{
    this->AddEntry(index, action, cubeblock.entityId);
}

void BlockToolbar::RemoveEntry(uint8_t index)
{
    for (uint8_t i = 0; i < Slots.size(); ++i)
    {
        if (Slots[i].Index == index)
        {
            Slots.erase(Slots.begin()+i);
            break;
        }
    }
}

uint8_t BlockToolbar::FirstEmptySlot()
{
    if (Slots.size())
    {
        uint8_t max_index = Slots[0].Index;
        for (std::vector<Slot>::iterator it = Slots.begin(); it != Slots.end(); ++it)
        {
            if (it->Index > max_index)
                max_index = it->Index;
        }
        return max_index+1;
    } else return 0;
}
