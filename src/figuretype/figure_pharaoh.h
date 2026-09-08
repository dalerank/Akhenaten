#pragma once

#include "figure/figure.h"

enum e_pharaoh_action {
    ACTION_120_PHARAOH_CREATED = 120,
    ACTION_121_PHARAOH_ROAMING = 121,
};

// Cinematic / victory VFX walker. No build-menu spawn; test/event only.
class figure_pharaoh : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_PHARAOH, figure_pharaoh)
    figure_pharaoh(figure *f) : figure_impl(f) {}

    virtual void on_create() override;
    virtual void figure_action() override;
    virtual void figure_roaming_action() override { /* avoid double-roam + home-less return */ }
    virtual void update_animation() override;
};
