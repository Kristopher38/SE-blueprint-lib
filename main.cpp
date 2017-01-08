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
        timer.ColorMaskHSV.Hue = 1.0f;
        timer.CustomName = "Timer Block";
        Bp.Cubegrids[0].blocks.AddBlock(timer);
        timer.Coords.x = 6;
        timer.Coords.y = 2;
        timer.Coords.z = 9;
        timer.CustomName = "Timer Block";
        Bp.Cubegrids[0].blocks.AddBlock(timer);
        timer.Coords.x = 6;
        timer.Coords.y = 1;
        timer.Coords.z = 3;
        timer.Delay = 1234;
        Bp.Cubegrids[0].blocks.AddBlock(timer);
        timer = TimerBlock();
        timer.Coords.x = 78;
        timer.Coords.y = 8;
        timer.Coords.z = 46;
        Bp.Cubegrids[0].blocks.AddBlock(timer);
        TimerBlock* timerptr = Bp.Cubegrids[0].blocks.AddBlock(timer);

        Bp.Cubegrids[0].blocks.GetBlock(timer).Toolbar.AddEntry(0, "OnOff_On", timerptr);
        TimerBlock timer2;
        timer2.Coords.x = 6;
        timer2.Coords.y = 2;
        timer2.Coords.z = 9;

        //Bp.Cubegrids[0].blocks.GetBlock(timer);
        //Bp.Cubegrids[0].blocks.GetBlock(timer);
        //Bp.Cubegrids[0].blocks.GetBlock(timer2);
        Bp.Cubegrids[0].blocks.GetBlock(timer).Toolbar.AddEntry(1, "OnOff", &Bp.Cubegrids[0].blocks.GetBlock(timer2));

        Bp.Cubegrids[0].blocks.GetBlock(timer).Delay = 4321;
        timer2.Coords.x = 27;
        timer2.Coords.y = 23;
        timer2.Coords.z = 12;
        Bp.Cubegrids[0].blocks.AddBlock(timer2);

        TimerBlock timertemplate;
        timertemplate.Coords.x = 6;
        timertemplate.Coords.y = 2;
        timertemplate.Coords.z = 9;
        timertemplate = TimerBlock();
        Bp.Cubegrids[0].blocks.GetBlockWithName<TimerBlock>("Timer Block").Coords.z = 10;
        Bp.Cubegrids[0].blocks.GetBlockWithCoords<TimerBlock>(78, 8, 46).Delay = 23542423;
        Bp.Cubegrids[0].blocks.GetBlocksWithCoords<TimerBlock>(78, 8, 46)[1]->Delay = 9999;

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
