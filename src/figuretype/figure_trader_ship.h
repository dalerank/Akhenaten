#pragma once

#include "figuretype/figure_cartpusher.h"
#include "grid/point.h"

enum {
    TRADE_SHIP_NONE = 0,
    TRADE_SHIP_BUYING = 1,
    TRADE_SHIP_SELLING = 2,
};

class figure_trade_ship : public figure_carrier {
public:
    FIGURE_METAINFO(FIGURE_TRADE_SHIP, figure_trade_ship)
    figure_trade_ship(figure *f) : figure_carrier(f) {}

    virtual void figure_action() override;
    virtual figure_trade_ship *dcast_trade_ship() override { return this; }
    virtual sound_key phrase_key() const override;

    int lost_queue();
    int done_trading();
    int is_trading() const;
};

int figure_create_trade_ship(tile2i tile, int city_id);