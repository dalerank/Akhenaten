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
#include "core/calc.h"
#include "empire/empire.h"
#include "empire/empire_map.h"
#include "empire/trade_prices.h"
#include "empire/trade_route.h"
#include "figure/combat.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "empire/trader_handler.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/image_desc.h"
#include "graphics/image_groups.h"
#include "grid/figure.h"
#include "grid/road_access.h"
#include "scenario/map.h"
#include "game/game.h"
#include "widget/debug_console.h"
#include "core/object_property.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_trade_caravan);

void ANK_PERMANENT_CALLBACK(event_trade_caravan_arrival, ev) {
    tile2i entry = g_city.map.entry_point;
    auto *emp_city = g_empire.city(ev.cid);
    
    if (!emp_city || !emp_city->in_use) {
        return;
    }

    // Find first available trader slot
    const int empire_trader_index = emp_city->get_free_slot();
    if (empire_trader_index == -1) {
        return;
    }

    if (!ev.tid) {
        assert(false);
        return;
    }

    figure *f = figure_create(FIGURE_TRADE_CARAVAN, entry, DIR_0_TOP_RIGHT);

    auto caravan = f->dcast<figure_trade_caravan>();
    assert(caravan != nullptr);

    caravan->runtime_data().empire_city = empire_city_handle{ emp_city->name_id };
    caravan->advance_action(ACTION_100_TRADE_CARAVAN_CREATED);
    caravan->base.wait_ticks = caravan->current_params().wait_ticks_after_create;
    caravan->runtime_data().trader = empire_trader_handle{ ev.tid };
    // donkey 1
    figure* donkey1 = figure_create(FIGURE_TRADE_CARAVAN_DONKEY, entry, DIR_0_TOP_RIGHT);
    donkey1->action_state = ACTION_100_TRADE_CARAVAN_CREATED;
    donkey1->leading_figure_id = caravan->id();
    // donkey 2
    figure* donkey2 = figure_create(FIGURE_TRADE_CARAVAN_DONKEY, entry, DIR_0_TOP_RIGHT);
    donkey2->action_state = ACTION_100_TRADE_CARAVAN_CREATED;
    donkey2->leading_figure_id = donkey1->id;

    emp_city->trader_figure_ids[empire_trader_index] = caravan->id();
}

int figure::trader_total_sold() {
    return resource_amount_full;
}

void figure_trade_caravan::go_to_next_storageyard(tile2i src_tile, int distance_to_entry) {
    tile2i dst;
    auto& d = runtime_data();
    int warehouse_id = get_closest_storageyard(src_tile, d.empire_city, distance_to_entry, dst);
    if (warehouse_id && warehouse_id != base.destinationID()) {
        set_destination(warehouse_id);
        advance_action(ACTION_101_TRADE_CARAVAN_ARRIVING, dst);
    } else {
        base.state = FIGURE_STATE_ALIVE;
        base.destination_tile = map_closest_road_within_radius(g_city.map.exit_point, 1, 2);
        base.direction = DIR_0_TOP_RIGHT;
        advance_action(ACTION_103_TRADE_CARAVAN_LEAVING);
    }
}

void figure_trade_caravan::debug_show_properties() {
    game_debug_show_property("trader_id", runtime_data().trader.handle);
    game_debug_show_property("empire_city_id", runtime_data().empire_city.handle);
}

void figure_trade_caravan::on_create() {
    figure_trader::on_create();
    auto &d = runtime_data();
    const uint16_t max_capacity = (current_params().capacity_random == 0) ? 800 : current_params().capacity_random;
    const uint16_t capacity = current_params().min_capacity + rand() % max_capacity;
    d.capacity = std::clamp(capacity, current_params().min_capacity, current_params().max_capacity);
}

void figure_trade_caravan::on_destroy() {
    figure_trader::on_destroy();
    empire_city().remove_trader(id());
}

void figure_trade_caravan::figure_action() {
    int last_action_state = action_state();
    auto& d = runtime_data();
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
        base.animctx.frame = 0;
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
            if (can_buy(destination(), d.empire_city)) {
                e_resource resource = empire_trader().get_buy_resource(destination(), d.empire_city, UNITS_PER_LOAD);
                if (resource) {
                    auto &trade_route = d.empire_city.get_route();
                    trade_route.increase_traded(resource, UNITS_PER_LOAD);
                    empire_trader().record_bought_resource(resource);
                    buy(UNITS_PER_LOAD);
                } else {
                    move_on++;
                }
            } else {
                move_on++;
            }

            if (move_on > 0 && can_sell(destination(), d.empire_city)) {
                e_resource resource = empire_trader().get_sell_resource(destination(), d.empire_city);
                if (resource) {
                    auto &trade_route = d.empire_city.get_route();
                    trade_route.increase_traded(resource, UNITS_PER_LOAD);
                    empire_trader().record_sold_resource(resource);
                    sell(UNITS_PER_LOAD);
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
        base.animctx.frame = 0;
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
            runtime_data().trader.back_to_city();
            poof();
        }
        break;
    }
}

void figure_trade_caravan::before_poof() {
    ; // nothing
}

sound_key figure_trade_caravan::phrase_key() const {
    auto& d = runtime_data();
    
    if (action_state() == ACTION_103_TRADE_CARAVAN_LEAVING) {
        if (!empire_trader().has_traded()) {
            return "trader_city_not_trades";
        } else {
            return "trader_you_talk_a_fine_bargain";
        }
    }

    if (action_state() == ACTION_102_TRADE_CARAVAN_TRADING) {
        if (can_buy(destination(), d.empire_city)) {
            return "trader_buy_for_less_sell_for_more"; 
        } else if (can_sell(destination(), d.empire_city)) {
            return "trader_you_talk_a_fine_bargain"; 
        } else {
            return "trader_its_my_life";
        }
    }

    if (action_state() == ACTION_101_TRADE_CARAVAN_ARRIVING) {
        return "trader_i_ll_be_a_hero";
    }
    
    // Default for other states (created, etc)
    return "trader_its_my_life";
}

void figure_trade_caravan::update_animation() {
    int dir = base.figure_image_normalize_direction(direction() < 8 ? direction() : base.previous_tile_direction);
    base.main_image_id = anim(animkeys().walk).first_img() + dir + 8 * base.animctx.frame;
}

bvariant figure_trade_caravan::get_property(const xstring& domain, const xstring& name) const {
    auto result = archive_helper::get(runtime_data(), name, domain == tags().figure);
    if (result) {
        return result.value();
    }

    return figure_impl::get_property(domain, name);
}

xstring figure_trade_caravan::action_tip() const {
    switch (action_state()) {
    case ACTION_101_TRADE_CARAVAN_ARRIVING: return "#trader_heading_storage";
    case ACTION_102_TRADE_CARAVAN_TRADING: return "#trader_trading_goods";
    case ACTION_103_TRADE_CARAVAN_LEAVING:
        return empire_trader().has_traded()
            ? "#trader_returning_home"
            : "#trader_nothing_to_trage";
    default:
        return "#trader_returning_home";
    }

    return "#trader_unknown";
}

