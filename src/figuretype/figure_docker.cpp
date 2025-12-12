#include "figure_docker.h"

#include "building/building.h"
#include "building/building_storage_yard.h"
#include "building/building_storage_room.h"
#include "building/building_dock.h"
#include "city/buildings.h"
#include "city/city_buildings.h"
#include "city/city_trade.h"
#include "core/calc.h"
#include "empire/empire.h"
#include "empire/empire_map.h"
#include "empire/trade_route.h"
#include "figure/combat.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "empire/trader_handler.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/image_desc.h"
#include "grid/road_access.h"
#include "figuretype/figure_trader_ship.h"
#include "city/city_figures.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_docker);

bool figure_docker::try_import_resource(building* b, e_resource resource, empire_city_handle city) {
    building_storage_yard *warehouse = b->dcast_storage_yard();
    if (!warehouse) {
        return false;
    }

    if (warehouse->is_not_accepting(resource)) {
        return false;
    }

    if (!warehouse->get_permission(BUILDING_STORAGE_PERMISSION_DOCK)) {
        return false;
    }

    auto &trade_route = city.get_route();
    // try existing storage bay with the same resource
    building_storage_room* space = warehouse->room();
    while (space) {
        if (space->stored_amount(resource) > 0 && space->stored_amount(resource) < 400) {
            trade_route.increase_traded(resource, 100);
            space->add_import(resource);
            return true;
        }
        space = space->next_room();
    }
    // try unused storage bay
    space = warehouse->room();
    while (space) {
        if (space->resource() == RESOURCE_NONE) {
            trade_route.increase_traded(resource, 100);
            space->add_import(resource);
            return true;
        }
        space = space->next_room();
    }
    return false;
}

bool figure_docker::try_export_resource(building* b, e_resource resource, empire_city_handle city) {
    building_storage_yard *warehouse = b->dcast_storage_yard();
    if (!warehouse) {
        return 0;
    }

    if (!warehouse->get_permission(BUILDING_STORAGE_PERMISSION_DOCK)) {
        return 0;
    }

    building_storage_room* space = warehouse->room();
    while (space) {
        if (space->stored_amount(resource)) {
            auto &trade_route = city.get_route();
            trade_route.increase_traded(resource, 100);
            space->remove_export(resource);
            return 1;
        }
        space = space->next_room();
    }
    return 0;
}

building_dest figure_docker::get_closest_warehouse_for_import(tile2i pos, empire_city_handle city, int distance_from_entry, int road_network_id, e_resource& import_resource) {
    const resource_list importable = g_empire.importable_resources_from_city(city.handle);

    e_resource resource = city_trade_next_docker_import_resource();
    for (e_resource i = RESOURCES_MIN; i < RESOURCES_MAX && !importable[resource]; ++i) {
        resource = city_trade_next_docker_import_resource();
    }

    if (!importable[resource]) {
        return { 0, tile2i::invalid };
    }

    int min_distance = 10000;
    building_id min_building_id = 0;
    buildings_valid_do([&] (building &b) {
        building_storage_yard *warehouse = b.dcast_storage_yard();
        if (!warehouse || !warehouse->is_valid()) {
            return;
        }

        if (!warehouse->has_road_access() || warehouse->base.distance_from_entry <= 0) {
            return;
        }

        if (warehouse->road_network() != road_network_id) {
            return;
        }

        if (!warehouse->get_permission(BUILDING_STORAGE_PERMISSION_DOCK)) {
            return;
        }

        if (warehouse->is_not_accepting(resource)) {
            return;
        }

        if (warehouse->is_empty_all()) {
            return;
        }

        int distance_penalty = 32;
        building_storage_room *space = warehouse->room();
        while (space) {
            if (space->resource() == RESOURCE_NONE) {
                distance_penalty -= 8;
            }

            if (space->base.stored_amount(resource) < 400) {
                distance_penalty -= 4;
            }

            space = space->next_room();
        }

        if (distance_penalty < 32) {
            int distance = calc_distance_with_penalty(warehouse->tile(), pos, distance_from_entry, warehouse->base.distance_from_entry);
            // prefer emptier warehouse
            distance += distance_penalty;
            if (distance < min_distance) {
                min_distance = distance;
                min_building_id = b.id;
            }
        }
    }, BUILDING_STORAGE_YARD);

    if (!min_building_id) {
        return { 0, tile2i::invalid };
    }

    building* minb = building_get(min_building_id);
    tile2i warehouse_tile;
    if (minb->has_road_access) {
        warehouse_tile = minb->tile;
        map_point_store_result(minb->tile, warehouse_tile);
    } else {
        warehouse_tile = map_get_road_access_tile(minb->tile, 3);
        if (!warehouse_tile.valid()) {
            return { 0, warehouse_tile };
        }
    }

    import_resource = resource;
    return { min_building_id, warehouse_tile };
}

building_dest figure_docker::get_closest_warehouse_for_export(tile2i pos, empire_city_handle city, int distance_from_entry, int road_network_id, e_resource &export_resource) {
    const resource_list exportable = g_empire.exportable_resources_from_city(city.handle);

    e_resource resource = city_trade_next_docker_export_resource();
    for (int i = RESOURCES_MIN; i < RESOURCES_MAX && !exportable[resource]; i++) {
        resource = city_trade_next_docker_export_resource();
    }

    if (!exportable[resource]) {
        return { 0, tile2i::invalid };
    }

    int min_distance = 10000;
    building_id min_building_id = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building *b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || b->type != BUILDING_STORAGE_YARD)
            continue;

        if (!b->has_road_access || b->distance_from_entry <= 0)
            continue;

        if (b->road_network_id != road_network_id)
            continue;

        building_storage_yard *warehouse = b->dcast_storage_yard();
        if (!warehouse->get_permission(BUILDING_STORAGE_PERMISSION_DOCK)) {
            continue;
        }

        int distance_penalty = 32;
        building_storage_room *space = warehouse->room();
        while (space) {
            if (space->stored_amount(resource) > 0) {
                distance_penalty--;
            }

            space = space->next_room();
        }

        if (distance_penalty < 32) {
            int distance = calc_distance_with_penalty(b->tile, pos, distance_from_entry, b->distance_from_entry);
            // prefer fuller warehouse
            distance += distance_penalty;
            if (distance < min_distance) {
                min_distance = distance;
                min_building_id = i;
            }
        }
    }

    if (!min_building_id) {
        return { 0, tile2i::invalid };
    }

    building *minb = building_get(min_building_id);
    tile2i warehouse_tile;
    if (minb->has_road_access == 1) {
        warehouse_tile = minb->tile;
        map_point_store_result(minb->tile, warehouse_tile);
    } else {
        warehouse_tile = map_get_road_access_tile(minb->tile, 3);
        if (!warehouse_tile.valid()) {
            return { 0, warehouse_tile };
        }
    }

    export_resource = resource;
    return { min_building_id, warehouse_tile };
}

tile2i figure_docker::get_trade_center_location() {
    int trade_center_id = city_buildings_get_trade_center();
    if (trade_center_id) {
        building *trade_center = building_get(trade_center_id);
        return trade_center->tile;
    } else {
        return tile();
    }
}

empire_trader_handle figure_docker::trader() {
    auto dock = home()->dcast_dock();
    return dock ? dock->empire_trader() : empire_trader_handle{};
}

empire_city_handle figure_docker::trader_city() {
    auto dock = home()->dcast_dock();
    return dock ? dock->trader_city() : empire_city_handle{};
}

bool figure_docker::deliver_import_resource(building* b) {
    building_dock *dock = b->dcast_dock();

    int ship_id = dock->runtime_data().trade_ship;
    if (!ship_id) {
        return false;
    }

    auto ship  = figure_get<figure_trade_ship>(ship_id);
    if (ship->action_state() != ACTION_112_TRADE_SHIP_MOORED || ship->base.get_carrying_amount() <= 0) {
        return false;
    }

    tile2i trade_center_tile = get_trade_center_location();
    e_resource resource;
    auto result = get_closest_warehouse_for_import(trade_center_tile, ship->empire_city(), b->distance_from_entry, b->road_network_id, resource);
    if (!result.bid) {
        return false;
    }

    ship->dump_resource(100);
    set_destination(result.bid);
    base.wait_ticks = 0;
    advance_action(ACTION_133_DOCKER_IMPORT_QUEUE);
    base.destination_tile = result.tile;
    base.resource_id = resource;
    base.resource_amount_full = 100;
    return true;
}

bool figure_docker::fetch_export_resource(building* b) {
    building_dock *dock = b->dcast_dock();

    figure_id ship_id = dock->runtime_data().trade_ship;
    if (!ship_id) {
        return false;
    }

    auto ship = figure_get<figure_trade_ship>(ship_id);
    if (ship->action_state() != ACTION_112_TRADE_SHIP_MOORED || ship->total_bought() >= ship->max_capacity()) {
        return false;
    }

    tile2i trade_cener_tile = get_trade_center_location();
    e_resource resource;
    auto result = get_closest_warehouse_for_export(trade_cener_tile, ship->empire_city(), b->distance_from_entry, b->road_network_id, resource);

    if (!result.bid) {
        return false;
    }

    ship->runtime_data().amount_bought += 100;
    set_destination(result.bid);
    advance_action(ACTION_136_DOCKER_EXPORT_GOING_TO_WAREHOUSE);
    base.wait_ticks = 0;
    base.destination_tile = result.tile;
    base.resource_id = resource;
    return true;
}

void figure_docker::figure_action() {
    building* b = home();

    base.use_cart = true;
    if (b->state != BUILDING_STATE_VALID) {
        poof();
    }

    if (b->type != BUILDING_DOCK && b->type != BUILDING_FISHING_WHARF) {
        poof();
    }

    auto &dock = b->dcast_dock()->runtime_data();
    if (dock.num_ships) {
        dock.num_ships--;
    }

    if (dock.trade_ship) {
        auto ship = figure_get<figure_trade_ship>(dock.trade_ship);
        if (ship->base.state != FIGURE_STATE_ALIVE || ship->type() != FIGURE_TRADE_SHIP) {
            dock.trade_ship = 0;
        } else if (ship->empire_trader().has_traded_max()) {
            dock.trade_ship = 0;
        } else if (ship->action_state() == ACTION_115_TRADE_SHIP_LEAVING) {
            dock.trade_ship = 0;
        }
    }

    base.terrain_usage = TERRAIN_USAGE_ROADS;
    switch (action_state()) {
    case ACTION_132_DOCKER_IDLING:
        base.resource_id = RESOURCE_NONE;
        base.cart_image_id = 0;
        base.animctx.frame = 0;
        if (!deliver_import_resource(b)) {
            fetch_export_resource(b);
        }
        break;

    case ACTION_133_DOCKER_IMPORT_QUEUE:
        base.cart_image_id = 0;
        base.animctx.frame = 0;
        if (dock.queued_docker_id <= 0) {
            dock.queued_docker_id = id();
            base.wait_ticks = 0;
        }

        if (dock.queued_docker_id == id()) {
            dock.num_ships = 120;
            base.wait_ticks++;
            if (base.wait_ticks >= 80) {
                advance_action(ACTION_135_DOCKER_IMPORT_GOING_TO_WAREHOUSE);
                base.wait_ticks = 0;
                //                    set_cart_graphic();
                dock.queued_docker_id = 0;
            }
        } else {
            int has_queued_docker = 0;
            for (int i = 0; i < 3; i++) {
                if (dock.docker_ids[i]) {
                    figure* docker = figure_get(dock.docker_ids[i]);
                    if (docker->id == dock.queued_docker_id && docker->state == FIGURE_STATE_ALIVE) {
                        if (docker->action_state == ACTION_133_DOCKER_IMPORT_QUEUE
                            || docker->action_state == ACTION_134_DOCKER_EXPORT_QUEUE) {
                            has_queued_docker = 1;
                        }
                    }
                }
            }

            if (!has_queued_docker) {
                dock.queued_docker_id = 0;
            }
        }
        break;

    case ACTION_134_DOCKER_EXPORT_QUEUE:
        if (dock.queued_docker_id <= 0) {
            dock.queued_docker_id = id();
            base.wait_ticks = 0;
        }
        if (dock.queued_docker_id == id()) {
            dock.num_ships = 120;
            base.wait_ticks++;
            if (base.wait_ticks >= 80) {
                advance_action(ACTION_132_DOCKER_IDLING);
                base.wait_ticks = 0;
                base.main_image_id = 0;
                base.cart_image_id = 0;
                dock.queued_docker_id = 0;
            }
        }
        base.wait_ticks++;
        if (base.wait_ticks >= 20) {
            advance_action(ACTION_132_DOCKER_IDLING);
            base.wait_ticks = 0;
        }
        base.animctx.frame = 0;
        break;

    case ACTION_135_DOCKER_IMPORT_GOING_TO_WAREHOUSE:
        do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, ACTION_139_DOCKER_IMPORT_AT_WAREHOUSE, ACTION_8_RECALCULATE);

        if (destination()->state != BUILDING_STATE_VALID) {
            poof();
        }
        break;

    case ACTION_136_DOCKER_EXPORT_GOING_TO_WAREHOUSE:
        do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, ACTION_140_DOCKER_EXPORT_AT_WAREHOUSE, ACTION_8_RECALCULATE);     
        if (destination()->state != BUILDING_STATE_VALID) {
            advance_action(ACTION_137_DOCKER_EXPORT_RETURNING);
        }
        break;

    case ACTION_137_DOCKER_EXPORT_RETURNING:
        if (do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, ACTION_134_DOCKER_EXPORT_QUEUE, ACTION_8_RECALCULATE)) {
            load_resource(RESOURCE_NONE, 0);
        }

        if (destination()->state != BUILDING_STATE_VALID) {
            poof();
        }
        break;

    case ACTION_138_DOCKER_IMPORT_RETURNING:
        do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, ACTION_132_DOCKER_IDLING, ACTION_8_RECALCULATE);
        break;

    case ACTION_139_DOCKER_IMPORT_AT_WAREHOUSE:
        base.wait_ticks++;
        if (base.wait_ticks > 10) {
            auto ship = figure_get<figure_trade_ship>(dock.trade_ship);
            auto trade_city = ship ? ship->empire_city() : empire_city_handle{};

            if (try_import_resource(destination(), base.resource_id, trade_city)) {
                base.wait_ticks = 0;
                trader().record_sold_resource(base.resource_id);
                advance_action(ACTION_138_DOCKER_IMPORT_RETURNING);
                load_resource(RESOURCE_NONE, 0);
                set_destination(home(), home()->tile);
                fetch_export_resource(b);
            } else {
                advance_action(ACTION_138_DOCKER_IMPORT_RETURNING);
                base.destination_tile = base.source_tile;
            }
            base.wait_ticks = 0;
        }
        base.animctx.frame = 0;
        break;

    case ACTION_140_DOCKER_EXPORT_AT_WAREHOUSE:
        base.wait_ticks++;
        if (base.wait_ticks > 10) {
            auto trade_city = trader_city();
            advance_action(ACTION_138_DOCKER_IMPORT_RETURNING);
            base.wait_ticks = 0;
            const bool can_export = try_export_resource(destination(), base.resource_id, trade_city);
            if (can_export) {
                int amount = trader().record_bought_resource(base.resource_id);
                load_resource(base.resource_id, amount);
                set_destination(home(), home()->tile);
                advance_action(ACTION_137_DOCKER_EXPORT_RETURNING);
            } else {
                fetch_export_resource(b);
            }
        }
        base.animctx.frame = 0;
        break;
    }
}

sound_key figure_docker::phrase_key() const {
    svector<sound_key, 3> keys;
    
    auto dock = ((building*)home())->dcast_dock();
    if (dock) {
        // When waiting in queue - space is limited
        if (action_state() == ACTION_133_DOCKER_IMPORT_QUEUE || 
            action_state() == ACTION_134_DOCKER_EXPORT_QUEUE) {
            keys.push_back("docker_wait_until_space_opens_up");
        }
        
        // When there are multiple ships or high activity - need more help
        if (dock->runtime_data().num_ships > 60) {
            keys.push_back("docker_need_more_help");
        }
    }
    
    // When going to warehouse - check distance
    if (action_state() == ACTION_135_DOCKER_IMPORT_GOING_TO_WAREHOUSE || 
        action_state() == ACTION_136_DOCKER_EXPORT_GOING_TO_WAREHOUSE) {
        int dist = calc_maximum_distance(base.destination_tile, base.source_tile);
        if (dist >= 25) {
            keys.push_back("docker_cant_haul_goods_much_farther");
        }
    }
    
    // Default fallback
    if (keys.empty()) {
        keys.push_back("docker_need_more_help");
    }
    
    int index = rand() % keys.size();
    return keys[index];
}

void figure_docker::update_animation() {
    int dir = base.figure_image_normalize_direction(direction() < 8 ? direction() : base.previous_tile_direction);

    if (action_state(FIGURE_ACTION_149_CORPSE)) {
        base.main_image_id = image_id_from_group(PACK_SPR_MAIN, 44);
        base.cart_image_id = 0;
    } else {
        base.main_image_id = image_id_from_group(PACK_SPR_MAIN, 43) + dir + 8 * base.animctx.frame;
    }

    if (base.cart_image_id) {
        base.cart_image_id += dir;
        base.figure_image_set_cart_offset(dir);
    } else {
        base.main_image_id = 0;
    }
}

void figure_docker::poof() {

}

void figure_docker::on_destroy() {
    if (!base.has_home()) {
        return;
    }

    auto &dock = home()->dcast_dock()->runtime_data();
    for (int i = 0; i < 3; i++) {
        if (dock.docker_ids[i] == id()) {
            dock.docker_ids[i] = 0;
        }
    }
}

