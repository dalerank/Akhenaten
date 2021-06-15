#include "trader.h"

#include "building/building.h"
#include "building/dock.h"
#include "building/warehouse.h"
#include "building/storage.h"
#include "city/buildings.h"
#include "city/finance.h"
#include "city/map.h"
#include "city/message.h"
#include "city/resource.h"
#include "city/trade.h"
#include "core/calc.h"
#include "core/image.h"
#include "empire/city.h"
#include "empire/empire.h"
#include "empire/trade_prices.h"
#include "empire/trade_route.h"
#include "figure/combat.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "figure/trader.h"
#include "map/figure.h"
#include "map/road_access.h"
#include "scenario/map.h"

int figure_create_trade_caravan(int x, int y, int city_id) {
    figure *caravan = figure_create(FIGURE_TRADE_CARAVAN, x, y, DIR_0_TOP_RIGHT);
    caravan->empire_city_id = city_id;
    caravan->action_state = FIGURE_ACTION_100_TRADE_CARAVAN_CREATED;
    caravan->wait_ticks = 10;
    // donkey 1
    figure *donkey1 = figure_create(FIGURE_TRADE_CARAVAN_DONKEY, x, y, DIR_0_TOP_RIGHT);
    donkey1->action_state = FIGURE_ACTION_100_TRADE_CARAVAN_CREATED;
    donkey1->leading_figure_id = caravan->id;
    // donkey 2
    figure *donkey2 = figure_create(FIGURE_TRADE_CARAVAN_DONKEY, x, y, DIR_0_TOP_RIGHT);
    donkey2->action_state = FIGURE_ACTION_100_TRADE_CARAVAN_CREATED;
    donkey2->leading_figure_id = donkey1->id;
    return caravan->id;
}
int figure_create_trade_ship(int x, int y, int city_id) {
    figure *ship = figure_create(FIGURE_TRADE_SHIP, x, y, DIR_0_TOP_RIGHT);
    ship->empire_city_id = city_id;
    ship->action_state = FIGURE_ACTION_110_TRADE_SHIP_CREATED;
    ship->wait_ticks = 10;
    return ship->id;
}
int figure_trade_caravan_can_buy(figure *trader, int warehouse_id, int city_id) {
    building *warehouse = building_get(warehouse_id);
    if (warehouse->type != BUILDING_WAREHOUSE)
        return 0;

    if (trader->trader_amount_bought >= 8)
        return 0;

    if (!building_storage_get_permission(BUILDING_STORAGE_PERMISSION_TRADERS, warehouse))
        return 0;

    building *space = warehouse;
    for (int i = 0; i < 8; i++) {
        space = building_next(space);
        if (space->id > 0 && space->loads_stored > 0 &&
            empire_can_export_resource_to_city(city_id, space->subtype.warehouse_resource_id)) {
            return 1;
        }
    }
    return 0;
}
int figure_trade_caravan_can_sell(figure *trader, int warehouse_id, int city_id) {
    building *warehouse = building_get(warehouse_id);
    if (warehouse->type != BUILDING_WAREHOUSE)
        return 0;

    if (trader->get_carrying_amount() >= 800)
        return 0;

    if (!building_storage_get_permission(BUILDING_STORAGE_PERMISSION_TRADERS, warehouse))
        return 0;

    const building_storage *storage = building_storage_get(warehouse->storage_id);
    if (storage->empty_all)
        return 0;

    int num_importable = 0;
    for (int r = RESOURCE_MIN; r < RESOURCE_MAX[GAME_ENV]; r++) {
        if (!building_warehouse_is_not_accepting(r, warehouse)) {
            if (empire_can_import_resource_from_city(city_id, r))
                num_importable++;

        }
    }
    if (num_importable <= 0)
        return 0;

    int can_import = 0;
    int resource = city_trade_current_caravan_import_resource();
    if (!building_warehouse_is_not_accepting(resource, warehouse) &&
        empire_can_import_resource_from_city(city_id, resource)) {
        can_import = 1;
    } else {
        for (int i = RESOURCE_MIN; i < RESOURCE_MAX[GAME_ENV]; i++) {
            resource = city_trade_next_caravan_import_resource();
            if (!building_warehouse_is_not_accepting(resource, warehouse) &&
                empire_can_import_resource_from_city(city_id, resource)) {
                can_import = 1;
                break;
            }
        }
    }
    if (can_import) {
        // at least one resource can be imported and accepted by this warehouse
        // check if warehouse can store any importable goods
        building *space = warehouse;
        for (int s = 0; s < 8; s++) {
            space = building_next(space);
            if (space->id > 0 && space->loads_stored < 4) {
                if (!space->loads_stored) {
                    // empty space
                    return 1;
                }
                if (empire_can_import_resource_from_city(city_id, space->subtype.warehouse_resource_id))
                    return 1;

            }
        }
    }
    return 0;
}
static int trader_get_buy_resource(int warehouse_id, int city_id) {
    building *warehouse = building_get(warehouse_id);
    if (warehouse->type != BUILDING_WAREHOUSE)
        return RESOURCE_NONE;

    building *space = warehouse;
    for (int i = 0; i < 8; i++) {
        space = building_next(space);
        if (space->id <= 0)
            continue;

        int resource = space->subtype.warehouse_resource_id;
        if (space->loads_stored > 0 && empire_can_export_resource_to_city(city_id, resource)) {
            // update stocks
            city_resource_remove_from_warehouse(resource, 1);
            space->loads_stored--;
            if (space->loads_stored <= 0)
                space->subtype.warehouse_resource_id = RESOURCE_NONE;

            // update finances
            city_finance_process_export(trade_price_sell(resource));

            // update graphics
            building_warehouse_space_set_image(space, resource);
            return resource;
        }
    }
    return 0;
}
static int trader_get_sell_resource(int warehouse_id, int city_id) {
    building *warehouse = building_get(warehouse_id);
    if (warehouse->type != BUILDING_WAREHOUSE)
        return 0;

    int resource_to_import = city_trade_current_caravan_import_resource();
    int imp = RESOURCE_MIN;
    while (imp < RESOURCE_MAX[GAME_ENV] && !empire_can_import_resource_from_city(city_id, resource_to_import)) {
        imp++;
        resource_to_import = city_trade_next_caravan_import_resource();
    }
    if (imp >= RESOURCE_MAX[GAME_ENV])
        return 0;

    // add to existing bay with room
    building *space = warehouse;
    for (int i = 0; i < 8; i++) {
        space = building_next(space);
        if (space->id > 0 && space->loads_stored > 0 && space->loads_stored < 4 &&
            space->subtype.warehouse_resource_id == resource_to_import) {
            building_warehouse_space_add_import(space, resource_to_import);
            city_trade_next_caravan_import_resource();
            return resource_to_import;
        }
    }
    // add to empty bay
    space = warehouse;
    for (int i = 0; i < 8; i++) {
        space = building_next(space);
        if (space->id > 0 && !space->loads_stored) {
            building_warehouse_space_add_import(space, resource_to_import);
            city_trade_next_caravan_import_resource();
            return resource_to_import;
        }
    }
    // find another importable resource that can be added to this warehouse
    for (int r = RESOURCE_MIN; r < RESOURCE_MAX[GAME_ENV]; r++) {
        resource_to_import = city_trade_next_caravan_backup_import_resource();
        if (empire_can_import_resource_from_city(city_id, resource_to_import)) {
            space = warehouse;
            for (int i = 0; i < 8; i++) {
                space = building_next(space);
                if (space->id > 0 && space->loads_stored < 4 &&
                    space->subtype.warehouse_resource_id == resource_to_import) {
                    building_warehouse_space_add_import(space, resource_to_import);
                    return resource_to_import;
                }
            }
        }
    }
    return 0;
}
int figure_trade_ship_is_trading(figure *ship) {
    building *b = building_get(ship->destination_building_id);
    if (b->state != BUILDING_STATE_VALID || b->type != BUILDING_DOCK)
        return TRADE_SHIP_BUYING;

    for (int i = 0; i < 3; i++) {
        figure *f = figure_get(b->data.dock.docker_ids[i]);
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

int figure::get_closest_warehouse(int x, int y, int city_id, int distance_from_entry, map_point *warehouse) {
    int exportable[RESOURCE_MAX[GAME_ENV]];
    int importable[RESOURCE_MAX[GAME_ENV]];
    exportable[RESOURCE_NONE] = 0;
    importable[RESOURCE_NONE] = 0;
    for (int r = RESOURCE_MIN; r < RESOURCE_MAX[GAME_ENV]; r++) {
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
    for (int r = RESOURCE_MIN; r < RESOURCE_MAX[GAME_ENV]; r++) {
        if (importable[r])
            num_importable++;

    }
    int min_distance = 10000;
    building *min_building = 0;
    for (int i = 1; i < MAX_BUILDINGS[GAME_ENV]; i++) {
        building *b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || b->type != BUILDING_WAREHOUSE)
            continue;

        if (!b->has_road_access || b->distance_from_entry <= 0)
            continue;

        if (!building_storage_get_permission(BUILDING_STORAGE_PERMISSION_TRADERS, b))
            continue;

        const building_storage *s = building_storage_get(b->storage_id);
        int num_imports_for_warehouse = 0;
        for (int r = RESOURCE_MIN; r < RESOURCE_MAX[GAME_ENV]; r++) {
            if (!building_warehouse_is_not_accepting(r, b) && empire_can_import_resource_from_city(city_id, r))
                num_imports_for_warehouse++;

        }
        int distance_penalty = 32;
        building *space = b;
        for (int space_cnt = 0; space_cnt < 8; space_cnt++) {
            space = building_next(space);
            if (space->id && exportable[space->subtype.warehouse_resource_id])
                distance_penalty -= 4;

            if (num_importable && num_imports_for_warehouse && !s->empty_all) {
                for (int r = RESOURCE_MIN; r < RESOURCE_MAX[GAME_ENV]; r++) {
                    if (!building_warehouse_is_not_accepting(city_trade_next_caravan_import_resource(), b))
                        break;

                }
                int resource = city_trade_current_caravan_import_resource();
                if (!building_warehouse_is_not_accepting(resource, b)) {
                    if (space->subtype.warehouse_resource_id == RESOURCE_NONE)
                        distance_penalty -= 16;

                    if (space->id && importable[space->subtype.warehouse_resource_id] && space->loads_stored < 4 &&
                        space->subtype.warehouse_resource_id == resource) {
                        distance_penalty -= 8;
                    }
                }
            }
        }
        if (distance_penalty < 32) {
            int distance = calc_distance_with_penalty(b->x, b->y, x, y, distance_from_entry, b->distance_from_entry);
            distance += distance_penalty;
            if (distance < min_distance) {
                min_distance = distance;
                min_building = b;
            }
        }
    }
    if (!min_building)
        return 0;

    if (min_building->has_road_access == 1)
        map_point_store_result(min_building->x, min_building->y, warehouse);
    else if (!map_has_road_access(min_building->x, min_building->y, 3, warehouse))
        return 0;

    return min_building->id;
}
void figure::go_to_next_warehouse(int x_src, int y_src, int distance_to_entry) {
    map_point dst;
    int warehouse_id = get_closest_warehouse(x_src, y_src, empire_city_id, distance_to_entry, &dst);
    if (warehouse_id) {
        destination_building_id = warehouse_id;
        action_state = FIGURE_ACTION_101_TRADE_CARAVAN_ARRIVING;
        destination_x = dst.x;
        destination_y = dst.y;
    } else {
        const map_tile *exit = city_map_exit_point();
        action_state = FIGURE_ACTION_103_TRADE_CARAVAN_LEAVING;
        destination_x = exit->x;
        destination_y = exit->y;
    }
}
int figure::trade_ship_lost_queue() {
    building *b = building_get(destination_building_id);
    if (b->state == BUILDING_STATE_VALID && b->type == BUILDING_DOCK &&
        b->num_workers > 0 && b->data.dock.trade_ship_id == id) {
        return 0;
    }
    return 1;
}
int figure::trade_ship_done_trading() {
    building *b = building_get(destination_building_id);
    if (b->state == BUILDING_STATE_VALID && b->type == BUILDING_DOCK && b->num_workers > 0) {
        for (int i = 0; i < 3; i++) {
            if (b->data.dock.docker_ids[i]) {
                figure *docker = figure_get(b->data.dock.docker_ids[i]);
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
//    is_ghost = 0;
//    terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
//    figure_image_increase_offset(12);
//    cart_image_id = 0;
    switch (action_state) {
        case FIGURE_ACTION_100_TRADE_CARAVAN_CREATED:
            is_ghost = 1;
            wait_ticks++;
            if (wait_ticks > 20) {
                wait_ticks = 0;
                int x_base, y_base;
                int trade_center_id = city_buildings_get_trade_center();
                if (trade_center_id) {
                    building *trade_center = building_get(trade_center_id);
                    x_base = trade_center->x;
                    y_base = trade_center->y;
                } else {
                    x_base = tile_x;
                    y_base = tile_y;
                }
                go_to_next_warehouse(x_base, y_base, 0);
            }
            anim_frame = 0;
            break;
        case FIGURE_ACTION_101_TRADE_CARAVAN_ARRIVING:
            move_ticks(1);
            switch (direction) {
                case DIR_FIGURE_AT_DESTINATION:
                    action_state = FIGURE_ACTION_102_TRADE_CARAVAN_TRADING;
                    break;
                case DIR_FIGURE_REROUTE:
                    route_remove();
                    break;
                case DIR_FIGURE_LOST:
                    poof();
                    is_ghost = 1;
                    break;
            }
            if (building_get(destination_building_id)->state != BUILDING_STATE_VALID)
                poof();

            break;
        case FIGURE_ACTION_102_TRADE_CARAVAN_TRADING:
            wait_ticks++;
            if (wait_ticks > 10) {
                wait_ticks = 0;
                int move_on = 0;
                if (figure_trade_caravan_can_buy(this, destination_building_id, empire_city_id)) {
                    int resource = trader_get_buy_resource(destination_building_id, empire_city_id);
                    if (resource) {
                        trade_route_increase_traded(empire_city_get_route_id(empire_city_id), resource);
                        trader_record_bought_resource(trader_id, resource);
                        trader_amount_bought++;
                    } else {
                        move_on++;
                    }
                } else {
                    move_on++;
                }
                if (figure_trade_caravan_can_sell(this, destination_building_id, empire_city_id)) {
                    int resource = trader_get_sell_resource(destination_building_id, empire_city_id);
                    if (resource) {
                        trade_route_increase_traded(empire_city_get_route_id(empire_city_id), resource);
                        trader_record_sold_resource(trader_id, resource);
                        load_resource(100, resource);
                    } else {
                        move_on++;
                    }
                } else {
                    move_on++;
                }
                if (move_on == 2)
                    go_to_next_warehouse(tile_x, tile_y, -1);

            }
            anim_frame = 0;
            break;
        case FIGURE_ACTION_103_TRADE_CARAVAN_LEAVING:
            move_ticks(1);
            switch (direction) {
                case DIR_FIGURE_AT_DESTINATION:
                    action_state = FIGURE_ACTION_100_TRADE_CARAVAN_CREATED;
                    poof();
                    break;
                case DIR_FIGURE_REROUTE:
                    route_remove();
                    break;
                case DIR_FIGURE_LOST:
                    poof();
                    break;
            }
            break;
    }
    int dir = figure_image_normalize_direction(direction < 8 ? direction : previous_tile_direction);
    sprite_image_id = image_id_from_group(GROUP_FIGURE_TRADE_CARAVAN) + dir + 8 * anim_frame;
}
void figure::trade_caravan_donkey_action() {
//    is_ghost = 0;
//    terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
//    figure_image_increase_offset(12);
//    cart_image_id = 0;

    figure *leader = figure_get(leading_figure_id);
//    if (leading_figure_id <= 0)
//        poof();
//    else {
        if (leader->action_state == FIGURE_ACTION_149_CORPSE)
            poof();
        else if (leader->state != FIGURE_STATE_ALIVE)
            poof();
        else if (leader->type != FIGURE_TRADE_CARAVAN && leader->type != FIGURE_TRADE_CARAVAN_DONKEY)
            poof();
        else {
            follow_ticks(1);
        }
//    }

//    if (leader->is_ghost)
//        is_ghost = 1;

    int dir = figure_image_normalize_direction(direction < 8 ? direction : previous_tile_direction);
    sprite_image_id = image_id_from_group(GROUP_FIGURE_TRADE_CARAVAN) + dir + 8 * anim_frame;
}
void figure::native_trader_action() {
//    is_ghost = 0;
//    terrain_usage = TERRAIN_USAGE_ANY;
//    figure_image_increase_offset(12);
//    cart_image_id = 0;
    switch (action_state) {
        case FIGURE_ACTION_160_NATIVE_TRADER_GOING_TO_WAREHOUSE:
            move_ticks(1);
            if (direction == DIR_FIGURE_AT_DESTINATION)
                action_state = FIGURE_ACTION_163_NATIVE_TRADER_AT_WAREHOUSE;
            else if (direction == DIR_FIGURE_REROUTE)
                route_remove();
            else if (direction == DIR_FIGURE_LOST) {
                poof();
                is_ghost = 1;
            }
            if (building_get(destination_building_id)->state != BUILDING_STATE_VALID)
                poof();

            break;
        case ACTION_11_RETURNING_EMPTY:
        case FIGURE_ACTION_161_NATIVE_TRADER_RETURNING:
            move_ticks(1);
            if (direction == DIR_FIGURE_AT_DESTINATION || direction == DIR_FIGURE_LOST)
                poof();
            else if (direction == DIR_FIGURE_REROUTE)
                route_remove();

            break;
        case FIGURE_ACTION_162_NATIVE_TRADER_CREATED:
            is_ghost = 1;
            wait_ticks++;
            if (wait_ticks > 10) {
                wait_ticks = 0;
                map_point tile;
                int building_id = get_closest_warehouse(tile_x, tile_y, 0, -1, &tile);
                if (building_id) {
                    action_state = FIGURE_ACTION_160_NATIVE_TRADER_GOING_TO_WAREHOUSE;
                    destination_building_id = building_id;
                    destination_x = tile.x;
                    destination_y = tile.y;
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
                if (figure_trade_caravan_can_buy(this, destination_building_id, 0)) {
                    int resource = trader_get_buy_resource(destination_building_id, 0);
                    trader_record_bought_resource(trader_id, resource);
                    trader_amount_bought += 3;
                } else {
                    map_point tile;
                    int building_id = get_closest_warehouse(tile_x, tile_y, 0, -1, &tile);
                    if (building_id) {
                        action_state = FIGURE_ACTION_160_NATIVE_TRADER_GOING_TO_WAREHOUSE;
                        destination_building_id = building_id;
                        destination_x = tile.x;
                        destination_y = tile.y;
                    } else {
                        action_state = FIGURE_ACTION_161_NATIVE_TRADER_RETURNING;
                        destination_x = source_x;
                        destination_y = source_y;
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
    cart_image_id = image_id_from_group(GROUP_FIGURE_MIGRANT_CART) +
                    8 + 8 * resource_id; // BUGFIX should be within else statement?
    if (cart_image_id) {
        cart_image_id += dir;
        figure_image_set_cart_offset(dir);
    }
}
void figure::trade_ship_action() {
//    is_ghost = 0;
    is_boat = 1;
//    figure_image_increase_offset(12);
//    cart_image_id = 0;
    switch (action_state) {
        case FIGURE_ACTION_110_TRADE_SHIP_CREATED:
            load_resource(1200, resource_id);
            trader_amount_bought = 0;
            is_ghost = 1;
            wait_ticks++;
            if (wait_ticks > 20) {
                wait_ticks = 0;
                map_point tile;
                int dock_id = building_dock_get_free_destination(id, &tile);
                if (dock_id) {
                    destination_building_id = dock_id;
                    action_state = FIGURE_ACTION_111_TRADE_SHIP_GOING_TO_DOCK;
                    destination_x = tile.x;
                    destination_y = tile.y;
                } else if (building_dock_get_queue_destination(id, &tile)) {
                    action_state = FIGURE_ACTION_113_TRADE_SHIP_GOING_TO_DOCK_QUEUE;
                    destination_x = tile.x;
                    destination_y = tile.y;
                } else {
                    poof();
                }
            }
            anim_frame = 0;
            break;
        case FIGURE_ACTION_111_TRADE_SHIP_GOING_TO_DOCK:
            move_ticks(1);
            height_adjusted_ticks = 0;
            if (direction == DIR_FIGURE_AT_DESTINATION)
                action_state = FIGURE_ACTION_112_TRADE_SHIP_MOORED;
            else if (direction == DIR_FIGURE_REROUTE)
                route_remove();
            else if (direction == DIR_FIGURE_LOST) {
                poof();
                if (!city_message_get_category_count(MESSAGE_CAT_BLOCKED_DOCK)) {
                    city_message_post(1, MESSAGE_NAVIGATION_IMPOSSIBLE, 0, 0);
                    city_message_increase_category_count(MESSAGE_CAT_BLOCKED_DOCK);
                }
            }
            if (building_get(destination_building_id)->state != BUILDING_STATE_VALID) {
                action_state = FIGURE_ACTION_115_TRADE_SHIP_LEAVING;
                wait_ticks = 0;
                map_point river_exit = scenario_map_river_exit();
                destination_x = river_exit.x;
                destination_y = river_exit.y;
            }
            break;
        case FIGURE_ACTION_112_TRADE_SHIP_MOORED:
            if (trade_ship_lost_queue()) {
                trade_ship_failed_dock_attempts = 0;
                action_state = FIGURE_ACTION_115_TRADE_SHIP_LEAVING;
                wait_ticks = 0;
                map_point river_entry = scenario_map_river_entry();
                destination_x = river_entry.x;
                destination_y = river_entry.y;
            } else if (trade_ship_done_trading()) {
                trade_ship_failed_dock_attempts = 0;
                action_state = FIGURE_ACTION_115_TRADE_SHIP_LEAVING;
                wait_ticks = 0;
                map_point river_entry = scenario_map_river_entry();
                destination_x = river_entry.x;
                destination_y = river_entry.y;
                building *dst = building_get(destination_building_id);
                dst->data.dock.queued_docker_id = 0;
                dst->data.dock.num_ships = 0;
            }
            switch (building_get(destination_building_id)->data.dock.orientation) {
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
            if (direction == DIR_FIGURE_AT_DESTINATION)
                action_state = FIGURE_ACTION_114_TRADE_SHIP_ANCHORED;
            else if (direction == DIR_FIGURE_REROUTE)
                route_remove();
            else if (direction == DIR_FIGURE_LOST)
                poof();

            break;
        case FIGURE_ACTION_114_TRADE_SHIP_ANCHORED:
            wait_ticks++;
            if (wait_ticks > 40) {
                map_point tile;
                int dock_id = building_dock_get_free_destination(id, &tile);
                if (dock_id) {
                    destination_building_id = dock_id;
                    action_state = FIGURE_ACTION_111_TRADE_SHIP_GOING_TO_DOCK;
                    destination_x = tile.x;
                    destination_y = tile.y;
                } else if (map_figure_at(grid_offset_figure) != id &&
                           building_dock_get_queue_destination(id, &tile)) {
                    action_state = FIGURE_ACTION_113_TRADE_SHIP_GOING_TO_DOCK_QUEUE;
                    destination_x = tile.x;
                    destination_y = tile.y;
                }
                wait_ticks = 0;
            }
            anim_frame = 0;
            break;
        case FIGURE_ACTION_115_TRADE_SHIP_LEAVING:
            move_ticks(1);
            height_adjusted_ticks = 0;
            if (direction == DIR_FIGURE_AT_DESTINATION) {
                action_state = FIGURE_ACTION_110_TRADE_SHIP_CREATED;
                poof();
            } else if (direction == DIR_FIGURE_REROUTE)
                route_remove();
            else if (direction == DIR_FIGURE_LOST)
                poof();

            break;
    }
    int dir = figure_image_normalize_direction(direction < 8 ? direction : previous_tile_direction);
    sprite_image_id = image_id_from_group(GROUP_FIGURE_SHIP) + dir;
}
