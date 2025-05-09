#pragma once

#include "core/buffer.h"
#include "figure/figure_type.h"
#include "grid/point.h"

// #define MAX_FORMATIONS 250

#define MAX_LEGIONS 6
#define MAX_FORMATION_FIGURES 16

enum {
    LEGION_RECRUIT_NONE = 0,
    LEGION_RECRUIT_ARCHER = 1,
    LEGION_RECRUIT_CHARIOTEER = 2,
    LEGION_RECRUIT_INFANTRY = 3 };

enum {
    FORMATION_ATTACK_FOOD_CHAIN = 0,
    FORMATION_ATTACK_GOLD_STORES = 1,
    FORMATION_ATTACK_BEST_BUILDINGS = 2,
    FORMATION_ATTACK_TROOPS = 3,
    FORMATION_ATTACK_RANDOM = 4
};

enum formation_layout {
    FORMATION_COLUMN = 0,
    FORMATION_DOUBLE_LINE_1 = 1,
    FORMATION_DOUBLE_LINE_2 = 2,
    FORMATION_SINGLE_LINE_1 = 3,
    FORMATION_SINGLE_LINE_2 = 4,
    FORMATION_TORTOISE = 5,
    FORMATION_MOP_UP = 6,
    FORMATION_AT_REST = 7,
    FORMATION_ENEMY_MOB = 8,
    FORMATION_HERD = 9,
    FORMATION_ENEMY_DOUBLE_LINE = 10,
    FORMATION_ENEMY_WIDE_COLUMN = 11,
    FORMATION_ENEMY12 = 12,
};

struct formation_state {
    int duration_halt;
    int duration_advance;
    int duration_regroup;
};

struct formation {
    int id;         /**< ID of the formation */
    int faction_id; /**< 1 = player, 0 = everyone else */

    /* General variables */
    int in_use;    /**< Flag whether this entry is in use */
    int is_herd;   /**< Flag to indicate herd */
    int is_legion; /**< Flag to indicate (own) legion */
    int legion_id; /**< Legion ID (0-5 for own troops) */
    formation_layout layout;
    int direction;
    int orientation;

    int morale;
    int months_from_home;
    int months_low_morale;
    int months_very_low_morale;

    /* Figures */
    e_figure_type figure_type;          /**< Type of figure in this formation */
    int num_figures;                    /**< Current number of figures in the formation */
    int max_figures;                    /**< Maximum number of figures */
    int figures[MAX_FORMATION_FIGURES]; /**< Figure IDs */
    int total_damage;                   /**< Total damage of all figures added */
    int max_total_damage;               /**< Maximum total damage of all figures added */

    /* Position */
    tile2i tile;
    tile2i home;
    int building_id;
    tile2i standard_tile;
    int standard_figure_id;
    int destination_x;
    int destination_y;
    int destination_building_id;

    /* Movement */
    int wait_ticks;
    int is_halted;
    int recent_fight;
    int unknown_fired;
    int missile_fired;
    int missile_attack_timeout;
    int missile_attack_formation_id;

    /* Legion-related */
    int empire_service;        /**< Flag to indicate this legion is selected for empire service */
    int in_distant_battle;     /**< Flag to indicate this legion is away in a distant battle */
    int cursed_by_seth;        /**< Flag to indicate this legion is cursed */
    int has_military_training; /**< Flag to indicate this legion has had military training */
    int legion_recruit_type;   /**< Recruit type: none if this legion is fully occupied */
    int is_at_fort;            /**< Flag to indicate this legion is resting at the fort */

    /* Enemy-related */
    int enemy_type;
    int enemy_legion_index;
    int attack_type;
    int invasion_id;
    int invasion_sequence;
    formation_state enemy_state;

    /* Herd-related */
    uint8_t herd_direction;
    uint8_t failed_creation_count;
    int herd_ostrich_spawn_delay;

    struct {
        formation_layout layout;
        int x_home;
        int y_home;
    } prev;
};

void formations_clear(void);

void formation_clear(int formation_id);

formation* formation_create_legion(int building_id, int x, int y, e_figure_type type);
int formation_create_herd(e_figure_type figure_type, tile2i tile, int num_animals);
int formation_create_enemy(e_figure_type figure_type, tile2i tile, formation_layout layout, int orientation, int enemy_type, int attack_type, int invasion_id, int invasion_sequence);

formation* formation_get(int formation_id);

void formation_toggle_empire_service(int formation_id);

void formation_record_missile_fired(formation* m);
void formation_record_missile_attack(formation* m, int from_formation_id);
void formation_record_fight(formation* m);

int formation_grid_offset_for_invasion(int invasion_sequence);

void formation_caesar_pause(void);

void formation_caesar_retreat(void);

int formation_get_num_forts_cached(void);
void formation_calculate_legion_totals(void);

int formation_get_num_forts();
int formation_get_max_forts();

int formation_for_legion(int legion_index);

void formation_change_morale(formation* m, int amount);
int formation_has_low_morale(formation* m);
void formation_update_morale_after_death(formation* m);

void formation_update_monthly_morale_deployed(void);
void formation_update_monthly_morale_at_rest(void);
void formation_decrease_monthly_counters(formation* m);
void formation_clear_monthly_counters(formation* m);

void formation_set_destination(formation* m, tile2i tile);
void formation_set_destination_building(formation* m, int x, int y, int building_id);
void formation_set_home(formation* m, tile2i tile);

void formation_clear_figures(void);
int formation_add_figure(int formation_id, int figure_id, int deployed, int damage, int max_damage);

void formation_move_herds_away(tile2i tile);

void formation_calculate_figures(void);

void formation_update_all(bool second_time);
int formation_rioter_get_target_building(int* x_tile, int* y_tile);
