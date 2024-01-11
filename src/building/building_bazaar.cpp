#include "building_bazaar.h"

#include "figure/figure.h"
#include "building/storage.h"
#include "building/building_type.h"
#include "building/storage_yard.h"
#include "city/resource.h"
#include "core/calc.h"
#include "game/resource.h"
#include "scenario/property.h"
#include "grid/desirability.h"
#include "grid/building_tiles.h"
#include "grid/terrain.h"
#include "graphics/image.h"

#include <numeric>

struct resource_data {
    int building_id;
    int distance;
    int num_buildings;
};

int building_bazaar_get_max_food_stock(building* market) {
    int max_stock = 0;
    if (market->id > 0 && market->type == BUILDING_BAZAAR) {
        for (int i = INVENTORY_MIN_FOOD; i < INVENTORY_MAX_FOOD; i++) {
            int stock = market->data.market.inventory[i];
            if (stock > max_stock)
                max_stock = stock;
        }
    }
    return max_stock;
}

int building_bazaar_get_max_goods_stock(building* market) {
    int max_stock = 0;
    if (market->id > 0 && market->type == BUILDING_BAZAAR) {
        for (int i = INVENTORY_MIN_GOOD; i < INVENTORY_MAX_GOOD; i++) {
            int stock = market->data.market.inventory[i];
            if (stock > max_stock)
                max_stock = stock;
        }
    }
    return max_stock;
}

static void update_food_resource(resource_data &data, int resource, const building &b, int distance) {
    if (!resource) {
        return;
    }

    if (b.data.granary.resource_stored[resource] > 100) {
        data.num_buildings++;
        if (distance < data.distance) {
            data.distance = distance;
            data.building_id = b.id;
        }
    }
}

static void update_good_resource(resource_data &data, e_resource resource, const building &b, int distance) {
    if (!city_resource_is_stockpiled(resource) && building_storageyard_get_amount(&b, resource) > 0) {
        data.num_buildings++;

        if (distance < data.distance) {
            data.distance = distance;
            data.building_id = b.id;
        }
    }
}

bool is_good_accepted(int index, building* market) {
    int goods_bit = 1 << index;
    return !(market->subtype.market_goods & goods_bit);
}

void toggle_good_accepted(int index, building* market) {
    int goods_bit = (1 << index);
    market->subtype.market_goods ^= goods_bit;
}

void unaccept_all_goods(building* market) {
    market->subtype.market_goods = 0xFFFF;
}

building *building_bazaar::get_storage_destination() {
    resource_data resources[INVENTORY_MAX];

    for (int i = 0; i < INVENTORY_MAX; i++) {
        resources[i].building_id = 0;
        resources[i].num_buildings = 0;
        resources[i].distance = 40;
    }

    buildings_valid_do([&] (building &b) {
        if (!b.has_road_access || b.distance_from_entry <= 0 || b.road_network_id != base.road_network_id) {
            return;
        }

        if (!building_storage_get_permission(BUILDING_STORAGE_PERMISSION_MARKET, &b)) {
            return;
        }

        int distance = calc_maximum_distance(base.tile, b.tile);
        if (distance >= 40) {
            return;
        }

        if (b.type == BUILDING_GRANARY) {
            if (scenario_property_kingdom_supplies_grain()) {
                return;
            }

            // todo: fetch map available foods?
            update_food_resource(resources[0], ALLOWED_FOODS(0), b, distance);
            update_food_resource(resources[1], ALLOWED_FOODS(1), b, distance);
            update_food_resource(resources[2], ALLOWED_FOODS(2), b, distance);
            update_food_resource(resources[3], ALLOWED_FOODS(3), b, distance);

        } else if (b.type == BUILDING_STORAGE_YARD) {
            // goods
            update_good_resource(resources[INVENTORY_GOOD1], RESOURCE_POTTERY, b, distance);
            update_good_resource(resources[INVENTORY_GOOD2], RESOURCE_LUXURY_GOODS, b, distance);
            update_good_resource(resources[INVENTORY_GOOD3], RESOURCE_LINEN, b, distance);
            update_good_resource(resources[INVENTORY_GOOD4], RESOURCE_BEER, b, distance);
        }
    }, BUILDING_GRANARY, BUILDING_STORAGE_YARD);

    // update demands
    if (base.data.market.pottery_demand)
        base.data.market.pottery_demand--;
    else
        resources[INVENTORY_GOOD1].num_buildings = 0;

    if (base.data.market.furniture_demand)
        base.data.market.furniture_demand--;
    else
        resources[INVENTORY_GOOD2].num_buildings = 0;

    if (base.data.market.oil_demand)
        base.data.market.oil_demand--;
    else
        resources[INVENTORY_GOOD3].num_buildings = 0;

    if (base.data.market.wine_demand)
        base.data.market.wine_demand--;
    else
        resources[INVENTORY_GOOD4].num_buildings = 0;

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
    if (!base.data.market.inventory[0] && resources[0].num_buildings && is_good_accepted(0, &base)) {
        base.data.market.fetch_inventory_id = 0;
        return building_get(resources[0].building_id);

    } else if (!base.data.market.inventory[1] && resources[1].num_buildings && is_good_accepted(1, &base)) {
        base.data.market.fetch_inventory_id = 1;
        return building_get(resources[1].building_id);

    } else if (!base.data.market.inventory[2] && resources[2].num_buildings && is_good_accepted(2, &base)) {
        base.data.market.fetch_inventory_id = 2;
        return building_get(resources[2].building_id);

    } else if (!base.data.market.inventory[3] && resources[3].num_buildings && is_good_accepted(3, &base)) {
        base.data.market.fetch_inventory_id = 3;
        return building_get(resources[3].building_id);
    }

    // then prefer resource if we don't have it
    if (!base.data.market.inventory[INVENTORY_GOOD1] && resources[INVENTORY_GOOD1].num_buildings && is_good_accepted(INVENTORY_GOOD1, &base)) {
        base.data.market.fetch_inventory_id = INVENTORY_GOOD1;
        return building_get(resources[INVENTORY_GOOD1].building_id);

    } else if (!base.data.market.inventory[INVENTORY_GOOD2] && resources[INVENTORY_GOOD2].num_buildings && is_good_accepted(INVENTORY_GOOD2, &base)) {
        base.data.market.fetch_inventory_id = INVENTORY_GOOD2;
        return building_get(resources[INVENTORY_GOOD2].building_id);

    } else if (!base.data.market.inventory[INVENTORY_GOOD3] && resources[INVENTORY_GOOD3].num_buildings && is_good_accepted(INVENTORY_GOOD3, &base)) {
        base.data.market.fetch_inventory_id = INVENTORY_GOOD3;
        return building_get(resources[INVENTORY_GOOD3].building_id);

    } else if (!base.data.market.inventory[INVENTORY_GOOD4] && resources[INVENTORY_GOOD4].num_buildings && is_good_accepted(INVENTORY_GOOD4, &base)) {
        base.data.market.fetch_inventory_id = INVENTORY_GOOD4;
        return building_get(resources[INVENTORY_GOOD4].building_id);
    }

    // then prefer smallest stock below 50
    int min_stock = 50;
    int fetch_inventory = -1;
    if (resources[0].num_buildings && base.data.market.inventory[0] < min_stock && is_good_accepted(0, &base)) {
        min_stock = base.data.market.inventory[0];
        fetch_inventory = 0;
    }

    if (resources[1].num_buildings && base.data.market.inventory[1] < min_stock && is_good_accepted(1, &base)) {
        min_stock = base.data.market.inventory[1];
        fetch_inventory = 1;
    }

    if (resources[2].num_buildings && base.data.market.inventory[2] < min_stock && is_good_accepted(2, &base)) {
        min_stock = base.data.market.inventory[2];
        fetch_inventory = 2;
    }

    if (resources[3].num_buildings && base.data.market.inventory[3] < min_stock && is_good_accepted(3, &base)) {
        min_stock = base.data.market.inventory[3];
        fetch_inventory = 3;
    }

    if (resources[INVENTORY_GOOD1].num_buildings && base.data.market.inventory[INVENTORY_GOOD1] < min_stock && is_good_accepted(INVENTORY_GOOD1, &base)) {
        min_stock = base.data.market.inventory[INVENTORY_GOOD1];
        fetch_inventory = INVENTORY_GOOD1;
    }

    if (resources[INVENTORY_GOOD2].num_buildings && base.data.market.inventory[INVENTORY_GOOD2] < min_stock && is_good_accepted(INVENTORY_GOOD2, &base)) {
        min_stock = base.data.market.inventory[INVENTORY_GOOD2];
        fetch_inventory = INVENTORY_GOOD2;
    }

    if (resources[INVENTORY_GOOD3].num_buildings && base.data.market.inventory[INVENTORY_GOOD3] < min_stock && is_good_accepted(INVENTORY_GOOD3, &base)) {
        min_stock = base.data.market.inventory[INVENTORY_GOOD3];
        fetch_inventory = INVENTORY_GOOD3;
    }

    if (resources[INVENTORY_GOOD4].num_buildings && base.data.market.inventory[INVENTORY_GOOD4] < min_stock && is_good_accepted(INVENTORY_GOOD4, &base)) {
        fetch_inventory = INVENTORY_GOOD4;
    }

    if (fetch_inventory == -1) {
        // all items well stocked: pick food below threshold
        if (resources[0].num_buildings && base.data.market.inventory[0] < 600 && is_good_accepted(0, &base)) {
            fetch_inventory = 0;
        }
        if (resources[1].num_buildings && base.data.market.inventory[1] < 400 && is_good_accepted(1, &base)) {
            fetch_inventory = 1;
        }
        if (resources[2].num_buildings && base.data.market.inventory[2] < 400 && is_good_accepted(2, &base)) {
            fetch_inventory = 2;
        }
        if (resources[3].num_buildings && base.data.market.inventory[3] < 400 && is_good_accepted(3, &base)) {
            fetch_inventory = 3;
        }
    }

    if (fetch_inventory < 0) {
        return building_get(0);
    }

    base.data.market.fetch_inventory_id = fetch_inventory;
    return building_get(resources[fetch_inventory].building_id);
}

void building_bazaar::update_graphic() {
    assert(base.type == BUILDING_BAZAAR);

    if (base.state != BUILDING_STATE_VALID) {
        return;
    }

    e_image_id img_id = (map_desirability_get(base.tile.grid_offset()) <= 30) ? IMG_BAZAAR : IMG_BAZAAR_FANCY;
    map_building_tiles_add(base.id, base.tile, base.size, image_group(img_id), TERRAIN_BUILDING);
}

void building_bazaar::update_day() {
    update_graphic();
}

void building_bazaar::spawn_figure() {
    base.check_labor_problem();

    if (base.common_spawn_figure_trigger(50)) {
        // market buyer
        int spawn_delay = base.figure_spawn_timer();
        if (!base.has_figure_of_type(1, FIGURE_MARKET_BUYER)) {
            base.figure_spawn_delay++;
            if (base.figure_spawn_delay > spawn_delay) {
                building *dest = get_storage_destination();
                if (dest->id) {
                    base.figure_spawn_delay = 0;
                    figure *f = base.create_figure_with_destination(FIGURE_MARKET_BUYER, dest, FIGURE_ACTION_145_MARKET_BUYER_GOING_TO_STORAGE, BUILDING_SLOT_MARKET_BUYER);
                    f->collecting_item_id = base.data.market.fetch_inventory_id;
                }
            }
        }

        // market trader
        if (!base.has_figure_of_type(0, FIGURE_MARKET_TRADER)) {
            int bazar_inventory = std::accumulate(base.data.market.inventory, base.data.market.inventory + 7, 0);
            if (bazar_inventory > 0) { // do not spawn trader if bazaar is 100% empty!
                base.figure_spawn_delay++;
                if (base.figure_spawn_delay > spawn_delay) {
                    base.figure_spawn_delay = 0;
                    base.create_roaming_figure(FIGURE_MARKET_TRADER);
                    return;
                }
            }
        }
    }
}
