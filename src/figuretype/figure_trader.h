#pragma once

#include "figure/figure.h"

class figure_trader : public figure_impl {
public:
    figure_trader(figure *f) : figure_impl(f) {}

    void buy(int amounts);
    void sell(int amounts);

    bool can_buy(building *warehouse, int city_id);
    bool can_sell(building *b, int city_id);

    int get_closest_storageyard(tile2i tile, int city_id, int distance_from_entry, tile2i &warehouse);
};