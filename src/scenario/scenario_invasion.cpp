#include "scenario_invasion.h"

#include "building/destruction.h"
#include "city/city.h"
#include "city/city_figures.h"
#include "city/city_warnings.h"
#include "game/game_events.h"
#include "city/city_message.h"
#include "core/calc.h"
#include "core/random.h"
#include "empire/empire_object.h"
#include "figure/figure.h"
#include "figure/formation.h"
#include "figure/figure_names.h"
#include "figuretype/figure_enemy.h"
#include "figuretype/figure_enemy_transport.h"
#include "figuretype/figure_enemy_warship.h"
#include "game/difficulty.h"
#include "game/game.h"
#include "grid/grid.h"
#include "grid/terrain.h"
#include "grid/water.h"
#include "scenario/map.h"
#include "scenario/scenario.h"
#include "scenario/invasion_auto_resolve.h"
#include "dev/debug.h"
#include "core/log.h"
#include "core/svector.h"
#include "empire/empire.h"
#include "js/js_game.h"
#include "figure/enemy_army.h"
#include "scenario/scenario_event_manager.h"

#include <algorithm>

const e_attack_faction_tokens_t ANK_CONFIG_ENUM(e_attack_faction_tokens);
const e_invasion_spawn_kind_tokens_t ANK_CONFIG_ENUM(e_invasion_spawn_kind_tokens);

// Skip OG attack popup when auto-resolve already queued this seq (quick-battle message sent).
static void emit_local_invasion_attack_message(xstring msg_id, uint16_t seq, int grid_offset) {
    if (g_invasion_auto_resolve.is_seq_frozen(seq)) {
        return;
    }
    events::emit(event_message{ true, msg_id, seq, grid_offset, SOURCE_LOCATION });
}

e_formation_attack_type formation_attack_from_event_target(int invasion_attack_target) {
    // Pak EVENT_ATTACK_TARGET_* is 0..4; FORMATION_ATTACK_RANDOM is 5 (SIMPLE sits at 4).
    switch (invasion_attack_target) {
    case 0: // EVENT_ATTACK_TARGET_FOOD
        return FORMATION_ATTACK_FOOD_CHAIN;
    case 1: // EVENT_ATTACK_TARGET_VAULTS
        return FORMATION_ATTACK_GOLD_STORES;
    case 2: // EVENT_ATTACK_TARGET_BEST_BUILDINGS
        return FORMATION_ATTACK_BEST_BUILDINGS;
    case 3: // EVENT_ATTACK_TARGET_TROOPS
        return FORMATION_ATTACK_TROOPS;
    case 4: // EVENT_ATTACK_TARGET_RANDOM
    default:
        return FORMATION_ATTACK_RANDOM;
    }
}

declare_console_command_p(start_invasion) {
    invasion_opts_t opts;
    opts.mode = ATTACK_TYPE_ENEMIES;
    opts.enemy_type = (e_enemy_type)parse_integer_from<bstring32>(is); // 0 type, 1 kingdome, 2 seth natives
    opts.size = parse_integer_from<bstring32>(is);
    int tilex = parse_integer_from<bstring32>(is);
    int tiley = parse_integer_from<bstring32>(is);
    opts.invasion_point = { tilex, tiley };
    opts.invasion_id = 23;
    opts.want_destroy = parse_integer_from<bstring32>(is);
    opts.via_sea = parse_integer_from<bstring32>(is) != 0;
    opts.kind = (opts.enemy_type == ENEMY_3_EGYPTIAN) ? INVASION_KIND_PHARAOH : INVASION_KIND_FOREIGN;

    scenario_invasion_start(opts);

    events::emit(event_city_warning{ "Started invasion" });
}

declare_console_command_p(start_invasion_fast) {
    invasion_opts_t opts;
    opts.mode = ATTACK_TYPE_ENEMIES;
    opts.enemy_type = ENEMY_0_BARBARIAN; // 0 type, 1 kingdome, 2 seth natives
    opts.size = 10;
    opts.attack_type = FORMATION_ATTACK_FOOD_CHAIN;
    opts.invasion_point = tile2i::invalid;
    opts.invasion_id = 23;
    opts.want_destroy = 5;
    opts.kind = INVASION_KIND_FOREIGN;
    tile2i tile = scenario_start_invasion_impl(opts);
    if (tile.valid()) {
        emit_local_invasion_attack_message("message_barbarians_attack",
            g_invasions.last_internal_invasion_id, tile.grid_offset());
    }
}

enemy_properties_t ANK_VARIABLE(enemy_barbarian);
enemy_properties_t ANK_VARIABLE(enemy_assyrian);
enemy_properties_t ANK_VARIABLE(enemy_canaanite);
enemy_properties_t ANK_VARIABLE(enemy_egyptian);
enemy_properties_t ANK_VARIABLE(enemy_hittite);
enemy_properties_t ANK_VARIABLE(enemy_hyksos);
enemy_properties_t ANK_VARIABLE(enemy_kushite);
enemy_properties_t ANK_VARIABLE(enemy_libian);
enemy_properties_t ANK_VARIABLE(enemy_nubian);
enemy_properties_t ANK_VARIABLE(enemy_persian);
enemy_properties_t ANK_VARIABLE(enemy_phoenician);
enemy_properties_t ANK_VARIABLE(enemy_roman);
enemy_properties_t ANK_VARIABLE(enemy_seapeople);

std::array<enemy_properties_t *, ENEMY_COUNT> g_enemy_properties = {
    &enemy_barbarian,
    &enemy_assyrian,
    &enemy_canaanite,
    &enemy_egyptian,
    &enemy_hittite,
    &enemy_hyksos,
    &enemy_kushite,
    &enemy_libian,
    &enemy_nubian,
    &enemy_persian,
    &enemy_phoenician,
    &enemy_roman,
    &enemy_seapeople,
};

// The favour army uses figure IDs 55–57 instead of egyptian proxy types.
static e_figure_type invasion_spawn_figure_type(const invasion_opts_t &opts, int type_slot) {
    e_figure_type figure_type = g_enemy_properties[opts.enemy_type]->figure_types[type_slot];
    if (opts.kind == INVASION_KIND_KINGDOME) {
        static const e_figure_type kingdom_types[3] = {
            FIGURE_ENEMY_KINGDOME_JAVELIN,
            FIGURE_ENEMY_KINGDOME_INFANTRY,
            FIGURE_ENEMY_KINGDOME_MOUNTED,
        };
        return kingdom_types[type_slot];
    }
    return figure_type;
}

// Split invasion size across the three type slots. Kingdom kind remaps all three
// slots; egyptian pack has percentage_type3=0, so steal a mounted share from type1.
static void invasion_type_counts(const invasion_opts_t &opts, int size, int *n1, int *n2, int *n3) {
    const auto *ep = g_enemy_properties[opts.enemy_type];
    int p1 = ep->percentage_type1;
    int p2 = ep->percentage_type2;
    int p3 = ep->percentage_type3;
    if (opts.kind == INVASION_KIND_KINGDOME && p3 <= 0) {
        constexpr int mounted_share = 10;
        p3 = mounted_share;
        p1 = std::max(0, p1 - mounted_share);
    }
    *n1 = calc_adjust_with_percentage(size, p1);
    *n2 = calc_adjust_with_percentage(size, p2);
    *n3 = calc_adjust_with_percentage(size, p3);
    *n1 += size - (*n1 + *n2 + *n3);
}

const int LOCAL_UPRISING_NUM_ENEMIES[20] = {0, 0, 0, 0, 0, 3, 3, 3, 0, 6, 6, 6, 6, 6, 9, 9, 9, 9, 9, 9};

invasion_warning_t g_invasion_warning;
invasion_data_t ANK_VARIABLE_N(g_invasions, "invasions");

void invasion_data_t::clear(void) {
    memset(warnings.data(), 0, warnings.size() * sizeof(invasion_warning_t));
    for (auto &b : binds) {
        b = {};
    }
    for (auto &h : history) {
        h = {};
    }
    history_count = 0;
    history_next = 0;
    g_invasion_auto_resolve.clear();
}

// ONLY_VIA masters clone to ACTIVATED_* then return; drain those clones here so KR/siege/request
// fire the same month (process_bind runs after process_events — without drain, +1 month lag).
static void drain_activated_events(int from_index) {
    while (from_index < g_scenario.events.events_count()) {
        const int end = g_scenario.events.events_count();
        for (int i = from_index; i < end; ++i) {
            g_scenario.events.process_event(i, false, -1);
            g_scenario.events.process_active_request(i);
        }
        from_index = end;
    }
}

static void fire_chain_by_tag(uint16_t tag) {
    if (!tag) {
        return;
    }
    event_ph_t *only_via = nullptr;
    event_ph_t *burned = nullptr;
    for (int i = 0; i < g_scenario.events.events_count(); ++i) {
        event_ph_t *e = g_scenario.events.at(i);
        if (!e || e->tag_id != tag) {
            continue;
        }
        if (e->event_trigger_type == EVENT_TRIGGER_ONLY_VIA_EVENT) {
            only_via = e;
            break;
        }
        if (e->event_trigger_type == EVENT_TRIGGER_ALREADY_FIRED && !burned) {
            burned = e;
        }
    }
    event_ph_t *e = only_via ? only_via : burned;
    if (!e) {
        logs::warn("invasion bind: chain tag %u not found", tag);
        return;
    }
    const int before = g_scenario.events.events_count();
    g_scenario.events.process_event(e->event_id, true, EVENT_ACTION_COMPLETED, 0);
    drain_activated_events(before);
}

void invasion_data_t::record_spawn(const invasion_opts_t &opts, tile2i tile, int size_after_clamp) {
    const uint16_t seq = (uint16_t)last_internal_invasion_id;

    invasion_history_entry_t &h = history[history_next];
    h = {};
    h.seq = seq;
    h.year = (int16_t)game.simtime.years_since_start();
    h.month = (int8_t)game.simtime.month;
    h.invasion_id = (uint8_t)opts.invasion_id;
    h.enemy_type = (uint8_t)opts.enemy_type;
    h.mode = (uint8_t)opts.mode;
    h.attack_type = (uint8_t)opts.attack_type;
    h.size = (uint16_t)size_after_clamp;
    h.tile_x = tile.valid() ? (int16_t)tile.x() : (int16_t)-1;
    h.tile_y = tile.valid() ? (int16_t)tile.y() : (int16_t)-1;
    h.want_destroy = opts.want_destroy;
    h.outcome = INVASION_OUTCOME_NONE;
    history_next = (history_next + 1) % MAX_HISTORY;
    if (history_count < MAX_HISTORY) {
        history_count++;
    }

    // Always arm a bind so wipe/refuse updates history.outcome (favour multi-wave /
    // overlap gates). Chain tags remain optional.
    for (const auto &b : binds) {
        if (b.in_use && b.invasion_id == (uint8_t)opts.invasion_id) {
            logs::warn("invasion bind: invasion_id %d already has active bind (seq %u); new seq %u",
                       opts.invasion_id, b.seq, seq);
            break;
        }
    }

    for (auto &b : binds) {
        if (b.in_use) {
            continue;
        }
        b.in_use = true;
        b.enemies_seen = false;
        b.invasion_id = (uint8_t)opts.invasion_id;
        b.seq = seq;
        b.on_completed_tag = opts.on_completed_tag;
        b.on_refusal_tag = opts.on_refusal_tag;
        b.on_defeat_tag = opts.on_defeat_tag;
        return;
    }
    logs::warn("invasion bind: active table full (max %d)", MAX_ACTIVE_BINDS);
}

static void history_set_outcome(uint16_t seq, e_invasion_outcome outcome) {
    for (int i = 0; i < invasion_data_t::MAX_HISTORY; ++i) {
        auto &h = g_invasions.history[i];
        if (h.seq == seq && h.seq != 0) {
            h.outcome = (uint8_t)outcome;
            return;
        }
    }
}

void invasion_force_outcome(uint16_t seq, e_invasion_outcome outcome) {
    if (!seq) {
        return;
    }
    history_set_outcome(seq, outcome);
    for (auto &b : g_invasions.binds) {
        if (!b.in_use || b.seq != seq) {
            continue;
        }
        const uint16_t ok_tag = b.on_completed_tag;
        const uint16_t defeat_tag = b.on_defeat_tag;
        b = {};
        if (outcome == INVASION_OUTCOME_COMPLETED && ok_tag) {
            fire_chain_by_tag(ok_tag);
        } else if (outcome == INVASION_OUTCOME_DEFEAT && defeat_tag) {
            fire_chain_by_tag(defeat_tag);
        }
        return;
    }
}

void invasion_data_t::process_bind_resolutions() {
    for (auto &b : binds) {
        if (!b.in_use) {
            continue;
        }

        int this_wave = 0;
        for (int fi = 1; fi < MAX_FORMATIONS; ++fi) {
            formation *m = formation_get(fi);
            if (m && m->in_use && !m->is_herd && !m->own_batalion && m->num_figures > 0
                && m->invasion_id == b.invasion_id) {
                this_wave++;
            }
        }

        if (this_wave > 0) {
            b.enemies_seen = true;
            continue;
        }
        if (!b.enemies_seen) {
            continue;
        }

        const uint8_t invasion_id = b.invasion_id;
        const uint16_t seq = b.seq;
        const uint16_t ok_tag = b.on_completed_tag;
        const uint16_t refuse_tag = b.on_refusal_tag;
        const uint16_t defeat_tag = b.on_defeat_tag;
        b = {};

        enemy_army *army = enemy_army_get_editable(invasion_id);
        const bool destroy_goal = army && army->buildings_to_destroy > 0
            && army->buildings_destroyed >= army->buildings_to_destroy;

        // Ok-only: no refuse/defeat tags → always completed (Behdet), even if destroy-goal met.
        if (destroy_goal && refuse_tag) {
            logs::info("akhenaten: invasion seq=%u id=%u destroy-goal → REFUSED tag=%u", seq, invasion_id, refuse_tag);
            history_set_outcome(seq, INVASION_OUTCOME_REFUSED);
            fire_chain_by_tag(refuse_tag);
        } else if (destroy_goal && defeat_tag) {
            logs::info("akhenaten: invasion seq=%u id=%u destroy-goal → DEFEAT tag=%u", seq, invasion_id, defeat_tag);
            history_set_outcome(seq, INVASION_OUTCOME_DEFEAT);
            fire_chain_by_tag(defeat_tag);
        } else if (ok_tag) {
            logs::info("akhenaten: invasion seq=%u id=%u wiped → COMPLETED tag=%u", seq, invasion_id, ok_tag);
            history_set_outcome(seq, INVASION_OUTCOME_COMPLETED);
            fire_chain_by_tag(ok_tag);
        } else {
            history_set_outcome(seq, INVASION_OUTCOME_COMPLETED);
        }
    }
}

int invasion_data_t::history_entry_count() const {
    return history_count;
}

const invasion_history_entry_t *invasion_data_t::history_at(int index) const {
    if (index < 0 || index >= history_count) {
        return nullptr;
    }
    // 0 = oldest retained in the ring.
    const int start = (history_count < MAX_HISTORY) ? 0 : history_next;
    const int slot = (start + index) % MAX_HISTORY;
    return &history[slot];
}

void invasion_data_t::init() {
    clear();
    int path_current = 1;
    int path_max = g_empire.get_max_invasion_path();

    if (path_max == 0) {
        return;
    }

    // Julius: warnings[0] unused; fill from [1] onward with ++warning per battle icon.
    invasion_warning_t *warning = &warnings[1];
    const invasion_warning_t *warnings_end = warnings.data() + warnings.size();

    for (int i = 0; i < MAX_INVASIONS; i++) {
        random_generate_next();
        if (!g_scenario.invasions[i].type) {
            continue;
        }

        g_scenario.invasions[i].month = 2 + (random_byte() & 7);
        if (g_scenario.invasions[i].type == INVASION_TYPE_LOCAL_UPRISING
            || g_scenario.invasions[i].type == INVASION_TYPE_DISTANT_BATTLE) {
            continue;
        }

        for (int year = 1; year < 8; year++) {
            const empire_object* obj = g_empire.get_battle_icon(path_current, year);
            if (!obj) {
                continue;
            }
            if (warning >= warnings_end) {
                logs::warn("scenario_invasion: warning table full");
                return;
            }

            warning->in_use = 1;
            warning->invasion_path_id = obj->invasion_path_id;
            warning->warning_years = obj->invasion_years;
            warning->pos = obj->pos;
            warning->image_id = obj->image_id;
            warning->invasion_id = i;
            warning->empire_object_id = obj->id;
            warning->month_notified = 0;
            warning->year_notified = 0;
            warning->months_to_go = 12 * g_scenario.invasions[i].year;
            warning->months_to_go += g_scenario.invasions[i].month;
            warning->months_to_go -= 12 * year;
            ++warning;
        }

        path_current++;
        if (path_current > path_max) {
            path_current = 1;
        }
    }
}

bool scenario_invasion_exists_upcoming() {
    for (const auto& warning : g_invasions.warnings) {
        if (warning.in_use && warning.handled)
            return true;
    }
    return false;
}

void scenario_invasion_foreach_warning(std::function<void(vec2i, int)> callback) {
    for (const auto& warning : g_invasions.warnings) {
        if (warning.in_use && warning.handled)
            callback(warning.pos, warning.image_id);
    }
}

int scenario_invasion_count() {
    int num_invasions = 0;
    for (int i = 0; i < MAX_INVASIONS; i++) {
        if (g_scenario.invasions[i].type)
            num_invasions++;
    }
    return num_invasions;
}

static void determine_formations(int num_soldiers, int* num_formations, int soldiers_per_formation[]) {
    if (num_soldiers > 0) {
        if (num_soldiers <= 16) {
            *num_formations = 1;
            soldiers_per_formation[0] = num_soldiers;
        } else if (num_soldiers <= 32) {
            *num_formations = 2;
            soldiers_per_formation[1] = num_soldiers / 2;
            soldiers_per_formation[0] = num_soldiers - num_soldiers / 2;
        } else {
            *num_formations = 3;
            soldiers_per_formation[2] = num_soldiers / 3;
            soldiers_per_formation[1] = num_soldiers / 3;
            soldiers_per_formation[0] = num_soldiers - 2 * (num_soldiers / 3);
        }
    }
}

namespace {

bool invasion_point_is_sea(tile2i point) {
    if (!point.valid()) {
        return false;
    }
    if (map_invasion_point(point) == 2) {
        return true;
    }
    // Water without road/bridge → treat as sea spawn when caller passed a water tile.
    if (map_terrain_is(point, TERRAIN_WATER | TERRAIN_DEEPWATER)
        && !map_terrain_is(point, TERRAIN_ROAD)) {
        return true;
    }
    return false;
}

bool invasion_should_use_sea(const invasion_opts_t &opts) {
    if (opts.via_sea) {
        return true;
    }
    return invasion_point_is_sea(opts.invasion_point);
}

tile2i pick_sea_spawn_tile(const invasion_opts_t &opts) {
    auto &seas = g_scenario.invasion_points_sea;
    if (opts.sea_point_index >= 0 && opts.sea_point_index < (int)seas.size()) {
        tile2i t = seas[opts.sea_point_index];
        if (t.valid() && map_terrain_is(t, TERRAIN_WATER | TERRAIN_DEEPWATER)) {
            return t;
        }
    }

    if (opts.invasion_point.valid()
        && map_terrain_is(opts.invasion_point, TERRAIN_WATER | TERRAIN_DEEPWATER)) {
        return opts.invasion_point;
    }

    svector<tile2i, 8> points;
    std::copy_if(seas.begin(), seas.end(), std::back_inserter(points), [](auto &p) {
        return p.valid() && map_terrain_is(p, TERRAIN_WATER | TERRAIN_DEEPWATER);
    });
    if (!points.empty()) {
        return points.at(rand() % points.size());
    }

    // Fallback: first water tile on the map.
    const int w = g_scenario.map.width;
    const int h = g_scenario.map.height;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            tile2i t(x, y);
            if (map_terrain_is(t, TERRAIN_WATER | TERRAIN_DEEPWATER)
                && !map_terrain_is(t, TERRAIN_BUILDING)) {
                return t;
            }
        }
    }
    return tile2i::invalid;
}

tile2i water_adjacent_to(tile2i land) {
    if (!land.valid()) {
        return tile2i::invalid;
    }
    static const vec2i dirs[] = {
        {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}
    };
    for (const vec2i &dir : dirs) {
        tile2i w = land.shifted(dir);
        if (w.valid() && map_terrain_is(w, TERRAIN_WATER | TERRAIN_DEEPWATER)) {
            return w;
        }
    }
    return tile2i::invalid;
}

tile2i pick_landing_water_tile(tile2i sea_spawn) {
    auto &dis = g_scenario.disembark_points;
    for (const auto &land : dis) {
        if (!enemy_transport_land_ok(land)) {
            continue;
        }
        tile2i water = water_adjacent_to(land);
        if (water.valid()) {
            return water;
        }
    }

    // No disembark points — find any shore water near the spawn.
    static const vec2i dirs[] = {
        {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}
    };
    for (int radius = 1; radius <= 40; radius++) {
        for (int dy = -radius; dy <= radius; dy++) {
            for (int dx = -radius; dx <= radius; dx++) {
                if (std::abs(dx) != radius && std::abs(dy) != radius) {
                    continue;
                }
                tile2i water = sea_spawn.shifted(dx, dy);
                if (!water.valid() || !map_terrain_is(water, TERRAIN_WATER | TERRAIN_DEEPWATER)) {
                    continue;
                }
                for (const vec2i &dir : dirs) {
                    tile2i land = water.shifted(dir);
                    if (enemy_transport_land_ok(land)) {
                        return water;
                    }
                }
            }
        }
    }
    return tile2i::invalid;
}

} // namespace

static void sea_invasion_abort_formation(int formation_id) {
    if (formation_id <= 0) {
        return;
    }
    for (figure *f : map_figures()) {
        if (f && f->is_alive() && f->formation_id == formation_id) {
            f->set_flag(e_figure_flag_invisible, false);
            f->kill();
        }
    }
    formation *m = formation_get(formation_id);
    if (m && m->in_use) {
        m->num_figures = 0;
        for (int fi = 0; fi < formation::max_figures_count; fi++) {
            m->figures[fi] = 0;
        }
        m->in_use = false;
    }
}

tile2i scenario_start_sea_invasion_impl(invasion_opts_t &opts) {
    auto &data = g_invasions;
    if (opts.size <= 0) {
        return tile2i::invalid;
    }

    opts.size = std::clamp<int>(difficulty_adjust_enemies(opts.size), data.min_invasion_amount, data.max_invasion_amount);

    data.last_internal_invasion_id++;
    if (data.last_internal_invasion_id > 32000) {
        data.last_internal_invasion_id = 1;
    }

    tile2i sea_spawn = pick_sea_spawn_tile(opts);
    if (!sea_spawn.valid()) {
        logs::warn("scenario_sea_invasion: no valid sea spawn tile");
        return tile2i::invalid;
    }

    tile2i landing_water = pick_landing_water_tile(sea_spawn);
    if (!landing_water.valid()) {
        logs::warn("scenario_sea_invasion: no landing water near disembark points");
        return tile2i::invalid;
    }

    int formations_per_type[3];
    int soldiers_per_formation[3][4];

    int num_type1, num_type2, num_type3;
    invasion_type_counts(opts, opts.size, &num_type1, &num_type2, &num_type3);

    for (int t = 0; t < 3; t++) {
        formations_per_type[t] = 0;
        for (int f = 0; f < 4; f++) {
            soldiers_per_formation[t][f] = 0;
        }
    }

    determine_formations(num_type1, &formations_per_type[0], soldiers_per_formation[0]);
    determine_formations(num_type2, &formations_per_type[1], soldiers_per_formation[1]);
    determine_formations(num_type3, &formations_per_type[2], soldiers_per_formation[2]);

    const int orientation = DIR_4_BOTTOM_LEFT;
    const e_figure_type transport_type = enemy_transport_type_for(opts.enemy_type);
    const e_figure_type warship_type = enemy_warship_type_for(opts.enemy_type);

    int total_formations = 0;
    int seq = 0;

    for (int type = 0; type < 3; type++) {
        if (formations_per_type[type] <= 0) {
            continue;
        }

        e_figure_type figure_type = invasion_spawn_figure_type(opts, type);
        if (figure_type == FIGURE_NONE) {
            logs::error("No figure type for %s enemy", e_enemy_type_tokens.name(opts.enemy_type));
            continue;
        }

        for (int i = 0; i < formations_per_type[type]; i++) {
            int formation_id = formation_create_enemy(figure_type,
                                                      landing_water,
                                                      g_enemy_properties[opts.enemy_type]->layout,
                                                      orientation,
                                                      opts.enemy_type,
                                                      opts.attack_type,
                                                      opts.invasion_id,
                                                      data.last_internal_invasion_id);
            if (formation_id <= 0) {
                continue;
            }

            for (int fig = 0; fig < soldiers_per_formation[type][i]; fig++) {
                figure *f = figure_create(figure_type, sea_spawn, orientation);
                if (!f || !f->is_valid()) {
                    logs::warn("scenario_sea_invasion: figure pool exhausted while spawning soldiers");
                    sea_invasion_abort_formation(formation_id);
                    formation_id = 0;
                    break;
                }
                f->faction_id = 0;
                f->action_state = ACTION_152_ENEMY_WAITING;
                f->wait_ticks = 30000;
                f->formation_id = formation_id;
                f->index_in_formation = (uint8_t)fig;
                f->formation_at_rest = 1;
                f->allow_move_type = EMOVE_AMPHIBIAN;
                f->name = figure_name_get(figure_type);
                f->set_flag(e_figure_flag_invisible);
            }
            if (formation_id <= 0) {
                continue;
            }

            figure *ship = figure_create(transport_type, sea_spawn, orientation);
            if (!ship || !ship->is_valid()) {
                logs::warn("scenario_sea_invasion: failed to create transport for formation %d", formation_id);
                sea_invasion_abort_formation(formation_id);
                continue;
            }
            ship->faction_id = 0;

            auto *transport = smart_cast<figure_enemy_transport>(ship);
            if (!transport) {
                logs::warn("scenario_sea_invasion: transport type missing enemy_transport impl");
                ship->dcast()->kill();
                sea_invasion_abort_formation(formation_id);
                continue;
            }
            transport->set_invasion_sequence(data.last_internal_invasion_id);

            if (!transport->load_formation(formation_id)) {
                logs::warn("scenario_sea_invasion: failed to load formation %d onto transport", formation_id);
                sea_invasion_abort_formation(formation_id);
                ship->dcast()->kill();
                continue;
            }
            if (!transport->sail_to_landing(landing_water)) {
                logs::warn("scenario_sea_invasion: landing water has no unloadable shore");
                sea_invasion_abort_formation(formation_id);
                ship->dcast()->kill();
                continue;
            }
            total_formations++;
            seq++;
        }
    }

    // Escort: max(1, ceil(formations / 3)) warships at the sea spawn.
    int escort = total_formations > 0 ? std::max(1, (total_formations + 2) / 3) : 0;
    for (int e = 0; e < escort; e++) {
        figure *w = figure_create(warship_type, sea_spawn, orientation);
        if (!w || !w->is_valid()) {
            continue;
        }
        w->faction_id = 0;
        w->name = figure_name_get(warship_type);
        if (auto *warship = smart_cast<figure_enemy_warship>(w)) {
            warship->set_invasion_sequence(data.last_internal_invasion_id);
        }
    }

    if (opts.invasion_id > 0
        && opts.invasion_id < enemy_armies_t::MAX_ENEMY_ARMIES
        && seq > 0) {
        enemy_army *army = enemy_army_get_editable((uint8_t)opts.invasion_id);
        army->buildings_to_destroy = opts.want_destroy;
        army->buildings_destroyed = 0;
    }

    if (seq > 0 && sea_spawn.valid()) {
        g_invasions.record_spawn(opts, sea_spawn, opts.size);
        g_invasion_auto_resolve.maybe_enqueue(opts, (uint16_t)data.last_internal_invasion_id);
    }

    return seq > 0 ? sea_spawn : tile2i::invalid;
}

tile2i scenario_start_invasion_impl(invasion_opts_t &opts) {
    if (invasion_should_use_sea(opts)) {
        return scenario_start_sea_invasion_impl(opts);
    }

    auto &data = g_invasions;
    if (opts.size <= 0) {
        return tile2i::invalid;
    }

    int formations_per_type[3];
    int soldiers_per_formation[3][4];

    opts.size = std::clamp<int>(difficulty_adjust_enemies(opts.size), data.min_invasion_amount, data.max_invasion_amount);

    data.last_internal_invasion_id++;
    if (data.last_internal_invasion_id > 32000) {
        data.last_internal_invasion_id = 1;
    }

    // calculate soldiers per type
    int num_type1, num_type2, num_type3;
    invasion_type_counts(opts, opts.size, &num_type1, &num_type2, &num_type3);

    for (int t = 0; t < 3; t++) {
        formations_per_type[t] = 0;
        for (int f = 0; f < 4; f++) {
            soldiers_per_formation[t][f] = 0;
        }
    }

    // calculate number of formations
    determine_formations(num_type1, &formations_per_type[0], soldiers_per_formation[0]);
    determine_formations(num_type2, &formations_per_type[1], soldiers_per_formation[1]);
    determine_formations(num_type3, &formations_per_type[2], soldiers_per_formation[2]);

    // determine invasion point
    tile2i invasion_tile;
    if (opts.invasion_point.valid()) {
        // Explicit JS/pak loc wins (incl. Egyptian — map entry only when tile unset).
        invasion_tile = opts.invasion_point;
    } else if (opts.enemy_type == ENEMY_3_EGYPTIAN) {
        invasion_tile = scenario_map_entry();
    } else {
        auto &lands = g_scenario.invasion_points_land;
        svector<tile2i, 8> points;
        std::copy_if(lands.begin(), lands.end(), std::back_inserter(points), [] (auto &p) { return p.valid(); });
        if (points.empty()) {
            logs::warn("scenario_invasion: no valid land invasion points, falling back to map exit");
            invasion_tile = tile2i::invalid;
        } else {
            invasion_tile = points.at(rand() % points.size());
        }
    }

    if (!invasion_tile.valid()) {
        invasion_tile = scenario_map_exit();
    }

    // determine orientation
    int orientation = DIR_4_BOTTOM_LEFT;
    
    // check terrain — try entry / a few edge candidates if the primary tile is blocked
    auto tile_ok = [] (tile2i t) {
        if (!t.valid()) {
            return false;
        }
        if (map_terrain_is(t, TERRAIN_ELEVATION | TERRAIN_ROCK | TERRAIN_TREE)) {
            return false;
        }
        if (map_terrain_is(t, TERRAIN_WATER) && !map_terrain_is(t, TERRAIN_ROAD)) {
            return false;
        }
        return true;
    };

    if (!tile_ok(invasion_tile)) {
        tile2i candidates[] = {
            scenario_map_entry(),
            scenario_map_exit(),
            tile2i(1, g_scenario.map.height / 2),
            tile2i(g_scenario.map.width - 2, g_scenario.map.height / 2),
            tile2i(g_scenario.map.width / 2, 1),
            tile2i(g_scenario.map.width / 2, g_scenario.map.height - 2),
        };
        invasion_tile = tile2i::invalid;
        for (tile2i c : candidates) {
            if (tile_ok(c)) {
                invasion_tile = c;
                break;
            }
        }
    }

    if (!invasion_tile.valid()) {
        return tile2i::invalid;
    }

    if (map_terrain_is(invasion_tile, TERRAIN_WATER)) {
        if (!map_terrain_is(invasion_tile, TERRAIN_ROAD)) { // bridge
            return tile2i::invalid;
        }
    } else if (map_terrain_is(invasion_tile, TERRAIN_BUILDING | TERRAIN_CANAL | TERRAIN_GATEHOUSE | TERRAIN_WALL)) {
        building *b = building_get(invasion_tile.grid_offset());
        if (b->id) {
            g_city.maintenance.destroy_by_enemy(b);
        }
    }

    // spawn the lot!
    int seq = 0;
    for (int type = 0; type < 3; type++) {
        if (formations_per_type[type] <= 0) {
            continue;
        }

        e_figure_type figure_type = invasion_spawn_figure_type(opts, type);
        if (figure_type == FIGURE_NONE) {
            logs::error("No figure type for %s enemy", e_enemy_type_tokens.name(opts.enemy_type));
            continue;
        }

        for (int i = 0; i < formations_per_type[type]; i++) {
            int formation_id = formation_create_enemy(figure_type,
                                                      invasion_tile,
                                                      g_enemy_properties[opts.enemy_type]->layout,
                                                      orientation,
                                                      opts.enemy_type,
                                                      opts.attack_type,
                                                      opts.invasion_id,
                                                      data.last_internal_invasion_id);
            if (formation_id <= 0) {
                continue;
            }

            for (int fig = 0; fig < soldiers_per_formation[type][i]; fig++) {
                figure* f = figure_create(figure_type, invasion_tile, orientation);
                f->faction_id = 0;
                f->action_state = ACTION_151_ENEMY_INITIAL;
                f->wait_ticks = 200 * seq + 10 * fig + 10;
                f->formation_id = formation_id;
                f->name = figure_name_get(figure_type);
            }
            seq++;
        }
    }

    // Apply destroy-goal to the army slot (JS want_destroy_buildings).
    // Without this, enemy_army_achieved_destroy_goal never returns true.
    if (opts.invasion_id > 0
        && opts.invasion_id < enemy_armies_t::MAX_ENEMY_ARMIES
        && seq > 0) {
        enemy_army *army = enemy_army_get_editable((uint8_t)opts.invasion_id);
        army->buildings_to_destroy = opts.want_destroy;
        army->buildings_destroyed = 0;
    }

    // Match sea path: no formations ⇒ invalid. Callers (begin_favour_army / messages)
    // key off tile.valid(); a bare tile with seq==0 would arm favour_only at duration=192
    // with zero soldiers and never clean up (duration never ticks without troops).
    if (seq <= 0) {
        return tile2i::invalid;
    }

    g_invasions.record_spawn(opts, invasion_tile, opts.size);
    g_invasion_auto_resolve.maybe_enqueue(opts, (uint16_t)data.last_internal_invasion_id);
    return invasion_tile;
}

void scenario_invasion_process() {
    e_enemy_type enemy_id = g_scenario.enemy_id;
    for (auto& warning : g_invasions.warnings) {
        if (!warning.in_use)
            continue;

        // update warnings
        warning.months_to_go--;
        if (warning.months_to_go <= 0) {
            if (warning.handled != 1) {
                warning.handled = 1;
                warning.year_notified = game.simtime.year;
                warning.month_notified = game.simtime.month;
                if (warning.warning_years > 2)
                    events::emit(event_message{ false, "message_distant_battle", 0, 0, SOURCE_LOCATION });
                else if (warning.warning_years > 1)
                    events::emit(event_message{ false, "message_enemies_closing", 0, 0, SOURCE_LOCATION });
                else {
                    events::emit(event_message{ false, "message_enemies_at_the_door", 0, 0, SOURCE_LOCATION });
                }
            }
        }

        if (game.simtime.year >= g_scenario.start_year + g_scenario.invasions[warning.invasion_id].year
            && game.simtime.month >= g_scenario.invasions[warning.invasion_id].month) {
            // invasion attack time has passed
            warning.in_use = 0;
            if (warning.warning_years > 1) {
                continue;
            }

            // enemy invasions
            if (g_scenario.invasions[warning.invasion_id].type == INVASION_TYPE_ENEMY_ARMY) {
                invasion_opts_t opts;
                opts.enemy_type = enemy_id;
                opts.size = g_scenario.invasions[warning.invasion_id].amount;
                // opts.invasion_point = g_scenario.invasions[warning.invasion_id].from;
                opts.attack_type = g_scenario.invasions[warning.invasion_id].attack_type;
                opts.invasion_id = warning.invasion_id;
                opts.kind = (enemy_id == ENEMY_3_EGYPTIAN) ? INVASION_KIND_PHARAOH : INVASION_KIND_FOREIGN;
                tile2i invasion_tile = scenario_start_invasion_impl(opts);
                if (invasion_tile.valid()) {
                    const bool egyptian = (enemy_id == ENEMY_3_EGYPTIAN);
                    emit_local_invasion_attack_message(
                        egyptian ? "message_legion_attacks" : "message_barbarians_attack",
                        g_invasions.last_internal_invasion_id, invasion_tile.grid_offset());
                }
            }
            if (g_scenario.invasions[warning.invasion_id].type == INVASION_TYPE_KNGDOME) {
                invasion_opts_t opts;
                opts.enemy_type = ENEMY_3_EGYPTIAN;
                opts.size = g_scenario.invasions[warning.invasion_id].amount;
                // opts.invasion_point = g_scenario.invasions[warning.invasion_id].from;
                opts.attack_type = g_scenario.invasions[warning.invasion_id].attack_type;
                opts.invasion_id = warning.invasion_id;
                opts.kind = INVASION_KIND_KINGDOME;
                tile2i invasion_tile = scenario_start_invasion_impl(opts);
                if (invasion_tile.valid()) {
                    // Scenario kingdom wave: kill tally via favour_only (no Caesar respect /
                    // pause-retreat). opts.size is difficulty-adjusted by start_invasion_impl.
                    g_city.kingdome.begin_favour_army(opts.size);
                    emit_local_invasion_attack_message("message_legion_attacks",
                        g_invasions.last_internal_invasion_id, invasion_tile.grid_offset());
                }
            }
        }
    }
    // local uprisings
    for (int i = 0; i < MAX_INVASIONS; i++) {
        if (g_scenario.invasions[i].type == INVASION_TYPE_LOCAL_UPRISING) {
            if (game.simtime.year == g_scenario.start_year + g_scenario.invasions[i].year && game.simtime.month == g_scenario.invasions[i].month) {
                invasion_opts_t opts;
                opts.enemy_type = ENEMY_0_BARBARIAN;
                opts.size = g_scenario.invasions[i].amount;
                // opts.invasion_point = g_scenario.invasions[warning.invasion_id].from;
                opts.attack_type = g_scenario.invasions[i].attack_type;
                opts.invasion_id = i;
                opts.kind = INVASION_KIND_UPRISING;
                tile2i invasion_tile = scenario_start_invasion_impl(opts);
                if (invasion_tile.valid()) {
                    events::emit(event_message{ true, "message_local_uprising", g_invasions.last_internal_invasion_id, invasion_tile.grid_offset(), SOURCE_LOCATION });
                }
            }
        }
    }
}

int map_invasion_point(tile2i point) {
    auto &lands = g_scenario.invasion_points_land;
    const auto it_land = std::find_if(lands.begin(), lands.end(), [point] (auto &p) { return p == point; });
    if (it_land != lands.end()) {
        return 1;
    }

    auto &sea = g_scenario.invasion_points_sea;
    const auto it_sea = std::find_if(sea.begin(), sea.end(), [point] (auto &p) { return p == point; });
    if (it_sea != sea.end()) {
        return 2;
    }

    return 0;
}

bool scenario_invasion_start_from_kingdome(int &size) {
    auto &data = g_invasions;

    invasion_opts_t opts;
    opts.enemy_type = ENEMY_3_EGYPTIAN;
    opts.size = size;
    // opts.invasion_point = g_scenario.invasions[warning.invasion_id].from;
    opts.attack_type = FORMATION_ATTACK_BEST_BUILDINGS;
    opts.invasion_id = 24;
    opts.kind = INVASION_KIND_KINGDOME;

    tile2i invasion_tile = scenario_start_invasion_impl(opts);
    if (invasion_tile.valid()) {
        size = opts.size; // difficulty-adjusted spawn count for kill bookkeeping
        // Same popup as scenario KINGDOME warnings (id 123); no separate
        // message_kingdome_army_attack archive entry.
        emit_local_invasion_attack_message("message_legion_attacks",
            data.last_internal_invasion_id, invasion_tile.grid_offset());
        return true;
    }
    return false;
}

int scenario_invasion_start(invasion_opts_t opts) {
    auto &data = g_invasions;
    // Derive kind when caller left default FOREIGN but mode/enemy imply otherwise.
    if (opts.kind == INVASION_KIND_FOREIGN) {
        if (opts.mode == ATTACK_TYPE_NATIVES) {
            opts.kind = INVASION_KIND_NATIVES;
        } else if (opts.mode == ATTACK_TYPE_KINGDOME) {
            opts.kind = INVASION_KIND_KINGDOME;
        } else if (opts.enemy_type == ENEMY_3_EGYPTIAN) {
            opts.kind = INVASION_KIND_PHARAOH;
        }
    }
    switch (opts.mode) {
    case ATTACK_TYPE_ENEMIES: {
        tile2i invasion_tile = scenario_start_invasion_impl(opts);
        if (invasion_tile.valid()) {
            if (opts.enemy_type == ENEMY_3_EGYPTIAN || opts.kind == INVASION_KIND_KINGDOME) {
                emit_local_invasion_attack_message("message_legion_attacks",
                    data.last_internal_invasion_id, invasion_tile.grid_offset());
            } else {
                emit_local_invasion_attack_message("message_barbarians_attack",
                    data.last_internal_invasion_id, invasion_tile.grid_offset());
            }
            if (opts.kind == INVASION_KIND_KINGDOME) {
                g_city.kingdome.begin_favour_army(opts.size);
            }
            return data.last_internal_invasion_id;
        }
        break;
    }
    case ATTACK_TYPE_KINGDOME: {
        // Legacy / console path — cheated_invasion skips pause/retreat.
        // Do not key off last_internal_invasion_id: failed spawns still bump the
        // counter before returning invalid (tile/seq failure).
        opts.kind = INVASION_KIND_KINGDOME;
        if (!g_city.kingdome.force_attack(opts.size)) {
            return 0;
        }
        return data.last_internal_invasion_id;
    }
    case ATTACK_TYPE_NATIVES: {
        opts.attack_type = FORMATION_ATTACK_FOOD_CHAIN;
        opts.enemy_type = ENEMY_0_BARBARIAN;
        opts.kind = INVASION_KIND_NATIVES;
        tile2i invasion_tile = scenario_start_invasion_impl(opts);
        if (invasion_tile.valid()) {
            events::emit(event_message{ true, "message_local_wrath_of_seth",
                data.last_internal_invasion_id, invasion_tile.grid_offset(), SOURCE_LOCATION });
            return data.last_internal_invasion_id;
        }
        break;
    }
    default:
        break;
    }
    return 0;
}

// Julius layout: 101 × 32 = 3232 (matches push_chunk size).
// per warning: u8×4 + i16×6 + i32 + u8 + pad11.
io_buffer* iob_invasion_warnings = new io_buffer([](io_buffer* iob, size_t version) {
    for (auto &w : g_invasions.warnings) {
        iob->bind_bool(w.in_use);
        iob->bind_bool(w.handled);
        iob->bind(BIND_SIGNATURE_UINT8, &w.invasion_path_id);
        iob->bind(BIND_SIGNATURE_UINT8, &w.warning_years);
        iob->bind_vec2i_compat(w.pos);
        iob->bind(BIND_SIGNATURE_INT16, &w.image_id);
        iob->bind(BIND_SIGNATURE_INT16, &w.empire_object_id);
        iob->bind(BIND_SIGNATURE_INT16, &w.month_notified);
        iob->bind(BIND_SIGNATURE_INT16, &w.year_notified);
        iob->bind(BIND_SIGNATURE_INT32, &w.months_to_go);
        iob->bind(BIND_SIGNATURE_UINT8, &w.invasion_id);
        iob->bind____skip(11);
    }
});

// v172 stub: keep chunk in schema so old saves load; ignore contents.
io_buffer *iob_invasion_event_pending = new io_buffer([] (io_buffer *iob, size_t version) {
    iob->bind____skip(272);
}, [] (size_t version) {
    // v172 stub: the chunk holds no state, it only keeps a slot in the old positional
    // layout. The defaulter exists to mark it optional for saves older than v172.
});

// v173: active binds + history ring (audit/debug; binds are gameplay mid-fight).
// Layout 1480: header 8 + 16×12 binds + 64×20 history.
io_buffer *iob_invasion_runtime = new io_buffer([] (io_buffer *iob, size_t version) {
    auto &data = g_invasions;
    iob->bind(BIND_SIGNATURE_INT32, &data.history_count);
    iob->bind(BIND_SIGNATURE_INT32, &data.history_next);
    for (auto &b : data.binds) {
        iob->bind_bool(b.in_use);
        iob->bind_bool(b.enemies_seen);
        iob->bind_u8(b.invasion_id);
        iob->bind____skip(1);
        iob->bind_u16(b.seq);
        iob->bind_u16(b.on_completed_tag);
        iob->bind_u16(b.on_refusal_tag);
        iob->bind_u16(b.on_defeat_tag);
    }
    for (auto &h : data.history) {
        iob->bind_u16(h.seq);
        iob->bind(BIND_SIGNATURE_INT16, &h.year);
        iob->bind(BIND_SIGNATURE_INT8, &h.month);
        iob->bind_u8(h.invasion_id);
        iob->bind_u8(h.enemy_type);
        iob->bind_u8(h.mode);
        iob->bind_u8(h.attack_type);
        iob->bind____skip(1);
        iob->bind_u16(h.size);
        iob->bind(BIND_SIGNATURE_INT16, &h.tile_x);
        iob->bind(BIND_SIGNATURE_INT16, &h.tile_y);
        iob->bind_u8(h.want_destroy);
        iob->bind_u8(h.outcome);
        iob->bind____skip(2);
    }
}, [] (size_t version) {
    // saves older than v173 have no resolve binds or history ring
    g_invasions.history_count = 0;
    g_invasions.history_next = 0;
    for (auto &b : g_invasions.binds) {
        b = {};
    }
});

const enemy_properties_t &invasion_data_t::get_prop(e_enemy_type type) {
    return *g_enemy_properties[type];
}
