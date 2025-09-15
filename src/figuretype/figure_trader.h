#pragma once

#include "figure/figure.h"
#include "empire/empire_city.h"

class figure_trader : public figure_impl {
public:
    figure_trader(figure *f) : figure_impl(f) {}

    void buy(int amounts);
    void sell(int amounts);

    bool can_buy(building *warehouse, empire_city_handle city);
    bool can_sell(building *b, empire_city_handle city);

    int get_closest_storageyard(tile2i tile, empire_city_handle city, int distance_from_entry, tile2i &warehouse);
};