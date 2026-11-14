#pragma once

#include "building/building_type.h"
#include "core/archive.h"
#include "core/svector.h"
#include "core/xstring.h"
#include "game/resource.h"

class building;

struct construction_warning_requirement {
    e_building_type building;
    e_building_type needs;
    xstring warning;
};
ANK_CONFIG_STRUCT(construction_warning_requirement, building, needs, warning)

struct construction_warning_stock {
    e_building_type building;
    e_resource resource;
    xstring warning;
};
ANK_CONFIG_STRUCT(construction_warning_stock, building, resource, warning)

struct construction_warning_road_area {
    e_building_type building;
    int size;
};
ANK_CONFIG_STRUCT(construction_warning_road_area, building, size)

struct construction_warning_school {
    e_building_type building;
    e_building_type school;
    xstring warning;
};
ANK_CONFIG_STRUCT(construction_warning_school, building, school, warning)

struct construction_warning_material {
    svector<e_building_type, 8> buildings;
    e_resource industry;
    e_resource stock;
    e_resource product;
    xstring warning;
    e_resource produce;
    xstring build;
    e_resource import_res;
    xstring no_route;
    xstring not_imported;
};
ANK_CONFIG_STRUCT(construction_warning_material, buildings, industry, stock, product, warning, produce, build,
  import_res, no_route, not_imported)

struct construction_warning_input {
    e_resource industry;
    e_resource stock;
    xstring warning;
    e_resource produce;
    xstring build;
    e_resource import_res;
    xstring no_route;
    xstring not_imported;
    xstring both_no_route;
    xstring both_not_imported;
};
ANK_CONFIG_STRUCT(construction_warning_input, industry, stock, warning, produce, build, import_res, no_route,
  not_imported, both_no_route, both_not_imported)

struct construction_warning_two_inputs {
    svector<e_building_type, 8> buildings;
    e_resource product;
    xstring warning;
    construction_warning_input first;
    construction_warning_input second;
};
ANK_CONFIG_STRUCT(construction_warning_two_inputs, buildings, product, warning, first, second)

struct construction_warning_finished_good {
    svector<e_building_type, 4> buildings;
    e_resource product;
    e_resource raw;
    xstring warning;
    xstring build;
    xstring no_route;
    xstring not_imported;
    bool import_only;
    xstring raw_no_route;
    xstring raw_not_imported;
    xstring product_no_route;
    xstring product_not_imported;
};
ANK_CONFIG_STRUCT(construction_warning_finished_good, buildings, product, raw, warning, build, no_route, not_imported,
  import_only, raw_no_route, raw_not_imported, product_no_route, product_not_imported)

struct construction_warning_rules_t {
    int min_population;
    int min_workers_needed;
    int max_unemployment_percent;
    int min_food_produced_percent;
    int max_problem_messages;

    xstring road_access;
    xstring shrine_road_access;
    xstring workers;
    xstring no_troops;
    xstring wall_patrol;
    xstring eating_more_than_produced;
    xstring too_few_jobs;
    xstring low_food;

    svector<e_building_type, 64> road_access_exempt;
    svector<construction_warning_road_area, 4> road_access_area;
    svector<e_building_type, 8> shrines;
    svector<e_building_type, 8> workers_exempt;
    svector<e_building_type, 64> defense;
    svector<e_building_type, 8> wall_patrol_types;
    svector<construction_warning_requirement, 8> requires_building;
    svector<construction_warning_stock, 8> requires_stock;
    svector<construction_warning_school, 8> venue_schools;
    svector<construction_warning_material, 24> raw_materials;
    svector<construction_warning_two_inputs, 8> two_inputs;
    svector<construction_warning_finished_good, 8> finished_goods;
};
ANK_CONFIG_STRUCT(construction_warning_rules_t, min_population, min_workers_needed, max_unemployment_percent,
  min_food_produced_percent, max_problem_messages, road_access, shrine_road_access, workers, no_troops, wall_patrol,
  eating_more_than_produced, too_few_jobs, low_food, road_access_exempt, road_access_area, shrines, workers_exempt,
  defense, wall_patrol_types, requires_building, requires_stock, venue_schools, raw_materials, two_inputs,
  finished_goods)

extern construction_warning_rules_t construction_warning_rules;

// OG run_warnings: hints after a site building was placed. Venues get only the school hints.
void construction_warnings_check_site(building& b);
void construction_warnings_check_road_access(building& b);
void construction_warnings_check_house_plots();
