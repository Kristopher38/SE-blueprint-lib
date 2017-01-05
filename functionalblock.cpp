#include "functionalblock.h"

using namespace rapidxml;

IFunctionalBlock::IFunctionalBlock()
{
    this->Enabled = true;
}

IFunctionalBlock::~IFunctionalBlock() {}

void IFunctionalBlock::AppendAttributes(rapidxml::xml_node<>* block)
{
    ITerminalBlock::AppendAttributes(block);
    block->append_node(block->document()->allocate_node(node_element, "Enabled", Enabled() ? "true" : "false"));
}
