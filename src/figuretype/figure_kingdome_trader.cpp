#include "figure_kingdome_trader.h"

#include "building/building.h"
#include "building/building_dock.h"
#include "building/building_storage_yard.h"
#include "building/building_storage_room.h"
#include "city/buildings.h"
#include "city/finance.h"
#include "city/city.h"
#include "city/message.h"
#include "city/city_resource.h"
#include "city/trade.h"
#include "core/calc.h"
#include "empire/empire.h"
#include "empire/empire_map.h"
#include "empire/trade_prices.h"
#include "empire/trade_route.h"
#include "figure/combat.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "figure/trader.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/image_desc.h"
#include "graphics/image_groups.h"
#include "grid/figure.h"
#include "grid/road_access.h"
#include "scenario/map.h"
#include "game/game.h"

#include "js/js_game.h"

figure_trade_caravan::static_params trade_caravan_m;

void figure_trade_caravan::static_params::load(archive arch)  {
    int wait_ticks_after_create = arch.r_int("wait_ticks_after_create");
};

int figure::trader_total_bought() {
    return trader_amount_bought;
}

int figure::trader_total_sold() {
    return resource_amount_full;
}

int figure_trade_caravan::create(tile2i tile, const empire_city& city) {
    figure* caravan = figure_create(FIGURE_TRADE_CARAVAN, tile, DIR_0_TOP_RIGHT);
    caravan->empire_city_id = city.name_id;
    caravan->action_state = FIGURE_ACTION_100_TRADE_CARAVAN_CREATED;
    caravan->wait_ticks = trade_caravan_m.wait_ticks_after_create;
    // donkey 1
    figure* donkey1 = figure_create(FIGURE_TRADE_CARAVAN_DONKEY, tile, DIR_0_TOP_RIGHT);
    donkey1->action_state = FIGURE_ACTION_100_TRADE_CARAVAN_CREATED;
    donkey1->leading_figure_id = caravan->id;
    // donkey 2
    figure* donkey2 = figure_create(FIGURE_TRADE_CARAVAN_DONKEY, tile, DIR_0_TOP_RIGHT);
    donkey2->action_state = FIGURE_ACTION_100_TRADE_CARAVAN_CREATED;
    donkey2->leading_figure_id = donkey1->id;
    return caravan->id;
}

void figure_trade_caravan::go_to_next_storageyard(tile2i src_tile, int distance_to_entry) {
    tile2i dst;
    int warehouse_id = get_closest_storageyard(src_tile, base.empire_city_id, distance_to_entry, dst);
    if (warehouse_id && warehouse_id != base.destinationID()) {
        set_destination(warehouse_id);
        base.action_state = FIGURE_ACTION_101_TRADE_CARAVAN_ARRIVING;
        base.destination_tile = dst;
    } else {
        base.state = FIGURE_STATE_ALIVE;
        base.destination_tile = map_closest_road_within_radius(g_city.map.exit_point, 1, 2);
        base.direction = DIR_0_TOP_RIGHT;
        advance_action(ACTION_16_EMIGRANT_RANDOM);
        base.action_state = FIGURE_ACTION_103_TRADE_CARAVAN_LEAVING;
    }
}

void figure_trade_caravan::on_create() {
    base.trader_id = trader_create();
}

void figure_trade_caravan::figure_action() {
    int last_action_state = action_state();
    switch (action_state()) {
    default:
    case FIGURE_ACTION_100_TRADE_CARAVAN_CREATED:
        base.wait_ticks++;
        if (base.wait_ticks > 20) {
            base.wait_ticks = 0;
            tile2i base_tile;
            int trade_center_id = city_buildings_get_trade_center();
            if (trade_center_id) {
                building* trade_center = building_get(trade_center_id);
                base_tile = trade_center->tile;
            } else {
                base_tile = tile();
            }
            go_to_next_storageyard(base_tile, 0);
        }
        base.anim.frame = 0;
        break;

    case FIGURE_ACTION_101_TRADE_CARAVAN_ARRIVING:
        do_gotobuilding(destination(), true, TERRAIN_USAGE_PREFER_ROADS, FIGURE_ACTION_102_TRADE_CARAVAN_TRADING, FIGURE_ACTION_100_TRADE_CARAVAN_CREATED);
        if (direction() == DIR_FIGURE_CAN_NOT_REACH || direction() == DIR_FIGURE_REROUTE) {
            int i = 0; // break
        }
        break;

    case FIGURE_ACTION_102_TRADE_CARAVAN_TRADING:
        base.wait_ticks++;
        if (base.wait_ticks > 10) {
            base.wait_ticks = 0;
            int move_on = 0;
            if (can_buy(destination(), base.empire_city_id)) {
                e_resource resource = trader_get_buy_resource(destination(), base.empire_city_id, UNITS_PER_LOAD);
                if (resource) {
                    auto &trade_route = g_empire.city(base.empire_city_id)->get_route();
                    trade_route.increase_traded(resource, UNITS_PER_LOAD);
                    trader_record_bought_resource(base.trader_id, resource);
                    trader_buy(UNITS_PER_LOAD);
                } else {
                    move_on++;
                }
            } else {
                move_on++;
            }

            if (move_on > 0 && can_sell(destination(), base.empire_city_id)) {
                e_resource resource = trader_get_sell_resource(destination(), base.empire_city_id);
                if (resource) {
                    auto &trade_route = g_empire.city(base.empire_city_id)->get_route();
                    trade_route.increase_traded(resource, UNITS_PER_LOAD);
                    trader_record_sold_resource(base.trader_id, resource);
                    trader_sell(UNITS_PER_LOAD);
                } else {
                    move_on++;
                }
            } else {
                move_on++;
            }

            if (move_on == 2) {
                go_to_next_storageyard(tile(), -1);
            }
        }
        base.anim.frame = 0;
        break;

    case FIGURE_ACTION_104_TRADE_CARAVAN_RECALC_LEAVING:
        if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            base.direction = DIR_0_TOP_RIGHT;
            base.destination_tile = g_city.map.closest_exit_tile_within_radius();
            advance_action(FIGURE_ACTION_103_TRADE_CARAVAN_LEAVING);
        }
        break;

    case FIGURE_ACTION_103_TRADE_CARAVAN_LEAVING:
        if (do_goto(base.destination_tile, TERRAIN_USAGE_PREFER_ROADS, -1, FIGURE_ACTION_104_TRADE_CARAVAN_RECALC_LEAVING)) {
            poof();
        }
        break;
    }
}

void figure_trade_caravan::before_poof() {
    ; // nothing
}

sound_key figure_trade_caravan::phrase_key() const {
    //    if (++f->phrase_sequence_exact >= 2)
    //        f->phrase_sequence_exact = 0;
    //
    //    if (f->action_state == FIGURE_ACTION_103_TRADE_CARAVAN_LEAVING) {
    //        if (!trader_has_traded(f->trader_id))
    //            return 7; // no trade
    //
    //    } else if (f->action_state == FIGURE_ACTION_102_TRADE_CARAVAN_TRADING) {
    //        if (figure_trade_caravan_can_buy(f, f->destination_building_id, f->empire_city_id))
    //            return 11; // buying goods
    //        else if (figure_trade_caravan_can_sell(f, f->destination_building_id, f->empire_city_id))
    //            return 10; // selling goods
    //
    //    }
    //    return 8 + f->phrase_sequence_exact;
    return 0;
}

bool figure_trade_caravan::window_info_background(object_info &c) {
    painter ctx = game.painter();
    figure* f = &base;
    const empire_city* city = g_empire.city(f->empire_city_id);
    int width = lang_text_draw(64, f->type, c.offset.x + 40, c.offset.y + 110, FONT_NORMAL_BLACK_ON_DARK);
    lang_text_draw(21, city->name_id, c.offset.x + 40 + width, c.offset.y + 110, FONT_NORMAL_BLACK_ON_DARK);

    width = lang_text_draw(129, 1, c.offset.x + 40, c.offset.y + 132, FONT_NORMAL_BLACK_ON_DARK);
    lang_text_draw_amount(8, 10, 800, c.offset.x + 40 + width, c.offset.y + 132, FONT_NORMAL_BLACK_ON_DARK);

    int trader_id = f->trader_id;
   
    int text_id;
    switch (f->action_state) {
    case FIGURE_ACTION_101_TRADE_CARAVAN_ARRIVING: text_id = 12; break;
    case FIGURE_ACTION_102_TRADE_CARAVAN_TRADING: text_id = 10; break;
    case FIGURE_ACTION_103_TRADE_CARAVAN_LEAVING:
        if (trader_has_traded(trader_id))
            text_id = 11;
        else
            text_id = 13;
        break;
    default:
        text_id = 11;
    break;
    }
    lang_text_draw(129, text_id, c.offset.x + 40, c.offset.y + 154, FONT_NORMAL_BLACK_ON_DARK);

    if (trader_has_traded(trader_id)) {
        // bought
        int y_base = c.offset.y + 180;
        width = lang_text_draw(129, 4, c.offset.x + 40, y_base, FONT_NORMAL_BLACK_ON_DARK);
        for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; ++r) {
            if (trader_bought_resources(trader_id, r)) {
                width += text_draw_number(trader_bought_resources(trader_id, r), '@'," ", c.offset.x + 40 + width, y_base, FONT_NORMAL_BLACK_ON_DARK);
                int image_id = image_id_resource_icon(r) + resource_image_offset(r, RESOURCE_IMAGE_ICON);
                ImageDraw::img_generic(ctx, image_id, vec2i{c.offset.x + 40 + width, y_base - 3});
                width += 25;
            }
        }
        // sold
        y_base = c.offset.y + 210;
        width = lang_text_draw(129, 5, c.offset.x + 40, y_base, FONT_NORMAL_BLACK_ON_DARK);
        for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; ++r) {
            if (trader_sold_resources(trader_id, r)) {
                width += text_draw_number(trader_sold_resources(trader_id, r), '@', " ", c.offset.x + 40 + width, y_base, FONT_NORMAL_BLACK_ON_DARK);
                int image_id = image_id_resource_icon(r) + resource_image_offset(r, RESOURCE_IMAGE_ICON);
                ImageDraw::img_generic(ctx, image_id, vec2i{c.offset.x + 40 + width, y_base - 3});
                width += 25;
            }
        }
    } else { // nothing sold/bought (yet)
             // buying
        int y_base = c.offset.y + 180;
        width = lang_text_draw(129, 2, c.offset.x + 40, y_base, FONT_NORMAL_BLACK_ON_DARK);
        for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; ++r) {
            if (city->buys_resource[r]) {
                int image_id = image_id_resource_icon(r) + resource_image_offset(r, RESOURCE_IMAGE_ICON);
                ImageDraw::img_generic(ctx, image_id, vec2i{c.offset.x + 40 + width, y_base - 3});
                width += 25;
            }
        }
        // selling
        y_base = c.offset.y + 210;
        width = lang_text_draw(129, 3, c.offset.x + 40, y_base, FONT_NORMAL_BLACK_ON_DARK);
        for (int r = RESOURCE_MIN; r < RESOURCES_MAX; r++) {
            if (city->sells_resource[r]) {
                int image_id = image_id_resource_icon(r) + resource_image_offset(r, RESOURCE_IMAGE_ICON);
                ImageDraw::img_generic(ctx, image_id, vec2i{c.offset.x + 40 + width, y_base - 3});
                width += 25;
            }
        }
    }

    return true;
}

const animations_t &figure_trade_caravan::anim() const {
    return trade_caravan_m.anim;
}

void figure_trade_caravan::update_animation() {
    int dir = figure_image_normalize_direction(direction() < 8 ? direction() : base.previous_tile_direction);
    base.sprite_image_id = trade_caravan_m.anim["walk"].first_img() + dir + 8 * base.anim.frame;
}
