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
#include <map>
#include "cubeblock.h"
#include "terminalblock.h"
#include "typedefs.h"
#include "blocksvector.h"
#include "blocktoolbar.h"
#include "blocks.h"

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
        BlocksVector<ICubeBlock> CloneBlocks(const BlocksVector<ICubeBlock>& to_clone);

    public:
        CubeGrid(CubeGridParams parameters = CubeGridParams()) : entityId(std::make_shared<uint64_t>(0)), Parameters(parameters) {}
        ~CubeGrid() {}

        CubeGrid(const CubeGrid& cubegrid) : entityId(std::make_shared<uint64_t>(0)), Parameters(cubegrid.Parameters), blocks(CloneBlocks(cubegrid.blocks)) {}
        CubeGrid(CubeGrid&& cubegrid) noexcept : entityId(std::move(cubegrid.entityId)), Parameters(cubegrid.Parameters), blocks(std::move(cubegrid.blocks)) {}

        static void TranslateCoords(BlocksVector<ICubeBlock>* to_translate, int x, int y, int z);
        void TranslateCoords(int x, int y, int z);
        void AttachCubegrid(CubeGrid& cubegrid, int x = 0, int y = 0, int z = 0);

        void DebugPrint(unsigned indent);
        std::string PrintIndent(unsigned indent);
};

#endif // H_CUBEGRID

