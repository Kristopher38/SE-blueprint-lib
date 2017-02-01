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
    Blueprint bp("Delay test", "Kristopher38");
    CubeGrid cb;
    bp.Cubegrids.push_back(cb);


    TimerBlock endTimer;
    endTimer.Coords.x = -1;
    endTimer.Coords.z = 0;
    endTimer.Coords.y = 0;
    endTimer.CustomName = "Timer Block End";
    bp.Cubegrids[0].blocks.AddBlock(endTimer);

    TimerBlock* prevTimer = dynamic_cast<TimerBlock*>(bp.Cubegrids[0].blocks.back().get());
    for (int i = 99; i >= 0; i--)
        for (int j = 100; j >= 0; j--)
        {
            TimerBlock timer;
            ArmorBlock armor;

            timer.Coords.x = j;
            timer.Coords.y = i;
            timer.CustomName = std::string("Timer Block ") + std::to_string((i*100) + j);
            timer.Toolbar.AddEntry(0, "OnOff_On", prevTimer);
            timer.Toolbar.AddEntry(1, "TriggerNow", prevTimer);
            armor.Coords.x = i;
            armor.Coords.y = -1;
            prevTimer = bp.Cubegrids[0].blocks.AddBlock(timer);
            bp.Cubegrids[0].blocks.AddBlock(armor);
        }
    bp.Cubegrids[0].blocks.GetBlock(endTimer).Toolbar.AddEntry(0, "OnOff_Off", prevTimer);

    bp.BuildXml();

    fstream output("bp.sbc", std::fstream::out);
    if (output.is_open())
        bp.Print(output, false);
    else cout<<"Error writing to file"<<endl;
}
