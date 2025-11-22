#include "figure_stonemason.h"

#include "building/monument_mastaba.h"
#include "building/building_statue.h"
#include "grid/terrain.h"
#include "grid/grid.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_stonemason);

void figure_stonemason::figure_action() {
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

    case FIGURE_ACTION_30_MASON_CREATED_ROAMING:
        base.destination_tile = destination()->access_tile();
        advance_action(FIGURE_ACTION_31_MASON_GOING_TO_STATUE);
        break;

    case FIGURE_ACTION_10_MASON_CREATED:
        base.destination_tile = destination()->access_tile();
        advance_action(FIGURE_ACTION_11_MASON_GOING);
        break;

    case FIGURE_ACTION_20_MASON_DESTROY:
        poof();
        break;

    case FIGURE_ACTION_31_MASON_GOING_TO_STATUE:
        if (do_goto(base.destination_tile, terrain_usage, -1, FIGURE_ACTION_20_MASON_DESTROY)) {
            base.wait_ticks = 0;
            advance_action(FIGURE_ACTION_14_MASON_WORK_STATUE_GROUND);
        }
        break;

    case FIGURE_ACTION_11_MASON_GOING:
        if (do_goto(base.destination_tile, terrain_usage, -1, FIGURE_ACTION_20_MASON_DESTROY)) {
            advance_action(FIGURE_ACTION_17_MASON_LOOKING_FOR_WORK_TILE);
        }
        break;

    case FIGURE_ACTION_14_MASON_WORK_STATUE_GROUND:
    case FIGURE_ACTION_14_MASON_WORK_STATUE_WALL:
        base.wait_ticks++;
        if (base.wait_ticks > simulation_time_t::ticks_in_day * 2) {
            auto statue = smart_cast<building_statue>(building_get(runtime_data().destination_bid));
            if (statue) {
                statue->set_service(100);
            }
            advance_action(FIGURE_ACTION_16_MASON_RETURN_HOME);
        }
        break;

    case FIGURE_ACTION_14_MASON_WORK_GROUND: {
            int progress = map_monuments_get_progress(tile());
            if (progress < 200) {
                map_grid_area_foreach(tile().shifted(-1, -1), tile(), [&] (tile2i t) {
                    map_monuments_set_progress(t, progress + 1);
                });
            } else {
                advance_action(FIGURE_ACTION_17_MASON_LOOKING_FOR_WORK_TILE);
            }
        }
        break;

    case FIGURE_ACTION_16_MASON_RETURN_HOME:
        if (do_gotobuilding(home(), true, TERRAIN_USAGE_PREFER_ROADS, -1, FIGURE_ACTION_18_MASON_RANDOM_TILE)) {
            poof();
        }
        break;
    }
}

void figure_stonemason::on_destroy() {
    figure_impl::on_destroy();

    // If the stonemason is working on a monument/statue, we need to remove it from the workers list.
    building *b_dest = building_get(runtime_data().destination_bid);
    if (b_dest) {
        b_dest->remove_figure_by_id(base.id);
    }
}

sound_key figure_stonemason::phrase_key() const {
    switch (action_state()) {
    case FIGURE_ACTION_10_MASON_CREATED:
    case FIGURE_ACTION_30_MASON_CREATED_ROAMING:
        return "stonemason_ready";
        
    case FIGURE_ACTION_11_MASON_GOING:
    case FIGURE_ACTION_31_MASON_GOING_TO_STATUE:
        return "stonemason_going_to_work";
        
    case FIGURE_ACTION_14_MASON_WORK_GROUND:
    case FIGURE_ACTION_14_MASON_WORK_STATUE_GROUND:
        return "stonemason_working_ground";
        
    case FIGURE_ACTION_15_MASON_WORK_WALL:
    case FIGURE_ACTION_14_MASON_WORK_STATUE_WALL:
        return "stonemason_working_wall";
        
    case FIGURE_ACTION_16_MASON_RETURN_HOME:
        return "stonemason_work_complete";
        
    case FIGURE_ACTION_17_MASON_LOOKING_FOR_WORK_TILE:
    case FIGURE_ACTION_18_MASON_RANDOM_TILE:
        return "stonemason_looking_for_work";
    }

    return "stonemason_ready";
}

void figure_stonemason::update_animation() {
    figure_impl::update_animation();

    switch (action_state()) {
    case FIGURE_ACTION_14_MASON_WORK_GROUND:
    case FIGURE_ACTION_14_MASON_WORK_STATUE_GROUND:
        image_set_animation(animkeys().work_ground);
        break;

    case FIGURE_ACTION_15_MASON_WORK_WALL:
    case FIGURE_ACTION_14_MASON_WORK_STATUE_WALL:
        image_set_animation(animkeys().work_wall);
        break;

    case FIGURE_ACTION_16_MASON_RETURN_HOME:
        image_set_animation(animkeys().walk);
        break;
    }
}