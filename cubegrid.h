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
        template <typename T> using Block = std::shared_ptr<T>;
        template <typename T> using BlocksVector = std::vector<Block<T>>;
        typedef BlocksVector<ICubeBlock> cubeblocks_vector;

        CubeGridParams Parameters;

        class IBlocksVector : public cubeblocks_vector
        {
            public:
                template <typename T> T* AddBlock(const T& cubeblock)
                {
                    cubeblocks_vector::push_back(cubeblock.clone());
                    return dynamic_cast<T*>(cubeblocks_vector::back().get());
                }

                template <typename T> T* AddBlock(T* cubeblock)
                {
                    if (cubeblock)
                    {
                        cubeblocks_vector::push_back(Block<T>(cubeblock));
                        return dynamic_cast<T*>(cubeblocks_vector::back().get());
                    } else return nullptr;
                }

                template <typename T> void RemoveBlocks(T& cubeblock)
                {
                    std::size_t last_removed = 0;
                    do {
                        last_removed = this->RemoveBlock(cubeblock, last_removed);
                    } while (last_removed < cubeblocks_vector::size());
                }

                template <typename T> std::size_t RemoveBlock(T& cubeblock, std::size_t offset = 0)
                {
                    std::size_t index = offset;
                    for (cubeblocks_vector::iterator it = cubeblocks_vector::begin()+offset; it != cubeblocks_vector::end(); ++it, ++index)
                    {
                        T* vectorblock = dynamic_cast<T*>(it->get());
                        if (vectorblock)
                            if (cubeblock == *vectorblock)
                            {
                                cubeblocks_vector::erase(it);
                                return index;
                            }
                    }
                    return cubeblocks_vector::size();
                }

                template <typename T> BlocksVector<T> GetBlocks(T& cubeblock)
                {
                    BlocksVector<T> matching_blocks;
                    for (cubeblocks_vector::iterator it = cubeblocks_vector::begin(); it != cubeblocks_vector::end(); ++it)
                    {
                        T* vectorblock = dynamic_cast<T*>(it->get());
                        if (vectorblock)
                            if (cubeblock == *vectorblock)
                                matching_blocks.push_back(std::dynamic_pointer_cast<T>(*it));
                    }
                    if (!matching_blocks.size())
                        throw std::logic_error("No block with specified search pattern was found");
                    return matching_blocks;
                }

                template <typename T> T& GetBlock(T& cubeblock)
                {
                    return dynamic_cast<T&>(*this->GetBlocks<T>(cubeblock)[0].get());
                }

                template <typename T> BlocksVector<T> GetBlocksWithName(std::string name)
                {
                    T cubeblock;
                    cubeblock.CustomName = name;
                    return this->GetBlocks<T>(cubeblock);
                }

                template <typename T> T& GetBlockWithName(std::string name)
                {
                    return *this->GetBlocksWithName<T>(name)[0].get();
                }

                template <typename T> BlocksVector<T> GetBlocksWithCoords(int x, int y, int z)
                {
                    T cubeblock;
                    cubeblock.Coords.x = x;
                    cubeblock.Coords.y = y;
                    cubeblock.Coords.z = z;
                    return this->GetBlocks<T>(cubeblock);
                }

                template <typename T> T& GetBlockWithCoords(int x, int y, int z)
                {
                    return *this->GetBlocksWithCoords<T>(x, y, z)[0].get();
                }

                template <typename T> BlocksVector<T> GetBlocksOfType()
                {
                    T cubeblock;
                    return this->GetBlocks<T>(cubeblock);
                }
        } blocks;

    private:
        CubeGrid(CubeGridParams parameters, IBlocksVector cubeblocks) : Parameters(parameters), blocks(cubeblocks) {}
        IBlocksVector CloneBlocks(IBlocksVector to_clone)
        {
            auto cloner = [](const Block<ICubeBlock>& ptr) -> Block<ICubeBlock>
                {return ptr->clone();};

            IBlocksVector cloned;
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

