#include "cubegrid.h"

using namespace rapidxml;

CubeGrid::CubeGrid() {}

CubeGrid::CubeGrid(uint64_t* entity_counter, rapidxml::xml_node<>* cubegrid_node, bool size_inheritance, BLOCK_SIZE grid_size)
{
    this->entity_counter_ptr = entity_counter;
    this->cubegrid_node = cubegrid_node;
    this->size_inheritance = size_inheritance;
    this->grid_size = grid_size;
}

CubeGrid::~CubeGrid() {}

rapidxml::xml_node<>* CubeGrid::FindBlock(int x, int y, int z)
{
    for (rapidxml::xml_node<>* block = cubegrid_node->first_node("CubeBlocks")->first_node(); block; block = block->next_sibling())
    {
        rapidxml::xml_node<>* block_coords = block->first_node("Min");
        if (std::string(block_coords->first_attribute("x")->value()) != std::to_string(x))
            continue;
        if (std::string(block_coords->first_attribute("y")->value()) != std::to_string(y))
            continue;
        if (std::string(block_coords->first_attribute("z")->value()) != std::to_string(z))
            continue;

        return block;
    }
    return 0;
}

void CubeGrid::AddBlock(ICubeBlock* cubeblock)
{
    rapidxml::xml_node<>* block = FindBlock(cubeblock->Coords.x, cubeblock->Coords.y, cubeblock->Coords.z);
    if (!block)
    {
        rapidxml::xml_node<>* block = cubegrid_node->first_node("CubeBlocks");
        rapidxml::xml_document<>* doc = block->document();
        block->append_node(doc->allocate_node(node_element, "MyObjectBuilder_CubeBlock"));
        block = block->last_node();
        block->append_attribute(doc->allocate_attribute("xsi:type", doc->allocate_string(cubeblock->ObjectBuilder().insert(0, "MyObjectBuilder_").c_str())));

        ITerminalBlock* myTerminalBlock = dynamic_cast<ITerminalBlock*>(cubeblock);
        if (myTerminalBlock)
            myTerminalBlock->EntityId = (*entity_counter_ptr)++;

        if (size_inheritance)
            cubeblock->Size = grid_size;
        cubeblock->AppendAttributes(block);
    } else throw std::invalid_argument(std::string("Cannot add block at coordinates [x: ") + std::to_string(cubeblock->Coords.x) + std::string(", y: ") + std::to_string(cubeblock->Coords.y) + std::string(", z: ") + std::to_string(cubeblock->Coords.z) + std::string("], block at those coordinates already exists"));
}

void CubeGrid::RemoveBlock(int x, int y, int z)
{
    rapidxml::xml_node<>* block = FindBlock(x, y, z);
    if (block)
        cubegrid_node->first_node("CubeBlocks")->remove_node(block);
    else throw std::invalid_argument(std::string("Cannot remove block at coordinates [x: ") + std::to_string(x) + std::string(", y: ") + std::to_string(y) + std::string(", z: ") + std::to_string(z) + std::string("], block at those coordinates doesn't exist"));
}

void CubeGrid::Remove()
{
    cubegrid_node->parent()->remove_node(cubegrid_node);
}
