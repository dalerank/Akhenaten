#pragma once

#include "core/buffer.h"
#include "game/resource.h"
#include "building/building_type.h"
#include "game/game_environment.h"
#include "core/custom_span.hpp"
#include "core/xstring.h"
#include "scenario_event_manager.h"
#include "grid/point.h"
#include "scenario/types.h"
#include "scenario/scenario_difficulty.h"
#include "core/archive.h"
#include "core/settings_vars.h"
#include "figure/formation.h"
#include "grid/envinronment.h"

#include <cstdint>
#include <unordered_map>

struct scenario_data_buffers {
    buffer* mission_index = nullptr;
    buffer* map_name = nullptr;
    buffer* map_settings = nullptr;
    buffer* is_custom = nullptr;
    buffer* player_name = nullptr;

    buffer* header = nullptr;
    buffer* info1 = nullptr;
    buffer* info2 = nullptr;
    buffer* info3 = nullptr;
    buffer* events = nullptr;
    buffer* win_criteria = nullptr;
    buffer* map_points = nullptr;
    buffer* river_points = nullptr;
    buffer* empire = nullptr;
    buffer* wheat = nullptr;
    buffer* climate_id = nullptr;

    buffer* requests = nullptr;
    buffer* invasions = nullptr;
    buffer* invasion_points_land = nullptr;
    buffer* request_comply_dialogs = nullptr;
    buffer* herds = nullptr;
    buffer* demands = nullptr;
    buffer* price_changes = nullptr;
    buffer* fishing_points = nullptr;
    buffer* request_extra = nullptr;
    buffer* allowed_builds = nullptr;

    buffer* events_ph = nullptr;

    buffer* monuments = nullptr;
};

enum e_climate { 
    CLIMATE_CENTRAL = 0, 
    CLIMATE_NORTHERN = 1, 
    CLIMATE_DESERT = 2
};

struct win_criteria_t {
    int enabled;
    int goal;
};
ANK_CONFIG_STRUCT(win_criteria_t, enabled, goal)

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
    e_formation_attack_type attack_type;
    int month;
};

struct price_change_t {
    int year;
    int month;
    e_resource resource;
    int amount;
    int is_rise;
};

struct demand_change_t {
    int year;
    int month;
    e_resource resource;
    int route_id;
    int is_rise;
};

struct extra_damage_t {
    e_building_type type;
    int8_t fire;
    int8_t collapse;
};

template<>
struct std::hash<extra_damage_t> {
    [[nodiscard]] size_t operator()(const extra_damage_t &d) const noexcept {
        return d.type;
    }
};
ANK_CONFIG_STRUCT(extra_damage_t, type, fire, collapse)

struct building_stage_t {
    xstring key;
    svector<e_building_type, 16> buildings;
};
ANK_CONFIG_STRUCT(building_stage_t, key, buildings)

enum e_scenario_mode {
    e_scenario_normal,
    e_scenario_selected,
    e_scenario_custom_map,
};

class io_buffer;

struct scenario_data_t {
    uint8_t scenario_name[65];
    scenario_difficulty_t difficulty;

    int start_year;
    int climate;
    int player_rank;
    int player_incarnation;

    int debt_interest_rate;

    int kingdom_supplies_grain;
    int image_id;
    uint8_t subtitle[64];
    uint8_t brief_description[522];
    e_enemy_type enemy_id;
    bool is_open_play;
    int open_play_scenario_id;
    bool is_custom;
    bool alt_predator_type;

    int player_faction;

    struct win_criterias_t {
        win_criteria_t population;
        win_criteria_t culture;
        win_criteria_t prosperity;
        win_criteria_t monuments;
        win_criteria_t kingdom;
        win_criteria_t housing_count;
        win_criteria_t housing_level;
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
        int next_mission;
    } win_criteria;

    struct {
        int initial_funds;
        int rescue_loan;
    } finance;

    struct {
        int id;
        int is_expanded;
        int expansion_year;
        int distant_battle_kingdome_travel_months;
        int distant_battle_enemy_travel_months;
    } empire;

    //request_t requests[40];
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
        int copper_mine_collapsed;
        int clay_pit_flooded;
    } random_events;

    map_data_t map;

    tile2i entry_point;
    tile2i exit_point;
    tile2i river_entry_point;
    tile2i river_exit_point;

    tile2i earthquake_point;
    tile2i herd_points_predator[MAX_PREDATOR_HERD_POINTS];
    tile2i herd_points_prey[MAX_PREY_HERD_POINTS];
    tile2i fishing_points[MAX_FISH_POINTS];
    tile2i disembark_points[MAX_DISEMBARK_POINTS];
    svector<tile2i, MAX_INVASION_POINTS_LAND> invasion_points_land;
    svector<tile2i, MAX_INVASION_POINTS_SEA> invasion_points_sea;

    bool allowed_buildings[BUILDING_MAX] = { 0 };
    resource_allow_vec init_resources;
    std::array<extra_damage_t, BUILDING_MAX> extra_damage;
    std::unordered_map<xstring, building_stage_t> stages;
    settings_vars_t vars;

    struct {
        int hut;
        int meeting;
        int crops;
    } native_images;

    struct { // used to be stored in the settings file
        int campaign_mission_rank;
        int campaign_scenario_id;
        int starting_kingdom;
        int starting_personal_savings;
        e_scenario_mode scmode;
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

    struct env_t {
        bool flotsam_enabled;
        bool has_animals;
        uint8_t gods_least_mood;
        bool hide_nilometer;
        vegetation_opt marshland_grow;
        vegetation_opt tree_grow;
    } env;

    struct meta_t {
        xstring start_message;
        bool start_message_shown;
        bool hide_won_screen;
        std::array<int, 8> initial_funds = { 0 };
        std::array<int, 8> rescue_loans = { 0 };
        std::array<int, 8> house_tax_multipliers = { 0 };
    } meta;

    event_manager_t events;

    bool is_saved;

    void update();
    e_scenario_mode mode();
    void set_mode(e_scenario_mode m) { settings.scmode = m; }

    bool is_scenario_id(custom_span<int> missions);

    int startup_funds() const;
    int rescue_loan() const;
    int house_tax_multiplier(int v) const;

    void load_metadata(const mission_id_t &missionid);
    void bind_data(io_buffer *iob, size_t version, size_t size);

    template<typename ... Args>
    bool is_scenario_id(const Args ... args) {
        int values[] = { args... };
        return is_scenario_id(make_span(values));
    }
};
ANK_CONFIG_STRUCT(scenario_data_t::meta_t, start_message, hide_won_screen, initial_funds, rescue_loans, house_tax_multipliers)
ANK_CONFIG_STRUCT(scenario_data_t::env_t, flotsam_enabled, has_animals, gods_least_mood, hide_nilometer, marshland_grow, tree_grow)
ANK_CONFIG_STRUCT(scenario_data_t::win_criterias_t, population, culture, prosperity, monuments, kingdom, housing_count, housing_level, next_mission)

extern scenario_data_t g_scenario;

void scenario_settings_init();
void scenario_settings_init_mission();

void scenario_set_campaign_rank(int rank);

int scenario_campaign_scenario_id();

void scenario_set_campaign_scenario(int scenario_id);

int scenario_additional_damage(e_building_type type, e_damage_type damage);

int scenario_is_before_mission(int mission);

int scenario_starting_kingdom();

int scenario_starting_personal_savings();

const uint8_t* scenario_name();

void scenario_set_name(const uint8_t* name);

int scenario_is_open_play();

int scenario_open_play_id();

int scenario_property_climate();

int scenario_property_start_year();

int scenario_property_kingdom_supplies_grain();

int scenario_property_enemy();

int scenario_property_player_rank();

int scenario_image_id();

const uint8_t* scenario_subtitle();

int scenario_property_monuments_is_enabled();
int scenario_property_monument(int field);
void scenario_set_monument(int field, int m);

bool scenario_building_allowed(e_building_type btype);
void scenario_building_allow(e_building_type btype, bool allow);

int scenario_building_image_native_hut();

int scenario_building_image_native_meeting();

int scenario_building_image_native_crops();
