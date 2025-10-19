#pragma once

#include "core/buffer.h"
#include "figure/figure_type.h"
#include "game/game_environment.h"
#include "grid/point.h"
#include "core/tokenum.h"

constexpr uint8_t MAX_BATALIONS = 6;

enum e_batalion_recruit_type {
    BATALION_RECRUIT_NONE = 0,
    BATALION_RECRUIT_ARCHER = 1,
    BATALION_RECRUIT_CHARIOTEER = 2,
    BATALION_RECRUIT_INFANTRY = 3 
};

enum e_formation_attack_type {
    FORMATION_ATTACK_FOOD_CHAIN = 0,
    FORMATION_ATTACK_GOLD_STORES = 1,
    FORMATION_ATTACK_BEST_BUILDINGS = 2,
    FORMATION_ATTACK_TROOPS = 3,
    FORMATION_ATTACK_SIMPLE = 4,
    FORMATION_ATTACK_RANDOM = 5,

    FORMATION_ATTACK_MAX
};

enum e_formation_layout {
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

    FORMATION_LAYOUT_COUNT
};
using e_formation_layout_tokens_t = token_holder<e_formation_layout, FORMATION_COLUMN, FORMATION_LAYOUT_COUNT>;
extern const e_formation_layout_tokens_t e_formation_layout_tokens;

struct formation_state {
    int duration_halt;
    int duration_advance;
    int duration_regroup;
};

using formation_id = uint8_t;

struct formation {
    enum {
        max_figures_count = 16
    };
    formation_id id;         /**< ID of the formation */
    uint8_t faction_id; /**< 1 = player, 0 = everyone else */

    /* General variables */
    bool in_use;    /**< Flag whether this entry is in use */
    bool is_herd;   /**< Flag to indicate herd */
    bool own_batalion; /**< Flag to indicate (own) legion */
    uint8_t batalion_id; /**< Batalion ID (0-5 for own troops) */
    e_formation_layout layout;
    uint8_t direction;
    uint8_t orientation;

    int16_t morale;
    uint8_t months_from_home;
    uint8_t months_low_morale;
    uint8_t months_very_low_morale;

    /* Figures */
    e_figure_type figure_type;          /**< Type of figure in this formation */
    uint8_t num_figures;                    /**< Current number of figures in the formation */
    uint8_t max_figures;                    /**< Maximum number of figures */
    uint16_t figures[max_figures_count];     /**< Figure IDs */
    int16_t total_damage;                   /**< Total damage of all figures added */
    int16_t max_total_damage;               /**< Maximum total damage of all figures added */

    /* Position */
    tile2i tile;
    tile2i home;
    uint16_t building_id;
    tile2i standard_tile;
    uint16_t standard_figure_id;
    tile2i destination;
    uint16_t destination_building_id;

    /* Movement */
    int16_t wait_ticks;
    bool is_halted;
    int8_t recent_fight;
    uint8_t unknown_fired;
    int16_t missile_fired;
    int16_t missile_attack_timeout;
    int16_t missile_attack_formation_id;

    /* Legion-related */
    uint8_t empire_service;        /**< Flag to indicate this batalion is selected for empire service */
    uint8_t in_distant_battle;     /**< Flag to indicate this batalion is away in a distant battle */
    int16_t cursed_by_seth;        /**< Flag to indicate this batalion is cursed */
    uint8_t has_military_training; /**< Flag to indicate this batalion has had military training */
    uint8_t batalion_recruit_type;   /**< Recruit type: none if this batalion is fully occupied */
    bool is_at_fort;            /**< Flag to indicate this batalion is resting at the fort */

    /* Enemy-related */
    e_enemy_type enemy_type;
    int enemy_legion_index;
    e_formation_attack_type attack_type;
    int invasion_id;
    int invasion_sequence;
    formation_state enemy_state;

    /* Herd-related */
    uint8_t herd_direction;
    uint8_t failed_creation_count;
    uint8_t herd_ostrich_spawn_delay;

    struct {
        e_formation_layout layout;
        tile2i home;
    } prev;

    void set_destination_building(tile2i tile, int building_id);
    const bool valid() const { return id != 0; }
};

void formations_clear(void);

void formation_clear(int formation_id);

int formation_create_herd(e_figure_type figure_type, tile2i tile, int num_animals);
int formation_create_enemy(e_figure_type figure_type, tile2i tile, e_formation_layout layout, int orientation, e_enemy_type enemy_type, e_formation_attack_type attack_type, int invasion_id, int invasion_sequence);

formation* formation_get(int formation_id);
formation *formation_get_free(int start_index);

template<typename F>
inline void formations_foreach(F func) {
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation* m = formation_get(i);
        if (m->in_use) {
            func(m);
        }
    }
}

template<typename T, typename F>
inline void formations_get(T& arr, F func) {
    formations_foreach([&] (auto *m) {
        if (func(m)) {
            arr.push_back(m);
        }
    });
}

void formation_toggle_empire_service(int formation_id);

void formation_record_missile_fired(formation* m);
void formation_record_missile_attack(formation* m, int from_formation_id);
void formation_record_fight(formation* m);

int formation_grid_offset_for_invasion(int invasion_sequence);

void formation_kingdome_pause(void);
void formation_kingdome_retreat(void);

int formation_get_num_forts_cached(void);
void formation_calculate_legion_totals(void);

int formation_get_num_forts();
int formation_get_max_forts();

int formation_for_legion(int legion_index);

void formation_change_morale(formation* m, int amount);
bool formation_has_low_morale(formation* m);
void formation_update_morale_after_death(formation* m);

void formation_update_monthly_morale_deployed(void);
void formation_update_monthly_morale_at_rest(void);
void formation_decrease_monthly_counters(formation* m);
void formation_clear_monthly_counters(formation* m);

void formation_set_destination(formation* m, tile2i tile);
void formation_set_home(formation* m, tile2i tile);

void formation_clear_figures(void);
int formation_add_figure(int formation_id, int figure_id, int deployed, int damage, int max_damage);

void formation_move_herds_away(tile2i tile);

void formation_calculate_figures(void);

void formation_update_all(bool second_time);
int formation_rioter_get_target_building(int* x_tile, int* y_tile);
