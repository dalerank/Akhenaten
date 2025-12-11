#pragma once

#include "figure/figure.h"
#include "empire/empire_city.h"

class figure_trader : public figure_impl {
public:
    figure_trader(figure *f) : figure_impl(f) {}

    bool can_buy(building *warehouse, empire_city_handle city) const;
    bool can_sell(building *b, empire_city_handle city) const;

    int get_closest_storageyard(tile2i tile, empire_city_handle city, int distance_from_entry, tile2i &warehouse);

    virtual void buy(int amounts) = 0;
    virtual void sell(int amounts) = 0;

    virtual uint16_t total_bought() const = 0;
    virtual uint16_t max_capacity() const = 0;
};