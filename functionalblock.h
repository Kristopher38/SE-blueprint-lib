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
        Accessor<bool> Enabled = true;

        IFunctionalBlock();
        virtual ~IFunctionalBlock();

        inline virtual bool operator==(IFunctionalBlock& rhs)
        {
            return (ITerminalBlock::operator==(*dynamic_cast<ITerminalBlock*>(&rhs)) &&
                    this->Enabled == rhs.Enabled);
        }
        inline virtual bool operator!=(IFunctionalBlock& rhs)
        {
            return !(*this==rhs);
        }
};

#endif // H_FUNCTIONALBLOCK

