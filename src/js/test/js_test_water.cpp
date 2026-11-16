#include "js/test/js_test_common.h"

#include "building/building.h"
#include "building/building_delivery_path.h"
#include "building/building_dock.h"
#include "building/building_ferry.h"
#include "building/building_fishing_wharf.h"
#include "building/building_shipyard.h"
#include "building/building_storage_yard.h"
#include "city/city.h"
#include "city/city_figures.h"
#include "city/object_info.h"
#include "core/xstring.h"
#include "empire/trader_handler.h"
#include "figure/figure.h"
#include "figure/figure_impl.h"
#include "figure/formation.h"
#include "figure/route.h"
#include "figuretype/figure_docker.h"
#include "figuretype/figure_ferry_boat.h"
#include "figuretype/figure_flotsam.h"
#include "figuretype/figure_plagued_citizen.h"
#include "game/resource.h"
#include "grid/grid.h"
#include "grid/road_access.h"
#include "grid/routing/routing.h"
#include "grid/terrain.h"
#include "grid/water.h"
#include "scenario/scenario.h"

#include <array>

static void __test_shipyard_set_water_access_to_figure(int bid, int fid) {
    building* b = building_get(bid);
    figure* f = figure_get(fid);
    auto* shipyard = b ? b->dcast_shipyard() : nullptr;
    if (shipyard && f && f->is_alive()) {
        shipyard->set_water_access_tiles({f->tile, f->tile});
    }
}
ANK_FUNCTION_2(__test_shipyard_set_water_access_to_figure);

static void __test_set_scenario_river_points(int entry_x, int entry_y, int exit_x, int exit_y) {
    g_scenario.river_entry_point = (entry_x < 0 || entry_y < 0) ? tile2i::invalid : tile2i(entry_x, entry_y);
    g_scenario.river_exit_point = (exit_x < 0 || exit_y < 0) ? tile2i::invalid : tile2i(exit_x, exit_y);
}
ANK_FUNCTION_4(__test_set_scenario_river_points);

static void __test_make_deep_water(int x, int y) {
    map_terrain_add(tile2i(x, y), TERRAIN_WATER | TERRAIN_DEEPWATER);
}
ANK_FUNCTION_2(__test_make_deep_water);

static int __test_flotsam_spawn(int kind) {
    return figure_flotsam::spawn(kind);
}
ANK_FUNCTION_1(__test_flotsam_spawn);

static void __test_flotsam_spawn_update_day() {
    figure_flotsam::spawn_update_day();
}
ANK_FUNCTION(__test_flotsam_spawn_update_day);

static int __test_docker_haul_amount() {
    return figure_docker::haul_amount();
}
ANK_FUNCTION(__test_docker_haul_amount);

static int __test_docker_import_loads(int yard_bid, int resource, int max_amount) {
    building* b = building_get(yard_bid);
    auto* yard = b ? b->dcast_storage_yard() : nullptr;
    if (!yard || !b->is_valid() || resource <= RESOURCE_NONE || resource >= RESOURCES_MAX) {
        return -1;
    }
    return figure_docker::import_loads(yard, (e_resource)resource, max_amount);
}
ANK_FUNCTION_3(__test_docker_import_loads);

static int __test_shipyard_queue_ship(int bid, int fid) {
    return building_shipyard_queue_ship((figure_id)fid, (building_id)bid) ? 1 : 0;
}
ANK_FUNCTION_2(__test_shipyard_queue_ship);

static int __test_shipyard_is_reparing(int bid) {
    building_shipyard* shipyard = building_get(bid)->dcast_shipyard();
    return (shipyard && shipyard->runtime_data().reparing) ? 1 : 0;
}
ANK_FUNCTION_1(__test_shipyard_is_reparing);

static int __test_shipyard_repair_fid(int bid) {
    building_shipyard* shipyard = building_get(bid)->dcast_shipyard();
    return shipyard ? (int)shipyard->runtime_data().repair_fid : 0;
}
ANK_FUNCTION_1(__test_shipyard_repair_fid);

static void __test_make_floodplain_water(int x, int y) {
    map_terrain_add(tile2i(x, y), TERRAIN_WATER | TERRAIN_FLOODPLAIN);
}
ANK_FUNCTION_2(__test_make_floodplain_water);

static void __test_clear_scenario_fishing_points() {
    g_scenario.fishing_points.assign(MAX_FISH_POINTS, tile2i::invalid);
}
ANK_FUNCTION(__test_clear_scenario_fishing_points);

static void __test_set_scenario_fishing_point(int index, int x, int y) {
    if (index < 0 || index >= MAX_FISH_POINTS) {
        return;
    }
    if ((int)g_scenario.fishing_points.size() <= index) {
        g_scenario.fishing_points.resize(index + 1, tile2i::invalid);
    }
    g_scenario.fishing_points[index] = tile2i(x, y);
}
ANK_FUNCTION_3(__test_set_scenario_fishing_point);

static void __test_fishing_points_create() {
    g_city.fishing_points.create();
}
ANK_FUNCTION(__test_fishing_points_create);

static void __test_fishing_points_clear() {
    g_city.fishing_points.clear();
}
ANK_FUNCTION(__test_fishing_points_clear);

static int __test_fishing_wharf_spawn_figure(int bid) {
    building* b = building_get(bid);
    auto* wharf = (b && b->is_valid()) ? b->dcast_fishing_wharf() : nullptr;
    if (!wharf) {
        return -1;
    }
    b->has_road_access = true;
    if (!b->road_access.valid()) {
        b->road_access = b->tile;
    }
    if (b->road_network_id <= 0) {
        b->road_network_id = 1;
    }
    if (b->distance_from_entry <= 0) {
        b->distance_from_entry = 1;
    }
    const int before = wharf->get_figures_number(FIGURE_CART_PUSHER);
    wharf->spawn_figure();
    return wharf->get_figures_number(FIGURE_CART_PUSHER) - before;
}
ANK_FUNCTION_1(__test_fishing_wharf_spawn_figure);

static int __test_fishing_wharf_fish_caught(int bid) {
    building* b = building_get(bid);
    auto* wharf = (b && b->is_valid()) ? b->dcast_fishing_wharf() : nullptr;
    return wharf ? wharf->runtime_data().fish_caught : -1;
}
ANK_FUNCTION_1(__test_fishing_wharf_fish_caught);

static void __test_fishing_wharf_set_fish_caught(int bid, int value) {
    building* b = building_get(bid);
    auto* wharf = (b && b->is_valid()) ? b->dcast_fishing_wharf() : nullptr;
    if (!wharf) {
        return;
    }
    wharf->runtime_data().fish_caught = (uint8_t)value;
}
ANK_FUNCTION_2(__test_fishing_wharf_set_fish_caught);

static int __test_ferry_boat_board_passenger(int boat_fid, int passenger_fid) {
    figure* boat_f = figure_get(boat_fid);
    figure* p = figure_get(passenger_fid);
    auto* boat = boat_f ? boat_f->dcast_ferry_boat() : nullptr;
    if (!boat || !boat->is_alive() || !p || !p->is_alive() || !p->dcast()) {
        return 0;
    }
    auto& d = boat->runtime_data();
    for (int i = 0; i < figure_ferry_boat::PASSENGER_SLOTS; i++) {
        if (d.passengers[i] > 0) {
            continue;
        }
        d.passengers[i] = (figure_id)passenger_fid;
        p->action_state = p->dcast()->ferry_ride_action();
        p->main_image_id = 0;
        p->cart_image_id = 0;
        p->set_flag(e_figure_flag_invisible, true);
        p->route_remove();
        p->map_figure_remove();
        return 1;
    }
    return 0;
}
ANK_FUNCTION_2(__test_ferry_boat_board_passenger);

static int __test_ferry_boat_slowness_step(int boat_fid) {
    figure* boat_f = figure_get(boat_fid);
    auto* boat = boat_f ? boat_f->dcast_ferry_boat() : nullptr;
    if (!boat || !boat->is_alive()) {
        return -1;
    }
    building* home = boat->home();
    if (!home || !home->is_valid()) {
        return -1;
    }
    boat->move_with_staff_slowness(home);
    return boat_f->wait_ticks;
}
ANK_FUNCTION_1(__test_ferry_boat_slowness_step);

static int __test_ferry_boat_passenger_count(int boat_fid) {
    figure* boat_f = figure_get(boat_fid);
    auto* boat = boat_f ? boat_f->dcast_ferry_boat() : nullptr;
    if (!boat) {
        return -1;
    }
    return boat->passenger_count();
}
ANK_FUNCTION_1(__test_ferry_boat_passenger_count);

static void __test_ferry_boat_sink(int boat_fid) {
    figure* boat_f = figure_get(boat_fid);
    auto* boat = boat_f ? boat_f->dcast_ferry_boat() : nullptr;
    if (!boat || (!boat_f->is_alive() && boat_f->state != FIGURE_STATE_DYING)) {
        return;
    }
    boat->sink();
}
ANK_FUNCTION_1(__test_ferry_boat_sink);

int __test_shipyard_find_best_dock(int fid) {
    return building_shipyard_find_best_dock((figure_id)fid);
}
ANK_FUNCTION_1(__test_shipyard_find_best_dock)

// Returns 1 if ferry_water_path_exists between two ferries (same check as partner search).
static int __test_ferry_water_path(int a, int b) {
    building* ba = building_get(a);
    building* bb = building_get(b);
    if (!ba || !bb || ba->type != BUILDING_FERRY || bb->type != BUILDING_FERRY) {
        return -1;
    }
    water_access_tiles begin = map_water_get_access_points(*ba, ba->dcast()->get_orientation(), 1);
    water_access_tiles end = map_water_get_access_points(*bb, bb->dcast()->get_orientation(), 1);
    const tile2i starts[] = {begin.point_a, begin.point_b};
    const tile2i ends[] = {end.point_a, end.point_b};
    std::array<uint8_t, 500> path_data;
    for (tile2i start : starts) {
        if (!start.valid()) {
            continue;
        }
        map_routing_calculate_distances_water_boat(start);
        for (tile2i dest : ends) {
            if (!dest.valid()) {
                continue;
            }
            const int len = map_routing_get_path_on_water(path_data.data(), dest, false);
            if (len > 0) {
                return len;
            }
        }
    }
    // Encode access-point water flags for diagnosis: bit0..3 = a0,a1,b0,b1 on water.
    int flags = 0;
    if (begin.point_a.valid() && map_terrain_is(begin.point_a, TERRAIN_WATER))
        flags |= 1;
    if (begin.point_b.valid() && map_terrain_is(begin.point_b, TERRAIN_WATER))
        flags |= 2;
    if (end.point_a.valid() && map_terrain_is(end.point_a, TERRAIN_WATER))
        flags |= 4;
    if (end.point_b.valid() && map_terrain_is(end.point_b, TERRAIN_WATER))
        flags |= 8;
    return -100 - flags;
}
ANK_FUNCTION_2(__test_ferry_water_path);

static building_dock* dock_from_bid(int bid) {
    building* b = building_get(bid);
    return b ? b->dcast_dock() : nullptr;
}

/** Test/helper: unweighted any-match count for up to 3 partner goods (0 = unused). */
static void __test_fill_resource_list(resource_list& out, int r0, int r1, int r2) {
    const int rs[3] = {r0, r1, r2};
    for (int r : rs) {
        if (r > RESOURCE_NONE && r < RESOURCES_MAX) {
            out[(e_resource)r] = 1;
        }
    }
}

int __test_dock_match_score(int bid, int r0, int r1, int r2) {
    auto b = dock_from_bid(bid);
    if (!b) {
        return -1;
    }
    resource_list active;
    __test_fill_resource_list(active, r0, r1, r2);
    resource_list empty;
    return b->count_matching_goods(active, empty);
}
ANK_FUNCTION_4(__test_dock_match_score)

bool __test_dock_any_match(int bid, int r0, int r1, int r2) {
    return __test_dock_match_score(bid, r0, r1, r2) > 0;
}
ANK_FUNCTION_4(__test_dock_any_match)

/** Test: weighted score — imports ×2, exports ×1 (up to 3 each; 0 = unused). */
int __test_dock_trade_score(int bid, int i0, int i1, int i2, int e0, int e1, int e2) {
    auto b = dock_from_bid(bid);
    if (!b) {
        return -1;
    }
    resource_list imports;
    resource_list exports;
    __test_fill_resource_list(imports, i0, i1, i2);
    __test_fill_resource_list(exports, e0, e1, e2);
    return b->trade_match_score(imports, exports);
}
ANK_FUNCTION_7(__test_dock_trade_score)

int __test_dock_yard_proximity(int bid) {
    auto b = dock_from_bid(bid);
    return b ? b->yard_proximity_cost() : -1;
}
ANK_FUNCTION_1(__test_dock_yard_proximity)

int __test_dock_match_score_for_ship(int bid, int ship_id) {
    auto b = dock_from_bid(bid);
    return b ? b->match_score_for_ship(ship_id) : -1;
}
ANK_FUNCTION_2(__test_dock_match_score_for_ship)

int __test_map_get_free_dock(int ship_id) {
    return map_get_free_destination_dock(ship_id).bid;
}
ANK_FUNCTION_1(__test_map_get_free_dock)

#include "city/city_floods.h"
#include "core/random.h"

static void __test_random_set_state(int iv1, int iv2) {
    random_TEMP_SET_DEBUG((uint32_t)iv1, (uint32_t)iv2);
}
ANK_FUNCTION_2(__test_random_set_state);

static int __test_random_iv1() {
    return (int)random_data_struct()->iv1;
}
ANK_FUNCTION(__test_random_iv1);

static void __test_random_generate_next() {
    random_generate_next();
}
ANK_FUNCTION(__test_random_generate_next);

static int __test_random_1_3bit() {
    return random_data_struct()->random1_3bit;
}
ANK_FUNCTION(__test_random_1_3bit);

static int __test_random_1_15bit() {
    return random_data_struct()->random1_15bit;
}
ANK_FUNCTION(__test_random_1_15bit);

static void __test_floods_set_quality(int initial, int next) {
    g_floods.quality_initial = initial;
    g_floods.quality_next = next;
}
ANK_FUNCTION_2(__test_floods_set_quality);

static int __test_floods_quality_next() {
    return g_floods.quality_next;
}
ANK_FUNCTION(__test_floods_quality_next);

static void __test_floods_update_next_params() {
    g_floods.update_next_flood_params();
}
ANK_FUNCTION(__test_floods_update_next_params);

// Queue fid at a ferry landing the way building_ferry::try_enter_ferry does.
static int __test_ferry_landing_enqueue(int bid, int fid) {
    building* b = building_get(bid);
    auto* landing = b ? b->dcast_ferry() : nullptr;
    figure* f = figure_get(fid);
    if (!landing || !f || !f->is_alive() || !landing->queue_push((figure_id)fid)) {
        return 0;
    }
    f->action_state_before_attack = (uint8_t)f->action_state;
    f->action_state = f->dcast()->ferry_wait_action();
    f->route_remove();
    return 1;
}
ANK_FUNCTION_2(__test_ferry_landing_enqueue);

static int __test_ferry_boat_load(int boat_fid, int bid) {
    figure* boat_f = figure_get(boat_fid);
    auto* boat = boat_f ? boat_f->dcast_ferry_boat() : nullptr;
    building* b = building_get(bid);
    auto* landing = b ? b->dcast_ferry() : nullptr;
    if (!boat || !landing) {
        return -1;
    }
    boat->load_passengers(landing, figure_ferry_boat::PASSENGER_SLOTS);
    return boat->passenger_count();
}
ANK_FUNCTION_2(__test_ferry_boat_load);

static void __test_ferry_boat_unload(int boat_fid, int bid) {
    figure* boat_f = figure_get(boat_fid);
    auto* boat = boat_f ? boat_f->dcast_ferry_boat() : nullptr;
    building* b = building_get(bid);
    auto* landing = b ? b->dcast_ferry() : nullptr;
    if (boat && landing) {
        boat->unload_passengers(landing);
    }
}
ANK_FUNCTION_2(__test_ferry_boat_unload);
