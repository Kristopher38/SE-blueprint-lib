#ifndef H_CUBEGRID
#define H_CUBEGRID

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <memory>
#include <algorithm>
#include <rapidxml/rapidxml.hpp>
#include "cubeblock.h"
#include "terminalblock.h"
#include "typedefs.h"
#include "blocksvector.h"

using namespace rapidxml;

class CubeGrid
{
    friend class Blueprint;
    private:
        void AppendXml(rapidxml::xml_node<>* cubegrids_node, uint64_t* entity_counter);

    public:
        CubeGridParams Parameters;
        IBlocksVector<ICubeBlock> blocks;

    private:
        CubeGrid(CubeGridParams parameters, IBlocksVector<ICubeBlock> cubeblocks) : Parameters(parameters), blocks(cubeblocks) {}
        IBlocksVector<ICubeBlock> CloneBlocks(IBlocksVector<ICubeBlock> to_clone)
        {
            auto cloner = [](const Block<ICubeBlock>& ptr) -> Block<ICubeBlock>
                {return ptr->clone();};

            IBlocksVector<ICubeBlock> cloned;
            std::transform(to_clone.begin(), to_clone.end(), std::back_inserter(cloned), cloner);
            return cloned;
        }

    public:
        CubeGrid(CubeGridParams parameters = CubeGridParams()) : Parameters(parameters) {}
        ~CubeGrid() {}

        CubeGrid(const CubeGrid& cubegrid) : Parameters(cubegrid.Parameters), blocks(CloneBlocks(cubegrid.blocks)) {}

        std::size_t FindBlock(int x, int y, int z);
};

#endif // H_CUBEGRID

