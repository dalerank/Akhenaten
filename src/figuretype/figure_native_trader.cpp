#include "figure_native_trader.h"

#include "figure/trader.h"
#include "figure/figure.h"

#include "figure/image.h"

#include "graphics/image_groups.h"
#include "graphics/image.h"

#include "js/js_game.h"

struct native_trader_model : public figures::model_t<FIGURE_NATIVE_TRADER, figure_native_trader> {};
native_trader_model native_trader_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_native_trader);
void config_load_figure_native_trader() {
    g_config_arch.r_section("figure_native_trader", [] (archive arch) {
        native_trader_m.anim.load(arch);
        native_trader_m.sounds.load(arch);
    });
}

void figure_native_trader::figure_action() {
    //    is_ghost = false;
    //    terrain_usage = TERRAIN_USAGE_ANY;
    //    figure_image_increase_offset(12);
    //    cart_image_id = 0;
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
        wait_ticks++;
        if (wait_ticks > 10) {
            wait_ticks = 0;
            tile2i tile;
            int building_id = get_closest_storageyard(tile, 0, -1, tile);
            if (building_id) {
                advance_action(FIGURE_ACTION_160_NATIVE_TRADER_GOING_TO_WAREHOUSE);
                set_destination(building_id);
                destination_tile = tile;
            } else {
                poof();
            }
        }
        base.anim_frame = 0;
        break;

    case FIGURE_ACTION_163_NATIVE_TRADER_AT_WAREHOUSE:
        wait_ticks++;
        if (wait_ticks > 10) {
            wait_ticks = 0;
            if (can_buy(destination(), 0)) {
                e_resource resource = trader_get_buy_resource(destination(), 0, 100);
                trader_record_bought_resource(base.trader_id, resource);
                base.trader_amount_bought += 3;
            } else {
                tile2i tile;
                int building_id = get_closest_storageyard(tile, 0, -1, tile);
                if (building_id) {
                    advance_action(FIGURE_ACTION_160_NATIVE_TRADER_GOING_TO_WAREHOUSE);
                    set_destination(building_id);
                    destination_tile = tile;
                } else {
                    advance_action(FIGURE_ACTION_161_NATIVE_TRADER_RETURNING);
                    destination_tile = base.source_tile;
                }
            }
        }
        base.anim_frame = 0;
        break;
    }
    int dir = figure_image_normalize_direction(direction() < 8 ? direction() : base.previous_tile_direction);

    if (action_state() == FIGURE_ACTION_149_CORPSE) {
        base.sprite_image_id = image_id_from_group(PACK_SPR_MAIN, 44);
        base.cart_image_id = 0;
    } else {
        base.sprite_image_id = image_id_from_group(PACK_SPR_MAIN, 43) + dir + 8 * base.anim_frame;
    }

    base.cart_image_id = image_id_from_group(GROUP_FIGURE_IMMIGRANT_CART) + 8 + 8 * base.resource_id; // BUGFIX should be within else statement?
    if (base.cart_image_id) {
        base.cart_image_id += dir;
        base.figure_image_set_cart_offset(dir);
    }
}

void figure_native_trader::figure_draw(painter &ctx, vec2i pixel, int highlight, vec2i *coord_out) {
    base.draw_figure_with_cart(ctx, pixel, highlight, coord_out);
}
