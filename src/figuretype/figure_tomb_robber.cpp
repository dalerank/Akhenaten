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
#include "empire/trade_prices.h"
#include "figure/figure.h"
#include "game/game.h"
#include "game/game_config.h"
#include "game/game_events.h"
#include "game/resource.h"
#include "game/simulation_time.h"
#include "grid/road_access.h"
#include "js/js_game.h"
#include "scenario/map.h"
#include "scenario/scenario.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_tomb_robber);

namespace {

constexpr int k_max_active_tomb_robbers = 2;
constexpr int k_steal_kingdom_penalty_remake = 10;
constexpr int k_preexisting_kingdom_penalty_remake = 25;
constexpr int k_professional_dispatched_min = 20;
constexpr int k_professional_roll = 24; // 1/24 monthly

// OG difficulty_rating for unfinished tombs (Very Easy … Very Hard).
constexpr int k_og_kingdom_by_difficulty[5] = {2, 4, 6, 8, 10};

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

bool is_mastaba_or_mausoleum(e_building_type t) {
    switch (t) {
    case BUILDING_MAUSOLEUM:
    case BUILDING_MAUSOLEUM_0:
    case BUILDING_MAUSOLEUM_1:
    case BUILDING_MAUSOLEUM_2:
    case BUILDING_SMALL_MASTABA:
    case BUILDING_MEDIUM_MASTABA:
    case BUILDING_LARGE_MASTABA:
        return true;
    default:
        return false;
    }
}

bool is_royal_tomb_type(e_building_type t) {
    switch (t) {
    case BUILDING_SMALL_ROYAL_TOMB:
    case BUILDING_MEDIUM_ROYAL_TOMB:
    case BUILDING_LARGE_ROYAL_TOMB:
    case BUILDING_GRAND_ROYAL_TOMB:
    case BUILDING_MEDIUM_ROYAL_BURIAL_TOMB:
    case BUILDING_LARGE_ROYAL_BURIAL_TOMB:
    case BUILDING_GRAND_ROYAL_BURIAL_TOMB:
        return true;
    default:
        return false;
    }
}

bool is_pyramid_type(e_building_type t) {
    return t == BUILDING_PYRAMID || t == BUILDING_PYRAMID_COMPLEX;
}

bool is_og_tomb_candidate(building &b, bool has_provisions) {
    if (!b.is_valid() || !b.is_main()) {
        return false;
    }
    if (!b.is_monument() || building_monument_is_non_tomb_type(b.type)) {
        return false;
    }

    auto *m = b.dcast_monument();
    if (!m) {
        return false;
    }

    const bool unfinished = m->is_unfinished();
    if (is_pyramid_type(b.type)) {
        return has_provisions;
    }
    if (is_mastaba_or_mausoleum(b.type) || is_royal_tomb_type(b.type)) {
        return unfinished || has_provisions;
    }
    // Other burial tombs (finished with provisions): allow when provisions exist.
    return has_provisions && m->is_finished();
}

bool city_has_unfinished_burial_tomb() {
    bool found = false;
    buildings_valid_do([&](building &b) {
        if (found || !b.is_main() || !b.is_monument()) {
            return;
        }
        if (building_monument_is_non_tomb_type(b.type)) {
            return;
        }
        if (!is_mastaba_or_mausoleum(b.type) && !is_royal_tomb_type(b.type)) {
            return;
        }
        auto *m = b.dcast_monument();
        if (m && m->is_unfinished()) {
            found = true;
        }
    });
    return found;
}

int og_kingdom_penalty(bool unfinished) {
    const int diff = std::clamp<int>(game_difficulty(), 0, 4);
    const int full = k_og_kingdom_by_difficulty[diff];
    return unfinished ? full : full / 2;
}

bool steal_highest_price_provision(building &tomb) {
    burial_provisions_migrate_city_pool_to_tombs();
    auto *mon = tomb.dcast_monument();
    if (!mon) {
        return false;
    }

    e_resource best = RESOURCE_NONE;
    int best_price = 0;
    for (int r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
        auto res = (e_resource)r;
        if (mon->burial_stock(res) <= 0) {
            continue;
        }
        const int price = trade_price_buy(res);
        if (price > best_price) {
            best_price = price;
            best = res;
        }
    }
    if (best == RESOURCE_NONE || !mon->take_burial_stock(best, 1)) {
        return false;
    }
    burial_provisions_sync_city_dispatched();
    return true;
}

int create_one_robber(tile2i spawn, bool remake) {
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

    if (remake) {
        f->advance_action(ACTION_120_TOMB_ROBBER_CREATED);
    } else {
        f->advance_action(ACTION_8_TOMB_ROBBER_WAITING);
    }
    f->wait_ticks = 10 + (random_byte() & 0xf);
    g_city.sentiment.criminals++;
    g_city.ratings.monument_record_criminal();
    g_city.figures.security_breach_duration = 10;
    return f->id;
}

building *find_target_remake(bool *out_threat_only) {
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

building *find_target_og(tile2i origin, bool *out_unfinished) {
    if (out_unfinished) {
        *out_unfinished = false;
    }

    burial_provisions_migrate_city_pool_to_tombs();
    const bool has_provisions = figure_tomb_robber::city_has_stealable_provisions();

    building *best = nullptr;
    int best_dist = 0x7fffffff;
    bool best_unfinished = false;

    if (!origin.valid()) {
        origin = resolve_entry_tile();
    }

    buildings_valid_do([&](building &b) {
        if (!is_og_tomb_candidate(b, has_provisions)) {
            return;
        }
        auto *m = b.dcast_monument();
        const bool unfinished = m && m->is_unfinished();
        const int d = calc_maximum_distance(origin, b.tile);
        if (d < best_dist) {
            best_dist = d;
            best = &b;
            best_unfinished = unfinished;
        }
    });

    if (best && out_unfinished) {
        *out_unfinished = best_unfinished;
    }
    return best;
}

void figure_action_remake(figure_tomb_robber &self) {
    auto &base = self.base;
    switch (self.action_state()) {
    case ACTION_120_TOMB_ROBBER_CREATED: {
        bool threat_only = false;
        building *tomb = figure_tomb_robber::find_target_tomb(&threat_only);
        if (!tomb) {
            self.advance_action(ACTION_123_TOMB_ROBBER_FLEEING);
            break;
        }
        if (!threat_only && !figure_tomb_robber::city_has_stealable_provisions()) {
            self.advance_action(ACTION_123_TOMB_ROBBER_FLEEING);
            break;
        }

        self.runtime_data().target_tomb_id = tomb->id;
        self.runtime_data().threat_only = threat_only ? 1 : 0;
        self.set_destination(tomb->id);

        base.destination_tile = tomb_destination_tile(tomb);
        self.route_remove();
        self.advance_action(ACTION_121_TOMB_ROBBER_GOING_TO_TOMB);
        break;
    }

    case ACTION_121_TOMB_ROBBER_GOING_TO_TOMB: {
        building *tomb = building_get(self.runtime_data().target_tomb_id);
        if (!tomb || !tomb->is_valid()) {
            self.advance_action(ACTION_123_TOMB_ROBBER_FLEEING);
            break;
        }

        if (self.do_goto(base.destination_tile, TERRAIN_USAGE_ANY, ACTION_122_TOMB_ROBBER_STEALING,
                         ACTION_123_TOMB_ROBBER_FLEEING)) {
            base.wait_ticks = 0;
            self.advance_action(ACTION_122_TOMB_ROBBER_STEALING);
        }
        break;
    }

    case ACTION_122_TOMB_ROBBER_STEALING: {
        base.wait_ticks++;
        if (base.wait_ticks > simulation_time_t::ticks_in_day / 2) {
            self.commit_plunder();
            self.advance_action(ACTION_123_TOMB_ROBBER_FLEEING);
        }
        break;
    }

    case ACTION_123_TOMB_ROBBER_FLEEING: {
        tile2i exit = resolve_exit_tile();
        if (self.do_goto(exit, TERRAIN_USAGE_ANY)) {
            self.poof();
        }
        break;
    }

    case ACTION_124_TOMB_ROBBER_CAUGHT:
        self.poof();
        break;

    default:
        self.advance_action(ACTION_120_TOMB_ROBBER_CREATED);
        break;
    }
}

void figure_action_og(figure_tomb_robber &self) {
    auto &base = self.base;
    base.terrain_usage = TERRAIN_USAGE_PREFER_ROADS;

    switch (self.action_state()) {
    case FIGURE_ACTION_149_CORPSE:
        if (!self.runtime_data().kill_bonus_done && base.opponent_id > 0) {
            self.runtime_data().kill_bonus_done = 1;
            g_city.kingdome.change(1);
            events::emit(event_city_warning{"#tomb_robber_caught"});
        }
        break;

    case ACTION_8_TOMB_ROBBER_WAITING:
        if (++base.wait_ticks <= 0x28) {
            break;
        }
        // fallthrough after wait — pick tomb
        [[fallthrough]];
    case ACTION_120_TOMB_ROBBER_CREATED: {
        // 120 kept for tests that force-start without waiting.
        bool unfinished = false;
        building *tomb = find_target_og(base.tile, &unfinished);
        if (!tomb) {
            self.poof();
            break;
        }
        self.runtime_data().target_tomb_id = tomb->id;
        self.runtime_data().threat_only = unfinished ? 1 : 0;
        self.set_destination(tomb->id);
        base.destination_tile = tomb_destination_tile(tomb);
        base.wait_ticks = 0;
        self.route_remove();
        self.advance_action(ACTION_9_TOMB_ROBBER_GOING_TO_TOMB);
        break;
    }

    case ACTION_9_TOMB_ROBBER_GOING_TO_TOMB:
    case ACTION_121_TOMB_ROBBER_GOING_TO_TOMB: {
        const int speed = std::max(1, (int)base.speed_multiplier) * 2;
        base.move_ticks(speed);
        if (self.direction() == DIR_FIGURE_NONE) {
            self.commit_plunder();
            self.poof();
        } else if (self.direction() == DIR_FIGURE_REROUTE || self.direction() == DIR_FIGURE_CAN_NOT_REACH) {
            self.poof();
        }
        break;
    }

    default: {
        // OG criminal_start: enter WAITING with random 0..9 wait.
        self.advance_action(ACTION_8_TOMB_ROBBER_WAITING);
        random_generate_next();
        base.wait_ticks = (int16_t)((random_byte() & 0x7f) % 10);
        break;
    }
    }
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

bool figure_tomb_robber::og_possible() {
    if (city_has_stealable_provisions()) {
        return true;
    }
    return city_has_unfinished_burial_tomb();
}

building *figure_tomb_robber::find_target_tomb(bool *out_threat_only, tile2i origin) {
    if (game_features::gameplay_change_tomb_robber_remake.to_bool()) {
        return find_target_remake(out_threat_only);
    }
    bool unfinished = false;
    building *t = find_target_og(origin, &unfinished);
    if (out_threat_only) {
        *out_threat_only = unfinished;
    }
    return t;
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

    if (game_features::gameplay_change_tomb_robber_remake.to_bool()) {
        if (rd.threat_only || monument_is_preexisting(*tomb)) {
            rd.stole = 1;
            g_city.kingdome.change(-k_preexisting_kingdom_penalty_remake);
            events::emit(event_city_warning{"#tomb_robbers_plundered"});
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

        burial_provisions_sync_city_dispatched();
        rd.stole = 1;
        g_city.kingdome.change(-k_steal_kingdom_penalty_remake);
        events::emit(event_city_warning{"#tomb_robbers_stole_provisions"});
        return true;
    }

    // --- OG plunder ---
    auto *mon = tomb->dcast_monument();
    const bool unfinished = mon && mon->is_unfinished();
    const int penalty = og_kingdom_penalty(unfinished);

    if (unfinished) {
        rd.stole = 1;
        g_city.kingdome.change(-penalty);
        if (is_royal_tomb_type(tomb->type)) {
            events::emit(event_city_warning{"#tomb_robbers_plundered"});
        } else {
            events::emit(event_city_warning{"#tomb_robbers_plundered"});
        }
        return true;
    }

    if (!steal_highest_price_provision(*tomb)) {
        // Finished tomb without stock: still apply half kingdom hit (OG pyramid/finished path
        // always hits kingdom after attempt; steal is best-effort).
        rd.stole = 1;
        g_city.kingdome.change(-penalty);
        events::emit(event_city_warning{"#tomb_robbers_stole_provisions"});
        return true;
    }

    rd.stole = 1;
    g_city.kingdome.change(-penalty);
    events::emit(event_city_warning{"#tomb_robbers_stole_provisions"});
    return true;
}

bool figure_tomb_robber::arrest(bool force) {
    if (!game_features::gameplay_change_tomb_robber_remake.to_bool()) {
        return false;
    }
    if (!base.is_alive()) {
        return false;
    }
    if (action_state() == ACTION_124_TOMB_ROBBER_CAUGHT) {
        return true;
    }
    if (action_state() == ACTION_123_TOMB_ROBBER_FLEEING && runtime_data().stole
        && !runtime_data().threat_only) {
        return false;
    }

    if (!force && (random_byte() % 100) >= 75) {
        return false;
    }

    advance_action(ACTION_124_TOMB_ROBBER_CAUGHT);
    events::emit(event_city_warning{"#tomb_robber_caught"});
    return true;
}

void figure_tomb_robber::figure_action() {
    if (game_features::gameplay_change_tomb_robber_remake.to_bool()) {
        figure_action_remake(*this);
        return;
    }
    figure_action_og(*this);
}

void figure_tomb_robber::update_animation() {
    xstring animkey = animkeys().walk;
    if (action_state(FIGURE_ACTION_149_CORPSE)) {
        animkey = animkeys().death;
    }
    image_set_animation(animkey);
}

int figure_tomb_robber::try_spawn(bool force_gates) {
    const bool remake = game_features::gameplay_change_tomb_robber_remake.to_bool();

    if (count_active_tomb_robbers() >= k_max_active_tomb_robbers) {
        return 0;
    }

    if (remake) {
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
        return create_one_robber(resolve_entry_tile(), true);
    }

    // OG helper (also used by tests): need a legal target.
    if (!og_possible() || !find_target_tomb()) {
        return 0;
    }
    if (!force_gates) {
        // House crime path is the real OG spawn; this monthly helper stays off unless forced.
        return 0;
    }
    return create_one_robber(resolve_entry_tile(), false);
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
    if (!threat_only && !city_has_stealable_provisions() && !og_possible()) {
        return 0;
    }

    const bool remake = game_features::gameplay_change_tomb_robber_remake.to_bool();
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
        const int id = create_one_robber(spawn, remake);
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
    if (!game_features::gameplay_change_tomb_robber_remake.to_bool()) {
        return 0;
    }
    if (city_dispatched_loads_total() < k_professional_dispatched_min) {
        return 0;
    }
    if ((random_byte() % k_professional_roll) != 0) {
        return 0;
    }
    return spawn_wave(2);
}
