#include "cubegrid.h"

using namespace rapidxml;

void CubeGrid::AppendXml(rapidxml::xml_node<>* cubegrids_node, uint64_t* entity_counter)
{
    rapidxml::xml_document<>* doc = cubegrids_node->document();
    rapidxml::xml_node<>* cubegrid = doc->allocate_node(node_element, "CubeGrid");
    cubegrids_node->append_node(cubegrid);

    cubegrid->append_node(doc->allocate_node(node_element, "SubtypeName"));
    cubegrid->append_node(doc->allocate_node(node_element, "EntityId", doc->allocate_string(std::to_string((*entity_counter)++).c_str())));
    cubegrid->append_node(doc->allocate_node(node_element, "PersistentFlags", "CastShadows InScene"));
    cubegrid->append_node(doc->allocate_node(node_element, "PositionAndOrientation"));

    rapidxml::xml_node<>* position = cubegrid->last_node();
    position->append_node(doc->allocate_node(node_element, "Position"));
    position = position->last_node();
    position->append_attribute(doc->allocate_attribute("x", doc->allocate_string(std::to_string(Parameters.Position.x).c_str())));
    position->append_attribute(doc->allocate_attribute("y", doc->allocate_string(std::to_string(Parameters.Position.y).c_str())));
    position->append_attribute(doc->allocate_attribute("z", doc->allocate_string(std::to_string(Parameters.Position.z).c_str())));
    position = position->parent();
    position->append_node(doc->allocate_node(node_element, "Forward"));
    position = position->last_node();
    position->append_attribute(doc->allocate_attribute("x", doc->allocate_string(std::to_string(Parameters.Forward.x).c_str())));
    position->append_attribute(doc->allocate_attribute("y", doc->allocate_string(std::to_string(Parameters.Forward.y).c_str())));
    position->append_attribute(doc->allocate_attribute("z", doc->allocate_string(std::to_string(Parameters.Forward.z).c_str())));
    position = position->parent();
    position->append_node(doc->allocate_node(node_element, "Up"));
    position = position->last_node();
    position->append_attribute(doc->allocate_attribute("x", doc->allocate_string(std::to_string(Parameters.Up.x).c_str())));
    position->append_attribute(doc->allocate_attribute("y", doc->allocate_string(std::to_string(Parameters.Up.y).c_str())));
    position->append_attribute(doc->allocate_attribute("z", doc->allocate_string(std::to_string(Parameters.Up.z).c_str())));
    position = position->parent();
    position->append_node(doc->allocate_node(node_element, "Orientation"));
    position = position->last_node();
    position->append_node(doc->allocate_node(node_element, "X", doc->allocate_string(std::to_string(Parameters.Orientation.x).c_str())));
    position->append_node(doc->allocate_node(node_element, "Y", doc->allocate_string(std::to_string(Parameters.Orientation.y).c_str())));
    position->append_node(doc->allocate_node(node_element, "Z", doc->allocate_string(std::to_string(Parameters.Orientation.z).c_str())));
    position->append_node(doc->allocate_node(node_element, "W", doc->allocate_string(std::to_string(Parameters.Orientation.w).c_str())));

    cubegrid->append_node(doc->allocate_node(node_element, "GridSizeEnum", Parameters.GridSize ? "Large" : "Small"));
    cubegrid->append_node(doc->allocate_node(node_element, "CubeBlocks"));
    for (std::size_t i = 0; i < blocks.size(); ++i)
    {
        ITerminalBlock* myTerminalBlock = dynamic_cast<ITerminalBlock*>(blocks[i].get());
        if (myTerminalBlock)
            myTerminalBlock->EntityId = (*entity_counter)++;
        if (Parameters.BlocksInheritGridSize)
            blocks[i]->Size = Parameters.GridSize;

        rapidxml::xml_node<>* cubeblocks_node = cubegrid->last_node();
        cubeblocks_node->append_node(doc->allocate_node(node_element, "MyObjectBuilder_CubeBlock"));
        cubeblocks_node = cubeblocks_node->last_node();
        cubeblocks_node->append_attribute(doc->allocate_attribute("xsi:type", doc->allocate_string(blocks[i]->ObjectBuilder().insert(0, "MyObjectBuilder_").c_str())));
        blocks[i]->AppendAttributes(cubeblocks_node);
    }
    cubegrid->append_node(doc->allocate_node(node_element, "IsStatic", Parameters.IsStatic ? "true" : "false"));
    cubegrid->append_node(doc->allocate_node(node_element, "DisplayName", doc->allocate_string(Parameters.DisplayName.c_str())));
    cubegrid->append_node(doc->allocate_node(node_element, "DestructibleBlocks", Parameters.DestructibleBlocks ? "true" : "false"));
    cubegrid->append_node(doc->allocate_node(node_element, "IsRespawnGrid", Parameters.IsRespawnGrid ? "true" : "false"));
    cubegrid->append_node(doc->allocate_node(node_element, "LocalCoordSys", doc->allocate_string(std::to_string(Parameters.LocalCoordSys).c_str())));
}

void CubeGrid::TranslateCoords(BlocksVector<ICubeBlock>* to_translate, int x, int y, int z)
{
    for (BlocksVector<ICubeBlock>::iterator it = to_translate->begin(); it != to_translate->end(); ++it)
    {
        (*it)->Coords.x += x;
        (*it)->Coords.y += y;
        (*it)->Coords.z += z;
    }
}

void CubeGrid::TranslateCoords(int x, int y, int z)
{
    CubeGrid::TranslateCoords(&this->blocks, x, y, z);
}

void CubeGrid::AttachCubegrid(CubeGrid& cubegrid, int x, int y, int z)
{
    BlocksVector<ICubeBlock> to_attach = cubegrid.CloneBlocks(cubegrid.blocks);
    CubeGrid::TranslateCoords(&to_attach, x, y, z);
    blocks.insert(blocks.end(), to_attach.begin(), to_attach.end());
}
