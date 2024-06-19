#include "figure_trader_ship.h"

#include "figure/figure.h"
#include "figure/image.h"
#include "figure/trader.h"
#include "figure_shipwreck.h"
#include "building/building_dock.h"

#include "city/message.h"

#include "graphics/image.h"
#include "grid/figure.h"
#include "js/js_game.h"

#include "dev/debug.h"
#include <iostream>

figures::model_t<figure_trade_ship> trader_ship_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_trade_ship);
void config_load_figure_trade_ship() {
    trader_ship_m.load();
}

declare_console_command_p(sinkallships, game_cheat_sink_all_ships)
void game_cheat_sink_all_ships(std::istream &is, std::ostream &os) {
    figure_valid_do([] (figure &f) {
        f.dcast()->kill();
    }, FIGURE_TRADE_SHIP, FIGURE_FISHING_BOAT);
}

int figure_trade_ship::create(tile2i tile, int city_id) {
    figure* ship = figure_create(FIGURE_TRADE_SHIP, tile, DIR_0_TOP_RIGHT);
    ship->empire_city_id = city_id;
    ship->action_state = FIGURE_ACTION_110_TRADE_SHIP_CREATED;
    ship->wait_ticks = 10;
    return ship->id;
}

int figure_trade_ship::is_trading() const {
    building* b = destination();
    if (b->state != BUILDING_STATE_VALID || b->type != BUILDING_DOCK) {
        return TRADE_SHIP_BUYING;
    }

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

int figure_trade_ship::lost_queue() {
    building* b = destination();
    if (b->state == BUILDING_STATE_VALID && b->type == BUILDING_DOCK && b->num_workers > 0
        && b->data.dock.trade_ship_id == id()) {
        return 0;
    }
    return 1;
}

int figure_trade_ship::done_trading() {
    building* b = destination();
    if (b->state == BUILDING_STATE_VALID && b->type == BUILDING_DOCK && b->num_workers > 0) {
        for (int i = 0; i < 3; i++) {
            if (b->data.dock.docker_ids[i]) {
                figure* docker = figure_get(b->data.dock.docker_ids[i]);
                if (docker->state == FIGURE_STATE_ALIVE && docker->action_state != FIGURE_ACTION_132_DOCKER_IDLING)
                    return 0;
            }
        }
        base.trade_ship_failed_dock_attempts++;
        if (base.trade_ship_failed_dock_attempts >= 10) {
            base.trade_ship_failed_dock_attempts = 11;
            return 1;
        }
        return 0;
    }
    return 1;
}

void figure_trade_ship::on_create() {
    base.trader_id = trader_create();
}

void figure_trade_ship::figure_action() {
    //    is_ghost = false;
    base.allow_move_type = EMOVE_BOAT;
    //    figure_image_increase_offset(12);
    //    cart_image_id = 0;
    switch (action_state()) {
    case FIGURE_ACTION_110_TRADE_SHIP_CREATED:
        load_resource(base.resource_id, 1200);
        base.trader_amount_bought = 0;
        //            is_ghost = true;
        base.wait_ticks++;
        if (base.wait_ticks > 20) {
            base.wait_ticks = 0;
            auto free_dock = map_get_free_destination_dock(id());
            if (free_dock.bid) {
                set_destination(free_dock.bid);
                base.action_state = FIGURE_ACTION_111_TRADE_SHIP_GOING_TO_DOCK;
                base.destination_tile = free_dock.tile;
                break;
            } 
            
            auto queued_dock = map_get_queue_destination_dock(id());
            if (queued_dock.bid) {
                base.action_state = FIGURE_ACTION_113_TRADE_SHIP_GOING_TO_DOCK_QUEUE;
                base.destination_tile = queued_dock.tile;
                break;
            } 
            
            poof();
        }
        base.anim.frame = 0;
        break;

    case FIGURE_ACTION_111_TRADE_SHIP_GOING_TO_DOCK:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE)
            base.action_state = FIGURE_ACTION_112_TRADE_SHIP_MOORED;
        else if (direction() == DIR_FIGURE_REROUTE)
            route_remove();
        else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
            if (!city_message_get_category_count(MESSAGE_CAT_BLOCKED_DOCK)) {
                city_message_post(true, MESSAGE_NAVIGATION_IMPOSSIBLE, 0, 0);
                city_message_increase_category_count(MESSAGE_CAT_BLOCKED_DOCK);
            }
        }
        if (destination()->state != BUILDING_STATE_VALID) {
            base.action_state = FIGURE_ACTION_115_TRADE_SHIP_LEAVING;
            base.wait_ticks = 0;
            base.destination_tile = scenario_map_river_exit();
            //                map_point river_exit = scenario_map_river_exit();
            //                destination_tile.x() = river_exit.x();
            //                destination_tile.y() = river_exit.y();
        }
        break;

    case FIGURE_ACTION_112_TRADE_SHIP_MOORED:
        if (lost_queue()) {
            base.trade_ship_failed_dock_attempts = 0;
            base.action_state = FIGURE_ACTION_115_TRADE_SHIP_LEAVING;
            base.wait_ticks = 0;
            base.destination_tile = scenario_map_river_entry();
        } else if (done_trading()) {
            base.trade_ship_failed_dock_attempts = 0;
            base.action_state = FIGURE_ACTION_115_TRADE_SHIP_LEAVING;
            base.wait_ticks = 0;
            base.destination_tile = scenario_map_river_entry();
            building* dst = destination();
            dst->data.dock.queued_docker_id = 0;
            dst->data.dock.num_ships = 0;
        }
        switch (destination()->data.dock.orientation) {
        case 0:
            base.direction = DIR_2_BOTTOM_RIGHT;
            break;
        case 1:
            base.direction = DIR_4_BOTTOM_LEFT;
            break;
        case 2:
            base.direction = DIR_6_TOP_LEFT;
            break;
        default:
            base.direction = DIR_0_TOP_RIGHT;
            break;
        }
        base.anim.frame = 0;
        city_message_reset_category_count(MESSAGE_CAT_BLOCKED_DOCK);
        break;

    case FIGURE_ACTION_113_TRADE_SHIP_GOING_TO_DOCK_QUEUE:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            base.action_state = FIGURE_ACTION_114_TRADE_SHIP_ANCHORED;
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }
        break;

    case FIGURE_ACTION_114_TRADE_SHIP_ANCHORED:
        base.wait_ticks++;
        if (base.wait_ticks > 40) {
            auto free_dock = map_get_free_destination_dock(id());
            if (free_dock.bid) {
                set_destination(free_dock.bid);
                base.action_state = FIGURE_ACTION_111_TRADE_SHIP_GOING_TO_DOCK;
                base.destination_tile = free_dock.tile;
                break;
            }
            
            auto queue_dock = map_get_queue_destination_dock(id());
            if (map_figure_id_get(free_dock.tile) != id() && queue_dock.bid) {
                base.action_state = FIGURE_ACTION_113_TRADE_SHIP_GOING_TO_DOCK_QUEUE;
                base.destination_tile = free_dock.tile;
            }
            base.wait_ticks = 0;
        }
        base.anim.frame = 0;
        break;

    case FIGURE_ACTION_115_TRADE_SHIP_LEAVING:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            base.action_state = FIGURE_ACTION_110_TRADE_SHIP_CREATED;
            poof();
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }

        break;
    }

    int dir = figure_image_normalize_direction(direction() < 8 ? direction() : base.previous_tile_direction);
    image_set_animation(trader_ship_m.anim["work"]);
}

sound_key figure_trade_ship::phrase_key() const {
    if (action_state() == FIGURE_ACTION_115_TRADE_SHIP_LEAVING) {
        if (!trader_has_traded(base.trader_id))
            return "no_trade"; // no trade
        else {
            return "good_trade"; // good trade
        }
    } else if (action_state() == FIGURE_ACTION_112_TRADE_SHIP_MOORED) {
        int state = is_trading();
        if (state == TRADE_SHIP_BUYING)
            return "waiting_for_cargo"; // buying goods
        else if (state == TRADE_SHIP_SELLING)
            return "looking_for_unload"; // selling goods
        else {
            return "no_trade";
        }
    } else {
        return "beatiful_journey"; // can't wait to trade
    }
}

void figure_trade_ship::kill() {
    destination()->data.dock.trade_ship_id = 0;
    base.set_home(0);
    base.wait_ticks = 0;
    figure_shipwreck::create(tile());
    figure_carrier::kill();
}
