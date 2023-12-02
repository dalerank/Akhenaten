#include "trader_caravan.h"

#include "figure/trader.h"
#include "figure/figure.h"

#include "building/storage.h"
#include "building/storage_yard.h"

#include "empire/empire.h"
#include "empire/trade_prices.h"

#include "city/trade.h"
#include "city/resource.h"
#include "city/finance.h"

bool figure_trade_caravan_can_buy(figure* trader, building* warehouse, int city_id) {
    if (warehouse->type != BUILDING_STORAGE_YARD)
        return false;

    if (trader->trader_total_bought() >= 800)
        return false;

    if (!building_storage_get_permission(BUILDING_STORAGE_PERMISSION_TRADERS, warehouse))
        return false;

    building* space = warehouse;
    for (int i = 0; i < 8; i++) {
        space = space->next();
        if (space->id > 0 && space->stored_full_amount >= 100
            && empire_can_export_resource_to_city(city_id, space->subtype.warehouse_resource_id)) {
            return true;
        }
    }
    return false;
}

bool figure_trade_caravan_can_sell(figure* trader, building* warehouse, int city_id) {
    if (warehouse->type != BUILDING_STORAGE_YARD)
        return false;

    if (trader->trader_total_sold() >= 800)
        return false;

    if (!building_storage_get_permission(BUILDING_STORAGE_PERMISSION_TRADERS, warehouse))
        return false;

    const building_storage* storage = building_storage_get(warehouse->storage_id);
    if (storage->empty_all)
        return false;

    int num_importable = 0;
    for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; ++r) {
        if (!building_storageyard_is_not_accepting(r, warehouse)) {
            if (empire_can_import_resource_from_city(city_id, r))
                num_importable++;
        }
    }
    if (num_importable <= 0)
        return false;

    int can_import = 0;
    e_resource resource = city_trade_current_caravan_import_resource();
    if (!building_storageyard_is_not_accepting(resource, warehouse)
        && empire_can_import_resource_from_city(city_id, resource)) {
        can_import = 1;
    } else {
        for (int i = RESOURCE_MIN; i < RESOURCES_MAX; i++) {
            resource = city_trade_next_caravan_import_resource();
            if (!building_storageyard_is_not_accepting(resource, warehouse)
                && empire_can_import_resource_from_city(city_id, resource)) {
                can_import = 1;
                break;
            }
        }
    }
    if (can_import) {
        // at least one resource can be imported and accepted by this warehouse
        // check if warehouse can store any importable goods
        building* space = warehouse;
        for (int s = 0; s < 8; s++) {
            space = space->next();
            if (space->id > 0 && space->stored_full_amount < 400) {
                if (!space->stored_full_amount) {
                    // empty space
                    return true;
                }
                if (empire_can_import_resource_from_city(city_id, space->subtype.warehouse_resource_id))
                    return true;
            }
        }
    }
    return false;
}