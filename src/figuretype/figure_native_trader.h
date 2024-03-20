#pragma once

#include "figuretype/figure_trader.h"

class figure_native_trader : public figure_trader {
public:
    figure_native_trader(figure *f) : figure_trader(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    //virtual void figure_before_action() override;
    virtual e_figure_sound phrase() const override { return {FIGURE_NATIVE_TRADER, "nativet"}; }
    //virtual sound_key phrase_key() const override;
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;
};