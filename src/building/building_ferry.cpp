#include "building/building_ferry.h"

#include "city/city_labor.h"
#include "grid/water.h"
#include "grid/image.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/terrain.h"
#include "grid/routing/routing.h"
#include "graphics/image.h"
#include "graphics/animkeys.h"
#include "graphics/view/view.h"
#include "js/js_game.h"
#include "figuretype/figure_ferry_boat.h"
#include "core/random.h"
#include "core/profiler.h"
#include "game/game_events.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_ferry);
BUILDING_RUNTIME_DATA_IMPL(building_ferry)

static int __ferry_partner_id(int bid) {
    building *partner = map_routing_ferry_partner(building_get(bid));
    return partner ? partner->id : 0;
}
ANK_FUNCTION_1(__ferry_partner_id);

void building_ferry::on_create(int orientation) {
    base.orientation = orientation;
    auto &d = runtime_data();
    d.phase = phase_wait_home;
    d.wait_remaining = 0;
}

void building_ferry::update_month() {
    building_impl::update_month();

    map_water_update_docking_points(base, get_orientation(), 2);
}

bool building_ferry::target_route_tile_blocked(int grid_offset) const {
    return false;
}

void building_ferry::on_place_update_tiles(int orientation, int variant) {
    int img_id = base_img() + orientation;
    map_water_add_building(id(), tile(), size(), img_id);
    map_building_tiles_add(id(), tile(), size(), img_id, TERRAIN_BUILDING|TERRAIN_ROAD|TERRAIN_FERRY_ROUTE);
}

void building_ferry::update_map_orientation(int orientation) {
    int image_offset = g_camera.relative_orientation(base.orientation);
    int image_id = base_img() + image_offset;
    map_water_add_building(id(), tile(), size(), image_id);
}

bool building_ferry::force_draw_height_tile(painter &ctx, tile2i t, vec2i pixel, color mask) {
    OZZY_PROFILER_FUNCTION()

    if (this->main()->tile() == t) {
        int image_id = current_params().first_img(animkeys().top);
        int image_offset = g_camera.relative_orientation(base.orientation);

        auto& command = ImageDraw::create_subcommand(ctx, render_command_t::ert_drawtile_top);
        command.image_id = image_id + image_offset;
        command.pixel = pixel + vec2i{ -HALF_TILE_WIDTH_PIXELS, -HALF_TILE_HEIGHT_PIXELS };
        command.mask = mask;

        return true;
    }

    return false;
}

bool building_ferry::force_draw_top_tile(painter &ctx, tile2i t, vec2i pixel, color mask) {
    OZZY_PROFILER_FUNCTION()

    if (this->main()->tile() == t) {
        return true;
    }

    return false;
}

bool building_ferry::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    return true;
}

void building_ferry::bind_dynamic(io_buffer *iob, size_t verrsion) {
    iob->bind____skip(88);
    iob->bind(BIND_SIGNATURE_UINT8, &base.orientation);
    iob->bind(BIND_SIGNATURE_INT32, &base.tiles[0]);
    iob->bind(BIND_SIGNATURE_INT32, &base.tiles[1]);
}

tile2i building_ferry::dock_tile() const {
    if (base.tiles[0] > 0) {
        tile2i dock(base.tiles[0]);
        if (map_terrain_is(dock, TERRAIN_WATER)) {
            return dock;
        }
    }

    water_access_tiles fpoints = map_water_get_access_points(base, get_orientation(), 1);
    if (fpoints.point_a.valid()) {
        return fpoints.point_a;
    }
    return fpoints.point_b;
}

void building_ferry::roll_dock_wait() {
    const auto &p = current_params();
    int min_w = p.dock_wait_ticks_min ? p.dock_wait_ticks_min : 80;
    int max_w = p.dock_wait_ticks_max ? p.dock_wait_ticks_max : 220;
    if (max_w < min_w) {
        max_w = min_w;
    }

    random_generate_next();
    runtime_data().wait_remaining = min_w + (int)(random_short() % (uint16_t)(max_w - min_w + 1));
}

bool building_ferry::is_pair_leader(building *partner) const {
    return partner && id() < partner->id;
}

void building_ferry::update_crossing() {
    building *partner = map_routing_ferry_partner(&base);
    if (!is_pair_leader(partner)) {
        return;
    }

    figure *fa = base.get_figure(BUILDING_SLOT_BOAT);
    figure *fb = partner->get_figure(BUILDING_SLOT_BOAT);
    auto *boat_a = fa ? fa->dcast_ferry_boat() : nullptr;
    auto *boat_b = fb ? fb->dcast_ferry_boat() : nullptr;
    if (!boat_a || !boat_b) {
        return;
    }

    auto &d = runtime_data();
    const bool both_idle = boat_a->is_idle_at_dock() && boat_b->is_idle_at_dock();

    switch (d.phase) {
    case phase_wait_home:
        if (d.wait_remaining > 0) {
            d.wait_remaining--;
        }
        if (d.wait_remaining <= 0 && both_idle) {
            auto *partner_ferry = partner->dcast_ferry();
            events::emit(event_ferry_boat_goto{ (figure_id)boat_a->id(), partner_ferry->dock_tile() });
            events::emit(event_ferry_boat_goto{ (figure_id)boat_b->id(), dock_tile() });
            d.phase = phase_crossing;
        }
        break;

    case phase_crossing:
        if (both_idle) {
            roll_dock_wait();
            d.phase = phase_wait_away;
        }
        break;

    case phase_wait_away:
        if (d.wait_remaining > 0) {
            d.wait_remaining--;
        }
        if (d.wait_remaining <= 0 && both_idle) {
            auto *partner_ferry = partner->dcast_ferry();
            events::emit(event_ferry_boat_goto{ (figure_id)boat_a->id(), dock_tile() });
            events::emit(event_ferry_boat_goto{ (figure_id)boat_b->id(), partner_ferry->dock_tile() });
            d.phase = phase_returning;
        }
        break;

    case phase_returning:
        if (both_idle) {
            roll_dock_wait();
            d.phase = phase_wait_home;
        }
        break;
    }
}

void building_ferry::spawn_figure() {
    check_labor_problem();

    if (!has_road_access()) {
        return;
    }

    common_spawn_labor_seeker(current_params().min_houses_coverage);

    int boat_id = base.get_figure_id(BUILDING_SLOT_BOAT);
    if (boat_id <= 0) {
        if (!map_routing_ferry_has_routes(&base)) {
            return;
        }

        if (num_workers() <= 0) {
            return;
        }

        tile2i dock = dock_tile();
        if (dock.valid() && map_terrain_is(dock, TERRAIN_WATER)) {
            figure *f = figure_create(FIGURE_FERRY_BOAT, dock, DIR_4_BOTTOM_LEFT);
            if (f) {
                f->action_state = ACTION_0_FERRY_BOAT_CREATED;
                f->set_home(id());
                base.set_figure(BUILDING_SLOT_BOAT, f);
                random_generate_next();
                f->wait_ticks = random_short() % 20;
            }
        }
    }

    if (runtime_data().wait_remaining <= 0 && runtime_data().phase == phase_wait_home) {
        roll_dock_wait();
    }

    update_crossing();
}
