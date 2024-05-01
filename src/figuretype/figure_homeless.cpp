#include "figure_homeless.h"

#include "city/city.h"
#include "core/profiler.h"
#include "core/random.h"
#include "figuretype/migrant.h"
#include "grid/road_access.h"
#include "building/building.h"
#include "city/population.h"

#include "js/js_game.h"

struct homeless_model : public figures::model_t<FIGURE_HOMELESS, figure_homeless> {};
homeless_model homeless_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_homeless);
void config_load_figure_homeless() {
    g_config_arch.r_section("figure_homeless", [] (archive arch) {
        homeless_m.anim.load(arch);
        homeless_m.sounds.load(arch);
    });
}

void figure_create_homeless(tile2i tile, int num_people) {
    figure* f = figure_create(FIGURE_HOMELESS, tile, DIR_0_TOP_RIGHT);
    f->action_state = FIGURE_ACTION_7_HOMELESS_CREATED;
    f->wait_ticks = 0;
    f->migrant_num_people = num_people;
    city_population_remove_homeless(num_people);
}

void figure_homeless::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/Homeless");
    tile2i exit = g_city.map.exit_point;
    switch (action_state()) {
    case FIGURE_ACTION_7_HOMELESS_CREATED:
        base.anim_frame = 0;
        wait_ticks++;
        if (wait_ticks > 51) {
            wait_ticks = 0;
            int building_id = figure_closest_house_with_room(tile());
            if (building_id) {
                building* b = building_get(building_id);
                tile2i road_tile;
                if (map_closest_road_within_radius(b->tile, b->size, 2, road_tile)) {
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
            building *ihome = building_get(base.immigrant_home_building_id);
            if (do_enterbuilding(false, ihome)) {
                figure_add_house_population(ihome, base.migrant_num_people);
            }
        }
        break;

    case ACTION_16_HOMELESS_RANDOM:
        base.roam_wander_freely = false;
        do_goto(destination_tile, TERRAIN_USAGE_ANY, FIGURE_ACTION_6_HOMELESS_LEAVING, FIGURE_ACTION_6_HOMELESS_LEAVING);
        if (direction() == DIR_FIGURE_CAN_NOT_REACH || direction() == DIR_FIGURE_REROUTE) {
            base.routing_try_reroute_counter++;
            if (base.routing_try_reroute_counter > 20) {
                poof();
                break;
            }
            base.state = FIGURE_STATE_ALIVE;
            destination_tile = random_around_point(tile(), tile(), /*step*/2, /*bias*/4, /*max_dist*/8);
            base.direction = DIR_0_TOP_RIGHT;
            advance_action(FIGURE_ACTION_6_HOMELESS_LEAVING);
        }
        break;

    case FIGURE_ACTION_6_HOMELESS_LEAVING:
        if (do_goto(exit, TERRAIN_USAGE_ANY)) {
            poof();
        }

        if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            base.routing_try_reroute_counter++;
            if (base.routing_try_reroute_counter > 20) {
                poof();
                break;
            }
            wait_ticks = 20;
            route_remove();
            base.state = FIGURE_STATE_ALIVE;
            tile2i road_tile;
            map_closest_road_within_radius(exit, 1, 2, road_tile);
            destination_tile = road_tile;
            base.direction = DIR_0_TOP_RIGHT;
            advance_action(ACTION_16_HOMELESS_RANDOM);
        }

        wait_ticks++;
        if (wait_ticks > 30) {
            wait_ticks = 0;
            int building_id = figure_closest_house_with_room(tile());
            if (building_id > 0) {
                building* b = building_get(building_id);
                tile2i road_tile;
                if (map_closest_road_within_radius(b->tile, b->size, 2, road_tile)) {
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
