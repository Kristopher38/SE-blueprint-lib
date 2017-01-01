#ifndef H_TYPEDEFS
#define H_TYPEDEFS

enum BLOCK_SIZE {SIZE_SMALL = 0, SIZE_LARGE = 1};
enum ORIENTATION {ORIENT_FORWARD = 0, ORIENT_BACKWARD, ORIENT_UP, ORIENT_DOWN, ORIENT_LEFT, ORIENT_RIGHT};

struct CubeGridParams
{
    struct position
    {
        int x = 0;
        int y = 0;
        int z = 0;
    } Position, Forward, Up;

    struct orientation
    {
        int x = 0;
        int y = 0;
        int z = 0;
        int w = 0;
    } Orientation;

    BLOCK_SIZE GridSize = SIZE_LARGE;
    bool IsStatic = true;
    std::string DisplayName = "";
    bool DestructibleBlocks = true;
    bool IsRespawnGrid = false;
    int LocalCoordSys = 0;

    bool BlocksInheritGridSize = true;
};

#endif // H_TYPEDEFS

