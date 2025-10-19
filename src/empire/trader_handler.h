#pragma once

#include "core/buffer.h"
#include "empire/empire_city.h"
#include "game/resource.h"

class building;

struct empire_trader_handle {
    uint8_t handle = 0;

    int record_bought_resource(e_resource resource);
    int record_sold_resource(e_resource resource);

    int bought_resources(e_resource resource);
    int sold_resources(e_resource resource);

    bool has_traded();
    bool has_traded_max();

    bool valid() { return handle != 0; }
    void back_to_city();

    e_resource get_buy_resource(building* storageyard, empire_city_handle city, int amount);
    e_resource get_sell_resource(building* warehouse, empire_city_handle city);
};

empire_trader_handle empire_create_trader();