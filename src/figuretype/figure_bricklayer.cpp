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
            advance_action(FIGURE_ACTION_14_BRICKLAYER_LOOKING_FOR_IDLE_TILE);
        }
        break;

    case FIGURE_ACTION_14_BRICKLAYER_LOOKING_FOR_IDLE_TILE:
        if (b_dest->type == BUILDING_SMALL_MASTABA || b_dest->type == BUILDING_SMALL_MASTABA_SEC) {
            tile2i wait_tile = building_small_mastaba_bricks_waiting_tile(b_dest);
            if (wait_tile == tile2i{-1, -1}) {
                poof();
                return;
            }

            map_grid_area_foreach(b_dest->tile, wait_tile, [] (tile2i t) {
                if (!map_monuments_get_progress(t)) {
                    map_monuments_set_progress(t, 1);
                }
            });

            destination_tile = wait_tile;
            advance_action(FIGURE_ACTION_11_BRICKLAYER_GOING_TO_PLACE);
        }
        break;

    case FIGURE_ACTION_11_BRICKLAYER_GOING_TO_PLACE:
        if (do_goto(destination_tile, false, TERRAIN_USAGE_ANY)) {
            wait_ticks = 0;
            direction = 0;
            map_grid_area_foreach(tile.shifted(-1, -1), tile, [&] (tile2i t) { map_monuments_set_progress(t.grid_offset(), 1); });
            advance_action(FIGURE_ACTION_12_BRICKLAYER_WAITING_RESOURCES);
        }
        break;

    case FIGURE_ACTION_12_BRICKLAYER_WAITING_RESOURCES:
        wait_ticks++;
        if (wait_ticks > 30) {
            wait_ticks = 0;
            bool area_ready = true;
            map_grid_area_foreach(tile.shifted(-1, -1), tile, [&] (tile2i t) { area_ready &= (map_monuments_get_progress(t) == 2); });
            if (area_ready) {
                advance_action(FIGURE_ACTION_13_BRICKLAYER_LAY_BRICKS);
            }
        }
        break;

    case FIGURE_ACTION_13_BRICKLAYER_LAY_BRICKS:
        int progress = map_monuments_get_progress(tile.grid_offset());
        if (progress < 200) {
            map_grid_area_foreach(tile.shifted(-1, -1), tile, [&] (tile2i t) { map_monuments_set_progress(t.grid_offset(), progress + 1); });
        } else {
            advance_action(FIGURE_ACTION_14_BRICKLAYER_LOOKING_FOR_IDLE_TILE);
        }
    }

    switch (action_state) {
    case FIGURE_ACTION_12_BRICKLAYER_WAITING_RESOURCES:
        image_set_animation(IMG_BRICKLAYER_IDLE, 0, 8);
        break;

    case FIGURE_ACTION_13_BRICKLAYER_LAY_BRICKS:
        image_set_animation(IMG_BRICKLAYER_WORK, 0, 12);
        break;
    }
}