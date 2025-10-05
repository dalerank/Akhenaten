#include "figure_constable.h"

#include "core/calc.h"
#include "grid/road_access.h"
#include "grid/building.h"
#include "figure/enemy_army.h"
#include "figure/image.h"
#include "figure/service.h"
#include "city/city.h"
#include "city/city_labor.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "building/building_house.h"

figure_constable::static_params constable_m;

void figure_constable::figure_before_action() {
    building *h = home();
    if (h->state != BUILDING_STATE_VALID || !h->has_figure(0, id())) {
        poof();
    }
}

void figure_constable::update_animation() {
    figure_impl::update_animation();

    pcstr anim_key = "walk";
    switch (action_state()) {
    case FIGURE_ACTION_150_ATTACK: anim_key = "attack"; break;
    case FIGURE_ACTION_149_CORPSE: anim_key = "death"; break;
    }

    image_set_animation(anim_key);
}

sound_key figure_constable::phrase_key() const {
    svector<sound_key, 10> keys;

    if (base.min_max_seen < 10) {
        keys.push_back("policeman_very_low_crime_level");
    } else if (base.min_max_seen < 30) {
        keys.push_back("policeman_low_crime_level");
    } else {
        keys.push_back("policeman_usual_crime_level");
    }

    if (formation_get_num_forts() < 0) {
        keys.push_back("policeman_city_not_safety");
        keys.push_back("policeman_enemies_are_coming");
        keys.push_back("policeman_no_army");
        keys.push_back("policeman_no_army_2");
    }

    if (g_city.labor.workers_needed >= 10) {
        keys.push_back("policeman_need_workers");
    }

    if (g_city.labor.workers_needed >= 20) {
        keys.push_back("policeman_need_more_workers");
    }

    if (g_city.health.value < 20) {
        keys.push_back("policeman_desease_can_start_at_any_moment");
    }

    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_FOOD) {
        keys.push_back("policeman_no_food_in_city");
    }

    if (g_city.religion.least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back("policeman_gods_are_angry");
    }

    if (g_city.labor.unemployment_percentage >= 15) {
        keys.push_back("policeman_much_unemployments");
    }

    if (g_city.festival.months_since_festival > 6) {  // low entertainment
        keys.push_back("policeman_low_entertainment");
    }

    const int sentiment = g_city.sentiment.value;
    if (sentiment > 90) {
        keys.push_back("policeman_city_is_amazing");
    } else  if (sentiment > 40) {
        keys.push_back("policeman_city_is_good");
    }

    keys.push_back("policeman_iam_too_busy_that_talk");
    keys.push_back("policeman_i_hope_my_work_is_need");

    int index = rand() % keys.size();
    return keys[index];
}

int figure_constable::provide_service() {
    int max_criminal_active = 0;
    int houses_serviced = figure_provide_service(tile(), &base, [&] (building* b, figure *f) {
        auto house = b->dcast_house();
        if (!house) {
            return;
        }

        auto &housed = house->runtime_data();
        housed.criminal_active -= 1;
        housed.criminal_active = std::max<int>(0, housed.criminal_active);

        if (housed.criminal_active > max_criminal_active) {
            max_criminal_active = housed.criminal_active;
        }
    });

    if (max_criminal_active > base.min_max_seen)
        base.min_max_seen = max_criminal_active;
    else if (base.min_max_seen <= 10)
        base.min_max_seen = 0;
    else
        base.min_max_seen -= 10;

    return houses_serviced;
}

bool figure_constable::fight_enemy(int category, int max_distance) {
    if (!g_city.figures_has_security_breach() && enemy_army_total_enemy_formations() <= 0) {
        return false;
    }

    auto &d = runtime_data();

    switch (action_state()) {
    case FIGURE_ACTION_150_ATTACK:
    case FIGURE_ACTION_149_CORPSE:
    case FIGURE_ACTION_70_POLICEMAN_CREATED:
    case FIGURE_ACTION_71_POLICEMAN_ENTERING_EXITING:
    case FIGURE_ACTION_76_POLICEMAN_GOING_TO_ENEMY:
    case FIGURE_ACTION_77_POLICEMAN_AT_ENEMY:
        return false;
    }
    d.wait_ticks_next_target++;
    if (d.wait_ticks_next_target < 10)
        return false;

    d.wait_ticks_next_target = 0;
    auto result = base.is_nearby(NEARBY_HOSTILE);
    if (result.fid > 0 && result.distance <= max_distance) {
        figure* enemy = figure_get(result.fid);
        d.wait_ticks_next_target = 0;
        advance_action(FIGURE_ACTION_76_POLICEMAN_GOING_TO_ENEMY);
        base.destination_tile = enemy->tile;
        base.target_figure_id = result.fid;
        enemy->targeted_by_figure_id = id();
        //base.target_figure_created_sequence = enemy->created_sequence;
        route_remove();
        return true;
    }

    return false;
}

void figure_constable::figure_action() {
    fight_enemy(2, 22);

    building* b = home();
    switch (action_state()) {
    case FIGURE_ACTION_70_POLICEMAN_CREATED:
        advance_action(FIGURE_ACTION_72_POLICEMAN_ROAMING);
        break;

    case 9:
    case FIGURE_ACTION_71_POLICEMAN_ENTERING_EXITING:
        do_enterbuilding(true, b);
        break;

    case 10:
    case FIGURE_ACTION_72_POLICEMAN_ROAMING:
        do_roam(TERRAIN_USAGE_ROADS, FIGURE_ACTION_73_POLICEMAN_RETURNING);
        break;

    case ACTION_11_RETURNING_EMPTY:
    case FIGURE_ACTION_73_POLICEMAN_RETURNING:
        do_returnhome(TERRAIN_USAGE_PREFER_ROADS);

    case FIGURE_ACTION_76_POLICEMAN_GOING_TO_ENEMY:
        base.terrain_usage = TERRAIN_USAGE_ANY;
        if (!base.target_is_alive()) {
            tile2i road_tile = map_closest_road_within_radius(b->tile, b->size, 2);
            if (road_tile.valid()) {
                advance_action(FIGURE_ACTION_73_POLICEMAN_RETURNING);
                base.destination_tile = road_tile;
                route_remove();
                base.roam_length = 0;
            } else {
                poof();
            }
        }
        base.move_ticks(1);
        if (direction() == DIR_FIGURE_NONE) {
            figure* target = figure_get(base.target_figure_id);
            base.destination_tile = target->tile;
            route_remove();
        } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }
        break;
    }
}
