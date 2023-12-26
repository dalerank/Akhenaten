#include "figure/figure.h"

#include "building/monument_mastaba.h"

void figure::bricklayer_action() {
    use_cross_country = false;
    max_roam_length = 384;
    building* bhome = home();
    building* b_dest = destination();
    e_terrain_usage terrain_usage = TERRAIN_USAGE_ROADS;
    bool stop_at_road = true;
    if (!bhome->is_valid() || !b_dest->is_valid()) {
        poof();
        return;
    }

    if (b_dest->is_monument()) {
        terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
        stop_at_road = false;
    } else {
        terrain_usage = TERRAIN_USAGE_ROADS;
    }

    switch (action_state) {
    case 9:
        break;

    case FIGURE_ACTION_10_BRIRKLAYER_GOING:
        if (do_gotobuilding(destination(), stop_at_road, terrain_usage)) {
            if (b_dest->type == BUILDING_SMALL_MASTABA || b_dest->type == BUILDING_SMALL_MASTABA_SEC) {
                tile2i wait_tile = building_small_mastaba_bricks_waiting_tile(b_dest);
                if (wait_tile == tile2i{-1, -1}) {
                    poof();
                    return;
                }

                map_grid_area_foreach(b_dest->tile, wait_tile, [] (tile2i tile) {
                    if (!map_monuments_get_progress(tile)) {
                        map_monuments_set_progress(tile, 1);
                    }
                });
                
                destination_tile = wait_tile;
                advance_action(FIGURE_ACTION_11_BRICKLAYER_GOING_TO_PLACE);
            }
        }
        break;

    case FIGURE_ACTION_11_BRICKLAYER_GOING_TO_PLACE:
        if (do_goto(destination_tile, false, TERRAIN_USAGE_ANY)) {
            wait_ticks = 0;
            direction = 0;
            advance_action(FIGURE_ACTION_12_BRICKLAYER_WAITING_RESOURCES);
        }
        break;

    case FIGURE_ACTION_12_BRICKLAYER_WAITING_RESOURCES:
        int progress = map_monuments_get_progress(tile.grid_offset());
        if (progress < 200) {
            map_monuments_set_progress(tile.grid_offset(), progress + 1);
        } else {
            poof();
        }
        break;
    }

    switch (action_state) {
    case FIGURE_ACTION_12_BRICKLAYER_WAITING_RESOURCES:
        return image_set_animation(IMG_BRICKLAYER_IDLE, 0, 12);
    }
}