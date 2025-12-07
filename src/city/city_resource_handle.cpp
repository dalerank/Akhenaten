#include "city_resource_handle.h"

#include "empire/empire.h"
#include "city/city.h"

city_resource_handle city_resource_barley{ RESOURCE_BARLEY };
city_resource_handle city_resource_gems{ RESOURCE_GEMS };
city_resource_handle city_resource_beer{ RESOURCE_BEER };
city_resource_handle city_resource_reeds{ RESOURCE_REEDS };
city_resource_handle city_resource_clay{ RESOURCE_CLAY };
city_resource_handle city_resource_copper{ RESOURCE_COPPER };
city_resource_handle city_resource_flax{ RESOURCE_FLAX };
city_resource_handle city_resource_linen{ RESOURCE_LINEN };
city_resource_handle city_resource_papyrus{ RESOURCE_PAPYRUS };

void city_resource_handle::cycle_trade_import() {
    // no sellers?
    if (!g_empire.can_import_resource(resource, true))
        return;

    switch (g_city.resource.trade_status[resource]) {
    default:
        g_city.resource.trade_status[resource] = TRADE_STATUS_IMPORT_AS_NEEDED;
        break;
    case TRADE_STATUS_IMPORT_AS_NEEDED:
        g_city.resource.trade_status[resource] = TRADE_STATUS_IMPORT;
        break;
    case TRADE_STATUS_IMPORT:
        g_city.resource.trade_status[resource] = TRADE_STATUS_NONE;
        break;
    }
}

e_trade_status city_resource_handle::trade_status() {
    return g_city.resource.trade_status[resource];
}

void city_resource_handle::cycle_trade_status() {
    auto &trade_status = g_city.resource.trade_status[resource];
    trade_status = (e_trade_status)((int)trade_status + 1);
    if (trade_status > TRADE_STATUS_EXPORT) {
        trade_status = TRADE_STATUS_NONE;
    }

    if (trade_status == TRADE_STATUS_IMPORT && !g_empire.can_import_resource(resource, true)) {
        trade_status = TRADE_STATUS_EXPORT;
    }

    if (trade_status == TRADE_STATUS_EXPORT && !g_empire.can_export_resource(resource, true)) {
        trade_status = TRADE_STATUS_NONE;
    }

    if (trade_status == TRADE_STATUS_EXPORT) {
        trade_status = TRADE_STATUS_NONE;
    }
}

void city_resource_handle::cycle_trade_export() {
    // no buyers?
    if (!g_empire.can_export_resource(resource, true))
        return;

    switch (g_city.resource.trade_status[resource]) {
    default:
        g_city.resource.trade_status[resource] = TRADE_STATUS_EXPORT_SURPLUS;
        g_city.resource.stockpiled[resource] = false;
        break;

    case TRADE_STATUS_EXPORT_SURPLUS:
        g_city.resource.trade_status[resource] = TRADE_STATUS_EXPORT;
        g_city.resource.stockpiled[resource] = false;
        break;

    case TRADE_STATUS_EXPORT:
        g_city.resource.trade_status[resource] = TRADE_STATUS_NONE;
        break;
    }
}

int city_resource_handle::industry_active() {
    return g_city.buildings.count_industry_active(resource);
}

int city_resource_handle::industry_total() {
    return g_city.buildings.count_industry_total(resource);
}

int city_resource_handle::yards_stored() {
    return g_city.resource.yards_stored(resource);
}

bool city_resource_handle::is_stockpiled() {
    return  g_city.resource.is_stockpiled(resource);
}

bool city_resource_handle::can_produce() {
    return g_city.can_produce_resource(resource);
}

bool city_resource_handle::can_import(bool check_if_import) {
    return g_empire.can_import_resource(resource, check_if_import);
}

bool city_resource_handle::can_export(bool check) {
    return g_empire.can_export_resource(resource, check);
}

int city_resource_handle::trading_amount() {
    return g_city.resource.trading_amount[resource];
}

void city_resource_handle::change_trading_amount(int delta) {
    g_city.resource.trading_amount[resource] = calc_bound(g_city.resource.trading_amount[resource] + delta, 0, 10000);
}

void city_resource_handle::toggle_stockpiled() {
    g_city.resource.toggle_stockpiled(resource);
}

bool city_resource_handle::is_mothballed() {
    return g_city.resource.is_mothballed(resource);
}

int stack_proper_quantity(int full, int resource) {
    switch (stack_units_by_resource(resource)) {
    default: // all other goods are 100 worth of, per pile
        return full;

    case RESOURCE_UNIT_BLOCK:
    case RESOURCE_UNIT_WEAPON:
    case RESOURCE_UNIT_CHARIOT:
    case RESOURCE_WEAPONS:
        return full / 100;
    }
}

xstring city_resource_handle::name() {
    return ui::str(23, resource);
}

int city_resource_handle::stack_proper_quantity(int value) {
    return ::stack_proper_quantity(value, resource);
}
