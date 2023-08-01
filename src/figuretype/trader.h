#ifndef FIGURETYPE_TRADER_H
#define FIGURETYPE_TRADER_H

#include "figure/figure.h"

enum {
    TRADE_SHIP_NONE = 0,
    TRADE_SHIP_BUYING = 1,
    TRADE_SHIP_SELLING = 2,
};

int figure_create_trade_caravan(int x, int y, int city_id);

int figure_create_trade_ship(int x, int y, int city_id);

bool figure_trade_caravan_can_buy(figure* trader, building* warehouse, int city_id);

bool figure_trade_caravan_can_sell(figure* trader, building* warehouse, int city_id);

// void figure_trade_caravan_action();
//
// void figure_trade_caravan_donkey_action();
//
// void figure_native_trader_action();
//
// int figure_trade_ship_is_trading(figure *ship);
//
// void figure_trade_ship_action();

#endif // FIGURETYPE_TRADER_H
