#include "building_dock.h"

#include "building/building_bazaar.h"
#include "building/building.h"
#include "building/building_type.h"
#include "building/building_storage_yard.h"
#include "figuretype/figure_docker.h"
#include "grid/water.h"
#include "city/buildings.h"
#include "city/city_buildings.h"
#include "city/city_resource.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "empire/empire.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/sprite.h"
#include "grid/image.h"
#include "grid/building_tiles.h"
#include "grid/routing/routing.h"
#include "grid/terrain.h"
#include "grid/building.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "scenario/map.h"
#include "game/game.h"
#include "graphics/elements/lang_text.h"
#include "figuretype/figure_trader_ship.h"
#include "empire/trader_handler.h"
#include "city/city.h"
#include "js/js_game.h"

BUILDING_RUNTIME_DATA_IMPL(building_dock)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_dock);

void building_dock::on_create(int orientation) {
    base.orientation = orientation;
    runtime_data().trading_goods.one();
}

void building_dock::on_place(int orientation, int variant) {
    int orientation_rel = g_camera.relative_orientation(orientation);
    map_water_add_building(id(), tile(), current_params().building_size, base_img() + orientation_rel);

    building_impl::on_place(orientation, variant);
}

void building_dock::update_count() const {
    const bool is_active = num_workers() > 0 && base.has_open_water_access;
    g_city.buildings.track_building(base, is_active);
}

void building_dock::update_month() {
    building_impl::update_month();

    map_water_update_docking_points(base, get_orientation(), 2);
}

void building_dock::update_map_orientation(int orientation) {
    int image_offset = g_camera.relative_orientation(base.orientation);
    int image_id = base_img() + image_offset;
    map_water_add_building(id(), tile(), 3, image_id);
}

void building_dock::on_place_update_tiles(int orientation, int variant) {
    int img_id = base_img() + orientation;
    map_water_add_building(id(), tile(), size(), img_id);
}

void building_dock::spawn_figure() {
    if (!has_road_access()) {
        return;
    }

    check_labor_problem();
    common_spawn_labor_seeker(current_params().min_houses_coverage);
    int pct_workers = worker_percentage();
    int max_dockers;
    if (pct_workers >= 75) {
        max_dockers = 3;
    } else if (pct_workers >= 50) {
        max_dockers = 2;
    } else if (pct_workers > 0) {
        max_dockers = 1;
    } else {
        max_dockers = 0;
    }
    // count existing dockers
    int existing_dockers = 0;
    auto &d = runtime_data();
    for (int i = 0; i < 3; i++) {
        if (d.docker_ids[i]) {
            if (figure_get(d.docker_ids[i])->type == FIGURE_DOCKER) {
                existing_dockers++;
            } else {
                d.docker_ids[i] = 0;
            }
        }
    }
    
    if (existing_dockers > max_dockers) {
        // too many dockers, poof one of them
        for (int i = 2; i >= 0; i--) {
            if (d.docker_ids[i]) {
                figure_get(d.docker_ids[i])->poof();
                return;
            }
        }
    } 
    
    if (existing_dockers < max_dockers) {
        figure *f = figure_create(FIGURE_DOCKER, base.road_access, DIR_4_BOTTOM_LEFT);
        f->action_state = ACTION_0_DOCKER_IDLING;
        f->set_home(&base);
        for (int i = 0; i < 3; i++) {
            if (!d.docker_ids[i]) {
                d.docker_ids[i] = f->id;
                return;
            }
        }
    }
}

void building_dock::on_tick(bool refresh_only) {
    auto &anim_wharf = base.anim;
    auto &d = runtime_data();
    if (anim_wharf.valid()) {
        d.docker_anim_frame++;
        d.docker_anim_frame %= (anim_wharf.max_frames * anim_wharf.frame_duration);
    }
}

bool building_dock::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i t, color color_mask) {
    auto &anim_dockers = base.anim;
    auto &d = runtime_data();
    if (anim_dockers.valid()) {
        int img_id = anim_dockers.start_frame() + (d.docker_anim_frame / anim_dockers.frame_duration) * 4;

        auto& command = ImageDraw::create_subcommand(ctx, render_command_t::ert_generic);
        command.image_id = img_id;
        command.pixel = point + anim_dockers.pos;
        command.mask = color_mask;
        command.flags = ImgFlag_InternalOffset;
    }
    return false;
}

void building_dock::bind_dynamic(io_buffer *iob, size_t version) {
    auto &d = runtime_data();
    iob->bind(BIND_SIGNATURE_INT16, &d.queued_docker_id);
    iob->bind(BIND_SIGNATURE_INT32, &d.dock_tiles[0]);
    iob->bind(BIND_SIGNATURE_INT32, &d.dock_tiles[1]);
    iob->bind(BIND_SIGNATURE_UINT64, d.trading_goods.data_ptr());
    iob->bind____skip(9);
    iob->bind(BIND_SIGNATURE_UINT8, &d.num_ships);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_INT8, &base.orientation);
    iob->bind____skip(3);

    iob->bind(BIND_SIGNATURE_INT16, &d.docker_ids[0]);
    iob->bind(BIND_SIGNATURE_INT16, &d.docker_ids[1]);
    iob->bind(BIND_SIGNATURE_INT16, &d.docker_ids[2]);

    iob->bind(BIND_SIGNATURE_INT16, &d.trade_ship);
}

int building_dock::count_idle_dockers() const {
    int num_idle = 0;
    auto &d = runtime_data();
    for (int i = 0; i < 3; i++) {
        if (d.docker_ids[i]) {
            figure* f = figure_get(d.docker_ids[i]);
            if (f->action_state == ACTION_0_DOCKER_IDLING
                || f->action_state == ACTION_1_DOCKER_IMPORT_QUEUE) {
                num_idle++;
            }
        }
    }
    return num_idle;
}

bool map_tile_is_connected_to_open_water(tile2i tile) {
    tile2i river_entry = scenario_map_river_entry();
    map_routing_calculate_distances_water_boat(river_entry);
    return map_terrain_is_adjacent_to_open_water(tile, 3);
}

void building_dock::unaccept_all_goods() {
    runtime_data().trading_goods.zeroes(64);
}

void building_dock::accept_all_goods() {
    runtime_data().trading_goods.one();
}

bool building_dock::accepts_any_goods() const {
    return runtime_data().trading_goods.is_not_zero();
}

empire_trader_handle building_dock::empire_trader() const {
    auto& d = runtime_data();
    if (d.trade_ship == 0) {
        return empire_trader_handle{};
    }

    auto ship = figure_get<figure_trade_ship>(d.trade_ship);
    verify_no_crash(ship != nullptr);

    return ship->empire_trader();
}

empire_city_handle building_dock::trader_city() {
    auto &d = runtime_data();
    auto ship = d.trade_ship ? figure_get<figure_trade_ship>(d.trade_ship) : nullptr;
    return { ship ? ship->empire_city() : empire_city_handle{} };
}

bool building_dock::is_trade_accepted(e_resource r) const {
    return runtime_data().trading_goods.is_set(r);
}

void building_dock::toggle_good_accepted(e_resource r) {
    runtime_data().trading_goods.flip(r);
}

int building_dock::count_matching_goods(const resource_list &importable, const resource_list &exportable) const {
    int n = 0;
    for (const auto &r : resource_list::all) {
        const bool active = importable[r.type] || exportable[r.type];
        if (!active) {
            continue;
        }
        if (is_trade_accepted(r.type)) {
            ++n;
        }
    }
    return n;
}

int building_dock::trade_match_score(const resource_list &importable, const resource_list &exportable) const {
    int n = 0;
    for (const auto &r : resource_list::all) {
        if (!is_trade_accepted(r.type)) {
            continue;
        }
        if (importable[r.type]) {
            n += 2; // Prefer unload (city import / ship sell) over buy-only docks
        } else if (exportable[r.type]) {
            n += 1;
        }
    }
    return n;
}

int building_dock::match_score_for_ship(int ship_id) const {
    auto ship = figure_get<figure_trade_ship>(ship_id);
    if (!ship) {
        return 0;
    }

    empire_city_handle city = ship->empire_city();
    const resource_list importable = g_empire.importable_resources_from_city(city.handle);
    const resource_list exportable = g_empire.exportable_resources_from_city(city.handle);

    resource_list import_focus;
    bool budgets_populated = false;
    for (const auto &slot : ship->runtime_data().import_budgets) {
        if (slot.resource == 0) {
            continue;
        }
        budgets_populated = true;
        if (slot.remaining_chunks > 0) {
            const e_resource r = (e_resource)slot.resource;
            // Only count goods the city can still import (quota/stock gates) and per-good room.
            if (importable[r] && !ship->empire_trader().sell_full(r)) {
                import_focus[r] = 1;
            }
        }
    }

    // Need free buy capacity for exports: total bag (TC) or any per-good room (B).
    resource_list export_for_score;
    bool export_room = false;
    if (empire_trader_ignore_total_bag()) {
        empire_trader_handle session = ship->empire_trader();
        for (const auto &entry : exportable) {
            if (entry.value && !session.buy_full(entry.type)) {
                export_for_score[entry.type] = entry.value;
                export_room = true;
            }
        }
    } else {
        const int buy_room = ship->max_capacity() - (int)ship->total_bought();
        if (buy_room >= 100) {
            export_for_score = exportable;
            export_room = true;
        }
    }
    if (!export_room) {
        export_for_score = {};
    }

    if (!budgets_populated) {
        return trade_match_score(importable, export_for_score);
    }

    // Budgets known: remaining feasible imports + current export opportunities.
    return trade_match_score(import_focus, export_for_score);
}

bool building_dock::accepts_ship(int ship_id) {
    return match_score_for_ship(ship_id) > 0;
}

int building_dock::yard_proximity_cost() const {
    if (!has_road_access() || base.distance_from_entry <= 0) {
        return 10000;
    }

    const int road_network_id = base.road_network_id;
    const int distance_from_entry = base.distance_from_entry;
    int min_distance = 10000;

    buildings_valid_do([&](building &b) {
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

        const int distance = calc_distance_with_penalty(
            warehouse->tile(), tile(), distance_from_entry, warehouse->base.distance_from_entry);
        if (distance < min_distance) {
            min_distance = distance;
        }
    }, BUILDING_STORAGE_YARD);

    return min_distance;
}

void building_dock::highlight_waypoints() {
    building_impl::highlight_waypoints();

    auto &d = runtime_data();
    map_highlight_set(d.dock_tiles[0], ehighligth_green);
    map_highlight_set(d.dock_tiles[1], ehighligth_green);
}

void building_dock::set_water_access_tiles(const water_access_tiles &tiles) {
    auto &d = runtime_data();
    d.dock_tiles[0] = tiles.point_a.grid_offset();
    d.dock_tiles[1] = tiles.point_b.grid_offset();
}

tile2i building_dock::moor_tile() const {
    vec2i offset;
    switch (base.orientation) {
    case 0: offset = { 1, -1 };  break;
    case 1: offset = { 3, 1 }; break;
    case 2: offset = { 1, 3 }; break;
    default: offset = { -1, 1 }; break;
    }

    return tile().shifted(offset.x, offset.y);
}

tile2i building_dock::wait_tile() const {
    vec2i offset;
    switch (base.orientation) {
    case 0: offset = { 2, -2 };  break;
    case 1: offset = { 4, 2 }; break;
    case 2: offset = { 2, 4 }; break;
    default: offset = { -2, 2 }; break;
    }

    return tile().shifted(offset.x, offset.y);
}

tile2i building_dock::reid_tile() const {
    vec2i offset;
    switch (base.orientation) {
    case 0: offset = { 2, -3 };  break;
    case 1: offset = { 5, 2 }; break;
    case 2: offset = { 2, 5 }; break;
    default: offset = { -3, 2 }; break;
    }

    return tile().shifted(offset.x, offset.y);
}

building_dest map_get_free_destination_dock(int ship_id) {
    if (!g_city.buildings.has_working_dock()) {
        return { 0, tile2i::invalid };
    }

    auto *ship = figure_get<figure_trade_ship>(ship_id);
    if (!ship) {
        return { 0, tile2i::invalid };
    }

    building_dock *best = nullptr;
    int best_score = -1;
    int best_yard = 0;
    int best_ship_dist = 0;
    const tile2i ship_tile = ship->tile();

    const auto &docks = g_city.buildings.track_buildings(BUILDING_DOCK);
    for (const auto &bid: docks) {
        building_dock *dock = ::building_get(bid)->dcast_dock();
        if (!dock || !dock->num_workers()) {
            continue;
        }

        const int score = dock->match_score_for_ship(ship_id);
        if (score <= 0) {
            continue;
        }

        auto &d = dock->runtime_data();
        if (d.trade_ship && d.trade_ship != ship_id) {
            continue;
        }

        const int yard = dock->yard_proximity_cost();
        const int ship_dist = calc_maximum_distance(ship_tile, dock->moor_tile());
        const bool better = !best
            || score > best_score
            || (score == best_score && yard < best_yard)
            || (score == best_score && yard == best_yard && ship_dist < best_ship_dist);
        if (better) {
            best_score = score;
            best_yard = yard;
            best_ship_dist = ship_dist;
            best = dock;
        }
    }

    if (!best) {
        return { 0, tile2i::invalid };
    }

    // Drop prior reservation if scoring moved the ship to another pier.
    for (const auto &bid : docks) {
        building_dock *dock = ::building_get(bid)->dcast_dock();
        if (dock && dock != best && dock->runtime_data().trade_ship == ship_id) {
            dock->runtime_data().trade_ship = 0;
        }
    }

    best->runtime_data().trade_ship = ship_id;
    return { best->id(), best->moor_tile() };
}

building_dest map_get_better_free_destination_dock(int ship_id, int min_exclusive_score) {
    if (!g_city.buildings.has_working_dock()) {
        return { 0, tile2i::invalid };
    }

    auto *ship = figure_get<figure_trade_ship>(ship_id);
    if (!ship) {
        return { 0, tile2i::invalid };
    }

    building_dock *best = nullptr;
    int best_score = min_exclusive_score;
    int best_yard = 0;
    int best_ship_dist = 0;
    const tile2i ship_tile = ship->tile();

    const auto &docks = g_city.buildings.track_buildings(BUILDING_DOCK);
    for (const auto &bid : docks) {
        building_dock *dock = ::building_get(bid)->dcast_dock();
        if (!dock || !dock->num_workers()) {
            continue;
        }

        const int score = dock->match_score_for_ship(ship_id);
        if (score <= min_exclusive_score) {
            continue;
        }

        auto &d = dock->runtime_data();
        if (d.trade_ship && d.trade_ship != ship_id) {
            continue;
        }

        const int yard = dock->yard_proximity_cost();
        const int ship_dist = calc_maximum_distance(ship_tile, dock->moor_tile());
        const bool better = !best
            || score > best_score
            || (score == best_score && yard < best_yard)
            || (score == best_score && yard == best_yard && ship_dist < best_ship_dist);
        if (better) {
            best_score = score;
            best_yard = yard;
            best_ship_dist = ship_dist;
            best = dock;
        }
    }

    if (!best) {
        return { 0, tile2i::invalid };
    }

    for (const auto &bid : docks) {
        building_dock *dock = ::building_get(bid)->dcast_dock();
        if (dock && dock != best && dock->runtime_data().trade_ship == ship_id) {
            dock->runtime_data().trade_ship = 0;
        }
    }

    best->runtime_data().trade_ship = ship_id;
    return { best->id(), best->moor_tile() };
}

building_dest map_get_queue_destination_dock(int ship_id) {
    if (!g_city.buildings.has_working_dock()) {
        return { 0, tile2i::invalid };
    }

    auto *ship = figure_get<figure_trade_ship>(ship_id);
    if (!ship) {
        return { 0, tile2i::invalid };
    }

    const auto &docks = g_city.buildings.track_buildings(BUILDING_DOCK);
    const tile2i ship_tile = ship->tile();

    building_dock *best_wait = nullptr;
    int best_wait_score = -1;
    int best_wait_yard = 0;
    int best_wait_dist = 0;
    tile2i best_wait_tile = tile2i::invalid;

    building_dock *best_reid = nullptr;
    int best_reid_score = -1;
    int best_reid_yard = 0;
    int best_reid_dist = 0;
    tile2i best_reid_tile = tile2i::invalid;

    for (const auto &bid : docks) {
        building_dock *dock = ::building_get(bid)->dcast_dock();
        if (!dock || !dock->num_workers()) {
            continue;
        }

        const int score = dock->match_score_for_ship(ship_id);
        if (score <= 0) {
            continue;
        }

        const int yard = dock->yard_proximity_cost();

        tile2i wait = dock->wait_tile();
        if (!map_has_figure_at(wait)) {
            const int dist = calc_maximum_distance(ship_tile, wait);
            const bool better = !best_wait
                || score > best_wait_score
                || (score == best_wait_score && yard < best_wait_yard)
                || (score == best_wait_score && yard == best_wait_yard && dist < best_wait_dist);
            if (better) {
                best_wait_score = score;
                best_wait_yard = yard;
                best_wait_dist = dist;
                best_wait = dock;
                best_wait_tile = wait;
            }
        }

        tile2i reid = dock->reid_tile();
        if (!map_has_figure_at(reid)) {
            const int dist = calc_maximum_distance(ship_tile, reid);
            const bool better = !best_reid
                || score > best_reid_score
                || (score == best_reid_score && yard < best_reid_yard)
                || (score == best_reid_score && yard == best_reid_yard && dist < best_reid_dist);
            if (better) {
                best_reid_score = score;
                best_reid_yard = yard;
                best_reid_dist = dist;
                best_reid = dock;
                best_reid_tile = reid;
            }
        }
    }

    if (best_wait) {
        return { best_wait->id(), best_wait_tile };
    }
    if (best_reid) {
        return { best_reid->id(), best_reid_tile };
    }
    return { 0, tile2i::invalid };
}
