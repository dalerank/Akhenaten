#include "figure_carpenter.h"

#include "building/monument_mastaba.h"
#include "building/building_statue.h"
#include "grid/terrain.h"
#include "grid/grid.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_carpenter);

void figure_carpenter::figure_action() {
    base.use_cross_country = false;
    base.max_roam_length = 384;
    building *bhome = home();
    building *b_dest = destination();
    e_terrain_usage terrain_usage = TERRAIN_USAGE_ROADS;
    if (!bhome->is_valid() || !b_dest->is_valid()) {
        poof();
        return;
    }

    if (b_dest->is_monument()) {
        terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
    } else {
        terrain_usage = TERRAIN_USAGE_ROADS;
    }

    switch (action_state()) {
    case 9:
        break;

    case ACTION_30_CARPENTER_CREATED_ROAMING:
        base.destination_tile = destination()->access_tile();
        advance_action(ACTION_31_CARPENTER_GOING_TO_GARDEN);
        break;

    case ACTION_10_CARPENTER_CREATED:
        base.destination_tile = destination()->access_tile();
        advance_action(ACTION_11_CARPENTER_GOING);
        break;

    case ACTION_20_CARPENTER_DESTROY:
        poof();
        break;

    case ACTION_31_CARPENTER_GOING_TO_GARDEN:
        if (do_goto(base.destination_tile, terrain_usage, -1, ACTION_20_CARPENTER_DESTROY)) {
            base.wait_ticks = 0;
            advance_action(ACTION_14_CARPENTER_WORK_GROUND);
        }
        break;

    case ACTION_11_CARPENTER_GOING:
        if (do_goto(base.destination_tile, terrain_usage, -1, ACTION_20_CARPENTER_DESTROY)) {
            advance_action(ACTION_17_CARPENTER_LOOKING_FOR_WORK_TILE);
        }
        break;

    case ACTION_14_CARPENTER_WORK_GROUND:
    case ACTION_15_CARPENTER_WORK_VERT:
        base.wait_ticks++;
        if (base.wait_ticks > simulation_time_t::ticks_in_day * 2) {
            auto statue = smart_cast<building_statue>(building_get(runtime_data().destination_bid));
            if (statue) {
                statue->set_service(100);
            }
            advance_action(ACTION_16_CARPENTER_RETURN_HOME);
        }
        break;

    //case FIGURE_ACTION_14_CARPENTER_WORK_GROUND:
    //{
    //    int progress = map_monuments_get_progress(tile());
    //    if (progress < 200) {
    //        map_grid_area_foreach(tile().shifted(-1, -1), tile(), [&] (tile2i t) {
    //            map_monuments_set_progress(t, progress + 1);
    //        });
    //    } else {
    //        advance_action(FIGURE_ACTION_17_CARPENTER_LOOKING_FOR_WORK_TILE);
    //    }
    //}
    //break;

    case ACTION_16_CARPENTER_RETURN_HOME:
        if (do_gotobuilding(home(), true, TERRAIN_USAGE_PREFER_ROADS, -1, ACTION_18_CARPENTER_RANDOM_TILE)) {
            poof();
        }
        break;
    }
}

void figure_carpenter::on_destroy() {
    figure_impl::on_destroy();

    // If the stonemason is working on a monument/statue, we need to remove it from the workers list.
    building *b_dest = building_get(runtime_data().destination_bid);
    if (b_dest) {
        b_dest->remove_figure_by_id(base.id);
    }
}

void figure_carpenter::update_animation() {
    figure_impl::update_animation();

    switch (action_state()) {
    case ACTION_14_CARPENTER_WORK_GROUND:
        image_set_animation(animkeys().work_ground);
        break;

    case ACTION_15_CARPENTER_WORK_VERT:
        image_set_animation(animkeys().work_wall);
        break;

    case ACTION_16_CARPENTER_RETURN_HOME:
        image_set_animation(animkeys().walk);
        break;
    }
}

sound_key figure_carpenter::phrase_key() const {
    switch (action_state()) {
    case ACTION_10_CARPENTER_CREATED:
    case ACTION_30_CARPENTER_CREATED_ROAMING:
        return "carpenter_work_my_tools_need_for_monument";
        
    case ACTION_11_CARPENTER_GOING:
    case ACTION_31_CARPENTER_GOING_TO_GARDEN:
        return "carpenter_work_my_tools_need_for_monument";
        
    case ACTION_17_CARPENTER_LOOKING_FOR_WORK_TILE:
        return "carpenter_work_my_tools_need_for_monument";
        
    case ACTION_14_CARPENTER_WORK_GROUND:
    case ACTION_15_CARPENTER_WORK_VERT:
        return "carpenter_this_monument_will_be_short";
        
    case ACTION_16_CARPENTER_RETURN_HOME:
        return "carpenter_this_monument_will_be_short";
    }

    return "carpenter_work_my_tools_need_for_monument";
}