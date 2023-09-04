#include "market.h"

#include "building/building.h"
#include "building/granary.h"
#include "building/storage.h"
#include "io/log.h"
#include "building/storage_yard.h"
#include "figure/combat.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "game/resource.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"

void figure::market_buyer_action() {
    image_set_animation(GROUP_FIGURE_MARKET_LADY);
    switch (action_state) {
    case 8:
    case FIGURE_ACTION_145_MARKET_BUYER_GOING_TO_STORAGE:
        if (do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, FIGURE_ACTION_146_MARKET_BUYER_RETURNING)) {
            if (collecting_item_id > 3) {
                if (!take_resource_from_storageyard(destination())) {
                    poof();
                }

            } else {
                if (!take_food_from_granary(home(), destination())) {
                    poof();
                }
            }
        }
        break;

    case 9:
    case ACTION_11_RETURNING_EMPTY:
    case FIGURE_ACTION_146_MARKET_BUYER_RETURNING:
        if (do_returnhome()) {
            logs::info("stop");
        }
        break;
    }
}

int figure::create_delivery_boy(int leader_id) {
    figure* boy = figure_create(FIGURE_DELIVERY_BOY, tile, 0);
    boy->leading_figure_id = leader_id;
    boy->collecting_item_id = collecting_item_id;
    boy->set_home(homeID());
    return boy->id;
}

int figure::take_food_from_granary(building* market, building* granary) {
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
    for (int i = 0; i < num_loads; i++)
        previous_boy = create_delivery_boy(previous_boy);

    return 1;
}

bool figure::take_resource_from_storageyard(building* warehouse) {
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

void figure::delivery_boy_action() {
    //    is_ghost = false;
    //    terrain_usage = TERRAIN_USAGE_ROADS;
    //    figure_image_increase_offset(12);
    //    cart_image_id = 0;

    figure* leader = figure_get(leading_figure_id);
    //    if (leading_figure_id <= 0 || leader->action_state == FIGURE_ACTION_149_CORPSE)
    //        poof();
    //    else {
    if (leader->state == FIGURE_STATE_ALIVE) {
        if (leader->type == FIGURE_MARKET_BUYER || leader->type == FIGURE_DELIVERY_BOY) {
            follow_ticks(1);
        } else {
            poof();
        }
    } else { // leader arrived at market, drop resource at market
        home()->data.market.inventory[collecting_item_id] += 100;
        poof();
    }
    //    }
    if (leader->is_ghost) {
        is_ghost = true;
    }

    int dir = figure_image_normalize_direction(direction < 8 ? direction : previous_tile_direction);
    if (action_state == FIGURE_ACTION_149_CORPSE) {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_GRANARY_BOY_DEATH) + figure_image_corpse_offset();
    } else {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_GRANARY_BOY) + dir + 8 * anim_frame;
    }
}
