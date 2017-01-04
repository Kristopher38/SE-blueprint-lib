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
        Bp.Cubegrids.push_back(CubeGrid());
        TimerBlock timer;
        timer.Coords.x = 5;
        timer.Coords.y = 3;
        timer.Coords.z = 7;
        Bp.Cubegrids[0].blocks.Add(&timer);
        timer.Coords.x = 6;
        timer.Coords.y = 2;
        timer.Coords.z = 9;
        Bp.Cubegrids[0].blocks.Add(timer);
        timer.Coords.x = 5;
        timer.Coords.y = 1;
        timer.Coords.z = 3;
        Bp.Cubegrids[0].blocks.Add(timer);
        Bp.Cubegrids[0].blocks.GetBlock<TimerBlock>(timer).Coords.x = 1;



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
