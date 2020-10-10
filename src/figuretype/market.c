#include "market.h"

#include "building/building.h"
#include "building/granary.h"
#include "building/storage.h"
#include "building/warehouse.h"
#include "core/image.h"
#include "figure/combat.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "game/resource.h"

void figure::market_buyer_action() {
    image_set_animation(GROUP_FIGURE_MARKET_LADY);
    switch (action_state) {
        case FIGURE_ACTION_145_MARKET_BUYER_GOING_TO_STORAGE:
            move_ticks(1);
            if (direction == DIR_FIGURE_AT_DESTINATION) {
                if (collecting_item_id > 3) {
                    if (!take_resource_from_warehouse(destination_building_id))
                        kill();

                } else {
                    if (!take_food_from_granary(building_id, destination_building_id))
                        kill();

                }
                action_state = FIGURE_ACTION_146_MARKET_BUYER_RETURNING;
                destination_x = source_x;
                destination_y = source_y;
            } else if (direction == DIR_FIGURE_REROUTE || direction == DIR_FIGURE_LOST) {
                action_state = FIGURE_ACTION_146_MARKET_BUYER_RETURNING;
                destination_x = source_x;
                destination_y = source_y;
                route_remove();
            }
            break;
        case ACTION_11_RETURNING_EMPTY:
        case FIGURE_ACTION_146_MARKET_BUYER_RETURNING:
            move_ticks(1);
            if (direction == DIR_FIGURE_AT_DESTINATION || direction == DIR_FIGURE_LOST)
                kill();
            else if (direction == DIR_FIGURE_REROUTE)
                route_remove();

            break;
    }
}

int figure::create_delivery_boy(int leader_id) {
    figure *boy = figure_create(FIGURE_DELIVERY_BOY, tile_x, tile_y, 0);
    boy->leading_figure_id = leader_id;
    boy->collecting_item_id = collecting_item_id;
    boy->building_id = building_id;
    return boy->id;
}
int figure::take_food_from_granary(int market_id, int granary_id) {
    int resource;
    switch (collecting_item_id) {
        case INVENTORY_FOOD1:
            resource = RESOURCE_WHEAT;
            break;
        case INVENTORY_FOOD2:
            resource = RESOURCE_VEGETABLES;
            break;
        case INVENTORY_FOOD3:
            resource = RESOURCE_FRUIT;
            break;
        case INVENTORY_FOOD4:
            resource = RESOURCE_MEAT_C3;
            break;
        default:
            return 0;
    }
    building *granary = building_get(granary_id);
    int market_units = building_get(market_id)->data.market.inventory[collecting_item_id];
    int max_units = (collecting_item_id == INVENTORY_FOOD1 ? 800 : 600) - market_units;
    int granary_units = granary->data.granary.resource_stored[resource];
    int num_loads;
    if (granary_units >= 800)
        num_loads = 8;
    else if (granary_units >= 700)
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
    else {
        num_loads = 0;
    }
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
int figure::take_resource_from_warehouse(int warehouse_id) {
    int resource;
    switch (collecting_item_id) {
        case INVENTORY_GOOD1:
            resource = RESOURCE_POTTERY_C3;
            break;
        case INVENTORY_GOOD2:
            resource = RESOURCE_FURNITURE;
            break;
        case INVENTORY_GOOD3:
            resource = RESOURCE_OIL_C3;
            break;
        case INVENTORY_GOOD4:
            resource = RESOURCE_WINE;
            break;
        default:
            return 0;
    }
    building *warehouse = building_get(warehouse_id);
    int num_loads;
    int stored = building_warehouse_get_amount(warehouse, resource);
    if (stored < 2)
        num_loads = stored;
    else {
        num_loads = 2;
    }
    if (num_loads <= 0)
        return 0;

    building_warehouse_remove_resource(warehouse, resource, num_loads);

    // create delivery boys
    int boy1 = create_delivery_boy(id);
    if (num_loads > 1)
        create_delivery_boy(boy1);

    return 1;
}
void figure::delivery_boy_action() {
//    is_ghost = 0;
//    terrain_usage = TERRAIN_USAGE_ROADS;
//    figure_image_increase_offset(12);
//    cart_image_id = 0;

    figure *leader = figure_get(leading_figure_id);
//    if (leading_figure_id <= 0 || leader->action_state == FIGURE_ACTION_149_CORPSE)
//        kill();
//    else {
        if (leader->state == FIGURE_STATE_ALIVE) {
            if (leader->type == FIGURE_MARKET_BUYER || leader->type == FIGURE_DELIVERY_BOY)
                follow_ticks(1);
            else
                kill();
        } else { // leader arrived at market, drop resource at market
            building_get(building_id)->data.market.inventory[collecting_item_id] += 100;
            kill();
        }
//    }
    if (leader->is_ghost)
        is_ghost = 1;

    int dir = figure_image_normalize_direction(direction < 8 ? direction : previous_tile_direction);
    if (action_state == FIGURE_ACTION_149_CORPSE) {
        sprite_image_id = image_id_from_group(GROUP_FIGURE_DELIVERY_BOY) + 96 + figure_image_corpse_offset();
    } else
        sprite_image_id = image_id_from_group(GROUP_FIGURE_DELIVERY_BOY) + dir + 8 * anim_frame;
}
