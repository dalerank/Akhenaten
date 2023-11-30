#pragma once

#include "core/game_environment.h"
#include "events.h"
#include "grid/point.h"
#include "scenario/types.h"

#include <game/resource.h>
#include <stdint.h>

enum {
    ALLOWED_BUILDING_NONE = 0,
    ALLOWED_BUILDING_FARMS = 1,
    ALLOWED_BUILDING_RAW_MATERIALS = 2,
    ALLOWED_BUILDING_WORKSHOPS = 3,
    ALLOWED_BUILDING_ROAD = 4,
    ALLOWED_BUILDING_WALL = 5,
    ALLOWED_BUILDING_AQUEDUCT = 6,
    ALLOWED_BUILDING_HOUSING = 7,
    ALLOWED_BUILDING_AMPHITHEATER = 8,
    ALLOWED_BUILDING_THEATER = 9,
    ALLOWED_BUILDING_HIPPODROME = 10,
    ALLOWED_BUILDING_COLOSSEUM = 11,
    ALLOWED_BUILDING_GLADIATOR_SCHOOL = 12,
    ALLOWED_BUILDING_LION_HOUSE = 13,
    ALLOWED_BUILDING_ACTOR_COLONY = 14,
    ALLOWED_BUILDING_CHARIOT_MAKER = 15,
    ALLOWED_BUILDING_GARDENS = 16,
    ALLOWED_BUILDING_PLAZA = 17,
    ALLOWED_BUILDING_STATUES = 18,
    ALLOWED_BUILDING_DOCTOR = 19,
    ALLOWED_BUILDING_HOSPITAL = 20,
    ALLOWED_BUILDING_BATHHOUSE = 21,
    ALLOWED_BUILDING_BARBER = 22,
    ALLOWED_BUILDING_SCRIBAL_SCHOOL = 23,
    ALLOWED_BUILDING_ACADEMY = 24,
    ALLOWED_BUILDING_LIBRARY = 25,
    ALLOWED_BUILDING_PREFECTURE = 26,
    ALLOWED_BUILDING_FORT = 27,
    ALLOWED_BUILDING_GATEHOUSE = 28,
    ALLOWED_BUILDING_TOWER = 29,
    ALLOWED_BUILDING_SMALL_TEMPLES = 30,
    ALLOWED_BUILDING_LARGE_TEMPLES = 31,
    ALLOWED_BUILDING_MARKET = 32,
    ALLOWED_BUILDING_GRANARY = 33,
    ALLOWED_BUILDING_STORAGE_YARD = 34,
    ALLOWED_BUILDING_TRIUMPHAL_ARCH = 35,
    ALLOWED_BUILDING_DOCK = 36,
    ALLOWED_BUILDING_WHARF = 37,
    ALLOWED_BUILDING_GOVERNOR_HOME = 38,
    ALLOWED_BUILDING_ENGINEERS_POST = 39,
    ALLOWED_BUILDING_PALACE = 40,
    ALLOWED_BUILDING_TAX_COLLECTOR = 41,
    ALLOWED_BUILDING_WELL = 42,
    ALLOWED_BUILDING_ORACLE = 43,
    ALLOWED_BUILDING_MISSION_POST = 44,
    ALLOWED_BUILDING_BRIDGE = 45,
    ALLOWED_BUILDING_BARRACKS = 46,
    ALLOWED_BUILDING_MILITARY_ACADEMY = 47,
    ALLOWED_BUILDING_DISTRIBUTION_CENTER = 48,
};

struct win_criteria_t {
    int enabled;
    int goal;
};

struct map_data_t {
    int width = -1;
    int height = -1;
    int start_offset = -1;
    int border_size = -1;
};

struct request_t {
    int year;
    e_resource resource;
    int amount;
    int deadline_years;
    int can_comply_dialog_shown;
    int kingdom;
    int month;
    int state;
    bool visible;
    int months_to_comply;
};

struct invasion_t {
    int year;
    int type;
    int amount;
    int from;
    int attack_type;
    int month;
};

struct price_change_t {
    int year;
    int month;
    int resource;
    int amount;
    int is_rise;
};

struct demand_change_t {
    int year;
    int month;
    int resource;
    int route_id;
    int is_rise;
};

struct scenario_data_t {
    uint8_t scenario_name[65];

    int start_year;
    int climate;
    int player_rank;
    int player_incarnation;

    int initial_funds;
    int rescue_loan;
    int debt_interest_rate;

    int kingdom_supplies_grain;
    int image_id;
    uint8_t subtitle[64];
    uint8_t brief_description[522];
    int enemy_id;
    bool is_open_play;
    int open_play_scenario_id;
    bool is_custom;
    bool alt_predator_type;

    int player_faction;

    struct {
        struct win_criteria_t population;
        struct win_criteria_t culture;
        struct win_criteria_t prosperity;
        struct win_criteria_t monuments;
        struct win_criteria_t kingdom;
        struct win_criteria_t housing_count;
        struct win_criteria_t housing_level;
        struct {
            int enabled;
            int years;
        } time_limit;
        struct {
            int enabled;
            int years;
        } survival_time;
        int milestone25_year;
        int milestone50_year;
        int milestone75_year;
    } win_criteria;

    struct {
        int id;
        int is_expanded;
        int expansion_year;
        int distant_battle_kingdome_travel_months;
        int distant_battle_enemy_travel_months;
    } empire;

    request_t requests[40];
    demand_change_t demand_changes[40];
    price_change_t price_changes[40];
    invasion_t invasions[40];

    struct {
        int severity;
        int year;
    } earthquake;

    int current_pharaoh;
    struct {
        int year;
        int enabled;
    } emperor_change;

    struct {
        int year;
        int enabled;
    } gladiator_revolt;

    struct {
        int sea_trade_problem;
        int land_trade_problem;
        int raise_wages;
        int lower_wages;
        int contaminated_water;
        int iron_mine_collapse;
        int clay_pit_flooded;
    } random_events;

    map_data_t map;

    //    struct {
    //        int width;
    //        int height;
    //        int grid_start;
    //        int grid_border_size;
    ////        map_tile entry_point;
    ////        map_tile exit_point;
    ////        map_tile entry_flag;
    ////        map_tile exit_flag;
    //    } map;
    map_point entry_point;
    map_point exit_point;
    map_point river_entry_point;
    map_point river_exit_point;
    map_point earthquake_point;
    map_point herd_points_predator[MAX_PREDATOR_HERD_POINTS];
    map_point herd_points_prey[MAX_PREY_HERD_POINTS];
    tile2i fishing_points[MAX_FISH_POINTS];
    map_point disembark_points[MAX_DISEMBARK_POINTS];
    map_point invasion_points_land[MAX_INVASION_POINTS_LAND];
    map_point invasion_points_sea[MAX_INVASION_POINTS_SEA];

    bool allowed_buildings[MAX_ALLOWED_BUILDINGS];

    struct {
        int hut;
        int meeting;
        int crops;
    } native_images;

    struct { // used to be stored in the settings file
        int campaign_mission_rank;
        int campaign_scenario_id;
        int is_custom;
        int starting_kingdom;
        int starting_personal_savings;
    } settings;

    struct {
        int monuments_set;
        int first;
        int second;
        int third;
        struct {
            int required;
            int dispatched;
        } burial_provisions[RESOURCES_MAX];
    } monuments;

    struct {
        bool flotsam_enabled;
        bool has_animals;
    } env;

    bool is_saved;
};

extern scenario_data_t g_scenario_data;
