#pragma once

#include "figuretype/figure_enemy.h"

// Enemy transports (E3b). Shared sail/disembark AI; one leaf per nation with
// FIGURE_METAINFO so figure_impl::acquire resolves instead of asserting.
// Config blocks live in src/scripts/enemies.js (figure_<nation>_transport_ship).

enum e_action_enemy_transport : uint16_t {
    ACTION_0_ENEMY_TRANSPORT_CREATED = 0,
    ACTION_1_ENEMY_TRANSPORT_SAILING = 1,
    ACTION_2_ENEMY_TRANSPORT_DISEMBARKING = 2,
    ACTION_3_ENEMY_TRANSPORT_IDLE = 3,

    ACTION_4_ENEMY_TRANSPORT_MAX
};
using e_action_enemy_transport_tokens_t = token_holder<e_action_enemy_transport, ACTION_0_ENEMY_TRANSPORT_CREATED, ACTION_4_ENEMY_TRANSPORT_MAX>;
extern const e_action_enemy_transport_tokens_t e_action_enemy_transport_tokens;

class figure_enemy_transport : public figure_enemy {
public:
    figure_enemy_transport(figure *f) : figure_enemy(f) {}
    virtual figure_enemy_transport *dcast_enemy_transport() override { return this; }

    struct runtime_data_t {
        int8_t formation_id;
        int8_t wreck_spawned;
        int16_t landing_x;
        int16_t landing_y;
        int16_t disembark_x;
        int16_t disembark_y;
        int16_t ticks;
        int16_t invasion_sequence;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override;
    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual void before_poof() override;
    virtual void kill() override;
    virtual bool is_attack() const override { return false; }
    virtual e_figure_action enemy_initial_action() const override { return (e_figure_action)ACTION_0_ENEMY_TRANSPORT_CREATED; }

    bool has_troops() const;
    int transported_formation() const;
    int invasion_sequence() const { return runtime_data().invasion_sequence; }
    void set_invasion_sequence(int seq) { runtime_data().invasion_sequence = (int16_t)seq; }
    bool load_formation(int formation_id);
    // Returns false if water_tile has no adjacent unloadable shore.
    bool sail_to_landing(tile2i water_tile);
    void disembark_troops();
    void kill_cargo();
    // Poof embarked troops + free formation (destroy-goal / cancel landing); keep hull.
    void dismiss_cargo();

private:
    // Drop formation_id if the slot was wiped / all cargo died without kill_cargo.
    void release_empty_cargo();
};

// Shared shore predicate for disembark / sea-invasion landing pick.
bool enemy_transport_land_ok(tile2i land);

// Leaf: empty static_params; ANK_CONFIG_STRUCT re-reads base fields so JS
// animations/combat stats bind to the CLSID block in enemies.js.
#define FIGURE_ENEMY_TRANSPORT_LEAF(enum_type, class_name)                                        \
    class class_name : public figure_enemy_transport {                                            \
    public:                                                                                       \
        FIGURE_METAINFO(enum_type, class_name)                                                    \
        class_name(figure *f) : figure_enemy_transport(f) {}                                      \
        struct static_params : public figure_static_params {                                      \
        } FIGURE_STATIC_DATA_T;                                                                   \
    };                                                                                            \
    ANK_CONFIG_STRUCT(class_name::static_params, max_damage, attack_value, missile_defense_value,  \
                      terrain_usage, is_enemy, category, animations)

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
