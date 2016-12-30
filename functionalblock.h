#ifndef H_FUNCTIONALBLOCK
#define H_FUNCTIONALBLOCK

#include <rapidxml/rapidxml.hpp>
#include "terminalblock.h"

using namespace rapidxml;

class IFunctionalBlock : public ITerminalBlock // can be turned on or off
{
    protected:
        virtual void AppendAttributes(rapidxml::xml_node<>* block);

    public:
        bool Enabled;

        IFunctionalBlock();
        virtual ~IFunctionalBlock();
};

#endif // H_FUNCTIONALBLOCK

