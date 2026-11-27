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

class construction_warnings_t {
public:
    struct static_params {
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

    static const static_params& params();

    // OG run_warnings: hints after a site building was placed. Venues get only the school hints.
    void check_site(building& b);
    void check_road_access(building& b);

private:
    template <typename List>
    static bool listed(const List& list, e_building_type type);

    void warn(const xstring& id);

    int active(e_resource r) const;
    int total(e_resource r) const;
    int stored(e_resource r) const;
    bool can_produce(e_resource r) const;
    bool can_import(e_resource r) const;
    bool could_import(e_resource r) const;
    bool imported(e_resource r) const;
    bool has(e_resource industry, e_resource stock) const;

    void hint_import(e_resource r, const xstring& no_route, const xstring& not_imported);
    void hint_raw_material(e_resource produce, const xstring& build, e_resource import_res, const xstring& no_route,
      const xstring& not_imported);
    void hint_input(const construction_warning_input& in, bool both);

    void check_raw_material(const construction_warning_material& m);
    void check_two_inputs(const construction_warning_two_inputs& t);
    void check_finished_good(const construction_warning_finished_good& g);
    void check_workers(building& b);
    void check_requirements(e_building_type type);
    void check_military(e_building_type type);
    void check_stock(e_building_type type);
    void check_wall_patrol(building& b);
    void check_materials(e_building_type type);
    bool is_venue(e_building_type type) const;
    void check_venue_schools(e_building_type type);
    bool has_road_access(building& b) const;

    bool shown = false;
};
ANK_CONFIG_STRUCT(construction_warnings_t::static_params, min_population, min_workers_needed, max_unemployment_percent,
  min_food_produced_percent, max_problem_messages, road_access, shrine_road_access, workers, no_troops, wall_patrol,
  eating_more_than_produced, too_few_jobs, low_food, road_access_exempt, road_access_area, shrines, workers_exempt,
  defense, wall_patrol_types, requires_building, requires_stock, venue_schools, raw_materials, two_inputs,
  finished_goods)
