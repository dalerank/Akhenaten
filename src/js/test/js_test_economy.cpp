#include "js/test/js_test_common.h"

#include "building/building.h"
#include "building/building_barracks.h"
#include "building/building_bazaar.h"
#include "building/building_delivery_path.h"
#include "building/building_farm.h"
#include "building/building_fishing_wharf.h"
#include "building/building_food_mill.h"
#include "building/building_fort.h"
#include "building/building_gatehouse.h"
#include "building/building_granary.h"
#include "building/building_house.h"
#include "building/building_shipyard.h"
#include "building/building_static_params.h"
#include "building/building_storage.h"
#include "building/building_storage_yard.h"
#include "building/building_temple_complex.h"
#include "building/monument_mastaba.h"
#include "building/monument_obelisk.h"
#include "building/monument_pyramid.h"
#include "building/monument_royal_tomb.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "city/city_industry.h"
#include "city/city_trade.h"
#include "city/object_info.h"
#include "core/bstring.h"
#include "core/xstring.h"
#include "empire/empire.h"
#include "empire/empire_traders.h"
#include "empire/trader_handler.h"
#include "figure/figure.h"
#include "figure/figure_impl.h"
#include "figure/formation.h"
#include "figuretype/animal_asp.h"
#include "figuretype/animal_lion.h"
#include "figuretype/animal_scorpion.h"
#include "figuretype/figure_bricklayer.h"
#include "figuretype/figure_carpenter.h"
#include "figuretype/figure_cartpusher.h"
#include "figuretype/figure_docker.h"
#include "figuretype/figure_enemy_archer.h"
#include "figuretype/figure_enemy_elephant.h"
#include "figuretype/figure_enemy_spearman.h"
#include "figuretype/figure_enemy_transport.h"
#include "figuretype/figure_enemy_warship.h"
#include "figuretype/figure_ferry_boat.h"
#include "figuretype/figure_flotsam.h"
#include "figuretype/figure_frog.h"
#include "figuretype/figure_hunter.h"
#include "figuretype/figure_kingdome_trader.h"
#include "figuretype/figure_locust.h"
#include "figuretype/figure_market_buyer.h"
#include "figuretype/figure_plagued_citizen.h"
#include "figuretype/figure_trader_ship.h"
#include "figuretype/figure_transport_ship.h"
#include "figuretype/figure_war_ship.h"
#include "figuretype/figure_worker.h"
#include "game/game.h"
#include "game/game_config.h"
#include "game/resource.h"
#include "grid/grid.h"
#include "grid/road_access.h"
#include "grid/road_network.h"
#include "grid/routing/routing.h"
#include "scenario/scenario.h"

#include <algorithm>

// Cycles the yard's storage state for `resource` until it equals `state`. Returns 1 on success.
static int __test_storage_yard_set_state(int yard_bid, int resource, int state) {
    building* b = building_get(yard_bid);
    auto* yard = b ? b->dcast_storage_yard() : nullptr;
    if (!yard || !b->is_valid() || resource <= RESOURCE_NONE || resource >= RESOURCES_MAX) {
        return 0;
    }
    for (int i = 0; i < STORAGE_STATE_MAX + 1; i++) {
        if (yard->storage()->resource_state[resource] == state) {
            return 1;
        }
        building_storage_cycle_resource_state(yard->storage_id(), (e_resource)resource, false);
    }
    return yard->storage()->resource_state[resource] == state ? 1 : 0;
}
ANK_FUNCTION_3(__test_storage_yard_set_state);

static void __test_city_set_trade(int resource, int status, int trading_amount) {
    if (resource <= RESOURCE_NONE || resource >= RESOURCES_MAX) {
        return;
    }
    g_city.resource.trade_status[resource] = (e_trade_status)status;
    g_city.resource.trading_amount[resource] = (int16_t)trading_amount;
}
ANK_FUNCTION_3(__test_city_set_trade);

static void __test_trade_update_export_keep() {
    city_trade_update_export_keep();
}
ANK_FUNCTION(__test_trade_update_export_keep);

// What the trade checks read as stored in yards, without placing a connected yard.
static void __test_city_set_yards_stored(int resource, int amount) {
    if (resource > RESOURCE_NONE && resource < RESOURCES_MAX) {
        g_city.resource.stored_in_storages[resource] = (uint16_t)amount;
    }
}
ANK_FUNCTION_2(__test_city_set_yards_stored);

static int __test_trade_export_keep(int resource) {
    return city_trade_export_keep((e_resource)resource);
}
ANK_FUNCTION_1(__test_trade_export_keep);

static bool __test_empire_can_export_to(int city_id, int resource) {
    if (!g_empire.city(city_id) || resource <= RESOURCE_NONE || resource >= RESOURCES_MAX) {
        return false;
    }
    return g_empire.can_export_resource_to_city(city_id, (e_resource)resource);
}
ANK_FUNCTION_2(__test_empire_can_export_to);

static bool __test_empire_can_import_from(int city_id, int resource) {
    if (!g_empire.city(city_id) || resource <= RESOURCE_NONE || resource >= RESOURCES_MAX) {
        return false;
    }
    return g_empire.can_import_resource_from_city(city_id, (e_resource)resource);
}
ANK_FUNCTION_2(__test_empire_can_import_from);

static int __test_empire_import_stock_limit(int resource) {
    if (resource <= RESOURCE_NONE || resource >= RESOURCES_MAX) {
        return 0;
    }
    return g_empire.import_stock_limit((e_resource)resource);
}
ANK_FUNCTION_1(__test_empire_import_stock_limit);

// Makes city_id trade only `resource` (buys and sells) with the given route limit; -1 when the slot is unused.
static int __test_empire_city_trade_only(int city_id, int resource, int limit) {
    empire_city* city = g_empire.city(city_id);
    if (!city || !city->in_use || resource <= RESOURCE_NONE || resource >= RESOURCES_MAX) {
        return -1;
    }
    city->clear_trade_resources();
    city->buys_resource[resource] = true;
    city->sells_resource[resource] = true;
    trade_route& route = city->get_route();
    for (e_resource r = RESOURCES_MIN; r < RESOURCES_MAX; ++r) {
        route.init(r, 0);
    }
    route.init((e_resource)resource, limit);
    return city->route_id;
}
ANK_FUNCTION_3(__test_empire_city_trade_only);

static bool __test_empire_city_add_trade(int city_id, int resource, int limit) {
    empire_city* city = g_empire.city(city_id);
    if (!city || !city->in_use || resource <= RESOURCE_NONE || resource >= RESOURCES_MAX) {
        return false;
    }
    city->buys_resource[resource] = true;
    city->get_route().init((e_resource)resource, limit);
    return true;
}
ANK_FUNCTION_3(__test_empire_city_add_trade);

static int __test_empire_city_trader_size(int city_id) {
    empire_city* city = g_empire.city(city_id);
    return city ? city->trader_size() : -1;
}
ANK_FUNCTION_1(__test_empire_city_trader_size);

static int __test_empire_city_free_trader_slot(int city_id) {
    empire_city* city = g_empire.city(city_id);
    return city ? city->free_trader_slot() : -1;
}
ANK_FUNCTION_1(__test_empire_city_free_trader_slot);

// Marks trader slots as taken (fid != 0) without spawning figures.
static void __test_empire_city_set_trader_figure(int city_id, int slot, int fid) {
    empire_city* city = g_empire.city(city_id);
    if (city && slot >= 0 && slot < (int)std::size(city->trader_figure_ids)) {
        city->trader_figure_ids[slot] = fid;
    }
}
ANK_FUNCTION_3(__test_empire_city_set_trader_figure);

static void __test_empire_city_set_trader_blocked(int city_id, int blocked) {
    if (empire_city* city = g_empire.city(city_id)) {
        city->trader_blocked = blocked;
    }
}
ANK_FUNCTION_2(__test_empire_city_set_trader_blocked);

static int __test_empire_set_max_traders_per_city(int count) {
    const int prev = empire_trade_rules.max_traders_per_city;
    empire_trade_rules.max_traders_per_city = count;
    return prev;
}
ANK_FUNCTION_1(__test_empire_set_max_traders_per_city);

static int __test_cartpusher_destination_wait_threshold() {
    return figure_cartpusher::destination_wait_threshold();
}
ANK_FUNCTION(__test_cartpusher_destination_wait_threshold);

static void __test_city_industry_update_production() {
    g_city.industry.update_production();
}
ANK_FUNCTION(__test_city_industry_update_production);

static void __test_city_industry_update_nearby_houses_weekly() {
    g_city.industry.update_nearby_houses_weekly();
}
ANK_FUNCTION(__test_city_industry_update_nearby_houses_weekly);

// Force-stock a storage yard (bypasses accepting/getting rules). Yard must already exist.
// Force-remove from a storage yard. Returns true when the resource is fully gone.
static bool __test_storage_yard_remove_resource(int bid, int resource, int amount) {
    building* b = building_get(bid);
    auto* yard = b ? b->dcast_storage_yard() : nullptr;
    if (!yard || !b->is_valid() || amount <= 0) {
        return false;
    }
    yard->remove_resource((e_resource)resource, amount);
    return yard->amount((e_resource)resource) <= 0;
}
ANK_FUNCTION_3(__test_storage_yard_remove_resource);

static bool __test_storage_yard_add_resource(int bid, int resource, int amount) {
    building* b = building_get(bid);
    auto* yard = b ? b->dcast_storage_yard() : nullptr;
    if (!yard || !b->is_valid() || resource <= RESOURCE_NONE || resource >= RESOURCES_MAX || amount <= 0) {
        return false;
    }
    return yard->add_resource(static_cast<e_resource>(resource), amount, /*force*/ true) >= 0;
}
ANK_FUNCTION_3(__test_storage_yard_add_resource);

static int __test_yards_stored(int resource) {
    if (resource <= RESOURCE_NONE || resource >= RESOURCES_MAX) {
        return 0;
    }
    return g_city.resource.yards_stored(static_cast<e_resource>(resource));
}
ANK_FUNCTION_1(__test_yards_stored);

static int __test_yards_stored_staffed(int resource) {
    if (resource <= RESOURCE_NONE || resource >= RESOURCES_MAX) {
        return 0;
    }
    return g_city.resource.yards_stored_staffed(static_cast<e_resource>(resource));
}
ANK_FUNCTION_1(__test_yards_stored_staffed);

static int __test_trader_capacity(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_valid()) {
        return -1;
    }
    if (auto* caravan = f->dcast<figure_trade_caravan>()) {
        return caravan->max_capacity();
    }
    if (auto* ship = f->dcast<figure_trade_ship>()) {
        return ship->max_capacity();
    }
    return -1;
}
ANK_FUNCTION_1(__test_trader_capacity);

static int __test_trader_static_max_capacity(int type) {
    if (type == FIGURE_TRADE_CARAVAN) {
        const auto& p = (const figure_trade_caravan::static_params&)figure_static_params::get(FIGURE_TRADE_CARAVAN);
        return p.max_capacity;
    }
    if (type == FIGURE_TRADE_SHIP) {
        const auto& p = (const figure_trade_ship::static_params&)figure_static_params::get(FIGURE_TRADE_SHIP);
        return p.max_capacity;
    }
    return -1;
}
ANK_FUNCTION_1(__test_trader_static_max_capacity);

static int __test_trader_static_capacity_random(int type) {
    if (type != FIGURE_TRADE_CARAVAN) {
        return -1;
    }
    const auto& p = (const figure_trade_caravan::static_params&)figure_static_params::get(FIGURE_TRADE_CARAVAN);
    return p.capacity_random;
}
ANK_FUNCTION_1(__test_trader_static_capacity_random);

static void __test_trader_set_bought(int fid, int amount) {
    figure* f = figure_get(fid);
    if (!f || !f->is_valid()) {
        return;
    }
    if (auto* caravan = f->dcast<figure_trade_caravan>()) {
        caravan->runtime_data().amount_bought = (uint16_t)std::max(0, amount);
        return;
    }
    if (auto* ship = f->dcast<figure_trade_ship>()) {
        ship->runtime_data().amount_bought = (uint16_t)std::max(0, amount);
    }
}
ANK_FUNCTION_2(__test_trader_set_bought);

static int __test_trader_buy_under_capacity(int fid) {
    figure* f = figure_get(fid);
    if (!f || !f->is_valid()) {
        return -1;
    }
    if (auto* caravan = f->dcast<figure_trade_caravan>()) {
        return caravan->total_bought() < caravan->max_capacity() ? 1 : 0;
    }
    if (auto* ship = f->dcast<figure_trade_ship>()) {
        return ship->total_bought() < ship->max_capacity() ? 1 : 0;
    }
    return -1;
}
ANK_FUNCTION_1(__test_trader_buy_under_capacity);

static int __test_empire_trader_has_traded_max(int bought, int sold, int capacity) {
    empire_trader_handle h = empire_create_trader();
    if (!h.valid()) {
        return -1;
    }
    auto& t = g_empire_traders.traders[h.handle];
    t.bought_amount = (uint16_t)std::max(0, bought);
    t.sold_amount = (uint16_t)std::max(0, sold);
    const int result = h.has_traded_max(capacity) ? 1 : 0;
    t.is_active = false;
    return result;
}
ANK_FUNCTION_3(__test_empire_trader_has_traded_max);

static int __test_empire_trader_per_good_cap() {
    return empire_trader_per_good_cap();
}
ANK_FUNCTION(__test_empire_trader_per_good_cap);

static int __test_empire_trader_ignore_total_bag() {
    return empire_trader_ignore_total_bag() ? 1 : 0;
}
ANK_FUNCTION(__test_empire_trader_ignore_total_bag);

// Sets bought_resources[resource]=amount (and totals), returns buy_full(resource) as 0/1.
static int __test_empire_trader_buy_full_at(int resource, int amount) {
    empire_trader_handle h = empire_create_trader();
    if (!h.valid()) {
        return -1;
    }
    auto& t = g_empire_traders.traders[h.handle];
    const e_resource r = (e_resource)std::clamp(resource, 0, (int)RESOURCES_MAX - 1);
    t.bought_resources[r] = (uint16_t)std::max(0, amount);
    t.bought_amount = t.bought_resources[r];
    const int result = h.buy_full(r) ? 1 : 0;
    t.is_active = false;
    return result;
}
ANK_FUNCTION_2(__test_empire_trader_buy_full_at);

// pottery_amt / beer_amt on one trader; returns buy_full(pottery)*10 + buy_full(beer).
static int __test_empire_trader_two_goods_buy_full(int pottery_amt, int beer_amt) {
    empire_trader_handle h = empire_create_trader();
    if (!h.valid()) {
        return -1;
    }
    auto& t = g_empire_traders.traders[h.handle];
    t.bought_resources[RESOURCE_POTTERY] = (uint16_t)std::max(0, pottery_amt);
    t.bought_resources[RESOURCE_BEER] = (uint16_t)std::max(0, beer_amt);
    t.bought_amount = (uint16_t)(t.bought_resources[RESOURCE_POTTERY] + t.bought_resources[RESOURCE_BEER]);
    const int result = (h.buy_full(RESOURCE_POTTERY) ? 10 : 0) + (h.buy_full(RESOURCE_BEER) ? 1 : 0);
    t.is_active = false;
    return result;
}
ANK_FUNCTION_2(__test_empire_trader_two_goods_buy_full);

static int __test_empire_trader_buy_room_at(int resource, int amount) {
    empire_trader_handle h = empire_create_trader();
    if (!h.valid()) {
        return -1;
    }
    auto& t = g_empire_traders.traders[h.handle];
    const e_resource r = (e_resource)std::clamp(resource, 0, (int)RESOURCES_MAX - 1);
    t.bought_resources[r] = (uint16_t)std::max(0, amount);
    const int result = h.buy_room(r);
    t.is_active = false;
    return result;
}
ANK_FUNCTION_2(__test_empire_trader_buy_room_at);

// Active trader with the given per-resource bought/sold amounts; returns its handle or -1.
static int __test_empire_trader_create_with(int resource, int bought, int sold) {
    empire_trader_handle h = empire_create_trader();
    if (!h.valid()) {
        return -1;
    }
    auto& t = g_empire_traders.traders[h.handle];
    const e_resource r = (e_resource)std::clamp(resource, 0, (int)RESOURCES_MAX - 1);
    t.bought_resources[r] = (uint16_t)std::max(0, bought);
    t.sold_resources[r] = (uint16_t)std::max(0, sold);
    return h.handle;
}
ANK_FUNCTION_3(__test_empire_trader_create_with);

static int __test_empire_trader_bought_at(int handle, int resource) {
    if (handle < 0 || handle >= (int)g_empire_traders.traders.size()) {
        return -1;
    }
    const e_resource r = (e_resource)std::clamp(resource, 0, (int)RESOURCES_MAX - 1);
    return g_empire_traders.traders[handle].bought_resources[r];
}
ANK_FUNCTION_2(__test_empire_trader_bought_at);

static int __test_empire_trader_sold_at(int handle, int resource) {
    if (handle < 0 || handle >= (int)g_empire_traders.traders.size()) {
        return -1;
    }
    const e_resource r = (e_resource)std::clamp(resource, 0, (int)RESOURCES_MAX - 1);
    return g_empire_traders.traders[handle].sold_resources[r];
}
ANK_FUNCTION_2(__test_empire_trader_sold_at);

static void __test_empire_trader_release(int handle) {
    if (handle >= 0 && handle < (int)g_empire_traders.traders.size()) {
        g_empire_traders.traders[handle].is_active = false;
    }
}
ANK_FUNCTION_1(__test_empire_trader_release);

// Attach FIGURE_MARKET_BUYER to a bazaar slot and run before_action.
// Returns figure id if still alive, else 0.
static int __test_bazaar_attach_buyer(int bid, int slot, int collecting_item) {
    auto* bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar) {
        return 0;
    }
    figure* f = figure_create(FIGURE_MARKET_BUYER, bazaar->tile(), DIR_0_TOP_RIGHT);
    if (!f || !f->is_alive()) {
        return 0;
    }
    f->set_home(bid);
    f->collecting_item_id = (uint8_t)std::clamp(collecting_item, 0, INVENTORY_MAX - 1);
    f->advance_action(ACTION_145_MARKET_BUYER_GOING_TO_STORAGE);
    bazaar->base.set_figure(slot, f->id);
    if (auto* buyer = f->dcast_market_buyer()) {
        if (figure_market_buyer::use_og_trip()) {
            int8_t items[4] = {-1, -1, -1, -1};
            items[0] = (int8_t)f->collecting_item_id;
            const bool food = f->collecting_item_id <= INVENTORY_FOOD4;
            buyer->init_og_trip(items, food);
        }
        buyer->figure_before_action();
    }
    return f->is_alive() ? f->id : 0;
}
ANK_FUNCTION_3(__test_bazaar_attach_buyer);

static int __test_market_buyer_og_resources(int fid, int index) {
    figure* f = figure_get(fid);
    if (!f || f->type != FIGURE_MARKET_BUYER || index < 0 || index > 3) {
        return -2;
    }
    auto* buyer = f->dcast_market_buyer();
    return buyer ? buyer->runtime_data().resources[index] : -2;
}
ANK_FUNCTION_2(__test_market_buyer_og_resources);

static int __test_market_buyer_og_storages_visited(int fid) {
    figure* f = figure_get(fid);
    if (!f || f->type != FIGURE_MARKET_BUYER) {
        return -1;
    }
    auto* buyer = f->dcast_market_buyer();
    return buyer ? buyer->runtime_data().storages_visited : -1;
}
ANK_FUNCTION_1(__test_market_buyer_og_storages_visited);

static int __test_market_buyer_og_is_food_trip(int fid) {
    figure* f = figure_get(fid);
    if (!f || f->type != FIGURE_MARKET_BUYER) {
        return -1;
    }
    auto* buyer = f->dcast_market_buyer();
    return buyer ? buyer->runtime_data().is_food_trip : -1;
}
ANK_FUNCTION_1(__test_market_buyer_og_is_food_trip);

static int __test_bazaar_og_food_destination(int bid) {
    auto* bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar) {
        return -1;
    }
    int8_t items[4] = {-1, -1, -1, -1};
    building* dest = bazaar->get_og_food_destination(items);
    return (dest && dest->id) ? dest->id : 0;
}
ANK_FUNCTION_1(__test_bazaar_og_food_destination);

static int __test_bazaar_og_goods_destination(int bid) {
    auto* bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar) {
        return -1;
    }
    int8_t items[4] = {-1, -1, -1, -1};
    building* dest = bazaar->get_og_goods_destination(items);
    return (dest && dest->id) ? dest->id : 0;
}
ANK_FUNCTION_1(__test_bazaar_og_goods_destination);

static int __test_bazaar_max_buyers_param() {
    const auto& p = (const building_bazaar::static_params&)building_static_params::get(BUILDING_BAZAAR);
    return p.max_buyers;
}
ANK_FUNCTION(__test_bazaar_max_buyers_param);

static int __test_bazaar_food_variety_target_param() {
    const auto& p = (const building_bazaar::static_params&)building_static_params::get(BUILDING_BAZAAR);
    return p.food_variety_target;
}
ANK_FUNCTION(__test_bazaar_food_variety_target_param);

static int __test_bazaar_count_buyers(int bid) {
    auto* bazaar = building_get(bid)->dcast_bazaar();
    return bazaar ? bazaar->count_market_buyers() : -1;
}
ANK_FUNCTION_1(__test_bazaar_count_buyers);

static int __test_bazaar_on_buyer_returned(int fid) {
    figure* f = figure_get(fid);
    if (!f || f->type != FIGURE_MARKET_BUYER) {
        return -1;
    }
    if (auto* buyer = f->dcast_market_buyer()) {
        buyer->apply_return_home_spawn_cooldown();
        building* h = f->home();
        return h ? h->figure_spawn_delay : -1;
    }
    return -1;
}
ANK_FUNCTION_1(__test_bazaar_on_buyer_returned);

static int __test_bazaar_pick_next_inventory(int bid) {
    auto* bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar) {
        return -1;
    }
    building* dest = bazaar->pick_next_buyer_destination();
    if (!dest || !dest->id) {
        return -1;
    }
    return bazaar->runtime_data().fetch_inventory_id;
}
ANK_FUNCTION_1(__test_bazaar_pick_next_inventory);

static int __test_bazaar_get_storage_inventory(int bid) {
    auto* bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar) {
        return -1;
    }
    building* dest = bazaar->get_storage_destination();
    if (!dest || !dest->id) {
        return -1;
    }
    return bazaar->runtime_data().fetch_inventory_id;
}
ANK_FUNCTION_1(__test_bazaar_get_storage_inventory);

static int __test_bazaar_get_storage_destination_type(int bid) {
    auto* bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar) {
        return -1;
    }
    building* dest = bazaar->get_storage_destination();
    if (!dest || !dest->id) {
        return 0;
    }
    return dest->type;
}
ANK_FUNCTION_1(__test_bazaar_get_storage_destination_type);

static int __test_bazaar_get_storage_destination_id(int bid) {
    auto* bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar) {
        return -1;
    }
    building* dest = bazaar->get_storage_destination();
    return (dest && dest->id) ? dest->id : 0;
}
ANK_FUNCTION_1(__test_bazaar_get_storage_destination_id);

static int __test_bazaar_set_desired_variety(int bid, int value) {
    auto* bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar) {
        return 0;
    }
    bazaar->set_desired_variety((uint8_t)value);
    return bazaar->desired_variety();
}
ANK_FUNCTION_2(__test_bazaar_set_desired_variety);

static int __test_bazaar_set_min_variety(int bid, int value) {
    auto* bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar) {
        return 0;
    }
    bazaar->set_min_variety((uint8_t)value);
    return bazaar->min_variety();
}
ANK_FUNCTION_2(__test_bazaar_set_min_variety);

static int __test_bazaar_desired_variety(int bid) {
    auto* bazaar = building_get(bid)->dcast_bazaar();
    return bazaar ? bazaar->desired_variety() : -1;
}
ANK_FUNCTION_1(__test_bazaar_desired_variety);

static int __test_bazaar_min_variety(int bid) {
    auto* bazaar = building_get(bid)->dcast_bazaar();
    return bazaar ? bazaar->min_variety() : -1;
}
ANK_FUNCTION_1(__test_bazaar_min_variety);

static int __test_bazaar_waiting_for_mill(int bid) {
    auto* bazaar = building_get(bid)->dcast_bazaar();
    return bazaar ? (bazaar->waiting_for_mill_variety() ? 1 : 0) : -1;
}
ANK_FUNCTION_1(__test_bazaar_waiting_for_mill);

static int __test_market_buyer_take_food(int fid, int market_id, int storage_id) {
    figure* f = figure_get(fid);
    if (!f || f->type != FIGURE_MARKET_BUYER) {
        return -1;
    }
    auto* buyer = f->dcast_market_buyer();
    building* market = building_get(market_id);
    building* storage = building_get(storage_id);
    if (!buyer || !market || !storage) {
        return -1;
    }
    return buyer->take_food_from_storage(market, storage);
}
ANK_FUNCTION_3(__test_market_buyer_take_food);

static int __test_bazaar_set_inventory(int bid, int inv, int amount) {
    auto* bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar || inv < 0 || inv >= INVENTORY_MAX) {
        return 0;
    }
    bazaar->runtime_data().inventory[inv].value = (uint16_t)std::max(0, amount);
    return 1;
}
ANK_FUNCTION_3(__test_bazaar_set_inventory);

static int __test_bazaar_get_inventory(int bid, int inv) {
    auto* bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar || inv < 0 || inv >= INVENTORY_MAX) {
        return -1;
    }
    return bazaar->runtime_data().inventory[inv].value;
}
ANK_FUNCTION_2(__test_bazaar_get_inventory);

static int __test_bazaar_food_types(int bid) {
    auto* bazaar = building_get(bid)->dcast_bazaar();
    return bazaar ? bazaar->food_types_in_inventory() : -1;
}
ANK_FUNCTION_1(__test_bazaar_food_types);

static void __test_bazaar_set_good_demands(int bid, int pottery, int luxury, int linen, int beer) {
    auto* bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar) {
        return;
    }
    auto& d = bazaar->runtime_data();
    d.pottery_demand = (short)pottery;
    d.luxurygoods_demand = (short)luxury;
    d.linen_demand = (short)linen;
    d.beer_demand = (short)beer;
}
ANK_FUNCTION_5(__test_bazaar_set_good_demands);

static int __test_bazaar_link_storage(int bazaar_id, int storage_id) {
    building* bazaar = building_get(bazaar_id);
    building* storage = building_get(storage_id);
    if (!bazaar || !storage || !bazaar->dcast_bazaar() || !storage->dcast_storage()) {
        return 0;
    }
    if (bazaar->road_network_id <= 0) {
        bazaar->road_network_id = 1;
    }
    if (bazaar->distance_from_entry <= 0) {
        bazaar->distance_from_entry = 1;
    }
    bazaar->has_road_access = true;
    storage->road_network_id = bazaar->road_network_id;
    storage->distance_from_entry = bazaar->distance_from_entry;
    storage->has_road_access = true;
    return 1;
}
ANK_FUNCTION_2(__test_bazaar_link_storage);

static int __test_bazaar_reclaim_slot(int bid, int slot) {
    auto* bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar) {
        return -1;
    }
    bazaar->reclaim_inactive_buyer_slot((e_building_slot)slot);
    return bazaar->base.get_figure_id(slot);
}
ANK_FUNCTION_2(__test_bazaar_reclaim_slot);

static int __test_bazaar_busy_excludes(int bid, int inv) {
    auto* bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar || inv < 0 || inv >= INVENTORY_MAX) {
        return -1;
    }
    bool exclude[INVENTORY_MAX];
    bool has_food = false;
    bool has_good = false;
    bazaar->collect_buyer_busy_state(exclude, &has_food, &has_good);
    return exclude[inv] ? 1 : 0;
}
ANK_FUNCTION_2(__test_bazaar_busy_excludes);

static int __test_bazaar_pottery_demand(int bid) {
    auto* bazaar = building_get(bid)->dcast_bazaar();
    return bazaar ? bazaar->runtime_data().pottery_demand : -1;
}
ANK_FUNCTION_1(__test_bazaar_pottery_demand);

static int __test_bazaar_slot_figure(int bid, int slot) {
    auto* bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar) {
        return -1;
    }
    return bazaar->base.get_figure_id(slot);
}
ANK_FUNCTION_2(__test_bazaar_slot_figure);

static int __test_bazaar_force_spawn(int bid) {
    auto* bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar) {
        return 0;
    }
    building& b = bazaar->base;
    b.num_workers = std::max(1, (int)b.max_workers);
    b.has_road_access = true;
    if (b.road_network_id <= 0) {
        b.road_network_id = 1;
    }
    if (b.distance_from_entry <= 0) {
        b.distance_from_entry = 1;
    }
    b.figure_spawn_delay = 0;
    // Align OG buyer stagger: pass index becomes 1 on spawn ? day % 8 == 1.
    g_city.figures.bazaar_figure_pass_index = 0;
    if (!game_features::gameplay_change_bazaar_buyer_spawn_timer.to_bool()) {
        game.simtime.day = 1;
    }
    bazaar->spawn_figure();
    return 1;
}
ANK_FUNCTION_1(__test_bazaar_force_spawn);

static int __test_bazaar_count_traders(int bid) {
    auto* bazaar = building_get(bid)->dcast_bazaar();
    if (!bazaar) {
        return -1;
    }
    int count = 0;
    for (int i = 1; i < MAX_FIGURES; i++) {
        figure* f = figure_get(i);
        if (f && f->is_alive() && f->type == FIGURE_MARKET_TRADER && f->has_home(bid)) {
            count++;
        }
    }
    return count;
}
ANK_FUNCTION_1(__test_bazaar_count_traders);

static int __test_bazaar_second_trader_id(int bid) {
    auto* bazaar = building_get(bid)->dcast_bazaar();
    return bazaar ? bazaar->second_trader_id() : -1;
}
ANK_FUNCTION_1(__test_bazaar_second_trader_id);

static int __test_bazaar_fancy_threshold(int bid) {
    auto* bazaar = building_get(bid)->dcast_bazaar();
    return bazaar ? bazaar->current_params().fancy_treshold_desirability : -1;
}
ANK_FUNCTION_1(__test_bazaar_fancy_threshold);

static int __test_granary_add_allowed_food(int bid, int food_index, int amount) {
    building* b = building_get(bid);
    auto* granary = b ? b->dcast_granary() : nullptr;
    if (!granary || !b->is_valid() || food_index < 0 || food_index >= INVENTORY_MAX_FOOD || amount <= 0) {
        return 0;
    }
    e_resource res = g_city.allowed_foods(food_index);
    if (res == RESOURCE_NONE) {
        return 0;
    }
    return granary->add_resource(res, amount, /*force*/ true) >= 0 ? 1 : 0;
}
ANK_FUNCTION_3(__test_granary_add_allowed_food);

static int __test_granary_add_resource(int bid, int resource, int amount) {
    building* b = building_get(bid);
    auto* granary = b ? b->dcast_granary() : nullptr;
    if (!granary || !b->is_valid() || amount <= 0) {
        return 0;
    }
    return granary->add_resource((e_resource)resource, amount, /*force*/ true) >= 0 ? 1 : 0;
}
ANK_FUNCTION_3(__test_granary_add_resource);

static int __test_granary_add_resource_noforce(int bid, int resource, int amount) {
    building* b = building_get(bid);
    auto* granary = b ? b->dcast_granary() : nullptr;
    if (!granary || !b->is_valid() || amount <= 0) {
        return 0;
    }
    return granary->add_resource((e_resource)resource, amount, /*force*/ false) >= 0 ? 1 : 0;
}
ANK_FUNCTION_3(__test_granary_add_resource_noforce);

static int __test_granary_set_getting(int bid, int resource) {
    building* b = building_get(bid);
    auto* granary = b ? b->dcast_granary() : nullptr;
    if (!granary || !b->is_valid()) {
        return 0;
    }
    for (int i = 0; i < 8; i++) {
        if (granary->is_getting((e_resource)resource)) {
            return 1;
        }
        building_storage_cycle_resource_state(granary->storage_id(), (e_resource)resource, false);
    }
    return granary->is_getting((e_resource)resource) ? 1 : 0;
}
ANK_FUNCTION_2(__test_granary_set_getting);

static int __test_granary_set_emptying(int bid, int resource) {
    building* b = building_get(bid);
    auto* granary = b ? b->dcast_granary() : nullptr;
    if (!granary || !b->is_valid()) {
        return 0;
    }
    for (int i = 0; i < 8; i++) {
        if (granary->is_emptying((e_resource)resource)) {
            return 1;
        }
        building_storage_cycle_resource_state(granary->storage_id(), (e_resource)resource, false);
    }
    return granary->is_emptying((e_resource)resource) ? 1 : 0;
}
ANK_FUNCTION_2(__test_granary_set_emptying);

static int __test_granary_worker_task(int bid) {
    building* b = building_get(bid);
    auto* granary = b ? b->dcast_granary() : nullptr;
    if (!granary || !b->is_valid()) {
        return -1;
    }
    return (int)granary->determine_worker_task().status;
}
ANK_FUNCTION_1(__test_granary_worker_task);

static int __test_granary_worker_task_resource(int bid) {
    building* b = building_get(bid);
    auto* granary = b ? b->dcast_granary() : nullptr;
    if (!granary || !b->is_valid()) {
        return 0;
    }
    return (int)granary->determine_worker_task().resource;
}
ANK_FUNCTION_1(__test_granary_worker_task_resource);

static int __test_granary_worker_task_amount(int bid) {
    building* b = building_get(bid);
    auto* granary = b ? b->dcast_granary() : nullptr;
    if (!granary || !b->is_valid()) {
        return 0;
    }
    return granary->determine_worker_task().amount;
}
ANK_FUNCTION_1(__test_granary_worker_task_amount);

static void __test_granary_spawn_figure(int bid) {
    building* b = building_get(bid);
    auto* granary = b ? b->dcast_granary() : nullptr;
    if (!granary || !b->is_valid()) {
        return;
    }
    granary->spawn_figure();
}
ANK_FUNCTION_1(__test_granary_spawn_figure);

static void __test_granary_update_graphic(int bid) {
    building* b = building_get(bid);
    auto* granary = b ? b->dcast_granary() : nullptr;
    if (!granary || !b->is_valid()) {
        return;
    }
    granary->update_graphic();
}
ANK_FUNCTION_1(__test_granary_update_graphic);

static int __test_granary_find_getting_source(int bid) {
    building* b = building_get(bid);
    auto* granary = b ? b->dcast_granary() : nullptr;
    if (!granary || !b->is_valid()) {
        return 0;
    }
    g_city.resource.calculate_stocks();
    return granary->find_storage_for_getting().building_id;
}
ANK_FUNCTION_1(__test_granary_find_getting_source);

static int __test_granary_set_resource(int bid, int resource, int amount) {
    building* b = building_get(bid);
    auto* granary = b ? b->dcast_granary() : nullptr;
    if (!granary || !b->is_valid() || amount < 0 || !resource_is_food((e_resource)resource)) {
        return 0;
    }
    auto& stored = granary->runtime_data().resource_stored;
    const e_resource res = (e_resource)resource;
    const int old_amount = stored[res];
    stored[res] = static_cast<short>(amount);
    stored[RESOURCE_NONE] = static_cast<short>(stored[RESOURCE_NONE] + old_amount - amount);
    if (stored[RESOURCE_NONE] < 0) {
        stored[RESOURCE_NONE] = 0;
    }
    return 1;
}
ANK_FUNCTION_3(__test_granary_set_resource);

static int __test_granary_clear_allowed_food(int bid, int food_index) {
    building* b = building_get(bid);
    auto* granary = b ? b->dcast_granary() : nullptr;
    if (!granary || !b->is_valid() || food_index < 0 || food_index >= INVENTORY_MAX_FOOD) {
        return 0;
    }
    e_resource res = g_city.allowed_foods(food_index);
    if (res == RESOURCE_NONE) {
        return 0;
    }
    granary->runtime_data().resource_stored[res] = 0;
    return 1;
}
ANK_FUNCTION_2(__test_granary_clear_allowed_food);

static int __test_city_allowed_food(int food_index) {
    if (food_index < 0 || food_index >= INVENTORY_MAX_FOOD) {
        return 0;
    }
    return (int)g_city.allowed_foods(food_index);
}
ANK_FUNCTION_1(__test_city_allowed_food);

static int __test_set_allowed_food(int food_index, int resource) {
    if (food_index < 0 || food_index >= INVENTORY_MAX_FOOD) {
        return 0;
    }
    g_city.set_allowed_food(food_index, (e_resource)resource);
    // Refresh bazaar slot types so accept toggles / display match the new foods.
    buildings_valid_do(
      [](building& b) {
          if (auto* bazaar = b.dcast_bazaar()) {
              bazaar->on_post_load();
          }
      },
      BUILDING_BAZAAR);
    return 1;
}
ANK_FUNCTION_2(__test_set_allowed_food);

static int __test_city_recalc_granary_stored(int resource) {
    g_city.resource.calculate_available_food();
    return (int)g_city.resource.granary_stored((e_resource)resource);
}
ANK_FUNCTION_1(__test_city_recalc_granary_stored);

static int __test_food_mill_add_resource(int bid, int resource, int amount) {
    building* b = building_get(bid);
    auto* mill = b ? b->dcast_food_mill() : nullptr;
    if (!mill || !b->is_valid() || amount <= 0) {
        return 0;
    }
    return mill->add_resource((e_resource)resource, amount, /*force*/ true) >= 0 ? 1 : 0;
}
ANK_FUNCTION_3(__test_food_mill_add_resource);

static int __test_food_mill_amount(int bid, int resource) {
    building* b = building_get(bid);
    auto* mill = b ? b->dcast_food_mill() : nullptr;
    if (!mill || !b->is_valid()) {
        return -1;
    }
    return mill->amount((e_resource)resource);
}
ANK_FUNCTION_2(__test_food_mill_amount);

static int __test_food_mill_variety(int bid) {
    building* b = building_get(bid);
    auto* mill = b ? b->dcast_food_mill() : nullptr;
    if (!mill || !b->is_valid()) {
        return -1;
    }
    return mill->food_variety();
}
ANK_FUNCTION_1(__test_food_mill_variety);

static int __test_food_mill_total_stored(int bid) {
    building* b = building_get(bid);
    auto* mill = b ? b->dcast_food_mill() : nullptr;
    if (!mill || !b->is_valid()) {
        return -1;
    }
    return mill->total_stored();
}
ANK_FUNCTION_1(__test_food_mill_total_stored);

static int __test_food_mill_freespace(int bid) {
    building* b = building_get(bid);
    auto* mill = b ? b->dcast_food_mill() : nullptr;
    if (!mill || !b->is_valid()) {
        return -1;
    }
    return mill->freespace();
}
ANK_FUNCTION_1(__test_food_mill_freespace);

static int __test_food_mill_set_getting(int bid, int resource) {
    building* b = building_get(bid);
    auto* mill = b ? b->dcast_food_mill() : nullptr;
    if (!mill || !b->is_valid()) {
        return 0;
    }
    for (int i = 0; i < 8; i++) {
        if (mill->is_getting((e_resource)resource)) {
            return 1;
        }
        building_storage_cycle_resource_state(mill->storage_id(), resource, false);
    }
    return mill->is_getting((e_resource)resource) ? 1 : 0;
}
ANK_FUNCTION_2(__test_food_mill_set_getting);

static int __test_food_mill_find_getting_source(int bid) {
    building* b = building_get(bid);
    auto* mill = b ? b->dcast_food_mill() : nullptr;
    if (!mill || !b->is_valid()) {
        return 0;
    }
    g_city.resource.calculate_stocks();
    return mill->find_storage_for_getting().building_id;
}
ANK_FUNCTION_1(__test_food_mill_find_getting_source);

static int __test_food_mill_spawn_figure(int bid) {
    building* b = building_get(bid);
    auto* mill = b ? b->dcast_food_mill() : nullptr;
    if (!mill || !b->is_valid()) {
        return -1;
    }
    b->has_road_access = true;
    if (b->road_network_id <= 0) {
        b->road_network_id = 1;
    }
    if (b->distance_from_entry <= 0) {
        b->distance_from_entry = 1;
    }
    // gettable stocks skip buildings with distance_from_entry <= 0 — ensure sources count.
    buildings_valid_do(
      [](building& src) {
          if (!src.has_road_access) {
              src.has_road_access = true;
          }
          if (src.road_network_id <= 0) {
              src.road_network_id = 1;
          }
          if (src.distance_from_entry <= 0) {
              src.distance_from_entry = 1;
          }
      },
      {BUILDING_GRANARY, BUILDING_STORAGE_YARD});
    g_city.resource.calculate_stocks();
    const bool before = mill->has_figure_of_type(0, FIGURE_STORAGEYARD_CART);
    mill->spawn_figure();
    const bool after = mill->has_figure_of_type(0, FIGURE_STORAGEYARD_CART);
    if (before) {
        return 0;
    }
    return after ? 1 : 0;
}
ANK_FUNCTION_1(__test_food_mill_spawn_figure);

static int __test_granary_touches_network(int bid, int road_network_id) {
    building* b = building_get(bid);
    if (!b || !b->is_valid() || !b->dcast_granary()) {
        return 0;
    }
    return building_granary_touches_network(*b, road_network_id) ? 1 : 0;
}
ANK_FUNCTION_2(__test_granary_touches_network);

static int __test_granary_access_on_network(int bid, int road_network_id, int prefer_grid_offset) {
    building* b = building_get(bid);
    if (!b || !b->is_valid() || !b->dcast_granary()) {
        return -1;
    }
    tile2i prefer = tile2i::invalid;
    if (prefer_grid_offset >= 0) {
        prefer = tile2i(prefer_grid_offset);
    }
    tile2i access = building_granary_access_on_network(*b, road_network_id, prefer);
    return access.valid() ? access.grid_offset() : -1;
}
ANK_FUNCTION_3(__test_granary_access_on_network);

static void __test_update_farms() {
    building_industry_update_farms();
}
ANK_FUNCTION(__test_update_farms);

static void __test_link_producer_for_delivery(int producer_id, int storage_id) {
    building* producer = building_get(producer_id);
    building* storage = building_get(storage_id);
    if (!producer || !storage) {
        return;
    }

    producer->has_road_access = true;
    if (!producer->road_access.valid()) {
        producer->road_access = producer->tile;
    }
    if (producer->distance_from_entry <= 0) {
        producer->distance_from_entry = 1;
    }

    // Match map network under access tile when present (predict prefers map net).
    int net = map_road_network_get(producer->road_access);
    if (net <= 0) {
        net = producer->road_network_id > 0 ? producer->road_network_id : 1;
    }
    producer->road_network_id = net;

    for (building* part = storage->main(); part;) {
        part->road_network_id = net;
        part->distance_from_entry = producer->distance_from_entry;
        part->has_road_access = true;
        if (!part->road_access.valid()) {
            part->road_access = part->tile;
        }
        if (part->max_workers > 0) {
            part->num_workers = part->max_workers;
        } else {
            part->num_workers = std::max(1, (int)part->num_workers);
        }
        if (!part->has_next()) {
            break;
        }
        part = part->next();
    }
}
ANK_FUNCTION_2(__test_link_producer_for_delivery);

static int __test_predict_delivery(int bid) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    delivery_path_query q = building_predict_delivery(*b);
    if (!q.to) {
        return 0;
    }
    building* dest = building_get(q.to);
    return dest && dest->is_valid() ? dest->main()->id : q.to;
}
ANK_FUNCTION_1(__test_predict_delivery);

static int __test_predict_delivery_kind(int bid) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }
    delivery_path_query q = building_predict_delivery(*b);
    return (int)q.kind;
}
ANK_FUNCTION_1(__test_predict_delivery_kind);

static int __test_predict_delivery_reason(int bid) {
    building* b = building_get(bid);
    if (!b || !b->is_valid()) {
        return -1;
    }
    delivery_path_query q = building_predict_delivery(*b);
    return (int)q.reason;
}
ANK_FUNCTION_1(__test_predict_delivery_reason);

static void __test_storage_toggle_empty_all(int bid) {
    building* b = building_get(bid);
    if (!b) {
        return;
    }
    building* m = b->main();
    if (!m || m->storage_id <= 0) {
        return;
    }
    building_storage_toggle_empty_all(m->storage_id);
}
ANK_FUNCTION_1(__test_storage_toggle_empty_all);

void __test_set_osiris_double_farm_yield(int active) {
    g_city.religion.osiris_double_farm_yield_days = active ? 1 : 0;
    g_city.religion.osiris_double_farm_yield_used = false;
}
ANK_FUNCTION_1(__test_set_osiris_double_farm_yield)

void __test_farm_harvest_and_clear_osiris(int bid) {
    building* b = building_get(bid);
    building_farm* farm = b ? b->dcast_farm() : nullptr;
    if (!farm) {
        return;
    }
    b->has_road_access = true;
    farm->spawn_figure_harvests();
    if (g_city.religion.osiris_double_farm_yield_used) {
        g_city.religion.osiris_double_farm_yield_days = 0;
        g_city.religion.osiris_double_farm_yield_used = false;
    }
}
ANK_FUNCTION_1(__test_farm_harvest_and_clear_osiris)

int __test_farm_food_warning() {
    return building_farm::food_warning();
}
ANK_FUNCTION(__test_farm_food_warning)
