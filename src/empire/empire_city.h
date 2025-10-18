#pragma once

#include "empire/empire_object.h"
#include "empire/type.h"
#include "game/resource.h"
#include "empire/trade_route.h"
#include "figure/figure_type.h"
#include "core/tokenum.h"
#include "core/archive.h"

struct empire_city {
    enum {
        check_open_route = 1
    };

    uint8_t in_use; // this can be 2, so it's an int!
    e_empire_city type;
    uint8_t name_id;
    int route_id;
    bool is_open;
    bool buys_resource[RESOURCES_MAX];
    bool sells_resource[RESOURCES_MAX];
    int16_t cost_to_open;
    int ph_unk01;
    int ph_unk02;
    int trader_entry_delay;
    int empire_object_id;
    bool is_sea_trade;
    int trader_figure_ids[3];
    svector<uint16_t, 5> trade_limits;
    uint8_t max_traders;

    void remove_trader(int figure_id);
    bool can_trade() const;
    trade_route &get_route();
    const trade_route &get_route() const;
    const empire_object *get_empire_object() const;
    const full_empire_object *get_full_empire_object() const;
    int get_free_slot(int max_traders) const;

    void set_vulnerable() {
        type = EMPIRE_CITY_FOREIGN_TRADING;
    }
    void set_foreign() {
        type = EMPIRE_CITY_EGYPTIAN;
    }
};
ANK_CONFIG_STRUCT(empire_city, is_sea_trade, max_traders, trade_limits)

struct empire_city_handle {
    uint8_t handle = 0;

    empire_city& operator*();
    empire_city& ref();
    const empire_city& ref() const;

    const trade_route& get_route() const;
    trade_route& get_route();
    bool valid() const { return handle > 0; }
    bool buys_resource(e_resource r) const;
    bool sells_resource(e_resource r) const;

    void remove_trader(figure_id fid);
    xstring name() const;

    [[nodiscard]]
    bool operator!() const { return !valid(); }
};

extern const token_holder<e_empire_city, EMPIRE_CITY_OURS, EMPIRE_CITY_COUNT> e_empire_city_tokens;