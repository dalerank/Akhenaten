#include "city_resource_handle.h"
#include "city/buildings.h"
#include "city/city_resource.h"

#include "empire/empire.h"
#include "city/city.h"
#include "io/gamefiles/lang.h"

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

    switch (city_resource().trade_status[resource]) {
    default:
        city_resource().trade_status[resource] = TRADE_STATUS_IMPORT_AS_NEEDED;
        break;
    case TRADE_STATUS_IMPORT_AS_NEEDED:
        city_resource().trade_status[resource] = TRADE_STATUS_IMPORT;
        break;
    case TRADE_STATUS_IMPORT:
        city_resource().trade_status[resource] = TRADE_STATUS_NONE;
        break;
    }
}

e_trade_status city_resource_handle::trade_status() {
    return city_resource().trade_status[resource];
}

void city_resource_handle::cycle_trade_status() {
    auto& trade_status = city_resource().trade_status[resource];
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

    switch (city_resource().trade_status[resource]) {
    default:
        city_resource().trade_status[resource] = TRADE_STATUS_EXPORT_SURPLUS;
        city_resource().stockpiled[resource] = false;
        break;

    case TRADE_STATUS_EXPORT_SURPLUS:
        city_resource().trade_status[resource] = TRADE_STATUS_EXPORT;
        city_resource().stockpiled[resource] = false;
        break;

    case TRADE_STATUS_EXPORT:
        city_resource().trade_status[resource] = TRADE_STATUS_NONE;
        break;
    }
}

int city_resource_handle::industry_active() {
    return city_building_stats().count_industry_active(resource);
}

int city_resource_handle::industry_total() {
    return city_building_stats().count_industry_total(resource);
}

int city_resource_handle::yards_stored() {
    return city_resource().yards_stored(resource);
}

bool city_resource_handle::is_stockpiled() {
    return city_resource().is_stockpiled(resource);
}

bool city_resource_handle::can_produce() {
    return g_empire.can_produce_resource(resource);
}

bool city_resource_handle::can_import(bool check_if_import) {
    return g_empire.can_import_resource(resource, check_if_import);
}

bool city_resource_handle::can_export(bool check) {
    return g_empire.can_export_resource(resource, check);
}

int city_resource_handle::trading_amount() {
    return city_resource().trading_amount[resource];
}

void city_resource_handle::change_trading_amount(int delta) {
    city_resource().trading_amount[resource] = calc_bound(city_resource().trading_amount[resource] + delta, 0, 10000);
}

void city_resource_handle::toggle_stockpiled() {
    city_resource().toggle_stockpiled(resource);
}

bool city_resource_handle::is_mothballed() {
    return city_resource().is_mothballed(resource);
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
    return lang_get_string(23, resource);
}

int city_resource_handle::stack_proper_quantity(int value) {
    return ::stack_proper_quantity(value, resource);
}
