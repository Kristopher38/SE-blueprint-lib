#include "terminalblock.h"

using namespace rapidxml;

ITerminalBlock::ITerminalBlock() : CustomName(std::string()) {}

ITerminalBlock::~ITerminalBlock() {}

void ITerminalBlock::AppendAttributes(rapidxml::xml_node<>* block)
{
    ICubeBlock::AppendAttributes(block);

    rapidxml::xml_document<>* doc = block->document();
    block->append_node(doc->allocate_node(node_element, "CustomName", doc->allocate_string(CustomName().c_str())));
    block->append_node(doc->allocate_node(node_element, "ShowOnHUD", ShowOnHUD() ? "true" : "false"));
    block->append_node(doc->allocate_node(node_element, "ShowInTerminal", ShowInTerminal() ? "true" : "false"));
    block->append_node(doc->allocate_node(node_element, "ShowInInventory", ShowInInventory() ? "true" : "false"));
    block->append_node(doc->allocate_node(node_element, "EntityId", EntityId().EntityIdStr()));
    if (HasOwnership())
    {
        block->append_node(doc->allocate_node(node_element, "Owner", doc->allocate_string(std::to_string(Owner()).c_str())));
        switch (ShareMode())
        {
            case SHARE_NONE:
                break;
            case SHARE_FACTION:
                block->append_node(doc->allocate_node(node_element, "ShareMode", "Faction"));
                break;
            case SHARE_ALL:
                block->append_node(doc->allocate_node(node_element, "ShareMode", "All"));
                break;
        }
    }
}
