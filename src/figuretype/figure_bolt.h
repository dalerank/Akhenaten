#pragma once

#include "figuretype/figure_missile.h"

// OG missiles.c figure_bolt_action (FIG_BOLT).
// Target: map_figure_find_target (same as javelin). Damage: missile_og_* (arrow formula).
// Image: MISSILE_IMAGE_BOLT offset. No formation missile_attack_timeout.
class figure_bolt : public figure_missile {
public:
    FIGURE_METAINFO(FIGURE_BOLT, figure_bolt)
    figure_bolt(figure *f) : figure_missile(f) {}

    virtual void figure_action() override;
    virtual void main_image_update() override;
};
