#pragma once

#include "core/variant.h"
#include "core/xstring.h"
#include "game/player_record.h"
#include "game/resource.h"

struct empire_city;
struct simulation_time_t;

struct city_t {
    void init();
    void reload_objects();

    void init_custom_map();
    void init_campaign_mission();
    void init_mission_resources(const resource_allow_vec& resources);

    bool generate_trader_from(empire_city &city);
    bool available_resource(e_resource resource);
    bool can_produce_resource(e_resource resource);
    void set_produce_resource(e_resource resource, bool v);

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
};

pcstr city_player_name();
void city_set_player_name(xstring name);
// Snapshot of what the city achieved, handed to the player profile when a mission is won.
mission_result_t city_make_mission_result(int scenario_id);
void city_restore_campaign_player_name();
bvariant city_get_property(xstring domain, xstring name);

extern city_t g_city;