#ifndef H_CUBEGRID
#define H_CUBEGRID

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <memory>
#include <algorithm>
#include <set>
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
        BlocksVector<ICubeBlock> blocks;

    private:
        CubeGrid(CubeGridParams parameters, BlocksVector<ICubeBlock> cubeblocks) : Parameters(parameters), blocks(cubeblocks) {}
        BlocksVector<ICubeBlock> CloneBlocks(BlocksVector<ICubeBlock> to_clone)
        {
            auto cloner = [](const Blockptr<ICubeBlock>& ptr) -> Blockptr<ICubeBlock>
                {return ptr->clone();};

            BlocksVector<ICubeBlock> cloned;
            std::transform(to_clone.begin(), to_clone.end(), std::back_inserter(cloned), cloner);
            return cloned;
        }

    public:
        CubeGrid(CubeGridParams parameters = CubeGridParams()) : Parameters(parameters) {}
        ~CubeGrid() {}

        CubeGrid(const CubeGrid& cubegrid) : Parameters(cubegrid.Parameters), blocks(CloneBlocks(cubegrid.blocks)) {}

        static void TranslateCoords(BlocksVector<ICubeBlock>* to_translate, int x, int y, int z);
        void TranslateCoords(int x, int y, int z);
        void AttachCubegrid(CubeGrid& cubegrid, int x = 0, int y = 0, int z = 0);
};

#endif // H_CUBEGRID

