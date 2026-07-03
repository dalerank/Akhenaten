#include "figure_war_ship.h"

#include "figure/route.h"
#include "figure_shipwreck.h"
#include "figure/combat.h"
#include "figure/movement.h"
#include "figuretype/figure_missile.h"
#include "figuretype/figure_transport_ship.h"
#include "grid/water.h"
#include "grid/figure.h"
#include "grid/terrain.h"
#include "city/city_message.h"
#include "city/city_figures.h"
#include "game/game.h"
#include "core/calc.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/ui.h"
#include "graphics/image_desc.h"
#include "building/building_warship_wharf.h"
#include "city/city.h"
#include "js/js_game.h"
#include "sound/sound.h"
#include "sound/effect.h"
#include "game/game_events.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_warship)

namespace {

constexpr int WARSHIP_MISSILE_RANGE = 10;
constexpr int WARSHIP_ENGAGE_RANGE = 18;
constexpr int WARSHIP_SEEK_RANGE = 80;
constexpr int WARSHIP_RAM_INTERVAL = 50;
constexpr int WARSHIP_REPAIR_INTERVAL = 20;
constexpr int WARSHIP_REPAIR_AMOUNT = 2;

bool is_water_figure(const figure *f) {
    return f->allow_move_type == EMOVE_WATER || f->allow_move_type == EMOVE_DEEPWATER;
}

bool is_enemy_warship_target(figure *f) {
    if (!f || !f->is_valid() || f->is_dead()) {
        return false;
    }

    if (!f->is_enemy() && f->category() != figure_category_hostile) {
        return false;
    }

    return is_water_figure(f) || f->type == FIGURE_WARSHIP || f->type == FIGURE_ENEMY_WARSHIP;
}

bool is_shore_enemy_target(figure *f) {
    if (!f || !f->is_valid() || f->is_dead()) {
        return false;
    }

    if (!f->is_enemy() && f->category() != figure_category_hostile) {
        return false;
    }

    return !is_water_figure(f);
}

int warship_target_priority(figure *f) {
    if (!f || !f->is_valid() || f->is_dead()) {
        return 0;
    }

    if (f->type == FIGURE_TRANSPORT_SHIP || f->type == FIGURE_ENEMY_WARSHIP) {
        if (auto transport = smart_cast<figure_transport_ship>(f)) {
            if (transport->has_troops()) {
                return 40;
            }
            return 10;
        }
        return 30;
    }

    if (is_enemy_warship_target(f) && is_water_figure(f)) {
        return 30;
    }

    if (is_shore_enemy_target(f)) {
        return 20;
    }

    return 0;
}

} // namespace

water_dest map_water_get_wharf_for_new_warship(figure &boat) {
    building_warship_wharf *wharf = nullptr;

    wharf = building_first_ex<building_warship_wharf>([&boat] (building_warship_wharf *w) {
        int wharf_boat_id = w->get_figure_id(BUILDING_SLOT_BOAT);
        if (!wharf_boat_id || wharf_boat_id == boat.id) {
            return true;
        }

        return false;
    });

    if (!wharf) {
        return { false, 0 };
    }

    tile2i dock_tile(wharf->runtime_data().dock_tiles[0]);
    return { dock_tile.valid(), wharf->id(), dock_tile };
}

water_dest map_water_get_closest_working_warship_wharf(figure &boat) {
    building_warship_wharf *wharf = nullptr;

    int mindist = 9999;
    tile2i dock_tile;
    buildings_valid_do([&] (building &b) {
        auto w = b.dcast_warship_wharf();
        if (!w) {
            return;
        }

        const auto water_tiles = w->get_water_access_tiles();
        const float curdist = boat.tile.dist(water_tiles.point_a);
        if (curdist < mindist) {
            wharf = w;
            mindist = curdist;
            dock_tile = water_tiles.point_a;
        }
    }, BUILDING_WARSHIP_WHARF);

    if (!wharf) {
        return { false, 0 };
    }

    return { true, wharf->id(), dock_tile };
}

void figure_warship::on_create() {
    figure_impl::on_create();
    base.allow_move_type = EMOVE_WATER;
    runtime_data().active_order = e_order_goto_wharf;
}

void figure_warship::on_destroy() {
    building* b = home();
    b->remove_figure_by_id(id());
}

void figure_warship::before_poof() {
}

void figure_warship::check_sink() {
    if (base.damage > base.max_damage()) {
        kill();
    }
}

figure_id figure_warship::find_combat_target(int max_distance) {
    figure_id best_id = 0;
    int best_priority = 0;
    int best_distance = 10000;

    for (figure *f : map_figures()) {
        if (!f || f->id == id()) {
            continue;
        }

        const int priority = warship_target_priority(f);
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

void figure_warship::launch_missile_at(figure *target) {
    if (!target || !target->is_valid()) {
        return;
    }

    base.wait_ticks++;
    if (base.wait_ticks < missile_delay()) {
        return;
    }

    base.wait_ticks = 0;
    if (!figure_movement_can_launch_cross_country_missile(base.tile, target->tile)) {
        return;
    }

    figure_missile::create(id(), base.tile, target->tile, FIGURE_ARROW);
    events::emit(event_sound_effect{ SOUND_EFFECT_ARROW });
}

void figure_warship::ram_target(figure *target) {
    if (!target || !target->is_valid()) {
        return;
    }

    base.wait_ticks++;
    if (base.wait_ticks < WARSHIP_RAM_INTERVAL) {
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
        if (smart_cast<figure_warship>(target)) {
            smart_cast<figure_warship>(target)->kill();
        } else {
            target->kill();
        }
    }

    base.apply_damage(net / 2, target->id);
    check_sink();
}

void figure_warship::combat_tick_vs_target(figure *target, int max_pursue_distance) {
    if (!target || !target->is_valid() || target->is_dead()) {
        runtime_data().target_id = 0;
        return;
    }

    const int distance = calc_maximum_distance(base.tile, target->tile);
    const bool hold_position = runtime_data().active_order == e_order_hold_position;

    if (is_enemy_warship_target(target) && distance <= 1) {
        advance_action(ACTION_204_WARSHIP_ATTACK);
        ram_target(target);
        return;
    }

    if (distance <= WARSHIP_MISSILE_RANGE
        && figure_movement_can_launch_cross_country_missile(base.tile, target->tile)) {
        advance_action(ACTION_204_WARSHIP_ATTACK);
        launch_missile_at(target);
        return;
    }

    if (hold_position) {
        advance_action(ACTION_211_WARSHIP_IDLE_AT_TILE);
        return;
    }

    if (distance > max_pursue_distance) {
        runtime_data().target_id = 0;
        return;
    }

    if (action_state() != ACTION_206_WARSHIP_GOING_TO_PATROL) {
        base.destination_tile = target->tile;
        base.source_tile = base.tile;
        advance_action(ACTION_206_WARSHIP_GOING_TO_PATROL);
        route_remove();
    }

    base.move_ticks(1);
    base.height_adjusted_ticks = 0;
    if (direction() == DIR_FIGURE_REROUTE) {
        route_remove();
    } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
        runtime_data().target_id = 0;
        advance_action(ACTION_211_WARSHIP_IDLE_AT_TILE);
    }
}

void figure_warship::figure_action_combat() {
    check_sink();
    if (!is_alive()) {
        return;
    }

    auto &d = runtime_data();
    if (d.last_order != d.active_order) {
        d.last_order = d.active_order;
        d.target_id = 0;
        if (d.active_order == e_order_hold_position) {
            base.source_tile = base.tile;
            advance_action(ACTION_211_WARSHIP_IDLE_AT_TILE);
        } else if (action_state() == ACTION_203_WARSHIP_MOORED) {
            base.source_tile = base.tile;
            advance_action(ACTION_211_WARSHIP_IDLE_AT_TILE);
        }
    }

    if (d.active_order == e_order_hold_position && action_state() == ACTION_211_WARSHIP_IDLE_AT_TILE) {
        if (base.tile != base.source_tile) {
            base.destination_tile = base.source_tile;
            advance_action(ACTION_210_WARSHIP_GOING_TO_TILE);
            route_remove();
            figure_action_move_to_tile();
            return;
        }
    }

    int search_range = WARSHIP_ENGAGE_RANGE;
    if (d.active_order == e_order_seek_and_destroy) {
        search_range = WARSHIP_SEEK_RANGE;
    }

    figure *target = figure_get(d.target_id);
    if (!target || !target->is_valid() || target->is_dead()) {
        d.target_id = find_combat_target(search_range);
        target = figure_get(d.target_id);
    }

    if (!target) {
        if (d.active_order == e_order_hold_position) {
            advance_action(ACTION_211_WARSHIP_IDLE_AT_TILE);
        } else if (action_state() == ACTION_204_WARSHIP_ATTACK) {
            advance_action(ACTION_211_WARSHIP_IDLE_AT_TILE);
        }
        return;
    }

    combat_tick_vs_target(target, search_range);
}

void figure_warship::figure_action_repair() {
    check_sink();
    if (base.damage <= 0) {
        figure_action_goto_wharf();
        return;
    }

    building_warship_wharf *wharf = home() ? home()->dcast_warship_wharf() : nullptr;
    if (action_state() == ACTION_203_WARSHIP_MOORED && wharf && wharf->num_workers() > 0) {
        base.wait_ticks++;
        if (base.wait_ticks >= WARSHIP_REPAIR_INTERVAL) {
            base.wait_ticks = 0;
            base.damage = std::max(0, base.damage - WARSHIP_REPAIR_AMOUNT);
        }
        return;
    }

    figure_action_goto_wharf();
}

void figure_warship::figure_action_move_to_tile() {
    base.move_ticks(1);
    base.height_adjusted_ticks = 0;
    if (direction() == DIR_FIGURE_NONE) {
        advance_action(ACTION_211_WARSHIP_IDLE_AT_TILE);
        base.source_tile = base.destination_tile;
        base.wait_ticks = 0;
    } else if (direction() == DIR_FIGURE_REROUTE) {
        route_remove();
    } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
        advance_action(ACTION_211_WARSHIP_IDLE_AT_TILE);
        base.source_tile = base.tile;
    }
}

void figure_warship::figure_action() {
    building* b = home();

    if (action_state() == ACTION_205_WARSHIP_CREATED) {
        figure_action_common();
        return;
    }

    building_warship_wharf *wharf = b->dcast_warship_wharf();

    if (!wharf) {
        if (action_state() != ACTION_207_WARSHIP_GOING_TO_WHARF || base.destination_building_id == 0) {
            water_dest result = map_water_get_closest_working_warship_wharf(base);
            if (result.found) {
                set_destination(result.bid);
                base.destination_tile = result.tile;
                route_remove();
                advance_action(ACTION_207_WARSHIP_GOING_TO_WHARF);
            } else {
                kill();
                return;
            }
        }

        base.move_ticks(1);
        if (direction(DIR_FIGURE_NONE, DIR_FIGURE_CAN_NOT_REACH, DIR_FIGURE_REROUTE)) {
            poof();
        }
        return;
    }

    if (wharf->num_workers() == 0
        && action_state() != ACTION_207_WARSHIP_GOING_TO_WHARF
        && runtime_data().active_order == e_order_goto_wharf) {
        runtime_data().active_order = e_order_goto_wharf;
        set_destination(&wharf->base);
        base.destination_tile = wharf->get_water_access_tiles().point_a;
        route_remove();
        advance_action(ACTION_207_WARSHIP_GOING_TO_WHARF);
    }

    int wharf_boat_id = b ? b->get_figure_id(BUILDING_SLOT_BOAT) : 0;
    if (action_state() != ACTION_205_WARSHIP_CREATED && wharf_boat_id != id()) {
        water_dest result = map_water_get_wharf_for_new_warship(base);
        b = building_get(result.bid);
        if (b->id) {
            set_home(b->id);
            b->set_figure(BUILDING_SLOT_BOAT, &base);
            advance_action(ACTION_207_WARSHIP_GOING_TO_WHARF);
            base.destination_tile = result.tile;
            base.source_tile = result.tile;
            route_remove();
        } else {
            poof();
        }
    }

    assert(base.allow_move_type == EMOVE_WATER);

    switch (runtime_data().active_order) {
    case e_order_goto_wharf:
        figure_action_goto_wharf();
        break;
    case e_order_repair:
        figure_action_repair();
        break;
    case e_order_hold_position:
    case e_order_engage_nearby:
    case e_order_seek_and_destroy:
        figure_action_combat();
        break;
    case e_order_move_to_tile:
        figure_action_move_to_tile();
        break;
    default:
        figure_action_goto_wharf();
        break;
    }
}

void figure_warship::kill() {
    if (building *b = home()) {
        b->remove_figure_by_id(id());
    }
    base.set_home(0);
    base.wait_ticks = 0;
    figure_shipwreck::create(tile());
    figure_impl::kill();
}

sound_key figure_warship::phrase_key() const {
    svector<sound_key, 5> keys;

    if (action_state() == ACTION_204_WARSHIP_ATTACK) {
        keys.push_back("warship_well_fight_to_the_death");
    }

    if (g_city.figures.enemies > 0) {
        keys.push_back("warship_enemies_coming_this_way");
    }

    if (action_state() == ACTION_206_WARSHIP_GOING_TO_PATROL ||
        action_state() == ACTION_209_WARSHIP_ON_PATROL) {
        keys.push_back("warship_ready_to_attack_invaders");
    }

    if (action_state() == ACTION_203_WARSHIP_MOORED) {
        keys.push_back("warship_ready_if_foes_come");
    }

    if (keys.empty()) {
        keys.push_back("warship_ready_if_foes_come");
    }

    int index = rand() % keys.size();
    return keys[index];
}

void figure_warship::update_animation() {
    pcstr anim_key = "walk";
    switch (action_state()) {
    case ACTION_205_WARSHIP_CREATED: anim_key = "idle"; break;
    case ACTION_204_WARSHIP_ATTACK: anim_key = "attack"; break;
    case ACTION_209_WARSHIP_ON_PATROL: anim_key = "walk"; break;
    case ACTION_203_WARSHIP_MOORED: anim_key = "idle"; break;
    case ACTION_211_WARSHIP_IDLE_AT_TILE: anim_key = "idle"; break;
    case ACTION_206_WARSHIP_GOING_TO_PATROL: anim_key = "walk"; break;
    case ACTION_210_WARSHIP_GOING_TO_TILE: anim_key = "walk"; break;
    }

    image_set_animation(anim_key);
}

void figure_warship::figure_action_goto_wharf() {
    if (action_state() == ACTION_204_WARSHIP_ATTACK) {
        base.wait_ticks++;
        if (base.wait_ticks >= 200) {
            base.wait_ticks = 0;
            advance_action(ACTION_207_WARSHIP_GOING_TO_WHARF);
            base.destination_tile = base.source_tile;
            route_remove();
        }
        return;
    }

    if (action_state() == ACTION_203_WARSHIP_MOORED) {
        return;
    }

    building *home_building = home();
    building_warship_wharf *wharf = home_building ? home_building->dcast_warship_wharf() : nullptr;
    if (!wharf || !home_building || !home_building->is_valid() || wharf->num_workers() == 0) {
        return;
    }

    advance_action(ACTION_207_WARSHIP_GOING_TO_WHARF);
    base.destination_tile.set(wharf->runtime_data().dock_tiles[0]);
    base.move_ticks(1);
    base.height_adjusted_ticks = 0;
    if (direction() == DIR_FIGURE_NONE) {
        advance_action(ACTION_203_WARSHIP_MOORED);
        base.wait_ticks = 0;
    } else if (direction() == DIR_FIGURE_REROUTE) {
        route_remove();
    } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
        advance_action(ACTION_205_WARSHIP_CREATED);
    }
}

void figure_warship::figure_action_common() {
    building *b = home();

    switch (action_state()) {
    case ACTION_205_WARSHIP_CREATED:
        base.wait_ticks++;
        if (base.wait_ticks >= 50) {
            base.wait_ticks = 0;
            water_dest result = map_water_get_wharf_for_new_warship(base);
            if (result.bid && result.found) {
                b->remove_figure_by_id(id());
                building *new_home = building_get(result.bid);
                set_home(new_home->id);
                new_home->set_figure(BUILDING_SLOT_BOAT, &base);
                advance_action(ACTION_207_WARSHIP_GOING_TO_WHARF);
                base.destination_tile = result.tile;
                base.source_tile = result.tile;
                route_remove();
            }
        }
        break;

    case ACTION_207_WARSHIP_GOING_TO_WHARF:
        base.move_ticks(1);
        base.height_adjusted_ticks = 0;
        if (direction() == DIR_FIGURE_NONE) {
            advance_action(ACTION_203_WARSHIP_MOORED);
            base.wait_ticks = 0;
        } else if (direction() == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            advance_action(ACTION_205_WARSHIP_CREATED);
        }
        break;
    }
}

void figure_warship::move_to_tile(tile2i dest) {
    runtime_data().active_order = e_order_move_to_tile;
    runtime_data().target_id = 0;
    base.destination_tile = dest;
    advance_action(ACTION_210_WARSHIP_GOING_TO_TILE);
    route_remove();
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
    base.source_tile = dock_tile;
    advance_action(ACTION_207_WARSHIP_GOING_TO_WHARF);
    route_remove();
}
