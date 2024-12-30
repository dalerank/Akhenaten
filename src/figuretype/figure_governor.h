#pragma once

#include "figure/figure.h"

class figure_governor : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_GOVERNOR, figure_governor)
    figure_governor(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_GOVERNOR, "governor"}; }
    virtual sound_key phrase_key() const override;
    virtual const animations_t &anim() const override;
};