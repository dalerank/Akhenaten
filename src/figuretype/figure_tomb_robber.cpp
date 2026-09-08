#include "figuretype/figure_tomb_robber.h"

#include "building/monuments.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "city/city_message.h"
#include "city/city_warnings.h"
#include "city/ratings.h"
#include "core/calc.h"
#include "core/random.h"
#include "figure/figure.h"
#include "game/game_events.h"
#include "game/resource.h"
#include "game/simulation_time.h"
#include "grid/road_access.h"
#include "js/js_game.h"
#include "scenario/map.h"
#include "scenario/scenario.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_tomb_robber);

namespace {

constexpr int k_max_active_tomb_robbers = 2;
constexpr int k_steal_kingdom_penalty = 10;
constexpr int k_preexisting_kingdom_penalty = 25;
constexpr int k_professional_dispatched_min = 20;
constexpr int k_professional_roll = 24; // 1/24 monthly

int count_active_tomb_robbers() {
    int n = 0;
    for (figure *f : map_figures()) {
        if (f->is_alive() && f->type == FIGURE_TOMB_ROBER) {
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

tile2i resolve_exit_tile() {
    tile2i t = g_city.map.exit_point;
    if (t.valid()) {
        return t;
    }
    t = g_city.map.entry_point;
    if (t.valid()) {
        return t;
    }
    scenario_map_init_entry_exit();
    t = scenario_map_exit();
    if (t.valid()) {
        return t;
    }
    return map_edge_spawn_tile();
}

tile2i tomb_destination_tile(building *tomb) {
    tile2i dest = tomb->tile;
    if (auto *m = tomb->dcast_monument()) {
        dest = m->access_point();
        if (!dest.valid()) {
            dest = tomb->access_tile();
        }
    } else {
        dest = tomb->access_tile();
    }
    if (!dest.valid()) {
        dest = tomb->tile;
    }
    return dest;
}

bool monument_is_preexisting(building &b) {
    auto *m = b.dcast_monument();
    return m && m->is_preexisting();
}

int create_one_robber(tile2i spawn) {
    if (!spawn.valid()) {
        return 0;
    }

    tile2i road = map_closest_road_within_radius(spawn, 1, 4);
    if (road.valid()) {
        spawn = road;
    }

    figure *f = figure_create(FIGURE_TOMB_ROBER, spawn, DIR_4_BOTTOM_LEFT);
    if (!f || !f->is_alive()) {
        return 0;
    }

    f->advance_action(ACTION_120_TOMB_ROBBER_CREATED);
    f->wait_ticks = 10 + (random_byte() & 0xf);
    g_city.sentiment.criminals++;
    g_city.ratings.monument_record_criminal();
    g_city.figures.security_breach_duration = 10;
    return f->id;
}

} // namespace

bool figure_tomb_robber::city_has_stealable_provisions() {
    burial_provisions_migrate_city_pool_to_tombs();
    for (int r = 0; r < RESOURCES_MAX; ++r) {
        if (g_scenario.monuments.burial_provisions[r].dispatched > 0) {
            return true;
        }
    }
    return false;
}

int figure_tomb_robber::city_dispatched_loads_total() {
    int total = 0;
    for (int r = 0; r < RESOURCES_MAX; ++r) {
        total += g_scenario.monuments.burial_provisions[r].dispatched;
    }
    return total;
}

building *figure_tomb_robber::find_target_tomb(bool *out_threat_only) {
    if (out_threat_only) {
        *out_threat_only = false;
    }

    burial_provisions_migrate_city_pool_to_tombs();

    building *best_steal = nullptr;
    building *best_steal_empty = nullptr;
    building *best_threat = nullptr;
    int best_steal_dist = 0x7fffffff;
    int best_steal_empty_dist = 0x7fffffff;
    int best_threat_dist = 0x7fffffff;
    tile2i origin = resolve_entry_tile();

    buildings_valid_do([&](building &b) {
        if (!building_monument_is_finished_burial_tomb(b)) {
            return;
        }
        const int d = calc_maximum_distance(origin, b.tile);
        if (monument_is_preexisting(b)) {
            if (d < best_threat_dist) {
                best_threat_dist = d;
                best_threat = &b;
            }
            return;
        }
        auto *m = b.dcast_monument();
        const bool has_stock = m && m->burial_stock_total() > 0;
        if (has_stock) {
            if (d < best_steal_dist) {
                best_steal_dist = d;
                best_steal = &b;
            }
        } else if (d < best_steal_empty_dist) {
            best_steal_empty_dist = d;
            best_steal_empty = &b;
        }
    });

    // Steal player provisions first. Preexisting sealed tombs are threat-only
    // and must not shadow a finished tomb that still has burial_stock.
    if (best_steal) {
        return best_steal;
    }
    if (best_threat) {
        if (out_threat_only) {
            *out_threat_only = true;
        }
        return best_threat;
    }
    return best_steal_empty;
}

void figure_tomb_robber::on_create() {
    base.flags |= e_figure_flag_criminal;
}

void figure_tomb_robber::on_post_load() {
    base.flags |= e_figure_flag_criminal;
}

bool figure_tomb_robber::commit_plunder() {
    auto &rd = runtime_data();
    if (rd.stole) {
        return false;
    }

    building *tomb = building_get(rd.target_tomb_id);
    if (!tomb || !tomb->is_valid()) {
        return false;
    }

    if (rd.threat_only || monument_is_preexisting(*tomb)) {
        rd.stole = 1;
        g_city.kingdome.change(-k_preexisting_kingdom_penalty);
        events::emit(event_city_warning{ "#tomb_robbers_plundered" });
        return true;
    }

    burial_provisions_migrate_city_pool_to_tombs();

    auto *mon = tomb->dcast_monument();
    if (!mon) {
        return false;
    }

    e_resource stolen = RESOURCE_NONE;
    for (int r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
        auto res = (e_resource)r;
        if (mon->burial_stock(res) > 0 && mon->take_burial_stock(res, 1)) {
            stolen = res;
            break;
        }
    }

    if (stolen == RESOURCE_NONE) {
        return false;
    }

    // Keep city dispatched == sum of tomb ledgers (no city-only steal).
    burial_provisions_sync_city_dispatched();
    rd.stole = 1;
    g_city.kingdome.change(-k_steal_kingdom_penalty);
    events::emit(event_city_warning{ "#tomb_robbers_stole_provisions" });
    return true;
}

bool figure_tomb_robber::arrest(bool force) {
    if (!base.is_alive()) {
        return false;
    }
    if (action_state() == ACTION_124_TOMB_ROBBER_CAUGHT) {
        return true;
    }
    // After a successful steal, fleeing means goods are gone — no detain.
    // Threat-only (preexisting) never took stock; constable may still catch.
    if (action_state() == ACTION_123_TOMB_ROBBER_FLEEING && runtime_data().stole
        && !runtime_data().threat_only) {
        return false;
    }

    // TEMP ~75% catch; force for tests.
    if (!force && (random_byte() % 100) >= 75) {
        return false;
    }

    advance_action(ACTION_124_TOMB_ROBBER_CAUGHT);
    events::emit(event_city_warning{ "#tomb_robber_caught" });
    return true;
}

void figure_tomb_robber::figure_action() {
    switch (action_state()) {
    case ACTION_120_TOMB_ROBBER_CREATED: {
        bool threat_only = false;
        building *tomb = find_target_tomb(&threat_only);
        if (!tomb) {
            advance_action(ACTION_123_TOMB_ROBBER_FLEEING);
            break;
        }
        // Steal path needs dispatched provisions; preexisting threat-only does not.
        if (!threat_only && !city_has_stealable_provisions()) {
            advance_action(ACTION_123_TOMB_ROBBER_FLEEING);
            break;
        }

        runtime_data().target_tomb_id = tomb->id;
        runtime_data().threat_only = threat_only ? 1 : 0;
        set_destination(tomb->id);

        base.destination_tile = tomb_destination_tile(tomb);
        route_remove();
        advance_action(ACTION_121_TOMB_ROBBER_GOING_TO_TOMB);
        break;
    }

    case ACTION_121_TOMB_ROBBER_GOING_TO_TOMB: {
        building *tomb = building_get(runtime_data().target_tomb_id);
        if (!tomb || !tomb->is_valid()) {
            advance_action(ACTION_123_TOMB_ROBBER_FLEEING);
            break;
        }

        if (do_goto(base.destination_tile, TERRAIN_USAGE_ANY, ACTION_122_TOMB_ROBBER_STEALING,
                    ACTION_123_TOMB_ROBBER_FLEEING)) {
            base.wait_ticks = 0;
            advance_action(ACTION_122_TOMB_ROBBER_STEALING);
        }
        break;
    }

    case ACTION_122_TOMB_ROBBER_STEALING: {
        base.wait_ticks++;
        if (base.wait_ticks > simulation_time_t::ticks_in_day / 2) {
            commit_plunder();
            advance_action(ACTION_123_TOMB_ROBBER_FLEEING);
        }
        break;
    }

    case ACTION_123_TOMB_ROBBER_FLEEING: {
        tile2i exit = resolve_exit_tile();
        if (do_goto(exit, TERRAIN_USAGE_ANY)) {
            poof();
        }
        break;
    }

    case ACTION_124_TOMB_ROBBER_CAUGHT:
        poof();
        break;
    }
}

void figure_tomb_robber::update_animation() {
    xstring animkey = animkeys().walk;
    if (action_state(FIGURE_ACTION_149_CORPSE)) {
        animkey = animkeys().death;
    }
    image_set_animation(animkey);
}

int figure_tomb_robber::try_spawn(bool force_gates) {
    if (count_active_tomb_robbers() >= k_max_active_tomb_robbers) {
        return 0;
    }
    if (!city_has_stealable_provisions()) {
        return 0;
    }
    if (!find_target_tomb()) {
        return 0;
    }

    if (!force_gates) {
        const int sentiment = g_city.sentiment.value;
        if (sentiment >= 30) {
            return 0;
        }
        if (random_byte() < sentiment + 50) {
            return 0;
        }
    }

    return create_one_robber(resolve_entry_tile());
}

int figure_tomb_robber::spawn_wave(int count) {
    if (count <= 0) {
        return 0;
    }

    const int room = k_max_active_tomb_robbers - count_active_tomb_robbers();
    if (room <= 0) {
        return 0;
    }

    bool threat_only = false;
    if (!find_target_tomb(&threat_only)) {
        return 0;
    }
    if (!threat_only && !city_has_stealable_provisions()) {
        return 0;
    }

    count = std::min(count, room);
    tile2i base_tile = resolve_entry_tile();
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
        const int id = create_one_robber(spawn);
        if (!id) {
            continue;
        }
        if (!first_id) {
            first_id = id;
        }
        ++spawned;
    }

    if (spawned > 0) {
        messages::popup("message_crime_wave", 0, 0);
    }
    return first_id;
}

int figure_tomb_robber::try_professional_wave() {
    if (city_dispatched_loads_total() < k_professional_dispatched_min) {
        return 0;
    }
    if ((random_byte() % k_professional_roll) != 0) {
        return 0;
    }
    return spawn_wave(2);
}
