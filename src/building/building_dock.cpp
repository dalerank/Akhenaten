#include "building_dock.h"

#include "building/building_bazaar.h"
#include "building/building.h"
#include "building/building_type.h"
#include "figuretype/figure_docker.h"
#include "grid/water.h"
#include "city/buildings.h"
#include "city/city_resource.h"
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
#include "window/building/distribution.h"
#include "graphics/elements/lang_text.h"
#include "figuretype/figure_trader_ship.h"
#include "city/city.h"
#include "construction/build_planner.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_dock);

int building_dock::preview::construction_update(build_planner &planer, tile2i start, tile2i end) const {
    const auto &params = building_static_params::get(planer.build_type);
    const auto result = map_shore_determine_orientation(end, params.building_size, true);
    planer.draw_as_constructing = result.match;
    return 1;
}

void building_dock::preview::setup_preview_graphics(build_planner &planer) const {
    const auto &params = building_static_params::get(planer.build_type);
    const int imgid = params.base_img() + planer.relative_orientation;
    planer.set_tiles_building(imgid, params.building_size);
}

void building_dock::on_create(int orientation) {
    base.orientation = orientation;
    runtime_data().trading_goods.one();
}

void building_dock::on_place(int orientation, int variant) {
    int orientation_rel = city_view_relative_orientation(orientation);
    map_water_add_building(id(), tile(), current_params().building_size, base_img() + orientation_rel);

    building_impl::on_place(orientation, variant);
}

void building_dock::on_destroy() {
}

bool building_dock::can_play_animation() const {
    if (runtime_data().num_ships > 0) {
        return true;
    }

    map_sprite_animation_set(tile(), 1);
    return false;
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
    int image_offset = city_view_relative_orientation(base.orientation);
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
        f->action_state = ACTION_132_DOCKER_IDLING;
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

void building_dock::update_graphic() {
    int num_idle_dockers = count_idle_dockers();
    if (num_idle_dockers > 0) {
        int image_dock = map_image_at(tile());
        xstring animkey;
        int image_dock_base = base_img();

        if (image_dock == image_dock_base) animkey = animkeys().work_n;
        else if (image_dock == image_dock_base + 1) animkey = animkeys().work_w;
        else if (image_dock == image_dock_base + 2) animkey = animkeys().work_s;
        else animkey = animkeys().work_e;

        set_animation(animkey);
    }

    building_impl::update_graphic();
}

bool building_dock::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i t, color color_mask) {
    auto &anim_dockers = base.anim;
    auto &d = runtime_data();
    if (anim_dockers.valid()) {
        int img_id = anim_dockers.start_frame() + (d.docker_anim_frame / anim_dockers.frame_duration) * 4;

        auto& command = ImageDraw::create_subcommand(render_command_t::ert_generic);
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
            if (f->action_state == ACTION_132_DOCKER_IDLING
                || f->action_state == ACTION_133_DOCKER_IMPORT_QUEUE) {
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

empire_trader_handle building_dock::empire_trader() const {
    auto& d = runtime_data();
    if (d.trade_ship == 0) {
        return empire_trader_handle{};
    }

    auto ship = figure_get<figure_trade_ship>(d.trade_ship);
    assert(ship != nullptr);

    return ship->empire_trader();
}

empire_city_handle building_dock::trader_city() {
    auto &d = runtime_data();
    auto ship = d.trade_ship ? figure_get<figure_trade_ship>(d.trade_ship) : nullptr;
    return { ship ? ship->empire_city() : empire_city_handle{} };
}

bool building_dock::is_trade_accepted(e_resource r) {
    return runtime_data().trading_goods.is_set(r);
}

void building_dock::toggle_good_accepted(e_resource r) {
    runtime_data().trading_goods.flip(r);
}

bool building_dock::accepts_ship(int ship_id) {
    auto ship = figure_get<figure_trade_ship>(ship_id);
    if (!ship) {
        return false;
    }

    empire_city_handle city = ship->empire_city();
    const resource_list resources = g_city.resource.available();
    for (const resource_value r: resources) {
        if (is_trade_accepted(r.type) && (city.sells_resource(r.type) || city.buys_resource(r.type))) {
            return true;
        }
    }

    return false;
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

    const auto &docks = g_city.buildings.track_buildings(BUILDING_DOCK);
    building_dock* better_dock = nullptr;
    for (const auto &bid: docks) {
        building_dock *dock = ::building_get(bid)->dcast_dock();
        if (!dock || !dock->num_workers()) {
            continue;
        }

        if (!dock->accepts_ship(ship_id)) {
            better_dock = nullptr;
            continue;
        }

        better_dock = dock;
        auto &d = dock->runtime_data();
        if (!d.trade_ship || d.trade_ship == ship_id) {
            break;
        }
    }

    // BUG: when 10 docks in city, always takes last one... regardless of whether it is free
    if (!better_dock) {
        return { 0, tile2i::invalid };
    }

    tile2i moor_tile = better_dock->moor_tile();
    better_dock->runtime_data().trade_ship = ship_id;
    return {better_dock->id(), moor_tile };
}

building_dest map_get_queue_destination_dock(int ship_id) {
    if (!g_city.buildings.has_working_dock()) {
        return { 0, tile2i::invalid };
    }

    // first queue position
    const auto &docks = g_city.buildings.track_buildings(BUILDING_DOCK);
    for (const auto &bid : docks) {
        building_dock *dock = ::building_get(bid)->dcast_dock();
        if (!dock) {
            continue;
        }

        if (!dock->accepts_ship(ship_id)) {
            continue;
        }

        tile2i wait_tile = dock->wait_tile();
        if (!map_has_figure_at(wait_tile)) {
            return {dock->id(), wait_tile};
        }
    }

    // second queue position
    building_dock *better_dock = nullptr;
    for (const auto &bid : docks) {
        building_dock *dock = ::building_get(bid)->dcast_dock();
        if (!dock) {
            continue;
        }

        if (!dock->accepts_ship(ship_id)) {
            continue;
        }
        
        tile2i reid_tile = dock->reid_tile();
        if (!map_has_figure_at(reid_tile)) {
            return {dock->id(), reid_tile};
        }
    }

    return {0, tile2i::invalid};
}
