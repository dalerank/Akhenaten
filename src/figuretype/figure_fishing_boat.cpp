#include "figuretype/water.h"

#include "figure/route.h"
#include "figure/image.h"
#include "grid/water.h"
#include "city/message.h"
#include "core/calc.h"
#include "building/model.h"
#include "graphics/image.h"
#include "graphics/image_desc.h"

void figure::fishing_boat_action() {
    building* b = home();
    //    if (b->state != BUILDING_STATE_VALID)
    //        poof();

    if (action_state != FIGURE_ACTION_190_FISHING_BOAT_CREATED && b->data.industry.fishing_boat_id != id) {
        map_point tile;
        b = building_get(map_water_get_wharf_for_new_fishing_boat(this, &tile));
        if (b->id) {
            set_home(b->id);
            b->data.industry.fishing_boat_id = id;
            action_state = FIGURE_ACTION_193_FISHING_BOAT_GOING_TO_WHARF;
            destination_tile = tile;
            source_tile = tile;
            route_remove();
        } else {
            poof();
        }
    }

    allow_move_type = EMOVE_BOAT;
    //    figure_image_increase_offset(12);
    //    cart_image_id = 0;
    switch (action_state) {
    case FIGURE_ACTION_190_FISHING_BOAT_CREATED:
        wait_ticks++;
        if (wait_ticks >= 50) {
            wait_ticks = 0;
            map_point tile;
            int wharf_id = map_water_get_wharf_for_new_fishing_boat(this, &tile);
            if (wharf_id) {
                b->remove_figure(0); // remove from original building
                set_home(wharf_id);
                building_get(wharf_id)->data.industry.fishing_boat_id = id;
                action_state = FIGURE_ACTION_193_FISHING_BOAT_GOING_TO_WHARF;
                destination_tile = tile;
                //                    destination_tile.x() = tile.x();
                //                    destination_tile.y() = tile.y();
                source_tile = tile;
                //                    source_tile.x() = tile.x();
                //                    source_tile.y() = tile.y();
                route_remove();
            }
        }
        break;

    case FIGURE_ACTION_191_FISHING_BOAT_GOING_TO_FISH:
        move_ticks(1);
        height_adjusted_ticks = 0;
        if (direction == DIR_FIGURE_NONE) {
            map_point tile;
            if (map_water_find_alternative_fishing_boat_tile(this, &tile)) {
                route_remove();
                destination_tile = tile;
                //                    destination_tile.x() = tile.x();
                //                    destination_tile.y() = tile.y();
                direction = previous_tile_direction;
            } else {
                action_state = FIGURE_ACTION_192_FISHING_BOAT_FISHING;
                wait_ticks = 0;
            }
        } else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_CAN_NOT_REACH) {
            action_state = FIGURE_ACTION_194_FISHING_BOAT_AT_WHARF;
            destination_tile = source_tile;
            //                destination_tile.x() = source_tile.x();
            //                destination_tile.y() = source_tile.y();
        }
        break;

    case FIGURE_ACTION_192_FISHING_BOAT_FISHING:
        wait_ticks++;
        if (wait_ticks >= 200) {
            wait_ticks = 0;
            action_state = FIGURE_ACTION_195_FISHING_BOAT_RETURNING_WITH_FISH;
            destination_tile = source_tile;
            //                destination_tile.x() = source_tile.x();
            //                destination_tile.y() = source_tile.y();
            route_remove();
        }
        break;

    case FIGURE_ACTION_193_FISHING_BOAT_GOING_TO_WHARF:
        move_ticks(1);
        height_adjusted_ticks = 0;
        if (direction == DIR_FIGURE_NONE) {
            action_state = FIGURE_ACTION_194_FISHING_BOAT_AT_WHARF;
            wait_ticks = 0;
        } else if (direction == DIR_FIGURE_REROUTE)
            route_remove();
        else if (direction == DIR_FIGURE_CAN_NOT_REACH) {
            // cannot reach grounds
            city_message_post_with_message_delay(MESSAGE_CAT_FISHING_BLOCKED, 1, MESSAGE_FISHING_BOAT_BLOCKED, 12);
            poof();
        }
        break;

    case FIGURE_ACTION_194_FISHING_BOAT_AT_WHARF: {
        int pct_workers = calc_percentage<int>(b->num_workers, model_get_building(b->type)->laborers);
        int max_wait_ticks = 5 * (102 - pct_workers);
        if (b->data.industry.has_fish) {
            pct_workers = 0;
        }

        if (pct_workers > 0) {
            wait_ticks++;
            if (wait_ticks >= max_wait_ticks) {
                wait_ticks = 0;
                tile2i fish_tile;
                bool found = scenario_map_closest_fishing_point(tile, fish_tile);
                if (found && map_water_is_point_inside(fish_tile)) {
                    action_state = FIGURE_ACTION_191_FISHING_BOAT_GOING_TO_FISH;
                    destination_tile = fish_tile;
                    route_remove();
                }
            }
        }
    } break;

    case FIGURE_ACTION_195_FISHING_BOAT_RETURNING_WITH_FISH:
        move_ticks(1);
        height_adjusted_ticks = 0;
        if (direction == DIR_FIGURE_NONE) {
            action_state = FIGURE_ACTION_194_FISHING_BOAT_AT_WHARF;
            wait_ticks = 0;
            b->figure_spawn_delay = 1;
            b->data.industry.has_fish = true;
            b->stored_full_amount += 200;
        } else if (direction == DIR_FIGURE_REROUTE) {
            route_remove();
        } else if (direction == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }

        break;
    }
    int dir = figure_image_normalize_direction(direction < 8 ? direction : previous_tile_direction);

    if (action_state == FIGURE_ACTION_192_FISHING_BOAT_FISHING)
        sprite_image_id = image_id_from_group(IMG_FISHING_BOAT_WORK) + dir + 8;
    else {
        sprite_image_id = image_id_from_group(IMG_FISHING_BOAT) + dir + 8;
    }
}