#include "figure/figure.h"

#include "graphics/image_groups.h"
#include "grid/road_access.h"
#include "core/calc.h"
#include "figure_fireman.h"
#include "sound/effect.h"
#include "config/config.h"
#include "building/list.h"
#include "building/maintenance.h"
#include "graphics/animation.h"

#include "js/js_game.h"

namespace model {

struct fireman_t {
    static constexpr e_figure_type type = FIGURE_FIREMAN;
    animations_t anim;
};

fireman_t fireman;

}

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_fireman);
void config_load_figure_fireman() {
    g_config_arch.r_section("figure_fireman", [] (archive arch) {
        model::fireman.anim.load(arch);
    });
}

void figure_fireman::figure_action() { // doubles as fireman! not as policeman!!!
    fight_fire();

    building* b = home();
    switch (base.action_state) {
    case FIGURE_ACTION_70_FIREMAN_CREATED:
        advance_action(ACTION_10_GOING);
        break;

    case ACTION_11_RETURNING_FROM_PATROL:
    case FIGURE_ACTION_73_FIREMAN_RETURNING:
        do_returnhome(TERRAIN_USAGE_PREFER_ROADS);
        break;

    case 9:
    case FIGURE_ACTION_71_FIREMAN_ENTERING_EXITING:
        do_enterbuilding(true, home());
        break;

    case ACTION_10_GOING:
    case FIGURE_ACTION_72_FIREMAN_ROAMING:
        do_roam(TERRAIN_USAGE_ROADS, ACTION_11_RETURNING_FROM_PATROL);
        break;

    case FIGURE_ACTION_74_FIREMAN_GOING_TO_FIRE:
    case 12:
        if (do_goto(base.destination_tile, TERRAIN_USAGE_PREFER_ROADS, FIGURE_ACTION_75_FIREMAN_AT_FIRE)) {
            base.wait_ticks = 50;
        }

        if (base.direction == DIR_FIGURE_REROUTE) {
            base.movement_ticks_watchdog++;
            int next_direction = calc_general_direction(tile(), base.destination_tile);
            int dir_grid_offset = tile().grid_offset() + map_grid_direction_delta(next_direction);
            building *next_tile_b = building_at(dir_grid_offset);
            building *next_b = destination();
            auto clear_ruin_destination = [&] { if (next_b && next_b->type == BUILDING_BURNING_RUIN) { next_b->set_figure(3, 0); }};
            if (next_tile_b && next_tile_b->type == BUILDING_BURNING_RUIN) {
                clear_ruin_destination();
                base.set_destination(next_tile_b);
                advance_action(FIGURE_ACTION_75_FIREMAN_AT_FIRE);
            }
            
            if (!next_b || next_b->state == BUILDING_STATE_UNUSED || next_b->type != BUILDING_BURNING_RUIN) {
                clear_ruin_destination();
                bool has_fire_around = fight_fire();
                if (!has_fire_around) {
                    advance_action(ACTION_11_RETURNING_FROM_PATROL);
                }
            }

            if (base.movement_ticks_watchdog > 10) {
                base.movement_ticks_watchdog = 0;
                clear_ruin_destination();
                route_remove();
                advance_action(ACTION_11_RETURNING_FROM_PATROL);
            }
        }
        break;

    case FIGURE_ACTION_75_FIREMAN_AT_FIRE:
    case 13:
        extinguish_fire();
        break;

    case FIGURE_ACTION_76_FIREMAN_GOING_TO_ENEMY:
        //terrain_usage = TERRAIN_USAGE_ANY;
        //if (!target_is_alive()) {
        //    map_point road_tile;
        //    if (map_closest_road_within_radius(b->tile.x(), b->tile.y(), b->size, 2, road_tile)) {
        //        action_state = FIGURE_ACTION_73_FIREMAN_RETURNING;
        //        destination_tile = road_tile;
        //        route_remove();
        //        roam_length = 0;
        //    } else {
        //        poof();
        //    }
        //}
        //move_ticks(1);
        //if (direction == DIR_FIGURE_NONE) {
        //    figure* target = figure_get(target_figure_id);
        //    destination_tile = target->tile;
        //    route_remove();
        //} else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_CAN_NOT_REACH) {
        //    poof();
        //}
        advance_action(ACTION_11_RETURNING_FROM_PATROL);
        break;
    }

    constexpr int DEATH_FRAMES = 8;
    switch (base.action_state) {
        default:
        break;
    
    case FIGURE_ACTION_75_FIREMAN_AT_FIRE:
    case 13:
        base.direction = base.attack_direction;
        //
        base.image_set_animation(model::fireman.anim["fight_fire"]);
        break;
    }
}

void figure_fireman::extinguish_fire() {
    building* burn = destination();
    int distance = calc_maximum_distance(tile(), burn->tile);
    if ((burn->state == BUILDING_STATE_VALID || burn->state == BUILDING_STATE_MOTHBALLED)
        && burn->type == BUILDING_BURNING_RUIN && distance < 2) {
        burn->fire_duration = 32;
        sound_effect_play(SOUND_EFFECT_FIRE_SPLASH);
    } else {
        base.wait_ticks = 1;
    }
    base.attack_direction = calc_general_direction(tile(), burn->tile);
    base.attack_direction = base.attack_direction % 8;

    base.wait_ticks--;
    if (base.wait_ticks <= 0) {
        base.wait_ticks_missile = 20;
        advance_action(FIGURE_ACTION_73_FIREMAN_RETURNING);

        if (!config_get(CONFIG_GP_CH_FIREMAN_RETUNING)) {
            if (!fight_fire()) {
                poof();
            }
        }
    }
}

bool figure_fireman::fight_fire() {
    if (building_list_burning_items().size() <= 0) {
        return false;
    }

    switch (base.action_state) {
    case FIGURE_ACTION_150_ATTACK:
    case FIGURE_ACTION_149_CORPSE:
    case FIGURE_ACTION_70_FIREMAN_CREATED:
    case FIGURE_ACTION_71_FIREMAN_ENTERING_EXITING:
    case FIGURE_ACTION_74_FIREMAN_GOING_TO_FIRE:
    case FIGURE_ACTION_75_FIREMAN_AT_FIRE:
    return false;
    }
    base.wait_ticks_missile++;
    if (base.wait_ticks_missile < 20)
        return false;

    auto result = building_maintenance_get_closest_burning_ruin(tile());
    int distance = calc_maximum_distance(tile(), result.second);
    if (result.first > 0 && distance <= 25) {
        building* ruin = building_get(result.first);
        base.wait_ticks_missile = 0;
        advance_action(FIGURE_ACTION_74_FIREMAN_GOING_TO_FIRE);
        base.destination_tile = result.second;
        base.set_destination(result.first);
        route_remove();
        ruin->set_figure(3, base.id);
        return true;
    }
    return false;
}

