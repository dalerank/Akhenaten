#include "building/building_ferry.h"

#include "city/city_labor.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "grid/water.h"
#include "grid/image.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/terrain.h"
#include "grid/routing/routing.h"
#include "grid/road_access.h"
#include "grid/grid.h"
#include "graphics/image.h"
#include "graphics/animkeys.h"
#include "graphics/view/view.h"
#include "js/js_game.h"
#include "figure/route.h"
#include "figuretype/figure_cartpusher.h"
#include "figuretype/figure_ferry_boat.h"
#include "core/random.h"
#include "core/profiler.h"

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
    d.queue_head = 0;
    d.queue_count = 0;
    memset(d.queue, 0, sizeof(d.queue));
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

void building_ferry::on_destroy() {
    queue_release_waiting();
    building_impl::on_destroy();
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

bool building_ferry::queue_is_full() const {
    // OG ring_queue: full at capacity - 1
    return runtime_data().queue_count >= FERRY_QUEUE_CAPACITY - 1;
}

int building_ferry::queue_size() const {
    return runtime_data().queue_count;
}

bool building_ferry::queue_contains(figure_id fid) const {
    const auto &d = runtime_data();
    for (int i = 0; i < d.queue_count; i++) {
        int idx = (d.queue_head + i) % FERRY_QUEUE_CAPACITY;
        if (d.queue[idx] == fid) {
            return true;
        }
    }
    return false;
}

bool building_ferry::queue_push(figure_id fid) {
    if (queue_is_full() || fid <= 0) {
        return false;
    }
    auto &d = runtime_data();
    int idx = (d.queue_head + d.queue_count) % FERRY_QUEUE_CAPACITY;
    d.queue[idx] = fid;
    d.queue_count++;
    return true;
}

figure_id building_ferry::queue_pop() {
    auto &d = runtime_data();
    if (d.queue_count <= 0) {
        return 0;
    }
    figure_id fid = d.queue[d.queue_head];
    d.queue[d.queue_head] = 0;
    d.queue_head = (d.queue_head + 1) % FERRY_QUEUE_CAPACITY;
    d.queue_count--;
    return fid;
}

void building_ferry::queue_release_waiting() {
    // OG quirk: loop vs shrinking size releases about half — keep that behaviour.
    while (queue_size() > 0) {
        const int before = queue_size();
        for (int i = 0; i < before; i++) {
            figure_id fid = queue_pop();
            figure *f = figure_get(fid);
            if (!f || !f->is_alive()) {
                continue;
            }
            if (f->action_state == ACTION_7_CARTPUSHER_WAIT_FOR_FERRY) {
                f->action_state = f->action_state_before_attack;
                f->route_remove();
            }
        }
        break;
    }
    auto &d = runtime_data();
    d.queue_head = 0;
    d.queue_count = 0;
    memset(d.queue, 0, sizeof(d.queue));
}

int building_ferry::route_find_partner_on_path(const figure &f, building *ferry) {
    building *partner = map_routing_ferry_partner(ferry);
    if (!partner || f.routing_path_id <= 0) {
        return 2;
    }

    int grid_offset = f.tile.grid_offset();
    for (int i = f.routing_path_current_tile; i < f.routing_path_length; i++) {
        if (map_building_at(grid_offset) == partner->id) {
            if (ferry->num_workers > 0 && partner->num_workers > 0) {
                return 1;
            }
            return 0;
        }
        int dir = figure_route_get_direction(f.routing_path_id, i);
        if (dir < 0 || dir > 7) {
            break;
        }
        grid_offset += map_grid_direction_delta(dir);
        if (!map_grid_is_valid_offset(grid_offset)) {
            break;
        }
    }
    return 2;
}

bool building_ferry::try_enter_ferry(figure &f) {
    if (f.action_state == ACTION_7_CARTPUSHER_WAIT_FOR_FERRY) {
        f.direction = DIR_FIGURE_NONE;
        return true;
    }

    building *partner = map_routing_ferry_partner(&base);
    const int found = route_find_partner_on_path(f, &base);
    if (found == 1 && partner) {
        if (!queue_is_full() && num_workers() > 0 && partner->num_workers > 0) {
            if (!queue_push(f.id)) {
                f.route_remove();
                f.direction = DIR_FIGURE_REROUTE;
                f.action_state = ACTION_8_RECALCULATE;
                return true;
            }
            f.action_state_before_attack = (uint8_t)f.action_state;
            f.action_state = ACTION_7_CARTPUSHER_WAIT_FOR_FERRY;
            f.wait_ticks = 0;
            f.route_remove();
            f.direction = DIR_FIGURE_NONE;
            if (figure *boat = base.get_figure(BUILDING_SLOT_BOAT)) {
                boat->wait_ticks = 0;
            }
            return true;
        }

        f.route_remove();
        tile2i road = map_closest_road_within_radius(base.tile, base.size, 2);
        if (road.valid()) {
            f.map_figure_remove();
            f.tile = road;
            f.previous_tile = road;
            f.map_figure_add();
        }
        f.action_state = ACTION_8_RECALCULATE;
        f.direction = DIR_FIGURE_REROUTE;
        return true;
    }

    if (found == 2) {
        // Partner not on remaining path: keep walking (up to a few tiles in OG).
        return false;
    }

    f.direction = DIR_FIGURE_REROUTE;
    return true;
}

bool figure_is_queued_for_ferry(figure_id fid) {
    figure *f = figure_get(fid);
    if (!f || !f->is_alive()) {
        return true;
    }
    if (f->action_state == ACTION_6_CARTPUSHER_ON_FERRY
        || f->action_state != ACTION_7_CARTPUSHER_WAIT_FOR_FERRY) {
        return true;
    }

    bool found = false;
    buildings_valid_do([&](building &b) {
        if (found || b.type != BUILDING_FERRY) {
            return;
        }
        auto *ferry = b.dcast_ferry();
        if (ferry && ferry->queue_contains(fid)) {
            found = true;
        }
    });
    return found;
}

void building_ferry::spawn_figure() {
    check_labor_problem();

    if (!has_road_access()) {
        return;
    }

    common_spawn_labor_seeker(current_params().min_houses_coverage);

    if (num_workers() <= 0) {
        queue_release_waiting();
    }

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
}
