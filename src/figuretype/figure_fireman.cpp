#include "figure/figure.h"

#include "graphics/image_groups.h"
#include "grid/road_access.h"
#include "core/calc.h"
#include "figure_fireman.h"
#include "sound/sound.h"
#include "game/game_config.h"
#include "building/building_house.h"
#include "building/building_burning_ruin.h"
#include "graphics/animation.h"
#include "city/city_health.h"
#include "city/city.h"
#include "figure/service.h"
#include "grid/building.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_fireman);

void figure_fireman::on_create() {
    figure_impl::on_create();
}

void figure_fireman::figure_before_action() {
    building* b = home();
    if (!b->is_valid() || !b->has_figure(0, id())) {
        poof();
    }
}

sound_key figure_fireman::phrase_key() const {
    if (base.action_state == ACTION_74_FIREMAN_GOING_TO_FIRE) {
        return "going_to_fire";
    }

    svector<sound_key, 10> keys;
    if (base.action_state == ACTION_75_FIREMAN_AT_FIRE) {
        keys.push_back("fighting_fire_also");
        keys.push_back("fighting_fire");

        int index = rand() % keys.size();
        return keys[index];
    }

    if (g_city.health.value < 20) {
        keys.push_back("desease_can_start_at_any_moment");
    }

    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_FOOD) {
        keys.push_back("no_food_in_city");
    }

    if (formation_get_num_forts() < 1) {
        keys.push_back("city_not_safety_workers_leaving");
    }

    if (g_city.labor.workers_needed >= 10) {
        keys.push_back("need_workers");
    }

    if (g_city.labor.workers_needed >= 20) {
        keys.push_back("need_more_workers");
    }

    int houses_risk_fire = 0;
    buildings_valid_do([&] (building &b) {
        houses_risk_fire += (b.fire_risk > 70) ? 1 : 0;
    });

    if (houses_risk_fire > 0) {
        keys.push_back("hight_fire_level");
    }

    if (g_city.religion.least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back("gods_are_angry");
    } else {
        keys.push_back("gods_are_pleasures");
    }

    if (g_city.festival.months_since_festival > 6) {  // low entertainment
        keys.push_back("low_entertainment");
    }

    const int sentiment = g_city.sentiment.value;
    if (sentiment > 90) {
        keys.push_back("city_is_amazing");
    }

    int index = rand() % keys.size();
    return xstring().printf("fireman_%s", keys[index].c_str());
}

void figure_fireman::figure_action() { // doubles as fireman! not as policeman!!!
    fight_fire();

    building* b = home();
    switch (base.action_state) {
    case ACTION_70_FIREMAN_CREATED:
        advance_action(ACTION_72_FIREMAN_ROAMING);
        break;

    case ACTION_73_FIREMAN_RETURNING:
        do_returnhome(TERRAIN_USAGE_PREFER_ROADS);
        break;

    case ACTION_71_FIREMAN_ENTERING_EXITING:
        do_enterbuilding(true, home());
        break;

    case ACTION_72_FIREMAN_ROAMING:
        do_roam(TERRAIN_USAGE_ROADS, ACTION_73_FIREMAN_RETURNING);
        break;

    case ACTION_74_FIREMAN_GOING_TO_FIRE:
        if (do_goto(base.destination_tile, TERRAIN_USAGE_PREFER_ROADS, ACTION_75_FIREMAN_AT_FIRE)) {
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
                advance_action(ACTION_75_FIREMAN_AT_FIRE);
            }
            
            if (!next_b || next_b->state == BUILDING_STATE_UNUSED || next_b->type != BUILDING_BURNING_RUIN) {
                clear_ruin_destination();
                bool has_fire_around = fight_fire();
                if (!has_fire_around) {
                    advance_action(ACTION_73_FIREMAN_RETURNING);
                }
            }

            if (base.movement_ticks_watchdog > 10) {
                base.movement_ticks_watchdog = 0;
                clear_ruin_destination();
                route_remove();
                advance_action(ACTION_73_FIREMAN_RETURNING);
            }
        }
        break;

    case ACTION_75_FIREMAN_AT_FIRE:
        extinguish_fire();
        break;

    case ACTION_76_FIREMAN_GOING_TO_ENEMY:
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
        assert(false && "should not happens");
        advance_action(ACTION_73_FIREMAN_RETURNING);
        break;
    }
}

void figure_fireman::extinguish_fire() {
    building* burn = destination();
    int distance = calc_maximum_distance(tile(), burn->tile);
    const bool is_valid = (burn->state == BUILDING_STATE_VALID || burn->state == BUILDING_STATE_MOTHBALLED) && burn->type == BUILDING_BURNING_RUIN;
    if (is_valid && distance < 2 && burn->fire_duration > 0) {
        burn->fire_duration--;
        g_sound.play_effect(SOUND_EFFECT_FIRE_SPLASH);
    } else {
        base.wait_ticks = 1;
    }

    base.attack_direction = calc_general_direction(tile(), burn->tile);
    base.attack_direction = base.attack_direction % 8;

    base.wait_ticks--;
    if (base.wait_ticks <= 0) {
        base.wait_ticks_missile = 20;
        advance_action(ACTION_73_FIREMAN_RETURNING);

        if (!game_features::gameplay_change_fireman_returning) {
            if (!fight_fire()) {
                assert(false);
                poof();
            }
        }
    }
}

bool figure_fireman::fight_fire() {
    const auto &burnings = building_burning_ruin::get_all();
    if (burnings.size() <= 0) {
        return false;
    }

    switch (base.action_state) {
    case FIGURE_ACTION_150_ATTACK:
    case FIGURE_ACTION_149_CORPSE:
    case ACTION_70_FIREMAN_CREATED:
    case ACTION_71_FIREMAN_ENTERING_EXITING:
    case ACTION_74_FIREMAN_GOING_TO_FIRE:
    case ACTION_75_FIREMAN_AT_FIRE:
        return false;
    }

    base.wait_ticks_missile++;
    if (base.wait_ticks_missile < 20) {
        return false;
    }

    auto result = building_burning_ruin::get_closest_from(tile());
    int distance = calc_maximum_distance(tile(), result.second);
    if (result.first > 0 && distance <= 25) {
        building* ruin = building_get(result.first);
        base.wait_ticks_missile = 0;
        advance_action(ACTION_74_FIREMAN_GOING_TO_FIRE, result.second);
        base.set_destination(result.first);
        route_remove();
        ruin->set_figure(3, base.id);
        return true;
    }

    return false;
}

int figure_fireman::provide_service() {
    int min_happiness;
    int result = figure_provide_service(tile(), &base, [&] (building *b, figure *f) {
        b = b->main();
        b->fire_risk = 0;

        auto house = b->dcast_house();
        if (house) {
            min_happiness = std::max<short>(house->runtime_data().house_happiness, min_happiness);
        }
    });
    base.min_max_seen = min_happiness;
    return result;
}

figure_sound_t figure_fireman::get_sound_reaction(xstring key) const {
    return current_params().sounds[key];
}

void figure_fireman::update_animation() {
    figure_impl::update_animation();

    switch (action_state()) {  
    case ACTION_75_FIREMAN_AT_FIRE:
        base.direction = base.attack_direction;
        image_set_animation(animkeys().fight_fire);
        break;

    case ACTION_73_FIREMAN_RETURNING:
    case ACTION_72_FIREMAN_ROAMING:
    case ACTION_74_FIREMAN_GOING_TO_FIRE:
        image_set_animation(animkeys().walk);
        break;
    }
}
