#include "building_dock.h"

#include "building/building_bazaar.h"
#include "building/building.h"
#include "building/building_type.h"
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
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "scenario/map.h"
#include "game/game.h"
#include "window/building/distribution.h"
#include "graphics/elements/lang_text.h"
#include "city/labor.h"
#include "city/city.h"
#include "js/js_game.h"

building_dock::static_params dock_m;

void building_dock::static_params::load(archive arch) {

}

void building_dock::on_create(int orientation) {
    data.dock.orientation = orientation;
    data.dock.trading_goods.one();
}

void building_dock::on_place(int orientation, int variant) {
    int orientation_rel = city_view_relative_orientation(orientation);
    map_water_add_building(id(), tile(), params().building_size, anim(animkeys().base).first_img() + orientation_rel);

    building_impl::on_place(orientation, variant);
}

void building_dock::on_destroy() {
}

bool building_dock::can_play_animation() const {
    if (data.dock.num_ships > 0) {
        return true;
    }

    map_sprite_animation_set(tile(), 1);
    return false;
}

void building_dock::update_count() const {
    const bool is_active = num_workers() > 0 && base.has_open_water_access;
    g_city.buildings.track_building(type(), id(), is_active);
}

void building_dock::update_map_orientation(int orientation) {
    int image_offset = city_view_relative_orientation(data.dock.orientation);
    int image_id = anim(animkeys().base).first_img() + image_offset;
    map_water_add_building(id(), tile(), 3, image_id);
}

void building_dock::on_place_update_tiles(int orientation, int variant) {
    int img_id = anim(animkeys().base).first_img() + orientation;
    map_water_add_building(id(), tile(), size(), img_id);
}

void building_dock::spawn_figure() {
    if (!has_road_access()) {
        return;
    }

    check_labor_problem();
    common_spawn_labor_seeker(50);
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
    for (int i = 0; i < 3; i++) {
        if (data.dock.docker_ids[i]) {
            if (figure_get(data.dock.docker_ids[i])->type == FIGURE_DOCKER) {
                existing_dockers++;
            } else {
                data.dock.docker_ids[i] = 0;
            }
        }
    }
    
    if (existing_dockers > max_dockers) {
        // too many dockers, poof one of them
        for (int i = 2; i >= 0; i--) {
            if (data.dock.docker_ids[i]) {
                figure_get(data.dock.docker_ids[i])->poof();
                return;
            }
        }
    } 
    
    if (existing_dockers < max_dockers) {
        figure *f = figure_create(FIGURE_DOCKER, base.road_access, DIR_4_BOTTOM_LEFT);
        f->action_state = FIGURE_ACTION_132_DOCKER_IDLING;
        f->set_home(&base);
        for (int i = 0; i < 3; i++) {
            if (!data.dock.docker_ids[i]) {
                data.dock.docker_ids[i] = f->id;
                return;
            }
        }
    }
}

void building_dock::on_tick(bool refresh_only) {
    auto &anim_wharf = base.anim;
    if (anim_wharf.valid()) {
        data.dock.docker_anim_frame++;
        data.dock.docker_anim_frame %= (anim_wharf.max_frames * anim_wharf.frame_duration);
    }
}

void building_dock::update_graphic() {
    int num_idle_dockers = count_idle_dockers();
    if (num_idle_dockers > 0) {
        int image_dock = map_image_at(tile());
        xstring animkey;
        int image_dock_base = anim(animkeys().base).first_img();

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

    if (anim_dockers.valid()) {
        int img_id = anim_dockers.start() + (data.dock.docker_anim_frame / anim_dockers.frame_duration) * 4;
        ImageDraw::img_generic(ctx, img_id, point + anim_dockers.pos, color_mask, 1.f, true);
    }
    return false;
}

void building_dock::bind_dynamic(io_buffer *iob, size_t version) {
    iob->bind(BIND_SIGNATURE_INT16, &data.dock.queued_docker_id);
    iob->bind(BIND_SIGNATURE_INT32, &data.dock.dock_tiles[0]);
    iob->bind(BIND_SIGNATURE_INT32, &data.dock.dock_tiles[1]);
    iob->bind(BIND_SIGNATURE_UINT64, data.dock.trading_goods.data_ptr());
    iob->bind____skip(9);
    iob->bind(BIND_SIGNATURE_UINT8, &data.dock.num_ships);
    iob->bind____skip(2);
    iob->bind(BIND_SIGNATURE_INT8, &data.dock.orientation);
    iob->bind____skip(3);
    for (int i = 0; i < 3; i++) {
        iob->bind(BIND_SIGNATURE_INT16, &data.dock.docker_ids[i]);
    }
    iob->bind(BIND_SIGNATURE_INT16, &data.dock.trade_ship_id);
}

int building_dock::count_idle_dockers() const {
    int num_idle = 0;
    for (int i = 0; i < 3; i++) {
        if (data.dock.docker_ids[i]) {
            figure* f = figure_get(data.dock.docker_ids[i]);
            if (f->action_state == FIGURE_ACTION_132_DOCKER_IDLING
                || f->action_state == FIGURE_ACTION_133_DOCKER_IMPORT_QUEUE) {
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
    data.dock.trading_goods.zeroes(64);
}

int building_dock::trader_id() {
    return figure_get(data.dock.trade_ship_id)->trader_id;
}

int building_dock::trader_city_id() {
    return data.dock.trade_ship_id
                ? figure_get(data.dock.trade_ship_id)->empire_city_id
                : 0;
}

bool building_dock::is_trade_accepted(e_resource r) {
    return data.dock.trading_goods.is_set(r);
}

void building_dock::toggle_good_accepted(e_resource r) {
    data.dock.trading_goods.flip(r);
}

bool building_dock::accepts_ship(int ship_id) {
    figure* f = figure_get(ship_id);

    empire_city* city = g_empire.city(f->empire_city_id);
    const resource_list resources = city_resource_get_available();
    int any_acceptance = 0;
    for (auto r: resources) {
        if (city->sells_resource[r.type] || city->buys_resource[r.type]) {
            any_acceptance += is_trade_accepted(r.type) ? 1 : 0;
        }
    }

    return (any_acceptance > 0);
}

tile2i building_dock::moor_tile() const {
    vec2i offset;
    switch (data.dock.orientation) {
    case 0: offset = { 1, -1 };  break;
    case 1: offset = { 3, 1 }; break;
    case 2: offset = { 1, 3 }; break;
    default: offset = { -1, 1 }; break;
    }

    return tile().shifted(offset.x, offset.y);
}

tile2i building_dock::wait_tile() const {
    vec2i offset;
    switch (data.dock.orientation) {
    case 0: offset = { 2, -2 };  break;
    case 1: offset = { 4, 2 }; break;
    case 2: offset = { 2, 4 }; break;
    default: offset = { -2, 2 }; break;
    }

    return tile().shifted(offset.x, offset.y);
}

tile2i building_dock::reid_tile() const {
    vec2i offset;
    switch (data.dock.orientation) {
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
        if (!dock->data.dock.trade_ship_id || dock->data.dock.trade_ship_id == ship_id) {
            break;
        }
    }

    // BUG: when 10 docks in city, always takes last one... regardless of whether it is free
    if (!better_dock) {
        return { 0, tile2i::invalid };
    }

    tile2i moor_tile = better_dock->moor_tile();
    better_dock->data.dock.trade_ship_id = ship_id;
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
