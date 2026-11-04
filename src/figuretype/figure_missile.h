#pragma once

#include "figure/figure.h"
#include "sound/effect.h"
#include "core/archive.h"

struct formation;

// OG missiles.c / missiles.h combat + image constants.
struct missile_rules_t {
    int16_t speed = 4;
    int16_t flight_ticks = 120;
    int16_t max_defense = 20;
    int16_t damage_base = 30;
    int16_t arrow_image_offset = 16;
    int16_t bolt_image_offset = 32;
    int16_t image_directions = 16;
    int16_t spear_image_directions = 32;
    int16_t spear_orientation_mult = 4;
    int16_t facing_away_penalty = 4;
    int16_t single_line_bonus = 4;
    int16_t mop_up_penalty = 2;
    int16_t attack_timeout = 6;
    int16_t docked_warship_bonus = 2;
};
ANK_CONFIG_STRUCT(missile_rules_t,
    speed, flight_ticks, max_defense, damage_base, arrow_image_offset, bolt_image_offset, image_directions,
    spear_image_directions, spear_orientation_mult, facing_away_penalty, single_line_bonus, mop_up_penalty,
    attack_timeout, docked_warship_bonus)

extern missile_rules_t missile_rules;

// OG animals_internal.h hunter spear flight.
struct hunter_spear_rules_t {
    int16_t speed = 3;
    int16_t flight_ticks = 104;
    int16_t image_directions = 32;
    int16_t orientation_mult = 4;
};
ANK_CONFIG_STRUCT(hunter_spear_rules_t, speed, flight_ticks, image_directions, orientation_mult)
extern hunter_spear_rules_t hunter_spear_rules;

// Shared OG missiles.c combat helpers (arrow + bolt).
int missile_og_defense(figure *target, formation *legion, int defense);
int missile_og_damage(int attack, int defense);

class figure_missile : public figure_impl {
public:
    figure_missile(figure *f) : figure_impl(f) {}
    virtual figure_missile* dcast_missile() override { return this; }

    struct runtime_data_t {
        int8_t missile_attack_value;
        int8_t image_direction;
        figure_id shooter_id;
    } FIGURE_RUNTIME_DATA_T;

    virtual void on_create() override;
    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual void main_image_update() override;
    virtual void cart_image_update() override;
    virtual e_sound_effect hit_sound_effect() const { return SOUND_EFFECT_ARROW_HIT; }

    figure_id get_non_citizen_on_tile();
    figure_id get_citizen_on_tile();
    void missile_hit_figure(figure_id target_id, int legionary_type);
    void missile_hit_building(building_id target_id);
    void set_image_direction(vec2i src, vec2i dst);
    figure* shooter() const;

    static figure_missile* create(figure_id building_id, tile2i tile, tile2i dst, e_figure_type type);
};

// OG FIG_HUNTER_SPEAR (74): marks herd prey HUNTED, does not apply HP damage.
class figure_hunter_arrow : public figure_missile {
public:
    FIGURE_METAINFO(FIGURE_HUNTER_ARROW, figure_hunter_arrow)
    figure_hunter_arrow(figure *f) : figure_missile(f) {}

    virtual void figure_action() override;
    virtual void main_image_update() override;
    virtual e_sound_effect hit_sound_effect() const override { return SOUND_EFFECT_JAVELIN; }
};

class figure_arrow : public figure_missile {
public:
    FIGURE_METAINFO(FIGURE_ARROW, figure_arrow)
    figure_arrow(figure *f) : figure_missile(f) {}

    virtual void figure_action() override;
    virtual void main_image_update() override;
};

class figure_spear : public figure_missile {
public:
    FIGURE_METAINFO(FIGURE_SPEAR, figure_spear)
    figure_spear(figure *f) : figure_missile(f) {}

    virtual void figure_action() override;
    virtual void main_image_update() override;
    virtual e_sound_effect hit_sound_effect() const override { return SOUND_EFFECT_JAVELIN; }
};

class figure_antelope_hunter_javelin : public figure_missile {
public:
    FIGURE_METAINFO(FIGURE_ANTELOPE_HUNTER_JAVELIN, figure_antelope_hunter_javelin)
    figure_antelope_hunter_javelin(figure *f) : figure_missile(f) {}

    virtual void figure_action() override;
    virtual void main_image_update() override;
    virtual e_sound_effect hit_sound_effect() const override { return SOUND_EFFECT_JAVELIN; }
};

// Shared OG hunter-spear flight/hit (ostrich/birds/antelope → HUNTED).
void hunter_spear_figure_action(figure_missile *missile);
void hunter_spear_main_image_update(figure_missile *missile);