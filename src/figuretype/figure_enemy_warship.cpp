#include "figure_enemy_warship.h"

#include "city/city_figures.h"
#include "city/city_warnings.h"
#include "core/calc.h"
#include "core/random.h"
#include "dev/debug.h"
#include "figure/figure_names.h"
#include "figure/formation.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "figuretype/figure_enemy_transport.h"
#include "figuretype/figure_missile.h"
#include "figuretype/figure_transport_ship.h"
#include "figuretype/figure_war_ship.h"
#include "game/game.h"
#include "game/game_events.h"
#include "grid/grid.h"
#include "grid/routing/routing.h"
#include "grid/water.h"
#include "input/mouse.h"
#include "js/js_game.h"
#include "scenario/invasion_auto_resolve.h"
#include "scenario/map.h"
#include "scenario/scenario.h"
#include "sound/sound.h"
#include "widget/widget_city.h"

#include <algorithm>
#include <iterator>

const e_action_enemy_warship_tokens_t ANK_CONFIG_ENUM(e_action_enemy_warship_tokens)

enemy_warship_rules_t ANK_VARIABLE(enemy_warship_rules);

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

    enum { ENEMY_WARSHIP_MONTHS_PER_YEAR = 12 };

    // OG ship_play_ram_sound: effect 10 + divisor (ship_collision_beam .. ship_collision_stern).
    constexpr e_sound_effect ram_sounds[] = {
      SOUND_EFFECT_SHIP_COLLISION_BEAM,
      SOUND_EFFECT_SHIP_COLLISION_FORE_QUARTER,
      SOUND_EFFECT_SHIP_COLLISION_AFT_QUARTER,
      SOUND_EFFECT_SHIP_COLLISION_BOW,
      SOUND_EFFECT_SHIP_COLLISION_STERN,
    };

    int facing_direction(const figure* f) {
        return f->direction > DIR_7_TOP ? f->previous_tile_direction : f->direction;
    }

    int clamp_heading(int dir) {
        return std::clamp<int>(dir, DIR_0_TOP_RIGHT, DIR_7_TOP);
    }

    // OG figure_military_is_away_on_mission.
    bool away_on_mission(figure* f) {
        switch (f->type) {
        case FIGURE_ARCHER:
        case FIGURE_INFANTRY:
        case FIGURE_FCHARIOTEER: {
            const formation* m = formation_get(f->formation_id);
            return m && m->request_event_id >= 0;
        }
        case FIGURE_TRANSPORT_SHIP: {
            auto* ship = smart_cast<figure_transport_ship>(f);
            return ship && ship->request_event_id() >= 0;
        }
        case FIGURE_WARSHIP: {
            auto* ship = smart_cast<figure_warship>(f);
            return ship && ship->request_event_id() >= 0;
        }
        default:
            return false;
        }
    }

    // OG figure_ship_direction_table[target heading * 8 + own heading].
    int ram_divisor(int target_heading, int own_heading) {
        const auto& rows = enemy_warship_rules.ram_divisors;
        if (target_heading < 0 || target_heading >= (int)rows.size()) {
            return 1;
        }
        const auto& own = rows[target_heading].own;
        if (own_heading < 0 || own_heading >= (int)own.size()) {
            return 1;
        }
        return std::max<int>(1, own[own_heading]);
    }

    bool is_land_troop(e_figure_type type) {
        return type == FIGURE_ARCHER || type == FIGURE_INFANTRY || type == FIGURE_FCHARIOTEER;
    }

    // OG enemy_landing_water_tile: the free water tile at the first landing point.
    bool landing_water_tile(tile2i& tile) {
        for (const tile2i& landing : g_scenario.disembark_points) {
            if (landing.valid()) {
                tile = landing;
                map_water_find_free_tile(tile);
                return true;
            }
        }
        return false;
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
    runtime_data() = {};
    runtime_data().leave_month = (uint8_t)game.simtime.month;
    advance_action(ACTION_8_ENEMY_WARSHIP_WAITING);
}

void figure_enemy_warship::launch(int wait_ticks, int invasion_sequence) {
    auto& d = runtime_data();
    base.faction_id = 0;
    base.wait_ticks = (int16_t)wait_ticks;
    base.set_flag(e_figure_flag_invisible);
    base.name = figure_name_get(base.type);
    base.damage = 0;
    d.invasion_sequence = (int16_t)invasion_sequence;
    d.leave_month = (uint8_t)game.simtime.month;
    advance_action(ACTION_8_ENEMY_WARSHIP_WAITING);
}

bool figure_enemy_warship::is_attack() const {
    return action_state() == ACTION_10_ENEMY_WARSHIP_ATTACKING;
}

void figure_enemy_warship::move_ticks_at_speed(int speed) {
    const auto& cycles = enemy_warship_rules.speed_cycles;
    if (cycles.empty()) {
        return;
    }
    const auto& ticks = cycles[std::clamp<int>(speed, 0, (int)cycles.size() - 1)].ticks;
    if (ticks.empty()) {
        return;
    }
    auto& d = runtime_data();
    int walk = ticks[0];
    if (ticks.size() > 1) {
        const int pos = std::min<int>(d.speed_counter, (int)ticks.size() - 1);
        walk = ticks[pos];
        d.speed_counter = (pos + 1 == (int)ticks.size()) ? 0 : (uint8_t)(pos + 1);
    }
    if (walk > 0) {
        base.move_ticks(walk);
        base.height_adjusted_ticks = 0;
    }
}

void figure_enemy_warship::ship_move(bool cautious) {
    auto &d = runtime_data();
    const auto& rules = enemy_warship_rules;
    const auto& p = warship_params();
    if (base.tile == base.destination_tile && direction() == DIR_FIGURE_NONE) {
        return;
    }
    switch (d.move_mode) {
    case ENEMY_WARSHIP_MOVE_FULL_SPEED:
        if (cautious) {
            if (++d.move_count >= p.ship_moves) {
                d.move_count = 0;
                d.move_mode = ENEMY_WARSHIP_MOVE_RESTING;
                return;
            }
            if (base.previous_tile_direction != base.direction) {
                d.move_steps = 0;
            }
            if (base.tile.x() != d.step_x || base.tile.y() != d.step_y) {
                d.step_x = (int16_t)base.tile.x();
                d.step_y = (int16_t)base.tile.y();
                d.move_steps++;
            }
            if (d.move_steps >= p.ship_steps) {
                move_ticks_at_speed(p.speed);
                return;
            }
        }
        move_ticks_at_speed(std::min<int>(p.speed * 2, rules.full_speed_max));
        return;

    case ENEMY_WARSHIP_MOVE_SLOW:
        move_ticks_at_speed(calc_adjust_with_percentage<int>(p.speed, rules.slow_speed_percent));
        if (++d.move_count >= rules.mode_change_ticks) {
            d.move_count = 0;
            d.move_mode = ENEMY_WARSHIP_MOVE_FULL_SPEED;
        }
        return;

    case ENEMY_WARSHIP_MOVE_RESTING:
        if (++d.move_count >= rules.mode_change_ticks) {
            d.move_count = 0;
            d.move_mode = ENEMY_WARSHIP_MOVE_SLOW;
        }
        return;
    }
}

// OG enemy_warship_find_target_at: best (score - distance) among the player's troops in missile range and its ships,
// in the line of fire.
figure_id figure_enemy_warship::find_target(int range) const {
    const auto& rules = enemy_warship_rules;
    figure_id best_id = 0;
    int best_score = 0;
    int best_distance = range;
    for (figure *f : map_figures()) {
        if (!f || !f->is_alive() || f->action_state == FIGURE_ACTION_149_CORPSE || away_on_mission(f)) {
            continue;
        }
        const int distance = calc_maximum_distance(base.tile, f->tile);
        int score = 0;
        switch (f->type) {
        case FIGURE_ARCHER:
        case FIGURE_INFANTRY:
        case FIGURE_FCHARIOTEER:
            if (distance > params().missile_range) {
                continue;
            }
            score = rules.score_land_enemy;
            break;
        case FIGURE_TRADE_SHIP:
        case FIGURE_FISHING_BOAT:
            score = rules.score_boat;
            break;
        case FIGURE_TRANSPORT_SHIP: {
            auto* transport = smart_cast<figure_transport_ship>(f);
            score = (transport && transport->has_troops()) ? rules.score_loaded_transport : rules.score_transport;
            break;
        }
        case FIGURE_WARSHIP:
            score = rules.score_warship;
            break;
        default:
            continue;
        }
        if (score - distance > best_score - best_distance
            && figure_movement_can_launch_cross_country_missile(base.tile, f->tile)) {
            best_id = f->id;
            best_distance = distance;
            best_score = score;
        }
    }
    return best_id;
}

void figure_enemy_warship::fire_missile_at(tile2i target) {
    if (base.attack_image_offset == 1 && target.valid()) {
        figure_missile::create(id(), base.tile, target, FIGURE_SPEAR);
    }
    if (++base.attack_image_offset > enemy_warship_rules.shoot_ticks) {
        base.attack_image_offset = 0;
    }
}

// OG enemy_warship_shoot.
void figure_enemy_warship::shoot() {
    tile2i target_tile = tile2i::invalid;
    if (++base.wait_ticks_missile > params().missile_delay) {
        base.wait_ticks_missile = 0;
        figure* target = figure_get(find_target(params().missile_range));
        if (!target || !target->id) {
            base.attack_image_offset = 0;
        } else {
            base.attack_image_offset = 1;
            target_tile = target->tile;
            base.direction = (uint8_t)calc_missile_shooter_direction(base.tile, target_tile);
        }
    }
    if (base.attack_image_offset) {
        fire_missile_at(target_tile);
    }
}

// OG ship_find_ram_target: a player ship on the own tile, else on the tile ahead.
figure_id figure_enemy_warship::find_ram_target() const {
    if (base.direction > DIR_7_TOP) {
        return 0;
    }
    const figure_id here = enemy_ship_player_ship_at(base.tile, base.id);
    if (here) {
        return here;
    }
    return enemy_ship_player_ship_at(tile2i(base.tile.grid_offset() + map_grid_direction_delta(base.direction)),
      base.id);
}

void figure_enemy_warship::action_wait() {
    if (--base.wait_ticks >= 1) {
        return;
    }
    base.wait_ticks = 0;
    base.set_flag(e_figure_flag_invisible, false);
    base.source_tile = base.tile;
    base.destination_tile = scenario_map_river_entry();
    advance_action(ACTION_17_ENEMY_WARSHIP_PATROLLING);
    route_remove();
}

void figure_enemy_warship::action_move() {
    ship_move(false);
    runtime_data().moving = 1;
    base.set_flag(e_figure_flag_invisible, false);
    if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
        route_remove();
    }
}

// OG enemy_warship_ram.
void figure_enemy_warship::action_ram() {
    auto& d = runtime_data();
    const auto& rules = enemy_warship_rules;
    ship_move(true);
    d.moving = 1;
    if (d.ram_cooldown != 0) {
        d.ram_cooldown = (uint8_t)std::clamp<int>(d.ram_cooldown - 1, 0, rules.ram_cooldown);
    } else if (figure* target = figure_get(find_ram_target()); target && target->id) {
        int reduce = 0;
        if (target->type == FIGURE_WARSHIP && target->action_state == ACTION_20_WARSHIP_DOCKED) {
            reduce = rules.docked_target_reduction;
        }
        const int divisor = ram_divisor(facing_direction(target), base.direction);
        const int slow = base.attack_value();
        const int fast = calc_adjust_with_percentage<int>(slow, rules.fast_ram_percent);
        const int damage = ((d.move_steps < warship_params().ship_steps ? fast : slow) - reduce) / divisor;
        if (divisor >= 1 && divisor <= (int)std::size(ram_sounds)) {
            events::emit(event_sound_effect{ram_sounds[divisor - 1]});
        }
        target->apply_damage(damage, id());
        route_remove();
        const int turn = (random_byte() & 2) - 1;
        base.direction = (uint8_t)clamp_heading(base.direction + turn);
        target->direction = (uint8_t)clamp_heading(target->direction - turn);
        d.ram_cooldown = (uint8_t)rules.ram_cooldown;
        advance_action(ACTION_10_ENEMY_WARSHIP_ATTACKING);
        d.target_id = 0;
        figure_create_explosion_cloud(target->tile, 0);
    }
    if (direction() == DIR_FIGURE_NONE) {
        advance_action(ACTION_10_ENEMY_WARSHIP_ATTACKING);
        d.secondary_action = ENEMY_WARSHIP_SECONDARY_WAITING;
        return;
    }
    if (direction() == DIR_FIGURE_REROUTE) {
        route_remove();
    } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
        kill();
        route_remove();
    }
}

// OG enemy_warship_evade.
void figure_enemy_warship::action_evade() {
    auto& d = runtime_data();
    const auto& rules = enemy_warship_rules;
    if (d.secondary_action == ENEMY_WARSHIP_SECONDARY_SAILING) {
        action_move();
        if (direction() == DIR_FIGURE_NONE) {
            d.secondary_action = ENEMY_WARSHIP_SECONDARY_WAITING;
        }
        return;
    }
    if (d.secondary_action != ENEMY_WARSHIP_SECONDARY_WAITING) {
        return;
    }
    if (++base.wait_ticks < rules.evade_ticks) {
        return;
    }
    base.wait_ticks = 0;
    figure* enemy = figure_get(enemy_ship_closest_player_ship(base.tile, base.id, rules.evade_range));
    if (!enemy || !enemy->id) {
        advance_action(ACTION_17_ENEMY_WARSHIP_PATROLLING);
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
    d.secondary_action = ENEMY_WARSHIP_SECONDARY_SAILING;
}

// OG enemy_warship_attack: pick a target over the whole map, then shoot it and ram ships for up to attack_ticks.
void figure_enemy_warship::action_attack() {
    auto& d = runtime_data();
    const auto& rules = enemy_warship_rules;
    if (d.secondary_action != ENEMY_WARSHIP_SECONDARY_FOLLOW_TARGET) {
        if (d.secondary_action != ENEMY_WARSHIP_SECONDARY_WAITING) {
            return;
        }
        figure* target = figure_get(find_target(GRID_LENGTH));
        if (!target || !target->id) {
            advance_action(ACTION_17_ENEMY_WARSHIP_PATROLLING);
            return;
        }
        const bool on_land = map_water_grid(target->tile.grid_offset()) < 0;
        if (is_land_troop(target->type) || target->type == FIGURE_TRANSPORT_SHIP || target->type == FIGURE_WARSHIP) {
            if (anti_scum_random_15bit() & 1) {
                d.leave_month = (uint8_t)((game.simtime.month + 1) % ENEMY_WARSHIP_MONTHS_PER_YEAR);
            }
        }
        if (is_land_troop(target->type)) {
            base.destination_tile = base.tile;
        } else if (on_land) {
            const tile2i shore(base.tile.x() < target->tile.x() ? target->tile.x() - 1 : target->tile.x(),
              base.tile.y() < target->tile.y() ? target->tile.y() - 1 : target->tile.y());
            map_routing_calculate_distances_water_boat(base.tile);
            base.destination_tile = map_routing_distance(shore) > 0 ? shore : base.tile;
        } else {
            base.destination_tile = target->tile;
            d.moving = 1;
        }
        d.secondary_action = ENEMY_WARSHIP_SECONDARY_FOLLOW_TARGET;
        base.direction = base.previous_tile_direction;
        d.target_id = target->id;
        route_remove();
        return;
    }

    figure* target = figure_get(d.target_id);
    if (!target) {
        return;
    }
    const int distance = calc_maximum_distance(base.tile, target->tile);
    bool in_range = false;
    if (distance < params().missile_range) {
        in_range = true;
        if (++base.wait_ticks_missile > params().missile_delay) {
            base.wait_ticks_missile = 0;
            base.attack_image_offset = d.target_id != 0;
        } else {
            base.attack_image_offset = 0;
        }
    } else {
        base.attack_image_offset = 0;
    }
    if (base.attack_image_offset) {
        fire_missile_at(target->tile);
    }
    if (is_land_troop(target->type)) {
        if (in_range) {
            d.moving = 0;
        }
    } else {
        action_ram();
    }
    base.wait_ticks++;
    if (direction() == DIR_FIGURE_NONE || base.wait_ticks >= rules.attack_ticks) {
        base.wait_ticks = 0;
        d.secondary_action = ENEMY_WARSHIP_SECONDARY_WAITING;
        route_remove();
    }
}

// OG enemy_warship_patrol: river entry -> landing water -> river exit and back, attacking every 75 + rand(30) ticks.
void figure_enemy_warship::action_patrol() {
    auto& d = runtime_data();
    const auto& rules = enemy_warship_rules;
    ship_move(false);
    d.moving = 1;
    base.wait_ticks++;
    if ((anti_scum_random_15bit() % rules.patrol_random_ticks) + rules.patrol_base_ticks <= base.wait_ticks) {
        base.wait_ticks = 0;
        advance_action(ACTION_10_ENEMY_WARSHIP_ATTACKING);
        d.secondary_action = ENEMY_WARSHIP_SECONDARY_WAITING;
    }
    if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
        route_remove();
        return;
    }
    if (direction() != DIR_FIGURE_NONE) {
        return;
    }
    tile2i landing;
    const bool found = landing_water_tile(landing);
    const tile2i entry = scenario_map_river_entry();
    const tile2i exit = scenario_map_river_exit();
    if (base.tile == entry) {
        base.destination_tile = found ? landing : exit;
    } else if (!found || base.tile != landing) {
        base.destination_tile = entry;
    } else {
        base.destination_tile = exit;
    }
    advance_action(ACTION_17_ENEMY_WARSHIP_PATROLLING);
    route_remove();
}

void figure_enemy_warship::action_leave() {
    ship_move(false);
    runtime_data().moving = 1;
    if (direction() == DIR_FIGURE_REROUTE) {
        route_remove();
        return;
    }
    if (direction() == DIR_FIGURE_CAN_NOT_REACH || direction() == DIR_FIGURE_NONE) {
        poof();
    }
}

void figure_enemy_warship::figure_action() {
    if (!is_alive()) {
        return;
    }
    if (invasion_auto_resolve_figure_immune(&base)) {
        return;
    }

    auto& d = runtime_data();
    const auto& rules = enemy_warship_rules;
    const bool egyptian = egyptian_action();
    d.moving = 0;
    if (!egyptian) {
        count_as_city_invader();
    }
    const int max_hp = warship_params().hit_points;
    const int hp = max_hp - base.damage;
    if (hp <= 0) {
        kill();
        return;
    }
    const int percent = calc_percentage(hp, max_hp);
    if (percent <= rules.damaged_percent && percent > 0) {
        advance_action(ACTION_12_ENEMY_WARSHIP_EVADING);
        d.secondary_action = ENEMY_WARSHIP_SECONDARY_WAITING;
    }
    if ((d.leave_month + rules.stay_months) % ENEMY_WARSHIP_MONTHS_PER_YEAR == game.simtime.month) {
        advance_action(ACTION_18_ENEMY_WARSHIP_LEAVING);
        base.destination_tile = scenario_map_river_exit();
    }
    if (++d.reroute_ticks > rules.reroute_ticks) {
        d.reroute_ticks = 0;
        route_remove();
    }

    switch (action_state()) {
    case ACTION_8_ENEMY_WARSHIP_WAITING:
        action_wait();
        break;
    case ACTION_9_ENEMY_WARSHIP_RAMMING:
        action_ram();
        break;
    case ACTION_10_ENEMY_WARSHIP_ATTACKING:
        action_attack();
        return;
    case ACTION_11_ENEMY_WARSHIP_MOVING:
        action_move();
        break;
    case ACTION_12_ENEMY_WARSHIP_EVADING:
        action_evade();
        break;
    case ACTION_17_ENEMY_WARSHIP_PATROLLING:
        action_patrol();
        break;
    case ACTION_18_ENEMY_WARSHIP_LEAVING:
        action_leave();
        return;
    default:
        advance_action(ACTION_17_ENEMY_WARSHIP_PATROLLING);
        return;
    }
    if (!egyptian && is_alive()) {
        shoot();
    }
}

void figure_enemy_warship::update_animation() {
    if (action_state() == FIGURE_ACTION_149_CORPSE) {
        image_set_animation(base.wait_ticks <= enemy_warship_rules.sinking_ticks ? "death" : "bubbles");
        return;
    }
    const auto& d = runtime_data();
    image_set_animation(d.moving && d.move_mode != ENEMY_WARSHIP_MOVE_RESTING ? "swim" : "idle");
}

declare_console_command_p(spawn_enemy_warship) {
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
        events::emit(event_city_warning{"No water tile for enemy warship"});
        return;
    }

    figure* f = figure_create(enemy_warship_type_for(enemy), spawn, DIR_0_TOP_RIGHT);
    if (!f || !f->is_valid()) {
        events::emit(event_city_warning{"Failed to spawn enemy warship"});
        return;
    }
    f->faction_id = 0;

    events::emit(event_city_warning{"Spawned enemy warship"});
}
