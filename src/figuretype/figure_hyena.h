#pragma once

#include "figure_animal.h"

enum e_hyena_action {
    ACTION_196_HYENA_AT_REST = 196,
    ACTION_197_HYENA_MOVING = 197,
    ACTION_199_HYENA_ATTACKING = 199,
};

class figure_hyena : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_HYENA, figure_hyena)
    figure_hyena(figure *f) : figure_impl(f) {}

    virtual void on_create() override;
    virtual void figure_action() override;
    virtual void on_destroy() override;
    virtual void update_animation() override;
};

int figure_combat_get_target_for_hyena(tile2i tile, int max_distance);