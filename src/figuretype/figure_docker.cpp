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
#include "figure/movement.h"
#include "figure/route.h"
#include "empire/trader_handler.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/image_desc.h"
#include "grid/road_access.h"
#include "figuretype/figure_trader_ship.h"
#include "city/city_figures.h"
#include "game/game_config.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_docker);

std::array<vec2i, 8> ANK_VARIABLE(docker_cart_offsets); //= { {17, -7}, {22, -1}, {17, 7}, {0, 11}, {-17, 6}, {-22, -1}, {-17, -7}, {0, -12} };

namespace {
    // Each add_import/remove_export call moves at most 100 units; the haul-amount lets a single docker trip make multiple such calls in succession.
    constexpr int DOCKER_HAUL_CHUNK = 100;
    int dock_haul_amount() {
        return !!game_features::gameplay_change_dock_double_haul ? 2 * DOCKER_HAUL_CHUNK : DOCKER_HAUL_CHUNK;
    }
}

int figure_docker::try_import_resource(building* b, e_resource resource, empire_city_handle city) {
    building_storage_yard *warehouse = b->dcast_storage_yard();
    if (!warehouse) {
        return 0;
    }

    if (warehouse->is_not_accepting(resource)) {
        return 0;
    }

    if (!warehouse->get_permission(BUILDING_STORAGE_PERMISSION_DOCK)) {
        return 0;
    }

    auto &trade_route = city.get_route();
    auto place_one_chunk = [&]() -> bool {
        // try existing storage bay with the same resource
        building_storage_room* space = warehouse->room();
        while (space) {
            if (space->stored_amount(resource) > 0 && space->stored_amount(resource) < 400) {
                space->add_import(resource);
                return true;
            }
            space = space->next_room();
        }
        // try unused storage bay
        space = warehouse->room();
        while (space) {
            if (space->resource() == RESOURCE_NONE) {
                space->add_import(resource);
                return true;
            }
            space = space->next_room();
        }
        return false;
    };

    int delivered = 0;
    const int target_chunks = dock_haul_amount() / DOCKER_HAUL_CHUNK;
    for (int i = 0; i < target_chunks; i++) {
        if (!place_one_chunk()) {
            break;
        }
        trade_route.increase_traded(resource, DOCKER_HAUL_CHUNK);
        delivered += DOCKER_HAUL_CHUNK;
    }
    return delivered;
}

void figure_docker::set_cart_offset(int direction) const {
    base.cart_offset = docker_cart_offsets[direction];
}

int figure_docker::try_export_resource(building* b, e_resource resource, empire_city_handle city) {
    building_storage_yard *warehouse = b->dcast_storage_yard();
    if (!warehouse) {
        return 0;
    }

    if (!warehouse->get_permission(BUILDING_STORAGE_PERMISSION_DOCK)) {
        return 0;
    }

    auto take_one_chunk = [&]() -> bool {
        building_storage_room* space = warehouse->room();
        while (space) {
            if (space->stored_amount(resource)) {
                space->remove_export(resource);
                return true;
            }
            space = space->next_room();
        }
        return false;
    };

    auto &trade_route = city.get_route();
    int taken = 0;
    const int target_chunks = dock_haul_amount() / DOCKER_HAUL_CHUNK;
    for (int i = 0; i < target_chunks; i++) {
        if (!take_one_chunk()) {
            break;
        }
        trade_route.increase_traded(resource, DOCKER_HAUL_CHUNK);
        taken += DOCKER_HAUL_CHUNK;
    }
    return taken;
}

building_dest figure_docker::get_closest_warehouse_for_import(tile2i pos, empire_city_handle city, int distance_from_entry, int road_network_id, building_dock *dock, e_resource& import_resource) {
    const resource_list importable = g_empire.importable_resources_from_city(city.handle);

    // Treat an unconfigured dock (all-zero trading_goods, e.g. legacy saves) as accept-all so the filter doesn't strand trade.
    const bool dock_filter = dock && dock->runtime_data().trading_goods.is_not_zero();
    auto allowed = [&](e_resource r) {
        return importable[r] && (!dock_filter || dock->is_trade_accepted(r));
    };

    // If the dock's ship has per-good budgets populated, pick from those (preserves per-visit
    // proportional split). Otherwise fall back to the legacy global round-robin.
    figure_trade_ship* ship = nullptr;
    if (dock && dock->runtime_data().trade_ship) {
        ship = figure_get<figure_trade_ship>(dock->runtime_data().trade_ship);
    }

    bool budgets_populated = false;
    if (ship) {
        for (const auto& slot : ship->runtime_data().import_budgets) {
            if (slot.resource != 0) {
                budgets_populated = true;
                break;
            }
        }
    }

    auto find_warehouse = [&](e_resource resource) -> building_dest {
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

        return { min_building_id, warehouse_tile };
    };

    if (budgets_populated) {
        // Try each viable slot until one yields a warehouse. Earlier code stopped at the first
        // allowed slot, so if its resource had no reachable warehouse the docker re-picked the
        // same slot every tick (remaining_chunks only decrements on a *successful* delivery),
        // stranding the ship until the idle-day cap fired.
        for (const auto& slot : ship->runtime_data().import_budgets) {
            if (slot.resource == 0 || slot.remaining_chunks == 0) {
                continue;
            }
            const e_resource r = (e_resource)slot.resource;
            if (!allowed(r)) {
                continue;
            }
            building_dest result = find_warehouse(r);
            if (result.bid) {
                import_resource = r;
                return result;
            }
        }
        return { 0, tile2i::invalid };
    }

    // Legacy / no-budget path: use the global round-robin (advances each call so successive
    // idle ticks naturally cycle across resources).
    e_resource resource = city_trade_next_docker_import_resource();
    for (e_resource i = RESOURCES_MIN; i < RESOURCES_MAX && !allowed(resource); ++i) {
        resource = city_trade_next_docker_import_resource();
    }

    if (!allowed(resource)) {
        return { 0, tile2i::invalid };
    }

    building_dest result = find_warehouse(resource);
    if (!result.bid) {
        return { 0, tile2i::invalid };
    }
    import_resource = resource;
    return result;
}

building_dest figure_docker::get_closest_warehouse_for_export(tile2i pos, empire_city_handle city, int distance_from_entry, int road_network_id, building_dock *dock, e_resource &export_resource) {
    const resource_list exportable = g_empire.exportable_resources_from_city(city.handle);

    const bool dock_filter = dock && dock->runtime_data().trading_goods.is_not_zero();
    auto allowed = [&](e_resource r) {
        return exportable[r] && (!dock_filter || dock->is_trade_accepted(r));
    };

    e_resource resource = city_trade_next_docker_export_resource();
    for (int i = RESOURCES_MIN; i < RESOURCES_MAX && !allowed(resource); i++) {
        resource = city_trade_next_docker_export_resource();
    }

    if (!allowed(resource)) {
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
    auto result = get_closest_warehouse_for_import(trade_center_tile, ship->empire_city(), b->distance_from_entry, b->road_network_id, dock, resource);
    if (!result.bid) {
        return false;
    }

    set_destination(result.bid);
    base.wait_ticks = 0;
    advance_action(ACTION_133_DOCKER_IMPORT_QUEUE);
    base.destination_tile = result.tile;
    base.resource_id = resource;
    base.resource_amount_full = dock_haul_amount();
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
    auto result = get_closest_warehouse_for_export(trade_cener_tile, ship->empire_city(), b->distance_from_entry, b->road_network_id, dock, resource);

    if (!result.bid) {
        return false;
    }

    ship->runtime_data().amount_bought += dock_haul_amount();
    set_destination(result.bid);
    advance_action(ACTION_136_DOCKER_EXPORT_GOING_TO_WAREHOUSE);
    base.wait_ticks = 0;
    base.destination_tile = result.tile;
    base.resource_id = resource;
    return true;
}

void figure_docker::figure_before_action() {
    if (action_state() == ACTION_132_DOCKER_IDLING) {
        base.routing_try_reroute_counter = 0;
    }
}

void figure_docker::figure_action() {
    building* b = home();

    base.use_cart = true;
    if (b->state != BUILDING_STATE_VALID) {
        poof();
        return;
    }

    if (b->type != BUILDING_DOCK && b->type != BUILDING_FISHING_WHARF) {
        poof();
        return;
    }

    building_dock* dock_b = b->dcast_dock();
    if (!dock_b) {
        poof();
        return;
    }

    auto& dock = dock_b->runtime_data();
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
    case ACTION_8_RECALCULATE:
        // Without this case a routing failure leaves the docker non-idle, so the moored ship's failed_dock_attempts never advances.
        if (++base.routing_try_reroute_counter > 5) {
            base.routing_try_reroute_counter = 0;
            base.poof();
            return;
        }
        load_resource(RESOURCE_NONE, 0);
        base.cart_image_id = 0;
        base.wait_ticks = 0;
        set_destination(home(), home()->tile);
        advance_action(ACTION_138_DOCKER_IMPORT_RETURNING);
        break;

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

            const int delivered = try_import_resource(destination(), base.resource_id, trade_city);
            if (delivered > 0) {
                const int chunks = delivered / DOCKER_HAUL_CHUNK;
                if (ship) {
                    ship->dump_resource(delivered);
                    ship->runtime_data().failed_dock_attempts = 0;
                    for (int i = 0; i < chunks; i++) {
                        ship->consume_import_budget(base.resource_id);
                    }
                }
                base.wait_ticks = 0;
                for (int i = 0; i < chunks; i++) {
                    trader().record_sold_resource(base.resource_id);
                }
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
            const int reserved = dock_haul_amount();
            const int taken = try_export_resource(destination(), base.resource_id, trade_city);
            // fetch_export_resource pre-reserved `reserved` units against the ship's
            // amount_bought. Refund any shortfall so total_bought() doesn't drift upward each
            // visit and eventually hit max_capacity(), which would stall all exports permanently.
            auto ship = dock.trade_ship ? figure_get<figure_trade_ship>(dock.trade_ship) : nullptr;
            const int refund = reserved - taken;
            if (ship && refund > 0) {
                auto &rd = ship->runtime_data();
                rd.amount_bought = (rd.amount_bought >= refund) ? rd.amount_bought - refund : 0;
            }
            if (taken > 0) {
                if (ship) {
                    ship->runtime_data().failed_dock_attempts = 0;
                }
                const int chunks = taken / DOCKER_HAUL_CHUNK;
                int loaded = 0;
                for (int i = 0; i < chunks; i++) {
                    loaded += trader().record_bought_resource(base.resource_id);
                }
                load_resource(base.resource_id, loaded);
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
        set_cart_offset(dir);
    } else {
        base.main_image_id = 0;
    }
}

void figure_docker::poof() {
    figure_carrier::poof();
}

void figure_docker::on_destroy() {
    if (!base.has_home()) {
        return;
    }

    auto dock = home()->dcast_dock();
    if (!dock) {
        return;
    }

    auto& rt = dock->runtime_data();
    for (int i = 0; i < 3; i++) {
        if (rt.docker_ids[i] == id()) {
            rt.docker_ids[i] = 0;
        }
    }
}

