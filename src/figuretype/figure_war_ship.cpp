#include "figure_war_ship.h"

#include "building/building_shipyard.h"
#include "building/building_warship_wharf.h"
#include "city/city.h"
#include "city/city_figures.h"
#include "core/calc.h"
#include "figure/combat.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "figuretype/figure_enemy_transport.h"
#include "figuretype/figure_enemy_warship.h"
#include "figuretype/figure_missile.h"
#include "figuretype/figure_shipwreck.h"
#include "core/random.h"
#include "game/game_events.h"
#include "grid/figure.h"
#include "grid/terrain.h"
#include "grid/water.h"
#include "scenario/map.h"
#include "scenario/scenario.h"
#include "sound/effect.h"
#include "sound/sound.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_warship)

namespace {

// OG figure_ship_direction_table reduced: divisor from circular heading delta.
int ram_direction_divisor(int target_dir, int own_dir) {
    int delta = (own_dir - target_dir) & 7;
    if (delta > 4) {
        delta = 8 - delta;
    }
    switch (delta) {
    case 0: return 5; // same heading
    case 1: return 3;
    case 2: return 1; // strongest glancing / broadside
    case 3: return 2;
    default: return 4; // opposite
    }
}

bool is_enemy(figure *f) {
    return f && f->is_valid() && !f->is_dead() && (f->is_enemy() || f->category() == figure_category_hostile);
}

bool is_enemy_ship(figure *f) {
    return is_enemy(f) && (smart_cast<figure_enemy_transport>(f) || smart_cast<figure_enemy_warship>(f));
}

tile2i tile_ahead(tile2i tile, int direction) {
    switch (direction) {
    case DIR_0_TOP_RIGHT: tile.shift(0, -1); break;
    case DIR_1_RIGHT: tile.shift(1, -1); break;
    case DIR_2_BOTTOM_RIGHT: tile.shift(1, 0); break;
    case DIR_3_BOTTOM: tile.shift(1, 1); break;
    case DIR_4_BOTTOM_LEFT: tile.shift(0, 1); break;
    case DIR_5_LEFT: tile.shift(-1, 1); break;
    case DIR_6_TOP_LEFT: tile.shift(-1, 0); break;
    case DIR_7_TOP: tile.shift(-1, -1); break;
    default: break;
    }
    return tile;
}

bool usable_water(tile2i tile) {
    return tile.valid()
        && map_terrain_is(tile, TERRAIN_WATER | TERRAIN_DEEPWATER)
        && !map_terrain_is(tile, TERRAIN_BUILDING);
}

// OG ship_pick_escape_point: farthest boat-routable water on (dir-1, dir, dir+1) rays.
tile2i pick_escape_tile(tile2i from, int direction, int distance) {
    if (direction < 0 || direction > 7) {
        direction = DIR_0_TOP_RIGHT;
    }
    if (distance <= 0) {
        distance = 10;
    }
    tile2i best = from;
    int best_d2 = -1;
    for (int delta = -1; delta <= 1; ++delta) {
        const int d = (direction + delta + 8) % 8;
        const tile2i unit = tile_ahead(tile2i(0, 0), d);
        tile2i toward(from.x() + unit.x() * distance, from.y() + unit.y() * distance);
        tile2i cand;
        const int d2 = map_water_farthest_on_line(from, toward, cand);
        if (d2 < 0 || cand == from) {
            continue;
        }
        if (d2 >= best_d2) {
            best_d2 = d2;
            best = cand;
        }
    }
    return best;
}

int clamp_dir8(int dir) {
    if (dir > DIR_7_TOP) {
        return DIR_7_TOP;
    }
    if (dir < 0) {
        return DIR_0_TOP_RIGHT;
    }
    return dir;
}

} // namespace

water_dest map_water_get_wharf_for_new_warship(figure &boat) {
    building_warship_wharf *wharf = building_first_ex<building_warship_wharf>([&boat](building_warship_wharf *w) {
        const int boat_id = w->get_figure_id(BUILDING_SLOT_BOAT);
        return !boat_id || boat_id == boat.id;
    });
    if (!wharf) {
        return { false, 0 };
    }

    tile2i dock = wharf->get_water_access_tiles().point_a;
    if (!dock.valid()) {
        dock = tile2i(wharf->base.tiles[0]);
    }
    return { dock.valid(), wharf->id(), dock };
}

void figure_warship::on_create() {
    figure_impl::on_create();
    base.allow_move_type = EMOVE_WATER;
    auto &d = runtime_data();
    d.active_order = e_order_goto_wharf;
    d.target_id = 0;
    d.action_before_attack = ACTION_10_WARSHIP_HUNTING;
    d.patrol_x = base.tile.x();
    d.patrol_y = base.tile.y();
    d.move_count = 0;
    d.move_steps = 0;
    d.secondary_action = WARSHIP_SECONDARY_WAITING;
    d.ship_move_mode = WARSHIP_MOVE_FULL_SPEED;
    d.ram_cooldown = 0;
    d.request_event_id = -1;
    d.answers_requests = 1;
    d.crew_fatigue = 0;
    d.fatigue_tick = 0;
    advance_action(ACTION_8_WARSHIP_WAITING);
}

void figure_warship::on_destroy() {
    building_shipyard_leave_queue(id());
    building *b = home();
    if (b && b->id) {
        b->remove_figure_by_id(id());
    }
}

void figure_warship::before_poof() {
}

void figure_warship::check_sink() {
    if (base.damage >= base.max_damage()) {
        kill();
    }
}

int figure_warship::target_score(figure *f, int distance) const {
    const auto &p = current_params();
    if (auto *transport = smart_cast<figure_enemy_transport>(f)) {
        return transport->has_troops() ? p.score_loaded_transport : p.score_transport;
    }
    if (smart_cast<figure_enemy_warship>(f)) {
        return p.score_warship;
    }
    if (is_enemy(f) && f->allow_move_type != EMOVE_WATER && f->allow_move_type != EMOVE_DEEPWATER
        && distance <= p.missile_range) {
        return p.score_land_enemy;
    }
    return 0;
}

figure_id figure_warship::find_enemy_at(tile2i origin, int range) {
    figure_id best = 0;
    int best_metric = -range;
    for (figure *candidate : map_figures()) {
        if (!candidate || candidate->id == id() || !is_enemy(candidate)) {
            continue;
        }
        const int distance = calc_maximum_distance(origin, candidate->tile);
        if (distance > range) {
            continue;
        }
        const int score = target_score(candidate, distance);
        if (score && score - distance > best_metric) {
            best_metric = score - distance;
            best = candidate->id;
        }
    }
    return best;
}

figure_id figure_warship::find_closest_enemy_ship(int range) {
    figure_id best = 0;
    int best_distance = range;
    for (figure *candidate : map_figures()) {
        if (!is_enemy_ship(candidate)) {
            continue;
        }
        const int distance = calc_maximum_distance(base.tile, candidate->tile);
        if (distance < best_distance) {
            best = candidate->id;
            best_distance = distance;
        }
    }
    return best;
}

figure_id figure_warship::find_ram_target() {
    const tile2i ahead = tile_ahead(base.tile, direction());
    for (figure *candidate : map_figures()) {
        if (is_enemy_ship(candidate) && (candidate->tile == base.tile || candidate->tile == ahead)) {
            return candidate->id;
        }
    }
    return 0;
}

void figure_warship::fire_missile(figure_id target_id) {
    figure *target = figure_get(target_id);
    if (!target || !target->is_valid() || target->is_dead() || !base.attack_image_offset) {
        base.attack_image_offset = 0;
        return;
    }
    if (base.attack_image_offset == 1) {
        figure_missile::create(id(), base.tile, target->tile, FIGURE_JAVELIN);
        events::emit(event_sound_effect{ SOUND_EFFECT_JAVELIN });
    }
    if (++base.attack_image_offset > current_params().shoot_ticks) {
        base.attack_image_offset = 0;
    }
}

void figure_warship::shoot() {
    const auto &p = current_params();
    if (++base.wait_ticks_missile > missile_delay()) {
        base.wait_ticks_missile = 0;
        runtime_data().target_id = find_enemy_at(base.tile, p.missile_range);
        base.attack_image_offset = runtime_data().target_id ? 1 : 0;
    }
    fire_missile(runtime_data().target_id);
}

void figure_warship::ram() {
    auto &d = runtime_data();
    const auto &p = current_params();
    if (d.ram_cooldown) {
        d.ram_cooldown--;
        return;
    }

    figure *target = figure_get(find_ram_target());
    if (!target) {
        return;
    }

    int target_dir = target->direction;
    if (target_dir > DIR_7_TOP) {
        target_dir = target->previous_tile_direction;
    }
    int own_dir = direction();
    if (own_dir > DIR_7_TOP) {
        own_dir = base.previous_tile_direction;
    }
    const int divisor = ram_direction_divisor(target_dir & 7, own_dir & 7);
    const int slow_damage = base.attack_value();
    int damage = d.move_steps < p.full_steps
        ? calc_adjust_with_percentage(slow_damage, (int)p.ram_fast_percent)
        : slow_damage;
    if (divisor > 0) {
        damage /= divisor;
    }
    target->apply_damage(damage, id());
    if (target->damage >= target->max_damage()) {
        target->dcast()->kill();
    }

    const int turn = (random_byte() & 2) - 1;
    base.set_direction(clamp_dir8(own_dir + turn));
    target->set_direction(clamp_dir8(target_dir - turn));
    figure_create_explosion_cloud(target->tile, 0);

    d.ram_cooldown = (uint8_t)p.ram_cooldown;
    d.target_id = 0;
    advance_action(ACTION_10_WARSHIP_HUNTING);
    d.secondary_action = WARSHIP_SECONDARY_WAITING;
    route_remove();
}

void figure_warship::ship_move(bool cautious) {
    auto &d = runtime_data();
    const auto &p = current_params();
    if (base.tile == base.destination_tile && direction() == DIR_FIGURE_NONE) {
        return;
    }

    switch (d.ship_move_mode) {
    case WARSHIP_MOVE_FULL_SPEED:
        if (cautious && ++d.move_count >= p.full_moves) {
            d.move_count = 0;
            d.ship_move_mode = WARSHIP_MOVE_RESTING;
            return;
        }
        if (base.tile != base.previous_tile) {
            d.move_steps++;
        }
        base.move_ticks(cautious && d.move_steps >= p.full_steps ? 1 : 2);
        break;
    case WARSHIP_MOVE_SLOW:
        base.move_ticks(1);
        if (++d.move_count >= p.fatigue_ticks) {
            d.move_count = 0;
            d.move_steps = 0;
            d.ship_move_mode = WARSHIP_MOVE_FULL_SPEED;
        }
        break;
    case WARSHIP_MOVE_RESTING:
        if (++d.move_count >= p.fatigue_ticks) {
            d.move_count = 0;
            d.ship_move_mode = WARSHIP_MOVE_SLOW;
        }
        break;
    }
    base.height_adjusted_ticks = 0;
}

void figure_warship::move_attack() {
    ship_move(true);
    ram();
    if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
        route_remove();
    }
}

void figure_warship::sail_to_destination() {
    if (base.tile != base.destination_tile) {
        ship_move(false);
    }
    if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
        route_remove();
        return;
    }
    if (base.tile != base.destination_tile && direction() != DIR_FIGURE_NONE) {
        return;
    }

    building *home_b = home();
    auto *wharf = home_b ? home_b->dcast_warship_wharf() : nullptr;
    if (action_state() != ACTION_20_WARSHIP_DOCKED
        && action_state() != ACTION_10_WARSHIP_HUNTING
        && action_state() != ACTION_13_WARSHIP_GOING_TO_DOCK
        && wharf) {
        advance_action(ACTION_23_WARSHIP_PATROLLING);
        auto &d = runtime_data();
        d.secondary_action = WARSHIP_SECONDARY_PATROL;
        d.patrol_x = base.tile.x();
        d.patrol_y = base.tile.y();
    }
}

void figure_warship::patrol() {
    auto &d = runtime_data();
    const auto &p = current_params();
    figure *target = figure_get(d.target_id);

    switch (d.secondary_action) {
    case WARSHIP_SECONDARY_MOVING:
        if (action_state() != ACTION_10_WARSHIP_HUNTING) {
            d.secondary_action = WARSHIP_SECONDARY_PATROLLING;
        }
        if (!target || !is_enemy(target)) {
            d.secondary_action = WARSHIP_SECONDARY_WAITING;
            d.target_id = 0;
            return;
        }
        if (calc_maximum_distance(base.tile, target->tile) < p.missile_range
            && ++base.wait_ticks_missile > missile_delay()) {
            base.wait_ticks_missile = 0;
            base.attack_image_offset = 1;
        }
        fire_missile(target->id);
        move_attack();
        if (direction() == DIR_FIGURE_NONE) {
            d.secondary_action = WARSHIP_SECONDARY_WAITING;
            route_remove();
        }
        return;

    case WARSHIP_SECONDARY_WAITING:
        if (action_state() != ACTION_10_WARSHIP_HUNTING) {
            d.secondary_action = WARSHIP_SECONDARY_PATROLLING;
        }
        d.target_id = find_enemy_at(base.tile, p.hunt_range);
        target = figure_get(d.target_id);
        if (target) {
            d.secondary_action = WARSHIP_SECONDARY_MOVING;
            base.destination_tile = target->tile;
            route_remove();
            return;
        }
        ship_move(false);
        return;

    case WARSHIP_SECONDARY_PATROL_ATTACK:
        if (action_state() != ACTION_23_WARSHIP_PATROLLING) {
            d.secondary_action = WARSHIP_SECONDARY_WAITING;
            return;
        }
        if (target
            && calc_maximum_distance(tile2i(d.patrol_x, d.patrol_y), base.tile) < p.patrol_radius
            && calc_maximum_distance(target->tile, base.tile) < p.missile_range) {
            if (++base.wait_ticks_missile > missile_delay()) {
                base.wait_ticks_missile = 0;
                base.attack_image_offset = 1;
            }
            fire_missile(target->id);
            move_attack();
            if (direction() != DIR_FIGURE_NONE) {
                return;
            }
        }
        d.secondary_action = WARSHIP_SECONDARY_PATROLLING;
        base.destination_tile = tile2i(d.patrol_x, d.patrol_y);
        route_remove();
        return;

    case WARSHIP_SECONDARY_PATROLLING:
        d.target_id = find_enemy_at(base.tile, p.missile_range + p.patrol_extra_range);
        target = figure_get(d.target_id);
        if (action_state() != ACTION_23_WARSHIP_PATROLLING) {
            d.secondary_action = WARSHIP_SECONDARY_WAITING;
            return;
        }
        if (target && calc_maximum_distance(tile2i(d.patrol_x, d.patrol_y), target->tile) < p.patrol_radius) {
            d.secondary_action = WARSHIP_SECONDARY_PATROL_ATTACK;
            base.destination_tile = target->tile;
            route_remove();
            return;
        }
        ship_move(false);
        return;
    }
}

void figure_warship::evade() {
    auto &d = runtime_data();
    const auto &p = current_params();
    if (d.secondary_action == WARSHIP_SECONDARY_SAILING) {
        sail_to_destination();
        if (base.tile == base.destination_tile) {
            d.secondary_action = WARSHIP_SECONDARY_WAITING;
        }
        return;
    }
    if (d.secondary_action != WARSHIP_SECONDARY_WAITING || ++base.wait_ticks < p.evade_ticks) {
        return;
    }
    base.wait_ticks = 0;
    figure *enemy = figure_get(find_closest_enemy_ship(p.evade_range));
    if (!enemy) {
        return;
    }

    // OG: direction from enemy to ship, then ship_escape_moves for that facing.
    int dir = calc_general_direction(enemy->tile, base.tile);
    if (dir > DIR_7_TOP) {
        dir = DIR_0_TOP_RIGHT;
    }
    tile2i escape = pick_escape_tile(base.tile, dir, p.escape_distance);
    if (escape == base.tile) {
        return;
    }
    base.destination_tile = escape;
    route_remove();
    d.secondary_action = WARSHIP_SECONDARY_SAILING;
}

void figure_warship::attack_ship() {
    auto &d = runtime_data();
    const auto &p = current_params();
    figure *target = figure_get(d.target_id);
    if (!target || !is_enemy(target)) {
        d.target_id = find_enemy_at(base.tile, p.hunt_range);
        target = figure_get(d.target_id);
        d.secondary_action = WARSHIP_SECONDARY_WAITING;
    }

    if (d.secondary_action == WARSHIP_SECONDARY_FOLLOW_TARGET) {
        if (!target) {
            d.secondary_action = WARSHIP_SECONDARY_WAITING;
            return;
        }
        if (calc_maximum_distance(base.tile, target->tile) < p.missile_range
            && ++base.wait_ticks_missile > missile_delay()) {
            base.wait_ticks_missile = 0;
            base.attack_image_offset = 1;
        }
        fire_missile(target->id);
        move_attack();
        if (direction() == DIR_FIGURE_NONE) {
            d.secondary_action = WARSHIP_SECONDARY_WAITING;
            route_remove();
            return;
        }
        if (++base.wait_ticks > p.target_check_ticks) {
            base.wait_ticks = 0;
            if (base.destination_tile.x() != target->tile.x() && base.destination_tile.y() != target->tile.y()) {
                d.secondary_action = WARSHIP_SECONDARY_WAITING;
                route_remove();
            }
        }
        return;
    }

    if (d.secondary_action != WARSHIP_SECONDARY_WAITING) {
        return;
    }
    if (target) {
        d.secondary_action = WARSHIP_SECONDARY_FOLLOW_TARGET;
        base.destination_tile = target->tile;
        route_remove();
        return;
    }

    advance_action(d.action_before_attack);
    base.destination_tile = base.tile;
    d.patrol_x = base.tile.x();
    d.patrol_y = base.tile.y();
    d.secondary_action = action_state() == ACTION_23_WARSHIP_PATROLLING
        ? WARSHIP_SECONDARY_PATROL
        : WARSHIP_SECONDARY_WAITING;
    d.target_id = 0;
    route_remove();
}

void figure_warship::wait_at_shipyard() {
    if (++base.wait_ticks < current_params().dock_wait_ticks) {
        return;
    }
    base.wait_ticks = 0;

    building *home_b = home();
    auto *home_wharf = home_b ? home_b->dcast_warship_wharf() : nullptr;
    water_dest result;
    if (home_wharf) {
        tile2i dock = home_wharf->get_water_access_tiles().point_a;
        result = { dock.valid(), home_wharf->id(), dock };
    } else {
        result = map_water_get_wharf_for_new_warship(base);
    }
    if (!result.found) {
        return;
    }
    move_to_wharf(result.bid, result.tile);
}

void figure_warship::go_to_best_dock() {
    building_shipyard_leave_queue(id());
    const int dock_id = building_shipyard_find_best_dock(id());
    building *dock = building_get(dock_id);
    auto *shipyard = dock ? dock->dcast_shipyard() : nullptr;
    if (!shipyard) {
        advance_action(ACTION_8_WARSHIP_WAITING);
        return;
    }

    tile2i berth = shipyard->get_water_access_tiles().point_a;
    if (!berth.valid()) {
        berth = tile2i(dock->tiles[0]);
    }
    if (!berth.valid()) {
        advance_action(ACTION_8_WARSHIP_WAITING);
        return;
    }
    set_destination(dock_id);
    base.destination_tile = berth;
    route_remove();
    advance_action(ACTION_13_WARSHIP_GOING_TO_DOCK);
}

void figure_warship::sail_to_dock() {
    ship_move(false);
    if (direction() == DIR_FIGURE_REROUTE) {
        route_remove();
        return;
    }
    if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
        go_to_best_dock();
        return;
    }
    if (base.tile != base.destination_tile && direction() != DIR_FIGURE_NONE) {
        return;
    }

    int dock_id = base.destination_building_id;
    const int best = building_shipyard_find_best_dock(id());
    if (best > 0 && dock_id > 0 && building_shipyard_repair_queue_size(dock_id) >= 1 && best != dock_id) {
        go_to_best_dock();
        return;
    }
    if (dock_id > 0 && building_shipyard_queue_ship(id(), dock_id)) {
        advance_action(ACTION_15_WARSHIP_QUEUED_AT_DOCK);
        base.wait_ticks = 0;
    } else {
        advance_action(ACTION_8_WARSHIP_WAITING);
    }
}

void figure_warship::docked() {
    sail_to_destination();
    shoot();
    const auto &p = current_params();
    if (++base.wait_ticks <= p.face_enemy_wait || runtime_data().ship_move_mode == WARSHIP_MOVE_RESTING) {
        return;
    }
    base.wait_ticks = 0;
    figure *enemy = figure_get(find_closest_enemy_ship(p.face_enemy_range));
    if (enemy) {
        base.previous_tile_direction = calc_general_direction(base.tile, enemy->tile);
    }
}

void figure_warship::send_to_request(int event_id) {
    auto &d = runtime_data();
    d.request_event_id = (int16_t)event_id;
    d.target_id = 0;
    route_remove();
    if (action_state() != ACTION_18_WARSHIP_AWAY_ON_REQUEST) {
        advance_action(ACTION_17_WARSHIP_GOING_TO_REQUEST);
    }
}

void figure_warship::return_from_request() {
    auto &d = runtime_data();
    d.request_event_id = -1;
    base.set_flag(e_figure_flag_invisible, false);
    building *home_b = home();
    auto *wharf = home_b ? home_b->dcast_warship_wharf() : nullptr;
    tile2i dock;
    if (wharf) {
        dock = wharf->get_water_access_tiles().point_a;
        if (!dock.valid()) {
            dock = tile2i(home_b->tiles[0]);
        }
    }
    if (!dock.valid()) {
        water_dest result = map_water_get_wharf_for_new_warship(base);
        if (result.found) {
            dock = result.tile;
            set_home(result.bid);
        }
    }
    if (dock.valid()) {
        base.destination_tile = dock;
        route_remove();
        advance_action(ACTION_19_WARSHIP_RETURNING_FROM_REQUEST);
    } else {
        advance_action(ACTION_8_WARSHIP_WAITING);
    }
}

void figure_warship::request_action() {
    switch (action_state()) {
    case ACTION_17_WARSHIP_GOING_TO_REQUEST:
        if (!scenario_map_has_river_entry()) {
            return;
        }
        base.destination_tile = scenario_map_river_entry();
        ship_move(false);
        if (base.tile == base.destination_tile || direction() == DIR_FIGURE_NONE) {
            advance_action(ACTION_18_WARSHIP_AWAY_ON_REQUEST);
            base.set_flag(e_figure_flag_invisible);
            route_remove();
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            kill();
        }
        break;
    case ACTION_18_WARSHIP_AWAY_ON_REQUEST:
        base.set_flag(e_figure_flag_invisible);
        break;
    case ACTION_19_WARSHIP_RETURNING_FROM_REQUEST:
        base.set_flag(e_figure_flag_invisible, false);
        ship_move(false);
        if (base.tile == base.destination_tile || direction() == DIR_FIGURE_NONE) {
            advance_action(ACTION_8_WARSHIP_WAITING);
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            kill();
        }
        break;
    }
}

void figure_warship::update_crew_fatigue() {
    auto &d = runtime_data();
    const auto &p = current_params();
    building *home_b = home();
    auto *wharf = home_b ? home_b->dcast_warship_wharf() : nullptr;
    const int state = action_state();
    const bool moored_resting = (state == ACTION_8_WARSHIP_WAITING || state == ACTION_20_WARSHIP_DOCKED)
        && wharf && wharf->num_workers() > 0;

    d.fatigue_tick++;
    if (moored_resting) {
        if (d.fatigue_tick >= p.fatigue_rest_interval) {
            d.fatigue_tick = 0;
            d.crew_fatigue = (int8_t)std::max(0, (int)d.crew_fatigue - (int)p.fatigue_rest_amount);
        }
        return;
    }

    const int interval = (state == ACTION_24_WARSHIP_ATTACKING_SHIP)
        ? p.fatigue_combat_interval
        : p.fatigue_grow_interval;
    if (d.fatigue_tick >= interval) {
        d.fatigue_tick = 0;
        d.crew_fatigue = (int8_t)std::min(100, (int)d.crew_fatigue + 1);
    }
}

void figure_warship::figure_action() {
    check_sink();
    if (!is_alive()) {
        return;
    }

    update_crew_fatigue();

    if (runtime_data().request_event_id >= 0) {
        if (action_state() == ACTION_18_WARSHIP_AWAY_ON_REQUEST) {
            request_action();
            return;
        }
        if (action_state() != ACTION_17_WARSHIP_GOING_TO_REQUEST) {
            route_remove();
            advance_action(ACTION_17_WARSHIP_GOING_TO_REQUEST);
        }
    }

    const int max_damage = base.max_damage();
    const int health = max_damage > 0 ? calc_percentage(max_damage - base.damage, max_damage) : 0;
    if (health > 0 && health <= current_params().damaged_percent
        && action_state() != ACTION_13_WARSHIP_GOING_TO_DOCK
        && action_state() != ACTION_15_WARSHIP_QUEUED_AT_DOCK
        && runtime_data().request_event_id < 0) {
        runtime_data().active_order = e_order_repair;
        go_to_best_dock();
        return;
    }

    switch (action_state()) {
    case ACTION_8_WARSHIP_WAITING:
        wait_at_shipyard();
        shoot();
        break;
    case ACTION_9_WARSHIP_STRAIGHT:
        move_attack();
        break;
    case ACTION_10_WARSHIP_HUNTING:
    case ACTION_23_WARSHIP_PATROLLING:
        patrol();
        break;
    case ACTION_11_WARSHIP_SAILING:
        sail_to_destination();
        shoot();
        break;
    case ACTION_12_WARSHIP_EVADING:
        evade();
        shoot();
        break;
    case ACTION_13_WARSHIP_GOING_TO_DOCK:
        sail_to_dock();
        break;
    case ACTION_15_WARSHIP_QUEUED_AT_DOCK:
        break;
    case ACTION_17_WARSHIP_GOING_TO_REQUEST:
    case ACTION_18_WARSHIP_AWAY_ON_REQUEST:
    case ACTION_19_WARSHIP_RETURNING_FROM_REQUEST:
        request_action();
        break;
    case ACTION_20_WARSHIP_DOCKED:
        docked();
        break;
    case ACTION_24_WARSHIP_ATTACKING_SHIP:
        attack_ship();
        break;
    default:
        advance_action(ACTION_8_WARSHIP_WAITING);
        break;
    }
}

void figure_warship::kill() {
    building_shipyard_leave_queue(id());
    building *b = home();
    if (b && b->id) {
        b->remove_figure_by_id(id());
    }
    base.set_home(0);
    base.wait_ticks = 0;
    figure_shipwreck::create(tile());
    figure_impl::kill();
}

void figure_warship::update_animation() {
    pcstr key = "walk";
    switch (action_state()) {
    case ACTION_8_WARSHIP_WAITING:
    case ACTION_15_WARSHIP_QUEUED_AT_DOCK:
    case ACTION_18_WARSHIP_AWAY_ON_REQUEST:
    case ACTION_20_WARSHIP_DOCKED:
        key = "idle";
        break;
    case ACTION_24_WARSHIP_ATTACKING_SHIP:
        key = "attack";
        break;
    default:
        key = runtime_data().ship_move_mode == WARSHIP_MOVE_RESTING ? "idle" : "walk";
        break;
    }
    image_set_animation(key);
}

void figure_warship::set_order(int order) {
    auto &d = runtime_data();
    d.active_order = (short)order;
    d.target_id = 0;
    base.attack_image_offset = 0;

    switch (order) {
    case e_order_goto_wharf: {
        building *home_b = home();
        auto *wharf = home_b ? home_b->dcast_warship_wharf() : nullptr;
        if (wharf) {
            tile2i dock = wharf->get_water_access_tiles().point_a;
            if (dock.valid()) {
                base.destination_tile = dock;
                advance_action(ACTION_11_WARSHIP_SAILING);
                route_remove();
                return;
            }
        }
        advance_action(ACTION_8_WARSHIP_WAITING);
        base.wait_ticks = current_params().dock_wait_ticks;
        break;
    }
    case e_order_engage_nearby:
        d.patrol_x = base.tile.x();
        d.patrol_y = base.tile.y();
        d.secondary_action = WARSHIP_SECONDARY_PATROL;
        base.destination_tile = base.tile;
        advance_action(ACTION_23_WARSHIP_PATROLLING);
        route_remove();
        break;
    case e_order_hold_position:
        base.destination_tile = base.tile;
        advance_action(ACTION_20_WARSHIP_DOCKED);
        route_remove();
        break;
    case e_order_seek_and_destroy:
        d.secondary_action = WARSHIP_SECONDARY_WAITING;
        base.destination_tile = base.tile;
        advance_action(ACTION_10_WARSHIP_HUNTING);
        route_remove();
        break;
    case e_order_repair:
        go_to_best_dock();
        break;
    case e_order_move_to_tile:
    default:
        break;
    }
}

void figure_warship::attack_target(figure_id target_id) {
    figure *target = figure_get(target_id);
    if (!is_enemy_ship(target)) {
        return;
    }
    auto &d = runtime_data();
    d.action_before_attack = action_state() == ACTION_23_WARSHIP_PATROLLING
        ? ACTION_23_WARSHIP_PATROLLING
        : ACTION_10_WARSHIP_HUNTING;
    d.target_id = target_id;
    d.secondary_action = WARSHIP_SECONDARY_WAITING;
    advance_action(ACTION_24_WARSHIP_ATTACKING_SHIP);
    route_remove();
}

void figure_warship::move_to_tile(tile2i dest) {
    auto &d = runtime_data();
    d.active_order = e_order_move_to_tile;
    d.target_id = 0;
    base.destination_tile = dest;
    route_remove();

    if (action_state() == ACTION_23_WARSHIP_PATROLLING) {
        d.patrol_x = dest.x();
        d.patrol_y = dest.y();
        d.secondary_action = WARSHIP_SECONDARY_PATROL;
    } else if (action_state() == ACTION_10_WARSHIP_HUNTING) {
        d.secondary_action = WARSHIP_SECONDARY_WAITING;
    } else {
        advance_action(ACTION_11_WARSHIP_SAILING);
    }
}

void figure_warship::move_to_wharf(int wharf_building_id, tile2i dock_tile) {
    building *new_home = building_get(wharf_building_id);
    if (!new_home || !new_home->is_valid()) {
        return;
    }
    building *old_home = home();
    if (old_home && old_home->id != wharf_building_id) {
        old_home->remove_figure_by_id(id());
    }
    set_home(wharf_building_id);
    new_home->set_figure(BUILDING_SLOT_BOAT, &base);
    runtime_data().active_order = e_order_goto_wharf;
    runtime_data().target_id = 0;
    base.destination_tile = dock_tile;
    route_remove();
    advance_action(ACTION_11_WARSHIP_SAILING);
}
