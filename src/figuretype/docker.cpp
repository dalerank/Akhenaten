#include "docker.h"

#include "building/building.h"
#include "building/storage.h"
#include "building/storage_yard.h"
#include "city/buildings.h"
#include "city/trade.h"
#include "core/calc.h"
#include "core/game_environment.h"
#include "empire/city.h"
#include "empire/empire.h"
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

static int try_import_resource(building* warehouse, e_resource resource, int city_id) {
    if (warehouse->type != BUILDING_STORAGE_YARD)
        return 0;

    if (building_storageyard_is_not_accepting(resource, warehouse))
        return 0;

    if (!building_storage_get_permission(BUILDING_STORAGE_PERMISSION_DOCK, warehouse))
        return 0;

    int route_id = empire_city_get_route_id(city_id);
    // try existing storage bay with the same resource
    building* space = warehouse;
    for (int i = 0; i < 8; i++) {
        space = space->next();
        if (space->id > 0) {
            if (space->stored_full_amount && space->stored_full_amount < 400
                && space->subtype.warehouse_resource_id == resource) {
                trade_route_increase_traded(route_id, resource);
                building_storageyard_space_add_import(space, resource);
                return 1;
            }
        }
    }
    // try unused storage bay
    space = warehouse;
    for (int i = 0; i < 8; i++) {
        space = space->next();
        if (space->id > 0) {
            if (space->subtype.warehouse_resource_id == RESOURCE_NONE) {
                trade_route_increase_traded(route_id, resource);
                building_storageyard_space_add_import(space, resource);
                return 1;
            }
        }
    }
    return 0;
}
static int try_export_resource(building* warehouse, e_resource resource, int city_id) {
    //    building *warehouse = building_get(b);
    if (warehouse->type != BUILDING_STORAGE_YARD)
        return 0;
    if (!building_storage_get_permission(BUILDING_STORAGE_PERMISSION_DOCK, warehouse))
        return 0;
    building* space = warehouse;
    for (int i = 0; i < 8; i++) {
        space = space->next();
        if (space->id > 0) {
            if (space->stored_full_amount && space->subtype.warehouse_resource_id == resource) {
                trade_route_increase_traded(empire_city_get_route_id(city_id), resource);
                building_storageyard_space_remove_export(space, resource);
                return 1;
            }
        }
    }
    return 0;
}

static int get_closest_warehouse_for_import(vec2i pos, int city_id, int distance_from_entry, int road_network_id, map_point &warehouse, e_resource& import_resource) {
    int importable[16];
    importable[RESOURCE_NONE] = 0;
    for (int r = RESOURCE_MIN; r < RESOURCES_MAX; r++) {
        importable[r] = empire_can_import_resource_from_city(city_id, r);
    }
    e_resource resource = city_trade_next_docker_import_resource();
    for (int i = RESOURCE_MIN; i < RESOURCES_MAX && !importable[resource]; i++) {
        resource = city_trade_next_docker_import_resource();
    }
    if (!importable[resource])
        return 0;

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

        if (!building_storage_get_permission(BUILDING_STORAGE_PERMISSION_DOCK, b))
            continue;

        const building_storage* storage = building_storage_get(b->storage_id);
        if (!building_storageyard_is_not_accepting(resource, b) && !storage->empty_all) {
            int distance_penalty = 32;
            building* space = b;
            for (int s = 0; s < 8; s++) {
                space = space->next();
                if (space->id && space->subtype.warehouse_resource_id == RESOURCE_NONE)
                    distance_penalty -= 8;

                if (space->id && space->subtype.warehouse_resource_id == resource && space->stored_full_amount < 400)
                    distance_penalty -= 4;
            }
            if (distance_penalty < 32) {
                int distance = calc_distance_with_penalty(b->tile, pos, distance_from_entry, b->distance_from_entry);
                // prefer emptier warehouse
                distance += distance_penalty;
                if (distance < min_distance) {
                    min_distance = distance;
                    min_building_id = i;
                }
            }
        }
    }
    if (!min_building_id)
        return 0;

    building* min = building_get(min_building_id);
    if (min->has_road_access == 1) {
        map_point_store_result(min->tile, warehouse);
    } else if (!map_get_road_access_tile(min->tile, 3, warehouse)) {
        return 0;
    }

    import_resource = resource;
    return min_building_id;
}

static int get_closest_warehouse_for_export(vec2i pos, int city_id, int distance_from_entry, int road_network_id, tile2i &warehouse, e_resource& export_resource) {
    int exportable[16];
    exportable[RESOURCE_NONE] = 0;
    for (int r = RESOURCE_MIN; r < RESOURCES_MAX; r++) {
        exportable[r] = empire_can_export_resource_to_city(city_id, r);
    }

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

        if (!building_storage_get_permission(BUILDING_STORAGE_PERMISSION_DOCK, b))
            continue;

        int distance_penalty = 32;
        building* space = b;
        for (int s = 0; s < 8; s++) {
            space = space->next();
            if (space->id && space->subtype.warehouse_resource_id == resource && space->stored_full_amount > 0)
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
    if (!min_building_id)
        return 0;

    building* min = building_get(min_building_id);
    if (min->has_road_access == 1) {
        map_point_store_result(min->tile, warehouse);
    } else if (!map_get_road_access_tile(min->tile, 3, warehouse)) {
        return 0;
    }

    export_resource = resource;
    return min_building_id;
}

void figure::get_trade_center_location(int* _x, int* _y) {
    int trade_center_id = city_buildings_get_trade_center();
    if (trade_center_id) {
        building* trade_center = building_get(trade_center_id);
        *_x = trade_center->tile.x();
        *_y = trade_center->tile.y();
    } else {
        *_x = tile.x();
        *_y = tile.y();
    }
}
int figure::deliver_import_resource(building* dock) {
    int ship_id = dock->data.dock.trade_ship_id;
    if (!ship_id)
        return 0;

    figure* ship = figure_get(ship_id);
    if (ship->action_state != FIGURE_ACTION_112_TRADE_SHIP_MOORED || ship->get_carrying_amount() <= 0)
        return 0;

    int x, y;
    get_trade_center_location(&x, &y);
    map_point tile;
    e_resource resource;
    int warehouse_id = get_closest_warehouse_for_import(vec2i(x, y), ship->empire_city_id, dock->distance_from_entry, dock->road_network_id, tile, resource);
    if (!warehouse_id) {
        return 0;
    }

    ship->dump_resource(100);
    set_destination(warehouse_id);
    wait_ticks = 0;
    action_state = FIGURE_ACTION_133_DOCKER_IMPORT_QUEUE;
    destination_tile = tile;
    //    destination_tile.x() = tile.x();
    //    destination_tile.y() = tile.y();
    resource_id = resource;
    return 1;
}
int figure::fetch_export_resource(building* dock) {
    int ship_id = dock->data.dock.trade_ship_id;
    if (!ship_id)
        return 0;

    figure* ship = figure_get(ship_id);
    if (ship->action_state != FIGURE_ACTION_112_TRADE_SHIP_MOORED || ship->trader_amount_bought >= 12)
        return 0;

    int x, y;
    get_trade_center_location(&x, &y);
    map_point tile;
    e_resource resource;
    int warehouse_id = get_closest_warehouse_for_export(vec2i(x, y), ship->empire_city_id, dock->distance_from_entry, dock->road_network_id, tile, resource);

    if (!warehouse_id) {
        return 0;
    }

    ship->trader_amount_bought++;
    set_destination(warehouse_id);
    action_state = FIGURE_ACTION_136_DOCKER_EXPORT_GOING_TO_WAREHOUSE;
    wait_ticks = 0;
    destination_tile = tile;
    //    destination_tile.x() = tile.x();
    //    destination_tile.y() = tile.y();
    resource_id = resource;
    return 1;
}

void figure::docker_action() {
    //    figure_image_increase_offset(12);
    //    cart_image_id = 0;
    building* b = home();
    if (b->state != BUILDING_STATE_VALID)
        poof();

    if (b->type != BUILDING_DOCK && b->type != BUILDING_FISHING_WHARF)
        poof();

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
    terrain_usage = TERRAIN_USAGE_ROADS;
    switch (action_state) {
    case FIGURE_ACTION_132_DOCKER_IDLING:
        resource_id = RESOURCE_NONE;
        cart_image_id = 0;
        if (!deliver_import_resource(b))
            fetch_export_resource(b);

        anim_frame = 0;
        break;
    case FIGURE_ACTION_133_DOCKER_IMPORT_QUEUE:
        cart_image_id = 0;
        anim_frame = 0;
        if (b->data.dock.queued_docker_id <= 0) {
            b->data.dock.queued_docker_id = id;
            wait_ticks = 0;
        }
        if (b->data.dock.queued_docker_id == id) {
            b->data.dock.num_ships = 120;
            wait_ticks++;
            if (wait_ticks >= 80) {
                action_state = FIGURE_ACTION_135_DOCKER_IMPORT_GOING_TO_WAREHOUSE;
                wait_ticks = 0;
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
        //            set_cart_graphic();
        if (b->data.dock.queued_docker_id <= 0) {
            b->data.dock.queued_docker_id = id;
            wait_ticks = 0;
        }
        if (b->data.dock.queued_docker_id == id) {
            b->data.dock.num_ships = 120;
            wait_ticks++;
            if (wait_ticks >= 80) {
                action_state = FIGURE_ACTION_132_DOCKER_IDLING;
                wait_ticks = 0;
                sprite_image_id = 0;
                cart_image_id = 0;
                b->data.dock.queued_docker_id = 0;
            }
        }
        wait_ticks++;
        if (wait_ticks >= 20) {
            action_state = FIGURE_ACTION_132_DOCKER_IDLING;
            wait_ticks = 0;
        }
        anim_frame = 0;
        break;
    case FIGURE_ACTION_135_DOCKER_IMPORT_GOING_TO_WAREHOUSE:
        //            set_cart_graphic();
        move_ticks(1);
        if (direction == DIR_FIGURE_NONE)
            action_state = FIGURE_ACTION_139_DOCKER_IMPORT_AT_WAREHOUSE;
        else if (direction == DIR_FIGURE_REROUTE)
            route_remove();
        else if (direction == DIR_FIGURE_CAN_NOT_REACH)
            poof();

        if (destination()->state != BUILDING_STATE_VALID)
            poof();

        break;
    case FIGURE_ACTION_136_DOCKER_EXPORT_GOING_TO_WAREHOUSE:
        cart_image_id = image_id_from_group(IMG_CARTPUSHER_CART); // empty
        move_ticks(1);
        if (direction == DIR_FIGURE_NONE)
            action_state = FIGURE_ACTION_140_DOCKER_EXPORT_AT_WAREHOUSE;
        else if (direction == DIR_FIGURE_REROUTE)
            route_remove();
        else if (direction == DIR_FIGURE_CAN_NOT_REACH)
            poof();

        if (destination()->state != BUILDING_STATE_VALID)
            poof();

        break;
    case FIGURE_ACTION_137_DOCKER_EXPORT_RETURNING:
        //            set_cart_graphic();
        move_ticks(1);
        if (direction == DIR_FIGURE_NONE) {
            action_state = FIGURE_ACTION_134_DOCKER_EXPORT_QUEUE;
            wait_ticks = 0;
        } else if (direction == DIR_FIGURE_REROUTE)
            route_remove();
        else if (direction == DIR_FIGURE_CAN_NOT_REACH)
            poof();

        if (destination()->state != BUILDING_STATE_VALID)
            poof();

        break;
    case FIGURE_ACTION_138_DOCKER_IMPORT_RETURNING:
        //            set_cart_graphic();
        move_ticks(1);
        if (direction == DIR_FIGURE_NONE)
            action_state = FIGURE_ACTION_132_DOCKER_IDLING;
        else if (direction == DIR_FIGURE_REROUTE)
            route_remove();
        else if (direction == DIR_FIGURE_CAN_NOT_REACH)
            poof();

        break;
    case FIGURE_ACTION_139_DOCKER_IMPORT_AT_WAREHOUSE:
        //            set_cart_graphic();
        wait_ticks++;
        if (wait_ticks > 10) {
            int trade_city_id;
            if (b->data.dock.trade_ship_id)
                trade_city_id = figure_get(b->data.dock.trade_ship_id)->empire_city_id;
            else {
                trade_city_id = 0;
            }
            if (try_import_resource(destination(), resource_id, trade_city_id)) {
                int trader_id = figure_get(b->data.dock.trade_ship_id)->trader_id;
                trader_record_sold_resource(trader_id, resource_id);
                action_state = FIGURE_ACTION_138_DOCKER_IMPORT_RETURNING;
                wait_ticks = 0;
                destination_tile = source_tile;
                //                    destination_tile.x() = source_tile.x();
                //                    destination_tile.y() = source_tile.y();
                resource_id = RESOURCE_NONE;
                fetch_export_resource(b);
            } else {
                action_state = FIGURE_ACTION_138_DOCKER_IMPORT_RETURNING;
                destination_tile = source_tile;
                //                    destination_tile.x() = source_tile.x();
                //                    destination_tile.y() = source_tile.y();
            }
            wait_ticks = 0;
        }
        anim_frame = 0;
        break;
    case FIGURE_ACTION_140_DOCKER_EXPORT_AT_WAREHOUSE:
        cart_image_id = image_id_from_group(IMG_CARTPUSHER_CART); // empty
        wait_ticks++;
        if (wait_ticks > 10) {
            int trade_city_id;
            if (b->data.dock.trade_ship_id)
                trade_city_id = figure_get(b->data.dock.trade_ship_id)->empire_city_id;
            else {
                trade_city_id = 0;
            }
            action_state = FIGURE_ACTION_138_DOCKER_IMPORT_RETURNING;
            destination_tile = source_tile;
            //                destination_tile.x() = source_tile.x();
            //                destination_tile.y() = source_tile.y();
            wait_ticks = 0;
            if (try_export_resource(destination(), resource_id, trade_city_id)) {
                int trader_id = figure_get(b->data.dock.trade_ship_id)->trader_id;
                trader_record_bought_resource(trader_id, resource_id);
                action_state = FIGURE_ACTION_137_DOCKER_EXPORT_RETURNING;
            } else {
                fetch_export_resource(b);
            }
        }
        anim_frame = 0;
        break;
    }

    int dir = figure_image_normalize_direction(direction < 8 ? direction : previous_tile_direction);

    if (action_state == FIGURE_ACTION_149_CORPSE) {
        sprite_image_id = image_id_from_group(IMG_CARTPUSHER_DEATH);
        cart_image_id = 0;
    } else {
        sprite_image_id = image_id_from_group(IMG_CARTPUSHER) + dir + 8 * anim_frame;
    }
    if (cart_image_id) {
        cart_image_id += dir;
        figure_image_set_cart_offset(dir);
    } else {
        sprite_image_id = 0;
    }
}
