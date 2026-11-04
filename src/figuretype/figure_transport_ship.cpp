#include "figure_transport_ship.h"

#include "building/building_shipyard.h"
#include "building/building_transport_wharf.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "city/city_message.h"
#include "core/calc.h"
#include "figure/formation.h"
#include "figure/formation_batalion.h"
#include "figure/route.h"
#include "figuretype/figure_enemy_transport.h"
#include "figuretype/figure_enemy_warship.h"
#include "figuretype/figure_shipwreck.h"
#include "figuretype/figure_soldier.h"
#include "grid/terrain.h"
#include "grid/water.h"
#include "graphics/window.h"
#include "js/js_game.h"
#include "scenario/map.h"
#include "window/window_city_transport.h"

#include <algorithm>
#include <cmath>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_transport_ship);

namespace {

bool transport_land_ok(tile2i land) {
    if (!land.valid()) {
        return false;
    }
    if (map_terrain_is(land, TERRAIN_WATER | TERRAIN_DEEPWATER)) {
        return false;
    }
    if (map_terrain_is(land, TERRAIN_BUILDING | TERRAIN_WALL | TERRAIN_ROCK | TERRAIN_ELEVATION)) {
        return false;
    }
    return true;
}

bool transport_is_navigable_water(tile2i tile) {
    return tile.valid()
        && map_terrain_is(tile, TERRAIN_WATER | TERRAIN_DEEPWATER)
        && !map_terrain_is(tile, TERRAIN_BUILDING);
}

bool transport_is_enemy_ship(figure *f) {
    if (!f || !f->is_alive()) {
        return false;
    }
    if (smart_cast<figure_enemy_warship>(f) || smart_cast<figure_enemy_transport>(f)) {
        return true;
    }
    return f->is_enemy()
        && (f->allow_move_type == EMOVE_WATER || f->allow_move_type == EMOVE_DEEPWATER);
}

bool transport_formation_already_embarked(int formation_id, int except_ship_id) {
    for (int i = 1; i < MAX_FIGURES; i++) {
        figure *f = figure_get(i);
        if (!f || !f->is_alive() || f->id == except_ship_id) {
            continue;
        }
        figure_transport_ship *ship = smart_cast<figure_transport_ship>(f);
        if (ship && ship->has_troops() && ship->transported_formation() == formation_id) {
            return true;
        }
    }
    return false;
}

// Walk from `from` toward `to`; keep the farthest open water tile on that line.
int transport_farthest_water_on_line(tile2i from, tile2i to, tile2i &out) {
    if (!from.valid()) {
        return -1;
    }
    int dx = to.x() - from.x();
    int dy = to.y() - from.y();
    int steps = std::max(std::abs(dx), std::abs(dy));
    if (steps <= 0) {
        if (transport_is_navigable_water(from)) {
            out = from;
            return 0;
        }
        return -1;
    }

    int best = -1;
    tile2i best_tile = tile2i::invalid;
    for (int i = 1; i <= steps; i++) {
        int x = from.x() + (dx * i) / steps;
        int y = from.y() + (dy * i) / steps;
        tile2i t(x, y);
        if (!transport_is_navigable_water(t)) {
            break;
        }
        best = i;
        best_tile = t;
    }
    if (best < 0) {
        return -1;
    }
    out = best_tile;
    return best;
}

} // namespace

water_dest map_water_get_wharf_for_new_transport_ship(figure &boat) {
    building_transport_wharf *wharf = building_first_ex<building_transport_wharf>([&boat](building_transport_wharf *w) {
        int wharf_boat_id = w->get_figure_id(BUILDING_SLOT_BOAT);
        return !wharf_boat_id || wharf_boat_id == boat.id;
    });

    if (!wharf) {
        return { false, 0 };
    }

    tile2i dock_tile(wharf->base.tiles[0]);
    water_access_tiles access = wharf->get_water_access_tiles();
    if (access.point_a.valid()) {
        dock_tile = access.point_a;
    }
    return { dock_tile.valid(), wharf->id(), dock_tile };
}

void figure_transport_ship::on_create() {
    figure_impl::on_create();
    base.allow_move_type = EMOVE_WATER;
    auto &d = runtime_data();
    d.formation_id = 0;
    d.has_troops = 0;
    d.evade_mode = evade_waiting;
    d.phase = 0;
    d.landing_x = -1;
    d.landing_y = -1;
    d.disembark_x = -1;
    d.disembark_y = -1;
    d.embark_ticks = 0;
    d.request_event_id = -1;
    base.damage = 0;
}

void figure_transport_ship::on_destroy() {
    building_shipyard_leave_queue(id());
    building *b = home();
    if (b && b->id) {
        b->remove_figure_by_id(id());
    }
}

bool figure_transport_ship::has_troops() const {
    return runtime_data().has_troops != 0 && runtime_data().formation_id > 0;
}

int figure_transport_ship::transported_formation() const {
    return has_troops() ? runtime_data().formation_id : 0;
}

bool figure_transport_ship::can_embark() const {
    if (has_troops() || runtime_data().formation_id > 0) {
        return false;
    }
    const int state = action_state();
    if (state == ACTION_221_TRANSPORT_SHIP_GOING_TO_REQUEST
        || state == ACTION_222_TRANSPORT_SHIP_AWAY_ON_REQUEST
        || state == ACTION_223_TRANSPORT_SHIP_RETURNING_FROM_REQUEST
        || state == ACTION_211_TRANSPORT_SHIP_WAITING) {
        return false;
    }
    return true;
}

tile2i figure_transport_ship::find_shore_tile(tile2i water_tile) const {
    static const vec2i dirs[] = {
        {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}
    };
    for (const vec2i &dir : dirs) {
        tile2i land = water_tile.shifted(dir);
        if (transport_land_ok(land)) {
            return land;
        }
    }
    return tile2i::invalid;
}

bool figure_transport_ship::legion_ready_to_board(int formation_id) const {
    const formation *m = formation_get(formation_id);
    if (!m || !m->in_use || m->num_figures <= 0) {
        return false;
    }

    int ready = 0;
    int count = 0;
    for (int i = 0; i < formation::max_figures_count && m->figures[i]; i++) {
        figure *soldier = figure_get(m->figures[i]);
        if (!soldier || !soldier->is_alive()) {
            continue;
        }
        count++;
        // OG: direction == DIRECTION_AT_DESTINATION. Remake also accepts at-standard
        // next to the hull (soldiers already staged on the embark shore).
        if (soldier->direction == DIR_FIGURE_NONE
            || soldier->action_state == ACTION_4_SOLDIER_AT_STANDARD) {
            ready++;
        }
    }
    return count > 0 && ready == count;
}

void figure_transport_ship::board_legion(int formation_id) {
    // OG transport_legion_board: SOLDIER_ON_SHIP, drop from map, keep prior action.
    formation *m = formation_get(formation_id);
    if (!m || !m->in_use) {
        return;
    }

    int loaded = 0;
    for (int i = 0; i < formation::max_figures_count && m->figures[i]; i++) {
        figure *f = figure_get(m->figures[i]);
        if (!f || !f->is_alive() || f->action_state == FIGURE_ACTION_149_CORPSE) {
            continue;
        }
        f->alternative_location_index = 0;
        f->action_state_before_attack = f->action_state;
        f->action_state = ACTION_18_SOLDIER_ON_SHIP;
        f->route_remove();
        f->map_figure_remove();
        f->tile = base.tile;
        f->formation_at_rest = 0;
        f->allow_move_type = EMOVE_TERRAIN;
        f->set_flag(e_figure_flag_invisible, false);
        loaded++;
    }

    if (loaded <= 0) {
        runtime_data().formation_id = 0;
        runtime_data().has_troops = 0;
        runtime_data().phase = 0;
        return;
    }

    auto &d = runtime_data();
    d.formation_id = (int8_t)formation_id;
    d.has_troops = 1;
    d.phase = 2;
    m->ship_figure_id = (int16_t)id();
    m->is_halted = 1;
    m->is_at_fort = 0;
    m->tile = base.tile;
    m->standard_tile = base.tile;
}

bool figure_transport_ship::embark_formation(int formation_id) {
    // OG embark_legion_under_mouse: assign company, order it ashore near the ship,
    // sail to water by the company — board happens in GOING_TO_LEGION on arrival.
    if (!can_embark()) {
        return false;
    }

    formation *m = formation_get(formation_id);
    if (!m || !m->in_use || !m->own_batalion || m->num_figures <= 0 || m->in_distant_battle) {
        return false;
    }
    if (transport_formation_already_embarked(formation_id, id())) {
        return false;
    }

    // Prefer the hull tile when it is already water (wharf access may also set
    // TERRAIN_BUILDING there — still a valid embark berth for this ship).
    tile2i water = base.tile;
    const bool hull_on_water = water.valid()
        && map_terrain_is(water, TERRAIN_WATER | TERRAIN_DEEPWATER);
    if (!hull_on_water) {
        // Prefer water next to the company's tile.
        static const vec2i dirs[] = {
            {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}
        };
        water = tile2i::invalid;
        for (const vec2i &dir : dirs) {
            tile2i cand = m->tile.shifted(dir);
            if (transport_is_navigable_water(cand)) {
                water = cand;
                break;
            }
        }
        if (!water.valid()) {
            return false;
        }
    }

    // Prefer the company's current tile when it already borders embark water.
    // Skip formation_batalion_move_to when the legion is already staged ready —
    // re-pathing leaves AT_STANDARD and boarding would wait on soldier ticks.
    tile2i shore = tile2i::invalid;
    if (calc_maximum_distance(m->tile, water) == 1 && transport_land_ok(m->tile)) {
        shore = m->tile;
    } else {
        shore = find_shore_tile(water);
        if (!shore.valid()) {
            shore = m->tile;
        }
    }
    if (transport_land_ok(shore) && !legion_ready_to_board(formation_id)) {
        formation_batalion_move_to(m, shore);
    }

    auto &d = runtime_data();
    d.formation_id = (int8_t)formation_id;
    d.has_troops = 0;
    d.phase = 1;
    d.landing_x = -1;
    d.landing_y = -1;
    d.disembark_x = -1;
    d.disembark_y = -1;

    base.destination_tile = water;
    if (!base.source_tile.valid()) {
        base.source_tile = base.tile;
    }
    advance_action(ACTION_218_TRANSPORT_SHIP_GOING_TO_LEGION);
    route_remove();
    // Already on embark water: mark arrived so the next action can board.
    if (base.tile == water) {
        base.direction = DIR_FIGURE_NONE;
    }
    base.wait_ticks = 0;
    return true;
}

void figure_transport_ship::sail_to_landing(tile2i water_tile, tile2i land_order) {
    if (!has_troops() || !transport_is_navigable_water(water_tile)) {
        return;
    }

    // OG ship_landing_* is the land click; water is only the sail destination.
    tile2i order = land_order;
    if (!order.valid() || map_terrain_is(order, TERRAIN_WATER | TERRAIN_DEEPWATER)) {
        order = find_shore_tile(water_tile);
    }
    if (!order.valid()) {
        return;
    }

    auto &d = runtime_data();
    d.landing_x = order.x();
    d.landing_y = order.y();
    d.disembark_x = -1;
    d.disembark_y = -1;

    base.destination_tile = water_tile;
    if (!base.source_tile.valid()) {
        base.source_tile = base.tile;
    }
    advance_action(ACTION_219_TRANSPORT_SHIP_GOING_TO_LANDING);
    route_remove();
    base.wait_ticks = 0;
}

void figure_transport_ship::move_to_tile(tile2i water_tile) {
    if (!transport_is_navigable_water(water_tile)) {
        return;
    }

    auto &d = runtime_data();
    d.landing_x = -1;
    d.landing_y = -1;
    d.disembark_x = -1;
    d.disembark_y = -1;

    base.destination_tile = water_tile;
    advance_action(ACTION_214_TRANSPORT_SHIP_SAILING);
    route_remove();
    d.evade_mode = evade_waiting;
}

void figure_transport_ship::move_to_wharf(int wharf_building_id, tile2i dock_tile) {
    if (!dock_tile.valid() || !map_terrain_is(dock_tile, TERRAIN_WATER | TERRAIN_DEEPWATER)) {
        return;
    }

    building *new_home = building_get(wharf_building_id);
    if (!new_home || !new_home->id || !new_home->is_valid() || !new_home->dcast_transport_wharf()) {
        return;
    }

    building *old_home = home();
    if (old_home && old_home->id && old_home->id != wharf_building_id) {
        old_home->remove_figure_by_id(id());
    }

    set_home(wharf_building_id);
    new_home->set_figure(BUILDING_SLOT_BOAT, &base);

    auto &d = runtime_data();
    d.landing_x = -1;
    d.landing_y = -1;
    d.disembark_x = -1;
    d.disembark_y = -1;
    d.evade_mode = evade_waiting;

    base.destination_tile = dock_tile;
    base.source_tile = dock_tile;
    advance_action(ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF);
    route_remove();
}

void figure_transport_ship::disembark_troops() {
    auto &d = runtime_data();
    formation *m = formation_get(d.formation_id);
    if (!m || !m->in_use) {
        d.formation_id = 0;
        d.has_troops = 0;
        d.phase = 0;
        d.request_event_id = -1;
        return;
    }

    tile2i order(d.landing_x, d.landing_y);
    if (!order.valid()) {
        order = find_shore_tile(base.tile);
    }
    if (!order.valid()) {
        return;
    }

    tile2i disembark = tile2i::invalid;
    map_water_landing_point(order, base.tile, disembark);
    if (!disembark.valid()) {
        return;
    }
    map_find_nearest_free_land_tile(disembark);

    m->tile = disembark;
    m->standard_tile = disembark;
    m->is_halted = 1;
    m->is_at_fort = 0;
    m->ship_figure_id = 0;
    m->in_distant_battle = 0;
    m->request_event_id = -1;

    for (int i = 0; i < formation::max_figures_count && m->figures[i]; i++) {
        figure *f = figure_get(m->figures[i]);
        if (!f || !f->is_alive() || f->action_state == FIGURE_ACTION_149_CORPSE) {
            continue;
        }

        // OG transport_legion_land: every figure shares the free land tile.
        f->previous_tile = disembark;
        f->tile = disembark;
        f->cc_coords.x = (int16_t)(disembark.x() * 15);
        f->cc_coords.y = (int16_t)(disembark.y() * 15);
        f->action_state = f->action_state_before_attack
            ? f->action_state_before_attack
            : ACTION_4_SOLDIER_AT_STANDARD;
        f->formation_at_rest = 0;
        f->allow_move_type = EMOVE_TERRAIN;
        f->set_flag(e_figure_flag_invisible, false);
        f->map_figure_add();
    }

    formation_batalion_move_to(m, order);

    d.formation_id = 0;
    d.has_troops = 0;
    d.phase = 0;
    d.landing_x = -1;
    d.landing_y = -1;
    d.disembark_x = -1;
    d.disembark_y = -1;
    d.request_event_id = -1;
}

void figure_transport_ship::before_poof() {
    // OG transport_sink: drown the company (legion_drowns_tick).
    // before_poof runs once on kill; drown immediately when troops are aboard.
    auto &d = runtime_data();
    if (!d.has_troops || d.formation_id <= 0) {
        return;
    }

    formation *m = formation_get(d.formation_id);
    if (m && m->in_use) {
        m->ship_figure_id = 0;
        for (int i = 0; i < formation::max_figures_count && m->figures[i]; i++) {
            figure *f = figure_get(m->figures[i]);
            if (f && f->is_alive()) {
                f->allow_move_type = EMOVE_TERRAIN;
                f->kill();
            }
        }
    }
    d.formation_id = 0;
    d.has_troops = 0;
    d.phase = 0;
}

void figure_transport_ship::clear_stale_cargo() {
    auto &d = runtime_data();
    if (d.formation_id <= 0) {
        d.has_troops = 0;
        return;
    }

    const int fid = d.formation_id;
    formation *m = formation_get(fid);
    if (!m || !m->in_use) {
        d.formation_id = 0;
        d.has_troops = 0;
        d.phase = 0;
        for (int i = 1; i < MAX_FIGURES; i++) {
            figure *f = figure_get(i);
            if (!f || !f->is_alive() || f->formation_id != fid) {
                continue;
            }
            if (f->action_state != ACTION_18_SOLDIER_ON_SHIP) {
                continue;
            }
            f->allow_move_type = EMOVE_TERRAIN;
            f->kill();
        }
        return;
    }

    if (!d.has_troops) {
        return;
    }

    int alive = 0;
    for (int i = 0; i < formation::max_figures_count && m->figures[i]; i++) {
        figure *f = figure_get(m->figures[i]);
        if (f && f->is_alive()) {
            alive++;
        }
    }
    if (alive > 0) {
        return;
    }

    m->ship_figure_id = 0;
    d.formation_id = 0;
    d.has_troops = 0;
    d.phase = 0;
}

void figure_transport_ship::sync_embarked_troops() {
    clear_stale_cargo();
    if (!has_troops()) {
        return;
    }

    auto &d = runtime_data();
    formation *m = formation_get(d.formation_id);
    if (!m || !m->in_use) {
        return;
    }

    for (int i = 0; i < formation::max_figures_count && m->figures[i]; i++) {
        figure *f = figure_get(m->figures[i]);
        if (!f || !f->is_alive() || f->action_state == FIGURE_ACTION_149_CORPSE) {
            continue;
        }
        if (f->action_state != ACTION_18_SOLDIER_ON_SHIP) {
            f->action_state_before_attack = f->action_state;
            f->action_state = ACTION_18_SOLDIER_ON_SHIP;
            f->route_remove();
        }
        f->map_figure_remove();
        f->tile = base.tile;
        f->formation_at_rest = 0;
        f->allow_move_type = EMOVE_TERRAIN;
        f->set_flag(e_figure_flag_invisible, false);
    }

    m->tile = base.tile;
    m->standard_tile = base.tile;
}

void figure_transport_ship::go_to_best_shipwright() {
    // OG ship_go_to_best_dock: only switches state when a dock exists.
    int dock_id = building_shipyard_find_best_dock(id());
    if (dock_id <= 0) {
        return;
    }

    building *dock = building_get(dock_id);
    auto *shipyard = dock ? dock->dcast_shipyard() : nullptr;
    if (!shipyard) {
        return;
    }

    tile2i berth = shipyard->get_water_access_tiles().point_a;
    if (!berth.valid()) {
        berth = dock->tile;
    }
    if (!berth.valid()) {
        return;
    }

    set_destination(dock_id);
    base.destination_tile = berth;
    base.source_tile = base.tile;
    route_remove();
    advance_action(ACTION_216_TRANSPORT_SHIP_GOING_TO_SHIPWRIGHT);
    base.wait_ticks = 0;
}

void figure_transport_ship::check_auto_repair() {
    const int state = action_state();
    if (state == ACTION_216_TRANSPORT_SHIP_GOING_TO_SHIPWRIGHT
        || state == ACTION_217_TRANSPORT_SHIP_QUEUED_AT_SHIPWRIGHT
        || state == ACTION_221_TRANSPORT_SHIP_GOING_TO_REQUEST
        || state == ACTION_222_TRANSPORT_SHIP_AWAY_ON_REQUEST
        || state == FIGURE_ACTION_149_CORPSE) {
        return;
    }

    const int max_d = base.max_damage();
    if (max_d <= 0) {
        return;
    }
    const int health = calc_percentage(max_d - (int)base.damage, max_d);
    if (health > 0 && health <= current_params().hull_auto_repair_percent) {
        go_to_best_shipwright();
    }
}

void figure_transport_ship::set_evade_order() {
    runtime_data().evade_mode = evade_waiting;
    base.wait_ticks = 0;
    advance_action(ACTION_215_TRANSPORT_SHIP_EVADING);
}

void figure_transport_ship::set_hold_order() {
    runtime_data().evade_mode = evade_waiting;
    base.destination_tile = base.tile;
    advance_action(ACTION_213_TRANSPORT_SHIP_DOCKED);
    base.wait_ticks = 0;
}

void figure_transport_ship::set_repair_order() {
    go_to_best_shipwright();
}

void figure_transport_ship::begin_kingdom_request() {
    tile2i entry = scenario_map_river_entry();
    if (!entry.valid()) {
        entry = scenario_map_entry();
    }
    base.destination_tile = entry;
    route_remove();
    advance_action(ACTION_221_TRANSPORT_SHIP_GOING_TO_REQUEST);
}

void figure_transport_ship::return_from_kingdom_request(tile2i landing) {
    // OG: ship_landing_* = legion land tile; destination = farthest water toward it.
    auto &d = runtime_data();
    tile2i land = landing.valid() ? landing : find_shore_tile(base.tile);
    if (!land.valid()) {
        land = base.tile;
    }
    d.landing_x = land.x();
    d.landing_y = land.y();
    d.disembark_x = -1;
    d.disembark_y = -1;

    tile2i water_dest = tile2i::invalid;
    map_water_farthest_on_line(base.tile, land, water_dest);
    if (!water_dest.valid() || !map_terrain_is(water_dest, TERRAIN_WATER | TERRAIN_DEEPWATER)) {
        water_dest = scenario_map_river_entry();
    }
    if (!water_dest.valid()) {
        water_dest = find_shore_tile(land);
        // Prefer water next to shore.
        if (water_dest.valid()) {
            static const vec2i dirs[] = {
                {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
            };
            for (const vec2i &dir : dirs) {
                tile2i cand = water_dest.shifted(dir);
                if (cand.valid() && map_terrain_is(cand, TERRAIN_WATER | TERRAIN_DEEPWATER)) {
                    water_dest = cand;
                    break;
                }
            }
        }
    }
    if (!water_dest.valid()) {
        water_dest = base.tile;
    }

    base.destination_tile = water_dest;
    base.set_flag(e_figure_flag_invisible, false);
    route_remove();
    advance_action(ACTION_223_TRANSPORT_SHIP_RETURNING_FROM_REQUEST);
}

figure_id figure_transport_ship::find_nearest_enemy_ship(int range) const {
    figure_id best = 0;
    int best_dist = range + 1;
    for (figure *f : map_figures()) {
        if (!f || f->id == base.id || !transport_is_enemy_ship(f)) {
            continue;
        }
        const int dist = calc_maximum_distance(base.tile, f->tile);
        if (dist < best_dist) {
            best_dist = dist;
            best = f->id;
        }
    }
    return best;
}

tile2i figure_transport_ship::pick_escape_tile(tile2i from_enemy) const {
    // OG transport_escapes: for flee-direction D, try D and its two diagonal
    // neighbors, each scaled by escape_distance (was hardcoded ±10).
    static const vec2i DIR8[8] = {
        {0, -1}, {1, -1}, {1, 0}, {1, 1},
        {0, 1}, {-1, 1}, {-1, 0}, {-1, -1},
    };

    int dir = calc_general_direction(from_enemy, base.tile);
    if (dir < 0 || dir > 7) {
        dir = 7;
    }

    const int dist = std::max(1, (int)current_params().escape_distance);
    int best = -1;
    tile2i best_tile = base.tile;
    // Main direction first, then +45°, then -45° (same set as OG table).
    for (int delta : {0, 1, -1}) {
        const vec2i &u = DIR8[(dir + delta + 8) % 8];
        tile2i target = base.tile.shifted(u.x * dist, u.y * dist);
        tile2i reached;
        int d = transport_farthest_water_on_line(base.tile, target, reached);
        if (d >= best) {
            best = d;
            best_tile = reached.valid() ? reached : best_tile;
        }
    }
    return best_tile;
}

void figure_transport_ship::action_waiting() {
    // OG transport_wait_at_dock: after dock_wait_ticks head for home wharf.
    base.wait_ticks++;
    if (base.wait_ticks < current_params().dock_wait_ticks) {
        return;
    }
    base.wait_ticks = 0;

    building *b = home();
    building_transport_wharf *wharf = (b && b->id) ? b->dcast_transport_wharf() : nullptr;
    if (wharf) {
        tile2i dock = wharf->get_water_access_tiles().point_a;
        if (!dock.valid()) {
            dock = tile2i(b->tiles[0]);
        }
        if (dock.valid()) {
            set_destination(b);
            base.destination_tile = dock;
            base.source_tile = dock;
            route_remove();
            advance_action(ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF);
            return;
        }
    }

    water_dest result = map_water_get_wharf_for_new_transport_ship(base);
    if (result.found) {
        if (b && b->id) {
            b->remove_figure_by_id(id());
        }
        set_home(result.bid);
        building *nb = building_get(result.bid);
        if (nb && nb->id) {
            nb->set_figure(BUILDING_SLOT_BOAT, &base);
        }
        set_destination(nb);
        base.destination_tile = result.tile;
        base.source_tile = result.tile;
        route_remove();
        advance_action(ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF);
    } else {
        kill();
    }
}

void figure_transport_ship::action_going_to_wharf() {
    base.move_ticks(1);
    base.height_adjusted_ticks = 0;
    if (direction() == DIR_FIGURE_NONE) {
        advance_action(ACTION_213_TRANSPORT_SHIP_DOCKED);
        base.wait_ticks = 0;
        base.source_tile = base.tile;
        building *b = home();
        if (b && b->id) {
            b->set_figure(BUILDING_SLOT_BOAT, &base);
        }
    } else if (direction() == DIR_FIGURE_REROUTE) {
        route_remove();
    } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
        if (has_troops()) {
            set_evade_order();
        } else {
            advance_action(ACTION_211_TRANSPORT_SHIP_WAITING);
        }
    }
}

tile2i figure_transport_ship::home_berth_tile() const {
    const building *b = base.home();
    if (!b || !b->id) {
        return tile2i::invalid;
    }

    // OG ship_update_dock berth: map_water_tile_next_to(home.x/y, size).
    tile2i next = tile2i::invalid;
    if (map_water_tile_next_to(b->tile, b->size, next) && next.valid()) {
        return next;
    }

    // Fallback: orientation access point (wharf layout).
    building *mutable_b = building_get(b->id);
    if (auto *wharf = mutable_b ? mutable_b->dcast_transport_wharf() : nullptr) {
        tile2i berth = wharf->get_water_access_tiles().point_a;
        if (berth.valid()) {
            return berth;
        }
    }
    return tile2i::invalid;
}

bool figure_transport_ship::is_docked() const {
    // OG ship_is_docked: home dock's ship_id == this figure.
    const building *b = base.home();
    if (!b || !b->id) {
        return false;
    }
    return b->get_figure_id(BUILDING_SLOT_BOAT) == base.id;
}

void figure_transport_ship::update_dock() {
    // OG ship_update_dock: claim berth only while ship stands on map_water_tile_next_to.
    building *b = home();
    if (!b || !b->id) {
        return;
    }
    tile2i berth = home_berth_tile();
    if (berth.valid() && base.tile == berth) {
        b->set_figure(BUILDING_SLOT_BOAT, &base);
    } else if (b->get_figure_id(BUILDING_SLOT_BOAT) == id()) {
        b->remove_figure(BUILDING_SLOT_BOAT);
    }
}

void figure_transport_ship::action_docked() {
    // OG: ship_move_to_dock then transport_docked (face enemy). DOCKED skips the
    // arrive→EVADING branch inside ship_move_to_dock.
    if (base.destination_tile.valid() && base.tile != base.destination_tile) {
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            route_remove();
        }
    } else if (base.destination_tile.valid() && base.tile == base.destination_tile) {
        base.direction = DIR_FIGURE_NONE;
    }
    update_dock();

    base.wait_ticks++;
    if (base.wait_ticks > current_params().face_enemy_wait) {
        base.wait_ticks = 0;
        figure_id enemy = find_nearest_enemy_ship(current_params().face_enemy_range);
        if (enemy) {
            figure *e = figure_get(enemy);
            if (e) {
                base.direction = (uint8_t)calc_missile_shooter_direction(base.tile, e->tile);
                base.previous_tile_direction = base.direction;
            }
        }
    }
}

void figure_transport_ship::action_sailing() {
    // OG ship_move_to_dock (SAILING / free-sail).
    if (base.destination_tile.valid() && base.tile == base.destination_tile) {
        base.direction = DIR_FIGURE_NONE;
    } else {
        base.move_ticks(1);
    }
    base.height_adjusted_ticks = 0;

    if (direction() == DIR_FIGURE_NONE) {
        base.wait_ticks = 0;
        // Arrived off the home berth → at-sea EVADING idle (OG ship_move_to_dock
        // when not at own dock). Berth tile, not only the boat slot: slot is
        // refreshed in update_dock after this check.
        tile2i berth = home_berth_tile();
        if (!berth.valid() || base.tile != berth) {
            set_evade_order();
        }
    } else if (direction() == DIR_FIGURE_REROUTE) {
        route_remove();
    } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
        route_remove();
    }

    update_dock();
}

void figure_transport_ship::action_evading() {
    auto &d = runtime_data();
    if (d.evade_mode == evade_moving) {
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            d.evade_mode = evade_waiting;
            base.wait_ticks = 0;
        } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            route_remove();
            d.evade_mode = evade_waiting;
            base.wait_ticks = 0;
        }
        return;
    }

    base.wait_ticks++;
    if (base.wait_ticks < current_params().evade_ticks) {
        return;
    }
    base.wait_ticks = 0;

    figure_id enemy_id = find_nearest_enemy_ship(current_params().evade_range);
    if (!enemy_id) {
        return;
    }
    figure *enemy = figure_get(enemy_id);
    if (!enemy) {
        return;
    }

    tile2i escape = pick_escape_tile(enemy->tile);
    base.destination_tile = escape;
    route_remove();
    d.evade_mode = evade_moving;
}

void figure_transport_ship::action_going_to_shipwright() {
    base.move_ticks(1);
    base.height_adjusted_ticks = 0;
    if (direction() == DIR_FIGURE_NONE) {
        int dock_id = base.destination_building_id;
        int best = building_shipyard_find_best_dock(id());
        if (best > 0 && building_shipyard_repair_queue_size(dock_id) >= 1 && best != dock_id) {
            dock_id = best;
            building *dock = building_get(dock_id);
            auto *shipyard = dock ? dock->dcast_shipyard() : nullptr;
            tile2i berth = shipyard ? shipyard->get_water_access_tiles().point_a : tile2i::invalid;
            if (!berth.valid() && dock) {
                berth = tile2i(dock->tiles[0]);
            }
            if (berth.valid()) {
                set_destination(dock_id);
                base.destination_tile = berth;
                route_remove();
                return;
            }
        }
        if (dock_id > 0 && building_shipyard_queue_ship(id(), dock_id)) {
            advance_action(ACTION_217_TRANSPORT_SHIP_QUEUED_AT_SHIPWRIGHT);
            base.wait_ticks = 0;
        } else {
            set_evade_order();
        }
    } else if (direction() == DIR_FIGURE_REROUTE) {
        route_remove();
    } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
        building_shipyard_leave_queue(id());
        set_evade_order();
    }
}

void figure_transport_ship::action_queued_at_shipwright() {
    building *dock = building_get(base.destination_building_id);
    auto *shipyard = dock ? dock->dcast_shipyard() : nullptr;
    if (!shipyard || !shipyard->base.is_valid() || shipyard->num_workers() <= 0) {
        building_shipyard_leave_queue(id());
        go_to_best_shipwright();
        return;
    }
    // Idle while shipwright heals (OG QUEUED_AT_DOCK).
}

void figure_transport_ship::action_going_to_legion() {
    // Already on the embark tile: do not wait for move_ticks progress to hit center.
    if (base.destination_tile.valid() && base.tile == base.destination_tile) {
        base.direction = DIR_FIGURE_NONE;
    } else {
        base.move_ticks(1);
    }
    base.height_adjusted_ticks = 0;
    auto &d = runtime_data();

    if (direction() == DIR_FIGURE_NONE) {
        base.wait_ticks = 0;
        const int formation_id = d.formation_id;
        if (formation_id <= 0 || !legion_ready_to_board(formation_id)) {
            return;
        }

        formation *m = formation_get(formation_id);
        if (!m || !m->in_use) {
            d.formation_id = 0;
            d.phase = 0;
            advance_action(ACTION_214_TRANSPORT_SHIP_SAILING);
            return;
        }

        if (m->ship_figure_id == 0 || m->ship_figure_id == id()) {
            board_legion(formation_id);
            advance_action(ACTION_214_TRANSPORT_SHIP_SAILING);
            base.wait_ticks = 0;
            return;
        }

        // Another ship already claimed this company.
        d.formation_id = 0;
        d.phase = 0;
        advance_action(ACTION_218_TRANSPORT_SHIP_GOING_TO_LEGION);
    } else if (direction() == DIR_FIGURE_REROUTE) {
        route_remove();
    } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
        route_remove();
        set_evade_order();
    }
}

void figure_transport_ship::action_going_to_landing() {
    base.move_ticks(1);
    base.height_adjusted_ticks = 0;
    auto &d = runtime_data();

    if (direction() == DIR_FIGURE_NONE) {
        if (d.landing_x < 0 && d.landing_y < 0) {
            return;
        }
        // OG: land immediately on arrival (no embark/disembark timer).
        disembark_troops();
        advance_action(ACTION_214_TRANSPORT_SHIP_SAILING);
        d.landing_x = -1;
        d.landing_y = -1;
        base.wait_ticks = 0;
    } else if (direction() == DIR_FIGURE_REROUTE) {
        route_remove();
    } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
        route_remove();
        set_evade_order();
    }
}

void figure_transport_ship::action_going_to_request() {
    tile2i entry = scenario_map_river_entry();
    if (!entry.valid()) {
        entry = scenario_map_entry();
    }
    base.destination_tile = entry;
    base.move_ticks(1);
    base.height_adjusted_ticks = 0;
    if (direction() == DIR_FIGURE_NONE) {
        advance_action(ACTION_222_TRANSPORT_SHIP_AWAY_ON_REQUEST);
        route_remove();
        base.set_flag(e_figure_flag_invisible);
    } else if (direction() == DIR_FIGURE_REROUTE) {
        route_remove();
    } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
        kill();
    }
}

void figure_transport_ship::action_away_on_request() {
    base.set_flag(e_figure_flag_invisible);
}

void figure_transport_ship::figure_action() {
    clear_stale_cargo();

    building *home_b = home();
    if (home_b && home_b->id && !home_b->is_valid()) {
        // OG: building not IN_USE → corpse.
        kill();
        return;
    }

    if (base.damage > base.max_damage()) {
        kill();
        return;
    }

    check_auto_repair();
    sync_embarked_troops();
    assert(base.allow_move_type == EMOVE_WATER);

    switch (action_state()) {
    case ACTION_211_TRANSPORT_SHIP_WAITING:
        action_waiting();
        break;
    case ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF:
        action_going_to_wharf();
        break;
    case ACTION_213_TRANSPORT_SHIP_DOCKED:
        action_docked();
        break;
    case ACTION_214_TRANSPORT_SHIP_SAILING:
        action_sailing();
        break;
    case ACTION_215_TRANSPORT_SHIP_EVADING:
        action_evading();
        break;
    case ACTION_216_TRANSPORT_SHIP_GOING_TO_SHIPWRIGHT:
        action_going_to_shipwright();
        break;
    case ACTION_217_TRANSPORT_SHIP_QUEUED_AT_SHIPWRIGHT:
        action_queued_at_shipwright();
        break;
    case ACTION_218_TRANSPORT_SHIP_GOING_TO_LEGION:
        action_going_to_legion();
        break;
    case ACTION_219_TRANSPORT_SHIP_GOING_TO_LANDING:
    case ACTION_220_TRANSPORT_SHIP_RETURNING_TO_LANDING:
    case ACTION_223_TRANSPORT_SHIP_RETURNING_FROM_REQUEST:
        base.set_flag(e_figure_flag_invisible, false);
        action_going_to_landing();
        break;
    case ACTION_221_TRANSPORT_SHIP_GOING_TO_REQUEST:
        action_going_to_request();
        break;
    case ACTION_222_TRANSPORT_SHIP_AWAY_ON_REQUEST:
        action_away_on_request();
        break;
    default:
        advance_action(ACTION_211_TRANSPORT_SHIP_WAITING);
        break;
    }
}

void figure_transport_ship::kill() {
    // Match OG drown-at-legion_drowns_tick; we drown in before_poof.
    base.wait_ticks = current_params().legion_drowns_tick;
    before_poof();
    building_shipyard_leave_queue(id());
    building *b = home();
    if (b && b->id) {
        b->remove_figure_by_id(id());
    }
    base.set_home(0);
    base.wait_ticks = 0;
    figure_shipwreck::create(tile());
    figure_impl::kill();
}

void figure_transport_ship::update_animation() {
    // OG military.c transport image: corpse → sinking(/swept); moving → swim;
    // still → idle. Swept sets need River of Blood sweep (EVENT_TYPE_BLOOD_RIVER
    // is still a stub) — keep the *_swept keys ready, select when sweep lands.
    const bool swept = false;
    pcstr anim_key = swept ? "idle_swept" : "idle";

    if (action_state() == FIGURE_ACTION_149_CORPSE) {
        anim_key = swept ? "death_swept" : "death";
        image_set_animation(anim_key);
        base.use_cart = false;
        base.cart_image_id = 0;
        return;
    }

    switch (action_state()) {
    case ACTION_214_TRANSPORT_SHIP_SAILING:
    case ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF:
    case ACTION_215_TRANSPORT_SHIP_EVADING:
    case ACTION_216_TRANSPORT_SHIP_GOING_TO_SHIPWRIGHT:
    case ACTION_218_TRANSPORT_SHIP_GOING_TO_LEGION:
    case ACTION_219_TRANSPORT_SHIP_GOING_TO_LANDING:
    case ACTION_220_TRANSPORT_SHIP_RETURNING_TO_LANDING:
    case ACTION_221_TRANSPORT_SHIP_GOING_TO_REQUEST:
    case ACTION_223_TRANSPORT_SHIP_RETURNING_FROM_REQUEST:
        anim_key = swept ? "swim_swept" : "swim";
        break;
    default:
        break;
    }
    image_set_animation(anim_key);

    // OG: selected transport draws ship wake via cart_image_id.
    if (g_window_manager.window_is("window_city_transport")
        && window_city_transport_figure_id() == id()) {
        const int wake_img = anim("wake").first_img();
        if (wake_img > 0) {
            const int frame = (base.animctx.frame << 3) / 12;
            base.use_cart = true;
            base.cart_image_id = (uint16_t)(wake_img + frame);
            return;
        }
    }
    base.use_cart = false;
    base.cart_image_id = 0;
}

void __transport_ship_embark(int ship_id, int formation_id) {
    figure *f = figure_get(ship_id);
    if (!f) {
        return;
    }
    if (auto *ship = smart_cast<figure_transport_ship>(f)) {
        ship->embark_formation(formation_id);
    }
}
ANK_FUNCTION_2(__transport_ship_embark)

void __transport_ship_sail_to(int ship_id, int x, int y) {
    figure *f = figure_get(ship_id);
    if (!f) {
        return;
    }
    if (auto *ship = smart_cast<figure_transport_ship>(f)) {
        ship->sail_to_landing(tile2i(x, y));
    }
}
ANK_FUNCTION_3(__transport_ship_sail_to)

int __transport_ship_has_troops(int ship_id) {
    figure *f = figure_get(ship_id);
    if (!f) {
        return 0;
    }
    auto *ship = smart_cast<figure_transport_ship>(f);
    return ship && ship->has_troops() ? 1 : 0;
}
ANK_FUNCTION_1(__transport_ship_has_troops)
