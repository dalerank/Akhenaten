#pragma once

#include "figure/figure_type.h"
#include "graphics/animation.h"
#include "sound/sound_walker.h"
#include "building/building_fwd.h"
#include "city/constants.h"

struct figure_static_params {
    static figure_static_params dummy;

    e_figure_type ftype;
    pcstr name;

    int8_t terrain_usage;
    animations_t animations;
    figure_sounds_t sounds;
    uint16_t max_roam_length;
    uint8_t speed_mult;
    metainfo meta;
    e_permission permission;
    bool is_enemy;
    bool is_soldier;
    bool use_cart;
    e_figure_category category;
    uint16_t max_damage;
    int8_t attack_value;
    int8_t defense_value;
    int8_t missile_defense_value;
    uint16_t corpse_time_delay;
    bool render_on_flat_tiles;

    static void set(e_figure_type, const figure_static_params &);
    static const figure_static_params &get(e_figure_type);
    static figure_static_params &ref(e_figure_type);

    void initialize();
};
ANK_CONFIG_STRUCT(figure_static_params, terrain_usage,  animations, sounds,
    max_roam_length, speed_mult, meta, permission, is_enemy, is_soldier, use_cart,
    category, attack_value, defense_value, missile_defense_value, corpse_time_delay,
    render_on_flat_tiles)
