#pragma once

#include "core/svector.h"
#include "figuretype/figure_enemy.h"
#include "scenario/scenario_invasion.h"

// OG figure/enemy_ships.c figure_enemy_transport_action (FIG_ENEMY_TRANSPORT). The ship carries a soldier
// count, not figures: the soldiers are created as formations when it reaches its landing point.
// Config blocks live in src/scripts/enemies.js (figure_<nation>_transport_ship, enemy_transport_rules).

enum e_action_enemy_transport : uint16_t {
    ACTION_8_ENEMY_TRANSPORT_WAITING = 8,
    ACTION_9_ENEMY_TRANSPORT_MOVING = 9,
    ACTION_10_ENEMY_TRANSPORT_EVADING = 10,
    ACTION_12_ENEMY_TRANSPORT_IDLE = 12,
    ACTION_13_ENEMY_TRANSPORT_GOING_TO_LANDING = 13,
    ACTION_17_ENEMY_TRANSPORT_LEAVING = 17,

    ACTION_18_ENEMY_TRANSPORT_MAX
};
using e_action_enemy_transport_tokens_t
  = token_holder<e_action_enemy_transport, ACTION_8_ENEMY_TRANSPORT_WAITING, ACTION_18_ENEMY_TRANSPORT_MAX>;
extern const e_action_enemy_transport_tokens_t e_action_enemy_transport_tokens;

// OG warship_secondary_action values the transport uses while evading.
enum e_enemy_transport_secondary : uint8_t {
    ENEMY_TRANSPORT_SECONDARY_FOLLOW_TARGET = 9,
    ENEMY_TRANSPORT_SECONDARY_WAITING = 16,
};

struct enemy_transport_rules_t {
    int16_t soldiers_per_ship;
    int16_t launch_first_wait;
    int16_t launch_wait_step;
    int16_t landing_wait;
    int16_t evade_wait;
    int16_t evade_ticks;
    int16_t evade_range;
    int16_t damaged_percent;
    int16_t reroute_ticks;
    int16_t sinking_ticks;
    int16_t escape_distance;
};
ANK_CONFIG_STRUCT(enemy_transport_rules_t, soldiers_per_ship, launch_first_wait, launch_wait_step, landing_wait,
  evade_wait, evade_ticks, evade_range, damaged_percent, reroute_ticks, sinking_ticks, escape_distance)

extern enemy_transport_rules_t enemy_transport_rules;

class figure_enemy_transport : public figure_enemy {
public:
    figure_enemy_transport(figure *f) : figure_enemy(f) {}
    virtual figure_enemy_transport *dcast_enemy_transport() override { return this; }

    // OG figure_movement_move_ticks(speed) as the walk ticks of each tick of its cycle.
    struct transport_params_t {
        svector<uint8_t, 4> move_cycle;
    };

    struct runtime_data_t {
        int16_t landing_x;
        int16_t landing_y;
        int16_t soldiers;
        int16_t invasion_id;
        int16_t invasion_sequence;
        uint8_t nation;
        uint8_t kind;
        uint8_t attack_type;
        uint8_t has_troops;
        uint8_t secondary_action;
        uint8_t move_counter;
        uint8_t reroute_ticks;
        uint8_t moving;
    } FIGURE_RUNTIME_DATA_T;

    virtual const transport_params_t& transport_params() const = 0;

    virtual void on_create() override;
    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual bool is_attack() const override { return false; }

    // OG invasion_ship_launch + the soldier fields set by invasion_start_sea.
    void launch(const invasion_opts_t& opts, int soldiers, tile2i landing, int wait_ticks, int invasion_sequence);

    bool has_troops() const { return runtime_data().has_troops != 0; }
    int soldiers() const { return runtime_data().soldiers; }
    int invasion_id() const { return runtime_data().invasion_id; }
    int invasion_sequence() const { return runtime_data().invasion_sequence; }
    tile2i landing() const { return tile2i(runtime_data().landing_x, runtime_data().landing_y); }

private:
    void move();
    void action_wait();
    void action_move();
    void action_evade();
    void action_go_to_landing();
    void action_go_away();
    void unload(tile2i land);
};

// Leaf: OG figure_properties for the nation's ENEMY_MODEL_TRANSPORT_SHIP row (max_damage, missile_defense,
// speed as move_cycle); ANK_CONFIG_STRUCT re-reads base fields so JS animations bind to the CLSID block.
#define FIGURE_ENEMY_TRANSPORT_LEAF(enum_type, class_name)                                                       \
    class class_name : public figure_enemy_transport {                                                           \
    public:                                                                                                      \
        FIGURE_METAINFO(enum_type, class_name)                                                                   \
        class_name(figure* f) : figure_enemy_transport(f) {                                                      \
        }                                                                                                        \
        struct static_params : public transport_params_t, public figure_static_params {                          \
        } FIGURE_STATIC_DATA_T;                                                                                  \
        virtual const transport_params_t& transport_params() const override {                                    \
            return current_params();                                                                             \
        }                                                                                                        \
    };                                                                                                           \
    ANK_CONFIG_STRUCT(class_name::static_params, max_damage, attack_value, missile_defense_value, terrain_usage, \
      is_enemy, category, animations, move_cycle)

FIGURE_ENEMY_TRANSPORT_LEAF(FIGURE_ENEMY_TRANSPORT, figure_enemy_transport_generic)
FIGURE_ENEMY_TRANSPORT_LEAF(FIGURE_ENEMY_EGYPTIAN_TRANSPORT_SHIP, figure_egyptian_transport_ship)
FIGURE_ENEMY_TRANSPORT_LEAF(FIGURE_ENEMY_BARBARIAN_TRANSPORT_SHIP, figure_barbarian_transport_ship)
FIGURE_ENEMY_TRANSPORT_LEAF(FIGURE_ENEMY_ASSYRIAN_TRANSPORT_SHIP, figure_assyrian_transport_ship)
FIGURE_ENEMY_TRANSPORT_LEAF(FIGURE_ENEMY_CANAANITE_TRANSPORT_SHIP, figure_canaanite_transport_ship)
FIGURE_ENEMY_TRANSPORT_LEAF(FIGURE_ENEMY_HITTITE_TRANSPORT_SHIP, figure_hittite_transport_ship)
FIGURE_ENEMY_TRANSPORT_LEAF(FIGURE_ENEMY_HYKSOS_TRANSPORT_SHIP, figure_hyksos_transport_ship)
FIGURE_ENEMY_TRANSPORT_LEAF(FIGURE_ENEMY_KUSHITE_TRANSPORT_SHIP, figure_kushite_transport_ship)
FIGURE_ENEMY_TRANSPORT_LEAF(FIGURE_ENEMY_LIBIAN_TRANSPORT_SHIP, figure_libian_transport_ship)
FIGURE_ENEMY_TRANSPORT_LEAF(FIGURE_ENEMY_NUBIAN_TRANSPORT_SHIP, figure_nubian_transport_ship)
FIGURE_ENEMY_TRANSPORT_LEAF(FIGURE_ENEMY_PERSIAN_TRANSPORT_SHIP, figure_persian_transport_ship)
FIGURE_ENEMY_TRANSPORT_LEAF(FIGURE_ENEMY_PHOENICIAN_TRANSPORT_SHIP, figure_phoenician_transport_ship)
FIGURE_ENEMY_TRANSPORT_LEAF(FIGURE_ENEMY_ROMAN_TRANSPORT_SHIP, figure_roman_transport_ship)
FIGURE_ENEMY_TRANSPORT_LEAF(FIGURE_ENEMY_SEAPEOPLE_TRANSPORT_SHIP, figure_seapeople_transport_ship)

#undef FIGURE_ENEMY_TRANSPORT_LEAF

e_figure_type enemy_transport_type_for(e_enemy_type enemy);

// OG ship_find_ship_at: the first player transport, warship or fishing boat on the tile other than `self`.
figure_id enemy_ship_player_ship_at(tile2i tile, figure_id self);
// OG ship_find_closest(any = 1): the nearest of those ships in the size x size square around `center`.
figure_id enemy_ship_closest_player_ship(tile2i center, figure_id self, int size);

// OG event_manager.c invasion_has_transport_ship: an enemy transport of the invasion is still on the map.
bool enemy_transport_of_invasion_exists(int invasion_id);
// A transport of the invasion still carries its soldiers.
bool enemy_transport_of_invasion_loaded(int invasion_id);
