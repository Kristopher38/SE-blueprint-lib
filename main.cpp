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
        CubeGrid cb(params);
        Bp.Cubegrids.push_back(cb);
        params.Forward.x = 4;
        params.IsRespawnGrid = true;
        cb = CubeGrid(params);
        Bp.Cubegrids.push_back(cb);

        TimerBlock timer;
        timer.Coords.x = 5;
        timer.Coords.y = 4;
        timer.Coords.z = 2;
        timer.ShowOnHUD = false;
        Bp.Cubegrids[0].blocks.Add<TimerBlock>(&timer);
        timer = TimerBlock();
        timer.Coords.x = 4;
        timer.Coords.y = 4;
        timer.Coords.z = 2;
        timer.Delay = 3424;
        Bp.Cubegrids[1].blocks.Add<TimerBlock>(&timer);
        timer = TimerBlock();
        timer.Coords.x = 2;
        timer.Coords.y = 3;
        timer.Coords.z = 3;
        timer.Enabled = false;
        Bp.Cubegrids[0].blocks.Add<TimerBlock>(&timer);
        Bp.Cubegrids[1].blocks.Add<TimerBlock>(&timer);

        Bp.Cubegrids.push_back(Bp.Cubegrids[0]);
        Bp.Cubegrids[2].blocks[0].get()->Coords.x = 1;
        std::cout<<"Saving output to file"<<std::endl;
        //Bp.Print(cout, false);

        fstream output("bp.sbc", std::fstream::out);
        if (output.is_open())
        {
            //Bp.BuildXml();
            Bp.Print(output, false);
        }

        else cout<<"Error writing to file"<<endl;
    }
    catch (rapidxml::parse_error &e)
    {
        cout<<"rapidxml error! "<<e.what()<<endl;
    }
}
