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

using namespace rapidxml;

class CubeGrid
{
    friend class Blueprint;
    private:
        void AppendXml(rapidxml::xml_node<>* cubegrids_node, uint64_t* entity_counter);

    public:
        CubeGridParams Parameters;
        class CubeBlocks : public std::vector<std::shared_ptr<ICubeBlock>>
        {
            public:
                void Add(const ICubeBlock& cubeblock)
                {
                    std::vector<std::shared_ptr<ICubeBlock>>::push_back(cubeblock.clone());
                }
                template <typename T> void Add(T* cubeblock)
                {
                    if (cubeblock)
                        std::vector<std::shared_ptr<ICubeBlock>>::push_back(std::shared_ptr<T>(cubeblock));
                }
                template <typename T> T& GetBlock(T& cubeblock)
                {
                    for (std::size_t i = 0; i < std::vector<std::shared_ptr<ICubeBlock>>::size(); ++i)
                    {
                        if (cubeblock.Coords.x != std::vector<std::shared_ptr<ICubeBlock>>::at(i).get()->Coords.x)
                            continue;
                        if (cubeblock.Coords.y != std::vector<std::shared_ptr<ICubeBlock>>::at(i).get()->Coords.y)
                            continue;
                        if (cubeblock.Coords.z != std::vector<std::shared_ptr<ICubeBlock>>::at(i).get()->Coords.z)
                            continue;
                        return dynamic_cast<T&>(*std::vector<std::shared_ptr<ICubeBlock>>::at(i).get());
                    }
                    return cubeblock;
                }
        } blocks;

    private:
        CubeGrid(CubeGridParams parameters, CubeBlocks cubeblocks) : Parameters(parameters), blocks(cubeblocks) {}
        CubeBlocks CloneBlocks(CubeBlocks to_clone)
        {
            auto cloner = [](const std::shared_ptr<ICubeBlock>& ptr) -> std::shared_ptr<ICubeBlock>
                {return ptr->clone();};

            CubeBlocks cloned;
            std::transform(to_clone.begin(), to_clone.end(), std::back_inserter(cloned), cloner);
            return cloned;
        }

    public:
        CubeGrid(CubeGridParams parameters = CubeGridParams()) : Parameters(parameters) {}
        ~CubeGrid() {}

        CubeGrid(const CubeGrid& cubegrid) : Parameters(cubegrid.Parameters), blocks(CloneBlocks(cubegrid.blocks)) {std::cout<<"Calling copy ctor"<<std::endl;}

        std::size_t FindBlock(int x, int y, int z);
};

#endif // H_CUBEGRID

