#ifndef H_CUBEBLOCK
#define H_CUBEBLOCK

#include <string>
#include <memory>
#include <rapidxml/rapidxml.hpp>
#include "typedefs.h"

using namespace rapidxml;

class ICubeBlock // basic class for all cubes
{
    friend class CubeGrid;

    private:
        static const char* OrientationStrLookup[6];

    protected:
        virtual void AppendAttributes(rapidxml::xml_node<>* cubeblocks_node);

    public:
        struct
        {
            Accessor<int> x = 0;
            Accessor<int> y = 0;
            Accessor<int> z = 0;
        } Coords;
        struct
        {
            Accessor<float> Hue = 0.0f;
            Accessor<float> Saturation = -1.0f;
            Accessor<float> Value = 0.0f;
        } ColorMaskHSV;
        struct
        {
            Accessor<ORIENTATION> Forward = ORIENT_FORWARD;
            Accessor<ORIENTATION> Up = ORIENT_UP;
        } BlockOrientation;
        Accessor<uint64_t> BuiltBy = 0;
        Accessor<BLOCK_SIZE> Size = SIZE_LARGE;

        ICubeBlock();
        virtual ~ICubeBlock();

        virtual std::string ObjectBuilder() = 0;
        virtual std::string SubtypeName() = 0;
        virtual std::shared_ptr<ICubeBlock> clone() const = 0;

        virtual bool operator==(ICubeBlock& rhs)
        {
            return (this->Coords.x == rhs.Coords.x &&
                    this->Coords.y == rhs.Coords.y &&
                    this->Coords.z == rhs.Coords.z &&
                    this->ColorMaskHSV.Hue == rhs.ColorMaskHSV.Hue &&
                    this->ColorMaskHSV.Saturation == rhs.ColorMaskHSV.Saturation &&
                    this->ColorMaskHSV.Value == rhs.ColorMaskHSV.Value &&
                    this->BlockOrientation.Forward == rhs.BlockOrientation.Forward &&
                    this->BlockOrientation.Up == rhs.BlockOrientation.Up &&
                    this->BuiltBy == rhs.BuiltBy &&
                    this->Size == rhs.Size);
        }
        virtual bool operator!=(ICubeBlock& rhs)
        {
            return !(*this==rhs);
        }
};



#endif // H_CUBEBLOCK
