#include "figure_emigrant.h"

#include "core/profiler.h"
#include "core/random.h"
#include "city/map.h"
#include "grid/road_access.h"
#include "city/population.h"
#include "building/house.h"
#include "city/migration.h"
#include "city/sentiment.h"

#include "js/js_game.h"

struct emigrant_model : public figures::model_t<FIGURE_EMIGRANT, figure_emigrant> {};
emigrant_model emigrant_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_emigrant);
void config_load_figure_emigrant() {
    g_config_arch.r_section("figure_emigrant", [] (archive arch) {
        emigrant_m.anim.load(arch);
        emigrant_m.sounds.load(arch);
    });
}

void figure_create_emigrant(building* house, int num_people) {
    city_population_remove(num_people);
    if (num_people < house->house_population) {
        house->house_population -= num_people;
    } else {
        house->house_population = 0;
        building_house_change_to_vacant_lot(house);
    }

    figure* f = figure_create(FIGURE_EMIGRANT, house->tile, DIR_0_TOP_RIGHT);
    if (house->subtype.house_level >= HOUSE_COMMON_MANOR) {
        city_migration_nobles_leave_city(num_people);
    }

    f->action_state = FIGURE_ACTION_4_EMIGRANT_CREATED;
    f->wait_ticks = 0;
    f->migrant_num_people = num_people;
}

void figure_emigrant::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/Emigrant");
    tile2i exit = city_map_exit_point();
    switch (action_state()) {
    case FIGURE_ACTION_4_EMIGRANT_CREATED:
        base.anim_frame = 0;
        wait_ticks++;
        if (wait_ticks >= 5) {
            advance_action(FIGURE_ACTION_5_EMIGRANT_EXITING_HOUSE);
        }
        break;

    case FIGURE_ACTION_5_EMIGRANT_EXITING_HOUSE:
        do_exitbuilding(false, FIGURE_ACTION_6_EMIGRANT_LEAVING);
        break;

    case ACTION_16_EMIGRANT_RANDOM:
        base.roam_wander_freely = false;
        do_goto(destination_tile, TERRAIN_USAGE_ANY, FIGURE_ACTION_6_EMIGRANT_LEAVING, FIGURE_ACTION_6_EMIGRANT_LEAVING);
        if (direction() == DIR_FIGURE_CAN_NOT_REACH || direction() == DIR_FIGURE_REROUTE) {
            base.state = FIGURE_STATE_ALIVE;
            destination_tile = random_around_point(tile(), tile(), /*step*/2, /*bias*/4, /*max_dist*/8);
            base.direction = DIR_0_TOP_RIGHT;
            advance_action(FIGURE_ACTION_6_EMIGRANT_LEAVING);
        }
        break;

    case FIGURE_ACTION_6_EMIGRANT_LEAVING:
    case 10:
        wait_ticks--;
        if (wait_ticks > 0) {
            base.anim_frame = 0;
            break;
        }

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
            advance_action(ACTION_16_EMIGRANT_RANDOM);
        }
        break;
    }

    {
        OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/Emigrant/Update Image");
        update_direction_and_image();
    }
}

figure_sound_t figure_emigrant::get_sound_reaction(pcstr key) const {
    return emigrant_m.sounds[key];
}

sound_key figure_emigrant::phrase_key() const {
    switch (city_sentiment_low_mood_cause()) {
    case LOW_MOOD_NO_JOBS: return "no_job_in_city";
    case LOW_MOOD_NO_FOOD: return "no_food_in_city";
    case LOW_MOOD_HIGH_TAXES: return "tax_too_high";
    case LOW_MOOD_LOW_WAGES: return "salary_too_low";
    }

    building *b = destination();
    if (!b || !b->id) {
        return "no_house_for_me";
    }

    return  "all_good_in_city";
}
