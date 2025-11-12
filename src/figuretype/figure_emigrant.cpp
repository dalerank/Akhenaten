#include "figure_emigrant.h"

#include "core/profiler.h"
#include "core/random.h"
#include "city/map.h"
#include "grid/road_access.h"
#include "grid/terrain.h"
#include "building/building_house.h"
#include "city/city.h"
#include "game/game_events.h"
#include "widget/debug_console.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_emigrant);

void ANK_PERMANENT_CALLBACK(event_create_emigrant, ev) {
    auto house = building_get(ev.bid)->dcast_house();
    if (!house) {
        return;
    }

    g_city.population.remove(ev.num_people);
    if (ev.num_people < house->house_population()) {
        house->change_population(-ev.num_people);
    } else {
        house->change_to_vacant_lot();
    }

    auto em = figure_create(FIGURE_EMIGRANT, house->tile(), DIR_0_TOP_RIGHT)->dcast_emigrant();
    if (house->house_level() >= HOUSE_COMMON_MANOR) {
        g_city.migration.nobles_leave_city(ev.num_people);
    }

    em->advance_action(ACTION_4_EMIGRANT_CREATED);
    em->base.wait_ticks = 0;
    em->runtime_data().migrant_num_people = ev.num_people;
}

void figure_emigrant::debug_show_properties() {
    auto &d = runtime_data();
    game_debug_show_property("migrant_num_people", d.migrant_num_people);
}

void figure_emigrant::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/Emigrant");
    switch (action_state()) {
    case ACTION_4_EMIGRANT_CREATED:
        base.animctx.frame = 0;
        base.wait_ticks++;
        if (base.wait_ticks >= 5) {
            advance_action(ACTION_5_EMIGRANT_EXITING_HOUSE);
        }
        break;

    case ACTION_5_EMIGRANT_EXITING_HOUSE:
        do_exitbuilding(false, ACTION_6_EMIGRANT_LEAVING);
        break;

    case ACTION_16_EMIGRANT_RANDOM:
        base.roam_wander_freely = false;
        do_goto(base.destination_tile, TERRAIN_USAGE_ANY, ACTION_6_EMIGRANT_LEAVING, ACTION_6_EMIGRANT_LEAVING);
        if (direction() == DIR_FIGURE_CAN_NOT_REACH || direction() == DIR_FIGURE_REROUTE) {
            base.state = FIGURE_STATE_ALIVE;
            base.destination_tile = random_around_point(tile(), tile(), /*step*/2, /*bias*/4, /*max_dist*/8);
            base.direction = DIR_0_TOP_RIGHT;
            advance_action(ACTION_6_EMIGRANT_LEAVING);
        }
        break;

    case ACTION_6_EMIGRANT_LEAVING:
        base.wait_ticks--;
        if (base.wait_ticks > 0) {
            base.animctx.frame = 0;
            break;
        }

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
            advance_action(ACTION_16_EMIGRANT_RANDOM);
        }
        break;
    }
}

void figure_emigrant::update_animation() {
    figure_impl::update_animation();

    int dir = base.figure_image_direction();
    switch (action_state()) {
    case ACTION_2_EMIGRANT_ARRIVING:
    case ACTION_6_EMIGRANT_LEAVING:
        base.cart_image_id = anim("cart").first_img() + dir;
        base.figure_image_set_cart_offset((dir + 4) % 8);
        break;
    }
}

figure_sound_t figure_emigrant::get_sound_reaction(xstring key) const {
    return current_params().sounds[key];
}

sound_key figure_emigrant::phrase_key() const {
    switch (g_city.sentiment.low_mood_cause) {
    case LOW_MOOD_NO_JOBS: return "emigrant_no_job_in_city";
    case LOW_MOOD_NO_FOOD: return "emigrant_no_food_in_city";
    case LOW_MOOD_HIGH_TAXES: return "emigrant_tax_too_high";
    case LOW_MOOD_LOW_WAGES: return "emigrant_salary_too_low";
    }

    building *b = destination();
    if (!b || !b->id) {
        return "emigrant_no_house_for_me";
    }

    return "emigrant_all_good_in_city";
}