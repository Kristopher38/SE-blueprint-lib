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
#include "blocktoolbar.h"

using namespace rapidxml;

class CubeGrid
{
    friend class Blueprint;
    private:
        void AppendXml(rapidxml::xml_node<>* cubegrids_node);
        EntityId entityId;

    public:
        CubeGridParams Parameters;
        BlocksVector<ICubeBlock> blocks;

    private:
        CubeGrid(CubeGridParams parameters, BlocksVector<ICubeBlock> cubeblocks) : Parameters(parameters), blocks(cubeblocks) {}
        BlocksVector<ICubeBlock> CloneBlocks(BlocksVector<ICubeBlock> to_clone);

    public:
        CubeGrid(CubeGridParams parameters = CubeGridParams()) : entityId(std::make_shared<uint64_t>(0)), Parameters(parameters) {}
        ~CubeGrid() {}

        CubeGrid(const CubeGrid& cubegrid) : entityId(std::make_shared<uint64_t>(0)), Parameters(cubegrid.Parameters), blocks(CloneBlocks(cubegrid.blocks)) {}

        static void TranslateCoords(BlocksVector<ICubeBlock>* to_translate, int x, int y, int z);
        void TranslateCoords(int x, int y, int z);
        void AttachCubegrid(CubeGrid& cubegrid, int x = 0, int y = 0, int z = 0);
};

#endif // H_CUBEGRID

