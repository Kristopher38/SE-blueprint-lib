#ifndef H_CUBEGRID
#define H_CUBEGRID

#include <string>
#include <stdexcept>
#include <rapidxml/rapidxml.hpp>
#include "cubeblock.h"
#include "terminalblock.h"
#include "typedefs.h"

using namespace rapidxml;

class CubeGrid
{
    private:
        uint64_t* entity_counter_ptr;
        bool local_entity_counter;
        rapidxml::xml_node<>* cubegrid_node;
        bool size_inheritance;
        BLOCK_SIZE grid_size;

        rapidxml::xml_node<>* FindBlock(int x, int y, int z);

    public:
        CubeGrid();
        CubeGrid(uint64_t* entity_counter, rapidxml::xml_node<>* cubegrid_node, bool size_inheritance, BLOCK_SIZE grid_size);
        ~CubeGrid();

        void AddBlock(ICubeBlock* cubeblock);

        void RemoveBlock(int x, int y, int z);

        void Remove();
};

#endif // H_CUBEGRID

