#include "figure_kingdome_trader.h"

#include "building/building.h"
#include "building/building_dock.h"
#include "building/building_storage_yard.h"
#include "building/building_storage_room.h"
#include "city/buildings.h"
#include "city/city_finance.h"
#include "city/city.h"
#include "city/city_message.h"
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
#include "figure/trader.h"

#include "js/js_game.h"

figure_trade_caravan::static_params trade_caravan_m;

void ANK_PERMANENT_CALLBACK(event_trade_caravan_arrival, ev) {
    tile2i entry = g_city.map.entry_point;
    auto& emp_city = *g_empire.city(ev.cid);

    // Find first available trader slot
    const int free_slot = emp_city.get_free_slot(ev.max_traders);
    if (free_slot == -1) {
        return;
    }

    figure* caravan = figure_create(FIGURE_TRADE_CARAVAN, entry, DIR_0_TOP_RIGHT);
    caravan->empire_city_id = emp_city.name_id;
    caravan->action_state = ACTION_100_TRADE_CARAVAN_CREATED;
    caravan->wait_ticks = trade_caravan_m.wait_ticks_after_create;
    // donkey 1
    figure* donkey1 = figure_create(FIGURE_TRADE_CARAVAN_DONKEY, entry, DIR_0_TOP_RIGHT);
    donkey1->action_state = ACTION_100_TRADE_CARAVAN_CREATED;
    donkey1->leading_figure_id = caravan->id;
    // donkey 2
    figure* donkey2 = figure_create(FIGURE_TRADE_CARAVAN_DONKEY, entry, DIR_0_TOP_RIGHT);
    donkey2->action_state = ACTION_100_TRADE_CARAVAN_CREATED;
    donkey2->leading_figure_id = donkey1->id;

    emp_city.trader_figure_ids[free_slot] = caravan->id;
}

void figure_trade_caravan::static_params::archive_load(archive arch)  {
    int wait_ticks_after_create = arch.r_int("wait_ticks_after_create");
};

int figure::trader_total_bought() {
    return trader_amount_bought;
}

int figure::trader_total_sold() {
    return resource_amount_full;
}

void figure_trade_caravan::go_to_next_storageyard(tile2i src_tile, int distance_to_entry) {
    tile2i dst;
    int warehouse_id = get_closest_storageyard(src_tile, base.empire_city_id, distance_to_entry, dst);
    if (warehouse_id && warehouse_id != base.destinationID()) {
        set_destination(warehouse_id);
        base.action_state = ACTION_101_TRADE_CARAVAN_ARRIVING;
        base.destination_tile = dst;
    } else {
        base.state = FIGURE_STATE_ALIVE;
        base.destination_tile = map_closest_road_within_radius(g_city.map.exit_point, 1, 2);
        base.direction = DIR_0_TOP_RIGHT;
        advance_action(ACTION_16_EMIGRANT_RANDOM);
        base.action_state = ACTION_103_TRADE_CARAVAN_LEAVING;
    }
}

void figure_trade_caravan::on_create() {
    base.trader_id = trader_create();
}

void figure_trade_caravan::figure_action() {
    int last_action_state = action_state();
    switch (action_state()) {
    default:
    case ACTION_100_TRADE_CARAVAN_CREATED:
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

    case ACTION_101_TRADE_CARAVAN_ARRIVING:
        do_gotobuilding(destination(), true, TERRAIN_USAGE_PREFER_ROADS, ACTION_102_TRADE_CARAVAN_TRADING, ACTION_100_TRADE_CARAVAN_CREATED);
        if (direction() == DIR_FIGURE_CAN_NOT_REACH || direction() == DIR_FIGURE_REROUTE) {
            int i = 0; // break
        }
        break;

    case ACTION_102_TRADE_CARAVAN_TRADING:
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

    case ACTION_104_TRADE_CARAVAN_RECALC_LEAVING:
        if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            base.direction = DIR_0_TOP_RIGHT;
            base.destination_tile = g_city.map.closest_exit_tile_within_radius();
            advance_action(ACTION_103_TRADE_CARAVAN_LEAVING);
        }
        break;

    case ACTION_103_TRADE_CARAVAN_LEAVING:
        if (do_goto(base.destination_tile, TERRAIN_USAGE_PREFER_ROADS, -1, ACTION_104_TRADE_CARAVAN_RECALC_LEAVING)) {
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
    return {};
}

void figure_trade_caravan::update_animation() {
    int dir = figure_image_normalize_direction(direction() < 8 ? direction() : base.previous_tile_direction);
    base.main_image_id = anim(animkeys().walk).first_img() + dir + 8 * base.anim.frame;
}

xstring figure_trade_caravan::action_tip() const {
    int text_id = 0;
    switch (action_state()) {
    case ACTION_101_TRADE_CARAVAN_ARRIVING: text_id = 12; break;
    case ACTION_102_TRADE_CARAVAN_TRADING: text_id = 10; break;
    case ACTION_103_TRADE_CARAVAN_LEAVING: text_id = trader_has_traded(base.trader_id) ? 11 : 13; break;
    default:
        text_id = 11;
        break;
    }

    return { ui::str(129, text_id) };
}

