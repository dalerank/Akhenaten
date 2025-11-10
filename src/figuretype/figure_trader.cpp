#include "figure_trader.h"

#include "core/calc.h"
#include "city/trade.h"
#include "empire/empire_map.h"
#include "empire/empire.h"
#include "game/game.h"
#include "building/building_storage_yard.h"
#include "building/building_storage_room.h"
#include "grid/road_access.h"
#include "graphics/painter.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/lang_text.h"
#include "empire/trader_handler.h"

bool figure_trader::can_buy(building* b, empire_city_handle city) const {
    building_storage_yard *warehouse = b->dcast_storage_yard();
    if (!warehouse) {
        return false;
    }

    if (total_bought() >= 800) {
        return false;
    }

    if (!warehouse->get_permission(BUILDING_STORAGE_PERMISSION_TRADERS)) {
        return false;
    }

    building_storage_room* space = warehouse->room();
    while (space) {
        if (space->base.stored_amount_first >= 100 && g_empire.can_export_resource_to_city(city.handle, space->resource())) {
            return true;
        }
        space = space->next_room();
    }

    return false;
}

bool figure_trader::can_sell(building* b, empire_city_handle city) const {
    auto warehouse = b->dcast_storage_yard();
    if (!warehouse) {
        return false;
    }

    if (base.trader_total_sold() >= 800) {
        return false;
    }

    if (!warehouse->get_permission(BUILDING_STORAGE_PERMISSION_TRADERS)) {
        return false;
    }

    auto* storage = warehouse->storage();
    if (storage->empty_all)
        return false;

    int num_importable = 0;
    for (e_resource r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
        if (!warehouse->is_not_accepting(r)) {
            if (g_empire.can_import_resource_from_city(city.handle, r))
                num_importable++;
        }
    }

    if (num_importable <= 0)
        return false;

    int can_import = 0;
    e_resource resource = city_trade_current_caravan_import_resource();
    if (!warehouse->is_not_accepting(resource) && g_empire.can_import_resource_from_city(city.handle, resource)) {
        can_import = 1;
    } else {
        for (int i = RESOURCES_MIN; i < RESOURCES_MAX; i++) {
            resource = city_trade_next_caravan_import_resource();
            if (!warehouse->is_not_accepting(resource) && g_empire.can_import_resource_from_city(city.handle, resource)) {
                can_import = 1;
                break;
            }
        }
    }

    if (can_import) {
        // at least one resource can be imported and accepted by this warehouse
        // check if warehouse can store any importable goods
        auto space = warehouse->room();
        while (space) {
            if (space->base.stored_amount_first < 400) {
                if (!space->base.stored_amount_first) {
                    // empty space
                    return true;
                }

                if (g_empire.can_import_resource_from_city(city.handle, space->resource())) {
                    return true;
                }
            }
            space = space->next_room();
        }
    }
    return false;
}

int figure_trader::get_closest_storageyard(tile2i tile, empire_city_handle city, int distance_from_entry, tile2i &warehouse) {
    const resource_list exportable = total_bought() < 800 
                                        ? g_empire.exportable_resources_from_city(city.handle)
                                        : resource_list{};

    const resource_list importable = base.get_carrying_amount() < 800 
                                        ? g_empire.importable_resources_from_city(city.handle)
                                        : resource_list{};

    int num_importable = importable.size();

    int min_distance = 10000;
    building* min_building = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building_storage_yard* warehouse = building_get(i)->dcast_storage_yard();
        if (!warehouse || !warehouse->is_valid()) {
            continue;
        }

        if (!warehouse->has_road_access() || warehouse->base.distance_from_entry <= 0) {
            continue;
        }

        if (!warehouse->get_permission(BUILDING_STORAGE_PERMISSION_TRADERS)) {
            continue;
        }

        const storage_t* s = warehouse->storage();
        int num_imports_for_warehouse = 0;
        for (e_resource r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
            if (!warehouse->is_not_accepting(r) && g_empire.can_import_resource_from_city(city.handle, r)) {
                num_imports_for_warehouse++;
            }
        }

        int distance_penalty = 32;
        building_storage_room* space = warehouse->room();
        while (space) {
            if (exportable[space->resource()]) {
                distance_penalty -= 4;
            }

            if (num_importable && num_imports_for_warehouse && !s->empty_all) {
                for (e_resource r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
                    if (!warehouse->is_not_accepting(city_trade_next_caravan_import_resource()))
                        break;
                }

                e_resource resource = city_trade_current_caravan_import_resource();
                if (!warehouse->is_not_accepting(resource)) {
                    if (space->resource() == RESOURCE_NONE)
                        distance_penalty -= 16;

                    if (importable[space->resource()] && space->base.stored_amount_first < 400
                        && space->resource() == resource) {
                        distance_penalty -= 8;
                    }
                }
            }
            space = space->next_room();
        }

        if (distance_penalty < 32) {
            int distance = calc_distance_with_penalty(warehouse->tile(), tile, distance_from_entry, warehouse->base.distance_from_entry);
            distance += distance_penalty;
            if (distance < min_distance) {
                min_distance = distance;
                min_building = &warehouse->base;
            }
        }
    }

    if (!min_building)
        return 0;

    if (min_building->has_road_access == 1) {
        map_point_store_result(min_building->tile, warehouse);
    } else {
        warehouse = map_get_road_access_tile(min_building->tile, 3);
        if (!warehouse.valid()) {
            return 0;
        }
    }

    return min_building->id;
}
