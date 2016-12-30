#ifndef H_CUBEBLOCK
#define H_CUBEBLOCK

#include <string>
#include <rapidxml/rapidxml.hpp>
#include "typedefs.h"

using namespace rapidxml;

class ICubeBlock // basic class for all cubes
{
    friend class CubeGrid;

    private:
        static const char* OrientationStrLookup[6];

    protected:
        virtual void AppendAttributes(rapidxml::xml_node<>* block);

    public:
        struct
        {
            int x = 0;
            int y = 0;
            int z = 0;
        } Coords;
        struct
        {
            float Hue = 0.0f;
            float Saturation = -1.0f;
            float Value = 0.0f;
        } ColorMaskHSV;
        struct
        {
            ORIENTATION Forward = ORIENT_FORWARD;
            ORIENTATION Up = ORIENT_UP;
        } BlockOrientation;
        uint64_t BuiltBy = 0;
        BLOCK_SIZE Size = SIZE_LARGE;

        ICubeBlock();
        virtual ~ICubeBlock();

        virtual std::string ObjectBuilder() = 0;
        virtual std::string SubtypeName() = 0;
};



#endif // H_CUBEBLOCK
