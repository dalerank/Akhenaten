#pragma once

#include "empire/type.h"
#include "game/resource.h"

struct empire_city {
    enum {
        check_open_route = 1
    };

    int in_use; // this can be 2, so it's an int!
    e_empire_city type;
    int name_id;
    int route_id;
    bool is_open;
    bool buys_resource[RESOURCES_MAX];
    bool sells_resource[RESOURCES_MAX];
    int cost_to_open;
    int ph_unk01;
    int ph_unk02;
    int trader_entry_delay;
    int empire_object_id;
    int is_sea_trade;
    int trader_figure_ids[3];

    void remove_trader(int figure_id);

    void set_vulnerable() {
        type = EMPIRE_CITY_FOREIGN_TRADING;
    }
    void set_foreign() {
        type = EMPIRE_CITY_EGYPTIAN;
    }
};