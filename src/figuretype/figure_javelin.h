#pragma once

#include "figuretype/figure_missile.h"
#include "core/archive.h"

// OG military.c figure_javelin_action constants (FIG_PLAYER_MISSILE).
struct javelin_rules_t {
    int16_t speed = 4;
    int16_t flight_ticks = 120;
    int16_t max_defense = 20;
    int16_t damage_base = 20;
    int16_t image_directions = 32;
    int16_t orientation_mult = 4;
    int16_t max_experience = 100;
    int16_t attack_timeout = 6;
};
ANK_CONFIG_STRUCT(javelin_rules_t,
    speed, flight_ticks, max_defense, damage_base, image_directions, orientation_mult,
    max_experience, attack_timeout)

extern javelin_rules_t javelin_rules;

class figure_javelin : public figure_missile {
public:
    FIGURE_METAINFO(FIGURE_JAVELIN, figure_javelin)
    figure_javelin(figure *f) : figure_missile(f) {}

    virtual void figure_action() override;
    virtual void main_image_update() override;
    virtual void cart_image_update() override;
};

// OG is_attack_target on the tile's figure stack — for tests.
figure_id javelin_find_attack_target(tile2i tile);
