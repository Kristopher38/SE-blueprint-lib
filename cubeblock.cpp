#include "cubeblock.h"

using namespace rapidxml;

ICubeBlock::ICubeBlock() {}
ICubeBlock::~ICubeBlock() {}

void ICubeBlock::AppendAttributes(rapidxml::xml_node<>* block)
{
    rapidxml::xml_document<>* doc = block->document();

    block->append_node(doc->allocate_node(node_element, "SubtypeName", doc->allocate_string(SubtypeName().c_str())));
    block->append_node(doc->allocate_node(node_element, "Min"));
    block = block->last_node();
    block->append_attribute(doc->allocate_attribute("x", doc->allocate_string(std::to_string(Coords.x).c_str())));
    block->append_attribute(doc->allocate_attribute("y", doc->allocate_string(std::to_string(Coords.y).c_str())));
    block->append_attribute(doc->allocate_attribute("z", doc->allocate_string(std::to_string(Coords.z).c_str())));
    block = block->parent();

    block->append_node(doc->allocate_node(node_element, "BlockOrientation"));
    block = block->last_node();
    block->append_attribute(doc->allocate_attribute("Forward", OrientationStrLookup[BlockOrientation.Forward]));
    block->append_attribute(doc->allocate_attribute("Up", OrientationStrLookup[BlockOrientation.Up]));
    block = block->parent();

    block->append_node(doc->allocate_node(node_element, "ColorMaskHSV"));
    block = block->last_node();
    block->append_attribute(doc->allocate_attribute("x", doc->allocate_string(std::to_string(ColorMaskHSV.Hue).c_str())));
    block->append_attribute(doc->allocate_attribute("y", doc->allocate_string(std::to_string(ColorMaskHSV.Saturation).c_str())));
    block->append_attribute(doc->allocate_attribute("z", doc->allocate_string(std::to_string(ColorMaskHSV.Value).c_str())));
    block = block->parent();

    block->append_node(doc->allocate_node(node_element, "BuiltBy", doc->allocate_string(std::to_string(BuiltBy).c_str())));
}

const char* ICubeBlock::OrientationStrLookup[6] = {"Forward", "Backward", "Up", "Down", "Left", "Right"};
