#include "figure_docker.h"

#include "building/building.h"
#include "building/building_storage_yard.h"
#include "building/building_storage_room.h"
#include "building/building_dock.h"
#include "building/building_ferry.h"
#include "city/buildings.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_trade.h"
#include "city/city_resource_handle.h"
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
#include "grid/terrain.h"
#include "figuretype/figure_trader_ship.h"
#include "city/city_figures.h"
#include "game/game_config.h"
#include "js/js_game.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_docker);

const figure_docker_action_tokens_t ANK_CONFIG_ENUM(figure_docker_action_tokens)

std::array<vec2i, 8> ANK_VARIABLE(docker_cart_offsets); //= { {17, -7}, {22, -1}, {17, 7}, {0, 11}, {-17, 6}, {-22, -1}, {-17, -7}, {0, -12} };

namespace {
    const figure_docker::static_params &docker_params() {
        return figure_docker::current_params();
    }

    int docker_load() {
        return std::max<int>(1, docker_params().load_amount);
    }

    int room_capacity() {
        return docker_params().room_capacity;
    }

    int room_free_for(const building_storage_room *space, e_resource resource) {
        const e_resource stored = space->resource();
        if (stored == RESOURCE_NONE) {
            return room_capacity();
        }
        if (stored != resource) {
            return 0;
        }
        return std::max(0, room_capacity() - space->stored_first().value);
    }

    bool ship_has_import_budgets(const figure_trade_ship *ship) {
        if (!ship) {
            return false;
        }
        for (const auto &slot : ship->runtime_data().import_budgets) {
            if (slot.resource != 0) {
                return true;
            }
        }
        return false;
    }

    building_dest warehouse_road_dest(building_id bid) {
        if (!bid) {
            return { 0, tile2i::invalid };
        }

        building *b = building_get(bid);
        tile2i warehouse_tile;
        if (b->has_road_access) {
            warehouse_tile = b->tile;
            map_point_store_result(b->tile, warehouse_tile);
        } else {
            warehouse_tile = map_get_road_access_tile(b->tile, 3);
            if (!warehouse_tile.valid()) {
                return { 0, warehouse_tile };
            }
        }
        return { bid, warehouse_tile };
    }

    bool warehouse_reachable_for_docker(building_storage_yard *warehouse, int road_network_id) {
        if (!warehouse || !warehouse->is_valid()) {
            return false;
        }
        if (!warehouse->has_road_access() || warehouse->base.distance_from_entry <= 0) {
            return false;
        }
        if (warehouse->road_network() != road_network_id) {
            return false;
        }
        return warehouse->get_permission(BUILDING_STORAGE_PERMISSION_DOCK);
    }
}

int figure_docker::haul_amount() {
    const int og_haul = docker_params().max_loads * docker_load();
    return !!game_features::gameplay_change_dock_double_haul ? 2 * og_haul : og_haul;
}

// OG storageyard_import_loads: whole loads the yard takes of `resource` out of `max_amount`, bounded by its
// free room, its accept/get limit and the city's stock limit for the resource.
int figure_docker::import_loads(building_storage_yard *warehouse, e_resource resource, int max_amount) {
    if (!warehouse || warehouse->is_not_accepting(resource)) {
        return 0;
    }

    int free_room = 0;
    for (building_storage_room *space = warehouse->room(); space; space = space->next_room()) {
        free_room += (room_free_for(space, resource) / docker_load()) * docker_load();
    }

    const int accept_room = warehouse->accepting_amount(resource) - warehouse->amount(resource);
    const int stock_room = g_empire.import_stock_limit(resource) - g_city.resource.yards_stored(resource);
    const int amount = std::min({ max_amount, free_room, accept_room, stock_room });
    return amount > 0 ? amount / docker_load() : 0;
}

figure_trade_ship *figure_docker::moored_ship() {
    building_dock *dock = home()->dcast_dock();
    if (!dock || !dock->runtime_data().trade_ship) {
        return nullptr;
    }

    auto *ship = figure_get<figure_trade_ship>(dock->runtime_data().trade_ship);
    if (!ship || !ship->base.is_alive() || ship->action_state() != ACTION_112_TRADE_SHIP_MOORED) {
        return nullptr;
    }
    return ship;
}

// Remake cap on top of OG's 4-load haul: trade route quota (Ra-adjusted in limit()), per-good trader
// room and the ship's per-visit import budget.
static int docker_import_cap(e_resource resource, figure_trade_ship *ship, empire_city_handle city, empire_trader_handle trader) {
    if (!city.valid()) {
        return 0;
    }

    const auto &route = city.get_route();
    int cap = std::max(0, route.limit(resource) - route.traded(resource));
    cap = std::min(cap, trader.sell_room(resource));
    if (ship_has_import_budgets(ship)) {
        cap = std::min(cap, ship->import_budget_remaining(resource) * docker_load());
    }
    return cap;
}

int figure_docker::try_import_resource(building *b, e_resource resource, empire_city_handle city) {
    building_storage_yard *warehouse = b->dcast_storage_yard();
    if (!warehouse || !warehouse->get_permission(BUILDING_STORAGE_PERMISSION_DOCK)) {
        return 0;
    }

    const int offered = std::min<int>(base.resource_amount_full, docker_import_cap(resource, moored_ship(), city, trader()));
    const int loads = import_loads(warehouse, resource, offered);

    auto place_one_load = [&]() -> bool {
        // add_import charges a full load, so a room must have room for a whole load.
        for (building_storage_room *space = warehouse->room(); space; space = space->next_room()) {
            if (space->resource() == resource && room_free_for(space, resource) >= docker_load()) {
                space->add_import(resource);
                return true;
            }
        }
        for (building_storage_room *space = warehouse->room(); space; space = space->next_room()) {
            if (space->resource() == RESOURCE_NONE) {
                space->add_import(resource);
                return true;
            }
        }
        return false;
    };

    auto &route = city.get_route();
    int delivered = 0;
    for (int i = 0; i < loads; i++) {
        if (!place_one_load()) {
            break;
        }
        route.increase_traded(resource, docker_load());
        delivered += docker_load();
    }
    return delivered;
}

void figure_docker::set_cart_offset(int direction) const {
    base.cart_offset = docker_cart_offsets[direction];
}

// OG figure_docker_try_export_resource: up to 4 loads of what the yard holds, keeping the city's stock
// limit and the ship's total capacity. The ship's bought counter grows per load here, not on assignment.
int figure_docker::try_export_resource(building *b, e_resource resource, empire_city_handle city) {
    building_storage_yard *warehouse = b->dcast_storage_yard();
    if (!warehouse || !warehouse->get_permission(BUILDING_STORAGE_PERMISSION_DOCK) || !city.valid()) {
        return 0;
    }

    figure_trade_ship *ship = moored_ship();
    int max_amount = haul_amount();
    if (ship && !empire_trader_ignore_total_bag()) {
        max_amount = std::min(max_amount, ship->max_capacity() - (int)ship->total_bought());
    }
    max_amount = std::min(max_amount, trader().buy_room(resource));

    city_resource_handle hresource{ resource };
    const int keep = hresource.trading_amount();
    max_amount = std::min(max_amount, g_city.resource.yards_stored(resource) - keep);

    auto take_one_load = [&]() -> bool {
        // remove_export pays a full load, so only rooms holding a whole load are taken from.
        for (building_storage_room *space = warehouse->room(); space; space = space->next_room()) {
            if (space->resource() == resource && space->stored_first().value >= docker_load()) {
                space->remove_export(resource);
                return true;
            }
        }
        return false;
    };

    auto &route = city.get_route();
    int taken = 0;
    const int loads = max_amount > 0 ? max_amount / docker_load() : 0;
    for (int i = 0; i < loads; i++) {
        if (!take_one_load()) {
            break;
        }
        route.increase_traded(resource, docker_load());
        taken += docker_load();
        if (ship) {
            ship->runtime_data().amount_bought += docker_load();
        }
    }
    return taken;
}

// OG figure_docker_get_closest_warehouse_for_import, plus the remake filters (dock permission,
// dock orders, per-visit import budgets). Score 32, -8 per empty room, -4 per room of the resource
// under 400; only yards scoring under 32 compete, by score + distance from the docker.
building_dest figure_docker::get_closest_warehouse_for_import(tile2i pos, empire_city_handle city, int distance_from_entry, int road_network_id, building_dock *dock, e_resource &import_resource) {
    const resource_list importable = g_empire.importable_resources_from_city(city.handle);

    figure_trade_ship *ship = nullptr;
    if (dock && dock->runtime_data().trade_ship) {
        ship = figure_get<figure_trade_ship>(dock->runtime_data().trade_ship);
    }
    empire_trader_handle session = ship ? ship->empire_trader() : empire_trader_handle{};

    auto allowed = [&](e_resource r) {
        if (!importable[r] || session.sell_full(r)) {
            return false;
        }
        if (!dock) {
            return true;
        }
        return dock->is_trade_accepted(r);
    };

    auto find_warehouse = [&](e_resource resource) -> building_dest {
        int min_distance = 10000;
        building_id min_building_id = 0;
        buildings_valid_do([&](building &b) {
            building_storage_yard *warehouse = b.dcast_storage_yard();
            if (!warehouse_reachable_for_docker(warehouse, road_network_id)) {
                return;
            }

            if (b.num_workers <= 0 || warehouse->is_empty_all()) {
                return;
            }

            if (!import_loads(warehouse, resource, haul_amount())) {
                return;
            }

            int score = 32;
            for (building_storage_room *space = warehouse->room(); space; space = space->next_room()) {
                if (space->resource() == RESOURCE_NONE) {
                    score -= 8;
                } else if (space->resource() == resource && space->stored_first().value < room_capacity()) {
                    score -= 4;
                }
            }

            if (score < 32) {
                const int distance = score + calc_distance_with_penalty(warehouse->tile(), pos, distance_from_entry, warehouse->base.distance_from_entry);
                if (distance < min_distance) {
                    min_distance = distance;
                    min_building_id = b.id;
                }
            }
        }, BUILDING_STORAGE_YARD);

        return warehouse_road_dest(min_building_id);
    };

    if (ship_has_import_budgets(ship)) {
        // Try each viable slot: stopping at the first allowed one re-picked an unreachable resource
        // every tick (budgets only shrink on delivery) and stranded the ship until the idle cap.
        for (const auto &slot : ship->runtime_data().import_budgets) {
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

// OG figure_docker_get_closest_warehouse_for_export: yards holding at least a load of the round-robin
// export resource; score 32, -1 per room holding it.
building_dest figure_docker::get_closest_warehouse_for_export(tile2i pos, empire_city_handle city, int distance_from_entry, int road_network_id, building_dock *dock, e_resource &export_resource) {
    const resource_list exportable = g_empire.exportable_resources_from_city(city.handle);

    figure_trade_ship *ship = nullptr;
    if (dock && dock->runtime_data().trade_ship) {
        ship = figure_get<figure_trade_ship>(dock->runtime_data().trade_ship);
    }
    empire_trader_handle session = ship ? ship->empire_trader() : empire_trader_handle{};

    auto allowed = [&](e_resource r) {
        if (!exportable[r] || session.buy_full(r)) {
            return false;
        }
        if (!dock) {
            return true;
        }
        return dock->is_trade_accepted(r);
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
    buildings_valid_do([&](building &b) {
        building_storage_yard *warehouse = b.dcast_storage_yard();
        if (!warehouse_reachable_for_docker(warehouse, road_network_id)) {
            return;
        }

        if (warehouse->amount(resource) < docker_load()) {
            return;
        }

        int score = 32;
        for (building_storage_room *space = warehouse->room(); space; space = space->next_room()) {
            if (space->resource() == resource && space->stored_first().value > 0) {
                score--;
            }
        }

        if (score < 32) {
            const int distance = score + calc_distance_with_penalty(b.tile, pos, distance_from_entry, b.distance_from_entry);
            if (distance < min_distance) {
                min_distance = distance;
                min_building_id = b.id;
            }
        }
    }, BUILDING_STORAGE_YARD);

    building_dest result = warehouse_road_dest(min_building_id);
    if (result.bid) {
        export_resource = resource;
    }
    return result;
}

empire_trader_handle figure_docker::trader() {
    auto dock = home()->dcast_dock();
    return dock ? dock->empire_trader() : empire_trader_handle{};
}

empire_city_handle figure_docker::trader_city() {
    auto dock = home()->dcast_dock();
    return dock ? dock->trader_city() : empire_city_handle{};
}

// OG docker_deliver_import_resource: the docker takes its loads off the ship when assigned
// (ship->resource_amount -= 4), so other dockers do not chase the same cargo.
bool figure_docker::deliver_import_resource(building *b) {
    building_dock *dock = b->dcast_dock();
    figure_trade_ship *ship = moored_ship();
    if (!dock || !ship || ship->base.get_carrying_amount() < docker_load()) {
        return false;
    }

    e_resource resource;
    auto result = get_closest_warehouse_for_import(tile(), ship->empire_city(), b->distance_from_entry, b->road_network_id, dock, resource);
    if (!result.bid) {
        return false;
    }

    int amount = std::min(haul_amount(), docker_import_cap(resource, ship, ship->empire_city(), ship->empire_trader()));
    amount = std::min(amount, ship->base.get_carrying_amount());
    amount = (amount / docker_load()) * docker_load();
    if (amount <= 0) {
        return false;
    }

    ship->dump_resource(amount);
    set_destination(result.bid);
    base.wait_ticks = 0;
    advance_action(ACTION_1_DOCKER_IMPORT_QUEUE);
    base.destination_tile = result.tile;
    load_resource(resource, amount);
    runtime_data().export_cargo = false;
    return true;
}

bool figure_docker::fetch_export_resource(building *b) {
    building_dock *dock = b->dcast_dock();
    figure_trade_ship *ship = moored_ship();
    if (!dock || !ship) {
        return false;
    }

    if (!empire_trader_ignore_total_bag() && ship->total_bought() >= ship->max_capacity()) {
        return false;
    }

    e_resource resource;
    auto result = get_closest_warehouse_for_export(tile(), ship->empire_city(), b->distance_from_entry, b->road_network_id, dock, resource);
    if (!result.bid) {
        return false;
    }

    set_destination(result.bid);
    advance_action(ACTION_4_DOCKER_EXPORT_GOING_TO_WAREHOUSE);
    base.wait_ticks = 0;
    base.destination_tile = result.tile;
    load_resource(RESOURCE_NONE, 0);
    base.resource_id = resource;
    return true;
}

void figure_docker::return_home() {
    set_destination(home(), home()->tile);
    advance_action(ACTION_6_DOCKER_IMPORT_RETURNING);
    base.wait_ticks = 0;
}

// Import cargo the yard did not take goes back to the ship (OG refunds it to ship->resource_amount).
// Export cargo is the ship's already and is simply handed over.
void figure_docker::return_cargo_to_ship() {
    const bool export_cargo = runtime_data().export_cargo;
    runtime_data().export_cargo = false;
    if (base.resource_id == RESOURCE_NONE || base.resource_amount_full <= 0) {
        return;
    }

    if (figure_trade_ship *ship = export_cargo ? nullptr : moored_ship()) {
        ship->base.resource_amount_full += base.resource_amount_full;
    }
    load_resource(RESOURCE_NONE, 0);
}

void figure_docker::figure_before_action() {
    if (action_state() == ACTION_0_DOCKER_IDLING) {
        base.routing_try_reroute_counter = 0;
    }
}

void figure_docker::figure_action() {
    building *b = home();

    base.use_cart = true;
    if (b->state != BUILDING_STATE_VALID) {
        poof();
        return;
    }

    building_dock *dock_b = b->dcast_dock();
    if (!dock_b) {
        poof();
        return;
    }

    auto &dock = dock_b->runtime_data();
    if (dock.num_ships) {
        dock.num_ships--;
    }

    if (dock.trade_ship) {
        auto ship = figure_get<figure_trade_ship>(dock.trade_ship);
        if (ship->base.state != FIGURE_STATE_ALIVE || ship->type() != FIGURE_TRADE_SHIP) {
            dock.trade_ship = 0;
        } else if (ship->empire_trader().has_traded_max(ship->max_capacity())) {
            dock.trade_ship = 0;
        } else if (ship->action_state() == ACTION_115_TRADE_SHIP_LEAVING) {
            dock.trade_ship = 0;
        }
    }

    base.terrain_usage = TERRAIN_USAGE_ROADS;
    switch (action_state()) {
    case ACTION_8_DOCKER_RECALCULATE:
        // Remake: OG kills a lost docker; we walk it home (cargo kept for the ship), giving up after 5 tries.
        if (++base.routing_try_reroute_counter > 5) {
            base.routing_try_reroute_counter = 0;
            poof();
            return;
        }
        base.cart_image_id = 0;
        return_home();
        break;

    case ACTION_0_DOCKER_IDLING:
        return_cargo_to_ship();
        base.resource_id = RESOURCE_NONE;
        base.cart_image_id = 0;
        base.animctx.frame = 0;
        // OG: an idle docker waits for work and only dies when it is off the road.
        if (!map_terrain_is(tile(), TERRAIN_ROAD)) {
            poof();
            return;
        }
        if (!deliver_import_resource(b)) {
            fetch_export_resource(b);
        }
        break;

    case ACTION_1_DOCKER_IMPORT_QUEUE:
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
                advance_action(ACTION_3_DOCKER_IMPORT_GOING_TO_WAREHOUSE);
                base.wait_ticks = 0;
                dock.queued_docker_id = 0;
            }
        } else {
            bool has_queued_docker = false;
            for (int i = 0; i < 3; i++) {
                if (dock.docker_ids[i]) {
                    figure *docker = figure_get(dock.docker_ids[i]);
                    if (docker->id == dock.queued_docker_id && docker->state == FIGURE_STATE_ALIVE) {
                        if (docker->action_state == ACTION_1_DOCKER_IMPORT_QUEUE
                            || docker->action_state == ACTION_2_DOCKER_EXPORT_QUEUE) {
                            has_queued_docker = true;
                        }
                    }
                }
            }

            if (!has_queued_docker) {
                dock.queued_docker_id = 0;
            }
        }
        break;

    case ACTION_2_DOCKER_EXPORT_QUEUE:
        // OG quirk kept: the extra ++wait_ticks >= 20 below ends the 80-tick hand-over early.
        if (dock.queued_docker_id <= 0) {
            dock.queued_docker_id = id();
            base.wait_ticks = 0;
        }
        if (dock.queued_docker_id == id()) {
            dock.num_ships = 120;
            base.wait_ticks++;
            if (base.wait_ticks >= 80) {
                advance_action(ACTION_0_DOCKER_IDLING);
                base.wait_ticks = 0;
                base.main_image_id = 0;
                base.cart_image_id = 0;
                dock.queued_docker_id = 0;
            }
        }
        base.wait_ticks++;
        if (base.wait_ticks >= 20) {
            advance_action(ACTION_0_DOCKER_IDLING);
            base.wait_ticks = 0;
        }
        base.animctx.frame = 0;
        break;

    case ACTION_3_DOCKER_IMPORT_GOING_TO_WAREHOUSE:
        if (destination()->state != BUILDING_STATE_VALID) {
            return_home();
            break;
        }
        do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, ACTION_7_DOCKER_IMPORT_AT_WAREHOUSE, ACTION_8_DOCKER_RECALCULATE);
        break;

    case ACTION_4_DOCKER_EXPORT_GOING_TO_WAREHOUSE:
        if (destination()->state != BUILDING_STATE_VALID) {
            return_home();
            break;
        }
        do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, ACTION_9_DOCKER_EXPORT_AT_WAREHOUSE, ACTION_8_DOCKER_RECALCULATE);
        break;

    case ACTION_5_DOCKER_EXPORT_RETURNING:
        if (do_gotobuilding(home(), true, TERRAIN_USAGE_ROADS, ACTION_2_DOCKER_EXPORT_QUEUE, ACTION_8_DOCKER_RECALCULATE)) {
            load_resource(RESOURCE_NONE, 0);
            runtime_data().export_cargo = false;
        }
        break;

    case ACTION_6_DOCKER_IMPORT_RETURNING:
        if (do_gotobuilding(home(), true, TERRAIN_USAGE_ROADS, ACTION_0_DOCKER_IDLING, ACTION_8_DOCKER_RECALCULATE)) {
            return_cargo_to_ship();
        }
        break;

    case ACTION_7_DOCKER_IMPORT_AT_WAREHOUSE:
        base.wait_ticks++;
        if (base.wait_ticks > 10) {
            figure_trade_ship *ship = moored_ship();
            const e_resource resource = base.resource_id;
            const int delivered = ship ? try_import_resource(destination(), resource, ship->empire_city()) : 0;
            if (delivered > 0) {
                dump_resource(delivered);
                ship->runtime_data().failed_dock_attempts = 0;
                for (int i = 0; i < delivered / docker_load(); i++) {
                    ship->consume_import_budget(resource);
                    trader().record_sold_resource(resource);
                }
            }

            return_home();
            // OG: after a delivery the docker may head straight to a yard for an export.
            if (delivered > 0 && base.resource_amount_full <= 0) {
                fetch_export_resource(b);
            }
        }
        base.animctx.frame = 0;
        break;

    case ACTION_9_DOCKER_EXPORT_AT_WAREHOUSE:
        base.wait_ticks++;
        if (base.wait_ticks > 10) {
            const e_resource resource = base.resource_id;
            const int taken = try_export_resource(destination(), resource, trader_city());
            return_home();
            if (taken > 0) {
                if (figure_trade_ship *ship = moored_ship()) {
                    ship->runtime_data().failed_dock_attempts = 0;
                }
                int loaded = 0;
                for (int i = 0; i < taken / docker_load(); i++) {
                    loaded += trader().record_bought_resource(resource);
                }
                load_resource(resource, loaded);
                runtime_data().export_cargo = true;
                advance_action(ACTION_5_DOCKER_EXPORT_RETURNING);
            } else {
                load_resource(RESOURCE_NONE, 0);
                fetch_export_resource(b);
            }
        }
        base.animctx.frame = 0;
        break;

    case ACTION_10_DOCKER_ON_FERRY:
        // OG FIGURE_ACTION_ON_FERRY: walker and cart hidden while aboard.
        base.cart_image_id = 0;
        break;

    case ACTION_11_DOCKER_WAIT_FOR_FERRY:
        // OG: waits at the landing; after 100 ticks without a queue slot it turns idle.
        base.animctx.frame = 0;
        if (++base.wait_ticks > 100) {
            base.wait_ticks = 0;
            if (!figure_is_queued_for_ferry(id())) {
                advance_action(ACTION_0_DOCKER_IDLING);
            }
        }
        break;
    }

    // OG draws no docker without a cart (image 0): idle and import-queued dockers stay hidden at the dock.
    base.set_flag(e_figure_flag_invisible, action_state(ACTION_0_DOCKER_IDLING, ACTION_1_DOCKER_IMPORT_QUEUE, ACTION_10_DOCKER_ON_FERRY));
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

    auto &rt = dock->runtime_data();
    for (int i = 0; i < 3; i++) {
        if (rt.docker_ids[i] == id()) {
            rt.docker_ids[i] = 0;
        }
    }
}
