#ifndef H_TYPEDEFS
#define H_TYPEDEFS

#include <iostream>

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
    bool CheckForDuplicateCoords = true;
};

template <typename T> class Accessor
{
    private:
        T value;
        T defaultValue;
        bool isdefault;

    public:
        T& operator=(T arg)
        {
            this->value = arg;
            this->isdefault = false;
            return this->value;
        }
        T& operator()()
        {
            this->isdefault = false;
            return this->value;
        }
        T& operator()(T arg)
        {
            this->isdefault = false;
            this->value = arg;
            return this->value;
        }
        T* getptr()
        {
            return &this->value;
        }
        inline bool operator< (const Accessor& rhs) const { return this->value < rhs.value; }
        inline bool operator> (const Accessor& rhs) const { return this->value > rhs.value; }
        inline bool operator<=(const Accessor& rhs) const { return this->value <= rhs.value; }
        inline bool operator>=(const Accessor& rhs) const { return this->value >= rhs.value; }
        inline bool operator==(const Accessor& rhs) const { return this->value == rhs.value || isdefault; }
        inline bool operator!=(const Accessor& rhs) const { return !(this->value == rhs.value); }

        //inline Accessor& operator+(const Accessor& rhs) {this->value += rhs; return *this;}
        inline Accessor& operator+=(const Accessor& rhs) {this->value += rhs.value; return *this;}

        Accessor() : isdefault(true) {}
        Accessor(T val) : value(val), defaultValue(val), isdefault(true) {}

        bool isDefault()
        {
            return isdefault;
        }

        T& reset()
        {
            this->value = defaultValue;
            this->isdefault = true;
            return this->value;
        }
};

#endif // H_TYPEDEFS

