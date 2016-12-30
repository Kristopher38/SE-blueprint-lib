#include "blueprint.h"

using namespace rapidxml;

Blueprint::Blueprint(std::string blueprint_name, std::string player_name, uint64_t owner_steam_id)
{
    rapidxml::xml_node<> *node;

    node = doc.allocate_node(node_declaration);
    node->append_attribute(doc.allocate_attribute("version", "1.0"));
    doc.append_node(node);

    node = doc.allocate_node(node_element, "Definitions");
    node->append_attribute(doc.allocate_attribute("xmlns:xsd", "http://www.w3.org/2001/XMLSchema"));
    node->append_attribute(doc.allocate_attribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance"));
    doc.append_node(node);

    node->append_node(doc.allocate_node(node_element, "ShipBlueprints"));
    node = node->first_node();

    node->append_node(doc.allocate_node(node_element, "ShipBlueprint"));
    node = node->first_node();
    node->append_attribute(doc.allocate_attribute("xsi:type", "MyObjectBuilder_ShipBlueprintDefinition"));
    shipblueprint_node = node;

    node->append_node(doc.allocate_node(node_element, "Id"));
    node = node->first_node();
    node->append_attribute(doc.allocate_attribute("Type", "MyObjectBuilder_ShipBlueprintDefinition"));
    node->append_attribute(doc.allocate_attribute("Subtype", doc.allocate_string(blueprint_name.c_str())));
    node = node->parent();

    node->append_node(doc.allocate_node(node_element, "DisplayName", doc.allocate_string(player_name.c_str())));
    node->append_node(doc.allocate_node(node_element, "CubeGrids"));
    Cubegrids = CubeGrids(node->last_node());
    node->append_node(doc.allocate_node(node_element, "WorkshopId", "0"));
    node->append_node(doc.allocate_node(node_element, "OwnerSteamId", doc.allocate_string(std::to_string(owner_steam_id).c_str())));
    node->append_node(doc.allocate_node(node_element, "Points", "0"));
}

Blueprint::~Blueprint() {}

void Blueprint::Print(std::ostream& out, bool no_indenting)
{
    rapidxml::print(out, doc, no_indenting ? print_no_indenting : 0);
}
