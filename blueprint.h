#ifndef H_BLUEPRINT
#define H_BLUEPRINT

#include <iostream>
#include <string>
#include <stdexcept>
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_print.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include "cubegrid.h"

using namespace rapidxml;

class CubeGrid;

class Blueprint
{
    private:
        std::string blueprint_name;
        std::string author_name;
        uint64_t author_steam_id;

        uint64_t entity_counter;
        rapidxml::xml_document<>* doc;

    public:
        std::vector<CubeGrid> Cubegrids;

        Blueprint(std::string blueprint_name = "", std::string author_name = "", uint64_t author_steam_id = 0);
        ~Blueprint();

        void AssignEntityIds();
        void BuildXml();
        void Print(std::ostream& out, bool no_indenting);
        void MergeCubegrids();
};

#endif // H_BLUEPRINT

