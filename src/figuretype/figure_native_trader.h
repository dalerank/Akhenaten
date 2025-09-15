#pragma once

#include "figuretype/figure_trader.h"
#include "figure/trader.h"

class figure_native_trader : public figure_trader {
public:
    FIGURE_METAINFO(FIGURE_NATIVE_TRADER, figure_native_trader)
    figure_native_trader(figure *f) : figure_trader(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;

    //virtual void figure_before_action() override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_NATIVE_TRADER, "nattrad"}; }
    virtual void update_animation() override;
    virtual void debug_show_properties() override;
    //virtual sound_key phrase_key() const override;
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;

    empire_trader_handle empire_trader();
};