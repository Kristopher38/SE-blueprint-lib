#include "blueprint.h"

using namespace rapidxml;

Blueprint::Blueprint(std::string blueprint_name, std::string author_name, uint64_t author_steam_id) : blueprint_name(blueprint_name), author_name(author_name), author_steam_id(author_steam_id), entity_counter(0), doc(0) {}

Blueprint::~Blueprint()
{
    if (doc)
        delete doc;
}

void Blueprint::AssignEntityIds()
{
    for (std::size_t i = 0; i < Cubegrids.size(); ++i)
    {
        *Cubegrids[i].EntityId = entity_counter++;
        for (BlocksVector<ICubeBlock>::iterator b_it = Cubegrids[i].blocks.begin(); b_it != Cubegrids[i].blocks.end(); ++b_it)
        {
            ITerminalBlock* myTerminalBlock = dynamic_cast<ITerminalBlock*>(b_it->get());
            if (myTerminalBlock)
                *myTerminalBlock->EntityId = entity_counter++;
        }
    }
}

void Blueprint::BuildXml()
{
    if (!doc)
        doc = new rapidxml::xml_document<>;

    this->AssignEntityIds();

    rapidxml::xml_node<> *node;
    node = doc->allocate_node(node_declaration);
    node->append_attribute(doc->allocate_attribute("version", "1.0"));
    doc->append_node(node);

    node = doc->allocate_node(node_element, "Definitions");
    node->append_attribute(doc->allocate_attribute("xmlns:xsd", "http://www.w3.org/2001/XMLSchema"));
    node->append_attribute(doc->allocate_attribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance"));
    doc->append_node(node);

    node->append_node(doc->allocate_node(node_element, "ShipBlueprints"));
    node = node->first_node();

    node->append_node(doc->allocate_node(node_element, "ShipBlueprint"));
    node = node->first_node();
    node->append_attribute(doc->allocate_attribute("xsi:type", "MyObjectBuilder_ShipBlueprintDefinition"));

    node->append_node(doc->allocate_node(node_element, "Id"));
    node = node->first_node();
    node->append_attribute(doc->allocate_attribute("Type", "MyObjectBuilder_ShipBlueprintDefinition"));
    node->append_attribute(doc->allocate_attribute("Subtype", doc->allocate_string(blueprint_name.c_str())));
    node = node->parent();

    node->append_node(doc->allocate_node(node_element, "DisplayName", doc->allocate_string(author_name.c_str())));
    node->append_node(doc->allocate_node(node_element, "CubeGrids"));
    for (std::size_t i = 0; i < Cubegrids.size(); ++i)
        Cubegrids[i].AppendXml(node->last_node(), &entity_counter);
    node->append_node(doc->allocate_node(node_element, "WorkshopId", "0"));
    node->append_node(doc->allocate_node(node_element, "OwnerSteamId", doc->allocate_string(std::to_string(author_steam_id).c_str())));
    node->append_node(doc->allocate_node(node_element, "Points", "0"));
}

void Blueprint::Print(std::ostream& out, bool no_indenting)
{
    if (!doc)
        BuildXml();
    rapidxml::print(out, *doc, no_indenting ? print_no_indenting : 0);
}
