#pragma once

#include "building/building_type.h"
#include "building/building_state.h"
#include "core/span.hpp"
#include "figure/action.h"
#include "figure/type.h"
#include "game/resource.h"
#include "grid/point.h"

#include <stdint.h>
#include <algorithm>

class figure;
class io_buffer;

constexpr uint32_t MAX_BUILDINGS = 4000;
constexpr uint32_t MAX_FIGURES_PER_BUILDING = 8;

enum e_labor_state {
    LABOR_STATE_NONE,
    LABOR_STATE_PRESENT,
    LABOR_STATE_JUST_ENTERED
};

enum e_building_slot {
    BUILDING_SLOT_SERVICE = 0,
    BUILDING_SLOT_CARTPUSHER = 1,
    BUILDING_SLOT_LABOR_SEEKER = 2,
    BUILDING_SLOT_HUNTER = 3,
};

class building {
private:
    //    short figure_id;
    //    short figure_id2; // labor seeker or market buyer
    //    short immigrant_figure_id;
    //    short figure_id4; // tower ballista or burning ruin prefect
    short figure_ids_array[MAX_FIGURES_PER_BUILDING]; // oh boy!

public:
    int id;
    e_building_state state;
    unsigned char faction_id;
    unsigned char unknown_value;
    unsigned char size;
    unsigned char house_is_merged;
    unsigned char house_size;
    map_point tile;
    //    unsigned char x;
    //    unsigned char y;
    //    unsigned short grid_offset;
    e_building_type type;
    union {
        short house_level;
        e_resource warehouse_resource_id;
        //        short workshop_type;
        short orientation;
        e_figure_type fort_figure_type;
        short native_meeting_center_id;
        short market_goods;
        short roadblock_exceptions;
        short barracks_priority;
    } subtype;
    unsigned short road_network_id;
    unsigned short creation_sequence_index;
    short houses_covered;
    short percentage_houses_covered;
    short house_population;
    short house_population_room;
    short distance_from_entry;
    short house_highest_population;
    short house_unreachable_ticks;
    map_point road_access;
    //    figure *figure_id;
    //    figure *figure_id2; // labor seeker or market buyer
    //    short immigrant_figure_id;
    //    short figure_id4; // tower ballista or burning ruin prefect
    short figure_spawn_delay;
    unsigned char figure_roam_direction;
    uint32_t has_water_access;
    int prev_part_building_id;
    int next_part_building_id;
    //    short stored_loads_c3;
    short stored_full_amount;
    bool has_well_access;
    short num_workers;
    unsigned char labor_category;
    e_resource output_resource_id;
    uint32_t has_road_access;
    short house_criminal_active;
    unsigned char disease_days;
    unsigned char common_health;
    unsigned char malaria_risk;
    short damage_risk;
    short fire_risk;
    short fire_duration;
    unsigned char health_proof;
    unsigned char fire_proof; // cannot catch fire or collapse
    unsigned char map_random_7bit;
    unsigned char house_tax_coverage;
    unsigned short tax_collector_id;
    short formation_id;
    union {
        struct dock_t {
            short queued_docker_id;
            unsigned char num_ships;
            signed char orientation;
            short docker_ids[3];
            short trade_ship_id;
        } dock;
        struct market_t {
            short inventory[8];
            short pottery_demand;
            short furniture_demand;
            short oil_demand;
            short wine_demand;
            short fetch_inventory_id;
        } market;
        struct granary_t {
            short resource_stored[16];
        } granary;
        struct industry_t {
            short ready_production;
            short progress;
            bool spawned_worker_this_month;
            int unk_b[11];
            unsigned char has_fish;
            int unk_c[14];
            unsigned char blessing_days_left;
            unsigned char orientation;
            bool has_raw_materials;
            int unk_1;
            unsigned char curse_days_left;
            int unk_6[6];
            short fishing_boat_id;
            int unk_40[40];
            e_labor_state labor_state;
            unsigned char labor_days_left;
            int unk_12[10];
            unsigned short work_camp_id;
            unsigned char worker_id;
        } industry;
        struct entertainment_t {
            unsigned char num_shows;
            unsigned char days1;
            unsigned char days2;
            //            unsigned char days3;
            unsigned char days3_or_play;
            unsigned short booth_corner_grid_offset;
            unsigned short ph_unk00_u32;
            unsigned short ph_unk01_u8;
            unsigned short ph_unk02_u8;
        } entertainment;
        struct {
            short foods[8];
            short inventory[8];
            unsigned char juggler;
            unsigned char bandstand_juggler;
            unsigned char bandstand_musician;
            unsigned char colosseum_gladiator;
            unsigned char magistrate; // colosseum_lion
            unsigned char hippodrome;
            unsigned char school;
            unsigned char library;
            unsigned char academy;
            unsigned char apothecary;
            unsigned char dentist;
            unsigned char mortuary;
            unsigned char physician;
            unsigned char temple_osiris;
            unsigned char temple_ra;
            unsigned char temple_ptah;
            unsigned char temple_seth;
            unsigned char temple_bast;
            unsigned char no_space_to_expand;
            unsigned char num_foods;
            unsigned char entertainment;
            unsigned char education;
            unsigned char health;
            unsigned char num_gods;
            unsigned char shrine_access;
            unsigned char devolve_delay;
            unsigned char evolve_text_id;
            unsigned char bazaar_access;
            unsigned char water_supply;
        } house;
        struct {
            unsigned char variant;
            unsigned char temple_complex_attachments;
        } monuments;
    } data;
    int tax_income_or_storage;
    unsigned char house_days_without_food;
    bool ruin_has_plague;
    signed char desirability;
    bool is_deleted;
    bool is_adjacent_to_water;
    unsigned char storage_id;
    union {
        signed char house_happiness;
        signed char native_anger;
    } sentiment;
    unsigned char show_on_problem_overlay;
    unsigned short deben_storage;

    ////

    // building.c
    building();
    building* main();
    building* next();
    building* top_xy();
    bool is_main();

    bool is_house();
    bool is_fort();
    bool is_defense_ph();
    bool is_farm();
    bool is_floodplain_farm();
    bool is_workshop();
    bool is_extractor();
    bool is_monument();
    bool is_palace();
    bool is_tax_collector();
    bool is_governor_palace();
    bool is_temple();
    bool is_large_temple();
    bool is_shrine() const;
    bool is_guild();
    bool is_beautification();
    bool is_water_crossing();

    bool is_industry();
    bool is_food_category();
    bool is_infrastructure();
    bool is_administration();
    bool is_religion();
    bool is_entertainment();
    bool is_culture();
    bool is_military();

    void clear_related_data();

    const int get_figureID(int i) const {
        return figure_ids_array[i];
    };

    figure* get_figure(int i);
    void bind_iob_figures(io_buffer* iob);
    void set_figure(int i, int figure_id = -1);
    void set_figure(int i, figure* f);
    void remove_figure(int i);
    bool has_figure(int i, int figure_id = -1);
    bool has_figure(int i, figure* f);
    bool has_figure_of_type(int i, e_figure_type _type);
    int get_figure_slot(figure* f);

    figure* create_figure_generic(e_figure_type _type, int created_action, int slot, int created_dir);
    figure* create_roaming_figure(e_figure_type _type, int created_action = FIGURE_ACTION_125_ROAMING, int slot = BUILDING_SLOT_SERVICE);
    figure* create_figure_with_destination(e_figure_type _type, building* destination, int created_action = ACTION_10_GOING, int slot = BUILDING_SLOT_SERVICE);
    figure* create_cartpusher(e_resource resource_id, int quantity, int created_action = FIGURE_ACTION_20_CARTPUSHER_INITIAL, int slot = BUILDING_SLOT_CARTPUSHER);

    int worker_percentage();
    int figure_hunting_longe_spawn_timer();
    int figure_spawn_timer();
    void check_labor_problem();
    bool common_spawn_figure_trigger(int min_houses);
    void common_spawn_labor_seeker(int min_houses);
    bool common_spawn_roamer(e_figure_type type, int min_houses, int created_action = FIGURE_ACTION_125_ROAMING);
    bool common_spawn_goods_output_cartpusher(bool only_one = true, bool only_full_loads = true, int min_carry = 100, int max_carry = 800);

    void spawn_figure_work_camp();
    bool spawn_patrician(bool spawned);
    void spawn_figure_engineers_post();
    void spawn_figure_firehouse();
    void spawn_figure_police();
    void spawn_figure_juggler();
    void spawn_figure_musician();
    void spawn_figure_dancer();
    void spawn_figure_bandstand();
    void spawn_figure_booth();
    void spawn_figure_senet();
    void spawn_figure_pavillion();
    void set_market_graphic();
    void spawn_figure_market();
    void set_water_supply_graphic();
    void spawn_figure_school();
    void spawn_figure_library();
    void spawn_figure_apothecary();
    void spawn_figure_dentist();
    void spawn_figure_mortuary();
    void spawn_figure_physician();
    void spawn_figure_magistrate();
    void spawn_figure_temple();
    void spawn_figure_watersupply();
    void set_greate_palace_graphic();
    void spawn_figure_tax_collector();
    void spawn_figure_industry();
    void spawn_figure_farms();
    void spawn_figure_farm_harvests();
    void spawn_figure_wharf();
    void spawn_figure_shipyard();
    void spawn_figure_dock();
    void spawn_figure_storageyard();
    void spawn_figure_granary();
    void spawn_figure_hunting_lodge();
    void spawn_figure_reed_gatherers();
    void spawn_figure_wood_cutters();
    void spawn_figure_native_hut();
    void spawn_figure_native_meeting();
    void spawn_figure_tower();
    void spawn_figure_barracks();

    bool can_spawn_ostrich_hunter();
    bool can_spawn_gatherer(e_figure_type ftype, int max_gatherers_per_building, int carry_per_person);
    bool can_spawn_woodcutter();

    void update_native_crop_progress();
    void update_road_access();
    void update_month();
    bool figure_generate();
    int get_fire_risk(int value);

    // barracks.c
    void barracks_add_weapon();
    int barracks_create_soldier();
    bool barracks_create_tower_sentry();
    void barracks_toggle_priority();
    int barracks_get_priority();
};

int building_id_first(e_building_type type);
building* building_first(e_building_type type);

building* building_next(int id, e_building_type type);
building* building_get(int id);

inline building* building_begin() {
    return building_get(1);
}

inline building* building_end() {
    return building_get(MAX_BUILDINGS);
}

template<typename T>
void buildings_valid_do(T func) {
    for (building *it = building_begin(), *e = building_end(); it != e; ++it) {
        if (it->state == BUILDING_STATE_VALID) {
            func(*it);
        }
    }
}

template<typename ... Args>
bool building_type_any_of(building &b, Args ... args) {
    int types[] = {args...};
    return (std::find(std::begin(types), std::end(types), b.type) != std::end(types));
}

template<typename ... Args>
bool building_type_none_of(building &b, Args ... args) {
    int types[] = {args...};
    return (std::find(std::begin(types), std::end(types), b.type) == std::end(types));
}

template<typename Array, typename ... Args>
void buildings_get(Array &arr, Args ... args) {
    int types[] = {args...};
    for (const auto &type : types) {
        for (building *it = building_begin(), *e = building_end(); it != e; ++it) {
            if (it->type == type) {
                arr.push_back(it);
            }
        }
    }
}

template <typename T>
inline building* building_first(T pred) {
    for (auto it = building_begin(), end = building_end(); it != end; ++it) {
        if (it->state == BUILDING_STATE_VALID && pred(*it)) {
            return it;
        }
    }
    return nullptr;
}

building* building_create(e_building_type type, int x, int y, int orientation);

building* building_at(int grid_offset);
building* building_at(int x, int y);
building* building_at(map_point point);
bool building_exists_at(int grid_offset, building* b);
bool building_exists_at(int x, int y, building* b);
bool building_exists_at(map_point point, building* b);

void building_clear_all(void);
// void building_totals_add_corrupted_house(int unfixable);

bool building_is_house(int type);
bool building_is_fort(int type);
bool building_is_defense_ph(int type);
bool building_is_farm(int type);
bool building_is_floodplain_farm(building* b);
bool building_is_workshop(int type);
bool building_is_extractor(int type);
bool building_is_harvester(int type);
bool building_is_monument(int type);
bool building_is_administration(int type);
bool building_is_palace(int type);
bool building_is_tax_collector(int type);
bool building_is_governor_palace(int type);
bool building_is_temple(int type);
bool building_is_large_temple(int type);
bool building_is_shrine(int type);
bool building_is_guild(int type);
bool building_is_statue(int type);
bool building_is_beautification(int type);
bool building_is_water_crossing(int type);
bool building_is_industry_type(const building* b);

bool building_is_industry(int type);
bool building_is_food_category(int type);
bool building_is_infrastructure(int type);
bool building_is_religion(int type);
bool building_is_entertainment(int type);
bool building_is_culture(int type);
bool building_is_military(int type);

bool building_is_draggable(int type);

int building_get_highest_id(void);
void building_update_highest_id(void);
void building_update_state(void);
void building_update_desirability(void);

int building_mothball_toggle(building* b);
int building_mothball_set(building* b, int value);

std::span<building>& city_buildings();