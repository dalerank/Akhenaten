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
#include "city/health.h"
#include "city/sentiment.h"
#include "city/labor.h"
#include "city/gods.h"
#include "city/data_private.h"
#include "figure/service.h"
#include "grid/building.h"

#include "js/js_game.h"

struct fireman_model : figures::model_t<FIGURE_FIREMAN, figure_fireman> {};
fireman_model fireman_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_fireman);
void config_load_figure_fireman() {
    g_config_arch.r_section("figure_fireman", [] (archive arch) {
        fireman_m.anim.load(arch);
    });
}

void figure_fireman::on_create() {

}

sound_key figure_fireman::phrase_key() const {
    if (base.action_state == FIGURE_ACTION_74_FIREMAN_GOING_TO_FIRE) {
        return "fireman_going_to_fire";
    }

    svector<sound_key, 10> keys;
    if (base.action_state == FIGURE_ACTION_75_FIREMAN_AT_FIRE) {
        keys.push_back("fireman_fighting_fire_also");
        keys.push_back("fireman_fighting_fire");

        int index = rand() % keys.size();
        return keys[index];
    }

    if (city_health() < 20) {
        keys.push_back("fireman_desease_can_start_at_any_moment");
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_FOOD) {
        keys.push_back("fireman_no_food_in_city");
    }

    if (formation_get_num_forts() < 1) {
        keys.push_back("fireman_city_not_safety_workers_leaving");
    }

    if (city_labor_workers_needed() >= 10) {
        keys.push_back("fireman_need_workers");
    }

    if (city_labor_workers_needed() >= 20) {
        keys.push_back("fireman_need_more_workers");
    }

    int houses_risk_fire = 0;
    buildings_valid_do([&] (building &b) {
        houses_risk_fire += (b.fire_risk > 70) ? 1 : 0;
    });

    if (houses_risk_fire > 0) {
        keys.push_back("fireman_hight_fire_level");
    }

    if (city_gods_least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back("fireman_gods_are_angry");
    } else {
        keys.push_back("fireman_gods_are_pleasures");
    }

    if (city_data_struct()->festival.months_since_festival > 6) {  // low entertainment
        keys.push_back("fireman_low_entertainment");
    }

    if (city_sentiment() > 90) {
        keys.push_back("fireman_city_is_amazing");
    }

    int index = rand() % keys.size();
    return keys[index];
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
        base.image_set_animation(fireman_m.anim["fight_fire"]);
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

void prefect_coverage(building* b, figure *f, int &min_happiness_seen) {
    if (b->type == BUILDING_SENET_HOUSE || b->type == BUILDING_STORAGE_YARD_SPACE)
        b = b->main();

    b->fire_risk = 0;
    if (b->sentiment.house_happiness < min_happiness_seen) {
        min_happiness_seen = b->sentiment.house_happiness;
    }
}

int figure_fireman::provide_service() {
    int min_happiness;
    int result = figure_provide_service(tile(), &base, min_happiness, prefect_coverage);
    base.min_max_seen = min_happiness;
    return result;
}

figure_sound_t figure_fireman::get_sound_reaction(pcstr key) const {
    return fireman_m.sounds[key];
}
