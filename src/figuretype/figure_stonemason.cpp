#include "figure_stonemason.h"

#include "building/monument_mastaba.h"
#include "grid/terrain.h"
#include "grid/grid.h"

figure_stonemason::static_params stonemason_m;

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

    case FIGURE_ACTION_10_MASON_CREATED:
        base.destination_tile = destination()->access_tile();
        advance_action(FIGURE_ACTION_11_BRIRKLAYER_GOING);
        break;

    case FIGURE_ACTION_20_MASON_DESTROY:
        poof();
        break;

    case FIGURE_ACTION_11_MASON_GOING:
        if (do_goto(base.destination_tile, terrain_usage, -1, FIGURE_ACTION_20_BRIRKLAYER_DESTROY)) {
            advance_action(FIGURE_ACTION_15_BRICKLAYER_LOOKING_FOR_IDLE_TILE);
        }
        break;

    case FIGURE_ACTION_14_MASON_WORK_GROUND: {
            int progress = map_monuments_get_progress(tile());
            if (progress < 200) {
                map_grid_area_foreach(tile().shifted(-1, -1), tile(), [&] (tile2i t) {
                    map_monuments_set_progress(t, progress + 1);
                });
            } else {
                advance_action(FIGURE_ACTION_15_BRICKLAYER_LOOKING_FOR_IDLE_TILE);
            }
        }
        break;

    case FIGURE_ACTION_16_MASON_RETURN_HOME:
        if (do_gotobuilding(home(), true, TERRAIN_USAGE_PREFER_ROADS, -1, FIGURE_ACTION_18_BRICKLAYER_RANDOM_TILE)) {
            poof();
        }
        break;
    }
}

void figure_stonemason::update_animation() {
    figure_impl::update_animation();

    switch (action_state()) {
    case FIGURE_ACTION_14_MASON_WORK_GROUND:
        image_set_animation(animkeys().work_ground);
        break;

    case FIGURE_ACTION_14_MASON_WORK_WALL:
        image_set_animation(animkeys().work_wall);
        break;

    case FIGURE_ACTION_16_MASON_RETURN_HOME:
        image_set_animation(animkeys().walk);
        break;
    }
}