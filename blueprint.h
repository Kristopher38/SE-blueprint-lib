#ifndef H_BLUEPRINT
#define H_BLUEPRINT

#include <iostream>
#include <string>
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_print.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include "cubegrids.h"

using namespace rapidxml;

class Blueprint
{
    private:
        rapidxml::xml_document<> doc;
        rapidxml::xml_node<>* shipblueprint_node;
        std::string blueprint_name;
        std::string player_name;
        uint64_t owner_steam_id;

    public:
        CubeGrids Cubegrids;

        Blueprint(std::string blueprint_name = "", std::string player_name = "", uint64_t owner_steam_id = 0);
        ~Blueprint();

        void Print(std::ostream& out, bool no_indenting);
};

#endif // H_BLUEPRINT

