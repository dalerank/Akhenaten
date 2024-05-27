#pragma once

#include "figure_trader.h"

int figure_create_trade_caravan(tile2i tile, int city_id);

class figure_trade_caravan : public figure_trader {
public:
    figure_trade_caravan(figure *f) : figure_trader(f) {}

    virtual void on_create() override {}
    virtual void figure_action() override;
    virtual e_figure_sound phrase() const override { return {FIGURE_TRADE_CARAVAN, "caravan"}; }
    virtual sound_key phrase_key() const override;
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;
    virtual bool window_info_background(object_info &ctx) override;
    virtual const animations_t &anim() const override;
    virtual void update_animation() override;

    void go_to_next_storageyard(tile2i src_tile, int distance_to_entry);
};