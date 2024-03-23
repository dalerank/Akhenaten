#include "figure_kingdome_trader.h"

#include "building/building.h"
#include "building/building_dock.h"
#include "building/storage.h"
#include "building/building_storage_yard.h"
#include "building/building_storage_room.h"
#include "city/buildings.h"
#include "city/finance.h"
#include "city/map.h"
#include "city/message.h"
#include "city/resource.h"
#include "city/trade.h"
#include "core/calc.h"
#include "empire/empire_city.h"
#include "empire/empire.h"
#include "empire/trade_prices.h"
#include "empire/trade_route.h"
#include "figure/combat.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "figure/trader.h"
#include "graphics/image.h"
#include "graphics/image_desc.h"
#include "graphics/image_groups.h"
#include "grid/figure.h"
#include "grid/road_access.h"
#include "scenario/map.h"

#include "js/js_game.h"

struct trade_caravan_model : public figures::model_t<FIGURE_TRADE_CARAVAN, figure_trade_caravan> {};
trade_caravan_model trade_caravan_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_trade_caravan);
void config_load_figure_trade_caravan() {
    g_config_arch.r_section("figure_trade_caravan", [] (archive arch) {
        trade_caravan_m.anim.load(arch);
        trade_caravan_m.sounds.load(arch);
    });
}

int figure::trader_total_bought() {
    return trader_amount_bought;
}

int figure::trader_total_sold() {
    return resource_amount_full;
}

int figure_create_trade_caravan(tile2i tile, int city_id) {
    figure* caravan = figure_create(FIGURE_TRADE_CARAVAN, tile, DIR_0_TOP_RIGHT);
    caravan->empire_city_id = city_id;
    caravan->action_state = FIGURE_ACTION_100_TRADE_CARAVAN_CREATED;
    caravan->wait_ticks = 10;
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
        destination_tile = dst;
    } else {
        tile2i exit = city_map_exit_point();
        tile2i road_tile;
        base.state = FIGURE_STATE_ALIVE;
        map_closest_road_within_radius(exit, 1, 2, road_tile);
        destination_tile = road_tile;
        base.direction = DIR_0_TOP_RIGHT;
        advance_action(ACTION_16_EMIGRANT_RANDOM);
        base.action_state = FIGURE_ACTION_103_TRADE_CARAVAN_LEAVING;
    }
}

void figure_trade_caravan::figure_action() {
    int last_action_state = action_state();
    switch (action_state()) {
    default:
    case FIGURE_ACTION_100_TRADE_CARAVAN_CREATED:
    case 8:
        wait_ticks++;
        if (wait_ticks > 20) {
            wait_ticks = 0;
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
        base.anim_frame = 0;
        break;

    case FIGURE_ACTION_101_TRADE_CARAVAN_ARRIVING:
    case 9:
        do_gotobuilding(destination(), true, TERRAIN_USAGE_PREFER_ROADS, FIGURE_ACTION_102_TRADE_CARAVAN_TRADING, FIGURE_ACTION_100_TRADE_CARAVAN_CREATED);
        if (direction() == DIR_FIGURE_CAN_NOT_REACH || direction() == DIR_FIGURE_REROUTE) {
            int i = 0; // break
        }
        break;

    case FIGURE_ACTION_102_TRADE_CARAVAN_TRADING:
    case 10:
        wait_ticks++;
        if (wait_ticks > 10) {
            wait_ticks = 0;
            int move_on = 0;
            constexpr int one_operation_amount = 100;
            if (can_buy(destination(), base.empire_city_id)) {
                e_resource resource = trader_get_buy_resource(destination(), base.empire_city_id, one_operation_amount);
                if (resource) {
                    trade_route_increase_traded(empire_city_get_route_id(base.empire_city_id), resource, one_operation_amount);
                    trader_record_bought_resource(base.trader_id, resource);
                    trader_buy(one_operation_amount);
                } else {
                    move_on++;
                }
            } else {
                move_on++;
            }

            if (move_on > 0 && can_sell(destination(), base.empire_city_id)) {
                e_resource resource = trader_get_sell_resource(destination(), base.empire_city_id);
                if (resource) {
                    trade_route_increase_traded(empire_city_get_route_id(base.empire_city_id), resource, one_operation_amount);
                    trader_record_sold_resource(base.trader_id, resource);
                    trader_sell(one_operation_amount);
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
        base.anim_frame = 0;
        break;

    case FIGURE_ACTION_103_TRADE_CARAVAN_LEAVING:
    case 11:
        if (do_goto(destination_tile, TERRAIN_USAGE_PREFER_ROADS)) {
            poof();
        }
        break;
    }

    int dir = figure_image_normalize_direction(direction() < 8 ? direction() : base.previous_tile_direction);
    base.sprite_image_id = image_group(IMG_TRADER_CARAVAN) + dir + 8 * base.anim_frame;
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

bool figure_trade_caravan::window_info_background(object_info &ctx) {
    draw_trader(&ctx);

    return true;
}
