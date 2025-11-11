#pragma once

#include "figure/figure.h"

enum e_water_carrier_action {
    ACTION_10_WATER_CARRIER_GOING = 10,
    ACTION_11_WATER_CARRIER_RETURNING_FROM_PATROL = 11,
    ACTION_72_WATER_CARRIER_ROAMING = 72,
    ACTION_73_WATER_CARRIER_RETURNING = 73,
};

class figure_water_carrier : public figure_impl {
public:
    FIGURE_METAINFO(FIGURE_WATER_CARRIER, figure_water_carrier)
    figure_water_carrier(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_before_action() override;
    virtual void figure_action() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_FIRE; }
    virtual sound_key phrase_key() const override;
    virtual int provide_service() override;
    virtual figure_sound_t get_sound_reaction(xstring key) const override;
};
