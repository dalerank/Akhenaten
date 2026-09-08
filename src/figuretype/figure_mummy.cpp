#include "figuretype/figure_mummy.h"

#include "city/city.h"
#include "city/city_figures.h"
#include "city/city_message.h"
#include "core/random.h"
#include "figure/figure.h"
#include "game/simulation_time.h"
#include "grid/road_access.h"
#include "grid/terrain.h"
#include "js/js_game.h"
#include "scenario/map.h"
#include "scenario/scenario.h"

const e_mummy_action_tokens_t ANK_CONFIG_ENUM(e_mummy_action_tokens)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_mummy);

namespace {

constexpr int k_mummy_roam_days = 16;
constexpr int k_mummy_default_wave = 1;
constexpr int k_mummy_max_wave = 4;

int count_live_mummies() {
    int n = 0;
    for (figure *f : map_figures()) {
        if (f->is_alive() && f->type == FIGURE_MUMMY) {
            ++n;
        }
    }
    return n;
}

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

tile2i pick_spawn_tile() {
    tile2i spawn = resolve_entry_tile();
    if (!spawn.valid()) {
        return tile2i::invalid;
    }
    // Prefer streets (message: "walks the streets"); widen search if entry is off-road.
    tile2i road = map_closest_road_within_radius(spawn, 1, 6);
    if (!road.valid()) {
        road = map_closest_road_within_radius(spawn, 1, 16);
    }
    if (road.valid()) {
        return road;
    }
    return spawn;
}

} // namespace

void figure_mummy::on_create() {
    base.roam_wander_freely = true;
    base.max_roam_length = 480;
    // Soldiers target is_enemy() || is_criminal(); params().is_enemy sets enemy flag at create.
    base.flags |= e_figure_flag_criminal;
    // figure_create leaves action_state=0; start roam even if caller skips spawn_wave.
    advance_action(ACTION_0_MUMMY_CREATED);
}

void figure_mummy::figure_action() {
    // action_perform already advances DYING corpses — do not double-tick, and never melee.
    if (!base.is_alive()) {
        return;
    }

    // Melee lock (same pattern as enemy sword).
    if (base.opponent_id > 0 && !figure_get(base.opponent_id)->is_dead()) {
        base.set_flag(e_figure_flag_inattack);
        base.figure_combat_handle_attack();
        return;
    }

    switch (action_state()) {
    case ACTION_0_MUMMY_CREATED:
        // spawn_wave may set wait_ticks > 0 to stagger figures.
        if (base.wait_ticks > 0) {
            base.wait_ticks--;
            break;
        }
        runtime_data().roam_ticks = 0;
        advance_action(ACTION_1_MUMMY_ROAMING);
        break;

    case ACTION_1_MUMMY_ROAMING:
        if (map_terrain_is(tile(), TERRAIN_ROAD)) {
            base.roam_ticks(1);
        } else {
            // Off-road: walk toward nearest street instead of idling until despawn.
            tile2i road = map_closest_road_within_radius(tile(), 1, 12);
            if (road.valid() && road != tile()) {
                base.destination_tile = road;
                base.move_ticks(1);
                if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
                    route_remove();
                }
            }
        }
        runtime_data().roam_ticks++;
        if (runtime_data().roam_ticks > simulation_time_t::ticks_in_day * k_mummy_roam_days) {
            poof();
        }
        break;
    }
}

void figure_mummy::update_animation() {
    xstring animkey = animkeys().walk;
    if (action_state(FIGURE_ACTION_149_CORPSE) || !base.is_alive()) {
        animkey = animkeys().death;
    } else if (base.in_attack()) {
        animkey = animkeys().attack;
    }
    image_set_animation(animkey);
}

void figure_mummy::acquire_attack() {
    // Default acquire_attack() is empty — without the flag, tile-overlap combat
    // re-enters every step and never locks the mummy into handle_attack.
    base.set_flag(e_figure_flag_inattack);
}

int figure_mummy::spawn_wave(int count) {
    if (count < 1) {
        count = k_mummy_default_wave;
    }
    if (count > k_mummy_max_wave) {
        count = k_mummy_max_wave;
    }

    const int room = k_mummy_max_wave - count_live_mummies();
    if (room <= 0) {
        return 0;
    }
    if (count > room) {
        count = room;
    }

    tile2i base_tile = pick_spawn_tile();
    if (!base_tile.valid()) {
        return 0;
    }

    int first_id = 0;
    int spawned = 0;
    for (int i = 0; i < count; ++i) {
        tile2i spawn = base_tile;
        if (i > 0) {
            tile2i alt = map_closest_road_within_radius(base_tile, 1, 4 + i);
            if (alt.valid()) {
                spawn = alt;
            }
        }

        figure *f = figure_create(FIGURE_MUMMY, spawn, DIR_4_BOTTOM_LEFT);
        if (!f || !f->is_alive()) {
            continue;
        }
        f->advance_action(ACTION_0_MUMMY_CREATED);
        f->wait_ticks = 4 + (random_byte() & 0x7);
        if (!first_id) {
            first_id = f->id;
        }
        ++spawned;
    }

    if (spawned > 0) {
        // One popup per wave (message id 496).
        messages::popup("message_mummy_attacks", 0, 0);
    }
    return first_id;
}
