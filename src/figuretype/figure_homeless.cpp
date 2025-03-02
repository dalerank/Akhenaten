#include "figure_homeless.h"

#include "city/city.h"
#include "core/profiler.h"
#include "core/random.h"
#include "core/calc.h"
#include "grid/road_access.h"
#include "grid/terrain.h"
#include "building/building.h"
#include "building/building_house.h"
#include "city/population.h"

#include "js/js_game.h"

figures::model_t<figure_homeless> homeless_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_homeless);
void config_load_figure_homeless() {
    homeless_m.load();
}

void figure_create_homeless(tile2i tile, int num_people) {
    figure* f = figure_create(FIGURE_HOMELESS, tile, DIR_0_TOP_RIGHT);
    f->action_state = FIGURE_ACTION_7_HOMELESS_CREATED;
    f->wait_ticks = 0;
    f->migrant_num_people = num_people;
    city_population_remove_homeless(num_people);
}

int figure_homeless::find_closest_house_with_room(tile2i tile) {
    int min_dist = 1000;
    int min_building_id = 0;
    int max_id = building_get_highest_id();
    for (int i = 1; i <= max_id; i++) {
        auto house = building_get(i)->dcast_house();
        if (house && house->state() == BUILDING_STATE_VALID && house->base.house_size && house->distance_from_entry() > 0 && house->population_room() > 0) {
            if (!house->base.has_figure(2)) {
                int dist = calc_maximum_distance(tile, house->tile());
                if (dist < min_dist) {
                    min_dist = dist;
                    min_building_id = i;
                }
            }
        }
    }
    return min_building_id;
}

void figure_homeless::on_destroy() {
    auto h = home();
    auto bhome = building_get(base.immigrant_home_building_id);
    if (h == bhome) {
        bhome->remove_figure(2);
    }
}

void figure_homeless::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/Homeless");
    switch (action_state()) {
    case FIGURE_ACTION_7_HOMELESS_CREATED:
        base.anim.frame = 0;
        base.wait_ticks++;
        if (base.wait_ticks > 51) {
            base.wait_ticks = 0;
            int building_id = find_closest_house_with_room(tile());
            if (building_id) {
                building* b = building_get(building_id);
                tile2i road_tile = map_closest_road_within_radius(b->tile, b->size, 2);
                if (road_tile.valid()) {
                    b->set_figure(2, id());
                    base.immigrant_home_building_id = building_id;
                    advance_action(FIGURE_ACTION_8_HOMELESS_GOING_TO_HOUSE);
                } else {
                    poof();
                }
            } else {
                advance_action(FIGURE_ACTION_6_HOMELESS_LEAVING);
            }
        }
        break;

    case FIGURE_ACTION_8_HOMELESS_GOING_TO_HOUSE:
        if (!base.has_home()) {
            base.direction = DIR_0_TOP_RIGHT;
            advance_action(FIGURE_ACTION_6_HOMELESS_LEAVING);
        } else {
            building *ihome = building_get(base.immigrant_home_building_id);
            do_gotobuilding(ihome, true, TERRAIN_USAGE_ANY, FIGURE_ACTION_9_HOMELESS_ENTERING_HOUSE);
        }
        break;

    case FIGURE_ACTION_9_HOMELESS_ENTERING_HOUSE:
        {
            building *b = building_get(base.immigrant_home_building_id);
            if (do_enterbuilding(false, b)) {
                building_house *house = b->dcast_house();
                house->add_population(base.migrant_num_people);
            }
        }
        break;

    case ACTION_16_HOMELESS_RANDOM:
        base.roam_wander_freely = false;
        do_goto(base.destination_tile, TERRAIN_USAGE_ANY, FIGURE_ACTION_6_HOMELESS_LEAVING, FIGURE_ACTION_6_HOMELESS_LEAVING);
        if (direction() == DIR_FIGURE_CAN_NOT_REACH || direction() == DIR_FIGURE_REROUTE) {
            base.routing_try_reroute_counter++;
            if (base.routing_try_reroute_counter > 20) {
                poof();
                break;
            }
            base.state = FIGURE_STATE_ALIVE;
            base.destination_tile = random_around_point(tile(), tile(), /*step*/2, /*bias*/4, /*max_dist*/8);
            base.direction = DIR_0_TOP_RIGHT;
            advance_action(FIGURE_ACTION_6_HOMELESS_LEAVING);
        }
        break;

    case FIGURE_ACTION_6_HOMELESS_LEAVING:
        if (do_goto(g_city.map.exit_point, TERRAIN_USAGE_ANY)) {
            poof();
        }

        if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            base.routing_try_reroute_counter++;
            if (base.routing_try_reroute_counter > 20) {
                poof();
                break;
            }
            base.wait_ticks = 20;
            route_remove();
            base.state = FIGURE_STATE_ALIVE;
            base.destination_tile = g_city.map.closest_exit_tile_within_radius();
            base.direction = DIR_0_TOP_RIGHT;
            advance_action(ACTION_16_HOMELESS_RANDOM);
        }

        base.wait_ticks++;
        if (base.wait_ticks > 30) {
            base.wait_ticks = 0;
            int building_id = find_closest_house_with_room(tile());
            if (building_id > 0) {
                building* b = building_get(building_id);
                tile2i road_tile = map_closest_road_within_radius(b->tile, b->size, 2);
                if (road_tile.valid()) {
                    b->set_figure(2, id());
                    base.immigrant_home_building_id = building_id;
                    advance_action(FIGURE_ACTION_8_HOMELESS_GOING_TO_HOUSE);
                }
            }
        }
        break;
    }
}

void figure_homeless::figure_before_action() {
    switch (action_state()) {
    case FIGURE_ACTION_150_ATTACK:
        base.figure_combat_handle_attack();
        break;

    case FIGURE_ACTION_149_CORPSE:
        base.figure_combat_handle_corpse();
        break;

    case FIGURE_ACTION_125_ROAMING:
    case ACTION_1_ROAMING:
        // do nothing
        break;

    case FIGURE_ACTION_126_ROAMER_RETURNING:
    case ACTION_2_ROAMERS_RETURNING:
        // do nothing
        break;
    }
}

const animations_t &figure_homeless::anim() const {
    return homeless_m.anim;
}
