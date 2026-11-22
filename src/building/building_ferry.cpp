#include "building/building_ferry.h"
#include "grid/orientation.h"

#include "building/construction/build_planner.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "city/city_labor.h"
#include "city/city_warnings.h"
#include "figure/route.h"
#include "figuretype/figure_cartpusher.h"
#include "figuretype/figure_ferry_boat.h"
#include "game/game_config.h"
#include "game/game_events.h"
#include "game/undo.h"
#include "graphics/image.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/grid.h"
#include "grid/image.h"
#include "grid/road_access.h"
#include "grid/routing/routing.h"
#include "grid/routing/routing_terrain.h"
#include "grid/sprite.h"
#include "grid/terrain.h"
#include "grid/water.h"
#include "js/js_game.h"

#include <algorithm>
#include <array>
#include <cstdlib>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_ferry);
BUILDING_RUNTIME_DATA_IMPL(building_ferry)

namespace {

    enum e_ferry_site { FERRY_SITE_SIZE = 2, FERRY_PATH_MAX = 500 };

    bool ferry_remake() {
        return game_features::gameplay_change_ferry_remake.to_bool();
    }

    int ferry_opposite(int orientation) {
        return (orientation + 2) % 4;
    }

    building_ferry* ferry_of(building* b) {
        return (b && b->is_valid()) ? b->dcast_ferry() : nullptr;
    }

    building_ferry* ferry_landing_at(tile2i tile) {
        building* b = building_at(tile);
        building_ferry* ferry = ferry_of(b);
        return (ferry && b->tile == tile) ? ferry : nullptr;
    }

    tile2i ferry_site_top_left(tile2i end) {
        switch (map_view_orientation()) {
        case DIR_2_BOTTOM_RIGHT:
            return end.shifted(-FERRY_SITE_SIZE + 1, 0);
        case DIR_4_BOTTOM_LEFT:
            return end.shifted(-FERRY_SITE_SIZE + 1, -FERRY_SITE_SIZE + 1);
        case DIR_6_TOP_LEFT:
            return end.shifted(0, -FERRY_SITE_SIZE + 1);
        default:
            return end;
        }
    }

    tile2i ferry_fan_tile(tile2i from, int orientation, int along, int side) {
        switch (orientation) {
        case 0:
            return from.shifted(side, -along);
        case 1:
            return from.shifted(along, side);
        case 2:
            return from.shifted(side, along);
        default:
            return from.shifted(-along, side);
        }
    }

    bool ferry_in_fan(tile2i from, int orientation, tile2i to, int route_length) {
        const int dx = to.x() - from.x();
        const int dy = to.y() - from.y();
        int along;
        int side;
        switch (orientation) {
        case 0:
            along = -dy;
            side = dx;
            break;
        case 1:
            along = dx;
            side = dy;
            break;
        case 2:
            along = dy;
            side = dx;
            break;
        default:
            along = -dx;
            side = dy;
            break;
        }
        const int half_width = std::min<int>(along, building_ferry::current_params().route_fan_half_width);
        return along >= 0 && along <= route_length * 2 && std::abs(side) <= half_width;
    }

    int ferry_route_measure(tile2i site, int orientation) {
        const int max_length = building_ferry::current_params().route_max_length;
        const int step = map_grid_direction_delta(orientation * 2);
        int offset = site.grid_offset();
        int length = 1;
        int water_tiles = 0;
        while (true) {
            const int ahead = offset + 2 * step;
            offset += step;
            length++;
            if (!map_grid_is_valid_offset(ahead) || !map_grid_is_valid_offset(offset + step)) {
                return max_length;
            }
            if (map_terrain_is(ahead, TERRAIN_TREE)) {
                break;
            }
            if (map_sprite_animation_at(offset + step) != 0) {
                break;
            }
            if (!map_terrain_is(ahead, TERRAIN_WATER)) {
                return max_length;
            }
            water_tiles++;
            if (water_tiles >= max_length) {
                break;
            }
        }
        return length;
    }

    bool ferry_water_path_to(tile2i to_site) {
        tile2i water;
        if (!map_water_tile_next_to(to_site, FERRY_SITE_SIZE, water)) {
            return false;
        }
        std::array<uint8_t, FERRY_PATH_MAX> path;
        return map_routing_get_path_on_water(path.data(), water, false) > 0;
    }

    bool ferry_water_distances_from(tile2i site) {
        tile2i water;
        if (!map_water_tile_next_to(site, FERRY_SITE_SIZE, water)) {
            return false;
        }
        map_routing_calculate_distances_water_boat(water);
        return true;
    }

    bool ferry_route_exists(tile2i site0, int direction0, tile2i site1, int direction1, int route_length) {
        if (direction0 != direction1 || !ferry_in_fan(site0, direction0, site1, route_length)) {
            return false;
        }
        return ferry_water_distances_from(site0) && ferry_water_path_to(site1);
    }

    bool ferry_route_to_first(tile2i site, int orientation, building_ferry& first) {
        const int first_orientation = first.base.orientation;
        return ferry_route_exists(site, orientation, first.tile(), ferry_opposite(first_orientation),
          ferry_route_measure(first.tile(), first_orientation));
    }

    bool ferry_first_site_ok(tile2i site, int orientation) {
        const int length = ferry_route_measure(site, orientation);
        const int facing = ferry_opposite(orientation);
        const int half_width_max = building_ferry::current_params().route_fan_half_width;
        if (!ferry_water_distances_from(site)) {
            return false;
        }
        for (int along = 0, half_width = 0; along <= length * 2; along++) {
            for (int side = -half_width; side <= half_width; side++) {
                const tile2i candidate = ferry_fan_tile(site, orientation, along, side);
                if (!map_grid_is_inside(candidate, 1)) {
                    continue;
                }
                building_ferry* landing = ferry_landing_at(candidate);
                if (landing && landing->linked_building_id() == building_ferry::FERRY_LINK_NONE) {
                    return true;
                }
                const shore_orientation shore = map_shore_determine_orientation(candidate, FERRY_SITE_SIZE, false);
                if (!shore.match || shore.orientation_absolute != facing) {
                    continue;
                }
                if (ferry_in_fan(candidate, facing, site, length) && ferry_water_path_to(candidate)) {
                    return true;
                }
            }
            half_width = std::min(half_width + 1, half_width_max);
        }
        return false;
    }

    void ferry_link(building_ferry& a, building_ferry& b) {
        a.set_linked_building_id(b.id());
        b.set_linked_building_id(a.id());
    }

    bool ferry_water_path_exists(building& from, building& to) {
        water_access_tiles begin = map_water_get_access_points(from, from.dcast()->get_orientation(), 1);
        water_access_tiles end = map_water_get_access_points(to, to.dcast()->get_orientation(), 1);

        const tile2i starts[] = {begin.point_a, begin.point_b};
        const tile2i ends[] = {end.point_a, end.point_b};
        std::array<uint8_t, FERRY_PATH_MAX> path_data;
        for (tile2i start : starts) {
            if (!start.valid()) {
                continue;
            }
            map_routing_calculate_distances_water_boat(start);
            for (tile2i dest : ends) {
                if (!dest.valid()) {
                    continue;
                }
                if (map_routing_get_path_on_water(path_data.data(), dest, false) > 0) {
                    return true;
                }
            }
        }
        return false;
    }

    building* ferry_remake_partner(building& b) {
        svector<building*, 64> ferries;
        buildings_get(ferries, BUILDING_FERRY);

        building* best = nullptr;
        int min_distance = 9999;
        tile2i home = b.tile;

        for (building* it : ferries) {
            if (!it || it->id == b.id) {
                continue;
            }

            const int dx = std::abs(home.x() - it->tile.x());
            const int dy = std::abs(home.y() - it->tile.y());
            if (dx > 4 && dy > 4) {
                continue;
            }

            if (!ferry_water_path_exists(*it, b)) {
                continue;
            }

            const int distance = (int)home.dist_sq(it->tile);
            if (distance < min_distance) {
                min_distance = distance;
                best = it;
            }
        }

        return best;
    }

    void ferry_mark_path(tile2i from, tile2i to) {
        std::array<uint8_t, FERRY_PATH_MAX> path_data;
        map_routing_calculate_distances_water_boat(from);
        int path_length = map_routing_get_path_on_water(path_data.data(), to, false);

        map_terrain_add(from.grid_offset(), TERRAIN_FERRY_ROUTE);
        map_terrain_add(to.grid_offset(), TERRAIN_FERRY_ROUTE);
        if (path_length > 0) {
            auto path = make_span(path_data.data(), path_length);

            int grid_offset = from.grid_offset();
            for (const auto& dir : path) {
                map_terrain_add(grid_offset, TERRAIN_FERRY_ROUTE);
                map_routing_adjust_tile_in_direction(dir, from, grid_offset);
            }
        }
    }

    void ferry_update_remake_routes() {
        svector<building*, 64> ferries;
        buildings_get(ferries, BUILDING_FERRY);

        for (auto f1 = ferries.begin(); f1 != ferries.end(); ++f1) {
            for (auto f2 = f1 + 1; f2 != ferries.end(); ++f2) {
                tile2i tile1 = (*f1)->tile;
                tile2i tile2 = (*f2)->tile;
                int dx = std::abs(tile1.x() - tile2.x());
                int dy = std::abs(tile1.y() - tile2.y());
                if (dx > 4 && dy > 4) {
                    continue;
                }

                water_access_tiles begin = map_water_get_access_points(**f1, (*f1)->dcast()->get_orientation(), 1);
                water_access_tiles end = map_water_get_access_points(**f2, (*f2)->dcast()->get_orientation(), 1);
                ferry_mark_path(begin.point_a, end.point_a);
                ferry_mark_path(begin.point_a, end.point_b);
                ferry_mark_path(begin.point_b, end.point_a);
                ferry_mark_path(begin.point_b, end.point_b);
            }
        }
    }

    void ferry_pair_unknown_links() {
        svector<building_ferry*, 64> unknown;
        buildings_valid_do([&](building& b) {
            building_ferry* ferry = b.dcast_ferry();
            if (ferry && ferry->linked_building_id() == building_ferry::FERRY_LINK_UNKNOWN) {
                unknown.push_back(ferry);
            }
        });

        for (size_t i = 0; i < unknown.size(); i++) {
            building_ferry& first = *unknown[i];
            if (first.linked_building_id() != building_ferry::FERRY_LINK_UNKNOWN) {
                continue;
            }
            for (size_t j = i + 1; j < unknown.size(); j++) {
                building_ferry& second = *unknown[j];
                if (second.linked_building_id() != building_ferry::FERRY_LINK_UNKNOWN) {
                    continue;
                }
                if (ferry_route_to_first(second.tile(), second.base.orientation, first)) {
                    ferry_link(first, second);
                    break;
                }
            }
            if (first.linked_building_id() == building_ferry::FERRY_LINK_UNKNOWN) {
                first.set_linked_building_id(building_ferry::FERRY_LINK_NONE);
            }
        }
    }

} // namespace

static int __ferry_partner_id(int bid) {
    building_ferry* ferry = ferry_of(building_get(bid));
    building* partner = ferry ? ferry->partner() : nullptr;
    return partner ? partner->id : 0;
}
ANK_FUNCTION_1(__ferry_partner_id);

void building_ferry::on_create(int orientation) {
    base.orientation = orientation;
    auto& d = runtime_data();
    d.queue_head = 0;
    d.queue_count = 0;
    d.linked_building_id = FERRY_LINK_UNKNOWN;
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
    map_building_tiles_add(id(), tile(), size(), img_id, TERRAIN_BUILDING | TERRAIN_ROAD | TERRAIN_FERRY_ROUTE);
}

void building_ferry::update_map_orientation(int orientation) {
    int image_offset = map_view_relative_orientation(base.orientation);
    int image_id = base_img() + image_offset;
    map_water_add_building(id(), tile(), size(), image_id);
}

void building_ferry::on_destroy() {
    queue_release_waiting();
    if (linked_building_id() > 0) {
        if (building_ferry* other = building_get(linked_building_id())->dcast_ferry()) {
            other->set_linked_building_id(FERRY_LINK_NONE);
        }
    }
    building_impl::on_destroy();
}

bool building_ferry::draw_ornaments_and_animations_height(painter& ctx, vec2i point, tile2i tile, color color_mask) {
    return true;
}

void building_ferry::bind_dynamic(io_buffer *iob, size_t verrsion) {
    auto& d = runtime_data();
    uint8_t link_stored = d.linked_building_id != FERRY_LINK_UNKNOWN;
    iob->bind____skip(85);
    iob->bind(BIND_SIGNATURE_UINT8, &link_stored);
    iob->bind(BIND_SIGNATURE_INT16, &d.linked_building_id);
    if (!link_stored) {
        d.linked_building_id = FERRY_LINK_UNKNOWN;
    }
    iob->bind(BIND_SIGNATURE_UINT8, &base.orientation);
    iob->bind(BIND_SIGNATURE_INT32, &base.tiles[0]);
    iob->bind(BIND_SIGNATURE_INT32, &base.tiles[1]);
}

building* building_ferry::partner() {
    if (ferry_remake()) {
        return ferry_remake_partner(base);
    }
    if (linked_building_id() <= 0) {
        return nullptr;
    }
    building* other = building_get(linked_building_id());
    return ferry_of(other) ? other : nullptr;
}

void building_ferry::update_routes() {
    foreach_river_tile([](int offset) {
        if (map_terrain_is(offset, TERRAIN_WATER) && map_terrain_is(offset, TERRAIN_FERRY_ROUTE)
            && !map_terrain_is(offset, TERRAIN_BUILDING)) {
            map_terrain_remove(offset, TERRAIN_FERRY_ROUTE);
        }
    });

    if (ferry_remake()) {
        ferry_update_remake_routes();
        return;
    }

    ferry_pair_unknown_links();
    buildings_valid_do([](building& b) {
        building_ferry* ferry = b.dcast_ferry();
        building* other = ferry ? ferry->partner() : nullptr;
        tile2i from;
        tile2i to;
        if (!other || !map_water_tile_next_to(b.tile, b.size, from)
            || !map_water_tile_next_to(other->tile, other->size, to)) {
            return;
        }
        ferry_mark_path(from, to);
    });
    map_routing_update_land_citizen();
}

void building_ferry::placement_cancel(build_planner& p) {
    if (p.ferry_placement == FERRY_PLACEMENT_FIRST_PLACED) {
        building* first = building_get(p.ferry_first);
        if (ferry_of(first)) {
            first->state = BUILDING_STATE_DELETED_BY_PLAYER;
        }
    }
    p.ferry_placement = FERRY_PLACEMENT_NONE;
}

int building_ferry::preview::can_place(build_planner& p, tile2i start, tile2i end, int state) const {
    state = building_planer_renderer::can_place(p, start, end, state);
    if (ferry_remake()) {
        return state;
    }

    const tile2i site = ferry_site_top_left(end);
    if (building_ferry* hovered = ferry_landing_at(site)) {
        if (hovered->linked_building_id() != FERRY_LINK_NONE) {
            return state;
        }
        if (p.ferry_placement == FERRY_PLACEMENT_NONE) {
            p.ferry_placement = FERRY_PLACEMENT_FIRST_EXISTING;
            p.ferry_first = hovered->id();
            p.set_warning("");
            return CAN_NOT_PLACE;
        }
        building_ferry* first = ferry_of(building_get(p.ferry_first));
        if (p.ferry_placement == FERRY_PLACEMENT_FIRST_PLACED && first && first != hovered
            && ferry_route_to_first(site, hovered->base.orientation, *first)) {
            ferry_link(*hovered, *first);
            p.ferry_placement = FERRY_PLACEMENT_NONE;
            update_routes();
            p.set_warning("");
            return CAN_NOT_PLACE;
        }
        return state;
    }

    const shore_orientation shore = map_shore_determine_orientation(site, FERRY_SITE_SIZE, false);
    if (!shore.match) {
        return state;
    }

    bool site_ok = false;
    if (p.ferry_placement == FERRY_PLACEMENT_NONE) {
        site_ok = ferry_first_site_ok(site, shore.orientation_absolute);
    } else if (building_ferry* first = ferry_of(building_get(p.ferry_first))) {
        site_ok = ferry_route_to_first(site, shore.orientation_absolute, *first);
    }

    if (!site_ok) {
        p.set_warning("#no_valid_spot_for_ferry_landing");
        return CAN_NOT_PLACE;
    }
    return state;
}

int building_ferry::preview::construction_place(build_planner& p, tile2i start, tile2i end, int orientation,
  int variant) const {
    const int placed = building_planer_renderer::construction_place(p, start, end, orientation, variant);
    building_ferry* ferry = ferry_of(p.last_created_building);
    if (!placed || !ferry || ferry_remake()) {
        return placed;
    }

    if (p.ferry_placement == FERRY_PLACEMENT_NONE) {
        ferry->set_linked_building_id(FERRY_LINK_PENDING);
        p.ferry_first = ferry->id();
        p.ferry_placement = FERRY_PLACEMENT_FIRST_PLACED;
        events::emit(event_city_warning{"#place_other_ferry_landing"});
        return placed;
    }

    building* first = building_get(p.ferry_first);
    if (building_ferry* first_ferry = ferry_of(first)) {
        ferry_link(*ferry, *first_ferry);
        if (p.ferry_placement == FERRY_PLACEMENT_FIRST_PLACED) {
            game_undo_add_building(first);
        }
    }
    p.ferry_placement = FERRY_PLACEMENT_NONE;
    return placed;
}

int building_ferry::preview::finalize_cost(build_planner& p, int cost) const {
    if (!ferry_remake() && p.ferry_placement == FERRY_PLACEMENT_NONE) {
        return 0;
    }
    return cost;
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
            if (f->action_state == f->dcast()->ferry_wait_action()) {
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
    building* partner = ferry->dcast_ferry() ? ferry->dcast_ferry()->partner() : nullptr;
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
    if (f.action_state == f.dcast()->ferry_wait_action()) {
        f.direction = DIR_FIGURE_NONE;
        return true;
    }

    building* other = partner();
    const int found = route_find_partner_on_path(f, &base);
    if (found == 1 && other) {
        if (!queue_is_full() && num_workers() > 0 && other->num_workers > 0) {
            if (!queue_push(f.id)) {
                f.route_remove();
                f.direction = DIR_FIGURE_REROUTE;
                f.action_state = f.dcast()->ferry_reroute_action();
                return true;
            }
            f.action_state_before_attack = (uint8_t)f.action_state;
            f.action_state = f.dcast()->ferry_wait_action();
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
        f.action_state = f.dcast()->ferry_reroute_action();
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
    if (f->action_state == f->dcast()->ferry_ride_action()
        || f->action_state != f->dcast()->ferry_wait_action()) {
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
        return;
    }

    // OG spawn_ferry: need a partner route before the worker-% delay gate.
    if (!partner()) {
        return;
    }

    // OG delays: 100%→3, 75%→7, 50%→15, 25%→29, 1%→-1 (immediate).
    const int pct = worker_percentage();
    int delay;
    if (pct >= 100) {
        delay = 3;
    } else if (pct >= 75) {
        delay = 7;
    } else if (pct >= 50) {
        delay = 15;
    } else if (pct >= 25) {
        delay = 29;
    } else if (pct >= 1) {
        delay = -1;
    } else {
        return;
    }

    const int days = ++base.figure_spawn_delay;
    if (days <= delay) {
        return;
    }
    base.figure_spawn_delay = 0;

    if (base.get_figure_id(BUILDING_SLOT_BOAT) > 0) {
        return;
    }

    tile2i dock = dock_tile();
    if (!dock.valid() || !map_terrain_is(dock, TERRAIN_WATER)) {
        return;
    }

    figure *f = figure_create(FIGURE_FERRY_BOAT, dock, DIR_4_BOTTOM_LEFT);
    if (!f) {
        return;
    }
    f->action_state = ACTION_0_FERRY_BOAT_CREATED;
    f->set_home(id());
    base.set_figure(BUILDING_SLOT_BOAT, f);
}
