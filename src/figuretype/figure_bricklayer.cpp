#include "figure_bricklayer.h"

#include "building/monument_mastaba.h"
#include "grid/terrain.h"
#include "grid/grid.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_bricklayer);

void figure_bricklayer::figure_action() {
    base.use_cross_country = false;
    base.max_roam_length = 384;
    building* bhome = home();
    building* b_dest = destination();
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

    case FIGURE_ACTION_20_BRIRKLAYER_DESTROY:
        poof();
        break;

    case FIGURE_ACTION_10_BRIRKLAYER_CREATED:
        base.destination_tile = destination()->access_tile();
        advance_action(FIGURE_ACTION_11_BRIRKLAYER_GOING);
        break;

    case FIGURE_ACTION_11_BRIRKLAYER_GOING:
        if (do_goto(base.destination_tile, terrain_usage, -1, FIGURE_ACTION_20_BRIRKLAYER_DESTROY)) {
            advance_action(FIGURE_ACTION_15_BRICKLAYER_LOOKING_FOR_IDLE_TILE);
        }
        break;

    case FIGURE_ACTION_15_BRICKLAYER_LOOKING_FOR_IDLE_TILE:
        if (smart_cast<building_mastaba>(b_dest)) {
            tile2i wait_tile = building_small_mastaba_bricks_waiting_tile(b_dest);
            if (!wait_tile.valid()) {
                poof();
                return;
            }

            map_grid_area_foreach(wait_tile.shifted(-1, -1), wait_tile, [] (tile2i t) {
                if (!map_monuments_get_progress(t)) {
                    map_monuments_set_progress(t, 1);
                }
            });

            base.destination_tile = wait_tile;
            advance_action(FIGURE_ACTION_12_BRICKLAYER_GOING_TO_PLACE);
        }
        break;

    case FIGURE_ACTION_12_BRICKLAYER_GOING_TO_PLACE:
        base.roam_wander_freely = false;
        if (do_goto(base.destination_tile, false, TERRAIN_USAGE_ANY)) {
            base.wait_ticks = 0;
            base.direction = 0;
            map_grid_area_foreach(tile().shifted(-1, -1), tile(), [&] (tile2i t) { 
                map_monuments_set_progress(t, 1); 
            });
            advance_action(FIGURE_ACTION_13_BRICKLAYER_WAITING_RESOURCES);
        }
        break;

    case FIGURE_ACTION_13_BRICKLAYER_WAITING_RESOURCES:
        base.wait_ticks++;
        if (base.wait_ticks > 30) {
            auto &d = runtime_data();
            base.wait_ticks = 0;
            d.idle_wait_count++;
            bool area_ready = true;
            map_grid_area_foreach(tile().shifted(-1, -1), tile(), [&] (tile2i t) { area_ready &= (map_monuments_get_progress(t) == 2); });
            if (area_ready) {
                advance_action(FIGURE_ACTION_14_BRICKLAYER_LAY_BRICKS);
            } else if (d.idle_wait_count > 20) {
                base.destination_tile = building_monument_access_point(destination());
                base.destination_tile.shift(1, 1);
                advance_action(FIGURE_ACTION_17_BRICKLAYER_EXIT_FROM_MONUMENT);
            }
        }
        break;

    case FIGURE_ACTION_14_BRICKLAYER_LAY_BRICKS: {
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

    case FIGURE_ACTION_17_BRICKLAYER_EXIT_FROM_MONUMENT:
        base.roam_wander_freely = false;
        if (do_goto(base.destination_tile, false, TERRAIN_USAGE_ANY)) {
            base.wait_ticks = 0;
            advance_action(FIGURE_ACTION_16_BRICKLAYER_RETURN_HOME);
        }
        break;

    case FIGURE_ACTION_16_BRICKLAYER_RETURN_HOME:
        if (do_gotobuilding(home(), true, TERRAIN_USAGE_PREFER_ROADS, -1, FIGURE_ACTION_18_BRICKLAYER_RANDOM_TILE)) {
            poof();
        }
        break;
    }
}

void figure_bricklayer::update_animation() {
    figure_impl::update_animation();

    switch (action_state()) {
    case FIGURE_ACTION_13_BRICKLAYER_WAITING_RESOURCES:
        image_set_animation(animkeys().idle);
        break;

    case FIGURE_ACTION_14_BRICKLAYER_LAY_BRICKS:
        image_set_animation(animkeys().work);
        break;

    case FIGURE_ACTION_16_BRICKLAYER_RETURN_HOME:
        image_set_animation(animkeys().walk);
        break;
    }
}
