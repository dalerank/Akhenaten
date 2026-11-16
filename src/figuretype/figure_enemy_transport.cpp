#include "figure_enemy_transport.h"

#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_warnings.h"
#include "core/calc.h"
#include "dev/debug.h"
#include "figure/figure_names.h"
#include "figure/route.h"
#include "game/game_events.h"
#include "grid/figure.h"
#include "grid/terrain.h"
#include "grid/water.h"
#include "input/mouse.h"
#include "js/js_game.h"
#include "scenario/invasion_auto_resolve.h"
#include "scenario/map.h"
#include "scenario/scenario.h"
#include "widget/widget_city.h"

const e_action_enemy_transport_tokens_t ANK_CONFIG_ENUM(e_action_enemy_transport_tokens)

enemy_transport_rules_t ANK_VARIABLE(enemy_transport_rules);

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

figure_id enemy_ship_player_ship_at(tile2i tile, figure_id self) {
    for (figure_id fid = map_figure_id_get(tile); fid > 0;) {
        figure* f = figure_get(fid);
        if (fid != self
            && (f->type == FIGURE_TRANSPORT_SHIP || f->type == FIGURE_WARSHIP || f->type == FIGURE_FISHING_BOAT)) {
            return fid;
        }
        fid = (f->next_figure != fid) ? f->next_figure : 0;
    }
    return 0;
}

figure_id enemy_ship_closest_player_ship(tile2i center, figure_id self, int size) {
    figure_id best_id = 0;
    int best_distance = 500000;
    const int x0 = center.x() - size / 2;
    const int y0 = center.y() - size / 2;
    for (int y = y0; y < y0 + size; y++) {
        for (int x = x0; x < x0 + size; x++) {
            const tile2i t(x, y);
            if (!t.valid()) {
                continue;
            }
            const figure_id fid = enemy_ship_player_ship_at(t, self);
            if (!fid) {
                continue;
            }
            const figure* f = figure_get(fid);
            const int dx = f->tile.x() - center.x();
            const int dy = f->tile.y() - center.y();
            const int distance = dx * dx + dy * dy;
            if (distance < best_distance) {
                best_id = fid;
                best_distance = distance;
            }
        }
    }
    return best_id;
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

bool enemy_transport_of_invasion_exists(int invasion_id) {
    for (figure* f : map_figures()) {
        auto* t = f ? smart_cast<figure_enemy_transport>(f) : nullptr;
        if (t && !f->is_dead() && t->invasion_id() == invasion_id) {
            return true;
        }
    }
    return false;
}

bool enemy_transport_of_invasion_loaded(int invasion_id) {
    for (figure* f : map_figures()) {
        auto* t = f ? smart_cast<figure_enemy_transport>(f) : nullptr;
        if (t && f->is_alive() && t->has_troops() && t->invasion_id() == invasion_id) {
            return true;
        }
    }
    return false;
}

void figure_enemy_transport::on_create() {
    figure_enemy::on_create();
    base.allow_move_type = EMOVE_WATER;
    base.terrain_usage = TERRAIN_USAGE_ANY;
    runtime_data() = {};
    runtime_data().landing_x = -1;
    runtime_data().landing_y = -1;
    runtime_data().secondary_action = ENEMY_TRANSPORT_SECONDARY_WAITING;
    advance_action(ACTION_8_ENEMY_TRANSPORT_WAITING);
}

void figure_enemy_transport::launch(const invasion_opts_t& opts, int soldiers, tile2i landing, int wait_ticks,
  int invasion_sequence) {
    auto& d = runtime_data();
    base.faction_id = 0;
    base.wait_ticks = (int16_t)wait_ticks;
    base.set_flag(e_figure_flag_invisible);
    base.name = figure_name_get(base.type);
    d.landing_x = (int16_t)landing.x();
    d.landing_y = (int16_t)landing.y();
    d.has_troops = 1;
    d.soldiers = (int16_t)soldiers;
    d.invasion_id = (int16_t)opts.invasion_id;
    d.invasion_sequence = (int16_t)invasion_sequence;
    d.nation = (uint8_t)opts.enemy_type;
    d.kind = (uint8_t)opts.kind;
    d.attack_type = (uint8_t)opts.attack_type;
    advance_action(ACTION_8_ENEMY_TRANSPORT_WAITING);
}

void figure_enemy_transport::move() {
    auto &d = runtime_data();
    const auto& cycle = transport_params().move_cycle;
    int ticks = 0;
    if (!cycle.empty()) {
        if (d.move_counter >= cycle.size()) {
            d.move_counter = 0;
        }
        ticks = cycle[d.move_counter];
        d.move_counter++;
    }
    base.move_ticks(ticks);
    base.height_adjusted_ticks = 0;
}

void figure_enemy_transport::action_wait() {
    auto& d = runtime_data();
    base.set_flag(e_figure_flag_invisible, false);
    d.moving = 0;
    if (--base.wait_ticks >= 1) {
        return;
    }
    base.wait_ticks = 0;
    base.source_tile = base.tile;
    if (d.has_troops) {
        tile2i dest;
        map_water_farthest_on_line(base.tile, landing(), dest);
        base.destination_tile = dest;
        advance_action(ACTION_13_ENEMY_TRANSPORT_GOING_TO_LANDING);
        route_remove();
        return;
    }
    base.destination_tile = scenario_map_river_exit();
    advance_action(ACTION_17_ENEMY_TRANSPORT_LEAVING);
}

void figure_enemy_transport::action_move() {
    move();
    if (direction() == DIR_FIGURE_REROUTE) {
        route_remove();
    } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
        kill();
    } else if (direction() == DIR_FIGURE_NONE) {
        runtime_data().moving = 0;
    }
}

void figure_enemy_transport::action_evade() {
    auto &d = runtime_data();
    const auto& rules = enemy_transport_rules;
    if (d.secondary_action == ENEMY_TRANSPORT_SECONDARY_FOLLOW_TARGET) {
        action_move();
        if (direction() == DIR_FIGURE_NONE) {
            d.secondary_action = ENEMY_TRANSPORT_SECONDARY_WAITING;
            d.moving = 0;
        }
        return;
    }
    if (d.secondary_action != ENEMY_TRANSPORT_SECONDARY_WAITING) {
        return;
    }
    d.moving = 0;
    if (++base.wait_ticks < rules.evade_ticks) {
        return;
    }
    base.wait_ticks = 0;
    figure* enemy = figure_get(enemy_ship_closest_player_ship(base.tile, base.id, rules.evade_range));
    if (!enemy || !enemy->id) {
        return;
    }
    int dir = calc_general_direction(enemy->tile, base.tile);
    if (dir > DIR_6_TOP_LEFT) {
        dir = DIR_7_TOP;
    }
    tile2i escape = map_water_escape_tile(base.tile, dir, rules.escape_distance);
    map_water_find_free_tile(escape);
    base.destination_tile = escape;
    route_remove();
    d.secondary_action = ENEMY_TRANSPORT_SECONDARY_FOLLOW_TARGET;
}

void figure_enemy_transport::unload(tile2i land) {
    auto &d = runtime_data();
    invasion_opts_t opts;
    opts.enemy_type = (e_enemy_type)d.nation;
    opts.kind = (e_invasion_spawn_kind)d.kind;
    opts.attack_type = (e_formation_attack_type)d.attack_type;
    opts.invasion_id = d.invasion_id;
    const invasion_army_spawn_t army
      = scenario_invasion_spawn_army(opts, d.soldiers, land, DIR_0_TOP_RIGHT, d.invasion_sequence);
    if (army.formations > 0) {
        base.wait_ticks = (int16_t)army.last_wait_ticks;
    }
    d.has_troops = 0;
    advance_action(ACTION_8_ENEMY_TRANSPORT_WAITING);
}

void figure_enemy_transport::action_go_to_landing() {
    move();
    if (direction() == DIR_FIGURE_NONE) {
        auto& d = runtime_data();
        d.moving = 0;
        tile2i land = landing();
        map_find_nearest_free_land_tile(land);
        if (map_terrain_is(land, TERRAIN_TREE | TERRAIN_ROCK | TERRAIN_ELEVATION)) {
            base.wait_ticks = enemy_transport_rules.landing_wait;
        }
        if (map_terrain_is(land, TERRAIN_WATER)) {
            if (!map_terrain_is(land, TERRAIN_ROAD)) {
                base.wait_ticks = enemy_transport_rules.landing_wait;
            }
        } else if (map_terrain_is(land, TERRAIN_BUILDING | TERRAIN_CANAL | TERRAIN_WALL | TERRAIN_GATEHOUSE)) {
            building* b = building_at(land);
            if (b && b->id) {
                g_city.maintenance.destroy_by_enemy(b);
            }
        }
        unload(land);
        scenario_invasion_landing_message(d.invasion_id, base.tile, d.invasion_sequence);
    } else if (direction() == DIR_FIGURE_REROUTE) {
        route_remove();
    } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
        kill();
    }
}

void figure_enemy_transport::action_go_away() {
    move();
    if (direction() == DIR_FIGURE_REROUTE) {
        route_remove();
        return;
    }
    if (direction() != DIR_FIGURE_CAN_NOT_REACH) {
        if (direction() != DIR_FIGURE_NONE) {
            return;
        }
        const tile2i entry = scenario_map_river_entry();
        const tile2i exit = scenario_map_river_exit();
        if (base.tile == entry) {
            base.destination_tile = exit;
            route_remove();
            return;
        }
        if (base.tile != exit) {
            base.destination_tile = entry;
            route_remove();
            return;
        }
        if (has_troops()) {
            route_remove();
            advance_action(ACTION_8_ENEMY_TRANSPORT_WAITING);
            return;
        }
    }
    kill();
}

void figure_enemy_transport::figure_action() {
    if (!is_alive()) {
        return;
    }
    if (invasion_auto_resolve_figure_immune(&base)) {
        return;
    }

    auto &d = runtime_data();
    const auto& rules = enemy_transport_rules;
    count_as_city_invader();
    d.moving = 1;
    const int max_hp = base.max_damage();
    const int hp = max_hp - base.damage;
    if (hp <= 0) {
        kill();
        return;
    }
    const int percent = calc_percentage(hp, max_hp);
    if (percent <= rules.damaged_percent && percent > 0) {
        advance_action(ACTION_10_ENEMY_TRANSPORT_EVADING);
        d.secondary_action = ENEMY_TRANSPORT_SECONDARY_WAITING;
        base.wait_ticks = rules.evade_wait;
    }

    if (++d.reroute_ticks > rules.reroute_ticks) {
        d.reroute_ticks = 0;
        route_remove();
    }

    switch (action_state()) {
    case ACTION_8_ENEMY_TRANSPORT_WAITING:
        action_wait();
        break;
    case ACTION_9_ENEMY_TRANSPORT_MOVING:
        action_move();
        break;
    case ACTION_10_ENEMY_TRANSPORT_EVADING:
        action_evade();
        break;
    case ACTION_12_ENEMY_TRANSPORT_IDLE:
        break;
    case ACTION_13_ENEMY_TRANSPORT_GOING_TO_LANDING:
        action_go_to_landing();
        break;
    case ACTION_17_ENEMY_TRANSPORT_LEAVING:
        action_go_away();
        break;
    default:
        advance_action(ACTION_17_ENEMY_TRANSPORT_LEAVING);
        break;
    }
}

void figure_enemy_transport::update_animation() {
    if (action_state() == FIGURE_ACTION_149_CORPSE) {
        image_set_animation(base.wait_ticks <= enemy_transport_rules.sinking_ticks ? "death" : "bubbles");
        return;
    }
    image_set_animation(runtime_data().moving ? "swim" : "idle");
}

declare_console_command_p(spawn_enemy_transport) {
    e_enemy_type enemy = (e_enemy_type)args.next_int(0);
    int tilex = args.next_int(0);
    int tiley = args.next_int(0);

    tile2i spawn = tile2i::invalid;
    if (tilex >= 0 && tiley >= 0) {
        spawn = tile2i(tilex, tiley);
    } else {
        const mouse &m = mouse::get();
        spawn = g_screen_city.update_city_view_coords({m.x, m.y});
    }

    if (!spawn.valid() || !map_water_find_free_tile(spawn)) {
        events::emit(event_city_warning{ "No water tile for enemy transport" });
        return;
    }

    figure* f = figure_create(enemy_transport_type_for(enemy), spawn, DIR_0_TOP_RIGHT);
    if (!f || !f->is_valid()) {
        events::emit(event_city_warning{ "Failed to spawn enemy transport" });
        return;
    }
    f->faction_id = 0;

    events::emit(event_city_warning{ "Spawned enemy transport" });
}
