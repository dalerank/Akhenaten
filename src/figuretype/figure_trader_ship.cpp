#include "figure_trader_ship.h"

#include "figure/figure.h"
#include "figure/image.h"
#include "building/dock.h"

#include "city/message.h"

#include "graphics/image.h"
#include "grid/figure.h"

int figure_create_trade_ship(tile2i tile, int city_id) {
    figure* ship = figure_create(FIGURE_TRADE_SHIP, tile, DIR_0_TOP_RIGHT);
    ship->empire_city_id = city_id;
    ship->action_state = FIGURE_ACTION_110_TRADE_SHIP_CREATED;
    ship->wait_ticks = 10;
    return ship->id;
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
    sprite_image_id = image_id_from_group(IMG_FISHING_BOAT) + dir;
}
