#include "migrant.h"

#include "building/house.h"
#include "building/model.h"
#include "city/map.h"
#include "city/population.h"
#include "city/city_data.h"
#include "core/calc.h"
#include "core/random.h"
#include "core/profiler.h"
#include "figure/combat.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "grid/road_access.h"
#include "grid/terrain.h"

void figure_create_homeless(tile2i tile, int num_people) {
    figure* f = figure_create(FIGURE_HOMELESS, tile, DIR_0_TOP_RIGHT);
    f->action_state = FIGURE_ACTION_7_HOMELESS_CREATED;
    f->wait_ticks = 0;
    f->migrant_num_people = num_people;
    city_population_remove_homeless(num_people);
}

void figure::update_direction_and_image() {
    //    figure_image_update(image_id_from_group(GROUP_FIGURE_MIGRANT));
    if (action_state == FIGURE_ACTION_2_IMMIGRANT_ARRIVING || action_state == FIGURE_ACTION_6_EMIGRANT_LEAVING) {
        int dir = figure_image_direction();
        cart_image_id = image_id_from_group(GROUP_FIGURE_IMMIGRANT_CART) + dir;
        figure_image_set_cart_offset((dir + 4) % 8);
    }
}

static int closest_house_with_room(tile2i tile) {
    int min_dist = 1000;
    int min_building_id = 0;
    int max_id = building_get_highest_id();
    for (int i = 1; i <= max_id; i++) {
        building* b = building_get(i);
        if (b->state == BUILDING_STATE_VALID && b->house_size && b->distance_from_entry > 0
            && b->house_population_room > 0) {
            if (!b->has_figure(2)) {
                int dist = calc_maximum_distance(tile, b->tile);
                if (dist < min_dist) {
                    min_dist = dist;
                    min_building_id = i;
                }
            }
        }
    }
    return min_building_id;
}

void figure_add_house_population(building* house, int num_people) {
    int max_people = model_get_house(house->subtype.house_level)->max_people;
    if (house->house_is_merged)
        max_people *= 4;

    int room = max_people - house->house_population;
    if (room < 0)
        room = 0;

    if (room < num_people)
        num_people = room;

    if (!house->house_population) {
        building_house_change_to(house, BUILDING_HOUSE_CRUDE_HUT);
    }

    house->house_population += num_people;
    house->house_population_room = max_people - house->house_population;
    city_population_add(num_people);
    house->remove_figure(2);
}

void figure::homeless_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/Homeless");
    tile2i exit = city_map_exit_point();
    switch (action_state) {
    case FIGURE_ACTION_7_HOMELESS_CREATED:
        anim_frame = 0;
        wait_ticks++;
        if (wait_ticks > 51) {
            wait_ticks = 0;
            int building_id = closest_house_with_room(tile);
            if (building_id) {
                building* b = building_get(building_id);
                tile2i road_tile;
                if (map_closest_road_within_radius(b->tile, b->size, 2, road_tile)) {
                    b->set_figure(2, id);
                    immigrant_home_building_id = building_id;
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
        if (!has_home()) {
            direction = DIR_0_TOP_RIGHT;
            advance_action(FIGURE_ACTION_6_HOMELESS_LEAVING);
        } else {
            building *ihome = building_get(immigrant_home_building_id);
            do_gotobuilding(ihome, true, TERRAIN_USAGE_ANY, FIGURE_ACTION_9_HOMELESS_ENTERING_HOUSE);
        }
        break;

    case FIGURE_ACTION_9_HOMELESS_ENTERING_HOUSE:
        {
            building *ihome = building_get(immigrant_home_building_id);
            if (do_enterbuilding(false, ihome)) {
                figure_add_house_population(ihome, migrant_num_people);
            }
            //            is_ghost = in_building_wait_ticks ? 1 : 0;
        }
        break;

    case ACTION_16_HOMELESS_RANDOM:
        roam_wander_freely = false;
        do_goto(destination_tile, TERRAIN_USAGE_ANY, FIGURE_ACTION_6_HOMELESS_LEAVING, FIGURE_ACTION_6_HOMELESS_LEAVING);
        if (direction == DIR_FIGURE_CAN_NOT_REACH || direction == DIR_FIGURE_REROUTE) {
            routing_try_reroute_counter++;
            if (routing_try_reroute_counter > 20) {
                poof();
                break;
            }
            state = FIGURE_STATE_ALIVE;
            destination_tile = random_around_point(tile, tile, /*step*/2, /*bias*/4, /*max_dist*/8);
            direction = DIR_0_TOP_RIGHT;
            advance_action(FIGURE_ACTION_6_HOMELESS_LEAVING);
        }
        break;

    case FIGURE_ACTION_6_HOMELESS_LEAVING:
        if (do_goto(exit, TERRAIN_USAGE_ANY)) {
            poof();
        }

        if (direction == DIR_FIGURE_CAN_NOT_REACH) {
            routing_try_reroute_counter++;
            if (routing_try_reroute_counter > 20) {
                poof();
                break;
            }
            wait_ticks = 20;
            route_remove();
            state = FIGURE_STATE_ALIVE;
            tile2i road_tile;
            map_closest_road_within_radius(exit, 1, 2, road_tile);
            destination_tile = road_tile;
            direction = DIR_0_TOP_RIGHT;
            advance_action(ACTION_16_HOMELESS_RANDOM);
        }

        wait_ticks++;
        if (wait_ticks > 30) {
            wait_ticks = 0;
            int building_id = closest_house_with_room(tile);
            if (building_id > 0) {
                building* b = building_get(building_id);
                tile2i road_tile;
                if (map_closest_road_within_radius(b->tile, b->size, 2, road_tile)) {
                    b->set_figure(2, id);
                    immigrant_home_building_id = building_id;
                    advance_action(FIGURE_ACTION_8_HOMELESS_GOING_TO_HOUSE);
                }
            }
        }
        break;
    }
}
