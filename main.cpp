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
        CubeGridParams params;
        params.BlocksInheritGridSize = false;
        params.GridSize = SIZE_SMALL;
        //CubeGrid cb(params);
        unsigned cbg1 = Bp.Cubegrids.Add(params);
        params.Forward.x = 4;
        params.IsRespawnGrid = true;
        unsigned cbg2 = Bp.Cubegrids.Add(params);

        TimerBlock timer;
        timer.Coords.x = 5;
        timer.Coords.y = 4;
        timer.Coords.z = 2;
        Bp.Cubegrids[cbg1].AddBlock(&timer);
        timer.Coords.x = 4;
        timer.Coords.y = 4;
        timer.Coords.z = 2;
        Bp.Cubegrids[cbg1].AddBlock(&timer);
        std::cout<<"Saving output to file"<<std::endl;
        //Bp.Print(cout, false);

        fstream output("bp.sbc", std::fstream::out);
        if (output.is_open())
            Bp.Print(output, false);
        else cout<<"Error writing to file"<<endl;
    }
    catch (rapidxml::parse_error &e)
    {
        cout<<"rapidxml error! "<<e.what()<<endl;
    }
}
