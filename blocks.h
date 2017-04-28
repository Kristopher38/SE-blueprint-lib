#ifndef H_BLOCKS
#define H_BLOCKS

#include <string>
#include "cubeblock.h"
#include "terminalblock.h"
#include "functionalblock.h"
#include "blocktoolbar.h"

class ArmorBlock : public ICubeBlock
{
    public:
        ArmorBlock() {}
        virtual ~ArmorBlock() {}

        std::string ObjectBuilder() override {return "CubeBlock";}
        std::string SubtypeName() override {return (this->Size() ? "LargeBlockArmorBlock" : "SmallBlockArmorBlock");}

        inline virtual std::shared_ptr<ICubeBlock> clone() const
        {
            return std::make_shared<ArmorBlock>(*this);
        }

        inline bool operator==(ArmorBlock& rhs)
        {
            return ICubeBlock::operator==(*dynamic_cast<IFunctionalBlock*>(&rhs));
        }
        inline bool operator!=(ArmorBlock& rhs)
        {
            return !(*this==rhs);
        }
};

class Door : public IFunctionalBlock
{
    protected:
        virtual void AppendAttributes(rapidxml::xml_node<>* block)
        {
            IFunctionalBlock::AppendAttributes(block);
            rapidxml::xml_document<>* doc = block->document();
            block->append_node(doc->allocate_node(node_element, "OpenSound", doc->allocate_string(OpenSound.c_str())));
            block->append_node(doc->allocate_node(node_element, "CloseSound", doc->allocate_string(CloseSound.c_str())));
        }

    public:
        std::string OpenSound = "ArcBlockDoorSmallOpen";
        std::string CloseSound = "ArcBlockDoorSmallClose";

        Door() {}
        virtual ~Door() {}

        inline virtual std::shared_ptr<ICubeBlock> clone() const
        {
            return std::make_shared<Door>(*this);
        }
        inline virtual std::string ObjectBuilder() override {return "Door";}
        inline virtual std::string SubtypeName() override {return std::string();}
};

class TimerBlock : public IFunctionalBlock, public Toolbar
{
    protected:
        virtual void AppendAttributes(rapidxml::xml_node<>* block)
        {
            IFunctionalBlock::AppendAttributes(block);
            toolbar.AppendAttributes(block);
            rapidxml::xml_document<>* doc = block->document();
            block->append_node(doc->allocate_node(node_element, "Delay", doc->allocate_string(std::to_string(Delay()).c_str())));
            block->append_node(doc->allocate_node(node_element, "CurrentTime", doc->allocate_string(std::to_string(CurrentTime()).c_str())));
            block->append_node(block->document()->allocate_node(node_element, "IsCountingDown", IsCountingDown() ? "true" : "false"));
            block->append_node(block->document()->allocate_node(node_element, "Silent", Silent() ? "true" : "false"));
        }

    public:
        Accessor<unsigned> Delay = 10000;
        Accessor<unsigned> CurrentTime = 0;
        Accessor<bool> IsCountingDown = false;
        Accessor<bool> Silent = false;

        TimerBlock() {}
        virtual ~TimerBlock() {}

        inline virtual std::string ObjectBuilder() override {return "TimerBlock";}
        inline virtual std::string SubtypeName() override {return (this->Size() ? "TimerBlockLarge" : "TimerBlockSmall");}

        inline virtual std::shared_ptr<ICubeBlock> clone() const
        {
            return std::make_shared<TimerBlock>(*this);
        }

        inline bool operator==(TimerBlock& rhs)
        {
            return (IFunctionalBlock::operator==(*dynamic_cast<IFunctionalBlock*>(&rhs)) &&
                    this->Delay == rhs.Delay &&
                    this->CurrentTime == rhs.CurrentTime &&
                    this->IsCountingDown == rhs.IsCountingDown &&
                    this->Silent == rhs.Silent);
        }
        inline bool operator!=(TimerBlock& rhs)
        {
            return !(*this==rhs);
        }
};

class ArmorBlockCornerInv : public ICubeBlock
{
    public:
        ArmorBlockCornerInv() {}
        virtual ~ArmorBlockCornerInv() {}

        std::string ObjectBuilder() override {return "CubeBlock";}
        std::string SubtypeName() override {return (this->Size() ? "LargeHeavyBlockArmorCornerInv" : "SmallHeavyBlockArmorCornerInv");}
};

#endif // H_BLOCKS
