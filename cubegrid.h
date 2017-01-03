#ifndef H_CUBEGRID
#define H_CUBEGRID

#include <string>
#include <stdexcept>
#include <vector>
#include <memory>
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
                template <typename T> void Add (ICubeBlock* cubeblock)
                {
                    T* cb = dynamic_cast<T*>(cubeblock);
                    std::vector<std::shared_ptr<ICubeBlock>>::push_back(std::make_shared<T>(*cb));
                }
        } blocks;

        CubeGrid(CubeGridParams parameters = CubeGridParams());
        ~CubeGrid();

        std::size_t FindBlock(int x, int y, int z);
};

#endif // H_CUBEGRID

