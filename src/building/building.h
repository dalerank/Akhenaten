#ifndef BUILDING_BUILDING_H
#define BUILDING_BUILDING_H

//#include "figure/figure.h"
#include "building/type.h"
#include "core/buffer.h"

//#define MAX_BUILDINGS[GAME_ENV] 10000
static const int MAX_BUILDINGS[2] = {
        2000,
        4000
};

// partial (forward) declaration for recursive class
class figure;
#include "figure/figure.h"

#define MAX_FIGURES_PER_BUILDING 8

class building {
private:
//    short figure_id;
//    short figure_id2; // labor seeker or market buyer
//    short immigrant_figure_id;
//    short figure_id4; // tower ballista or burning ruin prefect
    short figure_ids_array[MAX_FIGURES_PER_BUILDING]; // oh boy!
public:
    int id;
    unsigned char state;
    unsigned char faction_id;
    unsigned char unknown_value;
    unsigned char size;
    unsigned char house_is_merged;
    unsigned char house_size;
    unsigned char x;
    unsigned char y;
    unsigned short grid_offset;
    short type;
    union {
        short house_level;
        short warehouse_resource_id;
        short workshop_type;
        short orientation;
        short fort_figure_type;
        short native_meeting_center_id;
        short market_goods;
        short roadblock_exceptions;
        short barracks_priority;
    } subtype;
    unsigned char road_network_id;
    unsigned short creation_sequence_index;
    short houses_covered;
    short percentage_houses_covered;
    short house_population;
    short house_population_room;
    short distance_from_entry;
    short house_highest_population;
    short house_unreachable_ticks;
    unsigned char road_access_x;
    unsigned char road_access_y;
//    figure *figure_id;
//    figure *figure_id2; // labor seeker or market buyer
//    short immigrant_figure_id;
//    short figure_id4; // tower ballista or burning ruin prefect
    unsigned char figure_spawn_delay;
    unsigned char figure_roam_direction;
    unsigned char has_water_access;
    int prev_part_building_id;
    int next_part_building_id;
    short loads_stored;
    unsigned char has_well_access;
    short num_workers;
    unsigned char labor_category;
    unsigned char output_resource_id;
    unsigned char has_road_access;
    unsigned char house_criminal_active;
    short damage_risk;
    short fire_risk;
    short fire_duration;
    unsigned char fire_proof; // cannot catch fire or collapse
    unsigned char house_figure_generation_delay;
    unsigned char house_tax_coverage;
    short formation_id;
    union {
        struct {
            short queued_docker_id;
            unsigned char num_ships;
            signed char orientation;
            short docker_ids[3];
            short trade_ship_id;
        } dock;
        struct {
            short inventory[8];
            short pottery_demand;
            short furniture_demand;
            short oil_demand;
            short wine_demand;
            unsigned char fetch_inventory_id;
        } market;
        struct {
            short resource_stored[16];
        } granary;
        struct {
            int unk_2[2];
            short progress;
            int unk_b[12];
            unsigned char has_fish;
            int unk_c[14];
            unsigned char blessing_days_left;
            unsigned char orientation;
            unsigned char has_raw_materials;
            int unk_1;
            unsigned char curse_days_left;
            int unk_6[6];
            short fishing_boat_id;
            int unk_40[40];
            unsigned char labor_state; // 0 = no laborers; 1 = present; 2 = just entered;
            unsigned char labor_days_left;
            int unk_12[12];
            unsigned char worker_id;
        } industry;
        struct {
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
            short foods_ph[8];
            short inventory[8];
            unsigned char theater;
            unsigned char amphitheater_actor;
            unsigned char amphitheater_gladiator;
            unsigned char colosseum_gladiator;
            unsigned char magistrate; // colosseum_lion
            unsigned char hippodrome;
            unsigned char school;
            unsigned char library;
            unsigned char academy;
            unsigned char barber;
            unsigned char clinic;
            unsigned char bathhouse;
            unsigned char hospital;
            unsigned char temple_ceres;
            unsigned char temple_neptune;
            unsigned char temple_mercury;
            unsigned char temple_mars;
            unsigned char temple_venus;
            unsigned char no_space_to_expand;
            unsigned char num_foods;
            unsigned char entertainment;
            unsigned char education;
            unsigned char health;
            unsigned char num_gods;
            unsigned char devolve_delay;
            unsigned char evolve_text_id;
        } house;
    } data;
    int tax_income_or_storage;
    unsigned char house_days_without_food;
    unsigned char ruin_has_plague;
    signed char desirability;
    unsigned char is_deleted;
    unsigned char is_adjacent_to_water;
    unsigned char storage_id;
    union {
        signed char house_happiness;
        signed char native_anger;
    } sentiment;
    unsigned char show_on_problem_overlay;

    ////

    // building.c
    building *main();
    building *next();
    building *top_xy();

    int is_house();
    int is_fort();
    int is_defense_ph();
    int is_farm();
    int is_floodplain_farm();
    int is_workshop();
    int is_extractor();
    int is_monument();
    int is_senate();
    int is_tax_collector();
    int is_governor_palace();
    int is_temple();
    int is_large_temple();
    int is_shrine();
    int is_guild();
    int is_beautification();
    int is_water_crossing();

    int is_industry();
    int is_food_category();
    int is_infrastructure();
    int is_administration();
    int is_religion();
    int is_entertainment();
    int is_culture();
    int is_military();

    void clear_related_data();

    // figure.c
    bool road_is_accessible;

    const int get_figureID(int i) const {
        return figure_ids_array[i];
    };
    figure *get_figure(int i);
    void set_figure(int i, int figure_id = -1);
    void set_figure(int i, figure* f);
    void remove_figure(int i);
    bool has_figure(int i, int figure_id = -1);
    bool has_figure(int i, figure* f);
    bool has_figure_of_type(int i, int _type);

    figure *create_figure_generic(int _type, int created_action, int slot, int created_dir);
    figure *create_roaming_figure(int _type, int created_action = FIGURE_ACTION_125_ROAMING, int slot = 0);
    figure *create_figure_with_destination(int _type, building *destination, int created_action = ACTION_10_GOING, int slot = 0);
    figure *create_cartpusher(int resource_id, int quantity, int created_action = FIGURE_ACTION_20_CARTPUSHER_INITIAL, int slot = 0);

    int worker_percentage();
    int figure_spawn_timer();
    void check_labor_problem();
    bool common_spawn_figure_trigger();
    void common_spawn_labor_seeker(int min_houses);
    bool common_spawn_roamer(int type, int created_action = FIGURE_ACTION_125_ROAMING);
    bool common_spawn_goods_output_cartpusher(bool only_one = true);

    void spawn_figure_work_camp();
    bool spawn_patrician(bool spawned);
    void spawn_figure_engineers_post();
    void spawn_figure_prefecture();
    void spawn_figure_police();
    void spawn_figure_actor_colony();
    void spawn_figure_gladiator_school();
    void spawn_figure_lion_house();
    void spawn_figure_chariot_maker();
    void spawn_figure_amphitheater();
    void spawn_figure_theater();
    void spawn_figure_hippodrome();
    void spawn_figure_colosseum();
    void set_market_graphic();
    void spawn_figure_market();
    void set_bathhouse_graphic();
    void spawn_figure_bathhouse();
    void spawn_figure_school();
    void spawn_figure_library();
    void spawn_figure_academy();
    void spawn_figure_barber();
    void spawn_figure_doctor();
    void spawn_figure_hospital();
    void spawn_figure_physician();
    void spawn_figure_magistrate();
    void spawn_figure_temple();
    void set_water_supply_graphic();
    void spawn_figure_watersupply();
    void set_senate_graphic();
    void spawn_figure_tax_collector();
    void spawn_figure_senate();
    void spawn_figure_mission_post();
    void spawn_figure_industry();
    void spawn_figure_wharf();
    void spawn_figure_shipyard();
    void spawn_figure_dock();
    void spawn_figure_warehouse();
    void spawn_figure_granary();
    bool can_spawn_hunter();
    void spawn_figure_hunting_lodge();
    void spawn_figure_native_hut();
    void spawn_figure_native_meeting();
    void spawn_figure_tower();
    void spawn_figure_barracks();

    void update_native_crop_progress();
    void update_road_access();
    bool figure_generate();

    // barracks.c
    void barracks_add_weapon();
    int barracks_create_soldier();
    int barracks_create_tower_sentry();
    void barracks_toggle_priority();
    int barracks_get_priority();
};

int building_find(int type);
building *building_get(int id);
building *building_create(int type, int x, int y);

void building_clear_all(void);
//void building_totals_add_corrupted_house(int unfixable);

int building_is_house(int type);
int building_is_fort(int type);
int building_is_defense_ph(int type);
int building_is_farm(int type);
int building_is_floodplain_farm(building *b);
int building_is_workshop(int type);
int building_is_extractor(int type);
int building_is_monument(int type);
int building_is_senate(int type);
int building_is_tax_collector(int type);
int building_is_governor_palace(int type);
int building_is_temple(int type);
int building_is_large_temple(int type);
int building_is_shrine(int type);
int building_is_guild(int type);
int building_is_beautification(int type);
int building_is_water_crossing(int type);

int building_is_industry(int type);
int building_is_food_category(int type);
int building_is_infrastructure(int type);
int building_is_administration(int type);
int building_is_religion(int type);
int building_is_entertainment(int type);
int building_is_culture(int type);
int building_is_military(int type);

int building_get_highest_id(void);
void building_update_highest_id(void);
void building_update_state(void);
void building_update_desirability(void);

int building_mothball_toggle(building *b);
int building_mothball_set(building *b, int value);

void building_save_state(buffer *buf, buffer *highest_id, buffer *highest_id_ever);
void building_load_state(buffer *buf, buffer *highest_id, buffer *highest_id_ever);

#endif // BUILDING_BUILDING_H
