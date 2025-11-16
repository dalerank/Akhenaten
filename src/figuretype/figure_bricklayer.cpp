#include "figure_bricklayer.h"

#include "building/monument_mastaba.h"
#include "building/building_statue.h"
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

    case ACTION_20_BRICKLAYER_DESTROY:
        poof();
        break;

    case ACTION_30_BRICKLAYER_CREATED_ROAMING:
        base.destination_tile = destination()->access_tile();
        advance_action(ACTION_31_BRICKLAYER_GOING_TO_STATUE);
        break;

    case ACTION_10_BRICKLAYER_CREATED:
        base.destination_tile = destination()->access_tile();
        advance_action(ACTION_11_BRICKLAYER_GOING);
        break;

    case ACTION_31_BRICKLAYER_GOING_TO_STATUE:
        if (do_goto(base.destination_tile, terrain_usage, ACTION_14_BRICKLAYER_WORK_STATUE, ACTION_16_BRICKLAYER_RETURN_HOME)) {
            base.wait_ticks = 0;
            advance_action(ACTION_14_BRICKLAYER_WORK_STATUE);
        }
        break;

    case ACTION_11_BRICKLAYER_GOING:
        if (do_goto(base.destination_tile, terrain_usage, ACTION_15_BRICKLAYER_LOOKING_FOR_IDLE_TILE, ACTION_16_BRICKLAYER_RETURN_HOME)) {
            advance_action(ACTION_15_BRICKLAYER_LOOKING_FOR_IDLE_TILE);
        }
        break;

    case ACTION_15_BRICKLAYER_LOOKING_FOR_IDLE_TILE:
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
            advance_action(ACTION_12_BRICKLAYER_GOING_TO_PLACE);
        }
        break;

    case ACTION_12_BRICKLAYER_GOING_TO_PLACE:
        base.roam_wander_freely = false;
        if (do_goto(base.destination_tile, false, TERRAIN_USAGE_ANY)) {
            base.wait_ticks = 0;
            base.direction = 0;
            map_grid_area_foreach(tile().shifted(-1, -1), tile(), [&] (tile2i t) { 
                map_monuments_set_progress(t, 1); 
            });
            advance_action(ACTION_13_BRICKLAYER_WAITING_RESOURCES);
        }
        break;

    case ACTION_13_BRICKLAYER_WAITING_RESOURCES:
        base.wait_ticks++;
        if (base.wait_ticks > 30) {
            auto &d = runtime_data();
            base.wait_ticks = 0;
            d.idle_wait_count++;
            bool area_ready = true;
            map_grid_area_foreach(tile().shifted(-1, -1), tile(), [&] (tile2i t) { area_ready &= (map_monuments_get_progress(t) == 2); });
            if (area_ready) {
                advance_action(ACTION_14_BRICKLAYER_LAY_BRICKS);
            } else if (d.idle_wait_count > 20) {
                base.destination_tile = building_monument_access_point(destination());
                base.destination_tile.shift(1, 1);
                advance_action(ACTION_17_BRICKLAYER_EXIT_FROM_MONUMENT);
            }
        }
        break;

    case ACTION_14_BRICKLAYER_LAY_BRICKS: {
            int progress = map_monuments_get_progress(tile());
            if (progress < 200) {
                map_grid_area_foreach(tile().shifted(-1, -1), tile(), [&] (tile2i t) {
                    map_monuments_set_progress(t, progress + 1);
                });
            } else {
                advance_action(ACTION_15_BRICKLAYER_LOOKING_FOR_IDLE_TILE);
            }
        }
        break;

    case ACTION_17_BRICKLAYER_EXIT_FROM_MONUMENT:
        base.roam_wander_freely = false;
        if (do_goto(base.destination_tile, false, TERRAIN_USAGE_ANY)) {
            base.wait_ticks = 0;
            advance_action(ACTION_16_BRICKLAYER_RETURN_HOME);
        }
        break;

    case ACTION_14_BRICKLAYER_WORK_STATUE:
        base.wait_ticks++;
        if (base.wait_ticks > simulation_time_t::ticks_in_day * 2) {
            auto statue = smart_cast<building_statue>(building_get(runtime_data().destination_bid));
            if (statue) {
                statue->set_service(100);
            }
            advance_action(ACTION_16_BRICKLAYER_RETURN_HOME);
        }
        break;

    case ACTION_16_BRICKLAYER_RETURN_HOME:
        if (do_gotobuilding(home(), true, TERRAIN_USAGE_PREFER_ROADS, -1, ACTION_18_BRICKLAYER_RANDOM_TILE)) {
            poof();
        }
        break;
    }
}

void figure_bricklayer::update_animation() {
    figure_impl::update_animation();

    switch (action_state()) {
    case ACTION_13_BRICKLAYER_WAITING_RESOURCES:
        image_set_animation(animkeys().idle);
        break;

    case ACTION_14_BRICKLAYER_LAY_BRICKS:
    case ACTION_14_BRICKLAYER_WORK_STATUE:
        image_set_animation(animkeys().work);
        break;

    case ACTION_16_BRICKLAYER_RETURN_HOME:
        image_set_animation(animkeys().walk);
        break;
    }
}

sound_key figure_bricklayer::phrase_key() const {
    switch (action_state()) {
    case ACTION_10_BRICKLAYER_CREATED:
    case ACTION_30_BRICKLAYER_CREATED_ROAMING:
        return "brick_bricklaying_time_at_monument";
        
    case ACTION_11_BRICKLAYER_GOING:
    case ACTION_12_BRICKLAYER_GOING_TO_PLACE:
    case ACTION_31_BRICKLAYER_GOING_TO_STATUE:
        return "brick_bricklaying_time_at_monument";
        
    case ACTION_13_BRICKLAYER_WAITING_RESOURCES:
        return "brick_bricklaying_time_at_monument";
        
    case ACTION_14_BRICKLAYER_LAY_BRICKS:
    case ACTION_14_BRICKLAYER_WORK_STATUE:
    case ACTION_15_BRICKLAYER_LOOKING_FOR_IDLE_TILE:
        return "brick_monument_will_be_strong";
        
    case ACTION_16_BRICKLAYER_RETURN_HOME:
    case ACTION_17_BRICKLAYER_EXIT_FROM_MONUMENT:
        return "brick_monument_will_be_strong";
    }

    return "brick_bricklaying_time_at_monument";
}

void figure_bricklayer::on_destroy() {
    figure_impl::on_destroy();

    // If the bricklayer is working on a monument/statue, we need to remove it from the workers list.
    building *b_dest = building_get(runtime_data().destination_bid);
    if (b_dest) {
        b_dest->remove_figure_by_id(base.id);
    }
}