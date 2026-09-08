#include "figure_enemy_transport.h"

#include "city/city_figures.h"
#include "city/city_warnings.h"
#include "core/string.h"
#include "dev/debug.h"
#include "figure/formation.h"
#include "figure/formation_layout.h"
#include "figure/route.h"
#include "figuretype/figure_shipwreck.h"
#include "game/game_events.h"
#include "grid/figure.h"
#include "grid/terrain.h"
#include "input/mouse.h"
#include "js/js_game.h"
#include "scenario/scenario.h"
#include "scenario/invasion_auto_resolve.h"
#include "widget/widget_city.h"

#include <cstdlib>

const e_action_enemy_transport_tokens_t ANK_CONFIG_ENUM(e_action_enemy_transport_tokens)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_enemy_transport_generic)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_egyptian_transport_ship)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_barbarian_transport_ship)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_assyrian_transport_ship)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_canaanite_transport_ship)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_hittite_transport_ship)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_hyksos_transport_ship)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_kushite_transport_ship)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_libian_transport_ship)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_nubian_transport_ship)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_persian_transport_ship)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_phoenician_transport_ship)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_roman_transport_ship)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_seapeople_transport_ship)

namespace {

constexpr int ENEMY_TRANSPORT_DISEMBARK_TICKS = 50;

tile2i enemy_transport_find_shore_tile(tile2i water_tile) {
    static const vec2i dirs[] = {
        {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}
    };

    for (const vec2i &dir : dirs) {
        tile2i land = water_tile.shifted(dir);
        if (enemy_transport_land_ok(land)) {
            return land;
        }
    }

    return tile2i::invalid;
}

// Water tile near `from` that has a valid adjacent shore (for re-routing).
tile2i enemy_transport_find_alternate_landing(tile2i from, int max_radius) {
    for (int radius = 1; radius <= max_radius; radius++) {
        for (int dy = -radius; dy <= radius; dy++) {
            for (int dx = -radius; dx <= radius; dx++) {
                if (std::abs(dx) != radius && std::abs(dy) != radius) {
                    continue;
                }
                tile2i water = from.shifted(dx, dy);
                if (!water.valid()
                    || !map_terrain_is(water, TERRAIN_WATER | TERRAIN_DEEPWATER)) {
                    continue;
                }
                if (enemy_transport_find_shore_tile(water).valid()) {
                    return water;
                }
            }
        }
    }
    return tile2i::invalid;
}

tile2i find_water_spawn_tile_for_transport(tile2i preferred) {
    if (preferred.valid()
        && map_terrain_is(preferred, TERRAIN_WATER | TERRAIN_DEEPWATER)
        && !map_terrain_is(preferred, TERRAIN_BUILDING)) {
        return preferred;
    }

    auto &seas = g_scenario.invasion_points_sea;
    for (const auto &t : seas) {
        if (t.valid()
            && map_terrain_is(t, TERRAIN_WATER | TERRAIN_DEEPWATER)
            && !map_terrain_is(t, TERRAIN_BUILDING)) {
            return t;
        }
    }

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

} // namespace

bool enemy_transport_land_ok(tile2i land) {
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

e_figure_type enemy_transport_type_for(e_enemy_type enemy) {
    switch (enemy) {
    case ENEMY_1_ASSYRIAN: return FIGURE_ENEMY_ASSYRIAN_TRANSPORT_SHIP;
    case ENEMY_2_CANAANITE: return FIGURE_ENEMY_CANAANITE_TRANSPORT_SHIP;
    case ENEMY_3_EGYPTIAN: return FIGURE_ENEMY_EGYPTIAN_TRANSPORT_SHIP;
    case ENEMY_4_HITTITE: return FIGURE_ENEMY_HITTITE_TRANSPORT_SHIP;
    case ENEMY_5_HYKSOS: return FIGURE_ENEMY_HYKSOS_TRANSPORT_SHIP;
    case ENEMY_6_KUSHITE: return FIGURE_ENEMY_KUSHITE_TRANSPORT_SHIP;
    case ENEMY_7_LIBIAN: return FIGURE_ENEMY_LIBIAN_TRANSPORT_SHIP;
    case ENEMY_8_NUBIAN: return FIGURE_ENEMY_NUBIAN_TRANSPORT_SHIP;
    case ENEMY_9_PERSIAN: return FIGURE_ENEMY_PERSIAN_TRANSPORT_SHIP;
    case ENEMY_10_PHOENICIAN: return FIGURE_ENEMY_PHOENICIAN_TRANSPORT_SHIP;
    case ENEMY_11_ROMAN: return FIGURE_ENEMY_ROMAN_TRANSPORT_SHIP;
    case ENEMY_12_SEAPEOPLE: return FIGURE_ENEMY_SEAPEOPLE_TRANSPORT_SHIP;
    case ENEMY_0_BARBARIAN:
        return FIGURE_ENEMY_BARBARIAN_TRANSPORT_SHIP;
    default:
        return FIGURE_ENEMY_TRANSPORT;
    }
}

void figure_enemy_transport::on_create() {
    figure_enemy::on_create();
    base.allow_move_type = EMOVE_WATER;
    base.terrain_usage = TERRAIN_USAGE_ANY;
    auto &d = runtime_data();
    d.formation_id = 0;
    d.wreck_spawned = 0;
    d.landing_x = -1;
    d.landing_y = -1;
    d.disembark_x = -1;
    d.disembark_y = -1;
    d.ticks = 0;
    d.invasion_sequence = 0;
    advance_action(ACTION_0_ENEMY_TRANSPORT_CREATED);
}

bool figure_enemy_transport::has_troops() const {
    const int fid = runtime_data().formation_id;
    if (fid <= 0) {
        return false;
    }
    const formation *m = formation_get(fid);
    return m && m->in_use;
}

int figure_enemy_transport::transported_formation() const {
    return has_troops() ? runtime_data().formation_id : 0;
}

void figure_enemy_transport::release_empty_cargo() {
    auto &d = runtime_data();
    if (d.formation_id <= 0) {
        return;
    }

    formation *m = formation_get(d.formation_id);
    if (!m || !m->in_use) {
        d.formation_id = 0;
        return;
    }

    int alive = 0;
    for (figure *f : map_figures()) {
        if (f && f->is_alive() && f->formation_id == d.formation_id) {
            alive++;
        }
    }
    if (alive > 0) {
        return;
    }

    m->num_figures = 0;
    for (int i = 0; i < formation::max_figures_count; i++) {
        m->figures[i] = 0;
    }
    m->in_use = false;
    m->is_halted = 0;
    d.formation_id = 0;
}

bool figure_enemy_transport::load_formation(int formation_id) {
    if (has_troops() || formation_id <= 0) {
        return false;
    }

    formation *m = formation_get(formation_id);
    if (!m || !m->in_use || m->own_batalion) {
        return false;
    }

    int loaded = 0;
    for (figure *f : map_figures()) {
        if (!f || !f->is_alive() || f->formation_id != formation_id) {
            continue;
        }

        f->map_figure_remove();
        f->set_flag(e_figure_flag_invisible);
        f->tile = base.tile;
        f->route_remove();
        // WAITING: no enemy_initial missile fire / march while aboard.
        f->action_state = ACTION_152_ENEMY_WAITING;
        f->wait_ticks = 30000;
        f->formation_at_rest = 1;
        // Land enemies on a water hull would be killed by action.cpp's
        // !can_move_by_water() check — keep them amphibious until disembark.
        f->allow_move_type = EMOVE_AMPHIBIAN;
        loaded++;
    }

    if (loaded <= 0) {
        return false;
    }

    auto &d = runtime_data();
    d.formation_id = (int8_t)formation_id;
    d.ticks = 0;
    m->is_halted = 1;
    return true;
}

bool figure_enemy_transport::sail_to_landing(tile2i water_tile) {
    if (!water_tile.valid()
        || !map_terrain_is(water_tile, TERRAIN_WATER | TERRAIN_DEEPWATER)) {
        return false;
    }

    tile2i shore = enemy_transport_find_shore_tile(water_tile);
    if (!shore.valid()) {
        return false;
    }

    auto &d = runtime_data();
    d.landing_x = water_tile.x();
    d.landing_y = water_tile.y();
    d.disembark_x = shore.x();
    d.disembark_y = shore.y();
    d.ticks = 0;

    base.destination_tile = water_tile;
    if (!base.source_tile.valid()) {
        base.source_tile = base.tile;
    }
    advance_action(ACTION_1_ENEMY_TRANSPORT_SAILING);
    route_remove();
    return true;
}

void figure_enemy_transport::disembark_troops() {
    auto &d = runtime_data();
    formation *m = formation_get(d.formation_id);
    if (!m || !m->in_use) {
        d.formation_id = 0;
        d.ticks = 0;
        advance_action(ACTION_3_ENEMY_TRANSPORT_IDLE);
        return;
    }

    tile2i disembark(d.disembark_x, d.disembark_y);
    if (!enemy_transport_land_ok(disembark)) {
        disembark = enemy_transport_find_shore_tile(base.tile);
    }
    if (!enemy_transport_land_ok(disembark)) {
        // Last resort: stay embarked rather than dumping onto water.
        advance_action(ACTION_3_ENEMY_TRANSPORT_IDLE);
        return;
    }

    int index = 0;
    for (figure *f : map_figures()) {
        if (!f || !f->is_alive() || f->formation_id != d.formation_id) {
            continue;
        }

        tile2i pos = disembark.shifted(formation_layout_position(m->layout, f->index_in_formation));
        if (!enemy_transport_land_ok(pos)) {
            pos = disembark;
        }

        f->set_flag(e_figure_flag_invisible, false);
        f->map_figure_remove();
        f->tile = pos;
        if (auto *enemy = f->dcast_enemy()) {
            f->action_state = enemy->enemy_initial_action();
        } else {
            f->action_state = ACTION_151_ENEMY_INITIAL;
        }
        f->wait_ticks = 10 + index * 10;
        f->formation_at_rest = 0;
        f->allow_move_type = EMOVE_TERRAIN;
        f->map_figure_add();
        index++;
    }

    if (index <= 0) {
        // Cargo died while aboard — free the empty formation slot.
        m->num_figures = 0;
        for (int i = 0; i < formation::max_figures_count; i++) {
            m->figures[i] = 0;
        }
        m->in_use = false;
    } else {
        m->tile = disembark;
        m->home = disembark;
        m->standard_tile = disembark;
        m->destination = disembark;
        m->is_halted = 0;
        m->is_at_fort = 0;
    }

    d.formation_id = 0;
    d.ticks = 0;
    advance_action(ACTION_3_ENEMY_TRANSPORT_IDLE);
}

void figure_enemy_transport::kill_cargo() {
    auto &d = runtime_data();
    if (d.formation_id <= 0) {
        return;
    }

    const int fid = d.formation_id;
    for (figure *f : map_figures()) {
        if (!f || !f->is_alive() || f->formation_id != fid) {
            continue;
        }
        f->map_figure_remove();
        f->set_flag(e_figure_flag_invisible, false);
        f->kill();
    }

    formation *m = formation_get(fid);
    if (m && m->in_use) {
        m->num_figures = 0;
        for (int i = 0; i < formation::max_figures_count; i++) {
            m->figures[i] = 0;
        }
        m->in_use = false;
        m->is_halted = 0;
    }

    d.formation_id = 0;
}

void figure_enemy_transport::dismiss_cargo() {
    auto &d = runtime_data();
    if (d.formation_id <= 0) {
        return;
    }

    const int fid = d.formation_id;
    for (figure *f : map_figures()) {
        if (!f || !f->is_alive() || f->formation_id != fid) {
            continue;
        }
        f->map_figure_remove();
        f->set_flag(e_figure_flag_invisible, false);
        f->poof();
    }

    formation *m = formation_get(fid);
    if (m && m->in_use) {
        m->num_figures = 0;
        for (int i = 0; i < formation::max_figures_count; i++) {
            m->figures[i] = 0;
        }
        m->in_use = false;
        m->is_halted = 0;
    }

    d.formation_id = 0;
    advance_action(ACTION_3_ENEMY_TRANSPORT_IDLE);
}

void figure_enemy_transport::before_poof() {
    kill_cargo();
}

void figure_enemy_transport::kill() {
    kill_cargo();
    // Combat often calls figure::kill() first (DYING); corpse handling may bump
    // wait_ticks before we run — use an explicit one-shot wreck flag.
    auto &d = runtime_data();
    if (!d.wreck_spawned) {
        figure_shipwreck::create(tile());
        d.wreck_spawned = 1;
    }
    if (is_alive()) {
        base.wait_ticks = 1;
        figure_impl::kill();
    }
}

void figure_enemy_transport::figure_action() {
    // Prefer virtual kill() so shipwreck + cargo clear run even when combat
    // already set FIGURE_STATE_DYING via figure::kill().
    if (base.damage > base.max_damage()) {
        kill();
        return;
    }
    if (!is_alive()) {
        return;
    }
    // Pending auto-resolve: freeze sail/disembark like land formations.
    if (invasion_auto_resolve_figure_immune(&base)) {
        return;
    }

    assert(base.allow_move_type == EMOVE_WATER);

    release_empty_cargo();

    auto &d = runtime_data();

    // Keep embarked troops glued to the hull while sailing.
    if (has_troops()) {
        for (figure *f : map_figures()) {
            if (!f || !f->is_alive() || f->formation_id != d.formation_id) {
                continue;
            }
            // Destroy-goal leave_city sets ACTION_156 — do not snap them back aboard.
            if (f->action_state == ACTION_156_ENEMY_LEAVING) {
                continue;
            }
            f->map_figure_remove();
            f->tile = base.tile;
            f->wait_ticks = 30000;
            f->formation_at_rest = 1;
            f->allow_move_type = EMOVE_AMPHIBIAN;
            f->action_state = ACTION_152_ENEMY_WAITING;
            f->set_flag(e_figure_flag_invisible);
        }
    }

    switch (action_state()) {
    case ACTION_0_ENEMY_TRANSPORT_CREATED:
        d.ticks++;
        if (d.ticks >= 20) {
            d.ticks = 0;
            if (has_troops() && d.landing_x >= 0 && d.landing_y >= 0) {
                if (!sail_to_landing(tile2i(d.landing_x, d.landing_y))) {
                    advance_action(ACTION_3_ENEMY_TRANSPORT_IDLE);
                }
            } else {
                advance_action(ACTION_3_ENEMY_TRANSPORT_IDLE);
            }
        }
        break;

    case ACTION_1_ENEMY_TRANSPORT_SAILING: {
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            advance_action(ACTION_2_ENEMY_TRANSPORT_DISEMBARKING);
            d.ticks = 0;
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            // Prefer immediate shore unload; else re-route to alternate landing.
            tile2i shore = enemy_transport_find_shore_tile(base.tile);
            if (shore.valid()) {
                d.disembark_x = shore.x();
                d.disembark_y = shore.y();
                advance_action(ACTION_2_ENEMY_TRANSPORT_DISEMBARKING);
                d.ticks = 0;
            } else if (has_troops()) {
                tile2i alt = enemy_transport_find_alternate_landing(base.tile, 24);
                if (alt.valid() && sail_to_landing(alt)) {
                    // re-routed
                } else if (d.landing_x >= 0 && d.landing_y >= 0) {
                    d.ticks++;
                    if (d.ticks >= 50) {
                        d.ticks = 0;
                        if (!sail_to_landing(tile2i(d.landing_x, d.landing_y))) {
                            advance_action(ACTION_3_ENEMY_TRANSPORT_IDLE);
                        }
                    }
                } else {
                    advance_action(ACTION_3_ENEMY_TRANSPORT_IDLE);
                }
            } else {
                advance_action(ACTION_3_ENEMY_TRANSPORT_IDLE);
            }
        }
        break;
    }

    case ACTION_2_ENEMY_TRANSPORT_DISEMBARKING:
        d.ticks++;
        if (d.ticks >= ENEMY_TRANSPORT_DISEMBARK_TICKS) {
            if (has_troops()) {
                disembark_troops();
            } else {
                advance_action(ACTION_3_ENEMY_TRANSPORT_IDLE);
            }
        }
        break;

    case ACTION_3_ENEMY_TRANSPORT_IDLE:
        // Loaded but stranded (no path earlier): keep looking for a shore.
        if (has_troops()) {
            d.ticks++;
            if (d.ticks >= 50) {
                d.ticks = 0;
                tile2i shore = enemy_transport_find_shore_tile(base.tile);
                if (shore.valid()) {
                    d.disembark_x = shore.x();
                    d.disembark_y = shore.y();
                    advance_action(ACTION_2_ENEMY_TRANSPORT_DISEMBARKING);
                } else {
                    tile2i alt = enemy_transport_find_alternate_landing(base.tile, 24);
                    if (alt.valid() && sail_to_landing(alt)) {
                        // sailing again
                    } else if (d.landing_x >= 0 && d.landing_y >= 0) {
                        if (!sail_to_landing(tile2i(d.landing_x, d.landing_y))) {
                            // stay IDLE; retry next cooldown
                        }
                    }
                }
            }
        }
        break;

    default:
        break;
    }
}

void figure_enemy_transport::update_animation() {
    pcstr anim_key = "swim";
    switch (action_state()) {
    case ACTION_0_ENEMY_TRANSPORT_CREATED:
    case ACTION_2_ENEMY_TRANSPORT_DISEMBARKING:
    case ACTION_3_ENEMY_TRANSPORT_IDLE:
        anim_key = "idle";
        break;
    case ACTION_1_ENEMY_TRANSPORT_SAILING:
        anim_key = "swim";
        break;
    default:
        anim_key = "swim";
        break;
    }
    image_set_animation(anim_key);
}

declare_console_command_p(spawn_enemy_transport) {
    e_enemy_type enemy = (e_enemy_type)parse_integer_from<bstring32>(is);
    int tilex = parse_integer_from<bstring32>(is);
    int tiley = parse_integer_from<bstring32>(is);

    tile2i preferred = tile2i::invalid;
    if (tilex >= 0 && tiley >= 0) {
        preferred = tile2i(tilex, tiley);
    } else {
        const mouse &m = mouse::get();
        preferred = g_screen_city.update_city_view_coords({ m.x, m.y });
    }

    tile2i spawn = find_water_spawn_tile_for_transport(preferred);
    if (!spawn.valid()) {
        events::emit(event_city_warning{ "No water tile for enemy transport" });
        return;
    }

    e_figure_type ftype = enemy_transport_type_for(enemy);
    figure *f = figure_create(ftype, spawn, DIR_0_TOP_RIGHT);
    if (!f || !f->is_valid()) {
        events::emit(event_city_warning{ "Failed to spawn enemy transport" });
        return;
    }
    f->faction_id = 0;

    events::emit(event_city_warning{ "Spawned enemy transport" });
}
