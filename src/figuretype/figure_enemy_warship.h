#pragma once

#include "core/svector.h"
#include "figuretype/figure_enemy.h"

// OG figure/enemy_ships.c figure_enemy_warship_action (FIG_ENEMY_WARSHIP) and figure_egyptian_warship_action.
// One leaf per nation; config blocks live in src/scripts/enemies.js (figure_<nation>_war_ship, enemy_warship_rules).

enum e_action_enemy_warship : uint16_t {
    ACTION_8_ENEMY_WARSHIP_WAITING = 8,
    ACTION_9_ENEMY_WARSHIP_RAMMING = 9,
    ACTION_10_ENEMY_WARSHIP_ATTACKING = 10,
    ACTION_11_ENEMY_WARSHIP_MOVING = 11,
    ACTION_12_ENEMY_WARSHIP_EVADING = 12,
    ACTION_17_ENEMY_WARSHIP_PATROLLING = 17,
    ACTION_18_ENEMY_WARSHIP_LEAVING = 18,

    ACTION_19_ENEMY_WARSHIP_MAX
};
using e_action_enemy_warship_tokens_t
  = token_holder<e_action_enemy_warship, ACTION_8_ENEMY_WARSHIP_WAITING, ACTION_19_ENEMY_WARSHIP_MAX>;
extern const e_action_enemy_warship_tokens_t e_action_enemy_warship_tokens;

// OG warship_secondary_action values (ships_player.h warship_mode).
enum e_enemy_warship_secondary : uint8_t {
    ENEMY_WARSHIP_SECONDARY_FOLLOW_TARGET = 9,
    ENEMY_WARSHIP_SECONDARY_SAILING = 11,
    ENEMY_WARSHIP_SECONDARY_WAITING = 16,
};

// OG military.h ship_move_mode.
enum e_enemy_warship_move_mode : uint8_t {
    ENEMY_WARSHIP_MOVE_FULL_SPEED = 0,
    ENEMY_WARSHIP_MOVE_SLOW = 1,
    ENEMY_WARSHIP_MOVE_RESTING = 2,
};

// OG figure_movement_move_ticks: the walk ticks of each tick of the cycle of one speed value.
struct enemy_ship_speed_cycle_t {
    svector<uint8_t, 4> ticks;
};
ANK_CONFIG_STRUCT(enemy_ship_speed_cycle_t, ticks)

// OG figure_ship_direction_table: one row per target heading, the ram divisor per own heading.
struct enemy_ship_ram_divisor_row_t {
    svector<uint8_t, 8> own;
};
ANK_CONFIG_STRUCT(enemy_ship_ram_divisor_row_t, own)

struct enemy_warship_rules_t {
    int16_t launch_first_wait;
    int16_t launch_wait_step;
    int16_t reroute_ticks;
    int16_t damaged_percent;
    int16_t sinking_ticks;
    int16_t stay_months;
    int16_t attack_ticks;
    int16_t patrol_base_ticks;
    int16_t patrol_random_ticks;
    int16_t docked_target_reduction;
    int16_t ram_cooldown;
    int16_t evade_ticks;
    int16_t evade_range;
    int16_t escape_distance;
    int16_t shoot_ticks;
    int16_t fast_ram_percent;
    int16_t slow_speed_percent;
    int16_t full_speed_max;
    int16_t mode_change_ticks;
    int16_t score_land_enemy;
    int16_t score_boat;
    int16_t score_transport;
    int16_t score_loaded_transport;
    int16_t score_warship;
    svector<enemy_ship_speed_cycle_t, 20> speed_cycles;
    svector<enemy_ship_ram_divisor_row_t, 8> ram_divisors;
};
ANK_CONFIG_STRUCT(enemy_warship_rules_t, launch_first_wait, launch_wait_step, reroute_ticks, damaged_percent,
  sinking_ticks, stay_months, attack_ticks, patrol_base_ticks, patrol_random_ticks, docked_target_reduction,
  ram_cooldown, evade_ticks, evade_range, escape_distance, shoot_ticks, fast_ram_percent, slow_speed_percent,
  full_speed_max, mode_change_ticks, score_land_enemy, score_boat, score_transport, score_loaded_transport,
  score_warship, speed_cycles, ram_divisors)

extern enemy_warship_rules_t enemy_warship_rules;

class figure_enemy_warship : public figure_enemy {
public:
    figure_enemy_warship(figure *f) : figure_enemy(f) {}
    virtual figure_enemy_warship *dcast_enemy_warship() override { return this; }

    // OG figure_properties of the nation's ENEMY_MODEL_WARSHIP row: max_damage as the ship's hit points (kept
    // apart from figure max_damage, which the engine raises from 0 to 100), speed, ship_steps, ship_moves.
    struct warship_params_t {
        uint16_t hit_points;
        uint8_t speed;
        uint8_t ship_steps;
        uint16_t ship_moves;
    };

    // The first three fields keep the slots of the remake layout.
    struct runtime_data_t {
        int16_t target_id;
        int16_t invasion_sequence;
        uint8_t moving;
        uint8_t secondary_action;
        uint8_t move_mode;
        uint8_t ram_cooldown;
        uint16_t move_count;
        uint16_t move_steps;
        int16_t step_x;
        int16_t step_y;
        uint8_t leave_month;
        uint8_t reroute_ticks;
        uint8_t speed_counter;
    } FIGURE_RUNTIME_DATA_T;

    virtual const warship_params_t& warship_params() const = 0;
    // OG figure_egyptian_warship_action: no city enemy count and no shooting.
    virtual bool egyptian_action() const { return false; }

    virtual void on_create() override;
    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual bool is_attack() const override;

    // OG invasion_ship_launch + figure_enemy_ship_init for a warship of invasion_start_sea.
    void launch(int wait_ticks, int invasion_sequence);

    int invasion_sequence() const { return runtime_data().invasion_sequence; }

private:
    void move_ticks_at_speed(int speed);
    void ship_move(bool cautious);
    void shoot();
    void fire_missile_at(tile2i target);
    figure_id find_target(int range) const;
    figure_id find_ram_target() const;
    void action_wait();
    void action_move();
    void action_ram();
    void action_evade();
    void action_attack();
    void action_patrol();
    void action_leave();
};

// Leaf: OG figure_properties for the nation's ENEMY_MODEL_WARSHIP row (max_damage, attack = slow ram damage,
// missile stats, speed, ship_steps, ship_moves); ANK_CONFIG_STRUCT re-reads base fields so JS animations bind.
#define FIGURE_ENEMY_WARSHIP_LEAF(enum_type, class_name, egyptian)                                                   \
    class class_name : public figure_enemy_warship {                                                                 \
    public:                                                                                                          \
        FIGURE_METAINFO(enum_type, class_name)                                                                       \
        class_name(figure* f) : figure_enemy_warship(f) {                                                            \
        }                                                                                                            \
        struct static_params : public warship_params_t, public figure_static_params {                                \
        } FIGURE_STATIC_DATA_T;                                                                                      \
        virtual const warship_params_t& warship_params() const override {                                            \
            return current_params();                                                                                 \
        }                                                                                                            \
        virtual bool egyptian_action() const override {                                                              \
            return egyptian;                                                                                         \
        }                                                                                                            \
    };                                                                                                               \
    ANK_CONFIG_STRUCT(class_name::static_params, max_damage, attack_value, missile_defense_value,                    \
      missile_attack_value, missile_range, missile_delay, terrain_usage, is_enemy, category, animations, hit_points, \
      speed, ship_steps, ship_moves)

FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_WARSHIP, figure_enemy_warship_generic, false)
FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_ASSYRIAN_WAR_SHIP, figure_assyrian_war_ship, false)
FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_CANAANITE_WAR_SHIP, figure_canaanite_war_ship, false)
FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_EGYPTIAN_GALERA, figure_egyptian_galera, true)
FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_EGYPTIAN_WAR_SHIP, figure_egyptian_war_ship, true)
FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_HITTITE_WAR_SHIP, figure_hittite_war_ship, false)
FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_HYKSOS_WAR_SHIP, figure_hyksos_war_ship, false)
FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_KUSHITE_WAR_SHIP, figure_kushite_war_ship, false)
FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_LIBIAN_WAR_SHIP, figure_libian_war_ship, false)
FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_NUBIAN_WAR_SHIP, figure_nubian_war_ship, false)
FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_PERSIAN_WAR_SHIP, figure_persian_war_ship, false)
FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_PHOENICIAN_WAR_SHIP, figure_phoenician_war_ship, false)
FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_ROMAN_WAR_SHIP, figure_roman_war_ship, false)
FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_SEAPEOPLE_WAR_SHIP, figure_seapeople_war_ship, false)

#undef FIGURE_ENEMY_WARSHIP_LEAF

e_figure_type enemy_warship_type_for(e_enemy_type enemy);
