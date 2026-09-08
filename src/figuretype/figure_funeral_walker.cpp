#include "figuretype/figure_funeral_walker.h"

#include "building/monuments.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "figure/figure.h"
#include "grid/road_access.h"
#include "grid/terrain.h"
#include "js/js_game.h"
#include "scenario/map.h"
#include "scenario/scenario.h"

const e_funeral_walker_action_tokens_t ANK_CONFIG_ENUM(e_funeral_walker_action_tokens)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_funeral_walker);

namespace {

tile2i map_edge_spawn_tile() {
    scenario_map_init_entry_exit();
    tile2i t = scenario_map_entry();
    if (t.valid()) {
        return t;
    }
    return tile2i(g_scenario.map.width - 1, g_scenario.map.height / 2);
}

tile2i resolve_entry_tile() {
    tile2i t = g_city.map.entry_point;
    if (t.valid()) {
        return t;
    }
    t = g_city.map.exit_point;
    if (t.valid()) {
        return t;
    }
    return map_edge_spawn_tile();
}

// Road tile the walker should path to. Never returns a non-road footprint tile —
// finished monuments mark their footprint blocked for citizen routing.
tile2i resolve_tomb_road_destination(building &tomb) {
    if (auto *m = tomb.dcast_monument()) {
        tile2i ap = m->access_point();
        if (ap.valid()) {
            if (map_terrain_is(ap, TERRAIN_ROAD | TERRAIN_FERRY_ROUTE)) {
                return ap;
            }
            // Mastaba entrance is often just outside; mausoleum AP sits on footprint.
            tile2i near = map_closest_road_within_radius(ap, 1, 2);
            if (!near.valid()) {
                near = map_closest_road_within_radius(ap, 1, 6);
            }
            if (near.valid()) {
                return near;
            }
        }
    }

    if (tomb.has_road_access && tomb.road_access.valid()
        && map_terrain_is(tomb.road_access, TERRAIN_ROAD | TERRAIN_FERRY_ROUTE)) {
        return tomb.road_access;
    }

    // Mastaba/pyramid main->size is often only a 2×2 part — avoid it as footprint.
    // Prefer map_get_road_access_tile when size looks like a real footprint.
    if (tomb.size >= 3) {
        tile2i access = map_get_road_access_tile(tomb.tile, tomb.size);
        if (access.valid()) {
            return access;
        }
    }

    tile2i near = map_closest_road_within_radius(tomb.tile, 1, 8);
    if (near.valid()) {
        return near;
    }

    return tile2i::invalid;
}

bool tomb_has_road_access(building &tomb) {
    return resolve_tomb_road_destination(tomb).valid();
}

bool is_active_funeral_action(int action) {
    return action == ACTION_0_FUNERAL_CREATED
        || action == ACTION_1_FUNERAL_GOING_TO_TOMB
        || action == ACTION_2_FUNERAL_ARRIVED;
}

// Revive an inert slot targeting this tomb (action 0 / unknown) instead of spawning a duplicate.
figure *find_inert_funeral_for_tomb(building_id tomb_id) {
    if (!tomb_id) {
        return nullptr;
    }
    for (figure *f : map_figures()) {
        if (!f->is_alive() || f->type != FIGURE_FUNERAL_WALKER) {
            continue;
        }
        if (is_active_funeral_action(f->action_state) || f->action_state == ACTION_3_FUNERAL_ABORT
            || f->action_state == FIGURE_ACTION_149_CORPSE) {
            continue;
        }
        if (f->destination_building_id == tomb_id
            || figure_funeral_walker(f).runtime_data().target_tomb_id == tomb_id) {
            return f;
        }
    }
    return nullptr;
}

} // namespace

bool figure_funeral_walker::is_burial_tomb(building &b) {
    return building_monument_is_finished_burial_tomb(b);
}

bool figure_funeral_walker::city_burial_provisions_complete() {
    for (int r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
        const auto &bp = g_scenario.monuments.burial_provisions[r];
        if (bp.dispatched < bp.required) {
            return false;
        }
    }
    return true;
}

bool figure_funeral_walker::tomb_needs_funeral(building &b) {
    if (!is_burial_tomb(b)) {
        return false;
    }
    auto *m = b.dcast_monument();
    return m && !m->has_funeral_done();
}

bool figure_funeral_walker::tomb_has_active_funeral(building_id tomb_id) {
    if (!tomb_id) {
        return false;
    }
    for (figure *f : map_figures()) {
        if (!f->is_alive() || f->type != FIGURE_FUNERAL_WALKER) {
            continue;
        }
        // Ignore inert / unknown action slots — they must not block daily respawn.
        if (!is_active_funeral_action(f->action_state)) {
            continue;
        }
        if (f->destination_building_id == tomb_id) {
            return true;
        }
        // CREATED may set destination on first tick — also check runtime target.
        if (figure_funeral_walker(f).runtime_data().target_tomb_id == tomb_id) {
            return true;
        }
    }
    return false;
}

tile2i figure_funeral_walker::tomb_destination_tile(building &tomb) {
    // Prefer a road tile near the entrance so finished monuments (blocked footprint)
    // remain reachable. Never prefer a blocked access_point over road_access.
    tile2i road = resolve_tomb_road_destination(tomb);
    if (road.valid()) {
        return road;
    }

    // force_ignore_road / no-road maps: still need a non-empty destination.
    if (auto *m = tomb.dcast_monument()) {
        tile2i ap = m->access_point();
        if (ap.valid()) {
            return ap;
        }
    }
    if (tomb.has_road_access && tomb.road_access.valid()) {
        return tomb.road_access;
    }
    tile2i dest = tomb.access_tile();
    if (dest.valid()) {
        return dest;
    }
    return tomb.tile;
}

void figure_funeral_walker::on_create() {
    base.roam_wander_freely = true;
    base.allow_move_type = EMOVE_TERRAIN;
}

void figure_funeral_walker::on_post_load() {
    figure_impl::on_post_load();
    // Keep destination_building_id and runtime target in sync after save/load.
    auto &d = runtime_data();
    if (!d.target_tomb_id && base.destination_building_id) {
        d.target_tomb_id = base.destination_building_id;
    } else if (d.target_tomb_id && !base.destination_building_id) {
        base.destination_building_id = d.target_tomb_id;
    }

    building_id tomb_id = d.target_tomb_id ? d.target_tomb_id : base.destination_building_id;
    if (!tomb_id) {
        return;
    }

    const int a = action_state();
    const bool known = is_active_funeral_action(a) || a == ACTION_3_FUNERAL_ABORT
        || a == FIGURE_ACTION_149_CORPSE;
    if (!known) {
        // Recover type-only / zeroed action slots so they resume instead of idling
        // while still holding a tomb id (would otherwise block respawn forever).
        advance_action(ACTION_0_FUNERAL_CREATED);
    }

    if (is_active_funeral_action(action_state())) {
        building *tomb = building_get(tomb_id);
        if (tomb && tomb->is_valid()) {
            base.destination_tile = tomb_destination_tile(*tomb);
        }
    }
}

void figure_funeral_walker::figure_action() {
    switch (action_state()) {
    case ACTION_0_FUNERAL_CREATED: {
        building_id tomb_id = runtime_data().target_tomb_id;
        if (!tomb_id) {
            tomb_id = base.destination_building_id;
            runtime_data().target_tomb_id = tomb_id;
        }
        building *tomb = building_get(tomb_id);
        if (!tomb || !tomb->is_valid() || !tomb_needs_funeral(*tomb)) {
            poof();
            break;
        }

        set_destination(tomb->id);
        base.destination_tile = tomb_destination_tile(*tomb);
        route_remove();
        advance_action(ACTION_1_FUNERAL_GOING_TO_TOMB);
        break;
    }

    case ACTION_1_FUNERAL_GOING_TO_TOMB: {
        building_id tomb_id = runtime_data().target_tomb_id;
        if (!tomb_id) {
            tomb_id = base.destination_building_id;
            runtime_data().target_tomb_id = tomb_id;
        }
        building *tomb = building_get(tomb_id);
        if (!tomb || !tomb->is_valid()) {
            poof();
            break;
        }

        // do_goto advances to NEXT/FAIL itself; finish same tick when done.
        do_goto(base.destination_tile, TERRAIN_USAGE_ANY, ACTION_2_FUNERAL_ARRIVED,
                ACTION_3_FUNERAL_ABORT);
        if (action_state() == ACTION_2_FUNERAL_ARRIVED) {
            if (auto *m = tomb->dcast_monument()) {
                m->set_funeral_done(true);
            }
            poof();
        } else if (action_state() == ACTION_3_FUNERAL_ABORT) {
            // Leave funeral_done clear so daily try_spawn_all can retry.
            poof();
        }
        break;
    }

    case ACTION_2_FUNERAL_ARRIVED: {
        // Reached via set_action in tests, or if do_goto advanced without same-tick finish.
        building_id tomb_id = runtime_data().target_tomb_id;
        if (!tomb_id) {
            tomb_id = base.destination_building_id;
        }
        building *tomb = building_get(tomb_id);
        if (tomb && tomb->is_valid()) {
            if (auto *m = tomb->dcast_monument()) {
                m->set_funeral_done(true);
            }
        }
        poof();
        break;
    }

    case ACTION_3_FUNERAL_ABORT:
        poof();
        break;
    }
}

void figure_funeral_walker::update_animation() {
    xstring animkey = animkeys().walk;
    if (action_state(FIGURE_ACTION_149_CORPSE)) {
        animkey = animkeys().death;
    }
    image_set_animation(animkey);
}

int figure_funeral_walker::try_spawn_all(bool force_ignore_road) {
    if (!city_burial_provisions_complete()) {
        return 0;
    }

    int first_id = 0;
    buildings_valid_do([&](building &b) {
        if (!tomb_needs_funeral(b)) {
            return;
        }
        if (tomb_has_active_funeral(b.id)) {
            return;
        }
        if (!force_ignore_road && !tomb_has_road_access(b)) {
            return;
        }

        if (figure *inert = find_inert_funeral_for_tomb(b.id)) {
            figure_funeral_walker fw(inert);
            fw.runtime_data().target_tomb_id = b.id;
            fw.set_destination(b.id);
            fw.advance_action(ACTION_0_FUNERAL_CREATED);
            if (!first_id) {
                first_id = inert->id;
            }
            return;
        }

        tile2i spawn = resolve_entry_tile();
        if (!spawn.valid()) {
            return;
        }
        tile2i road = map_closest_road_within_radius(spawn, 1, 4);
        if (road.valid()) {
            spawn = road;
        }

        figure *f = figure_create(FIGURE_FUNERAL_WALKER, spawn, DIR_0_TOP_RIGHT);
        if (!f || !f->is_alive()) {
            return;
        }

        figure_funeral_walker fw(f);
        fw.runtime_data().target_tomb_id = b.id;
        fw.set_destination(b.id);
        fw.advance_action(ACTION_0_FUNERAL_CREATED);
        if (!first_id) {
            first_id = f->id;
        }
    });
    return first_id;
}
