#pragma once

#include "figure/figure.h"

class figure_water_carrier : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_WATER_CARRIER, figure_water_carrier)
    figure_water_carrier(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_WATER_CARRIER, "water"}; }
    virtual e_overlay get_overlay() const override { return OVERLAY_FIRE; }
    virtual sound_key phrase_key() const override;
    virtual const animations_t &anim() const override;
    virtual int provide_service() override;
    virtual figure_sound_t get_sound_reaction(xstring key) const override;
};
