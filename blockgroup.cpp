#include "blockgroup.h"

void BlockGroup::AddBlock(int x, int y, int z)
{
    this->blocks.push_back(Vector3I(x, y, z));
}

void BlockGroup::AddBlock(ICubeBlock& block)
{
    this->blocks.push_back(Vector3I(block.Coords.x(), block.Coords.y(), block.Coords.z()));
}

void BlockGroup::AppendXml(rapidxml::xml_node<>* group)
{
    rapidxml::xml_document<>* doc = group->document();
    group->append_node(doc->allocate_node(node_element, "Name", name.c_str()));
    group->append_node(doc->allocate_node(node_element, "Blocks"));
    group = group->last_node();
    for (std::size_t i = 0; i < blocks.size(); ++i)
    {
        group->append_node(doc->allocate_node(node_element, "Vector3I"));
        group = group->last_node();
        group->append_node(doc->allocate_node(node_element, "X", doc->allocate_string(std::to_string(blocks[i].x).c_str())));
        group->append_node(doc->allocate_node(node_element, "Y", doc->allocate_string(std::to_string(blocks[i].y).c_str())));
        group->append_node(doc->allocate_node(node_element, "Z", doc->allocate_string(std::to_string(blocks[i].z).c_str())));
        group = group->parent();
    }
}
