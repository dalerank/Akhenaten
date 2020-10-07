#include "cartpusher.h"

#include "building/barracks.h"
#include "building/granary.h"
#include "building/industry.h"
#include "building/storage.h"
#include "building/warehouse.h"
#include "city/resource.h"
#include "core/calc.h"
#include "core/config.h"
#include "core/image.h"
#include "figure/combat.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "game/resource.h"
#include "map/road_network.h"
#include "map/routing_terrain.h"

static const int CART_OFFSET_MULTIPLE_LOADS_FOOD[] = {0, 0, 8, 16, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static const int CART_OFFSET_MULTIPLE_LOADS_NON_FOOD[] = {0, 0, 0, 0, 0, 8, 0, 16, 24, 32, 40, 48, 56, 64, 72, 80};
static const int CART_OFFSET_8_LOADS_FOOD[] = {0, 40, 48, 56, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void figure::determine_cartpusher_destination(building *b, int road_network_id) {
    map_point dst;
    int understaffed_storages = 0;

    // priority 1: warehouse if resource is on stockpile
    destination_building_id = building_warehouse_for_storing(0, tile_x, tile_y, b->output_resource_id, b->distance_from_entry, road_network_id, &understaffed_storages, &dst);
    if (!city_resource_is_stockpiled(b->output_resource_id))
        destination_building_id = 0;
    if (destination_building_id)
        return advance_action(FIGURE_ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE);

    // priority 2: accepting granary for food
    destination_building_id = building_granary_for_storing(tile_x, tile_y, b->output_resource_id, b->distance_from_entry, road_network_id, 0, &understaffed_storages, &dst);
    if (config_get(CONFIG_GP_CH_FARMS_DELIVER_CLOSE)) {
        int dist = 0;
        building *src_building = building_get(building_id);
        building *dst_building = building_get(destination_building_id);
        int src_int = src_building->type;
        if ((src_int >= BUILDING_WHEAT_FARM && src_int <= BUILDING_PIG_FARM) || src_int == BUILDING_WHARF)
            dist = calc_distance_with_penalty(src_building->x, src_building->y, dst_building->x, dst_building->y, src_building->distance_from_entry, dst_building->distance_from_entry);
        if (dist >= 64)
            destination_building_id = 0;
    }
    if (destination_building_id)
        return advance_action(FIGURE_ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY);

    // priority 3: workshop for raw material
    destination_building_id = building_get_workshop_for_raw_material_with_room(tile_x, tile_y, b->output_resource_id, b->distance_from_entry, road_network_id, &dst);
    if (destination_building_id)
        return advance_action(FIGURE_ACTION_23_CARTPUSHER_DELIVERING_TO_WORKSHOP);

    // priority 4: warehouse
    destination_building_id = building_warehouse_for_storing(0, tile_x, tile_y, b->output_resource_id, b->distance_from_entry, road_network_id, &understaffed_storages, &dst);
    if (destination_building_id)
        return advance_action(FIGURE_ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE);

    // priority 5: granary forced when on stockpile
    destination_building_id = building_granary_for_storing(tile_x, tile_y, b->output_resource_id, b->distance_from_entry, road_network_id, 1, &understaffed_storages, &dst);
    if (config_get(CONFIG_GP_CH_FARMS_DELIVER_CLOSE)) {
        int dist = 0;
        building *src_building = building_get(building_id);
        building *dst_building = building_get(destination_building_id);
        int src_int = src_building->type;
        if ((src_int >= BUILDING_WHEAT_FARM && src_int <= BUILDING_PIG_FARM) || src_int == BUILDING_WHARF)
            dist = calc_distance_with_penalty(src_building->x, src_building->y, dst_building->x, dst_building->y, src_building->distance_from_entry, dst_building->distance_from_entry);
        if (dist >= 64)
            destination_building_id = 0;
    }
    if (destination_building_id)
        return advance_action(FIGURE_ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY);

    // no one will accept
    min_max_seen = understaffed_storages ? 2 : 1;
//    if (type == 9)
//        advance_action(FIGURE_ACTION_59_WAREHOUSEMAN_RETURNING_WITH_RESOURCE);
//    else
    advance_action(ACTION_8_IDLE_RECALCULATE);
}
void figure::determine_cartpusher_destination_food(int road_network_id) {
    building *b = building_get(building_id);
    map_point dst;
    // priority 1: accepting granary for food
    int dst_building_id = building_granary_for_storing(tile_x, tile_y, b->output_resource_id, b->distance_from_entry, road_network_id, 0, 0, &dst);
    if (dst_building_id && config_get(CONFIG_GP_CH_FARMS_DELIVER_CLOSE)) {
        int dist = 0;
        building *dst_building = building_get(dst_building_id);
        if ((b->type >= BUILDING_WHEAT_FARM && b->type <= BUILDING_PIG_FARM) || b->type == BUILDING_WHARF)
            dist = calc_distance_with_penalty(b->x, b->y, dst_building->x, dst_building->y, b->distance_from_entry, dst_building->distance_from_entry);
        if (dist >= 64)
            dst_building_id = 0;
    }
    if (dst_building_id) {
        destination_building_id = dst_building_id;
        return advance_action(FIGURE_ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY);
//        set_destination(FIGURE_ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY, dst_building_id, dst.x, dst.y);
//        return;
    }
    // priority 2: warehouse
    dst_building_id = building_warehouse_for_storing(0, tile_x, tile_y, b->output_resource_id, b->distance_from_entry, road_network_id, 0, &dst);
    if (dst_building_id) {
        destination_building_id = dst_building_id;
        return advance_action(FIGURE_ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE);
//        set_destination(FIGURE_ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE, dst_building_id, dst.x, dst.y);
//        return;
    }
    // priority 3: granary
    dst_building_id = building_granary_for_storing(tile_x, tile_y, b->output_resource_id, b->distance_from_entry, road_network_id, 1, 0, &dst);
    if (dst_building_id) {
        destination_building_id = dst_building_id;
        return advance_action(FIGURE_ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY);
//        set_destination(FIGURE_ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY, dst_building_id, dst.x, dst.y);
//        return;
    }
    // no one will accept, stand idle
//    if (type == 9)
//        advance_action(FIGURE_ACTION_56_WAREHOUSEMAN_RETURNING_WITH_FOOD);
//    else
    advance_action(ACTION_8_IDLE_RECALCULATE);
}
void figure::reroute_cartpusher() {
    route_remove();
    if (!map_routing_citizen_is_passable_terrain(grid_offset_figure))
        action_state = FIGURE_ACTION_20_CARTPUSHER_INITIAL;
    wait_ticks = 0;
}
void figure::determine_granaryman_destination( int road_network_id) {
    map_point dst;
//    int dst_building_id;
    building *granary = building_get(building_id);
    if (!resource_id) {
        // getting granaryman
        destination_building_id = building_granary_for_getting(granary, &dst);
        if (destination_building_id) {
            loads_sold_or_carrying = 0;
            advance_action(FIGURE_ACTION_54_WAREHOUSEMAN_GETTING_FOOD);
//            set_destination(FIGURE_ACTION_54_WAREHOUSEMAN_GETTING_FOOD, dst_building_id, dst.x, dst.y);
            if (config_get(CONFIG_GP_CH_GETTING_GRANARIES_GO_OFFROAD))
                terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
        } else
            kill();
        return;
    }
    // delivering resource
    // priority 1: another granary
    destination_building_id = building_granary_for_storing(tile_x, tile_y, resource_id, granary->distance_from_entry, road_network_id, 0, 0, &dst);
    if (destination_building_id) {
//        set_destination(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE, dst_building_id, dst.x, dst.y);
        building_granary_remove_resource(granary, resource_id, 100);
        return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
//        return;
    }
    // priority 2: warehouse
    destination_building_id = building_warehouse_for_storing(0, tile_x, tile_y, resource_id, granary->distance_from_entry, road_network_id, 0, &dst);
    if (destination_building_id) {
//        set_destination(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE, dst_building_id, dst.x, dst.y);
        building_granary_remove_resource(granary, resource_id, 100);
        return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
//        return;
    }
    // priority 3: granary even though resource is on stockpile
    destination_building_id = building_granary_for_storing(tile_x, tile_y, resource_id, granary->distance_from_entry, road_network_id, 1, 0, &dst);
    if (destination_building_id) {
//        set_destination(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE, dst_building_id, dst.x, dst.y);
        building_granary_remove_resource(granary, resource_id, 100);
        return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
//        return;
    }
    // nowhere to go to: kill figure
//    min_max_seen = understaffed_storages ? 2 : 1;
//    if (type == 9)
//        advance_action(FIGURE_ACTION_56_WAREHOUSEMAN_RETURNING_WITH_FOOD);
//    else
//        advance_action(ACTION_8_IDLE_RECALCULATE);
    advance_action(FIGURE_ACTION_56_WAREHOUSEMAN_RETURNING_WITH_FOOD);
}
void figure::remove_resource_from_warehouse() {
    if (loads_sold_or_carrying)
        return;
    if (state != FIGURE_STATE_DEAD) {
        int err = building_warehouse_remove_resource(building_get(building_id), resource_id, 1);
        if (err)
            kill();
    }
}
void figure::determine_warehouseman_destination(int road_network_id) {
    map_point dst;

    ////// getting resources!
    if (!resource_id) {
        destination_building_id = building_warehouse_for_getting(building_get(building_id), collecting_item_id, &dst);
        if (destination_building_id) {
            loads_sold_or_carrying = 0;
            advance_action(FIGURE_ACTION_57_WAREHOUSEMAN_GETTING_RESOURCE);
            terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
        } else
            kill();
        return;
    }
    building *warehouse = building_get(building_id);

    ////// delivering resource!
    // priority 1: weapons to barracks
    destination_building_id = building_get_barracks_for_weapon(tile_x, tile_y, resource_id, road_network_id, warehouse->distance_from_entry, &dst);
    if (destination_building_id) {
        remove_resource_from_warehouse();
        return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
    }
    // priority 2: raw materials to workshop
    destination_building_id = building_get_workshop_for_raw_material_with_room(tile_x, tile_y, resource_id, warehouse->distance_from_entry, road_network_id, &dst);
    if (destination_building_id) {
        remove_resource_from_warehouse();
        return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
    }
    // priority 3: food to granary
    destination_building_id = building_granary_for_storing(tile_x, tile_y, resource_id, warehouse->distance_from_entry, road_network_id, 0, 0, &dst);
    if (destination_building_id) {
        remove_resource_from_warehouse();
        return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
    }
    // priority 4: food to getting granary
    destination_building_id = building_getting_granary_for_storing(tile_x, tile_y, resource_id, warehouse->distance_from_entry, road_network_id, &dst);
    if (destination_building_id) {
        remove_resource_from_warehouse();
        advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
    }
    // priority 5: resource to other warehouse
    destination_building_id = building_warehouse_for_storing(building_id, tile_x, tile_y, resource_id, warehouse->distance_from_entry, road_network_id, 0, &dst);
    int empty_warehouse = building_storage_get(building_get(building_id)->storage_id)->empty_all; // deliver to another warehouse because this one is being emptied
    if (destination_building_id && empty_warehouse) {
        if (destination_building_id == building_id)
            kill();
        else {
            remove_resource_from_warehouse();
            advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
        }
        return;
    }

//    // priority 6: raw material to well-stocked workshop
//    destination_building_id = building_get_workshop_for_raw_material(tile_x, tile_y, resource_id, warehouse->distance_from_entry, road_network_id, &dst);
//    if (destination_building_id) {
//        remove_resource_from_warehouse();
//        return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
//    }

    // no destination: kill figure
//    advance_action(ACTION_8_IDLE_RECALCULATE);
    advance_action(FIGURE_ACTION_59_WAREHOUSEMAN_RETURNING_WITH_RESOURCE);
}

void figure::cartpusher_action() {

//    if (config_get(CONFIG_GP_CH_GETTING_GRANARIES_GO_OFFROAD))
//        terrain_usage = TERRAIN_USAGE_PREFER_ROADS;

    building *b = building_get(building_id);
    int from_industry = true;
    if (type == BUILDING_WAREHOUSE)
        from_industry = false;
    int road_network_id = map_road_network_get(grid_offset_figure);
    switch (action_state) {
        case ACTION_8_IDLE_RECALCULATE:
        case FIGURE_ACTION_20_CARTPUSHER_INITIAL:
            destination_building_id = 0;
            direction = previous_tile_direction;
            anim_frame = 0;
//            if (!map_routing_citizen_is_passable(grid_offset_figure))
//                kill();
            wait_ticks++;
            if (wait_ticks > 30) {
                wait_ticks = 0;
                determine_cartpusher_destination(b, road_network_id);
            }
            break;
        case ACTION_9_DELIVERING_GOODS:
            do_gotobuilding(destination_building_id, true, TERRAIN_USAGE_ROADS, ACTION_12_UNLOADING1, ACTION_8_IDLE_RECALCULATE);
            break;
        case ACTION_10_DELIVERING_FOOD:
            do_gotobuilding(destination_building_id, true, TERRAIN_USAGE_ROADS, ACTION_13_UNLOADING2, ACTION_8_IDLE_RECALCULATE);
            break;
        case FIGURE_ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE:
            do_gotobuilding(destination_building_id, true, TERRAIN_USAGE_ROADS, FIGURE_ACTION_24_CARTPUSHER_AT_WAREHOUSE, ACTION_8_IDLE_RECALCULATE);
            break;
        case FIGURE_ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY:
            do_gotobuilding(destination_building_id, true, TERRAIN_USAGE_ROADS, FIGURE_ACTION_25_CARTPUSHER_AT_GRANARY, ACTION_8_IDLE_RECALCULATE);
            break;
        case FIGURE_ACTION_23_CARTPUSHER_DELIVERING_TO_WORKSHOP:
            do_gotobuilding(destination_building_id, true, TERRAIN_USAGE_ROADS, FIGURE_ACTION_26_CARTPUSHER_AT_WORKSHOP, ACTION_8_IDLE_RECALCULATE);
            break;

        case ACTION_12_UNLOADING1:
        case ACTION_13_UNLOADING2:
        case FIGURE_ACTION_24_CARTPUSHER_AT_WAREHOUSE:
        case FIGURE_ACTION_25_CARTPUSHER_AT_GRANARY:
        case FIGURE_ACTION_26_CARTPUSHER_AT_WORKSHOP:
            wait_ticks++;
            if (wait_ticks > 5) {
                building *dest = building_get(destination_building_id);
                if (dest->state != BUILDING_STATE_VALID || dest->figure_id != id)
                    advance_action(ACTION_8_IDLE_RECALCULATE);
                bool delivery_check = false;
                switch (dest->type) {
                    case BUILDING_WAREHOUSE:
                    case BUILDING_WAREHOUSE_SPACE:
                        delivery_check = building_warehouse_add_resource(dest, resource_id);
                        break;
                    case BUILDING_GRANARY:
                        delivery_check = building_granary_add_resource(dest, resource_id, from_industry);
                        break;
                    case BUILDING_BARRACKS:
                        building_barracks_add_weapon(dest);
                        delivery_check = true;
                        break;
                    default:
                        building_workshop_add_raw_material(dest);
                        delivery_check = true;
                        break;
                }
                if (delivery_check)
                    loads_sold_or_carrying -= 1;
                if (!loads_sold_or_carrying) {
                    advance_action(ACTION_11_RETURNING_EMPTY);
                    wait_ticks = 0;
                } else if (!delivery_check)
                    advance_action(ACTION_8_IDLE_RECALCULATE);
            }
            anim_frame = 0;
            break;
        case ACTION_11_RETURNING_EMPTY:
        case ACTION_15_RETURNING2:
        case FIGURE_ACTION_27_CARTPUSHER_RETURNING:
            if (do_returnhome()) {
                // has returned - get back goods that are left?
            }
            break;
    }
    cart_update_image();
}
void figure::warehouseman_action() {

//    if (config_get(CONFIG_GP_CH_GETTING_GRANARIES_GO_OFFROAD))
//        terrain_usage = TERRAIN_USAGE_PREFER_ROADS;

    int road_network_id = map_road_network_get(grid_offset_figure);
    switch (action_state) {
        case ACTION_8_IDLE_RECALCULATE:
        case FIGURE_ACTION_50_WAREHOUSEMAN_CREATED: {
            destination_building_id = 0;
//            direction = previous_tile_direction;
            building *b = building_get(building_id);
            wait_ticks++;
            if (wait_ticks > 2) {
                wait_ticks = 0;
                if (building_get(building_id)->type == BUILDING_GRANARY)
                    determine_granaryman_destination(road_network_id);
                else
                    determine_warehouseman_destination(road_network_id);
            }
            anim_frame = 0;
            break;
        }
        case ACTION_9_DELIVERING_GOODS:
        case FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE:
            do_gotobuilding(destination_building_id, true, TERRAIN_USAGE_ROADS, FIGURE_ACTION_52_WAREHOUSEMAN_AT_DELIVERY_BUILDING, ACTION_8_IDLE_RECALCULATE);
            break;
//            move_ticks(1);
//            if (direction == DIR_FIGURE_AT_DESTINATION)
//                action_state = FIGURE_ACTION_52_WAREHOUSEMAN_AT_DELIVERY_BUILDING;
//            else if (direction == DIR_FIGURE_REROUTE)
//                route_remove();
//            else if (direction == DIR_FIGURE_LOST)
//                kill();
//            break;
        case ACTION_12_UNLOADING1:
        case FIGURE_ACTION_52_WAREHOUSEMAN_AT_DELIVERY_BUILDING:
            wait_ticks++;
//            direction = previous_tile_direction;
            if (wait_ticks > 4) {
                bool delivery_check = false;
                building *dest = building_get(destination_building_id);
                if (dest->state != BUILDING_STATE_VALID || dest->figure_id != id)
                    advance_action(ACTION_8_IDLE_RECALCULATE);
                switch (dest->type) {
                    case BUILDING_GRANARY:
                        delivery_check = building_granary_add_resource(dest, resource_id, 0);
                        break;
                    case BUILDING_BARRACKS:
                        building_barracks_add_weapon(dest);
                        delivery_check = true;
                        break;
                    case BUILDING_WAREHOUSE:
                    case BUILDING_WAREHOUSE_SPACE:
                        delivery_check = building_warehouse_add_resource(dest, resource_id);
                        break;
                    default: // workshop
                        if (dest->loads_stored < 2) {
                            building_workshop_add_raw_material(dest);
                            delivery_check = true; // temp
                        } else
                            advance_action(ACTION_8_IDLE_RECALCULATE);
                        break;
                }
                if (delivery_check)
                    loads_sold_or_carrying -= 1;
                if (!loads_sold_or_carrying) {
                    advance_action(ACTION_11_RETURNING_EMPTY);
                    wait_ticks = 0;
                } else if (!delivery_check)
                    advance_action(ACTION_8_IDLE_RECALCULATE);
//                // BUG: what if warehouse/granary is full and returns false?
//                action_state = FIGURE_ACTION_53_WAREHOUSEMAN_RETURNING_EMPTY;
//                wait_ticks = 0;
//                destination_x = source_x;
//                destination_y = source_y;
            }
            anim_frame = 0;
            break;
        case ACTION_11_RETURNING_EMPTY:
        case FIGURE_ACTION_53_WAREHOUSEMAN_RETURNING_EMPTY:
            if (do_returnhome()) {
                // has returned - get back goods that are left?
            }
//            cart_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER_CART); // empty
//            move_ticks(1);
//            if (direction == DIR_FIGURE_AT_DESTINATION || direction == DIR_FIGURE_LOST)
//                kill();
//            else if (direction == DIR_FIGURE_REROUTE)
//                route_remove();
            break;
        case FIGURE_ACTION_54_WAREHOUSEMAN_GETTING_FOOD:
            do_gotobuilding(destination_building_id, true, TERRAIN_USAGE_ROADS, FIGURE_ACTION_55_WAREHOUSEMAN_AT_GRANARY, ACTION_8_IDLE_RECALCULATE);
//            cart_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER_CART); // empty
//            move_ticks(1);
//            if (direction == DIR_FIGURE_AT_DESTINATION)
//                action_state = FIGURE_ACTION_55_WAREHOUSEMAN_AT_GRANARY;
//            else if (direction == DIR_FIGURE_REROUTE)
//                route_remove();
//            else if (direction == DIR_FIGURE_LOST)
//                kill();
            break;
        case FIGURE_ACTION_55_WAREHOUSEMAN_AT_GRANARY:
            wait_ticks++;
//            direction = previous_tile_direction;
            if (wait_ticks > 4) {
                int resource;
                loads_sold_or_carrying = building_granary_remove_for_getting_deliveryman(building_get(destination_building_id), building_get(building_id), &resource);
                resource_id = resource;
                advance_action(FIGURE_ACTION_56_WAREHOUSEMAN_RETURNING_WITH_FOOD);
//                action_state = FIGURE_ACTION_56_WAREHOUSEMAN_RETURNING_WITH_FOOD;
//                wait_ticks = 0;
//                destination_x = source_x;
//                destination_y = source_y;
//                route_remove();
            }
            anim_frame = 0;
            break;
        case ACTION_14_RETURNING_WITH_FOOD:
        case FIGURE_ACTION_56_WAREHOUSEMAN_RETURNING_WITH_FOOD:
        case FIGURE_ACTION_59_WAREHOUSEMAN_RETURNING_WITH_RESOURCE:
            // update graphic
            if (do_returnhome()) {
                building *b = building_get(building_id);
                bool delivery_check = false;
                for (int i = 0; i < loads_sold_or_carrying; i++) {
                    switch (b->type) {
                        case BUILDING_GRANARY:
                            delivery_check = building_granary_add_resource(building_get(building_id), resource_id, 0);
                            break;
                        case BUILDING_WAREHOUSE:
                        case BUILDING_WAREHOUSE_SPACE:
                            delivery_check = building_warehouse_add_resource(building_get(building_id), resource_id);
                            break;
                    }
                }
                if (!delivery_check)
                    advance_action(ACTION_8_IDLE_RECALCULATE);
            }
//            if (loads_sold_or_carrying <= 0)
//                cart_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER_CART); // empty
//            else if (loads_sold_or_carrying == 1) {
////                set_cart_graphic();
//            } else {
//                if (loads_sold_or_carrying >= 8)
//                    cart_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER_CART_MULTIPLE_FOOD) + CART_OFFSET_8_LOADS_FOOD[resource_id];
//                else
//                    cart_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER_CART_MULTIPLE_FOOD) + CART_OFFSET_MULTIPLE_LOADS_FOOD[resource_id];
//                cart_image_id += resource_image_offset(resource_id, RESOURCE_IMAGE_FOOD_CART);
//            }
//            move_ticks(1);
//            if (direction == DIR_FIGURE_AT_DESTINATION) {
//                for (int i = 0; i < loads_sold_or_carrying; i++)
//                    building_granary_add_resource(building_get(building_id), resource_id, 0);
//                kill();
//            } else if (direction == DIR_FIGURE_REROUTE)
//                route_remove();
//            else if (direction == DIR_FIGURE_LOST)
//                kill();
            break;
        case ACTION_15_GETTING_GOODS:
        case FIGURE_ACTION_57_WAREHOUSEMAN_GETTING_RESOURCE:
            do_gotobuilding(destination_building_id, true, TERRAIN_USAGE_ROADS, FIGURE_ACTION_58_WAREHOUSEMAN_AT_WAREHOUSE, ACTION_8_IDLE_RECALCULATE);
//            terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
//            cart_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER_CART); // empty
//            move_ticks(1);
//            if (direction == DIR_FIGURE_AT_DESTINATION)
//                action_state = FIGURE_ACTION_58_WAREHOUSEMAN_AT_WAREHOUSE;
//            else if (direction == DIR_FIGURE_REROUTE)
//                route_remove();
//            else if (direction == DIR_FIGURE_LOST)
//                kill();
            break;
        case FIGURE_ACTION_58_WAREHOUSEMAN_AT_WAREHOUSE:
//            terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
            wait_ticks++;
//            direction = previous_tile_direction;
            if (wait_ticks > 4) {
                loads_sold_or_carrying = 0;
                if (loads_sold_or_carrying < 4 && 0 == building_warehouse_remove_resource(building_get(destination_building_id), collecting_item_id, 1))
                    loads_sold_or_carrying++;
                else { // made it so it goes through the loads bit by bit??
                    resource_id = collecting_item_id;
                    advance_action(FIGURE_ACTION_59_WAREHOUSEMAN_RETURNING_WITH_RESOURCE);
                }
//                action_state = FIGURE_ACTION_59_WAREHOUSEMAN_RETURNING_WITH_RESOURCE;
//                wait_ticks = 0;
//                destination_x = source_x;
//                destination_y = source_y;
//                route_remove();
            }
            anim_frame = 0;
            break;
//        case FIGURE_ACTION_59_WAREHOUSEMAN_RETURNING_WITH_RESOURCE:
//            terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
            // update graphic
//            if (loads_sold_or_carrying <= 0)
//                cart_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER_CART); // empty
//            else if (loads_sold_or_carrying == 1) {
////                set_cart_graphic();
//            } else {
//                if (resource_id == RESOURCE_WHEAT || resource_id == RESOURCE_VEGETABLES ||
//                    resource_id == RESOURCE_FRUIT || resource_id == RESOURCE_MEAT_C3) {
//                    cart_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER_CART_MULTIPLE_FOOD) + CART_OFFSET_MULTIPLE_LOADS_FOOD[resource_id];
//                } else
//                    cart_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER_CART_MULTIPLE_RESOURCE) + CART_OFFSET_MULTIPLE_LOADS_NON_FOOD[resource_id];
//                cart_image_id += resource_image_offset(resource_id, RESOURCE_IMAGE_FOOD_CART);
//            }
//            move_ticks(1);
//            if (direction == DIR_FIGURE_AT_DESTINATION) {
//            if (do_returnhome())
//                for (int i = 0; i < loads_sold_or_carrying; i++)
//                    building_warehouse_add_resource(building_get(building_id), resource_id);
//                kill();
//            } else if (direction == DIR_FIGURE_REROUTE)
//                route_remove();
//            else if (direction == DIR_FIGURE_LOST)
//                kill();
//            break;
    }

    cart_update_image();
}
