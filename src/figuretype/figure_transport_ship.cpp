#include "figure_transport_ship.h"

#include "figure/route.h"
#include "figure/formation.h"
#include "figure/formation_layout.h"
#include "figuretype/figure_soldier.h"
#include "grid/water.h"
#include "grid/terrain.h"
#include "city/city_buildings.h"
#include "building/building_transport_wharf.h"
#include "figuretype/figure_shipwreck.h"
#include "city/city.h"
#include "city/city_message.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_transport_ship);

namespace {

constexpr int TRANSPORT_EMBARK_TICKS = 50;
constexpr int TRANSPORT_DISEMBARK_TICKS = 50;

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

// map_water_is_point_inside() is only a map-bounds check — require real water.
bool transport_is_navigable_water(tile2i tile) {
    return tile.valid()
        && map_terrain_is(tile, TERRAIN_WATER | TERRAIN_DEEPWATER)
        && !map_terrain_is(tile, TERRAIN_BUILDING);
}

tile2i transport_find_shore_tile(tile2i water_tile) {
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

// Wider search used when the ship is dying and must dump cargo somewhere.
tile2i transport_find_shore_tile_wide(tile2i water_tile) {
    tile2i near = transport_find_shore_tile(water_tile);
    if (near.valid()) {
        return near;
    }

    for (int radius = 2; radius <= 4; radius++) {
        for (int dy = -radius; dy <= radius; dy++) {
            for (int dx = -radius; dx <= radius; dx++) {
                if (dx == 0 && dy == 0) {
                    continue;
                }
                tile2i land = water_tile.shifted(dx, dy);
                if (transport_land_ok(land)) {
                    return land;
                }
            }
        }
    }
    return tile2i::invalid;
}

bool transport_formation_already_embarked(int formation_id, int except_ship_id) {
    for (int i = 1; i < MAX_FIGURES; i++) {
        figure *f = figure_get(i);
        if (!f || !f->is_alive() || f->id == except_ship_id) {
            continue;
        }
        figure_transport_ship *ship = smart_cast<figure_transport_ship>(f);
        if (ship && ship->transported_formation() == formation_id) {
            return true;
        }
    }
    return false;
}

} // namespace

water_dest map_water_get_wharf_for_new_transport_ship(figure &boat) {
    building_transport_wharf *wharf = nullptr;

    wharf = building_first_ex<building_transport_wharf>([&boat] (building_transport_wharf *w) {
        int wharf_boat_id = w->get_figure_id(BUILDING_SLOT_BOAT);
        if (!wharf_boat_id || wharf_boat_id == boat.id) {
            return true;
        }

        return false;
    });

    if (!wharf) {
        return { false, 0 };
    }

    tile2i dock_tile(wharf->runtime_data().dock_tiles[0]);
    return { dock_tile.valid(), wharf->id(), dock_tile };
}

void figure_transport_ship::on_create() {
    figure_impl::on_create();
    base.allow_move_type = EMOVE_WATER;
}

void figure_transport_ship::on_destroy() {
    building *b = home();
    if (b && b->id) {
        b->remove_figure_by_id(id());
    }
}

bool figure_transport_ship::has_troops() const {
    const int fid = runtime_data().formation_id;
    if (fid <= 0) {
        return false;
    }
    const formation *m = formation_get(fid);
    return m && m->in_use;
}

int figure_transport_ship::transported_formation() const {
    return has_troops() ? runtime_data().formation_id : 0;
}

bool figure_transport_ship::can_embark() const {
    if (has_troops()) {
        return false;
    }

    const int state = action_state();
    if (state == ACTION_213_TRANSPORT_SHIP_MOORED) {
        return true;
    }

    if (state == ACTION_214_TRANSPORT_SHIP_ANCHORED) {
        return transport_find_shore_tile(base.tile).valid();
    }

    return false;
}

bool figure_transport_ship::embark_formation(int formation_id) {
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

    auto &d = runtime_data();
    d.formation_id = (int8_t)formation_id;
    d.phase = 1;
    d.embark_ticks = 0;
    d.landing_x = -1;
    d.landing_y = -1;
    d.disembark_x = -1;
    d.disembark_y = -1;

    int loaded = 0;
    for (int i = 0; i < formation::max_figures_count && m->figures[i]; i++) {
        figure *f = figure_get(m->figures[i]);
        if (!f || !f->is_alive()) {
            continue;
        }

        // Match enemy transport: leave the land grid and stay amphibious while
        // aboard — otherwise action.cpp kills land soldiers on water tiles.
        f->map_figure_remove();
        f->set_flag(e_figure_flag_invisible);
        f->tile = base.tile;
        f->route_remove();
        f->action_state = ACTION_84_SOLDIER_AT_STANDARD;
        f->formation_at_rest = 1;
        f->allow_move_type = EMOVE_AMPHIBIAN;
        loaded++;
    }

    if (loaded <= 0) {
        d.formation_id = 0;
        d.phase = 0;
        return false;
    }

    m->is_halted = 1;
    m->is_at_fort = 0;
    return true;
}

void figure_transport_ship::sail_to_landing(tile2i water_tile) {
    if (!has_troops() || !transport_is_navigable_water(water_tile)) {
        return;
    }

    tile2i shore = transport_find_shore_tile(water_tile);
    if (!shore.valid()) {
        return;
    }

    auto &d = runtime_data();
    d.landing_x = water_tile.x();
    d.landing_y = water_tile.y();
    d.disembark_x = shore.x();
    d.disembark_y = shore.y();
    d.phase = 2;
    d.embark_ticks = 0;

    base.destination_tile = water_tile;
    if (!base.source_tile.valid()) {
        base.source_tile = base.tile;
    }
    advance_action(ACTION_215_TRANSPORT_SHIP_LEAVING);
    route_remove();
}

void figure_transport_ship::move_to_tile(tile2i water_tile) {
    if (!transport_is_navigable_water(water_tile)) {
        return;
    }

    auto &d = runtime_data();
    // Reposition only — do not arm auto-disembark on arrival.
    d.landing_x = -1;
    d.landing_y = -1;
    d.disembark_x = -1;
    d.disembark_y = -1;
    d.embark_ticks = 0;

    base.destination_tile = water_tile;
    advance_action(ACTION_215_TRANSPORT_SHIP_LEAVING);
    route_remove();
}

void figure_transport_ship::move_to_wharf(int wharf_building_id, tile2i dock_tile) {
    // Wharf access tiles are authoritative; allow BUILDING bit (unlike free-water move).
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
    // Returning to a wharf is not a landing order — keep troops aboard until Disembark.
    d.landing_x = -1;
    d.landing_y = -1;
    d.disembark_x = -1;
    d.disembark_y = -1;
    d.embark_ticks = 0;

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
        d.phase = 0;
        return;
    }

    tile2i disembark(d.disembark_x, d.disembark_y);
    if (!transport_land_ok(disembark)) {
        disembark = transport_find_shore_tile(base.tile);
    }
    if (!transport_land_ok(disembark)) {
        // Keep troops aboard rather than dumping onto water / invalid tiles.
        return;
    }

    for (int i = 0; i < formation::max_figures_count && m->figures[i]; i++) {
        figure *f = figure_get(m->figures[i]);
        if (!f || !f->is_alive()) {
            continue;
        }

        tile2i pos = disembark;
        if (f->dcast_soldier()) {
            tile2i offset = formation_layout_position(m->layout, f->index_in_formation);
            tile2i candidate = disembark.shifted(offset);
            if (transport_land_ok(candidate)) {
                pos = candidate;
            }
        }

        f->set_flag(e_figure_flag_invisible, false);
        f->map_figure_remove();
        f->tile = pos;
        f->action_state = ACTION_84_SOLDIER_AT_STANDARD;
        f->formation_at_rest = 0;
        f->allow_move_type = EMOVE_TERRAIN;
        f->map_figure_add();
    }

    m->tile = disembark;
    m->standard_tile = disembark;
    m->is_halted = 1;
    m->is_at_fort = 0;

    d.formation_id = 0;
    d.phase = 0;
    d.embark_ticks = 0;
    d.landing_x = -1;
    d.landing_y = -1;
    d.disembark_x = -1;
    d.disembark_y = -1;
}

void figure_transport_ship::before_poof() {
    if (!has_troops()) {
        return;
    }

    disembark_troops();
    if (!has_troops()) {
        return;
    }

    // Ship is dying with no adjacent shore — force a wider dump so soldiers are
    // not left invisible/amphibious forever.
    auto &d = runtime_data();
    tile2i shore = transport_find_shore_tile_wide(base.tile);
    if (shore.valid()) {
        d.disembark_x = shore.x();
        d.disembark_y = shore.y();
        disembark_troops();
    }

    if (!has_troops()) {
        return;
    }

    // Last resort: make the company visible at the ship's tile and clear hold
    // (they may die on water next tick, but are no longer orphaned invisibly).
    formation *m = formation_get(d.formation_id);
    if (m && m->in_use) {
        for (int i = 0; i < formation::max_figures_count && m->figures[i]; i++) {
            figure *f = figure_get(m->figures[i]);
            if (!f || !f->is_alive()) {
                continue;
            }
            f->set_flag(e_figure_flag_invisible, false);
            f->map_figure_remove();
            f->tile = base.tile;
            f->allow_move_type = EMOVE_AMPHIBIAN;
            f->map_figure_add();
        }
    }
    d.formation_id = 0;
    d.phase = 0;
    d.embark_ticks = 0;
}

void figure_transport_ship::clear_stale_cargo() {
    auto &d = runtime_data();
    if (d.formation_id <= 0) {
        return;
    }

    const int fid = d.formation_id;
    formation *m = formation_get(fid);
    if (!m || !m->in_use) {
        d.formation_id = 0;
        d.phase = 0;
        d.embark_ticks = 0;
        // Formation wiped under us — do not dump leftovers onto water as
        // EMOVE_TERRAIN (action.cpp would kill them mid-tile). Kill cleanly.
        for (int i = 1; i < MAX_FIGURES; i++) {
            figure *f = figure_get(i);
            if (!f || !f->is_alive() || f->formation_id != fid) {
                continue;
            }
            if (f->allow_move_type != EMOVE_AMPHIBIAN) {
                continue;
            }
            f->set_flag(e_figure_flag_invisible, false);
            f->allow_move_type = EMOVE_TERRAIN;
            f->kill();
        }
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

    d.formation_id = 0;
    d.phase = 0;
    d.embark_ticks = 0;
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

    // Keep embarked troops glued to the hull (match enemy transport).
    for (int i = 0; i < formation::max_figures_count && m->figures[i]; i++) {
        figure *f = figure_get(m->figures[i]);
        if (!f || !f->is_alive()) {
            continue;
        }
        f->map_figure_remove();
        f->tile = base.tile;
        f->formation_at_rest = 1;
        f->allow_move_type = EMOVE_AMPHIBIAN;
        f->action_state = ACTION_84_SOLDIER_AT_STANDARD;
        f->set_flag(e_figure_flag_invisible);
    }

    // Keep formation marker with the hull so military UI/orders track the ship.
    m->tile = base.tile;
    m->standard_tile = base.tile;
}

void figure_transport_ship::figure_action() {
    clear_stale_cargo();

    building *b = home();
    building_transport_wharf *wharf = (b && b->id) ? b->dcast_transport_wharf() : nullptr;

    // Empty ship without a home wharf must seek one (or die). Loaded ships keep
    // the troop mission going even if the wharf was deleted mid-crossing.
    if (!wharf && !has_troops()) {
        if (action_state() != ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF || base.destination_building_id == 0) {
            // Prefer a free berth — stealing an occupied slot causes reclaim fights.
            water_dest result = map_water_get_wharf_for_new_transport_ship(base);
            if (result.found) {
                building *nb = building_get(result.bid);
                if (b && b->id) {
                    b->remove_figure_by_id(id());
                }
                set_home(result.bid);
                if (nb && nb->id) {
                    nb->set_figure(BUILDING_SLOT_BOAT, &base);
                }
                set_destination(nb);
                base.destination_tile = result.tile;
                base.source_tile = result.tile;
                route_remove();
                advance_action(ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF);
                return;
            } else {
                kill();
                return;
            }
        }

        base.move_ticks(1);
        if (direction(DIR_FIGURE_NONE, DIR_FIGURE_CAN_NOT_REACH, DIR_FIGURE_REROUTE)) {
            poof();
        }
        return;
    }

    // Do not abort an active troop-carrying trip if the home wharf loses labor
    // or the boat slot — yanking home mid-crossing dumps the company wrong.
    // Already-moored empty ships stay put (otherwise MOORED↔GOING every tick).
    // Do not cancel an in-flight LEAVING order (player reposition / return sail).
    if (wharf && !has_troops()
        && wharf->num_workers() == 0
        && action_state() != ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF
        && action_state() != ACTION_213_TRANSPORT_SHIP_MOORED
        && action_state() != ACTION_215_TRANSPORT_SHIP_LEAVING) {
        tile2i dock = wharf->get_water_access_tiles().point_a;
        if (dock.valid()) {
            set_destination(&wharf->base);
            base.destination_tile = dock;
            route_remove();
            advance_action(ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF);
        }
    }

    if (wharf && !has_troops()
        && action_state() != ACTION_211_TRANSPORT_SHIP_CREATED) {
        int wharf_boat_id = b->get_figure_id(BUILDING_SLOT_BOAT);
        if (wharf_boat_id != id()) {
            const int state = action_state();
            // Sitting at home berth — reclaim rather than flee/poof after a trip.
            if (state == ACTION_213_TRANSPORT_SHIP_MOORED) {
                b->set_figure(BUILDING_SLOT_BOAT, &base);
            } else if (state == ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF
                       || (state == ACTION_215_TRANSPORT_SHIP_LEAVING
                           && base.source_tile.valid()
                           && base.destination_tile == base.source_tile)) {
                // Already heading home / to a berth — finish the trip; reclaim on MOOR.
            } else {
                water_dest result = map_water_get_wharf_for_new_transport_ship(base);
                building *nb = building_get(result.bid);
                if (nb && nb->id) {
                    if (b && b->id && b->id != nb->id) {
                        b->remove_figure_by_id(id());
                    }
                    set_home(nb->id);
                    nb->set_figure(BUILDING_SLOT_BOAT, &base);
                    b = nb;
                    wharf = nb->dcast_transport_wharf();
                    advance_action(ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF);
                    base.destination_tile = result.tile;
                    base.source_tile = result.tile;
                    route_remove();
                } else {
                    // No free berth elsewhere — reclaim our home instead of poofing
                    // after a successful troop drop (common with a single wharf).
                    tile2i dock = wharf->get_water_access_tiles().point_a;
                    if (dock.valid()) {
                        b->set_figure(BUILDING_SLOT_BOAT, &base);
                        set_destination(&wharf->base);
                        advance_action(ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF);
                        base.destination_tile = dock;
                        base.source_tile = dock;
                        route_remove();
                    } else {
                        poof();
                    }
                }
            }
        }
    }

    assert(base.allow_move_type == EMOVE_WATER);

    sync_embarked_troops();

    auto &d = runtime_data();

    switch (action_state()) {
    case ACTION_211_TRANSPORT_SHIP_CREATED:
        base.wait_ticks++;
        if (base.wait_ticks >= 50) {
            base.wait_ticks = 0;
            water_dest result = map_water_get_wharf_for_new_transport_ship(base);
            if (result.bid && result.found) {
                if (b && b->id) {
                    b->remove_figure_by_id(id());
                }
                set_home(result.bid);
                building *nb = building_get(result.bid);
                if (nb && nb->id) {
                    nb->set_figure(BUILDING_SLOT_BOAT, &base);
                }
                advance_action(ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF);
                base.destination_tile = result.tile;
                base.source_tile = result.tile;
                route_remove();
            }
        }
        break;

    case ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            advance_action(ACTION_213_TRANSPORT_SHIP_MOORED);
            base.wait_ticks = 0;
            base.source_tile = base.tile;
            // Reclaim berth on arrival (another ship may have taken the slot mid-trip).
            if (b && b->id) {
                b->set_figure(BUILDING_SLOT_BOAT, &base);
            }
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            // Loaded ships must not drop into CREATED (spawn/seek loop) mid-mission.
            if (has_troops()) {
                advance_action(ACTION_214_TRANSPORT_SHIP_ANCHORED);
                d.embark_ticks = 0;
            } else {
                advance_action(ACTION_211_TRANSPORT_SHIP_CREATED);
            }
        }
        break;

    case ACTION_215_TRANSPORT_SHIP_LEAVING:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            // Empty arrival at the home dock → moor; otherwise anchor
            // (landing / reposition / return to a non-dock source_tile).
            tile2i home_dock = tile2i::invalid;
            if (wharf) {
                home_dock = wharf->get_water_access_tiles().point_a;
            }
            if (!has_troops() && home_dock.valid() && base.tile == home_dock) {
                advance_action(ACTION_213_TRANSPORT_SHIP_MOORED);
                if (b && b->id) {
                    b->set_figure(BUILDING_SLOT_BOAT, &base);
                }
            } else {
                advance_action(ACTION_214_TRANSPORT_SHIP_ANCHORED);
            }
            d.embark_ticks = 0;
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            tile2i home_dock = tile2i::invalid;
            if (wharf) {
                home_dock = wharf->get_water_access_tiles().point_a;
            }
            if (!has_troops() && home_dock.valid() && base.tile == home_dock) {
                advance_action(ACTION_213_TRANSPORT_SHIP_MOORED);
                if (b && b->id) {
                    b->set_figure(BUILDING_SLOT_BOAT, &base);
                }
            } else {
                advance_action(ACTION_214_TRANSPORT_SHIP_ANCHORED);
                // Could not reach armed landing — unload here if shore exists, else idle loaded.
                if (has_troops() && d.landing_x >= 0 && d.landing_y >= 0) {
                    tile2i shore = transport_find_shore_tile(base.tile);
                    if (shore.valid()) {
                        d.disembark_x = shore.x();
                        d.disembark_y = shore.y();
                    } else {
                        d.landing_x = -1;
                        d.landing_y = -1;
                        d.disembark_x = -1;
                        d.disembark_y = -1;
                    }
                }
            }
            d.embark_ticks = 0;
        }
        break;

    case ACTION_214_TRANSPORT_SHIP_ANCHORED: {
        // Empty ship already sitting on the home dock → moor (covers edge paths
        // that anchored instead of mooring, and frees the embark UI).
        if (!has_troops() && wharf) {
            tile2i home_dock = wharf->get_water_access_tiles().point_a;
            if (home_dock.valid() && base.tile == home_dock) {
                advance_action(ACTION_213_TRANSPORT_SHIP_MOORED);
                if (b && b->id) {
                    b->set_figure(BUILDING_SLOT_BOAT, &base);
                }
                d.embark_ticks = 0;
                break;
            }
        }

        if (d.phase == 1 && has_troops()) {
            // Loading at shore — same embark timer as moored, never auto-unload mid-board.
            d.embark_ticks++;
            if (d.embark_ticks >= TRANSPORT_EMBARK_TICKS) {
                d.phase = 2;
                d.embark_ticks = 0;
            }
        } else if (has_troops() && d.phase == 2
                   && d.landing_x >= 0 && d.landing_y >= 0) {
            // Auto-unload only when sail_to_landing armed a trip. Do not invent a
            // shore from the hull — that would dump after embark-at-shore or a plain move.
            tile2i pending_disembark(d.disembark_x, d.disembark_y);
            if (!transport_land_ok(pending_disembark)) {
                tile2i shore = transport_find_shore_tile(base.tile);
                if (shore.valid()) {
                    d.disembark_x = shore.x();
                    d.disembark_y = shore.y();
                    pending_disembark = shore;
                }
            }
            if (transport_land_ok(pending_disembark)) {
                d.embark_ticks++;
                if (d.embark_ticks >= TRANSPORT_DISEMBARK_TICKS) {
                    disembark_troops();
                    if (has_troops()) {
                        // Unload failed (terrain changed mid-timer) — retry next cycle.
                        d.embark_ticks = 0;
                    } else {
                        // Prefer home dock over a stale embark-shore source_tile.
                        tile2i home_dock = tile2i::invalid;
                        if (wharf) {
                            home_dock = wharf->get_water_access_tiles().point_a;
                        }
                        if (home_dock.valid()) {
                            base.destination_tile = home_dock;
                            base.source_tile = home_dock;
                            advance_action(ACTION_215_TRANSPORT_SHIP_LEAVING);
                            route_remove();
                        } else if (base.source_tile.valid()) {
                            base.destination_tile = base.source_tile;
                            advance_action(ACTION_215_TRANSPORT_SHIP_LEAVING);
                            route_remove();
                        } else {
                            // No home dock remembered — stay ANCHORED (never MOOR mid-water).
                            advance_action(ACTION_214_TRANSPORT_SHIP_ANCHORED);
                        }
                    }
                }
            }
        }
        // Empty ANCHORED / loaded idle (no armed landing): wait for player orders.
        break;
    }

    case ACTION_213_TRANSPORT_SHIP_MOORED:
        if (d.phase == 1 && has_troops()) {
            d.embark_ticks++;
            if (d.embark_ticks >= TRANSPORT_EMBARK_TICKS) {
                d.phase = 2;
                d.embark_ticks = 0;
            }
        }
        break;
    }
}

void figure_transport_ship::kill() {
    before_poof();
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
    pcstr anim_key = "swim";
    switch (action_state()) {
    case ACTION_215_TRANSPORT_SHIP_LEAVING: anim_key = "swim"; break;
    case ACTION_214_TRANSPORT_SHIP_ANCHORED: anim_key = "idle"; break;
    case ACTION_212_TRANSPORT_SHIP_GOING_TO_WHARF: anim_key = "swim"; break;
    case ACTION_211_TRANSPORT_SHIP_CREATED: anim_key = "idle"; break;
    case ACTION_213_TRANSPORT_SHIP_MOORED: anim_key = "idle"; break;
    }

    image_set_animation(anim_key);
}

void __transport_ship_embark(int ship_id, int formation_id) {
    figure *f = figure_get(ship_id);
    if (!f) {
        return;
    }

    figure_transport_ship *ship = smart_cast<figure_transport_ship>(f);
    if (ship) {
        ship->embark_formation(formation_id);
    }
}
ANK_FUNCTION_2(__transport_ship_embark)

void __transport_ship_sail_to(int ship_id, int x, int y) {
    figure *f = figure_get(ship_id);
    if (!f) {
        return;
    }

    figure_transport_ship *ship = smart_cast<figure_transport_ship>(f);
    if (ship) {
        ship->sail_to_landing(tile2i(x, y));
    }
}
ANK_FUNCTION_3(__transport_ship_sail_to)

int __transport_ship_has_troops(int ship_id) {
    figure *f = figure_get(ship_id);
    if (!f) {
        return 0;
    }

    figure_transport_ship *ship = smart_cast<figure_transport_ship>(f);
    return ship && ship->has_troops() ? 1 : 0;
}
ANK_FUNCTION_1(__transport_ship_has_troops)
