#include "cubegrid.h"

using namespace rapidxml;

void CubeGrid::AppendXml(rapidxml::xml_node<>* cubegrids_node)
{
    rapidxml::xml_document<>* doc = cubegrids_node->document();
    rapidxml::xml_node<>* cubegrid = doc->allocate_node(node_element, "CubeGrid");
    cubegrids_node->append_node(cubegrid);

    cubegrid->append_node(doc->allocate_node(node_element, "SubtypeName"));
    cubegrid->append_node(doc->allocate_node(node_element, "EntityId", doc->allocate_string(std::to_string(*this->entityId).c_str())));
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
        if (Parameters.BlocksInheritGridSize)
            blocks[i]->Size = Parameters.GridSize;

        rapidxml::xml_node<>* cubeblocks_node = cubegrid->last_node();
        cubeblocks_node->append_node(doc->allocate_node(node_element, "MyObjectBuilder_CubeBlock"));
        cubeblocks_node = cubeblocks_node->last_node();
        cubeblocks_node->append_attribute(doc->allocate_attribute("xsi:type", doc->allocate_string(blocks[i]->ObjectBuilder().insert(0, "MyObjectBuilder_").c_str())));
        blocks[i]->AppendAttributes(cubeblocks_node);
    }

    cubegrid->append_node(doc->allocate_node(node_element, "BlockGroups"));
    for (std::size_t i = 0; i < groups.size(); ++i)
    {
        rapidxml::xml_node<>* blockgroups_node = cubegrid->last_node();
        blockgroups_node->append_node(doc->allocate_node(node_element, "MyObjectBuilder_BlockGroup"));
        blockgroups_node = blockgroups_node->last_node();
        groups[i].AppendXml(blockgroups_node);
    }

    cubegrid->append_node(doc->allocate_node(node_element, "IsStatic", Parameters.IsStatic ? "true" : "false"));
    cubegrid->append_node(doc->allocate_node(node_element, "DisplayName", doc->allocate_string(Parameters.DisplayName.c_str())));
    cubegrid->append_node(doc->allocate_node(node_element, "DestructibleBlocks", Parameters.DestructibleBlocks ? "true" : "false"));
    cubegrid->append_node(doc->allocate_node(node_element, "IsRespawnGrid", Parameters.IsRespawnGrid ? "true" : "false"));
    cubegrid->append_node(doc->allocate_node(node_element, "LocalCoordSys", doc->allocate_string(std::to_string(Parameters.LocalCoordSys).c_str())));
}

BlocksVector<ICubeBlock> CubeGrid::CloneBlocks(const BlocksVector<ICubeBlock>& to_clone)
{
    BlocksVector<ICubeBlock> cloned;
    std::map<uint64_t*, uint64_t*> entityIdPair;

    cloned.reserve(to_clone.size());
    for (BlocksVector<ICubeBlock>::const_iterator it = to_clone.cbegin(); it != to_clone.cend(); ++it)
    {
        Blockptr<ICubeBlock> cloned_block = it->get()->clone();
        Blockptr<ITerminalBlock> myTerminalBlock = std::dynamic_pointer_cast<ITerminalBlock>(cloned_block);
        if (myTerminalBlock)
        {
            uint64_t* old_entityid = myTerminalBlock->entityId.get();
            myTerminalBlock->entityId = std::make_shared<uint64_t>(0);
            entityIdPair[old_entityid] = myTerminalBlock->entityId.get();   // use old pointer address (old entity id) as a key to new pointer address (new entity id)
        }
        cloned.push_back(cloned_block);
    }

    for (BlocksVector<ICubeBlock>::iterator it = cloned.begin(); it != cloned.end(); ++it)
    {
        std::shared_ptr<Toolbar> myToolbarBlock = std::dynamic_pointer_cast<Toolbar>(*it);
        if (myToolbarBlock)
            for (std::vector<std::shared_ptr<Slot>>::iterator it_slot = myToolbarBlock->toolbar.Slots.begin(); it_slot != myToolbarBlock->toolbar.Slots.end(); ++it_slot)
            {
                uint64_t* new_entityid = entityIdPair[it_slot->get()->BlockEntityId.get()];
                if (new_entityid)
                    it_slot->get()->BlockEntityId.reset(new_entityid);   // update pointer in slot using old pointer (old entity id) that is still sitting there after copying by using it as a key in map to get new pointer address (new entity id)
            }
    }

    return cloned;
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

/*struct Coordinates
{
    int x;
    int y;
    int z;
    Coordinates(int i_x, int i_y, int i_z) : x(i_x), y(i_y), z(i_z) {}
    bool operator()(const Coordinates& lhs, const Coordinates& rhs) const
    {
        return lhs < rhs;
    }
};*/

void CubeGrid::AttachCubegrid(CubeGrid cubegrid, int x, int y, int z)
{
    CubeGrid::TranslateCoords(&cubegrid.blocks, x, y, z);
    this->blocks.insert(this->blocks.end(), std::make_move_iterator(cubegrid.blocks.begin()), std::make_move_iterator(cubegrid.blocks.end()));

    /*std::set<Coordinates> cubeCoords;
    for (BlocksVector<ICubeBlock>::iterator it = blocks.begin(); it != blocks.end(); ++it)
    {
        cubeCoords.insert(Coordinates((**it).Coords.x(), (**it).Coords.y(), (**it).Coords.z()));
    }

    if (this->Parameters.CheckForDuplicateCoords)
    {

    }*/
}

void CubeGrid::DebugPrint(unsigned indent)
{
    std::cout<<PrintIndent(indent)<<"BlocksVector<ICubeBlock> blocks:"<<std::endl;
    for (std::size_t i = 0; i < blocks.size(); i++)
    {
        std::cout<<PrintIndent(indent+1)<<"blocks["<<i<<"]:"<<std::endl;
        ITerminalBlock* myTerminalBlock = dynamic_cast<ITerminalBlock*>(blocks[i].get());
        if (myTerminalBlock)
        {
            std::cout<<PrintIndent(indent+2)<<"ObjectBuilder(): "<<myTerminalBlock->ObjectBuilder()<<std::endl;
            std::cout<<PrintIndent(indent+2)<<"entityId ptr address: "<<myTerminalBlock->entityId.get()<<std::endl;
            std::cout<<PrintIndent(indent+2)<<"CustomName: "<<myTerminalBlock->CustomName()<<std::endl;
            TimerBlock* myTimerBlock = dynamic_cast<TimerBlock*>(myTerminalBlock);
            if (myTimerBlock)
            {
                std::cout<<PrintIndent(indent+2)<<"Toolbar: "<<std::endl;
                myTimerBlock->toolbar.DebugPrint(indent+3);
            }
        }
    }
}

inline std::string CubeGrid::PrintIndent(unsigned indent)
{
    std::string tabs;
    for (unsigned i = 0; i < indent; i++, tabs+="\t");
    return tabs;
}
