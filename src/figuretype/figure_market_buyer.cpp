#include "figure_market_buyer.h"

#include "market.h"
#include "building/building_house.h"
#include "building/building_granary.h"
#include "building/building_food_mill.h"
#include "window/building/figures.h"
#include "core/log.h"
#include "building/building_storage_yard.h"
#include "building/building_bazaar.h"
#include "city/city_recorded_paths.h"
#include "figure/combat.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "game/resource.h"
#include "game/game.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/ui.h"
#include "graphics/image_groups.h"
#include "game/game_config.h"
#include "grid/building.h"
#include "city/city.h"
#include "core/object_property.h"
#include "js/js_game.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_market_buyer);

namespace {

int og_stock_loads(int stock, int max_loads) {
    int loads = 0;
    for (int level = max_loads; level >= 1; level--) {
        if (stock >= level * 100) {
            loads = level;
            break;
        }
    }
    if (!loads) {
        loads = stock > 0 ? 1 : 0;
    }
    return loads;
}

int og_buyer_loads(int want, int available) {
    if (want < 1) {
        return 0;
    }
    int max_want = want / 100 + 1;
    int loads = available;
    if (max_want < loads) {
        loads = max_want;
    }
    return loads < 1 ? 0 : loads;
}

e_resource inventory_good_resource(int inv) {
    switch (inv) {
    case INVENTORY_GOOD1: return RESOURCE_POTTERY;
    case INVENTORY_GOOD2: return RESOURCE_LUXURY_GOODS;
    case INVENTORY_GOOD3: return RESOURCE_LINEN;
    case INVENTORY_GOOD4: return RESOURCE_BEER;
    default: return RESOURCE_NONE;
    }
}

void handoff_arrival_path(figure &f, building *dest) {
    if (dest && f.trail_path_id && dest->params().flags.keeps_visitor_paths) {
        building *main = dest->main();
        if (main) {
            g_recorded_paths.handoff_to_building(f, main->id);
        }
    }
    if (!f.trail_path_id) {
        figure_recorded_path_acquire(f);
    }
}

} // namespace

bool figure_market_buyer::use_og_trip() {
    return !game_features::gameplay_change_bazaar_multi_buyers.to_bool();
}

void figure_market_buyer::init_og_trip(const int8_t items[4], bool food) {
    auto &d = runtime_data();
    d.is_food_trip = food ? 1 : 0;
    d.storages_visited = 0;
    for (int i = 0; i < 4; i++) {
        d.resources[i] = items[i];
        d.amounts_bought[i] = 0;
    }
    for (int i = 0; i < 3; i++) {
        d.visited_storage_ids[i] = 0;
    }
    for (int i = 0; i < 4; i++) {
        if (items[i] >= 0) {
            base.collecting_item_id = (uint8_t)items[i];
            break;
        }
    }
}

bool figure_market_buyer::og_has_bought() const {
    const auto &d = runtime_data();
    for (int i = 0; i < 4; i++) {
        if (d.amounts_bought[i] != 0) {
            return true;
        }
    }
    return false;
}

void figure_market_buyer::og_return_or_die() {
    if (og_has_bought()) {
        advance_action(ACTION_146_MARKET_BUYER_RETURNING);
        return;
    }
    poof();
}

void figure_market_buyer::og_go_to_storage(int storage_id) {
    building *b = building_get(storage_id);
    if (!b || !b->id) {
        og_return_or_die();
        return;
    }
    base.set_destination(storage_id);
    advance_action(ACTION_145_MARKET_BUYER_GOING_TO_STORAGE);
}

void figure_market_buyer::figure_before_action() {
    building *b = home();
    const bool in_buyer_slot = b->has_figure(BUILDING_SLOT_MARKET_BUYER, id())
        || b->has_figure(BUILDING_SLOT_MARKET_BUYER_2, id());
    if (b->state != BUILDING_STATE_VALID || !in_buyer_slot) {
        poof();
    }
}

void figure_market_buyer::apply_return_home_spawn_cooldown() {
    building *h = home();
    if (!h) {
        return;
    }

    // Cooldown only when this is the last active buyer (OG dual food+goods, and enhanced multi).
    int others = 0;
    auto count_other = [&](e_building_slot slot) {
        if (!h->has_figure_of_type(slot, FIGURE_MARKET_BUYER)
            || h->get_figure_id(slot) == id()) {
            return;
        }
        if (building_bazaar::is_active_market_buyer(h->get_figure(slot))) {
            others++;
        }
    };
    count_other(BUILDING_SLOT_MARKET_BUYER);
    count_other(BUILDING_SLOT_MARKET_BUYER_2);
    if (others == 0) {
        h->figure_spawn_delay = -3;
    }
}

void figure_market_buyer::figure_action() {
    bool ok = false;
    switch (action_state()) {
    case ACTION_144_MARKET_BUYER_CREATE:
        break;

    case ACTION_145_MARKET_BUYER_GOING_TO_STORAGE:
        if (use_og_trip()) {
            // Stay in 145 on arrival so og_at_storage can chain another storage.
            ok = do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS,
                                 ACTION_145_MARKET_BUYER_GOING_TO_STORAGE,
                                 ACTION_146_MARKET_BUYER_RETURNING);
            if (ok) {
                handoff_arrival_path(base, destination());
                og_at_storage();
            }
            break;
        }

        ok = do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, ACTION_146_MARKET_BUYER_RETURNING);
        if (ok) {
            building *dest = destination();
            bool took = false;
            if (base.collecting_item_id > 3) {
                took = take_resource_from_storageyard(destination());
            } else {
                took = take_food_from_storage(home(), destination());
            }
            handoff_arrival_path(base, dest);
            if (!took) {
                advance_action(ACTION_146_MARKET_BUYER_RETURNING);
            }
        }
        break;

    case ACTION_146_MARKET_BUYER_RETURNING:
        if (base.do_returnhome()) {
            building *h = home();
            if (h && h->params().flags.keeps_visitor_paths) {
                building *main = h->main();
                if (main) {
                    g_recorded_paths.handoff_to_building(base, main->id);
                }
            }
            apply_return_home_spawn_cooldown();
        }
        break;

    case ACTION_150_MARKET_BUYER_ATTACKED:
        kill();
    }
}

namespace {

void distribute_good_remake(building *b, building *market, int stock_wanted, int inventory_resource) {
    building_bazaar *bazaar = market->dcast_bazaar();
    if (!bazaar) {
        return;
    }

    auto house = b->dcast_house();
    if (!house) {
        return;
    }

    auto &housed = house->runtime_data();
    int amount_wanted = stock_wanted - housed.inventory[inventory_resource];

    auto &d = bazaar->runtime_data();
    if (d.inventory[inventory_resource].value > 0 && amount_wanted > 0) {
        if (amount_wanted <= d.inventory[inventory_resource].value) {
            housed.inventory[inventory_resource] += amount_wanted;
            d.inventory[inventory_resource].value -= amount_wanted;
        } else {
            housed.inventory[inventory_resource] += d.inventory[inventory_resource].value;
            d.inventory[inventory_resource].value = 0;
        }
    }
}

// OG deliver_good: up to need*2 - have (need×4 first if house size > 1); sets demand flag to 10.
void distribute_good_og(building_bazaar &bazaar, building_house &house, int need, short &demand_flag, int inventory_resource) {
    if (house.base.size > 1) {
        need <<= 2;
    }
    if (!need) {
        return;
    }

    if (game_features::gameplay_change_bazaar_demand_from_trader.to_bool()) {
        demand_flag = 10;
    }
    auto &marketd = bazaar.runtime_data();
    int stock = marketd.inventory[inventory_resource].value;
    if (stock <= 0) {
        return;
    }

    auto &housed = house.runtime_data();
    int have = housed.inventory[inventory_resource];
    int want = need * 2 - have;
    if (want <= 0) {
        return;
    }

    if (want > stock) {
        housed.inventory[inventory_resource] = (uint16_t)(have + stock);
        marketd.inventory[inventory_resource].value = 0;
    } else {
        housed.inventory[inventory_resource] = (uint16_t)(have + want);
        marketd.inventory[inventory_resource].value -= (uint16_t)want;
    }
}

bool market_food_is_whole_load(e_resource resource) {
    // OG food_index 0 (grain) and 6 (fish) take the full amount; others half.
    return resource == RESOURCE_GRAIN || resource == RESOURCE_FISH;
}

void distribute_market_resources_remake(building *b, building *market) {
    building_bazaar *bazaar = market->dcast_bazaar();
    if (!bazaar) {
        return;
    }

    auto house = b->dcast_house();
    if (!house) {
        return;
    }

    auto &marketd = bazaar->runtime_data();
    auto &housed = house->runtime_data();
    const auto &house_model = house->model();
    int level = house->house_level();
    if (level < HOUSE_PALATIAL_ESTATE) {
        level++;
    }

    int max_food_stocks = house_model.food_storage_multiplier * housed.highest_population;
    int food_types_stored_max = 0;
    for (int i = INVENTORY_MIN_FOOD; i < INVENTORY_MAX_FOOD; i++) {
        if (housed.foods[i] >= max_food_stocks)
            food_types_stored_max++;
    }

    const model_house &model = building_house::get_model(level);
    if (model.food_types > food_types_stored_max) {
        for (int i = INVENTORY_MIN_FOOD; i < INVENTORY_MAX_FOOD; i++) {
            if (housed.foods[i] >= max_food_stocks) {
                continue;
            }

            if (marketd.inventory[i].value >= max_food_stocks) {
                housed.foods[i] += max_food_stocks;
                marketd.inventory[i].value -= max_food_stocks;
                break;
            } else if (marketd.inventory[i].value) {
                housed.foods[i] += marketd.inventory[i].value;
                marketd.inventory[i].value = 0;
                break;
            }
        }
    }

    int goods_no = 8;
    if (!!game_features::gameplay_houses_stockpile_more) {
        goods_no = 16;
    }

    int aproximated_level = housed.highest_population / 10;
    const bool demand_on_visit = game_features::gameplay_change_bazaar_demand_from_trader.to_bool();
    if (model.pottery) {
        if (demand_on_visit) {
            marketd.pottery_demand = 10;
        }
        distribute_good_remake(b, market, goods_no * aproximated_level * model.pottery, INVENTORY_GOOD1);
    }

    if (model.jewelry) {
        if (demand_on_visit) {
            marketd.luxurygoods_demand = 10;
        }
        distribute_good_remake(b, market, goods_no * aproximated_level * model.jewelry, INVENTORY_GOOD2);
    }

    if (model.linen) {
        if (demand_on_visit) {
            marketd.linen_demand = 10;
        }
        distribute_good_remake(b, market, goods_no * aproximated_level * model.linen, INVENTORY_GOOD3);
    }

    if (model.beer) {
        if (demand_on_visit) {
            marketd.beer_demand = 10;
        }
        distribute_good_remake(b, market, goods_no * aproximated_level * model.beer, INVENTORY_GOOD4);
    }
}

void distribute_market_resources_og(building *b, building *market) {
    building_bazaar *bazaar = market->dcast_bazaar();
    if (!bazaar) {
        return;
    }

    auto house = b->dcast_house();
    if (!house) {
        return;
    }

    auto &marketd = bazaar->runtime_data();
    auto &housed = house->runtime_data();
    int level = house->house_level();
    if (level < HOUSE_PALATIAL_ESTATE) {
        level++;
    }

    const model_house &model = building_house::get_model(level);
    const int population = house->house_population();

    int types_left = model.food_types;
    if (types_left > 0 && types_left < 4) {
        types_left++;
    }

    for (int i = INVENTORY_MIN_FOOD; i < INVENTORY_MAX_FOOD; i++) {
        e_resource resource = g_city.allowed_foods(i);
        if (!resource) {
            continue;
        }

        int stock = marketd.inventory[i].value;
        if (stock <= 0 || !types_left) {
            continue;
        }

        int have = housed.foods[i];
        int amount = population * 6 - have;
        if (population * 2 < amount) {
            amount = population * 2;
        }
        if (amount <= 0) {
            continue;
        }

        const bool whole = market_food_is_whole_load(resource);
        if (stock >= amount) {
            if (!whole) {
                amount >>= 1;
            }
            housed.foods[i] = (uint16_t)(have + amount);
            marketd.inventory[i].value -= (uint16_t)amount;
        } else if (!whole && stock >= (amount >> 1)) {
            amount >>= 1;
            housed.foods[i] = (uint16_t)(have + amount);
            marketd.inventory[i].value -= (uint16_t)amount;
        } else {
            housed.foods[i] = (uint16_t)(have + stock);
            marketd.inventory[i].value = 0;
        }
        types_left--;
    }

    distribute_good_og(*bazaar, *house, model.pottery, marketd.pottery_demand, INVENTORY_GOOD1);
    distribute_good_og(*bazaar, *house, model.jewelry, marketd.luxurygoods_demand, INVENTORY_GOOD2);
    distribute_good_og(*bazaar, *house, model.linen, marketd.linen_demand, INVENTORY_GOOD3);
    distribute_good_og(*bazaar, *house, model.beer, marketd.beer_demand, INVENTORY_GOOD4);
}

} // namespace

void distribute_market_resources(building *b, building *market) {
    if (game_features::gameplay_change_market_distribute_remake.to_bool()) {
        distribute_market_resources_remake(b, market);
        return;
    }
    distribute_market_resources_og(b, market);
}


int figure_market_buyer::og_buy_food_slot(int index, building *storage_b) {
    auto &d = runtime_data();
    const int slot = d.resources[index];
    if (slot < INVENTORY_FOOD1 || slot > INVENTORY_FOOD4) {
        return 0;
    }

    e_resource resource = g_city.allowed_foods(slot);
    if (!resource || g_city.resource.is_stockpiled(resource)) {
        return 0;
    }

    building_bazaar *bazaar = home()->dcast_bazaar();
    building_storage *storage = storage_b->dcast_storage();
    if (!bazaar || !storage) {
        return 0;
    }

    const int max_stock = slot == INVENTORY_FOOD1 ? 800 : 600;
    const int want = max_stock - bazaar->runtime_data().inventory[slot].value - d.amounts_bought[index];
    if (want < 1) {
        return 0;
    }

    const int loads = og_buyer_loads(want, og_stock_loads(storage->amount(resource), 8));
    if (loads <= 0) {
        return 0;
    }

    storage->remove_resource(resource, loads * 100);
    base.collecting_item_id = (uint8_t)slot;
    int leader = id();
    for (int i = 0; i < 8 && (i == 0 || i < loads); i++) {
        leader = create_delivery_boy(leader, slot);
    }
    d.amounts_bought[index] = (uint16_t)(d.amounts_bought[index] + loads * 100);
    return 1;
}

int figure_market_buyer::og_buy_goods_slot(int index, building *storage_b) {
    auto &d = runtime_data();
    const int slot = d.resources[index];
    e_resource resource = inventory_good_resource(slot);
    if (!resource || g_city.resource.is_stockpiled(resource)) {
        return 0;
    }

    building_bazaar *bazaar = home()->dcast_bazaar();
    building_storage_yard *warehouse = storage_b->dcast_storage_yard();
    if (!bazaar || !warehouse) {
        return 0;
    }

    const int want = 400 - bazaar->runtime_data().inventory[slot].value - d.amounts_bought[index];
    if (want < 1) {
        return 0;
    }

    const int loads = og_buyer_loads(want, og_stock_loads(warehouse->amount(resource), 4));
    if (loads <= 0) {
        return 0;
    }

    warehouse->remove_resource(resource, loads * 100);
    base.collecting_item_id = (uint8_t)slot;
    int leader = id();
    for (int i = 0; i < 4 && (i == 0 || i < loads); i++) {
        leader = create_delivery_boy(leader, slot);
    }
    d.amounts_bought[index] = (uint16_t)(d.amounts_bought[index] + loads * 100);
    return 1;
}

void figure_market_buyer::og_next_storage() {
    auto &d = runtime_data();
    if (d.storages_visited >= 3) {
        og_return_or_die();
        return;
    }

    building_bazaar *bazaar = home()->dcast_bazaar();
    if (!bazaar) {
        og_return_or_die();
        return;
    }

    int wants[4] = {};
    for (int i = 0; i < 4; i++) {
        const int item = d.resources[i];
        wants[i] = 0;
        if (item < 0) {
            continue;
        }
        const int max = d.is_food_trip ? (item == INVENTORY_FOOD1 ? 800 : 600) : 400;
        wants[i] = max - bazaar->runtime_data().inventory[item].value - d.amounts_bought[i];
    }

    auto best_slot = [&]() -> int {
        int best = -1;
        int max_loads = 0;
        for (int i = 0; i < 4; i++) {
            if (wants[i] / 100 > max_loads) {
                best = i;
                max_loads = wants[i] / 100;
            }
        }
        return best;
    };

    int nearest[INVENTORY_MAX] = {};
    bazaar->update_og_buyer_storages(nearest);

    int index = best_slot();
    while (index != -1) {
        const int item = d.resources[index];
        if (item >= 0 && item < INVENTORY_MAX && nearest[item] > 0) {
            og_go_to_storage(nearest[item]);
            return;
        }
        wants[index] = 0;
        index = best_slot();
    }
    og_return_or_die();
}

void figure_market_buyer::og_at_storage() {
    building *storage_b = destination();
    if (!storage_b || !storage_b->id) {
        og_return_or_die();
        return;
    }

    auto &d = runtime_data();
    for (int i = 0; i < 4; i++) {
        const int item = d.resources[i];
        if (item < 0) {
            continue;
        }
        if (item <= INVENTORY_FOOD4) {
            og_buy_food_slot(i, storage_b);
        } else if (item <= INVENTORY_GOOD4) {
            og_buy_goods_slot(i, storage_b);
        }
    }

    if (d.storages_visited < 3) {
        d.visited_storage_ids[d.storages_visited] = (uint16_t)storage_b->id;
    }
    d.storages_visited++;
    og_next_storage();
}

bool figure_market_buyer::take_resource_from_storageyard(building* b) {
    building_storage_yard *warehouse = b->dcast_storage_yard();
    if (!warehouse) {
        return false;
    }

    e_resource resource = inventory_good_resource(base.collecting_item_id);
    if (!resource) {
        return false;
    }

    int stored = warehouse->amount(resource);
    int num_loads = std::min<int>(stored, 200);

    if (num_loads <= 0) {
        return false;
    }

    warehouse->remove_resource(resource, num_loads);

    // create delivery boys
    int boy1 = create_delivery_boy(id());
    if (num_loads > 100) {
        create_delivery_boy(boy1);
    }

    return true;
}

int provide_market_goods(building* market, tile2i tile) {
    int serviced = 0;
    grid_area area = map_grid_get_area(tile, 1, 2);

    map_grid_area_foreach(area, [&] (tile2i tile) {
        int grid_offset = tile.grid_offset();
        building_id bid = map_building_at(grid_offset);
        auto house = building_get(bid)->dcast_house();
        if (house && house->house_population() > 0) {
            distribute_market_resources(&house->base, market);
            serviced++;
        }
    });
    return serviced;
}

int figure_market_buyer::create_delivery_boy(int leader_id, int inventory_slot) {
    figure* boy = figure_create(FIGURE_DELIVERY_BOY, tile(), 0);
    boy->leading_figure_id = leader_id;
    boy->collecting_item_id = inventory_slot >= 0 ? (uint8_t)inventory_slot : base.collecting_item_id;
    boy->set_home(base.homeID());
    return boy->id;
}

int figure_market_buyer::provide_service() {
    int houses_serviced = 0;
    if (!game_features::gameplay_buyers_dont_distribute) {
        houses_serviced = provide_market_goods(home(), tile());
    }

    return houses_serviced;
}

bvariant figure_market_buyer::get_property(const xstring &domain, const xstring &name) const {
    if (domain == tags().figure && name == tags().resource) {
        return bvariant(base.collecting_item_id);
    }

    return figure_impl::get_property(domain, name);
}

xstring figure_market_buyer::action_tip() const {
    if (action_state() == ACTION_145_MARKET_BUYER_GOING_TO_STORAGE) {
        return "#market_buyer_collecting";
    } else if (action_state() == ACTION_146_MARKET_BUYER_RETURNING) {
        return "#market_buyer_returning_to";
    }

    return "#market_buyer_idle";
}

void figure_market_buyer::acquire_attack() {
    kill();
}

int figure_market_buyer::take_food_from_storage(building* market, building* b) {
    building_bazaar *bazaar = market->dcast_bazaar();
    if (!bazaar) {
        return 0;
    }

    building_storage *storage = b->dcast_storage();
    if (!storage) {
        return 0;
    }

    auto take_one_type = [&](int inv) -> int {
        if (inv < INVENTORY_FOOD1 || inv > INVENTORY_FOOD4) {
            return 0;
        }
        e_resource resource = g_city.allowed_foods(inv);
        if (!resource) {
            return 0;
        }

        uint16_t market_units = bazaar->runtime_data().inventory[inv].value;
        int storage_units = storage->amount(resource);

        const int max_units = (inv == 0 ? 700 : 600) - market_units;
        const int max_num_loads = max_units / 100;
        const int num_loads = std::clamp(storage_units / 100, 0, max_num_loads);

        if (num_loads <= 0) {
            return 0;
        }

        storage->remove_resource(resource, 100 * num_loads);

        base.collecting_item_id = (uint8_t)inv;
        int previous_boy = id();
        for (int i = 0; i < num_loads; i++) {
            previous_boy = create_delivery_boy(previous_boy);
        }
        return 1;
    };

    auto pick_next_understocked = [&](const bool *taken_slots) -> int {
        int best = -1;
        int min_stock = 999;
        const auto &pick_food_below = bazaar->current_params().pick_food_below;
        for (int foodi = INVENTORY_FOOD1; foodi <= INVENTORY_FOOD4; ++foodi) {
            if ((taken_slots && taken_slots[foodi]) || !bazaar->idx_accepted(foodi)) {
                continue;
            }
            e_resource res = g_city.allowed_foods(foodi);
            if (!res || storage->amount(res) < 100) {
                continue;
            }
            const int stock = bazaar->runtime_data().inventory[foodi].value;
            if (stock > pick_food_below[foodi]) {
                continue;
            }
            if (stock < min_stock) {
                min_stock = stock;
                best = foodi;
            }
        }
        return best;
    };

    const int primary = base.collecting_item_id;
    bool taken[INVENTORY_MAX_FOOD] = {};
    int taken_types = 0;

    if (take_one_type(primary)) {
        if (primary >= INVENTORY_FOOD1 && primary <= INVENTORY_FOOD4) {
            taken[primary] = true;
        }
        taken_types = 1;
    } else {
        // Mill only: primary may be gone by arrival — try another understocked food.
        // Granary/SY keep single-type OG behavior on primary fail.
        if (!b->dcast_food_mill()) {
            return 0;
        }
        const int alt = pick_next_understocked(nullptr);
        if (alt < 0 || !take_one_type(alt)) {
            return 0;
        }
        taken[alt] = true;
        taken_types = 1;
    }

    // FM3: at a food mill, loop additional understocked foods up to desired variety.
    auto *mill = b->dcast_food_mill();
    if (!mill || !game_features::gameplay_enhanced_food_mill.to_bool()) {
        return 1;
    }

    const int desired = bazaar->desired_variety();
    while (taken_types < desired) {
        const int best = pick_next_understocked(taken);
        if (best < 0 || !take_one_type(best)) {
            break;
        }
        taken[best] = true;
        taken_types++;
    }

    return 1;
}
