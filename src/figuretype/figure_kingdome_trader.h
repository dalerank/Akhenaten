#pragma once

#include "figure_trader.h"

int figure_create_trade_caravan(tile2i tile, int city_id);

class figure_trade_caravan : public figure_trader {
public:
    FIGURE_METAINFO(FIGURE_TRADE_CARAVAN, figure_trade_caravan);
    figure_trade_caravan(figure *f) : figure_trader(f) {}

    struct static_params : figures::model_t<figure_trade_caravan> {
        int wait_ticks_after_create;
        virtual void load(archive arch) override;
    };

    virtual void on_create() override;
    virtual void figure_action() override;
    virtual void before_poof() override;
    virtual e_figure_sound phrase() const override { return {FIGURE_TRADE_CARAVAN, "caravan"}; }
    virtual sound_key phrase_key() const override;
    //virtual figure_sound_t get_sound_reaction(pcstr key) const override;
    virtual bool window_info_background(object_info &ctx) override;
    virtual const animations_t &anim() const override;
    virtual void update_animation() override;

    const static_params &current_params() const { static_cast<const static_params &>(params()); }

    void go_to_next_storageyard(tile2i src_tile, int distance_to_entry);
};