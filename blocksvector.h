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

    template <typename T> T* AddBlock(T* const cubeblock)
    {
        if (cubeblock)
        {
            BlockptrVec<BlockT>::push_back(std::shared_ptr<BlockT>(cubeblock, [](BlockT*){})); // empty deleter to avoid deleting pointer when shared_ptr deletes - memory management relies on user with pointers
            return dynamic_cast<T*>(BlockptrVec<BlockT>::back().get());
        } else return nullptr;
    }

    template <typename T> std::size_t RemoveBlocks(T& cubeblock, bool remove_all = true, std::size_t offset = 0)
    {
        std::size_t removed_count = 0;
        for (typename BlockptrVec<BlockT>::iterator it = BlockptrVec<BlockT>::begin()+offset; it != BlockptrVec<BlockT>::end(); ++it)
        {
            T* vectorblock = dynamic_cast<T*>(it->get());
            if (vectorblock)
            {
                if (cubeblock == *vectorblock)
                {
                    BlockptrVec<BlockT>::erase(it);
                    removed_count++;
                    if (!remove_all)
                        break;
                }
            }
        }
        return removed_count;
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
            {
                if (cubeblock == *vectorblock)
                {
                    matching_blocks.push_back(std::dynamic_pointer_cast<T>(*it));
                    if (amount && matching_blocks.size() == amount)
                        break;
                }
            }
        }
        return matching_blocks;
    }

    template <typename T> BlocksVector<T> GetBlocks(std::string name)
    {
        T cubeblock;
        cubeblock.CustomName = name;
        return this->GetBlocks<T>(cubeblock);
    }

    template <typename T> BlocksVector<T> GetBlocks(int x, int y, int z)
    {
        T cubeblock;
        cubeblock.Coords.x = x;
        cubeblock.Coords.y = y;
        cubeblock.Coords.z = z;
        return this->GetBlocks<T>(cubeblock);
    }

    template <typename T> BlocksVector<T> GetBlocks()
    {
        T cubeblock;
        return this->GetBlocks<T>(cubeblock);
    }
};

#endif // H_BLOCKSVECTOR
