#ifndef H_BLOCKSVECTOR
#define H_BLOCKSVECTOR

#include <memory>
#include <vector>

template <typename T> using Block = std::shared_ptr<T>;
template <typename T> using BlocksVector = std::vector<Block<T>>;
template <typename T> using cb_vec = BlocksVector<T>;

template <class BlockT> class IBlocksVector : public cb_vec<BlockT>
{
public:
    template <typename T> T* AddBlock(const T& cubeblock)
    {
        cb_vec<BlockT>::push_back(cubeblock.clone());
        return dynamic_cast<T*>(cb_vec<BlockT>::back().get());
    }

    template <typename T> T* AddBlock(T* cubeblock)
    {
        if (cubeblock)
        {
            cb_vec<BlockT>::push_back(Block<T>(cubeblock));
            return dynamic_cast<T*>(cb_vec<BlockT>::back().get());
        } else return nullptr;
    }

    template <typename T> void RemoveBlocks(T& cubeblock)
    {
        std::size_t last_removed = 0;
        do {
            last_removed = this->RemoveBlock(cubeblock, last_removed);
        } while (last_removed < cb_vec<BlockT>::size());
    }

    template <typename T> std::size_t RemoveBlock(T& cubeblock, std::size_t offset = 0)
    {
        std::size_t index = offset;
        for (typename cb_vec<BlockT>::iterator it = cb_vec<BlockT>::begin()+offset; it != cb_vec<BlockT>::end(); ++it, ++index)
        {
            T* vectorblock = dynamic_cast<T*>(it->get());
            if (vectorblock)
                if (cubeblock == *vectorblock)
                {
                    cb_vec<BlockT>::erase(it);
                    return index;
                }
        }
        return cb_vec<BlockT>::size();
    }

    template <typename T> IBlocksVector<T> GetBlocks(T& cubeblock)
    {
        IBlocksVector<T> matching_blocks;
        for (typename cb_vec<BlockT>::iterator it = cb_vec<BlockT>::begin(); it != cb_vec<BlockT>::end(); ++it)
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

    template <typename T> IBlocksVector<T> GetBlocksWithName(std::string name)
    {
        T cubeblock;
        cubeblock.CustomName = name;
        return this->GetBlocks<T>(cubeblock);
    }

    template <typename T> T& GetBlockWithName(std::string name)
    {
        return *this->GetBlocksWithName<T>(name)[0].get();
    }

    template <typename T> IBlocksVector<T> GetBlocksWithCoords(int x, int y, int z)
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

    template <typename T> IBlocksVector<T> GetBlocksOfType()
    {
        T cubeblock;
        return this->GetBlocks<T>(cubeblock);
    }
};

#endif // H_BLOCKSVECTOR
