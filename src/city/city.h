#pragma once

#include <stdint.h>

#include "city/city_kingdome_relations.h"
#include "game/player_record.h"
#include "city/entertainment.h"
#include "city/city_industry.h"
#include "city/city_population.h"
#include "city/city_finance.h"
#include "city/city_taxes.h"
#include "city/city_labor.h"
#include "city/buildings.h"
#include "city/city_migration.h"
#include "city/city_sentiment.h"
#include "city/city_health.h"
#include "city/military.h"
#include "city/city_resource.h"
#include "city/city_food_supply.h"
#include "city/city_monuments.h"
#include "city/map.h"
#include "city/coverage.h"
#include "city/city_religion.h"
#include "city/city_figures.h"
#include "city/ratings.h"
#include "grid/point.h"
#include "city/city_trade.h"
#include "grid/desirability.h"
#include "city/city_buildings.h"
#include "city/city_maintenance.h"
#include "building/building_house_demands.h"

struct empire_city;

struct city_t {
    city_buildings_t buildings;
    city_figures_t figures;
    population_state population;

    house_demands houses;
    kingdome_state kingdome;
    city_military_t military;
    city_industry_t industry;
    city_maintenance_t maintenance;
    e_availability advisors[ADVISOR_MAX];
    e_availability empire_screen = AVAILABLE;

    finance_state finance;
    city_resources_t resource;
    city_food_supply_t food_supply;
    taxes_state taxes;

    labor_state labor;
    migration_state migration;
    sentiment_state sentiment;

    health_state health;
    ratings_state ratings;
    city_average_coverage_t avg_coverage;

    gods_state gods;
    city_entertainment_t entertainment;

    city_monuments_t monuments;

    city_coverage_t coverage;

    struct {
        int8_t march_enemy;
        int8_t march_horse;
        int8_t march_wolf;
        int8_t shoot_arrow;
        int8_t hit_soldier;
        int8_t hit_spear;
        int8_t hit_club;
        int8_t hit_elephant;
        int8_t hit_axe;
        int8_t hit_wolf;
        int8_t die_citizen;
        int8_t die_soldier;
    } sound;

    trade_state trade;
    city_map_t map;

    // OG vegetation_growth_state gatherer reach flags (refreshed with daily growth).
    struct {
        bool trees_reachable = false;
        bool reeds_reachable = false;
    } vegetation;

    // OG city_locusts_countdown (-1 = waiting for the flood), city_frogs_countdown, mummies_max.
    struct {
        int32_t locusts_countdown;
        int32_t frogs_countdown;
        int32_t mummies_max;
    } plagues;

    struct {
        bool fired_message_shown;
        bool victory_message_shown;
        bool reserved;
        int32_t reserved_2;
    } mission;


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
    finance_context finance_ctx();
    finance_system finance_sys();
    taxes_context taxes_ctx();
    taxes_system taxes_sys();
    labor_context labor_ctx();
    labor_system labor_sys();
    trade_context trade_ctx();
    trade_system trade_sys();
    health_context health_ctx();
    health_system health_sys();
    gods_context gods_ctx();
    gods_system gods_sys();
    sentiment_context sentiment_ctx();
    sentiment_system sentiment_sys();
    population_context population_ctx();
    population_system population_sys();
    migration_context migration_ctx();
    migration_system migration_sys();
    ratings_context ratings_ctx();
    ratings_system ratings_sys();
    kingdome_context kingdome_ctx();
    kingdome_system kingdome_sys();

    e_availability is_advisor_available(e_advisor advisor) const;
    void set_advisor_available(e_advisor advisor, e_availability available);

    e_availability is_empire_available() const { return empire_screen; }
    void set_empire_available(e_availability available) { empire_screen = available; }

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