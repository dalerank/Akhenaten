#include "market.h"

#include "building/building.h"
#include "building/granary.h"
#include "building/storage.h"
#include "core/log.h"
#include "building/storage_yard.h"
#include "figure/combat.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "game/resource.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "config/config.h"

void figure::market_buyer_action() {
    image_set_animation(GROUP_FIGURE_MARKET_BUYER);
    switch (action_state) {
    case 8:
    case FIGURE_ACTION_145_MARKET_BUYER_GOING_TO_STORAGE:
        if (do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, FIGURE_ACTION_146_MARKET_BUYER_RETURNING)) {
            if (collecting_item_id > 3) {
                if (!market_buyer_take_resource_from_storageyard(destination())) {
                    poof();
                }

            } else {
                if (!market_buyer_take_food_from_granary(home(), destination())) {
                    poof();
                }
            }
        }
        break;

    case 9:
    case ACTION_11_RETURNING_EMPTY:
    case FIGURE_ACTION_146_MARKET_BUYER_RETURNING:
        if (do_returnhome()) {
            home()->figure_spawn_delay = -3;
            //logs::info("stop");
        }
        break;
    }
}

int figure::market_buyer_take_food_from_granary(building* market, building* granary) {
    int resource;
    switch (collecting_item_id) {
    case 0:
        resource = ALLOWED_FOODS(0);
        break;

    case 1:
        resource = ALLOWED_FOODS(1);
        break;
    case 2:
        resource = ALLOWED_FOODS(2);
        break;

    case 3:
        resource = ALLOWED_FOODS(3);
        break;

    default:
        return 0;
    }
    //    building *granary = building_get(granary);
    //    int market_units = building_get(market)->data.market.inventory[collecting_item_id];
    int market_units = market->data.market.inventory[collecting_item_id];
    int max_units = (collecting_item_id == 0 ? 700 : 600) - market_units;
    int granary_units = granary->data.granary.resource_stored[resource];
    int num_loads;
    //    if (granary_units >= 800)
    //        num_loads = 8;
    //    else
    if (granary_units >= 700)
        num_loads = 7;
    else if (granary_units >= 600)
        num_loads = 6;
    else if (granary_units >= 500)
        num_loads = 5;
    else if (granary_units >= 400)
        num_loads = 4;
    else if (granary_units >= 300)
        num_loads = 3;
    else if (granary_units >= 200)
        num_loads = 2;
    else if (granary_units >= 100)
        num_loads = 1;
    else
        num_loads = 0;

    if (num_loads > max_units / 100)
        num_loads = max_units / 100;

    if (num_loads <= 0)
        return 0;

    building_granary_remove_resource(granary, resource, 100 * num_loads);

    // create delivery boys
    int previous_boy = id;
    for (int i = 0; i < num_loads; i++) {
        previous_boy = create_delivery_boy(previous_boy);
    }

    return 1;
}

bool figure::market_buyer_take_resource_from_storageyard(building* warehouse) {
    e_resource resource;
    switch (collecting_item_id) {
    case INVENTORY_GOOD1:
        resource = RESOURCE_POTTERY;
        break;

    case INVENTORY_GOOD2:
        resource = RESOURCE_LUXURY_GOODS;
        break;
    case INVENTORY_GOOD3:
        resource = RESOURCE_LINEN;
        break;

    case INVENTORY_GOOD4:
        resource = RESOURCE_BEER;
        break;

    default:
        return false;
    }
    //    building *warehouse = building_get(warehouse);
    int stored = building_storageyard_get_amount(warehouse, resource);
    int num_loads = std::min<int>(stored, 200);

    if (num_loads <= 0) {
        return false;
    }

    building_storageyard_remove_resource(warehouse, resource, num_loads);

    // create delivery boys
    int boy1 = create_delivery_boy(id);
    if (num_loads > 100) {
        create_delivery_boy(boy1);
    }

    return true;
}
