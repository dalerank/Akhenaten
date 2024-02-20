#include "figure_native_trader.h"

#include "figure/trader.h"
#include "figure/figure.h"

#include "figuretype/trader_caravan.h"
#include "figure/image.h"

#include "graphics/image_groups.h"
#include "graphics/image.h"

void figure::native_trader_action() {
    //    is_ghost = false;
    //    terrain_usage = TERRAIN_USAGE_ANY;
    //    figure_image_increase_offset(12);
    //    cart_image_id = 0;
    switch (action_state) {
    case FIGURE_ACTION_160_NATIVE_TRADER_GOING_TO_WAREHOUSE:
    move_ticks(1);
    if (direction == DIR_FIGURE_NONE)
        action_state = FIGURE_ACTION_163_NATIVE_TRADER_AT_WAREHOUSE;
    else if (direction == DIR_FIGURE_REROUTE)
        route_remove();
    else if (direction == DIR_FIGURE_CAN_NOT_REACH) {
        poof();
        //                is_ghost = true;
    }
    if (destination()->state != BUILDING_STATE_VALID)
        poof();

    break;
    case ACTION_11_RETURNING_EMPTY:
    case FIGURE_ACTION_161_NATIVE_TRADER_RETURNING:
    move_ticks(1);
    if (direction == DIR_FIGURE_NONE || direction == DIR_FIGURE_CAN_NOT_REACH)
        poof();
    else if (direction == DIR_FIGURE_REROUTE)
        route_remove();

    break;
    case FIGURE_ACTION_162_NATIVE_TRADER_CREATED:
    //            is_ghost = true;
    wait_ticks++;
    if (wait_ticks > 10) {
        wait_ticks = 0;
        tile2i tile;
        int building_id = get_closest_storageyard(tile, 0, -1, tile);
        if (building_id) {
            action_state = FIGURE_ACTION_160_NATIVE_TRADER_GOING_TO_WAREHOUSE;
            set_destination(building_id);
            destination_tile = tile;
        } else {
            poof();
        }
    }
    anim_frame = 0;
    break;
    case FIGURE_ACTION_163_NATIVE_TRADER_AT_WAREHOUSE:
    wait_ticks++;
    if (wait_ticks > 10) {
        wait_ticks = 0;
        if (figure_trade_caravan_can_buy(this, destination(), 0)) {
            e_resource resource = trader_get_buy_resource(destination(), 0, 100);
            trader_record_bought_resource(trader_id, resource);
            trader_amount_bought += 3;
        } else {
            tile2i tile;
            int building_id = get_closest_storageyard(tile, 0, -1, tile);
            if (building_id) {
                action_state = FIGURE_ACTION_160_NATIVE_TRADER_GOING_TO_WAREHOUSE;
                set_destination(building_id);
                destination_tile = tile;
            } else {
                action_state = FIGURE_ACTION_161_NATIVE_TRADER_RETURNING;
                destination_tile = source_tile;
            }
        }
    }
    anim_frame = 0;
    break;
    }
    int dir = figure_image_normalize_direction(direction < 8 ? direction : previous_tile_direction);

    if (action_state == FIGURE_ACTION_149_CORPSE) {
        sprite_image_id = image_group(IMG_CARTPUSHER_DEATH);
        cart_image_id = 0;
    } else {
        sprite_image_id = image_group(IMG_CARTPUSHER) + dir + 8 * anim_frame;
    }

    cart_image_id = image_id_from_group(GROUP_FIGURE_IMMIGRANT_CART) + 8 + 8 * resource_id; // BUGFIX should be within else statement?
    if (cart_image_id) {
        cart_image_id += dir;
        figure_image_set_cart_offset(dir);
    }
}