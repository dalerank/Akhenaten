#include "building_bazaar.h"

#include "figure/figure.h"
#include "building/building_type.h"
#include "building/building_storage_yard.h"
#include "figuretype/figure_market_buyer.h"
#include "figuretype/figure_market_trader.h"
#include "graphics/elements/ui.h"
#include "city/city.h"
#include "city/city_labor.h"
#include "core/calc.h"
#include "game/resource.h"
#include "scenario/scenario.h"
#include "grid/desirability.h"
#include "grid/building_tiles.h"
#include "grid/terrain.h"
#include "grid/routing/routing.h"
#include "graphics/image.h"
#include "window/building/distribution.h"
#include "building/building_granary.h"
#include "graphics/graphics.h"
#include "game/game.h"
#include "widget/city/ornaments.h"
#include "js/js_game.h"
#include <numeric>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_bazaar);

struct resource_data {
    int building_id;
    int min_distance;
    int num_buildings;

    void update_food(int resource, building &b, int distance, int minimal_amount) {
        if (!resource) {
            return;
        }

        building_granary *granary = b.dcast_granary();
        if (!granary) {
            return;
        }

        if (granary->runtime_data().resource_stored[resource] < minimal_amount) {
            return;
        }

        num_buildings++;
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

uint16_t building_bazaar::get_resource_amount(e_resource res) const {
    auto it = std::find_if(std::begin(runtime_data().inventory), std::end(runtime_data().inventory),
                           [res] (const resource_value &rv) { return rv.type == res; });

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

bool building_bazaar::idx_accepted(uint8_t index) {
    return runtime_data().market_goods.is_set(index);
}

bool building_bazaar::res_accepted(e_resource res) {
    auto &d = runtime_data();
    auto it = std::find_if(std::begin(d.inventory), std::end(d.inventory), [res] (const resource_value &rv) { return rv.type == res; });
    if (it == std::end(d.inventory)) {
        return false;
    }

    const uint8_t idx = std::distance(d.inventory, it);
    return d.market_goods.is_set(idx);
}

void building_bazaar::toggle_res_accepted(e_resource res) {
    auto &d = runtime_data();
    auto it = std::find_if(std::begin(d.inventory), std::end(d.inventory), [res] (const resource_value &rv) { return rv.type == res; });
    if (it != std::end(d.inventory)) {
        const uint8_t idx = std::distance(d.inventory, it);
        d.market_goods.inv(idx);
    }
}

void building_bazaar::toggle_idx_accepted(uint8_t idx) {
    runtime_data().market_goods.inv(idx);
}

void building_bazaar::unaccept_all_goods() {
    runtime_data().market_goods.set_one();
}

building *building_bazaar::get_storage_destination() {
    resource_data resources[INVENTORY_MAX];

    std::fill(std::begin(resources), std::end(resources), resource_data{0, current_params().max_search_distance, 0});
    buildings_valid_do([&] (building &b) {
        if (!b.has_road_access || b.distance_from_entry <= 0 || b.road_network_id != base.road_network_id) {
            return;
        }

        building_storage *s = b.dcast_storage();
        if (!s->get_permission(BUILDING_STORAGE_PERMISSION_MARKET)) {
            return;
        }

        int distance = calc_maximum_distance(base.tile, b.tile);
        if (distance >= this->current_params().max_search_distance) {
            return;
        }

        if (b.type == BUILDING_GRANARY) {
            if (g_scenario.kingdom_supplies_grain) {
                return;
            }

            // foods
            const int minimal_amount = this->current_params().minimal_pick_food_amount;
            resources[INVENTORY_FOOD1].update_food(g_city.allowed_foods(INVENTORY_FOOD1), b, distance, minimal_amount);
            resources[INVENTORY_FOOD2].update_food(g_city.allowed_foods(INVENTORY_FOOD2), b, distance, minimal_amount);
            resources[INVENTORY_FOOD3].update_food(g_city.allowed_foods(INVENTORY_FOOD3), b, distance, minimal_amount);
            resources[INVENTORY_FOOD4].update_food(g_city.allowed_foods(INVENTORY_FOOD4), b, distance, minimal_amount);

        } else if (b.type == BUILDING_STORAGE_YARD) {
            // foods
            resources[INVENTORY_FOOD1].update_good(g_city.allowed_foods(INVENTORY_FOOD1), b, distance);
            resources[INVENTORY_FOOD2].update_good(g_city.allowed_foods(INVENTORY_FOOD2), b, distance);
            resources[INVENTORY_FOOD3].update_good(g_city.allowed_foods(INVENTORY_FOOD3), b, distance);
            resources[INVENTORY_FOOD4].update_good(g_city.allowed_foods(INVENTORY_FOOD4), b, distance);

            // goods
            resources[INVENTORY_GOOD1].update_good(RESOURCE_POTTERY, b, distance);
            resources[INVENTORY_GOOD2].update_good(RESOURCE_LUXURY_GOODS, b, distance);
            resources[INVENTORY_GOOD3].update_good(RESOURCE_LINEN, b, distance);
            resources[INVENTORY_GOOD4].update_good(RESOURCE_BEER, b, distance);
        }
    }, { BUILDING_GRANARY, BUILDING_STORAGE_YARD });

    // update demands
    auto &d = runtime_data();
    if (d.pottery_demand) {
        d.pottery_demand--;
    } else {
        resources[INVENTORY_GOOD1].num_buildings = 0;
    }

    if (d.luxurygoods_demand) {
        d.luxurygoods_demand--;
    } else {
        resources[INVENTORY_GOOD2].num_buildings = 0;
    }

    if (d.linen_demand) {
        d.linen_demand--;
    } else {
        resources[INVENTORY_GOOD3].num_buildings = 0;
    }

    if (d.beer_demand) {
        d.beer_demand--;
    } else {
        resources[INVENTORY_GOOD4].num_buildings = 0;
    }

    int can_go = 0;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        if (resources[i].num_buildings) {
            can_go = 1;
            break;
        }
    }

    if (!can_go) {
        return building_get(0);
    }

    // prefer food if we don't have it
    for (int foodi = INVENTORY_FOOD1; foodi <= INVENTORY_FOOD4; ++foodi) {
        if (!d.inventory[foodi].value && resources[foodi].num_buildings && idx_accepted(foodi)) {
            d.fetch_inventory_id = foodi;
            return building_get(resources[foodi].building_id);
        }
    }
    
    // then prefer resource if we don't have it
    for (int goodi = INVENTORY_GOOD1; goodi <= INVENTORY_GOOD4; ++goodi) {
        if (!d.inventory[goodi].value && resources[goodi].num_buildings && idx_accepted(goodi)) {
            d.fetch_inventory_id = goodi;
            return building_get(resources[goodi].building_id);
        }
    }
    
    // then prefer smallest stock below 50
    int fetch_inventory = -1;
    int min_stock = 999;
    const auto &pick_good_below = current_params().pick_good_below;
    const auto &pick_food_below = current_params().pick_food_below;
    for (int goodi = INVENTORY_FOOD1; goodi <= INVENTORY_GOOD4; ++goodi) {
        if (!resources[goodi].num_buildings) {
            continue;
        }

        int pickup_threshold = (goodi <= INVENTORY_FOOD4) ? pick_good_below[goodi] : pick_good_below[goodi - INVENTORY_GOOD1];
        if (d.inventory[goodi].value > pickup_threshold) {
            continue;
        }

        if (!idx_accepted(goodi)) {
            continue;
        }

        if (d.inventory[goodi].value < min_stock) {
            min_stock = d.inventory[goodi].value;
            fetch_inventory = goodi;
        }
    }

    if (fetch_inventory == -1) {
        // all items well stocked: pick food below threshold
        if (resources[INVENTORY_FOOD1].num_buildings && d.inventory[INVENTORY_FOOD1].value < pick_food_below[INVENTORY_FOOD1]  && idx_accepted(INVENTORY_FOOD1)) {
            fetch_inventory = INVENTORY_FOOD1;
        }
        if (resources[INVENTORY_FOOD2].num_buildings && d.inventory[INVENTORY_FOOD2].value < pick_food_below[INVENTORY_FOOD2] && idx_accepted(INVENTORY_FOOD2)) {
            fetch_inventory = INVENTORY_FOOD2;
        }
        if (resources[INVENTORY_FOOD3].num_buildings && d.inventory[INVENTORY_FOOD3].value < pick_food_below[INVENTORY_FOOD3] && idx_accepted(INVENTORY_FOOD3)) {
            fetch_inventory = INVENTORY_FOOD3;
        }
        if (resources[INVENTORY_FOOD4].num_buildings && d.inventory[INVENTORY_FOOD4].value < pick_food_below[INVENTORY_FOOD4] && idx_accepted(INVENTORY_FOOD4)) {
            fetch_inventory = INVENTORY_FOOD4;
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

    const xstring& animkey = is_fancy ? animkeys().base : animkeys().fancy;
    map_building_tiles_add(base.id, base.tile, base.size, first_img(animkey), TERRAIN_BUILDING);

    building_impl::update_graphic();
}

void building_bazaar::on_create(int orientation) {
    runtime_data().market_goods.set_one();
    base.set_flag(e_building_fancy, false);
}

void building_bazaar::on_post_load() {
    building_impl::on_post_load();

    auto &d = runtime_data();
    d.inventory[INVENTORY_FOOD1].type = g_city.allowed_foods(INVENTORY_FOOD1);
    d.inventory[INVENTORY_FOOD2].type = g_city.allowed_foods(INVENTORY_FOOD2);
    d.inventory[INVENTORY_FOOD3].type = g_city.allowed_foods(INVENTORY_FOOD3);
    d.inventory[INVENTORY_FOOD4].type = g_city.allowed_foods(INVENTORY_FOOD4);
    d.inventory[INVENTORY_GOOD1].type = RESOURCE_POTTERY;
    d.inventory[INVENTORY_GOOD2].type = RESOURCE_LUXURY_GOODS;
    d.inventory[INVENTORY_GOOD3].type = RESOURCE_LINEN;
    d.inventory[INVENTORY_GOOD4].type = RESOURCE_BEER;
}

void building_bazaar::spawn_figure() {
    base.check_labor_problem();

    if (!common_spawn_figure_trigger(current_params().min_houses_coverage)) {
        return;
    }

    const auto &d = runtime_data();
    // market buyer
    int spawn_delay = base.figure_spawn_timer();
    if (!base.has_figure_of_type(BUILDING_SLOT_MARKET_BUYER, FIGURE_MARKET_BUYER)) {
        base.figure_spawn_delay++;
        if (base.figure_spawn_delay > spawn_delay) {
            building *dest = get_storage_destination();
            if (dest->id) {
                base.figure_spawn_delay = 0;
                figure *f = base.create_figure_with_destination(FIGURE_MARKET_BUYER, dest, (e_figure_action)ACTION_145_MARKET_BUYER_GOING_TO_STORAGE, BUILDING_SLOT_MARKET_BUYER);
                f->collecting_item_id = d.fetch_inventory_id;
            }
        }
    }

    // market trader
    if (!base.has_figure_of_type(BUILDING_SLOT_SERVICE, FIGURE_MARKET_TRADER)) {
        int bazar_inventory = std::accumulate(d.inventory, d.inventory + 7, 0,
                                              [](int sum, const resource_value &rv) { return sum + rv.value; });
        if (bazar_inventory > 0) { // do not spawn trader if bazaar is 100% empty!
            base.figure_spawn_delay++;
            if (base.figure_spawn_delay > spawn_delay) {
                base.figure_spawn_delay = 0;
                base.create_roaming_figure(FIGURE_MARKET_TRADER, ACTION_125_MARKET_TRADER_ROAMING, BUILDING_SLOT_SERVICE);
                return;
            }
        }
    }
}

bool building_bazaar::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    const xstring& animkey = base.get_flag(e_building_fancy) ? animkeys().base_work : animkeys().fancy_work;
    const animation_t &ranim = anim(animkey);
    building_draw_normal_anim(ctx, point, &base, tile, ranim, color_mask);

    return true;
}
 
void building_bazaar::bind_dynamic(io_buffer *iob, size_t version) {
    auto &d = runtime_data();

    iob->bind(BIND_SIGNATURE_INT16, d.market_goods.data_ptr());
    iob->bind(BIND_SIGNATURE_INT16, &d.pottery_demand);
    iob->bind(BIND_SIGNATURE_INT16, &d.luxurygoods_demand);
    iob->bind(BIND_SIGNATURE_INT16, &d.linen_demand);
    iob->bind(BIND_SIGNATURE_INT16, &d.beer_demand);

    uint16_t tmp;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        iob->bind(BIND_SIGNATURE_UINT8,  &d.inventory[i].type);
        iob->bind(BIND_SIGNATURE_UINT8, &tmp);
        iob->bind(BIND_SIGNATURE_UINT16, &d.inventory[i].value);
    }

    iob->bind(BIND_SIGNATURE_UINT8, &d.fetch_inventory_id);
}
