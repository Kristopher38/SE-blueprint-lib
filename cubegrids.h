#ifndef H_CUBEGRIDS
#define H_CUBEGRIDS

#include <string>
#include <vector>
#include <rapidxml/rapidxml.hpp>
#include "cubegrid.h"
#include "typedefs.h"

using namespace rapidxml;

struct CubeGridParams
{
    struct position
    {
        int x = 0;
        int y = 0;
        int z = 0;
    } Position, Forward, Up;

    struct orientation
    {
        int x = 0;
        int y = 0;
        int z = 0;
        int w = 0;
    } Orientation;

    BLOCK_SIZE GridSize = SIZE_LARGE;
    bool IsStatic = true;
    std::string DisplayName = "";
    bool DestructibleBlocks = true;
    bool IsRespawnGrid = false;
    int LocalCoordSys = 0;

    bool BlocksInheritGridSize = true;
};

class CubeGrids
{
    private:
        rapidxml::xml_node<>* node_cubegrids;
        std::vector<CubeGrid> cubegrids;
        uint64_t entity_counter;
    public:
        CubeGrids();
        CubeGrids(rapidxml::xml_node<>* node_cubegrids);
        ~CubeGrids();

        CubeGrid& operator[](std::size_t idx);
        std::size_t Add();
        std::size_t Add(CubeGridParams parameters);
        void Remove(std::size_t index);
};

#endif // H_CUBEGRIDS
