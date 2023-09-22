#include "trader.h"

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
#include "empire/city.h"
#include "empire/empire.h"
#include "empire/trade_prices.h"
#include "empire/trade_route.h"
#include "figure/combat.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "figure/trader.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "grid/figure.h"
#include "grid/road_access.h"
#include "scenario/map.h"

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

int figure_create_trade_caravan(int x, int y, int city_id) {
    figure* caravan = figure_create(FIGURE_TRADE_CARAVAN, map_point(x, y), DIR_0_TOP_RIGHT);
    caravan->empire_city_id = city_id;
    caravan->action_state = FIGURE_ACTION_100_TRADE_CARAVAN_CREATED;
    caravan->wait_ticks = 10;
    // donkey 1
    figure* donkey1 = figure_create(FIGURE_TRADE_CARAVAN_DONKEY, map_point(x, y), DIR_0_TOP_RIGHT);
    donkey1->action_state = FIGURE_ACTION_100_TRADE_CARAVAN_CREATED;
    donkey1->leading_figure_id = caravan->id;
    // donkey 2
    figure* donkey2 = figure_create(FIGURE_TRADE_CARAVAN_DONKEY, map_point(x, y), DIR_0_TOP_RIGHT);
    donkey2->action_state = FIGURE_ACTION_100_TRADE_CARAVAN_CREATED;
    donkey2->leading_figure_id = donkey1->id;
    return caravan->id;
}
int figure_create_trade_ship(int x, int y, int city_id) {
    figure* ship = figure_create(FIGURE_TRADE_SHIP, map_point(x, y), DIR_0_TOP_RIGHT);
    ship->empire_city_id = city_id;
    ship->action_state = FIGURE_ACTION_110_TRADE_SHIP_CREATED;
    ship->wait_ticks = 10;
    return ship->id;
}
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
    for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; r = (e_resource)(r + 1)) {
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
static int trader_get_buy_resource(building* storageyard, int city_id) {
    if (storageyard->type != BUILDING_STORAGE_YARD)
        return RESOURCE_NONE;

    building* space = storageyard;
    for (int i = 0; i < 8; i++) {
        space = space->next();
        if (space->id <= 0)
            continue;

        e_resource resource = space->subtype.warehouse_resource_id;
        if (space->stored_full_amount >= 100 && empire_can_export_resource_to_city(city_id, resource)) {
            // update stocks
            city_resource_remove_from_storageyard(resource, 100);
            space->stored_full_amount -= 100;
            if (space->stored_full_amount <= 0)
                space->subtype.warehouse_resource_id = RESOURCE_NONE;

            // update finances
            city_finance_process_export(trade_price_sell(resource));

            // update graphics
            building_storageyard_space_set_image(space, resource);
            return resource;
        }
    }
    return 0;
}
static int trader_get_sell_resource(building* warehouse, int city_id) {
    //    building *warehouse = building_get(warehouse);
    if (warehouse->type != BUILDING_STORAGE_YARD)
        return 0;

    e_resource resource_to_import = city_trade_current_caravan_import_resource();
    int imp = RESOURCE_MIN;
    while (imp < RESOURCES_MAX && !empire_can_import_resource_from_city(city_id, resource_to_import)) {
        imp++;
        resource_to_import = city_trade_next_caravan_import_resource();
    }
    if (imp >= RESOURCES_MAX)
        return 0;

    // add to existing bay with room
    building* space = warehouse;
    for (int i = 0; i < 8; i++) {
        space = space->next();
        if (space->id > 0 && space->stored_full_amount > 0 && space->stored_full_amount < 400
            && space->subtype.warehouse_resource_id == resource_to_import) {
            building_storageyard_space_add_import(space, resource_to_import);
            city_trade_next_caravan_import_resource();
            return resource_to_import;
        }
    }
    // add to empty bay
    space = warehouse;
    for (int i = 0; i < 8; i++) {
        space = space->next();
        if (space->id > 0 && !space->stored_full_amount) {
            building_storageyard_space_add_import(space, resource_to_import);
            city_trade_next_caravan_import_resource();
            return resource_to_import;
        }
    }
    // find another importable resource that can be added to this warehouse
    for (int r = RESOURCE_MIN; r < RESOURCES_MAX; r++) {
        resource_to_import = city_trade_next_caravan_backup_import_resource();
        if (empire_can_import_resource_from_city(city_id, resource_to_import)) {
            space = warehouse;
            for (int i = 0; i < 8; i++) {
                space = space->next();
                if (space->id > 0 && space->stored_full_amount < 400
                    && space->subtype.warehouse_resource_id == resource_to_import) {
                    building_storageyard_space_add_import(space, resource_to_import);
                    return resource_to_import;
                }
            }
        }
    }
    return 0;
}
int figure_trade_ship_is_trading(figure* ship) {
    building* b = ship->destination();
    if (b->state != BUILDING_STATE_VALID || b->type != BUILDING_DOCK)
        return TRADE_SHIP_BUYING;

    for (int i = 0; i < 3; i++) {
        figure* f = figure_get(b->data.dock.docker_ids[i]);
        if (!b->data.dock.docker_ids[i] || f->state != FIGURE_STATE_ALIVE)
            continue;

        switch (f->action_state) {
        case FIGURE_ACTION_133_DOCKER_IMPORT_QUEUE:
        case FIGURE_ACTION_135_DOCKER_IMPORT_GOING_TO_WAREHOUSE:
        case FIGURE_ACTION_138_DOCKER_IMPORT_RETURNING:
        case FIGURE_ACTION_139_DOCKER_IMPORT_AT_WAREHOUSE:
            return TRADE_SHIP_BUYING;
        case FIGURE_ACTION_134_DOCKER_EXPORT_QUEUE:
        case FIGURE_ACTION_136_DOCKER_EXPORT_GOING_TO_WAREHOUSE:
        case FIGURE_ACTION_137_DOCKER_EXPORT_RETURNING:
        case FIGURE_ACTION_140_DOCKER_EXPORT_AT_WAREHOUSE:
            return TRADE_SHIP_SELLING;
        }
    }
    return TRADE_SHIP_NONE;
}

int figure::get_closest_storageyard(map_point tile, int city_id, int distance_from_entry, map_point* warehouse) {
    int exportable[RESOURCES_MAX];
    int importable[RESOURCES_MAX];
    exportable[RESOURCE_NONE] = 0;
    importable[RESOURCE_NONE] = 0;
    for (int r = RESOURCE_MIN; r < RESOURCES_MAX; r++) {
        exportable[r] = empire_can_export_resource_to_city(city_id, r);
        if (trader_amount_bought >= 8)
            exportable[r] = 0;

        if (city_id)
            importable[r] = empire_can_import_resource_from_city(city_id, r);
        else { // exclude own city (id=0), shouldn't happen, but still..
            importable[r] = 0;
        }
        if (get_carrying_amount() >= 800)
            importable[r] = 0;
    }
    int num_importable = 0;
    for (int r = RESOURCE_MIN; r < RESOURCES_MAX; r++) {
        if (importable[r])
            num_importable++;
    }
    int min_distance = 10000;
    building* min_building = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || b->type != BUILDING_STORAGE_YARD)
            continue;

        if (!b->has_road_access || b->distance_from_entry <= 0)
            continue;

        if (!building_storage_get_permission(BUILDING_STORAGE_PERMISSION_TRADERS, b))
            continue;

        const building_storage* s = building_storage_get(b->storage_id);
        int num_imports_for_warehouse = 0;
        for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; r = (e_resource)(r + 1)) {
            if (!building_storageyard_is_not_accepting(r, b) && empire_can_import_resource_from_city(city_id, r))
                num_imports_for_warehouse++;
        }
        int distance_penalty = 32;
        building* space = b;
        for (int space_cnt = 0; space_cnt < 8; space_cnt++) {
            space = space->next();
            if (space->id && exportable[space->subtype.warehouse_resource_id])
                distance_penalty -= 4;

            if (num_importable && num_imports_for_warehouse && !s->empty_all) {
                for (int r = RESOURCE_MIN; r < RESOURCES_MAX; r++) {
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
        map_point_store_result(min_building->tile.x(), min_building->tile.y(), warehouse);
    } else if (!map_has_road_access(min_building->tile, 3, warehouse)) {
        return 0;
    }

    return min_building->id;
}
void figure::go_to_next_storageyard(map_point src_tile, int distance_to_entry) {
    map_point dst;
    int warehouse_id = get_closest_storageyard(src_tile, empire_city_id, distance_to_entry, &dst);
    if (warehouse_id && warehouse_id != destinationID()) {
        set_destination(warehouse_id);
        action_state = FIGURE_ACTION_101_TRADE_CARAVAN_ARRIVING;
        destination_tile = dst;
        //        destination_tile.x() = dst.x();
        //        destination_tile.y() = dst.y();
    } else {
        map_point& exit = city_map_exit_point();
        action_state = FIGURE_ACTION_103_TRADE_CARAVAN_LEAVING;
        destination_tile = exit;
        //        destination_tile.x() = exit->x();
        //        destination_tile.y() = exit->y();
    }
}
int figure::trade_ship_lost_queue() {
    building* b = destination();
    if (b->state == BUILDING_STATE_VALID && b->type == BUILDING_DOCK && b->num_workers > 0
        && b->data.dock.trade_ship_id == id) {
        return 0;
    }
    return 1;
}
int figure::trade_ship_done_trading() {
    building* b = destination();
    if (b->state == BUILDING_STATE_VALID && b->type == BUILDING_DOCK && b->num_workers > 0) {
        for (int i = 0; i < 3; i++) {
            if (b->data.dock.docker_ids[i]) {
                figure* docker = figure_get(b->data.dock.docker_ids[i]);
                if (docker->state == FIGURE_STATE_ALIVE && docker->action_state != FIGURE_ACTION_132_DOCKER_IDLING)
                    return 0;
            }
        }
        trade_ship_failed_dock_attempts++;
        if (trade_ship_failed_dock_attempts >= 10) {
            trade_ship_failed_dock_attempts = 11;
            return 1;
        }
        return 0;
    }
    return 1;
}

void figure::trade_caravan_action() {
    switch (action_state) {
    default:
    case FIGURE_ACTION_100_TRADE_CARAVAN_CREATED:
    case 8:
        wait_ticks++;
        if (wait_ticks > 20) {
            wait_ticks = 0;
            map_point base_tile;
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
        do_gotobuilding(destination(),
                        true,
                        TERRAIN_USAGE_ROADS,
                        FIGURE_ACTION_102_TRADE_CARAVAN_TRADING,
                        FIGURE_ACTION_100_TRADE_CARAVAN_CREATED);
        break;
    case FIGURE_ACTION_102_TRADE_CARAVAN_TRADING:
    case 10:
        wait_ticks++;
        if (wait_ticks > 10) {
            wait_ticks = 0;
            int move_on = 0;
            if (figure_trade_caravan_can_buy(this, destination(), empire_city_id)) {
                int resource = trader_get_buy_resource(destination(), empire_city_id);
                if (resource) {
                    trade_route_increase_traded(empire_city_get_route_id(empire_city_id), resource);
                    trader_record_bought_resource(trader_id, resource);
                    trader_buy(100);
                } else
                    move_on++;
            } else
                move_on++;
            if (move_on > 0 && figure_trade_caravan_can_sell(this, destination(), empire_city_id)) {
                int resource = trader_get_sell_resource(destination(), empire_city_id);
                if (resource) {
                    trade_route_increase_traded(empire_city_get_route_id(empire_city_id), resource);
                    trader_record_sold_resource(trader_id, resource);
                    trader_sell(100);
                } else
                    move_on++;
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
        do_goto(destination_tile, TERRAIN_USAGE_PREFER_ROADS);
        break;
    }
    int dir = figure_image_normalize_direction(direction < 8 ? direction : previous_tile_direction);
    sprite_image_id = image_id_from_group(GROUP_FIGURE_TRADE_CARAVAN) + dir + 8 * anim_frame;
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
    sprite_image_id = image_id_from_group(GROUP_FIGURE_TRADE_CARAVAN) + dir + 8 * anim_frame;
}
void figure::native_trader_action() {
    //    is_ghost = false;
    //    terrain_usage = TERRAIN_USAGE_ANY;
    //    figure_image_increase_offset(12);
    //    cart_image_id = 0;
    switch (action_state) {
    case FIGURE_ACTION_160_NATIVE_TRADER_GOING_TO_WAREHOUSE:
        move_ticks(1);
        if (direction == DIR_FIGURE_NONE)
            action_state = FIGURE_ACTION_163_NATIVE_TRADER_AT_WAREHOUSE;
        else if (direction == DIR_FIGURE_REROUTE)
            route_remove();
        else if (direction == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
            //                is_ghost = true;
        }
        if (destination()->state != BUILDING_STATE_VALID)
            poof();

        break;
    case ACTION_11_RETURNING_EMPTY:
    case FIGURE_ACTION_161_NATIVE_TRADER_RETURNING:
        move_ticks(1);
        if (direction == DIR_FIGURE_NONE || direction == DIR_FIGURE_CAN_NOT_REACH)
            poof();
        else if (direction == DIR_FIGURE_REROUTE)
            route_remove();

        break;
    case FIGURE_ACTION_162_NATIVE_TRADER_CREATED:
        //            is_ghost = true;
        wait_ticks++;
        if (wait_ticks > 10) {
            wait_ticks = 0;
            map_point tile;
            int building_id = get_closest_storageyard(tile, 0, -1, &tile);
            if (building_id) {
                action_state = FIGURE_ACTION_160_NATIVE_TRADER_GOING_TO_WAREHOUSE;
                set_destination(building_id);
                destination_tile = tile;
                //                    destination_tile.x() = tile.x();
                //                    destination_tile.y() = tile.y();
            } else {
                poof();
            }
        }
        anim_frame = 0;
        break;
    case FIGURE_ACTION_163_NATIVE_TRADER_AT_WAREHOUSE:
        wait_ticks++;
        if (wait_ticks > 10) {
            wait_ticks = 0;
            if (figure_trade_caravan_can_buy(this, destination(), 0)) {
                int resource = trader_get_buy_resource(destination(), 0);
                trader_record_bought_resource(trader_id, resource);
                trader_amount_bought += 3;
            } else {
                map_point tile;
                int building_id = get_closest_storageyard(tile, 0, -1, &tile);
                if (building_id) {
                    action_state = FIGURE_ACTION_160_NATIVE_TRADER_GOING_TO_WAREHOUSE;
                    set_destination(building_id);
                    destination_tile = tile;
                    //                        destination_tile.x() = tile.x();
                    //                        destination_tile.y() = tile.y();
                } else {
                    action_state = FIGURE_ACTION_161_NATIVE_TRADER_RETURNING;
                    destination_tile = source_tile;
                    //                        destination_tile.x() = source_tile.x();
                    //                        destination_tile.y() = source_tile.y();
                }
            }
        }
        anim_frame = 0;
        break;
    }
    int dir = figure_image_normalize_direction(direction < 8 ? direction : previous_tile_direction);

    if (action_state == FIGURE_ACTION_149_CORPSE) {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER) + 96 + figure_image_corpse_offset();
        cart_image_id = 0;
    } else {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER) + dir + 8 * anim_frame;
    }
    cart_image_id = image_id_from_group(GROUP_FIGURE_IMMIGRANT_CART) + 8
                    + 8 * resource_id; // BUGFIX should be within else statement?
    if (cart_image_id) {
        cart_image_id += dir;
        figure_image_set_cart_offset(dir);
    }
}
void figure::trade_ship_action() {
    //    is_ghost = false;
    allow_move_type = EMOVE_BOAT;
    //    figure_image_increase_offset(12);
    //    cart_image_id = 0;
    switch (action_state) {
    case FIGURE_ACTION_110_TRADE_SHIP_CREATED:
        load_resource(1200, resource_id);
        trader_amount_bought = 0;
        //            is_ghost = true;
        wait_ticks++;
        if (wait_ticks > 20) {
            wait_ticks = 0;
            map_point tile;
            int dock_id = building_dock_get_free_destination(id, &tile);
            if (dock_id) {
                set_destination(dock_id);
                action_state = FIGURE_ACTION_111_TRADE_SHIP_GOING_TO_DOCK;
                destination_tile = tile;
                //                    destination_tile.x() = tile.x();
                //                    destination_tile.y() = tile.y();
            } else if (building_dock_get_queue_destination(id, &tile)) {
                action_state = FIGURE_ACTION_113_TRADE_SHIP_GOING_TO_DOCK_QUEUE;
                destination_tile = tile;
                //                    destination_tile.x() = tile.x();
                //                    destination_tile.y() = tile.y();
            } else {
                poof();
            }
        }
        anim_frame = 0;
        break;
    case FIGURE_ACTION_111_TRADE_SHIP_GOING_TO_DOCK:
        move_ticks(1);
        height_adjusted_ticks = 0;
        if (direction == DIR_FIGURE_NONE)
            action_state = FIGURE_ACTION_112_TRADE_SHIP_MOORED;
        else if (direction == DIR_FIGURE_REROUTE)
            route_remove();
        else if (direction == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
            if (!city_message_get_category_count(MESSAGE_CAT_BLOCKED_DOCK)) {
                city_message_post(true, MESSAGE_NAVIGATION_IMPOSSIBLE, 0, 0);
                city_message_increase_category_count(MESSAGE_CAT_BLOCKED_DOCK);
            }
        }
        if (destination()->state != BUILDING_STATE_VALID) {
            action_state = FIGURE_ACTION_115_TRADE_SHIP_LEAVING;
            wait_ticks = 0;
            destination_tile = scenario_map_river_exit();
            //                map_point river_exit = scenario_map_river_exit();
            //                destination_tile.x() = river_exit.x();
            //                destination_tile.y() = river_exit.y();
        }
        break;

    case FIGURE_ACTION_112_TRADE_SHIP_MOORED:
        if (trade_ship_lost_queue()) {
            trade_ship_failed_dock_attempts = 0;
            action_state = FIGURE_ACTION_115_TRADE_SHIP_LEAVING;
            wait_ticks = 0;
            destination_tile = scenario_map_river_entry();
            //                map_point river_entry = scenario_map_river_entry();
            //                destination_tile.x() = river_entry.x();
            //                destination_tile.y() = river_entry.y();
        } else if (trade_ship_done_trading()) {
            trade_ship_failed_dock_attempts = 0;
            action_state = FIGURE_ACTION_115_TRADE_SHIP_LEAVING;
            wait_ticks = 0;
            destination_tile = scenario_map_river_entry();
            //                map_point river_entry = scenario_map_river_entry();
            //                destination_tile.x() = river_entry.x();
            //                destination_tile.y() = river_entry.y();
            building* dst = destination();
            dst->data.dock.queued_docker_id = 0;
            dst->data.dock.num_ships = 0;
        }
        switch (destination()->data.dock.orientation) {
        case 0:
            direction = DIR_2_BOTTOM_RIGHT;
            break;
        case 1:
            direction = DIR_4_BOTTOM_LEFT;
            break;
        case 2:
            direction = DIR_6_TOP_LEFT;
            break;
        default:
            direction = DIR_0_TOP_RIGHT;
            break;
        }
        anim_frame = 0;
        city_message_reset_category_count(MESSAGE_CAT_BLOCKED_DOCK);
        break;

    case FIGURE_ACTION_113_TRADE_SHIP_GOING_TO_DOCK_QUEUE:
        move_ticks(1);
        height_adjusted_ticks = 0;
        if (direction == DIR_FIGURE_NONE)
            action_state = FIGURE_ACTION_114_TRADE_SHIP_ANCHORED;
        else if (direction == DIR_FIGURE_REROUTE)
            route_remove();
        else if (direction == DIR_FIGURE_CAN_NOT_REACH)
            poof();

        break;

    case FIGURE_ACTION_114_TRADE_SHIP_ANCHORED:
        wait_ticks++;
        if (wait_ticks > 40) {
            map_point tile;
            int dock_id = building_dock_get_free_destination(id, &tile);
            if (dock_id) {
                set_destination(dock_id);
                action_state = FIGURE_ACTION_111_TRADE_SHIP_GOING_TO_DOCK;
                destination_tile = tile;
                //                    destination_tile.x() = tile.x();
                //                    destination_tile.y() = tile.y();
            } else if (map_figure_id_get(tile) != id && building_dock_get_queue_destination(id, &tile)) {
                action_state = FIGURE_ACTION_113_TRADE_SHIP_GOING_TO_DOCK_QUEUE;
                destination_tile = tile;
                //                    destination_tile.x() = tile.x();
                //                    destination_tile.y() = tile.y();
            }
            wait_ticks = 0;
        }
        anim_frame = 0;
        break;

    case FIGURE_ACTION_115_TRADE_SHIP_LEAVING:
        move_ticks(1);
        height_adjusted_ticks = 0;
        if (direction == DIR_FIGURE_NONE) {
            action_state = FIGURE_ACTION_110_TRADE_SHIP_CREATED;
            poof();
        } else if (direction == DIR_FIGURE_REROUTE)
            route_remove();
        else if (direction == DIR_FIGURE_CAN_NOT_REACH)
            poof();

        break;
    }
    int dir = figure_image_normalize_direction(direction < 8 ? direction : previous_tile_direction);
    sprite_image_id = image_id_from_group(GROUP_FIGURE_SHIP) + dir;
}
