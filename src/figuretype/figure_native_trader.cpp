#include "figure_native_trader.h"

#include "figure/trader.h"
#include "figure/figure.h"

#include "figure/image.h"

#include "widget/debug_console.h"
#include "graphics/image_groups.h"
#include "graphics/image.h"
#include "city/city.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_native_trader);

void figure_native_trader::figure_action() {
    //    is_ghost = false;
    //    terrain_usage = TERRAIN_USAGE_ANY;
    //    figure_image_increase_offset(12);
    //    cart_image_id = 0;
    base.use_cart = true;

    switch (action_state()) {
    case FIGURE_ACTION_160_NATIVE_TRADER_GOING_TO_WAREHOUSE:
        base.move_ticks(1);
        if (direction() == DIR_FIGURE_NONE)
            advance_action(FIGURE_ACTION_163_NATIVE_TRADER_AT_WAREHOUSE);
        else if (direction() == DIR_FIGURE_REROUTE)
            route_remove();
        else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
            //                is_ghost = true;
        }
        if (destination()->state != BUILDING_STATE_VALID)
            poof();
        break;

    case ACTION_11_RETURNING_EMPTY:
    case FIGURE_ACTION_161_NATIVE_TRADER_RETURNING:
        base.move_ticks(1);
        if (direction() == DIR_FIGURE_NONE || direction() == DIR_FIGURE_CAN_NOT_REACH)
            poof();
        else if (direction() == DIR_FIGURE_REROUTE)
            route_remove();
        break;

    case FIGURE_ACTION_162_NATIVE_TRADER_CREATED:
        //            is_ghost = true;
        base.wait_ticks++;
        if (base.wait_ticks > 10) {
            base.wait_ticks = 0;
            tile2i tile;
            int building_id = get_closest_storageyard(tile, { g_city.ourcity().name_id }, -1, tile);
            if (building_id) {
                advance_action(FIGURE_ACTION_160_NATIVE_TRADER_GOING_TO_WAREHOUSE);
                set_destination(building_id);
                base.destination_tile = tile;
            } else {
                poof();
            }
        }
        base.animctx.frame = 0;
        break;

    case FIGURE_ACTION_163_NATIVE_TRADER_AT_WAREHOUSE:
        base.wait_ticks++;
        if (base.wait_ticks > 10) {
            base.wait_ticks = 0;
            if (can_buy(destination(), { g_city.ourcity().name_id })) {
                e_resource resource = empire_trader().get_buy_resource(destination(), { g_city.ourcity().name_id }, 100);
                empire_trader().record_bought_resource(resource);
                runtime_data().amount_bought += 300;
            } else {
                tile2i tile;
                int building_id = get_closest_storageyard(tile, { g_city.ourcity().name_id }, -1, tile);
                if (building_id) {
                    advance_action(FIGURE_ACTION_160_NATIVE_TRADER_GOING_TO_WAREHOUSE);
                    set_destination(building_id);
                    base.destination_tile = tile;
                } else {
                    advance_action(FIGURE_ACTION_161_NATIVE_TRADER_RETURNING);
                    base.destination_tile = base.source_tile;
                }
            }
        }
        base.animctx.frame = 0;
        break;
    }

}

void figure_native_trader::update_animation() {
    figure_impl::update_animation();

    int dir = base.figure_image_normalize_direction(direction() < 8 ? direction() : base.previous_tile_direction);
    if (action_state() == FIGURE_ACTION_149_CORPSE) {
        base.main_image_id = image_id_from_group(PACK_SPR_MAIN, 44);
        base.cart_image_id = 0;
    } else {
        base.main_image_id = image_id_from_group(PACK_SPR_MAIN, 43) + dir + 8 * base.animctx.frame;
    }

    int cart_img = anim("cart").first_img();
    base.cart_image_id = cart_img + 8 + 8 * base.resource_id; // BUGFIX should be within else statement?
    if (base.cart_image_id) {
        base.cart_image_id += dir;
        base.figure_image_set_cart_offset(dir);
    }
}

void figure_native_trader::debug_show_properties() {
    game_debug_show_property("trader_id", 0);
}

empire_trader_handle figure_native_trader::empire_trader() { 
    return empire_trader_handle{}; 
}
