#include "building_bazaar.h"

#include "figure/figure.h"
#include "building/building_type.h"
#include "building/building_storage_yard.h"
#include "building/building_food_mill.h"
#include "figuretype/figure_market_buyer.h"
#include "figuretype/figure_market_trader.h"
#include "building/building_house.h"
#include "graphics/elements/ui.h"
#include "city/city.h"
#include "city/city_labor.h"
#include "city/constants.h"
#include "core/calc.h"
#include "game/resource.h"
#include "game/game_config.h"
#include "scenario/scenario.h"
#include "grid/desirability.h"
#include "grid/building_tiles.h"
#include "grid/terrain.h"
#include "grid/routing/routing.h"
#include "graphics/image.h"
#include "building/building_granary.h"
#include "graphics/graphics.h"
#include "game/game.h"
#include "widget/city/ornaments.h"
#include "js/js_game.h"
#include <numeric>
#include <algorithm>

BUILDING_RUNTIME_DATA_IMPL(building_bazaar)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_bazaar);

namespace {
constexpr e_building_slot k_buyer_slots[] = {
    BUILDING_SLOT_MARKET_BUYER,
    BUILDING_SLOT_MARKET_BUYER_2,
};

bool inventory_in_group(int inv, e_bazaar_fetch_group group) {
    if (group == e_bazaar_fetch_all) {
        return true;
    }
    if (group == e_bazaar_fetch_foods) {
        return inv >= INVENTORY_FOOD1 && inv <= INVENTORY_FOOD4;
    }
    return inv >= INVENTORY_GOOD1 && inv <= INVENTORY_GOOD4;
}

bool is_excluded(int inv, const bool *exclude) {
    return exclude && inv >= 0 && inv < INVENTORY_MAX && exclude[inv];
}
} // namespace

struct resource_data {
    int building_id;
    int min_distance;
    int num_buildings;

    // Prefer food mill over granary/SY when both have stock (FM3).
    void update_food(int resource, building &b, int distance, int minimal_amount) {
        if (!resource) {
            return;
        }

        building_storage *storage = b.dcast_storage();
        if (!storage || storage->amount((e_resource)resource) < minimal_amount) {
            return;
        }

        const bool is_mill = b.type == BUILDING_FOOD_MILL;
        const bool cur_is_mill = building_id && building_get(building_id)->type == BUILDING_FOOD_MILL;

        num_buildings++;
        if (!building_id) {
            min_distance = distance;
            building_id = b.id;
            return;
        }
        if (is_mill && !cur_is_mill) {
            min_distance = distance;
            building_id = b.id;
            return;
        }
        if (!is_mill && cur_is_mill) {
            return;
        }
        if (distance < min_distance) {
            min_distance = distance;
            building_id = b.id;
        }
    }

    void update_good(e_resource resource, building &b, int distance) {
        if (g_city.resource.is_stockpiled(resource)) {
            return;
        }

        building_storage_yard *warehouse = b.dcast_storage_yard();
        if (!warehouse) {
            return;
        }

        if (warehouse->amount(resource) <= 0) {
            return;
        }

        num_buildings++;
        if (distance < min_distance) {
            min_distance = distance;
            building_id = b.id;
        }
    }
};

void scan_bazaar_storages(building_bazaar &bazaar, resource_data *resources, bool tick_demand) {
    std::fill(resources, resources + INVENTORY_MAX, resource_data{0, bazaar.current_params().max_search_distance, 0});
    const bool mill_enabled = game_features::gameplay_enhanced_food_mill.to_bool();
    buildings_valid_do([&](building &b) {
        if (!b.has_road_access) {
            return;
        }

        if (b.params().flags.perimeter_access) {
            if (!building_granary_touches_network(b, bazaar.base.road_network_id)) {
                return;
            }
        } else if (b.distance_from_entry <= 0 || b.road_network_id != bazaar.base.road_network_id) {
            return;
        }

        building_storage *s = b.dcast_storage();
        if (!s || !s->get_permission(BUILDING_STORAGE_PERMISSION_MARKET)) {
            return;
        }

        int distance = calc_maximum_distance(bazaar.base.tile, b.tile);
        if (distance >= bazaar.current_params().max_search_distance) {
            return;
        }

        if (b.type == BUILDING_FOOD_MILL) {
            if (!mill_enabled || b.num_workers <= 0 || g_scenario.kingdom_supplies_grain) {
                return;
            }

            const int minimal_amount = bazaar.current_params().minimal_pick_food_amount;
            resources[INVENTORY_FOOD1].update_food(g_city.allowed_foods(INVENTORY_FOOD1), b, distance, minimal_amount);
            resources[INVENTORY_FOOD2].update_food(g_city.allowed_foods(INVENTORY_FOOD2), b, distance, minimal_amount);
            resources[INVENTORY_FOOD3].update_food(g_city.allowed_foods(INVENTORY_FOOD3), b, distance, minimal_amount);
            resources[INVENTORY_FOOD4].update_food(g_city.allowed_foods(INVENTORY_FOOD4), b, distance, minimal_amount);

        } else if (b.dcast_granary() || b.type == BUILDING_GRANARY || b.type == BUILDING_GRANARY_UP) {
            if (g_scenario.kingdom_supplies_grain) {
                return;
            }

            const int minimal_amount = bazaar.current_params().minimal_pick_food_amount;
            resources[INVENTORY_FOOD1].update_food(g_city.allowed_foods(INVENTORY_FOOD1), b, distance, minimal_amount);
            resources[INVENTORY_FOOD2].update_food(g_city.allowed_foods(INVENTORY_FOOD2), b, distance, minimal_amount);
            resources[INVENTORY_FOOD3].update_food(g_city.allowed_foods(INVENTORY_FOOD3), b, distance, minimal_amount);
            resources[INVENTORY_FOOD4].update_food(g_city.allowed_foods(INVENTORY_FOOD4), b, distance, minimal_amount);

        } else if (b.type == BUILDING_STORAGE_YARD) {
            auto sy_food = [&](int inv) {
                e_resource res = g_city.allowed_foods(inv);
                if (!res || g_city.resource.is_stockpiled(res)) {
                    return;
                }
                // OG: bazaars take SY food only while that food is being imported.
                const e_trade_status st = g_city.resource.trade_status[res];
                if (st != TRADE_STATUS_IMPORT && st != TRADE_STATUS_IMPORT_AS_NEEDED) {
                    return;
                }
                resources[inv].update_food(res, b, distance, 1);
            };
            sy_food(INVENTORY_FOOD1);
            sy_food(INVENTORY_FOOD2);
            sy_food(INVENTORY_FOOD3);
            sy_food(INVENTORY_FOOD4);

            resources[INVENTORY_GOOD1].update_good(RESOURCE_POTTERY, b, distance);
            resources[INVENTORY_GOOD2].update_good(RESOURCE_LUXURY_GOODS, b, distance);
            resources[INVENTORY_GOOD3].update_good(RESOURCE_LINEN, b, distance);
            resources[INVENTORY_GOOD4].update_good(RESOURCE_BEER, b, distance);
        }
    }, {BUILDING_GRANARY, BUILDING_GRANARY_UP, BUILDING_STORAGE_YARD, BUILDING_FOOD_MILL});

    auto &d = bazaar.runtime_data();
    auto apply_good_demand = [&](short &demand, int inv) {
        if (!demand) {
            resources[inv].num_buildings = 0;
        } else if (tick_demand) {
            demand--;
        }
    };
    apply_good_demand(d.pottery_demand, INVENTORY_GOOD1);
    apply_good_demand(d.luxurygoods_demand, INVENTORY_GOOD2);
    apply_good_demand(d.linen_demand, INVENTORY_GOOD3);
    apply_good_demand(d.beer_demand, INVENTORY_GOOD4);
}

uint16_t building_bazaar::get_resource_amount(e_resource res) const {
    auto it = std::find_if(std::begin(runtime_data().inventory), std::end(runtime_data().inventory),
                           [res](const resource_value &rv) { return rv.type == res; });

    if (it != std::end(runtime_data().inventory)) {
        return it->value;
    }

    return 0;
}

int building_bazaar::max_food_stock() {
    const auto &d = runtime_data();
    auto it = std::max_element(d.inventory, d.inventory + INVENTORY_MAX_FOOD, [](const resource_value &a, const resource_value &b) { return a.value < b.value; });
    return it->value;
}

int building_bazaar::max_goods_stock() {
    const auto &d = runtime_data();
    auto it = std::max_element(d.inventory + INVENTORY_MIN_GOOD, d.inventory + INVENTORY_MAX_GOOD, [](const resource_value &a, const resource_value &b) { return a.value < b.value; });
    return it->value;
}

int building_bazaar::food_types_in_inventory() const {
    const auto &d = runtime_data();
    int count = 0;
    for (int foodi = INVENTORY_FOOD1; foodi <= INVENTORY_FOOD4; ++foodi) {
        if (d.inventory[foodi].type && d.inventory[foodi].value > 0) {
            count++;
        }
    }
    return count;
}

uint8_t building_bazaar::desired_variety() const {
    uint8_t v = runtime_data().desired_variety;
    if (v < 1) {
        v = current_params().food_variety_target;
    }
    if (v < 1) {
        v = 2;
    }
    return std::min<uint8_t>(v, 4);
}

uint8_t building_bazaar::min_variety() const {
    uint8_t v = runtime_data().min_variety;
    if (v < 1) {
        v = 1;
    }
    return std::min(v, desired_variety());
}

void building_bazaar::set_desired_variety(uint8_t value) {
    auto &d = runtime_data();
    d.desired_variety = (uint8_t)std::clamp<int>(value, 1, 4);
    if (d.min_variety > d.desired_variety) {
        d.min_variety = d.desired_variety;
    }
}

void building_bazaar::set_min_variety(uint8_t value) {
    auto &d = runtime_data();
    d.min_variety = (uint8_t)std::clamp<int>(value, 1, 4);
    if (d.min_variety > desired_variety()) {
        d.min_variety = desired_variety();
    }
}

bool building_bazaar::needs_food_variety() const {
    if (!game_features::gameplay_enhanced_food_mill.to_bool()) {
        return false;
    }

    int target = desired_variety();
    int available = 0;
    for (int foodi = INVENTORY_FOOD1; foodi <= INVENTORY_FOOD4; ++foodi) {
        if (g_city.allowed_foods(foodi) && idx_accepted(foodi)) {
            available++;
        }
    }
    if (available > 0 && target > available) {
        target = available;
    }
    return food_types_in_inventory() < target;
}

bool building_bazaar::waiting_for_mill_variety() const {
    if (!game_features::gameplay_enhanced_food_mill.to_bool()) {
        return false;
    }
    if (g_scenario.kingdom_supplies_grain) {
        return false;
    }

    const int min_v = min_variety();
    bool has_ready = false;
    bool has_partial = false;

    buildings_valid_do([&](building &b) {
        if (has_ready) {
            return;
        }
        if (!b.has_road_access || b.distance_from_entry <= 0 || b.road_network_id != base.road_network_id
            || b.num_workers <= 0) {
            return;
        }

        building_storage *s = b.dcast_storage();
        if (!s || !s->get_permission(BUILDING_STORAGE_PERMISSION_MARKET)) {
            return;
        }

        int distance = calc_maximum_distance(base.tile, b.tile);
        if (distance >= current_params().max_search_distance) {
            return;
        }

        auto *mill = b.dcast_food_mill();
        if (!mill) {
            return;
        }

        const int variety = mill->food_variety();
        if (variety >= min_v) {
            has_ready = true;
        } else if (variety > 0) {
            has_partial = true;
        }
    }, BUILDING_FOOD_MILL);

    // Wait only when some mill has partial stock and none meet min (ready mill → go).
    return !has_ready && has_partial;
}

bool building_bazaar::idx_accepted(uint8_t index) const {
    return runtime_data().market_goods.is_set(index);
}

bool building_bazaar::res_accepted(e_resource res) const {
    auto &d = runtime_data();
    auto it = std::find_if(std::begin(d.inventory), std::end(d.inventory), [res](const resource_value &rv) { return rv.type == res; });
    if (it == std::end(d.inventory)) {
        return false;
    }

    const uint8_t idx = std::distance(d.inventory, it);
    return d.market_goods.is_set(idx);
}

void building_bazaar::toggle_res_accepted(e_resource res) {
    auto &d = runtime_data();
    auto it = std::find_if(std::begin(d.inventory), std::end(d.inventory), [res](const resource_value &rv) { return rv.type == res; });
    if (it != std::end(d.inventory)) {
        const uint8_t idx = std::distance(d.inventory, it);
        d.market_goods.inv(idx);
    }
}

void building_bazaar::toggle_idx_accepted(uint8_t idx) {
    runtime_data().market_goods.inv(idx);
}

void building_bazaar::unaccept_all_goods() {
    runtime_data().market_goods.set_zero();
}

int building_bazaar::effective_max_buyers() const {
    const int configured = current_params().max_buyers;
    if (configured <= 0) {
        return 2;
    }
    return std::clamp(configured, 1, 2);
}

bool building_bazaar::is_active_market_buyer(figure *f) {
    return f && f->is_alive() && f->action_state >= 0;
}

int building_bazaar::count_market_buyers() const {
    int count = 0;
    for (e_building_slot slot : k_buyer_slots) {
        if (!base.has_figure_of_type(slot, FIGURE_MARKET_BUYER)) {
            continue;
        }
        if (is_active_market_buyer(base.get_figure(slot))) {
            count++;
        }
    }
    return count;
}

e_building_slot building_bazaar::free_market_buyer_slot() const {
    for (e_building_slot slot : k_buyer_slots) {
        if (!base.has_figure_of_type(slot, FIGURE_MARKET_BUYER)) {
            return slot;
        }
        if (!is_active_market_buyer(base.get_figure(slot))) {
            return slot;
        }
    }
    return BUILDING_SLOT_SERVICE;
}

void building_bazaar::reclaim_inactive_buyer_slot(e_building_slot slot) {
    if (slot != BUILDING_SLOT_MARKET_BUYER && slot != BUILDING_SLOT_MARKET_BUYER_2) {
        return;
    }
    figure *f = base.get_figure(slot);
    if (!f || !f->id) {
        base.remove_figure(slot);
        return;
    }
    if (is_active_market_buyer(f)) {
        return;
    }
    f->poof();
    base.remove_figure(slot);
}

void building_bazaar::force_clear_buyer_slot(e_building_slot slot) {
    if (slot != BUILDING_SLOT_MARKET_BUYER && slot != BUILDING_SLOT_MARKET_BUYER_2) {
        return;
    }
    figure *f = base.get_figure(slot);
    if (f && f->id) {
        f->poof();
    }
    base.remove_figure(slot);
}

void building_bazaar::tick_good_demands() {
    auto &d = runtime_data();
    if (d.pottery_demand) {
        d.pottery_demand--;
    }
    if (d.luxurygoods_demand) {
        d.luxurygoods_demand--;
    }
    if (d.linen_demand) {
        d.linen_demand--;
    }
    if (d.beer_demand) {
        d.beer_demand--;
    }
}

void building_bazaar::collect_buyer_busy_state(bool *exclude, bool *has_food_buyer, bool *has_good_buyer) const {
    if (exclude) {
        std::fill(exclude, exclude + INVENTORY_MAX, false);
    }
    if (has_food_buyer) {
        *has_food_buyer = false;
    }
    if (has_good_buyer) {
        *has_good_buyer = false;
    }

    for (e_building_slot slot : k_buyer_slots) {
        if (!base.has_figure_of_type(slot, FIGURE_MARKET_BUYER)) {
            continue;
        }
        figure *f = base.get_figure(slot);
        if (!is_active_market_buyer(f)) {
            continue;
        }
        const int inv = f->collecting_item_id;
        if (exclude && inv >= 0 && inv < INVENTORY_MAX) {
            exclude[inv] = true;
        }
        if (inv <= INVENTORY_FOOD4) {
            if (has_food_buyer) {
                *has_food_buyer = true;
            }
        } else if (inv >= INVENTORY_GOOD1 && inv <= INVENTORY_GOOD4) {
            if (has_good_buyer) {
                *has_good_buyer = true;
            }
        }
    }
}

building *building_bazaar::pick_next_buyer_destination() {
    if (waiting_for_mill_variety()) {
        return building_get(0);
    }

    bool exclude[INVENTORY_MAX];
    bool has_food_buyer = false;
    bool has_good_buyer = false;
    collect_buyer_busy_state(exclude, &has_food_buyer, &has_good_buyer);

    // Never tick inside probes: complementary may fail and fall back; burning
    // *_demand on a failed goods/foods probe would soft-lock demand for nothing.
    // Tick only after a successful pick while no active buyers are out.
    building *dest;
    if (needs_food_variety()) {
        // Slice B: fill food variety before complementary goods-first.
        dest = get_storage_destination(e_bazaar_fetch_foods, exclude, false);
        if (!dest->id) {
            dest = get_storage_destination(e_bazaar_fetch_goods, exclude, false);
        }
    } else if (has_food_buyer) {
        dest = get_storage_destination(e_bazaar_fetch_goods, exclude, false);
        if (!dest->id) {
            dest = get_storage_destination(e_bazaar_fetch_foods, exclude, false);
        }
    } else if (has_good_buyer) {
        dest = get_storage_destination(e_bazaar_fetch_foods, exclude, false);
        if (!dest->id) {
            dest = get_storage_destination(e_bazaar_fetch_goods, exclude, false);
        }
    } else {
        dest = get_storage_destination(e_bazaar_fetch_all, exclude, false);
    }

    if (dest->id && count_market_buyers() == 0) {
        tick_good_demands();
    }
    return dest;
}

namespace {

void fill_og_food_items(building_bazaar &bazaar, const resource_data *resources, int8_t *items) {
    const auto &d = bazaar.runtime_data();
    int n = 0;
    items[0] = items[1] = items[2] = items[3] = -1;
    for (int foodi = INVENTORY_FOOD1; foodi <= INVENTORY_FOOD4; ++foodi) {
        if (!bazaar.idx_accepted(foodi) || !g_city.allowed_foods(foodi) || !resources[foodi].num_buildings) {
            continue;
        }
        if (d.inventory[foodi].value == 0) {
            items[n++] = (int8_t)foodi;
            if (n > 3) {
                return;
            }
        }
    }
    for (int foodi = INVENTORY_FOOD1; foodi <= INVENTORY_FOOD4; ++foodi) {
        if (!bazaar.idx_accepted(foodi) || !g_city.allowed_foods(foodi) || !resources[foodi].num_buildings) {
            continue;
        }
        if (d.inventory[foodi].value < 600) {
            bool listed = false;
            for (int i = 0; i < n; i++) {
                if (items[i] == foodi) {
                    listed = true;
                    break;
                }
            }
            if (!listed) {
                items[n++] = (int8_t)foodi;
                if (n > 3) {
                    return;
                }
            }
        }
    }
}

void fill_og_goods_items(building_bazaar &bazaar, const resource_data *resources, int8_t *items) {
    const auto &d = bazaar.runtime_data();
    int n = 0;
    items[0] = items[1] = items[2] = items[3] = -1;
    for (int goodi = INVENTORY_GOOD1; goodi <= INVENTORY_GOOD4; ++goodi) {
        if (!bazaar.idx_accepted(goodi) || !resources[goodi].num_buildings) {
            continue;
        }
        if (d.inventory[goodi].value == 0) {
            items[n++] = (int8_t)goodi;
            if (n > 3) {
                return;
            }
        }
    }
    for (int goodi = INVENTORY_GOOD1; goodi <= INVENTORY_GOOD4; ++goodi) {
        if (!bazaar.idx_accepted(goodi) || !resources[goodi].num_buildings) {
            continue;
        }
        if (d.inventory[goodi].value < 100) {
            bool listed = false;
            for (int i = 0; i < n; i++) {
                if (items[i] == goodi) {
                    listed = true;
                    break;
                }
            }
            if (!listed) {
                items[n++] = (int8_t)goodi;
                if (n > 3) {
                    return;
                }
            }
        }
    }
}

building *pick_og_food_destination(building_bazaar &bazaar, const resource_data *resources, int8_t *items) {
    fill_og_food_items(bazaar, resources, items);
    auto &d = bazaar.runtime_data();

    for (int foodi = INVENTORY_FOOD1; foodi <= INVENTORY_FOOD4; ++foodi) {
        if (!bazaar.idx_accepted(foodi) || !g_city.allowed_foods(foodi) || !resources[foodi].num_buildings) {
            continue;
        }
        if (d.inventory[foodi].value == 0) {
            d.fetch_inventory_id = (int16_t)foodi;
            return building_get(resources[foodi].building_id);
        }
    }

    int16_t lowest = 50;
    int chosen = -1;
    for (int foodi = INVENTORY_FOOD1; foodi <= INVENTORY_FOOD4; ++foodi) {
        if (!bazaar.idx_accepted(foodi) || !g_city.allowed_foods(foodi) || !resources[foodi].num_buildings) {
            continue;
        }
        if (d.inventory[foodi].value < lowest) {
            lowest = d.inventory[foodi].value;
            chosen = foodi;
        }
    }
    if (chosen < 0) {
        for (int foodi = INVENTORY_FOOD1; foodi <= INVENTORY_FOOD4; ++foodi) {
            if (!bazaar.idx_accepted(foodi) || !g_city.allowed_foods(foodi) || !resources[foodi].num_buildings) {
                continue;
            }
            if (d.inventory[foodi].value < 600) {
                chosen = foodi;
            }
        }
    }
    if (chosen < 0) {
        return building_get(0);
    }
    d.fetch_inventory_id = (int16_t)chosen;
    return building_get(resources[chosen].building_id);
}

building *pick_og_goods_destination(building_bazaar &bazaar, const resource_data *resources, int8_t *items) {
    fill_og_goods_items(bazaar, resources, items);
    auto &d = bazaar.runtime_data();

    for (int goodi = INVENTORY_GOOD1; goodi <= INVENTORY_GOOD4; ++goodi) {
        if (!bazaar.idx_accepted(goodi) || !resources[goodi].num_buildings) {
            continue;
        }
        if (d.inventory[goodi].value == 0) {
            d.fetch_inventory_id = (int16_t)goodi;
            return building_get(resources[goodi].building_id);
        }
    }

    int chosen = -1;
    int16_t lowest = 100;
    for (int goodi = INVENTORY_GOOD1; goodi <= INVENTORY_GOOD4; ++goodi) {
        if (!bazaar.idx_accepted(goodi) || !resources[goodi].num_buildings) {
            continue;
        }
        if (d.inventory[goodi].value < lowest) {
            chosen = goodi;
            lowest = d.inventory[goodi].value;
        }
    }
    if (chosen < 0) {
        return building_get(0);
    }
    d.fetch_inventory_id = (int16_t)chosen;
    return building_get(resources[chosen].building_id);
}

} // namespace

building *building_bazaar::get_storage_destination(e_bazaar_fetch_group group, const bool *exclude, bool tick_demand) {
    if (waiting_for_mill_variety()) {
        return building_get(0);
    }

    resource_data resources[INVENTORY_MAX];
    scan_bazaar_storages(*this, resources, tick_demand);

    auto &d = runtime_data();
    auto can_pick = [&](int inv) {
        return inventory_in_group(inv, group)
            && !is_excluded(inv, exclude)
            && resources[inv].num_buildings
            && idx_accepted(inv);
    };

    int can_go = 0;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        if (can_pick(i)) {
            can_go = 1;
            break;
        }
    }

    if (!can_go) {
        return building_get(0);
    }

    // prefer food if we don't have it
    if (group == e_bazaar_fetch_all || group == e_bazaar_fetch_foods) {
        for (int foodi = INVENTORY_FOOD1; foodi <= INVENTORY_FOOD4; ++foodi) {
            if (!d.inventory[foodi].value && can_pick(foodi)) {
                d.fetch_inventory_id = foodi;
                return building_get(resources[foodi].building_id);
            }
        }
    }

    const bool variety_first = needs_food_variety()
        && (group == e_bazaar_fetch_all || group == e_bazaar_fetch_foods);

    // Slice B / foods group: top up understocked foods before empty goods.
    if (variety_first || group == e_bazaar_fetch_foods) {
        int fetch_food = -1;
        int min_food_stock = 999;
        const auto &pick_food_below = current_params().pick_food_below;
        for (int foodi = INVENTORY_FOOD1; foodi <= INVENTORY_FOOD4; ++foodi) {
            if (!can_pick(foodi) || d.inventory[foodi].value > pick_food_below[foodi]) {
                continue;
            }
            if (d.inventory[foodi].value < min_food_stock) {
                min_food_stock = d.inventory[foodi].value;
                fetch_food = foodi;
            }
        }
        if (fetch_food >= 0) {
            d.fetch_inventory_id = fetch_food;
            return building_get(resources[fetch_food].building_id);
        }
        if (group == e_bazaar_fetch_foods) {
            return building_get(0);
        }
        // variety_first + fetch_all: no more food to pick → fall through to goods
    }

    // then prefer resource if we don't have it
    if (group == e_bazaar_fetch_all || group == e_bazaar_fetch_goods) {
        for (int goodi = INVENTORY_GOOD1; goodi <= INVENTORY_GOOD4; ++goodi) {
            if (!d.inventory[goodi].value && can_pick(goodi)) {
                d.fetch_inventory_id = goodi;
                return building_get(resources[goodi].building_id);
            }
        }
    }

    // then prefer smallest stock below threshold
    int fetch_inventory = -1;
    int min_stock = 999;
    const auto &pick_good_below = current_params().pick_good_below;
    const auto &pick_food_below = current_params().pick_food_below;
    for (int goodi = INVENTORY_FOOD1; goodi <= INVENTORY_GOOD4; ++goodi) {
        if (!can_pick(goodi)) {
            continue;
        }

        int pickup_threshold = (goodi <= INVENTORY_FOOD4)
            ? pick_food_below[goodi]
            : pick_good_below[goodi - INVENTORY_GOOD1];
        if (d.inventory[goodi].value > pickup_threshold) {
            continue;
        }

        if (d.inventory[goodi].value < min_stock) {
            min_stock = d.inventory[goodi].value;
            fetch_inventory = goodi;
        }
    }

    if (fetch_inventory == -1 && (group == e_bazaar_fetch_all || group == e_bazaar_fetch_foods)) {
        min_stock = 999;
        for (int foodi = INVENTORY_FOOD1; foodi <= INVENTORY_FOOD4; ++foodi) {
            if (!can_pick(foodi) || d.inventory[foodi].value >= pick_food_below[foodi]) {
                continue;
            }
            if (d.inventory[foodi].value < min_stock) {
                min_stock = d.inventory[foodi].value;
                fetch_inventory = foodi;
            }
        }
    }

    if (fetch_inventory < 0) {
        return building_get(0);
    }

    d.fetch_inventory_id = fetch_inventory;
    return building_get(resources[fetch_inventory].building_id);
}

void building_bazaar::update_graphic() {
    if (base.state != BUILDING_STATE_VALID) {
        return;
    }

    const bool is_fancy = g_desirability.get(base.tile) <= current_params().fancy_treshold_desirability;
    base.set_flag(e_building_fancy, is_fancy);

    const xstring &animkey = is_fancy ? animkeys().base : animkeys().fancy;
    map_building_tiles_add(base.id, base.tile, base.size, first_img(animkey), TERRAIN_BUILDING);

    building_impl::update_graphic();
}

void building_bazaar::on_create(int orientation) {
    auto &d = runtime_data();
    d.market_goods.set_one();
    base.set_flag(e_building_fancy, false);
    d.desired_variety = current_params().food_variety_target;
    if (d.desired_variety < 1) {
        d.desired_variety = 2;
    }
    if (d.desired_variety > 4) {
        d.desired_variety = 4;
    }
    d.min_variety = 1;

    sync_inventory_types();
}

// The food slots follow the city's allowed foods, which update_month recomputes.
void building_bazaar::sync_inventory_types() {
    auto& d = runtime_data();
    d.inventory[INVENTORY_FOOD1].type = g_city.allowed_foods(INVENTORY_FOOD1);
    d.inventory[INVENTORY_FOOD2].type = g_city.allowed_foods(INVENTORY_FOOD2);
    d.inventory[INVENTORY_FOOD3].type = g_city.allowed_foods(INVENTORY_FOOD3);
    d.inventory[INVENTORY_FOOD4].type = g_city.allowed_foods(INVENTORY_FOOD4);
    d.inventory[INVENTORY_GOOD1].type = RESOURCE_POTTERY;
    d.inventory[INVENTORY_GOOD2].type = RESOURCE_LUXURY_GOODS;
    d.inventory[INVENTORY_GOOD3].type = RESOURCE_LINEN;
    d.inventory[INVENTORY_GOOD4].type = RESOURCE_BEER;
}

void building_bazaar::update_month() {
    building_impl::update_month();
    sync_inventory_types();
}

void building_bazaar::on_post_load() {
    building_impl::on_post_load();

    auto &d = runtime_data();
    sync_inventory_types();

    if (d.desired_variety < 1) {
        d.desired_variety = current_params().food_variety_target;
        if (d.desired_variety < 1) {
            d.desired_variety = 2;
        }
    }
    if (d.min_variety < 1) {
        d.min_variety = 1;
    }
    if (d.min_variety > d.desired_variety) {
        d.min_variety = d.desired_variety;
    }
}

void building_bazaar::maintain_fancy_second_trader() {
    auto &d = runtime_data();
    figure *cur = figure_get(d.second_trader_id);
    const bool alive = cur && cur->is_alive()
        && (cur->type == FIGURE_MARKET_TRADER || cur->type == FIGURE_LABOR_SEEKER)
        && cur->has_home(id());
    if (!alive) {
        d.second_trader_id = 0;
    }

    // OG: second trader only while desirability > fancy threshold (image_bazaar_fancy).
    const int desir = g_desirability.get(base.tile);
    if (desir <= current_params().fancy_treshold_desirability) {
        return;
    }

    if (d.second_trader_id != 0) {
        return;
    }

    const int inventory = std::accumulate(d.inventory, d.inventory + INVENTORY_MAX, 0,
                                          [](int sum, const resource_value &rv) { return sum + rv.value; });
    if (inventory <= 0) {
        return;
    }

    tile2i spawn_tile = base.road_access.valid() ? base.road_access : base.tile;
    figure *f = figure_create(FIGURE_MARKET_TRADER, spawn_tile, base.figure_roam_direction);
    f->action_state = ACTION_125_MARKET_TRADER_ROAMING;
    f->set_home(base.id);
    f->init_roaming_from_building(base.figure_roam_direction);
    base.figure_roam_direction += 2;
    if (base.figure_roam_direction > 6) {
        base.figure_roam_direction = 0;
    }
    d.second_trader_id = (int16_t)f->id;
}

void building_bazaar::update_good_demands_from_houses(int radius) {
    auto &d = runtime_data();
    buildings_house_do([&](building_house *house) {
        if (!house || !house->hsize() || house->house_population() <= 0) {
            return;
        }
        if (calc_maximum_distance(base.tile, house->base.tile) > radius) {
            return;
        }
        int level = house->house_level();
        if (level < HOUSE_PALATIAL_ESTATE) {
            level++;
        }
        const model_house &model = building_house::get_model(level);
        if (model.beer) {
            d.beer_demand = 10;
        }
        if (model.pottery) {
            d.pottery_demand = 10;
        }
        if (model.linen) {
            d.linen_demand = 10;
        }
        if (model.jewelry) {
            d.luxurygoods_demand = 10;
        }
    });
}

building *building_bazaar::get_og_food_destination(int8_t items[4]) {
    resource_data resources[INVENTORY_MAX];
    // OG ticks good demands on every destination search.
    scan_bazaar_storages(*this, resources, true);
    return pick_og_food_destination(*this, resources, items);
}

building *building_bazaar::get_og_goods_destination(int8_t items[4]) {
    resource_data resources[INVENTORY_MAX];
    scan_bazaar_storages(*this, resources, true);
    return pick_og_goods_destination(*this, resources, items);
}

void building_bazaar::update_og_buyer_storages(int nearest_out[INVENTORY_MAX]) {
    resource_data resources[INVENTORY_MAX];
    scan_bazaar_storages(*this, resources, true);
    for (int i = 0; i < INVENTORY_MAX; i++) {
        nearest_out[i] = resources[i].num_buildings ? resources[i].building_id : 0;
    }
}

void building_bazaar::spawn_figure() {
    check_labor_problem();
    if (!base.has_road_access) {
        return;
    }

    common_spawn_labor_seeker(current_params().min_houses_coverage);

    // OG maintains the fancy second trader every visit (not behind spawn_delay).
    maintain_fancy_second_trader();

    // OG bazaar_index: counted for every road-connected bazaar in the generate pass.
    g_city.figures.bazaar_figure_pass_index++;

    int spawn_delay = figure_spawn_timer();
    if (spawn_delay == -1) {
        return;
    }

    base.figure_spawn_delay++;
    const bool spawn_due = base.figure_spawn_delay > spawn_delay;
    if (spawn_due) {
        base.figure_spawn_delay = 0;
    }

    const auto &d = runtime_data();
    const int inventory = std::accumulate(d.inventory, d.inventory + INVENTORY_MAX, 0,
                                          [](int sum, const resource_value &rv) { return sum + rv.value; });
    bool trader_alive = base.has_figure_of_type(BUILDING_SLOT_SERVICE, FIGURE_MARKET_TRADER);
    if (!trader_alive && d.second_trader_id > 0) {
        figure *second = figure_get(d.second_trader_id);
        trader_alive = second && second->is_alive() && second->type == FIGURE_MARKET_TRADER;
    }

    // OG: when a trader is out or the bazaar is empty, scan houses in radius 10 for goods demand.
    // Remake flag: demand is set only when a trader visits a house.
    if (!game_features::gameplay_change_bazaar_demand_from_trader.to_bool()) {
        if (trader_alive || inventory == 0) {
            update_good_demands_from_houses(10);
        }
    }

    const bool multi = !!game_features::gameplay_change_bazaar_multi_buyers;
    const bool remake_buyer_timer = !!game_features::gameplay_change_bazaar_buyer_spawn_timer;
    // OG: day % 8 == bazaar_index % 8. Remake flag: buyers share labor spawn_due.
    const bool buyers_due = remake_buyer_timer
        ? spawn_due
        : ((game.simtime.day % 8) == (g_city.figures.bazaar_figure_pass_index % 8));

    if (buyers_due) {
        if (multi) {
            const int alive_buyers = count_market_buyers();
            if (alive_buyers < effective_max_buyers()) {
                e_building_slot slot = free_market_buyer_slot();
                if (slot == BUILDING_SLOT_MARKET_BUYER || slot == BUILDING_SLOT_MARKET_BUYER_2) {
                    reclaim_inactive_buyer_slot(slot);
                    building *dest = pick_next_buyer_destination();
                    if (dest->id) {
                        figure *f = create_figure_with_destination(FIGURE_MARKET_BUYER, dest,
                                                                       (e_figure_action)ACTION_145_MARKET_BUYER_GOING_TO_STORAGE, slot);
                        f->collecting_item_id = d.fetch_inventory_id;
                    }
                }
            }
        } else {
            // OG: dedicated food buyer (slot 1) + goods buyer (slot 2), shopping-list trips.
            auto try_og_buyer = [&](e_building_slot slot, bool food) {
                figure *cur = base.get_figure(slot);
                const bool busy = base.has_figure_of_type(slot, FIGURE_MARKET_BUYER) && is_active_market_buyer(cur);
                if (busy) {
                    return;
                }
                reclaim_inactive_buyer_slot(slot);
                int8_t items[4] = { -1, -1, -1, -1 };
                building *dest = food ? get_og_food_destination(items) : get_og_goods_destination(items);
                if (!dest->id) {
                    return;
                }
                figure *f = create_figure_with_destination(FIGURE_MARKET_BUYER, dest,
                                                           (e_figure_action)ACTION_145_MARKET_BUYER_GOING_TO_STORAGE, slot);
                if (auto *buyer = f->dcast_market_buyer()) {
                    buyer->init_og_trip(items, food);
                } else {
                    f->collecting_item_id = d.fetch_inventory_id;
                }
            };
            try_og_buyer(BUILDING_SLOT_MARKET_BUYER, true);
            try_og_buyer(BUILDING_SLOT_MARKET_BUYER_2, false);
        }
    }

    if (spawn_due && !base.has_figure_of_type(BUILDING_SLOT_SERVICE, FIGURE_MARKET_TRADER)) {
        if (inventory > 0) {
            create_roaming_figure(FIGURE_MARKET_TRADER, ACTION_125_MARKET_TRADER_ROAMING, BUILDING_SLOT_SERVICE);
        }
    }
}

const animation_t& building_bazaar::work_anim() const {
    const xstring &animkey = base.get_flag(e_building_fancy) ? animkeys().base_work : animkeys().fancy_work;
    return anim(animkey);
}

void building_bazaar::update_sprite_anims() {
    register_sprite_anim(work_anim());
}

bool building_bazaar::draw_ornaments_and_animations_height(painter& ctx, vec2i point, tile2i tile, color color_mask) {
    building_draw_normal_anim(ctx, point, &base, tile, work_anim(), color_mask);

    return true;
}

void building_bazaar::bind_dynamic(io_buffer *iob, size_t version) {
    auto &d = runtime_data();

    iob->bind(BIND_SIGNATURE_INT16, d.market_goods.data_ptr());
    iob->bind(BIND_SIGNATURE_INT16, &d.pottery_demand);
    iob->bind(BIND_SIGNATURE_INT16, &d.luxurygoods_demand);
    iob->bind(BIND_SIGNATURE_INT16, &d.linen_demand);
    iob->bind(BIND_SIGNATURE_INT16, &d.beer_demand);

    uint16_t tmp = 0;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &d.inventory[i].type);
        iob->bind(BIND_SIGNATURE_UINT8, &tmp);
        iob->bind(BIND_SIGNATURE_UINT16, &d.inventory[i].value);
    }

    iob->bind(BIND_SIGNATURE_UINT8, &d.fetch_inventory_id);

    if (version >= 185) {
        iob->bind_u8(d.desired_variety);
        iob->bind_u8(d.min_variety);
    } else {
        d.desired_variety = current_params().food_variety_target;
        if (d.desired_variety < 1) {
            d.desired_variety = 2;
        }
        d.min_variety = 1;
    }

    iob->bind(BIND_SIGNATURE_INT16, &d.second_trader_id);
}
