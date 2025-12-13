#pragma once

#include <stdint.h>

#include "city/city_kingdome_relations.h"
#include "city/entertainment.h"
#include "city/city_industry.h"
#include "city/city_population.h"
#include "city/city_finance.h"
#include "city/city_labor.h"
#include "city/buildings.h"
#include "city/city_migration.h"
#include "city/city_sentiment.h"
#include "city/city_health.h"
#include "city/city_animals.h"
#include "city/military.h"
#include "city/city_resource.h"
#include "city/city_resource.h"
#include "city/city_fishing_points.h"
#include "city/map.h"
#include "city/coverage.h"
#include "city/city_religion.h"
#include "city/city_figures.h"
#include "city/victory.h"
#include "city/ratings.h"
#include "grid/point.h"
#include "city/city_trade.h"
#include "city/city_festival.h"
#include "grid/desirability.h"
#include "city/city_buildings.h"
#include "city/city_maintenance.h"
#include "city/city_hotkeys_handler.h"
#include "grid/bookmark.h"
#include "building/building_house_demands.h"

struct empire_city;
struct city_overlay;

struct city_t {
    city_buildings_t buildings;
    city_figures_t figures;
    city_population_t population;

    house_demands houses;
    kingdome_relation_t kingdome;
    city_military_t military;
    city_industry_t industry;
    victory_state_t victory_state;
    city_maintenance_t maintenance;
    e_availability advisors[ADVISOR_MAX];

    struct {
        uint8_t city;
        int8_t city_foreign_months_left;
        int8_t total_count;
        int8_t won_count;
        uint8_t enemy_strength;
        uint8_t roman_strength;
        int8_t months_until_battle;
        int8_t roman_months_to_travel_forth;
        int8_t roman_months_to_travel_back;
        int8_t enemy_months_traveled;
        int8_t roman_months_traveled;
    } distant_battle;

    city_finance_t finance;
    city_resources_t resource;
    city_taxes_t taxes;

    city_labor_t labor;
    city_migration_t migration;
    city_sentiment_t sentiment;

    city_health_t health;
    city_ratings_t ratings;
    city_average_coverage_t avg_coverage;

    city_religion_t religion;
    city_entertainment_t entertainment;

    city_festival_t festival;
    city_coverage_t coverage;
    e_overlay current_overlay = OVERLAY_NONE;
    e_overlay previous_overlay = OVERLAY_NONE;

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

    city_trade_t trade;
    city_map_t map;
    struct {
        int32_t has_won;
        int32_t continue_months_left;
        int32_t continue_months_chosen;
        bool fired_message_shown;
        bool victory_message_shown;
        bool start_message_shown;
        bool reserved;
        int32_t reserved_2;
    } mission;

    struct {
        int8_t other_player[18904];
        int8_t unknown_00a0;
        int8_t unknown_00a1;
        int8_t unknown_00a2;
        int8_t unknown_00a3;
        int8_t unknown_00a4;
        int8_t unknown_00a6;
        int8_t unknown_00a7;
        int32_t unknown_00c0;
        int32_t unused_27d0;
        uint16_t unused_27d0_short;
        int32_t unknown_27e0[3];
        int16_t unknown_27f0;
        int16_t unknown_27f4[18];
        int16_t unknown_2828;
        int16_t unused_28ca;
        int8_t unknown_2924[272];
        int32_t unknown_2b6c;
        int32_t unknown_2c20[1400];
        int32_t houses_requiring_unknown_to_evolve[8];
        int32_t unknown_4238[4];
        int32_t unknown_4284;
        int32_t unknown_4294[2];
        int32_t unknown_4334;
        int32_t unknown_4374[2];
        int16_t unknown_439c[3];
        int8_t padding_43b2[2];
        int32_t unknown_43d8[4];
        int32_t unknown_43f0;
        int32_t unused_4454;
        int32_t unknown_446c[4];
        int32_t unused_4488;
        int32_t unused_native_force_attack;
        int32_t unused_44e0[2];
        int32_t unused_44ec;
        int32_t unused_44f8;
        int32_t unused_4524[11];
        uint8_t unknown_458e;
        int8_t unused_45a5[6];
        int8_t unknown_464c[232];
        int32_t unknown_order;
        int32_t faction_id;
        int16_t faction_bytes[2];
    } unused;

    city_fishing_points_t fishing_points;
    city_animals_t animals;
    city_hotkeys_handler_t hotkeys_handler;
    map_bookmarks_t bookmarks;

    struct environment_t {
        void update_day();
        void river_update_flotsam();
    } environment;

    void houses_reset_demands();
    void houses_calculate_culture_demands();
    void house_service_update_health();
    void house_decay_tax_coverage();
    void house_decay_services();
    void house_service_decay_houses_covered();
    void house_service_calculate_culture_aggregates();
    void house_process_evolve();

    const city_overlay *overlay();
    inline bool overlay_is(e_overlay o) const { return current_overlay == o; }
    void set_overlay(e_overlay o);
    void toggle_overlay();
    void reset_overlay();

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

    void figures_add_attacking_native();
    void figures_add_enemy();
    void figures_add_kingdome_soldier();
    void figures_add_rioter(int is_attacking);
    void figures_add_soldier();
    void figures_update_day();
    bool figures_has_security_breach();
    void figures_generate_criminals();

    void update_prosperity_explanation();
    bool has_made_money();
    void update_prosperity_rating();
    void calculate_max_prosperity();
    void ratings_update_explanations();
    void ratings_update(bool is_yearly_update);

    bool determine_granary_get_foods(resource_list &foods, int road_network);

    empire_city& ourcity();
    void victory_check();
    void buildings_update_open_water_access();

    void government_distribute_treasury();
    void buildings_generate_figure();
    void before_start_simulation();
    void plague_update_day();
    void criminals_update_day();
    void set_max_happiness(int max);
    void change_happiness(int amount);

    void update_tick(int simtick);
    void update_day(simulation_time_t t);
    void update_week(simulation_time_t t);
    void update_month(simulation_time_t t);

    e_availability is_advisor_available(e_advisor advisor) const;
    void set_advisor_available(e_advisor advisor, e_availability available);

    bvariant get_property(const xstring &domain, const xstring &name) const;
    void on_post_load();
    void trade_update();
};

const uint8_t* city_player_name();
void city_set_player_name(const uint8_t* name);
void city_save_campaign_player_name();
void city_restore_campaign_player_name();
bvariant city_get_property(const xstring &domain, const xstring &name);

extern city_t g_city;