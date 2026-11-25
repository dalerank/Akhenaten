#pragma once

#include <stdint.h>

#include "game/player_record.h"
#include "city/city_industry.h"
#include "city/buildings.h"
#include "city/military.h"
#include "city/city_resource.h"
#include "city/city_food_supply.h"
#include "city/map.h"
#include "city/coverage.h"
#include "city/city_figures.h"
#include "grid/point.h"
#include "grid/desirability.h"
#include "city/city_buildings.h"
#include "building/building_house_demands.h"

struct empire_city;

struct city_t {
    city_buildings_t buildings;
    city_figures_t figures;
    house_demands houses;
    city_military_t military;
    city_industry_t industry;

    city_resources_t resource;
    city_food_supply_t food_supply;


    city_map_t map;


    void houses_reset_demands();
    void houses_calculate_culture_demands();
    void house_service_update_health();
    void house_decay_tax_coverage();
    void house_decay_services();
    void house_service_decay_houses_covered();
    void house_service_calculate_culture_aggregates();
    void house_process_evolve();


    void init();
    void reload_objects();

    void init_custom_map();
    void init_campaign_mission();
    void init_mission_resources(const resource_allow_vec &resources);
    e_resource allowed_foods(int i);
    bool is_food_allowed(e_resource resource);
    void set_allowed_food(int i, e_resource r);

    bool generate_trader_from(empire_city &city);
    bool available_resource(e_resource resource);
    void update_allowed_foods();
    bool can_produce_resource(e_resource resource);
    void set_produce_resource(e_resource resource, bool v);

    void figures_add_kingdome_soldier();
    void figures_add_rioter(int is_attacking);
    void figures_add_soldier();
    void figures_update_day();
    bool figures_has_security_breach();
    void figures_generate_criminals();


    bool determine_granary_get_foods(resource_list &foods, int road_network);

    empire_city& ourcity();
    void buildings_update_open_water_access();

    void government_distribute_treasury();
    void buildings_generate_figure();
    void before_start_simulation();
    void plague_update_day();
    void criminals_update_day();
    void set_max_happiness(int max);
    void change_happiness(int amount);

    void update_tick(int simtick);
    void update_month(simulation_time_t t);

    bvariant get_property(xstring domain, xstring name) const;
    void on_post_load();

    template <typename T>
    void reload_system(T &system) {
        call_unload_if_exists(system);
        const bool ok = g_config_arch.r(system.esid(), system);
        call_init_if_exists(system);
        verify_no_crash_var(ok, "Variable not exist in config: %s", system.esid());
    }
};

pcstr city_player_name();
void city_set_player_name(xstring name);
// Snapshot of what the city achieved, handed to the player profile when a mission is won.
mission_result_t city_make_mission_result(int scenario_id);
void city_restore_campaign_player_name();
bvariant city_get_property(xstring domain, xstring name);

extern city_t g_city;