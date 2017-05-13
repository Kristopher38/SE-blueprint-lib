#include "blocktoolbar.h"

using namespace rapidxml;

void Slot::AppendXml(rapidxml::xml_node<>* slot)
{
    rapidxml::xml_document<>* doc = slot->document();
    slot->append_node(doc->allocate_node(node_element, "Slot"));
    slot = slot->last_node();
    slot->append_node(doc->allocate_node(node_element, "Index", doc->allocate_string(std::to_string(this->Index).c_str())));
    slot->append_node(doc->allocate_node(node_element, "Item"));
    slot->append_node(doc->allocate_node(node_element, "Data"));
    slot = slot->last_node();
    slot->append_attribute(doc->allocate_attribute("xsi:type", "MyObjectBuilder_ToolbarItemTerminalBlock"));
    slot->append_node(doc->allocate_node(node_element, "Action", this->Action.c_str()));
    slot->append_node(doc->allocate_node(node_element, "BlockEntityId", doc->allocate_string(std::to_string(*this->BlockEntityId).c_str())));
}

void GroupSlot::AppendXml(rapidxml::xml_node<>* group_slot)
{
    rapidxml::xml_document<>* doc = group_slot->document();
    this->Slot::AppendXml(group_slot);
    group_slot = group_slot->last_node("Slot")->last_node("Data");
    group_slot->first_attribute()->value("MyObjectBuilder_ToolbarItemTerminalGroup");
    group_slot->insert_node(group_slot->last_node("BlockEntityId"), doc->allocate_node(node_element, "GridEntityId", doc->allocate_string(std::to_string(*this->gridEntityId).c_str())));
    group_slot->append_node(doc->allocate_node(node_element, "GroupName", this->groupName.c_str()));
    group_slot->last_node("BlockEntityId")->value(group_slot->parent()->parent()->parent()->parent()->last_node("EntityId")->value());
}

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
        Slots[i]->AppendXml(block);
}

int8_t BlockToolbar::GetIndex(int8_t index)
{
    if (index > -1)   // range check
    {
        if (index < MaxSlots)
            return index;
        else
            throw std::out_of_range("Toolbar index out of range");
    }
    else
        return this->FirstEmptySlot();
}

void BlockToolbar::AddEntry(std::string action, EntityId blockEntityId, int8_t index)
{
    std::shared_ptr<Slot> item = std::make_shared<Slot>();
    item->Index = this->GetIndex(index);
    item->Action = action;
    item->BlockEntityId = blockEntityId;
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

void BlockToolbar::AddEntry(std::string action, const BlockGroup& blockgroup, int8_t index)
{
    std::shared_ptr<GroupSlot> item = std::make_shared<GroupSlot>();
    item->Index = this->GetIndex(index);
    item->Action = action;
    item->BlockEntityId = std::make_shared<uint64_t>(0);
    item->groupName = blockgroup.name;
    item->gridEntityId = std::make_shared<uint64_t>(0);
    Slots.push_back(item);
}

void BlockToolbar::RemoveEntry(int8_t index)
{
    Slots.erase(Slots.begin()+index);
}

uint8_t BlockToolbar::FirstEmptySlot()
{
    if (Slots.size())
    {
        uint8_t max_index = Slots[0]->Index;
        for (std::vector<std::shared_ptr<Slot>>::iterator it = Slots.begin()+1; it != Slots.end(); ++it)
        {
            if (it->get()->Index > max_index)
                max_index = it->get()->Index;
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
        std::cout<<PrintIndent(indent+2)<<"Index: "<<static_cast<int>(Slots[i]->Index)<<std::endl;
        std::cout<<PrintIndent(indent+2)<<"Action: "<<Slots[i]->Action<<std::endl;
        std::cout<<PrintIndent(indent+2)<<"EntityId ptr address: "<<Slots[i]->BlockEntityId.get()<<std::endl;
    }
}
