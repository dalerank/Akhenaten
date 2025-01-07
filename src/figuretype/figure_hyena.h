#pragma once

#include "figure_animal.h"

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