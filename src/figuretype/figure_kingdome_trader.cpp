#include "figure_kingdome_trader.h"

#include "building/building.h"
#include "building/dock.h"
#include "building/storage.h"
#include "building/storage_yard.h"
#include "city/buildings.h"
#include "city/finance.h"
#include "city/map.h"
#include "city/message.h"
#include "city/resource.h"
#include "city/trade.h"
#include "core/calc.h"
#include "empire/empire_city.h"
#include "empire/empire.h"
#include "empire/trade_prices.h"
#include "empire/trade_route.h"
#include "figure/combat.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "figure/trader.h"
#include "graphics/image.h"
#include "graphics/image_desc.h"
#include "graphics/image_groups.h"
#include "grid/figure.h"
#include "grid/road_access.h"
#include "scenario/map.h"
#include "figuretype/trader_caravan.h"

void figure::trader_buy(int amounts) {
    trader_amount_bought += amounts;
}

void figure::trader_sell(int amounts) {
    resource_amount_full += amounts;
    //    resource_amount_loads += amounts / 100;
}

int figure::trader_total_bought() {
    return trader_amount_bought;
}

int figure::trader_total_sold() {
    return resource_amount_full;
}

int figure_create_trade_caravan(tile2i tile, int city_id) {
    figure* caravan = figure_create(FIGURE_TRADE_CARAVAN, tile, DIR_0_TOP_RIGHT);
    caravan->empire_city_id = city_id;
    caravan->action_state = FIGURE_ACTION_100_TRADE_CARAVAN_CREATED;
    caravan->wait_ticks = 10;
    // donkey 1
    figure* donkey1 = figure_create(FIGURE_TRADE_CARAVAN_DONKEY, tile, DIR_0_TOP_RIGHT);
    donkey1->action_state = FIGURE_ACTION_100_TRADE_CARAVAN_CREATED;
    donkey1->leading_figure_id = caravan->id;
    // donkey 2
    figure* donkey2 = figure_create(FIGURE_TRADE_CARAVAN_DONKEY, tile, DIR_0_TOP_RIGHT);
    donkey2->action_state = FIGURE_ACTION_100_TRADE_CARAVAN_CREATED;
    donkey2->leading_figure_id = donkey1->id;
    return caravan->id;
}


int figure::get_closest_storageyard(tile2i tile, int city_id, int distance_from_entry, tile2i &warehouse) {
    bool exportable[RESOURCES_MAX];
    bool importable[RESOURCES_MAX];
    exportable[RESOURCE_NONE] = false;
    importable[RESOURCE_NONE] = false;

    for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; ++r) {
        exportable[r] = empire_can_export_resource_to_city(city_id, r);
        if (trader_amount_bought >= 800) {
            exportable[r] = false;
        }

        if (city_id) {
            importable[r] = empire_can_import_resource_from_city(city_id, r);
        } else { // exclude own city (id=0), shouldn't happen, but still..
            importable[r] = false;
        }

        if (get_carrying_amount() >= 800) {
            importable[r] = false;
        }
    }

    int num_importable = 0;
    for (int r = RESOURCE_MIN; r < RESOURCES_MAX; r++) {
        num_importable += importable[r] ? 1 : 0;
    }

    int min_distance = 10000;
    building* min_building = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || b->type != BUILDING_STORAGE_YARD) {
            continue;
        }

        if (!b->has_road_access || b->distance_from_entry <= 0) {
            continue;
        }

        if (!building_storage_get_permission(BUILDING_STORAGE_PERMISSION_TRADERS, b)) {
            continue;
        }

        const building_storage* s = building_storage_get(b->storage_id);
        int num_imports_for_warehouse = 0;
        for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; r = (e_resource)(r + 1)) {
            if (!building_storageyard_is_not_accepting(r, b) && empire_can_import_resource_from_city(city_id, r)) {
                num_imports_for_warehouse++;
            }
        }
        int distance_penalty = 32;
        building* space = b;
        for (int space_cnt = 0; space_cnt < 8; space_cnt++) {
            space = space->next();
            if (space->id && exportable[space->subtype.warehouse_resource_id])
                distance_penalty -= 4;

            if (num_importable && num_imports_for_warehouse && !s->empty_all) {
                for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; ++r) {
                    if (!building_storageyard_is_not_accepting(city_trade_next_caravan_import_resource(), b))
                        break;
                }
                e_resource resource = city_trade_current_caravan_import_resource();
                if (!building_storageyard_is_not_accepting(resource, b)) {
                    if (space->subtype.warehouse_resource_id == RESOURCE_NONE)
                        distance_penalty -= 16;

                    if (space->id && importable[space->subtype.warehouse_resource_id] && space->stored_full_amount < 400
                        && space->subtype.warehouse_resource_id == resource) {
                        distance_penalty -= 8;
                    }
                }
            }
        }

        if (distance_penalty < 32) {
            int distance = calc_distance_with_penalty(b->tile, tile, distance_from_entry, b->distance_from_entry);
            distance += distance_penalty;
            if (distance < min_distance) {
                min_distance = distance;
                min_building = b;
            }
        }
    }
    if (!min_building)
        return 0;

    if (min_building->has_road_access == 1) {
        map_point_store_result(min_building->tile, warehouse);
    } else if (!map_get_road_access_tile(min_building->tile, 3, warehouse)) {
        return 0;
    }

    return min_building->id;
}

void figure::go_to_next_storageyard(tile2i src_tile, int distance_to_entry) {
    tile2i dst;
    int warehouse_id = get_closest_storageyard(src_tile, empire_city_id, distance_to_entry, dst);
    if (warehouse_id && warehouse_id != destinationID()) {
        set_destination(warehouse_id);
        action_state = FIGURE_ACTION_101_TRADE_CARAVAN_ARRIVING;
        destination_tile = dst;
    } else {
        tile2i exit = city_map_exit_point();
        tile2i road_tile;
        state = FIGURE_STATE_ALIVE;
        map_closest_road_within_radius(exit, 1, 2, road_tile);
        destination_tile = road_tile;
        direction = DIR_0_TOP_RIGHT;
        advance_action(ACTION_16_EMIGRANT_RANDOM);
        action_state = FIGURE_ACTION_103_TRADE_CARAVAN_LEAVING;
    }
}

void figure::trade_caravan_action() {
    int last_action_state = action_state;
    switch (action_state) {
    default:
    case FIGURE_ACTION_100_TRADE_CARAVAN_CREATED:
    case 8:
        wait_ticks++;
        if (wait_ticks > 20) {
            wait_ticks = 0;
            tile2i base_tile;
            int trade_center_id = city_buildings_get_trade_center();
            if (trade_center_id) {
                building* trade_center = building_get(trade_center_id);
                base_tile = trade_center->tile;
            } else {
                base_tile = tile;
            }
            go_to_next_storageyard(base_tile, 0);
        }
        anim_frame = 0;
        break;
    case FIGURE_ACTION_101_TRADE_CARAVAN_ARRIVING:
    case 9:
        do_gotobuilding(destination(), true, TERRAIN_USAGE_PREFER_ROADS, FIGURE_ACTION_102_TRADE_CARAVAN_TRADING, FIGURE_ACTION_100_TRADE_CARAVAN_CREATED);
        if (direction == DIR_FIGURE_CAN_NOT_REACH || direction == DIR_FIGURE_REROUTE) {
            int i = 0; // break
        }
        break;
    case FIGURE_ACTION_102_TRADE_CARAVAN_TRADING:
    case 10:
        wait_ticks++;
        if (wait_ticks > 10) {
            wait_ticks = 0;
            int move_on = 0;
            constexpr int one_operation_amount = 100;
            if (figure_trade_caravan_can_buy(this, destination(), empire_city_id)) {
                e_resource resource = trader_get_buy_resource(destination(), empire_city_id, one_operation_amount);
                if (resource) {
                    trade_route_increase_traded(empire_city_get_route_id(empire_city_id), resource, one_operation_amount);
                    trader_record_bought_resource(trader_id, resource);
                    trader_buy(one_operation_amount);
                } else {
                    move_on++;
                }
            } else {
                move_on++;
            }

            if (move_on > 0 && figure_trade_caravan_can_sell(this, destination(), empire_city_id)) {
                e_resource resource = trader_get_sell_resource(destination(), empire_city_id);
                if (resource) {
                    trade_route_increase_traded(empire_city_get_route_id(empire_city_id), resource, one_operation_amount);
                    trader_record_sold_resource(trader_id, resource);
                    trader_sell(one_operation_amount);
                } else {
                    move_on++;
                }
            } else {
                move_on++;
            }

            if (move_on == 2) {
                go_to_next_storageyard(tile, -1);
            }
        }
        anim_frame = 0;
        break;
    case FIGURE_ACTION_103_TRADE_CARAVAN_LEAVING:
    case 11:
        if (do_goto(destination_tile, TERRAIN_USAGE_PREFER_ROADS)) {
            poof();
        }
        break;
    }
    int dir = figure_image_normalize_direction(direction < 8 ? direction : previous_tile_direction);
    sprite_image_id = image_group(IMG_TRADER_CARAVAN) + dir + 8 * anim_frame;
}

void figure::trade_caravan_donkey_action() {
    figure* leader = figure_get(leading_figure_id);
    if (leader->action_state == FIGURE_ACTION_149_CORPSE)
        poof();
    else if (leader->state != FIGURE_STATE_ALIVE)
        poof();
    else if (leader->type != FIGURE_TRADE_CARAVAN && leader->type != FIGURE_TRADE_CARAVAN_DONKEY)
        poof();
    else
        follow_ticks(1);

    int dir = figure_image_normalize_direction(direction < 8 ? direction : previous_tile_direction);
    sprite_image_id = image_group(IMG_TRADER_CARAVAN) + dir + 8 * anim_frame;
}