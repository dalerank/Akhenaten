#pragma once

#include "figuretype/figure_enemy.h"

// Enemy warships (E3a). Shared water combat AI; one leaf per nation with
// FIGURE_METAINFO so figure_impl::acquire resolves instead of asserting.
// Config blocks live in src/scripts/enemies.js (figure_<nation>_war_ship).

enum e_action_enemy_warship : uint16_t {
    ACTION_0_ENEMY_WARSHIP_CREATED = 0,
    ACTION_1_ENEMY_WARSHIP_IDLE = 1,
    ACTION_2_ENEMY_WARSHIP_PURSUING = 2,
    ACTION_3_ENEMY_WARSHIP_ATTACK = 3,

    ACTION_4_ENEMY_WARSHIP_MAX
};
using e_action_enemy_warship_tokens_t = token_holder<e_action_enemy_warship, ACTION_0_ENEMY_WARSHIP_CREATED, ACTION_4_ENEMY_WARSHIP_MAX>;
extern const e_action_enemy_warship_tokens_t e_action_enemy_warship_tokens;

class figure_enemy_warship : public figure_enemy {
public:
    figure_enemy_warship(figure *f) : figure_enemy(f) {}
    virtual figure_enemy_warship *dcast_enemy_warship() override { return this; }

    struct runtime_data_t {
        short target_id;
        int16_t invasion_sequence;
        int8_t wreck_spawned;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override;
    virtual void figure_action() override;
    virtual void update_animation() override;
    virtual void kill() override;
    virtual bool is_attack() const override;
    virtual e_figure_action enemy_initial_action() const override { return (e_figure_action)ACTION_0_ENEMY_WARSHIP_CREATED; }

    int invasion_sequence() const { return runtime_data().invasion_sequence; }
    void set_invasion_sequence(int seq) { runtime_data().invasion_sequence = (int16_t)seq; }

    figure_id find_combat_target(int max_distance);
    void combat_tick_vs_target(figure *target, int max_pursue_distance);
    void launch_missile_at(figure *target);
    void ram_target(figure *target);
    void check_sink();
};

// Leaf: empty static_params; ANK_CONFIG_STRUCT re-reads base fields so JS
// animations/combat stats bind to the CLSID block in enemies.js.
#define FIGURE_ENEMY_WARSHIP_LEAF(enum_type, class_name)                                          \
    class class_name : public figure_enemy_warship {                                              \
    public:                                                                                       \
        FIGURE_METAINFO(enum_type, class_name)                                                    \
        class_name(figure *f) : figure_enemy_warship(f) {}                                        \
        struct static_params : public figure_static_params {                                      \
        } FIGURE_STATIC_DATA_T;                                                                   \
    };                                                                                            \
    ANK_CONFIG_STRUCT(class_name::static_params, max_damage, attack_value, missile_defense_value,  \
                      terrain_usage, is_enemy, category, animations)

FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_WARSHIP, figure_enemy_warship_generic)
FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_ASSYRIAN_WAR_SHIP, figure_assyrian_war_ship)
FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_CANAANITE_WAR_SHIP, figure_canaanite_war_ship)
FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_EGYPTIAN_GALERA, figure_egyptian_galera)
FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_EGYPTIAN_WAR_SHIP, figure_egyptian_war_ship)
FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_HITTITE_WAR_SHIP, figure_hittite_war_ship)
FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_HYKSOS_WAR_SHIP, figure_hyksos_war_ship)
FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_KUSHITE_WAR_SHIP, figure_kushite_war_ship)
FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_LIBIAN_WAR_SHIP, figure_libian_war_ship)
FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_NUBIAN_WAR_SHIP, figure_nubian_war_ship)
FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_PERSIAN_WAR_SHIP, figure_persian_war_ship)
FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_PHOENICIAN_WAR_SHIP, figure_phoenician_war_ship)
FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_ROMAN_WAR_SHIP, figure_roman_war_ship)
FIGURE_ENEMY_WARSHIP_LEAF(FIGURE_ENEMY_SEAPEOPLE_WAR_SHIP, figure_seapeople_war_ship)

#undef FIGURE_ENEMY_WARSHIP_LEAF

e_figure_type enemy_warship_type_for(e_enemy_type enemy);
