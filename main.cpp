#include <iostream>
#include <fstream>

#include "blueprint.h"
#include "blocks.h"

using namespace std;
using namespace rapidxml;

const uint64_t myPlayerId = 144115188075855875;
const uint64_t mySteamId = 76561198040660483;

int main()
{
    try
    {
        Blueprint Bp("Orientation testing", "Kristopher38", mySteamId);
        CubeGrid waffle;
        waffle.Parameters.BlocksInheritGridSize = true;
        waffle.Parameters.GridSize = SIZE_LARGE;
        waffle.Parameters.DisplayName = "waffle no. 1";
        waffle.Parameters.IsStatic = true;
        ArmorBlock cube;
        for (unsigned i = 0; i < 2; i++)
        {
            cube.Coords.x = 0;
            cube.Coords.y = 0;
            cube.Coords.z = i;
            waffle.blocks.AddBlock(cube);
            cube.Coords.x = 1;
            cube.Coords.y = 0;
            waffle.blocks.AddBlock(cube);
            cube.Coords.x = 2;
            cube.Coords.y = 0;
            waffle.blocks.AddBlock(cube);
            cube.Coords.x = 0;
            cube.Coords.y = -1;
            waffle.blocks.AddBlock(cube);
            cube.Coords.x = 1;
            cube.Coords.y = -1;
            waffle.blocks.AddBlock(cube);
            cube.Coords.x = 0;
            cube.Coords.y = -2;
            waffle.blocks.AddBlock(cube);
        }
        Bp.Cubegrids.push_back(waffle);

        CubeGrid crumb;
        for (unsigned i = 0; i < 2; i++)
        {
            cube.Coords.x = 0;
            cube.Coords.y = 0;
            cube.Coords.z = i;
            crumb.blocks.AddBlock(cube);
            cube.Coords.x = 1;
            cube.Coords.y = 0;
            crumb.blocks.AddBlock(cube);
            cube.Coords.x = 1;
            cube.Coords.y = 1;
            crumb.blocks.AddBlock(cube);
        }
        crumb.TranslateCoords(1, -2, 1);
        Bp.Cubegrids.back().AttachCubegrid(crumb);

        fstream output("bp.sbc", std::fstream::out);
        if (output.is_open())
            Bp.Print(output, false);
        else cout<<"Error writing to file"<<endl;
    }
    catch (rapidxml::parse_error &e)
    {
        cout<<"rapidxml exception: "<<e.what()<<endl;
    }
}
