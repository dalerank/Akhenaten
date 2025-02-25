#pragma once

#include "figuretype/figure_cartpusher.h"
#include "grid/point.h"

enum {
    TRADE_SHIP_NONE = 0,
    TRADE_SHIP_BUYING = 1,
    TRADE_SHIP_SELLING = 2,
};

struct empire_city;

class figure_trade_ship : public figure_carrier {
public:
    FIGURE_METAINFO(FIGURE_TRADE_SHIP, figure_trade_ship)
    figure_trade_ship(figure *f) : figure_carrier(f) {}

    virtual void on_create() override;
    virtual void figure_action() override;
    virtual figure_trade_ship *dcast_trade_ship() override { return this; }
    virtual sound_key phrase_key() const override;
    virtual void kill() override;
    virtual void update_animation() override;
    virtual void poof() override;
    virtual const animations_t &anim() const override;
    virtual figure_phrase_t phrase() const override { return {FIGURE_TRADE_SHIP, "barge"}; }
    virtual bool window_info_background(object_info &c) override;
    virtual void update_day() override;

    bool lost_queue();
    bool done_trading();
    int is_trading() const;

    static int create(tile2i tile, const empire_city& city);
};
