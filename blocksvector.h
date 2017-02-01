#ifndef H_BLOCKSVECTOR
#define H_BLOCKSVECTOR

#include <memory>
#include <vector>

template <typename T> using Blockptr = std::shared_ptr<T>;
template <typename T> using BlockptrVec = std::vector<Blockptr<T>>;

template <class BlockT> class BlocksVector : public BlockptrVec<BlockT>
{
public:
    template <typename T> T* AddBlock(const T& cubeblock)
    {
        BlockptrVec<BlockT>::push_back(cubeblock.clone());
        return dynamic_cast<T*>(BlockptrVec<BlockT>::back().get());
    }

    template <typename T> T* AddBlock(T* cubeblock)
    {
        if (cubeblock)
        {
            BlockptrVec<BlockT>::push_back(std::shared_ptr<BlockT>(cubeblock, [](BlockT*){})); // empty deleter to avoid deleting pointer when shared_ptr deletes - memory management relies on user with pointers
            return dynamic_cast<T*>(BlockptrVec<BlockT>::back().get());
        } else return nullptr;
    }

    template <typename T> void RemoveBlocks(T& cubeblock)
    {
        std::size_t last_removed = 0;
        do {
            last_removed = this->RemoveBlock(cubeblock, last_removed);
        } while (last_removed < BlockptrVec<BlockT>::size());
    }

    template <typename T> std::size_t RemoveBlock(T& cubeblock, std::size_t offset = 0)
    {
        std::size_t index = offset;
        for (typename BlockptrVec<BlockT>::iterator it = BlockptrVec<BlockT>::begin()+offset; it != BlockptrVec<BlockT>::end(); ++it, ++index)
        {
            T* vectorblock = dynamic_cast<T*>(it->get());
            if (vectorblock)
                if (cubeblock == *vectorblock)
                {
                    BlockptrVec<BlockT>::erase(it);
                    return index;
                }
        }
        return BlockptrVec<BlockT>::size();
    }

    template <typename T> BlocksVector<T> GetBlocks(T& cubeblock, std::size_t amount = 0)
    {
        BlocksVector<T> matching_blocks;
        if (amount)
            BlockptrVec<BlockT>::reserve(amount);
        for (typename BlockptrVec<BlockT>::iterator it = BlockptrVec<BlockT>::begin(); it != BlockptrVec<BlockT>::end(); ++it)
        {
            T* vectorblock = dynamic_cast<T*>(it->get());
            if (vectorblock)
                if (cubeblock == *vectorblock)
                {
                    matching_blocks.push_back(std::dynamic_pointer_cast<T>(*it));
                    if (amount && matching_blocks.size() == amount)
                        break;
                }
        }
        if (!matching_blocks.size())
            throw std::logic_error("No block with specified search pattern was found");
        return matching_blocks;
    }

    template <typename T> T& GetBlock(T& cubeblock)
    {
        return dynamic_cast<T&>(*this->GetBlocks<T>(cubeblock, 1)[0].get());
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
};

#endif // H_BLOCKSVECTOR
