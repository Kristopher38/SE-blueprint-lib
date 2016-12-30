#include "cubegrids.h"

using namespace rapidxml;

CubeGrids::CubeGrids()
{
    this->entity_counter = 0;
}

CubeGrids::CubeGrids(rapidxml::xml_node<>* node_cubegrids)
{
    this->entity_counter = 0;
    this->node_cubegrids = node_cubegrids;
}

CubeGrids::~CubeGrids() {}

CubeGrid& CubeGrids::operator[](std::size_t idx)
{
    return cubegrids.at(idx);
}

std::size_t CubeGrids::Add()
{
    return this->Add(CubeGridParams());
}

std::size_t CubeGrids::Add(CubeGridParams parameters)
{
    rapidxml::xml_document<>* doc = node_cubegrids->document();
    rapidxml::xml_node<>* cubegrid = doc->allocate_node(node_element, "CubeGrid");
    node_cubegrids->append_node(cubegrid);
    cubegrids.push_back(CubeGrid(&entity_counter, cubegrid, parameters.BlocksInheritGridSize, parameters.GridSize));
    cubegrid->append_node(doc->allocate_node(node_element, "SubtypeName"));
    cubegrid->append_node(doc->allocate_node(node_element, "EntityId", doc->allocate_string(std::to_string(entity_counter++).c_str())));
    cubegrid->append_node(doc->allocate_node(node_element, "PersistentFlags", "CastShadows InScene"));
    cubegrid->append_node(doc->allocate_node(node_element, "PositionAndOrientation"));

    rapidxml::xml_node<>* position = cubegrid->last_node();
    position->append_node(doc->allocate_node(node_element, "Position"));
    position = position->last_node();
    position->append_attribute(doc->allocate_attribute("x", doc->allocate_string(std::to_string(parameters.Position.x).c_str())));
    position->append_attribute(doc->allocate_attribute("y", doc->allocate_string(std::to_string(parameters.Position.y).c_str())));
    position->append_attribute(doc->allocate_attribute("z", doc->allocate_string(std::to_string(parameters.Position.z).c_str())));
    position = position->parent();
    position->append_node(doc->allocate_node(node_element, "Forward"));
    position = position->last_node();
    position->append_attribute(doc->allocate_attribute("x", doc->allocate_string(std::to_string(parameters.Forward.x).c_str())));
    position->append_attribute(doc->allocate_attribute("y", doc->allocate_string(std::to_string(parameters.Forward.y).c_str())));
    position->append_attribute(doc->allocate_attribute("z", doc->allocate_string(std::to_string(parameters.Forward.z).c_str())));
    position = position->parent();
    position->append_node(doc->allocate_node(node_element, "Up"));
    position = position->last_node();
    position->append_attribute(doc->allocate_attribute("x", doc->allocate_string(std::to_string(parameters.Up.x).c_str())));
    position->append_attribute(doc->allocate_attribute("y", doc->allocate_string(std::to_string(parameters.Up.y).c_str())));
    position->append_attribute(doc->allocate_attribute("z", doc->allocate_string(std::to_string(parameters.Up.z).c_str())));
    position = position->parent();
    position->append_node(doc->allocate_node(node_element, "Orientation"));
    position = position->last_node();
    position->append_node(doc->allocate_node(node_element, "X", doc->allocate_string(std::to_string(parameters.Orientation.x).c_str())));
    position->append_node(doc->allocate_node(node_element, "Y", doc->allocate_string(std::to_string(parameters.Orientation.y).c_str())));
    position->append_node(doc->allocate_node(node_element, "Z", doc->allocate_string(std::to_string(parameters.Orientation.z).c_str())));
    position->append_node(doc->allocate_node(node_element, "W", doc->allocate_string(std::to_string(parameters.Orientation.w).c_str())));

    cubegrid->append_node(doc->allocate_node(node_element, "GridSizeEnum", parameters.GridSize ? "Large" : "Small"));
    cubegrid->append_node(doc->allocate_node(node_element, "CubeBlocks"));
    cubegrid->append_node(doc->allocate_node(node_element, "IsStatic", parameters.IsStatic ? "true" : "false"));
    cubegrid->append_node(doc->allocate_node(node_element, "DisplayName", doc->allocate_string(parameters.DisplayName.c_str())));
    cubegrid->append_node(doc->allocate_node(node_element, "DestructibleBlocks", parameters.DestructibleBlocks ? "true" : "false"));
    cubegrid->append_node(doc->allocate_node(node_element, "IsRespawnGrid", parameters.IsRespawnGrid ? "true" : "false"));
    cubegrid->append_node(doc->allocate_node(node_element, "LocalCoordSys", doc->allocate_string(std::to_string(parameters.LocalCoordSys).c_str())));

    return entity_counter - 1;
}

void CubeGrids::Remove(std::size_t index)
{
    cubegrids.at(index).Remove();
}
