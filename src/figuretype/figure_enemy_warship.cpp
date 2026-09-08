#include "figure_enemy_warship.h"

#include "city/city_figures.h"
#include "city/city_warnings.h"
#include "core/calc.h"
#include "core/string.h"
#include "dev/debug.h"
#include "figure/combat.h"
#include "figure/route.h"
#include "figuretype/figure_missile.h"
#include "figuretype/figure_shipwreck.h"
#include "figuretype/figure_transport_ship.h"
#include "figuretype/figure_enemy_transport.h"
#include "figuretype/figure_war_ship.h"
#include "game/game_events.h"
#include "graphics/image_desc.h"
#include "grid/figure.h"
#include "grid/terrain.h"
#include "js/js_game.h"
#include "scenario/scenario.h"
#include "scenario/invasion_auto_resolve.h"
#include "sound/effect.h"
#include "sound/sound.h"
#include "widget/widget_city.h"
#include "input/mouse.h"

const e_action_enemy_warship_tokens_t ANK_CONFIG_ENUM(e_action_enemy_warship_tokens)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_enemy_warship_generic)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_assyrian_war_ship)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_canaanite_war_ship)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_egyptian_galera)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_egyptian_war_ship)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_hittite_war_ship)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_hyksos_war_ship)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_kushite_war_ship)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_libian_war_ship)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_nubian_war_ship)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_persian_war_ship)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_phoenician_war_ship)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_roman_war_ship)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_seapeople_war_ship)

namespace {

constexpr int ENEMY_WARSHIP_MISSILE_RANGE = 10;
constexpr int ENEMY_WARSHIP_ENGAGE_RANGE = 40;
constexpr int ENEMY_WARSHIP_RAM_INTERVAL = 50;
constexpr int ENEMY_WARSHIP_MISSILE_DELAY = 200;

bool is_water_figure(const figure *f) {
    return f->allow_move_type == EMOVE_WATER || f->allow_move_type == EMOVE_DEEPWATER;
}

bool is_player_fleet_target(figure *f) {
    if (!f || !f->is_valid() || f->is_dead()) {
        return false;
    }
    if (f->is_enemy()) {
        return false;
    }
    // Player navy only (78/77). Enum 100/101 are unused lang slots — not aliases.
    if (f->type == FIGURE_WARSHIP || f->type == FIGURE_TRANSPORT_SHIP) {
        return true;
    }
    return is_water_figure(f) && !f->is_enemy();
}

bool is_shore_player_target(figure *f) {
    if (!f || !f->is_valid() || f->is_dead()) {
        return false;
    }
    if (f->is_enemy()) {
        return false;
    }
    if (is_water_figure(f)) {
        return false;
    }
    return f->is_soldier() || f->category() == figure_category_military;
}

int enemy_warship_target_priority(figure *f) {
    if (is_player_fleet_target(f)) {
        if (f->type == FIGURE_TRANSPORT_SHIP) {
            if (auto transport = smart_cast<figure_transport_ship>(f)) {
                if (transport->has_troops()) {
                    return 40;
                }
                return 10;
            }
        }
        return 30;
    }
    if (is_shore_player_target(f)) {
        return 20;
    }
    return 0;
}

tile2i find_water_spawn_tile(tile2i preferred) {
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

e_figure_type enemy_warship_type_for(e_enemy_type enemy) {
    switch (enemy) {
    case ENEMY_1_ASSYRIAN: return FIGURE_ENEMY_ASSYRIAN_WAR_SHIP;
    case ENEMY_2_CANAANITE: return FIGURE_ENEMY_CANAANITE_WAR_SHIP;
    case ENEMY_3_EGYPTIAN: return FIGURE_ENEMY_EGYPTIAN_WAR_SHIP;
    case ENEMY_4_HITTITE: return FIGURE_ENEMY_HITTITE_WAR_SHIP;
    case ENEMY_5_HYKSOS: return FIGURE_ENEMY_HYKSOS_WAR_SHIP;
    case ENEMY_6_KUSHITE: return FIGURE_ENEMY_KUSHITE_WAR_SHIP;
    case ENEMY_7_LIBIAN: return FIGURE_ENEMY_LIBIAN_WAR_SHIP;
    case ENEMY_8_NUBIAN: return FIGURE_ENEMY_NUBIAN_WAR_SHIP;
    case ENEMY_9_PERSIAN: return FIGURE_ENEMY_PERSIAN_WAR_SHIP;
    case ENEMY_10_PHOENICIAN: return FIGURE_ENEMY_PHOENICIAN_WAR_SHIP;
    case ENEMY_11_ROMAN: return FIGURE_ENEMY_ROMAN_WAR_SHIP;
    case ENEMY_12_SEAPEOPLE: return FIGURE_ENEMY_SEAPEOPLE_WAR_SHIP;
    case ENEMY_0_BARBARIAN:
    default:
        return FIGURE_ENEMY_WARSHIP;
    }
}

void figure_enemy_warship::on_create() {
    figure_enemy::on_create();
    base.allow_move_type = EMOVE_WATER;
    base.terrain_usage = TERRAIN_USAGE_ANY;
    runtime_data().target_id = 0;
    runtime_data().invasion_sequence = 0;
    runtime_data().wreck_spawned = 0;
    advance_action(ACTION_0_ENEMY_WARSHIP_CREATED);
}

bool figure_enemy_warship::is_attack() const {
    return action_state() == ACTION_3_ENEMY_WARSHIP_ATTACK;
}

void figure_enemy_warship::check_sink() {
    if (base.damage > base.max_damage()) {
        kill();
    }
}

void figure_enemy_warship::kill() {
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

figure_id figure_enemy_warship::find_combat_target(int max_distance) {
    figure_id best_id = 0;
    int best_priority = 0;
    int best_distance = 10000;

    for (figure *f : map_figures()) {
        if (!f || f->id == id()) {
            continue;
        }

        const int priority = enemy_warship_target_priority(f);
        if (priority <= 0) {
            continue;
        }

        const int distance = calc_maximum_distance(base.tile, f->tile);
        if (distance > max_distance) {
            continue;
        }

        if (priority > best_priority || (priority == best_priority && distance < best_distance)) {
            best_priority = priority;
            best_distance = distance;
            best_id = f->id;
        }
    }

    return best_id;
}

void figure_enemy_warship::launch_missile_at(figure *target) {
    if (!target || !target->is_valid()) {
        return;
    }

    base.wait_ticks++;
    if (base.wait_ticks < ENEMY_WARSHIP_MISSILE_DELAY) {
        return;
    }

    base.wait_ticks = 0;
    if (!figure_movement_can_launch_cross_country_missile(base.tile, target->tile)) {
        return;
    }

    figure_missile::create(id(), base.tile, target->tile, FIGURE_ARROW);
    events::emit(event_sound_effect{ SOUND_EFFECT_ARROW });
}

void figure_enemy_warship::ram_target(figure *target) {
    if (!target || !target->is_valid()) {
        return;
    }

    base.wait_ticks++;
    if (base.wait_ticks < ENEMY_WARSHIP_RAM_INTERVAL) {
        return;
    }

    base.wait_ticks = 0;

    const int attack = base.attack_value();
    const int defense = target->defense_value();
    int net = attack - defense;
    if (net < 0) {
        net = 0;
    }

    target->apply_damage(net, id());
    if (target->damage > target->max_damage()) {
        if (auto warship = smart_cast<figure_warship>(target)) {
            warship->kill();
        } else if (auto transport = smart_cast<figure_enemy_transport>(target)) {
            transport->kill();
        } else {
            target->kill();
        }
    }

    base.apply_damage(net / 2, target->id);
    check_sink();
}

void figure_enemy_warship::combat_tick_vs_target(figure *target, int max_pursue_distance) {
    if (!target || !target->is_valid() || target->is_dead()) {
        runtime_data().target_id = 0;
        return;
    }

    const int distance = calc_maximum_distance(base.tile, target->tile);

    if (is_player_fleet_target(target) && distance <= 1) {
        advance_action(ACTION_3_ENEMY_WARSHIP_ATTACK);
        ram_target(target);
        return;
    }

    if (distance <= ENEMY_WARSHIP_MISSILE_RANGE
        && figure_movement_can_launch_cross_country_missile(base.tile, target->tile)) {
        advance_action(ACTION_3_ENEMY_WARSHIP_ATTACK);
        launch_missile_at(target);
        return;
    }

    if (distance > max_pursue_distance) {
        runtime_data().target_id = 0;
        return;
    }

    if (action_state() != ACTION_2_ENEMY_WARSHIP_PURSUING) {
        base.destination_tile = target->tile;
        base.source_tile = base.tile;
        advance_action(ACTION_2_ENEMY_WARSHIP_PURSUING);
        route_remove();
    }

    base.move_ticks(1);
    base.height_adjusted_ticks = 0;
    if (direction() == DIR_FIGURE_REROUTE) {
        route_remove();
    } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
        runtime_data().target_id = 0;
        advance_action(ACTION_1_ENEMY_WARSHIP_IDLE);
    }
}

void figure_enemy_warship::figure_action() {
    check_sink();
    if (!is_alive()) {
        return;
    }
    if (invasion_auto_resolve_figure_immune(&base)) {
        return;
    }

    assert(base.allow_move_type == EMOVE_WATER);

    if (action_state() == ACTION_0_ENEMY_WARSHIP_CREATED) {
        base.wait_ticks++;
        if (base.wait_ticks >= 20) {
            base.wait_ticks = 0;
            advance_action(ACTION_1_ENEMY_WARSHIP_IDLE);
        }
        return;
    }

    auto &d = runtime_data();
    figure *target = figure_get(d.target_id);
    if (!target || !target->is_valid() || target->is_dead()) {
        d.target_id = find_combat_target(ENEMY_WARSHIP_ENGAGE_RANGE);
        target = figure_get(d.target_id);
    }

    if (!target) {
        advance_action(ACTION_1_ENEMY_WARSHIP_IDLE);
        return;
    }

    combat_tick_vs_target(target, ENEMY_WARSHIP_ENGAGE_RANGE);
}

void figure_enemy_warship::update_animation() {
    // Enemy ship configs expose swim / idle / death (no walk/attack keys).
    pcstr anim_key = "swim";
    switch (action_state()) {
    case ACTION_0_ENEMY_WARSHIP_CREATED:
    case ACTION_1_ENEMY_WARSHIP_IDLE:
        anim_key = "idle";
        break;
    case ACTION_3_ENEMY_WARSHIP_ATTACK:
    case ACTION_2_ENEMY_WARSHIP_PURSUING:
        anim_key = "swim";
        break;
    default:
        anim_key = "swim";
        break;
    }
    image_set_animation(anim_key);
}

declare_console_command_p(spawn_enemy_warship) {
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

    tile2i spawn = find_water_spawn_tile(preferred);
    if (!spawn.valid()) {
        events::emit(event_city_warning{ "No water tile for enemy warship" });
        return;
    }

    e_figure_type ftype = enemy_warship_type_for(enemy);
    figure *f = figure_create(ftype, spawn, DIR_0_TOP_RIGHT);
    if (!f || !f->is_valid()) {
        events::emit(event_city_warning{ "Failed to spawn enemy warship" });
        return;
    }
    f->faction_id = 0;

    events::emit(event_city_warning{ "Spawned enemy warship" });
}
