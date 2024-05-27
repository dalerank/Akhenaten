#pragma once

#include "figure/figure.h"

class figure_caravan_donkey : public figure_impl {
public:
    figure_caravan_donkey(figure *f) : figure_impl(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual void figure_before_action() override;
    virtual e_figure_sound phrase() const override { return {FIGURE_TRADE_CARAVAN_DONKEY, "donkey"}; }
    virtual void update_animation() override;
    //virtual sound_key phrase_key() const override;
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;
    virtual bool window_info_background(object_info &ctx) override;

    figure *get_head_of_caravan();
};