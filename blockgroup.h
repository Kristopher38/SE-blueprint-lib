#ifndef H_BLOCKGROUP
#define H_BLOCKGROUP

#include <vector>
#include <string>
#include <rapidxml/rapidxml.hpp>
#include "cubeblock.h"

class BlockGroup
{
    private:
        struct Vector3I
        {
            int x;
            int y;
            int z;

            Vector3I() : x(0), y(0), z(0) {}
            Vector3I(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
        };
        std::vector<Vector3I> blocks;

    public:
        std::string name;

    void AddBlock(int x, int y, int z);
    void AddBlock(ICubeBlock& block);
    void AppendXml(rapidxml::xml_node<>* group);
};

#endif // H_BLOCKGROUP
