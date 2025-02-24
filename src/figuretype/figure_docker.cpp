#include "figure_docker.h"

#include "building/building.h"
#include "building/building_storage_yard.h"
#include "building/building_storage_room.h"
#include "building/building_dock.h"
#include "city/buildings.h"
#include "city/city_buildings.h"
#include "city/trade.h"
#include "core/calc.h"
#include "core/game_environment.h"
#include "empire/empire.h"
#include "empire/empire_map.h"
#include "empire/trade_route.h"
#include "figure/combat.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "figure/trader.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/image_desc.h"
#include "grid/road_access.h"
#include "figuretype/figure_trader_ship.h"
#include "city/city_figures.h"

figures::model_t<figure_docker> docker_m;

bool figure_docker::try_import_resource(building* b, e_resource resource, int city_id) {
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

    auto &trade_route = g_empire.city(city_id)->get_route();
    // try existing storage bay with the same resource
    building_storage_room* space = warehouse->room();
    while (space) {
        if (space->base.stored_amount_first > 0 && space->base.stored_amount_first < 400 && space->data.warehouse.resource_id == resource) {
            trade_route.increase_traded(resource, 100);
            space->add_import(resource);
            return true;
        }
        space = space->next_room();
    }
    // try unused storage bay
    space = warehouse->room();
    while (space) {
        if (space->data.warehouse.resource_id == RESOURCE_NONE) {
            trade_route.increase_traded(resource, 100);
            space->add_import(resource);
            return true;
        }
        space = space->next_room();
    }
    return false;
}

int figure_docker::try_export_resource(building* b, e_resource resource, int city_id) {
    building_storage_yard *warehouse = b->dcast_storage_yard();
    if (!warehouse) {
        return 0;
    }

    if (!warehouse->get_permission(BUILDING_STORAGE_PERMISSION_DOCK)) {
        return 0;
    }

    building_storage_room* space = warehouse->room();
    while (space) {
        if (space->base.stored_amount_first && space->data.warehouse.resource_id == resource) {
            auto &trade_route = g_empire.city(city_id)->get_route();
            trade_route.increase_traded(resource, 100);
            space->remove_export(resource);
            return 1;
        }
        space = space->next_room();
    }
    return 0;
}

int figure_docker::get_closest_warehouse_for_import(tile2i pos, int city_id, int distance_from_entry, int road_network_id, tile2i &warehouse, e_resource& import_resource) {
    const resource_list importable = g_empire.importable_resources_from_city(city_id);

    e_resource resource = city_trade_next_docker_import_resource();
    for (e_resource i = RESOURCE_MIN; i < RESOURCES_MAX && !importable[resource]; ++i) {
        resource = city_trade_next_docker_import_resource();
    }

    if (!importable[resource]) {
        return 0;
    }

    int min_distance = 10000;
    int min_building_id = 0;
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
            if (space->data.warehouse.resource_id == RESOURCE_NONE) {
                distance_penalty -= 8;
            }

            if (space->data.warehouse.resource_id == resource && space->base.stored_amount_first < 400) {
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
        return 0;
    }

    building* minb = building_get(min_building_id);
    if (minb->has_road_access) {
        warehouse = minb->tile;
        map_point_store_result(minb->tile, warehouse);
    } else {
        warehouse = map_get_road_access_tile(minb->tile, 3);
        if (!warehouse.valid()) {
            return 0;
        }
    }

    import_resource = resource;
    return min_building_id;
}

int figure_docker::get_closest_warehouse_for_export(tile2i pos, int city_id, int distance_from_entry, int road_network_id, tile2i &warehouse, e_resource& export_resource) {
    const resource_list exportable = g_empire.exportable_resources_from_city(city_id);

    e_resource resource = city_trade_next_docker_export_resource();
    for (int i = RESOURCE_MIN; i < RESOURCES_MAX && !exportable[resource]; i++) {
        resource = city_trade_next_docker_export_resource();
    }

    if (!exportable[resource]) {
        return 0;
    }

    int min_distance = 10000;
    int min_building_id = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || b->type != BUILDING_STORAGE_YARD)
            continue;

        if (!b->has_road_access || b->distance_from_entry <= 0)
            continue;

        if (b->road_network_id != road_network_id)
            continue;

        building_storage *s = b->dcast_storage();
        if (!s->get_permission(BUILDING_STORAGE_PERMISSION_DOCK))
            continue;

        int distance_penalty = 32;
        building* space = b;
        for (int s = 0; s < 8; s++) {
            space = space->next();
            if (space->id && space->data.warehouse.resource_id == resource && space->stored_amount_first > 0)
                distance_penalty--;
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
        return 0;
    }

    building* minb = building_get(min_building_id);
    if (minb->has_road_access == 1) {
        warehouse = minb->tile;
        map_point_store_result(minb->tile, warehouse);
    } else {
        warehouse = map_get_road_access_tile(minb->tile, 3);
        if (!warehouse.valid()) {
            return 0;
        }
    }

    export_resource = resource;
    return min_building_id;
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

int figure_docker::trader_id() {
    building_dock *dock = home()->dcast_dock();
    return dock->trader_id();
}

int figure_docker::trader_city_id() {
    building_dock *dock = home()->dcast_dock();
    return dock->trader_city_id();
}

bool figure_docker::deliver_import_resource(building* dock) {
    int ship_id = dock->data.dock.trade_ship_id;
    if (!ship_id) {
        return false;
    }

    figure* f = figure_get(ship_id);
    auto ship = smart_cast<figure_trade_ship>(f);
    if (ship->action_state() != FIGURE_ACTION_112_TRADE_SHIP_MOORED || ship->base.get_carrying_amount() <= 0) {
        return false;
    }

    tile2i trade_center_tile = get_trade_center_location();
    tile2i tile;
    e_resource resource;
    int warehouse_id = get_closest_warehouse_for_import(trade_center_tile, ship->base.empire_city_id, dock->distance_from_entry, dock->road_network_id, tile, resource);
    if (!warehouse_id) {
        return false;
    }

    ship->dump_resource(100);
    set_destination(warehouse_id);
    base.wait_ticks = 0;
    advance_action(FIGURE_ACTION_133_DOCKER_IMPORT_QUEUE);
    base.destination_tile = tile;
    base.resource_id = resource;
    base.resource_amount_full = 100;
    return true;
}

bool figure_docker::fetch_export_resource(building* dock) {
    int ship_id = dock->data.dock.trade_ship_id;
    if (!ship_id) {
        return false;
    }

    figure* ship = figure_get(ship_id);
    if (ship->action_state != FIGURE_ACTION_112_TRADE_SHIP_MOORED || ship->trader_amount_bought >= 1200) {
        return false;
    }

    tile2i trade_cener_tile = get_trade_center_location();
    tile2i tile;
    e_resource resource;
    int warehouse_id = get_closest_warehouse_for_export(trade_cener_tile, ship->empire_city_id, dock->distance_from_entry, dock->road_network_id, tile, resource);

    if (!warehouse_id) {
        return false;
    }

    ship->trader_amount_bought++;
    set_destination(warehouse_id);
    advance_action(FIGURE_ACTION_136_DOCKER_EXPORT_GOING_TO_WAREHOUSE);
    base.wait_ticks = 0;
    base.destination_tile = tile;
    base.resource_id = resource;
    return true;
}

void figure_docker::figure_action() {
    building* b = home();
    if (b->state != BUILDING_STATE_VALID) {
        poof();
    }

    if (b->type != BUILDING_DOCK && b->type != BUILDING_FISHING_WHARF) {
        poof();
    }

    if (b->data.dock.num_ships)
        b->data.dock.num_ships--;

    if (b->data.dock.trade_ship_id) {
        figure* ship = figure_get(b->data.dock.trade_ship_id);
        if (ship->state != FIGURE_STATE_ALIVE || ship->type != FIGURE_TRADE_SHIP)
            b->data.dock.trade_ship_id = 0;
        else if (trader_has_traded_max(ship->trader_id))
            b->data.dock.trade_ship_id = 0;
        else if (ship->action_state == FIGURE_ACTION_115_TRADE_SHIP_LEAVING)
            b->data.dock.trade_ship_id = 0;
    }

    base.terrain_usage = TERRAIN_USAGE_ROADS;
    switch (action_state()) {
    case FIGURE_ACTION_132_DOCKER_IDLING:
        base.resource_id = RESOURCE_NONE;
        base.cart_image_id = 0;
        base.anim.frame = 0;
        if (!deliver_import_resource(b)) {
            fetch_export_resource(b);
        }
        break;

    case FIGURE_ACTION_133_DOCKER_IMPORT_QUEUE:
        base.cart_image_id = 0;
        base.anim.frame = 0;
        if (b->data.dock.queued_docker_id <= 0) {
            b->data.dock.queued_docker_id = id();
            base.wait_ticks = 0;
        }

        if (b->data.dock.queued_docker_id == id()) {
            b->data.dock.num_ships = 120;
            base.wait_ticks++;
            if (base.wait_ticks >= 80) {
                advance_action(FIGURE_ACTION_135_DOCKER_IMPORT_GOING_TO_WAREHOUSE);
                base.wait_ticks = 0;
                //                    set_cart_graphic();
                b->data.dock.queued_docker_id = 0;
            }
        } else {
            int has_queued_docker = 0;
            for (int i = 0; i < 3; i++) {
                if (b->data.dock.docker_ids[i]) {
                    figure* docker = figure_get(b->data.dock.docker_ids[i]);
                    if (docker->id == b->data.dock.queued_docker_id && docker->state == FIGURE_STATE_ALIVE) {
                        if (docker->action_state == FIGURE_ACTION_133_DOCKER_IMPORT_QUEUE
                            || docker->action_state == FIGURE_ACTION_134_DOCKER_EXPORT_QUEUE) {
                            has_queued_docker = 1;
                        }
                    }
                }
            }
            if (!has_queued_docker)
                b->data.dock.queued_docker_id = 0;
        }
        break;

    case FIGURE_ACTION_134_DOCKER_EXPORT_QUEUE:
        if (b->data.dock.queued_docker_id <= 0) {
            b->data.dock.queued_docker_id = id();
            base.wait_ticks = 0;
        }
        if (b->data.dock.queued_docker_id == id()) {
            b->data.dock.num_ships = 120;
            base.wait_ticks++;
            if (base.wait_ticks >= 80) {
                advance_action(FIGURE_ACTION_132_DOCKER_IDLING);
                base.wait_ticks = 0;
                base.sprite_image_id = 0;
                base.cart_image_id = 0;
                b->data.dock.queued_docker_id = 0;
            }
        }
        base.wait_ticks++;
        if (base.wait_ticks >= 20) {
            advance_action(FIGURE_ACTION_132_DOCKER_IDLING);
            base.wait_ticks = 0;
        }
        base.anim.frame = 0;
        break;

    case FIGURE_ACTION_135_DOCKER_IMPORT_GOING_TO_WAREHOUSE:
        do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, FIGURE_ACTION_139_DOCKER_IMPORT_AT_WAREHOUSE, ACTION_8_RECALCULATE);

        if (destination()->state != BUILDING_STATE_VALID) {
            poof();
        }
        break;

    case FIGURE_ACTION_136_DOCKER_EXPORT_GOING_TO_WAREHOUSE:
        do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, FIGURE_ACTION_140_DOCKER_EXPORT_AT_WAREHOUSE, ACTION_8_RECALCULATE);     
        if (destination()->state != BUILDING_STATE_VALID) {
            advance_action(FIGURE_ACTION_137_DOCKER_EXPORT_RETURNING);
        }
        break;

    case FIGURE_ACTION_137_DOCKER_EXPORT_RETURNING:
        if (do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, FIGURE_ACTION_134_DOCKER_EXPORT_QUEUE, ACTION_8_RECALCULATE)) {
            load_resource(RESOURCE_NONE, 0);
        }

        if (destination()->state != BUILDING_STATE_VALID) {
            poof();
        }
        break;

    case FIGURE_ACTION_138_DOCKER_IMPORT_RETURNING:
        do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, FIGURE_ACTION_132_DOCKER_IDLING, ACTION_8_RECALCULATE);
        break;

    case FIGURE_ACTION_139_DOCKER_IMPORT_AT_WAREHOUSE:
        base.wait_ticks++;
        if (base.wait_ticks > 10) {
            int trade_city_id = b->data.dock.trade_ship_id
                                    ? figure_get(b->data.dock.trade_ship_id)->empire_city_id
                                    : 0;

            if (try_import_resource(destination(), base.resource_id, trade_city_id)) {
                base.wait_ticks = 0;
                trader_record_sold_resource(trader_id(), base.resource_id);
                advance_action(FIGURE_ACTION_138_DOCKER_IMPORT_RETURNING);
                load_resource(RESOURCE_NONE, 0);
                set_destination(home(), home()->tile);
                fetch_export_resource(b);
            } else {
                advance_action(FIGURE_ACTION_138_DOCKER_IMPORT_RETURNING);
                base.destination_tile = base.source_tile;
            }
            base.wait_ticks = 0;
        }
        base.anim.frame = 0;
        break;

    case FIGURE_ACTION_140_DOCKER_EXPORT_AT_WAREHOUSE:
        base.wait_ticks++;
        if (base.wait_ticks > 10) {
            int trade_city_id = trader_city_id();
            advance_action(FIGURE_ACTION_138_DOCKER_IMPORT_RETURNING);
            base.wait_ticks = 0;
            const bool can_export = try_export_resource(destination(), base.resource_id, trade_city_id);
            if (can_export) {
                int amount = trader_record_bought_resource(trader_id(), base.resource_id);
                load_resource(base.resource_id, amount);
                set_destination(home(), home()->tile);
                advance_action(FIGURE_ACTION_137_DOCKER_EXPORT_RETURNING);
            } else {
                fetch_export_resource(b);
            }
        }
        base.anim.frame = 0;
        break;
    }
}

void figure_docker::figure_draw(painter &ctx, vec2i pixel, int highlight, vec2i* coord_out) {
    base.draw_figure_with_cart(ctx, pixel, highlight, coord_out);
}

sound_key figure_docker::phrase_key() const {
    const bool in_action = action_state(FIGURE_ACTION_135_DOCKER_IMPORT_GOING_TO_WAREHOUSE, FIGURE_ACTION_136_DOCKER_EXPORT_GOING_TO_WAREHOUSE);
    if (in_action) {
        int dist = calc_maximum_distance(base.destination_tile, base.source_tile);
        if (dist >= 25) {
            return "too_far"; // too far
        }
    }

    return {};
}

void figure_docker::update_animation() {
    int dir = figure_image_normalize_direction(direction() < 8 ? direction() : base.previous_tile_direction);

    if (action_state(FIGURE_ACTION_149_CORPSE)) {
        base.sprite_image_id = image_id_from_group(PACK_SPR_MAIN, 44);
        base.cart_image_id = 0;
    } else {
        base.sprite_image_id = image_id_from_group(PACK_SPR_MAIN, 43) + dir + 8 * base.anim.frame;
    }

    if (base.cart_image_id) {
        base.cart_image_id += dir;
        base.figure_image_set_cart_offset(dir);
    } else {
        base.sprite_image_id = 0;
    }
}

void figure_docker::poof() {

}

void figure_docker::on_destroy() {
    if (!base.has_home()) {
        return;
    }

    building* b = home();
    for (int i = 0; i < 3; i++) {
        if (b->data.dock.docker_ids[i] == id())
            b->data.dock.docker_ids[i] = 0;
    }
}
