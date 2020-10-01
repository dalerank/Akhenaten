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

void figure::set_cartpusher_graphic() {
    cart_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER_CART) + 8 * resource_id + resource_image_offset(resource_id, RESOURCE_IMAGE_CART);
}

void figure::set_destination(int action, int building_id, int x_dst, int y_dst) {
    destination_building_id = building_id;
    action_state = action;
    wait_ticks = 0;
    destination_x = x_dst;
    destination_y = y_dst;
}
void figure::determine_cartpusher_destination(building *b, int road_network_id) {
    map_point dst;
    int understaffed_storages = 0;

    // priority 1: warehouse if resource is on stockpile
    int dst_building_id = building_warehouse_for_storing(0, tile_x, tile_y, b->output_resource_id, b->distance_from_entry, road_network_id, &understaffed_storages, &dst);
    if (!city_resource_is_stockpiled(b->output_resource_id))
        dst_building_id = 0;
    if (dst_building_id) {
        set_destination(FIGURE_ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE, dst_building_id, dst.x, dst.y);
        return;
    }
    // priority 2: accepting granary for food
    dst_building_id = building_granary_for_storing(tile_x, tile_y, b->output_resource_id, b->distance_from_entry, road_network_id, 0, &understaffed_storages, &dst);
    if (config_get(CONFIG_GP_CH_FARMS_DELIVER_CLOSE)) {
        int dist = 0;
        building *src_building = building_get(building_id);
        building *dst_building = building_get(dst_building_id);
        int src_int = src_building->type;
        if ((src_int >= BUILDING_WHEAT_FARM && src_int <= BUILDING_PIG_FARM) || src_int == BUILDING_WHARF)
            dist = calc_distance_with_penalty(src_building->x, src_building->y, dst_building->x, dst_building->y, src_building->distance_from_entry, dst_building->distance_from_entry);
        if (dist >= 64)
            dst_building_id = 0;

    }
    if (dst_building_id) {
        set_destination(FIGURE_ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY, dst_building_id, dst.x, dst.y);
        return;
    }
    // priority 3: workshop for raw material
    dst_building_id = building_get_workshop_for_raw_material_with_room(tile_x, tile_y, b->output_resource_id, b->distance_from_entry, road_network_id, &dst);
    if (dst_building_id) {
        set_destination(FIGURE_ACTION_23_CARTPUSHER_DELIVERING_TO_WORKSHOP, dst_building_id, dst.x, dst.y);
        return;
    }
    // priority 4: warehouse
    dst_building_id = building_warehouse_for_storing(0, tile_x, tile_y, b->output_resource_id, b->distance_from_entry, road_network_id, &understaffed_storages, &dst);
    if (dst_building_id) {
        set_destination(FIGURE_ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE, dst_building_id, dst.x, dst.y);
        return;
    }
    // priority 5: granary forced when on stockpile

    dst_building_id = building_granary_for_storing(tile_x, tile_y, b->output_resource_id, b->distance_from_entry, road_network_id, 1, &understaffed_storages, &dst);
    if (config_get(CONFIG_GP_CH_FARMS_DELIVER_CLOSE)) {
        int dist = 0;
        building *src_building = building_get(building_id);
        building *dst_building = building_get(dst_building_id);
        int src_int = src_building->type;
        if ((src_int >= BUILDING_WHEAT_FARM && src_int <= BUILDING_PIG_FARM) || src_int == BUILDING_WHARF)
            dist = calc_distance_with_penalty(src_building->x, src_building->y, dst_building->x, dst_building->y, src_building->distance_from_entry, dst_building->distance_from_entry);
        if (dist >= 64)
            dst_building_id = 0;

    }
    if (dst_building_id) {
        set_destination(FIGURE_ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY, dst_building_id, dst.x, dst.y);
        return;
    }
    // no one will accept
    wait_ticks = 0;
    // set cartpusher text
    min_max_seen = understaffed_storages ? 2 : 1;
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
        set_destination(FIGURE_ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY, dst_building_id, dst.x, dst.y);
        return;
    }
    // priority 2: warehouse
    dst_building_id = building_warehouse_for_storing(0, tile_x, tile_y, b->output_resource_id, b->distance_from_entry, road_network_id, 0, &dst);
    if (dst_building_id) {
        set_destination(FIGURE_ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE, dst_building_id, dst.x, dst.y);
        return;
    }
    // priority 3: granary
    dst_building_id = building_granary_for_storing(tile_x, tile_y, b->output_resource_id, b->distance_from_entry, road_network_id, 1, 0, &dst);
    if (dst_building_id) {
        set_destination(FIGURE_ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY, dst_building_id, dst.x, dst.y);
        return;
    }
    // no one will accept, stand idle
    wait_ticks = 0;
}
void figure::cart_update_image() {
    int dir = figure_image_normalize_direction( direction < 8 ? direction : previous_tile_direction);

    if (action_state == FIGURE_ACTION_149_CORPSE) {
        image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER) + figure_image_corpse_offset() + 96;
        cart_image_id = 0;
    } else
        image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER) + dir + 8 * image_offset;
    if (cart_image_id) {
        cart_image_id += dir;
        figure_image_set_cart_offset(dir);
        if (loads_sold_or_carrying >= 8)
            y_offset_cart -= 40;

    }
}
void figure::reroute_cartpusher() {
    route_remove();
    if (!map_routing_citizen_is_passable_terrain(grid_offset))
        action_state = FIGURE_ACTION_20_CARTPUSHER_INITIAL;
    wait_ticks = 0;
}
void figure::determine_granaryman_destination( int road_network_id) {
    map_point dst;
    int dst_building_id;
    building *granary = building_get(building_id);
    if (!resource_id) {
        // getting granaryman
        dst_building_id = building_granary_for_getting(granary, &dst);
        if (dst_building_id) {
            loads_sold_or_carrying = 0;
            set_destination(FIGURE_ACTION_54_WAREHOUSEMAN_GETTING_FOOD, dst_building_id, dst.x, dst.y);
            if (config_get(CONFIG_GP_CH_GETTING_GRANARIES_GO_OFFROAD))
                terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
        } else
            state = FIGURE_STATE_DEAD;
        return;
    }
    // delivering resource
    // priority 1: another granary
    dst_building_id = building_granary_for_storing(tile_x, tile_y, resource_id, granary->distance_from_entry, road_network_id, 0, 0, &dst);
    if (dst_building_id) {
        set_destination(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE, dst_building_id, dst.x, dst.y);
        building_granary_remove_resource(granary, resource_id, 100);
        return;
    }
    // priority 2: warehouse
    dst_building_id = building_warehouse_for_storing(0, tile_x, tile_y, resource_id, granary->distance_from_entry, road_network_id, 0, &dst);
    if (dst_building_id) {
        set_destination(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE, dst_building_id, dst.x, dst.y);
        building_granary_remove_resource(granary, resource_id, 100);
        return;
    }
    // priority 3: granary even though resource is on stockpile
    dst_building_id = building_granary_for_storing(tile_x, tile_y, resource_id, granary->distance_from_entry, road_network_id, 1, 0, &dst);
    if (dst_building_id) {
        set_destination(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE, dst_building_id, dst.x, dst.y);
        building_granary_remove_resource(granary, resource_id, 100);
        return;
    }
    // nowhere to go to: kill figure
    state = FIGURE_STATE_DEAD;
}
void figure::remove_resource_from_warehouse() {
    if (state != FIGURE_STATE_DEAD) {
        int err = building_warehouse_remove_resource(building_get(building_id), resource_id, 1);
        if (err)
            state = FIGURE_STATE_DEAD;

    }
}
void figure::determine_warehouseman_destination(int road_network_id) {
    map_point dst;
    int dst_building_id;
    if (!resource_id) {
        // getting warehouseman
        dst_building_id = building_warehouse_for_getting(building_get(building_id), collecting_item_id, &dst);
        if (dst_building_id) {
            loads_sold_or_carrying = 0;
            set_destination(FIGURE_ACTION_57_WAREHOUSEMAN_GETTING_RESOURCE, dst_building_id, dst.x, dst.y);
            terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
        } else
            state = FIGURE_STATE_DEAD;
        return;
    }
    building *warehouse = building_get(building_id);
    // delivering resource
    // priority 1: weapons to barracks
    dst_building_id = building_get_barracks_for_weapon(tile_x, tile_y, resource_id, road_network_id, warehouse->distance_from_entry, &dst);
    if (dst_building_id) {
        set_destination(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE, dst_building_id, dst.x, dst.y);
        remove_resource_from_warehouse();
        return;
    }
    // priority 2: raw materials to workshop
    dst_building_id = building_get_workshop_for_raw_material_with_room(tile_x, tile_y, resource_id, warehouse->distance_from_entry, road_network_id, &dst);
    if (dst_building_id) {
        set_destination(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE, dst_building_id, dst.x, dst.y);
        remove_resource_from_warehouse();
        return;
    }
    // priority 3: food to granary
    dst_building_id = building_granary_for_storing(tile_x, tile_y, resource_id, warehouse->distance_from_entry, road_network_id, 0, 0, &dst);
    if (dst_building_id) {
        set_destination(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE, dst_building_id, dst.x, dst.y);
        remove_resource_from_warehouse();
        return;
    }
    // priority 4: food to getting granary
    dst_building_id = building_getting_granary_for_storing(tile_x, tile_y, resource_id, warehouse->distance_from_entry, road_network_id, &dst);
    if (dst_building_id) {
        set_destination(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE, dst_building_id, dst.x, dst.y);
        remove_resource_from_warehouse();
        return;
    }
    // priority 5: resource to other warehouse
    dst_building_id = building_warehouse_for_storing(building_id, tile_x, tile_y, resource_id, warehouse->distance_from_entry, road_network_id, 0, &dst);

    int empty_warehouse = building_storage_get(building_get(
            building_id)->storage_id)->empty_all; // deliver to another warehouse because this one is being emptied
    if (dst_building_id && empty_warehouse) {
        if (dst_building_id == building_id)
            state = FIGURE_STATE_DEAD;
        else {
            set_destination(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE, dst_building_id, dst.x, dst.y);
            remove_resource_from_warehouse();
        }
        return;
    }
    // priority 6: raw material to well-stocked workshop
    dst_building_id = building_get_workshop_for_raw_material(tile_x, tile_y, resource_id, warehouse->distance_from_entry, road_network_id, &dst);
    if (dst_building_id) {
        set_destination(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE, dst_building_id, dst.x, dst.y);
        remove_resource_from_warehouse();
        return;
    }
    // no destination: kill figure
    state = FIGURE_STATE_DEAD;
}

void figure::cartpusher_action() {
    figure_image_increase_offset(12);
    cart_image_id = 0;
    int road_network_id = map_road_network_get(grid_offset);
    terrain_usage = TERRAIN_USAGE_ROADS;
    building *b = building_get(building_id);

    switch (action_state) {
        case FIGURE_ACTION_150_ATTACK:
            figure_combat_handle_attack();
            break;
        case FIGURE_ACTION_149_CORPSE:
            figure_combat_handle_corpse();
            break;
        case FIGURE_ACTION_20_CARTPUSHER_INITIAL:
            set_cart_graphic();
            if (!map_routing_citizen_is_passable(grid_offset))
                state = FIGURE_STATE_DEAD;
            if (b->state != BUILDING_STATE_IN_USE || b->figure_id != id)
                state = FIGURE_STATE_DEAD;
            wait_ticks++;
            if (wait_ticks > 30)
                determine_cartpusher_destination(b, road_network_id);

            image_offset = 0;
            break;
        case FIGURE_ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE:
            set_cart_graphic();
            move_ticks(1);
            if (direction == DIR_FIGURE_AT_DESTINATION)
                action_state = FIGURE_ACTION_24_CARTPUSHER_AT_WAREHOUSE;
            else if (direction == DIR_FIGURE_REROUTE)
                reroute_cartpusher();
            else if (direction == DIR_FIGURE_LOST)
                state = FIGURE_STATE_DEAD;

            if (building_get(destination_building_id)->state != BUILDING_STATE_IN_USE)
                state = FIGURE_STATE_DEAD;

            break;
        case FIGURE_ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY:
            set_cart_graphic();
            move_ticks(1);
            if (direction == DIR_FIGURE_AT_DESTINATION)
                action_state = FIGURE_ACTION_25_CARTPUSHER_AT_GRANARY;
            else if (direction == DIR_FIGURE_REROUTE)
                reroute_cartpusher();
            else if (direction == DIR_FIGURE_LOST) {
                action_state = FIGURE_ACTION_20_CARTPUSHER_INITIAL;
                wait_ticks = 0;
            }
            if (building_get(destination_building_id)->state != BUILDING_STATE_IN_USE)
                state = FIGURE_STATE_DEAD;
            break;
        case FIGURE_ACTION_23_CARTPUSHER_DELIVERING_TO_WORKSHOP:
            set_cart_graphic();
            move_ticks(1);
            if (direction == DIR_FIGURE_AT_DESTINATION)
                action_state = FIGURE_ACTION_26_CARTPUSHER_AT_WORKSHOP;
            else if (direction == DIR_FIGURE_REROUTE)
                reroute_cartpusher();
            else if (direction == DIR_FIGURE_LOST)
                state = FIGURE_STATE_DEAD;
            break;
        case FIGURE_ACTION_24_CARTPUSHER_AT_WAREHOUSE:
            wait_ticks++;
            if (wait_ticks > 10) {
                if (building_warehouse_add_resource(building_get(destination_building_id), resource_id)) {
                    action_state = FIGURE_ACTION_27_CARTPUSHER_RETURNING;
                    wait_ticks = 0;
                    destination_x = source_x;
                    destination_y = source_y;
                } else {
                    route_remove();
                    action_state = FIGURE_ACTION_20_CARTPUSHER_INITIAL;
                    wait_ticks = 0;
                }
            }
            image_offset = 0;
            break;
        case FIGURE_ACTION_25_CARTPUSHER_AT_GRANARY:
            wait_ticks++;
            if (wait_ticks > 5) {
                if (building_granary_add_resource(building_get(destination_building_id), resource_id, 1)) {
                    action_state = FIGURE_ACTION_27_CARTPUSHER_RETURNING;
                    wait_ticks = 0;
                    destination_x = source_x;
                    destination_y = source_y;
                } else
                    determine_cartpusher_destination_food(road_network_id);
            }
            image_offset = 0;
            break;
        case FIGURE_ACTION_26_CARTPUSHER_AT_WORKSHOP:
            wait_ticks++;
            if (wait_ticks > 5) {
                building_workshop_add_raw_material(building_get(destination_building_id));
                action_state = FIGURE_ACTION_27_CARTPUSHER_RETURNING;
                wait_ticks = 0;
                destination_x = source_x;
                destination_y = source_y;
            }
            image_offset = 0;
            break;
        case FIGURE_ACTION_COMMON_RETURN:
        case FIGURE_ACTION_27_CARTPUSHER_RETURNING:
            cart_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER_CART);
            move_ticks(1);
            if (direction == DIR_FIGURE_AT_DESTINATION) {
                action_state = FIGURE_ACTION_20_CARTPUSHER_INITIAL;
                state = FIGURE_STATE_DEAD;
            } else if (direction == DIR_FIGURE_REROUTE)
                route_remove();
            else if (direction == DIR_FIGURE_LOST)
                state = FIGURE_STATE_DEAD;

            break;
    }
    cart_update_image();
}
void figure::warehouseman_action() {
    terrain_usage = TERRAIN_USAGE_ROADS;
    figure_image_increase_offset(12);
    cart_image_id = 0;
    int road_network_id = map_road_network_get(grid_offset);

    switch (action_state) {
        case FIGURE_ACTION_150_ATTACK:
            figure_combat_handle_attack();
            break;
        case FIGURE_ACTION_149_CORPSE:
            figure_combat_handle_corpse();
            break;
        case FIGURE_ACTION_50_WAREHOUSEMAN_CREATED: {
            building *b = building_get(building_id);
            if (b->state != BUILDING_STATE_IN_USE || b->figure_id != id)
                state = FIGURE_STATE_DEAD;
            wait_ticks++;
            if (wait_ticks > 2) {
                if (building_get(building_id)->type == BUILDING_GRANARY)
                    determine_granaryman_destination(road_network_id);
                else
                    determine_warehouseman_destination(road_network_id);
            }
            image_offset = 0;
            break;
        }
        case FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE:
            if (loads_sold_or_carrying == 1) {
                cart_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER_CART_MULTIPLE_FOOD) + 8 * resource_id - 8 + resource_image_offset(resource_id, RESOURCE_IMAGE_FOOD_CART);
            } else
                set_cart_graphic();
            move_ticks(1);
            if (direction == DIR_FIGURE_AT_DESTINATION)
                action_state = FIGURE_ACTION_52_WAREHOUSEMAN_AT_DELIVERY_BUILDING;
            else if (direction == DIR_FIGURE_REROUTE)
                route_remove();
            else if (direction == DIR_FIGURE_LOST)
                state = FIGURE_STATE_DEAD;
            break;
        case FIGURE_ACTION_52_WAREHOUSEMAN_AT_DELIVERY_BUILDING:
            wait_ticks++;
            if (wait_ticks > 4) {
                building *b = building_get(destination_building_id);
                switch (b->type) {
                    case BUILDING_GRANARY:
                        building_granary_add_resource(b, resource_id, 0);
                        break;
                    case BUILDING_BARRACKS:
                        building_barracks_add_weapon(b);
                        break;
                    case BUILDING_WAREHOUSE:
                    case BUILDING_WAREHOUSE_SPACE:
                        building_warehouse_add_resource(b, resource_id);
                        break;
                    default: // workshop
                        building_workshop_add_raw_material(b);
                        break;
                }
                // BUG: what if warehouse/granary is full and returns false?
                action_state = FIGURE_ACTION_53_WAREHOUSEMAN_RETURNING_EMPTY;
                wait_ticks = 0;
                destination_x = source_x;
                destination_y = source_y;
            }
            image_offset = 0;
            break;
        case FIGURE_ACTION_53_WAREHOUSEMAN_RETURNING_EMPTY:
            cart_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER_CART); // empty
            move_ticks(1);
            if (direction == DIR_FIGURE_AT_DESTINATION || direction == DIR_FIGURE_LOST)
                state = FIGURE_STATE_DEAD;
            else if (direction == DIR_FIGURE_REROUTE)
                route_remove();
            break;
        case FIGURE_ACTION_54_WAREHOUSEMAN_GETTING_FOOD:
            if (config_get(CONFIG_GP_CH_GETTING_GRANARIES_GO_OFFROAD))
                terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
            cart_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER_CART); // empty
            move_ticks(1);
            if (direction == DIR_FIGURE_AT_DESTINATION)
                action_state = FIGURE_ACTION_55_WAREHOUSEMAN_AT_GRANARY;
            else if (direction == DIR_FIGURE_REROUTE)
                route_remove();
            else if (direction == DIR_FIGURE_LOST)
                state = FIGURE_STATE_DEAD;
            break;
        case FIGURE_ACTION_55_WAREHOUSEMAN_AT_GRANARY:
            if (config_get(CONFIG_GP_CH_GETTING_GRANARIES_GO_OFFROAD))
                terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
            wait_ticks++;
            if (wait_ticks > 4) {
                int resource;
                loads_sold_or_carrying = building_granary_remove_for_getting_deliveryman(building_get(destination_building_id), building_get(building_id), &resource);
                resource_id = resource;
                action_state = FIGURE_ACTION_56_WAREHOUSEMAN_RETURNING_WITH_FOOD;
                wait_ticks = 0;
                destination_x = source_x;
                destination_y = source_y;
                route_remove();
            }
            image_offset = 0;
            break;
        case FIGURE_ACTION_56_WAREHOUSEMAN_RETURNING_WITH_FOOD:
            // update graphic
            if (config_get(CONFIG_GP_CH_GETTING_GRANARIES_GO_OFFROAD))
                terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
            if (loads_sold_or_carrying <= 0)
                cart_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER_CART); // empty
            else if (loads_sold_or_carrying == 1)
                set_cart_graphic();
            else {
                if (loads_sold_or_carrying >= 8)
                    cart_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER_CART_MULTIPLE_FOOD) + CART_OFFSET_8_LOADS_FOOD[resource_id];
                else
                    cart_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER_CART_MULTIPLE_FOOD) + CART_OFFSET_MULTIPLE_LOADS_FOOD[resource_id];
                cart_image_id += resource_image_offset(resource_id, RESOURCE_IMAGE_FOOD_CART);
            }
            move_ticks(1);
            if (direction == DIR_FIGURE_AT_DESTINATION) {
                for (int i = 0; i < loads_sold_or_carrying; i++)
                    building_granary_add_resource(building_get(building_id), resource_id, 0);
                state = FIGURE_STATE_DEAD;
            } else if (direction == DIR_FIGURE_REROUTE)
                route_remove();
            else if (direction == DIR_FIGURE_LOST)
                state = FIGURE_STATE_DEAD;
            break;
        case FIGURE_ACTION_57_WAREHOUSEMAN_GETTING_RESOURCE:
            terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
            cart_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER_CART); // empty
            move_ticks(1);
            if (direction == DIR_FIGURE_AT_DESTINATION)
                action_state = FIGURE_ACTION_58_WAREHOUSEMAN_AT_WAREHOUSE;
            else if (direction == DIR_FIGURE_REROUTE)
                route_remove();
            else if (direction == DIR_FIGURE_LOST)
                state = FIGURE_STATE_DEAD;
            break;
        case FIGURE_ACTION_58_WAREHOUSEMAN_AT_WAREHOUSE:
            terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
            wait_ticks++;
            if (wait_ticks > 4) {
                loads_sold_or_carrying = 0;
                while (loads_sold_or_carrying < 4 && 0 == building_warehouse_remove_resource(building_get(destination_building_id), collecting_item_id, 1))
                    loads_sold_or_carrying++;
                resource_id = collecting_item_id;
                action_state = FIGURE_ACTION_59_WAREHOUSEMAN_RETURNING_WITH_RESOURCE;
                wait_ticks = 0;
                destination_x = source_x;
                destination_y = source_y;
                route_remove();
            }
            image_offset = 0;
            break;
        case FIGURE_ACTION_59_WAREHOUSEMAN_RETURNING_WITH_RESOURCE:
            terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
            // update graphic
            if (loads_sold_or_carrying <= 0)
                cart_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER_CART); // empty
            else if (loads_sold_or_carrying == 1)
                set_cart_graphic();
            else {
                if (resource_id == RESOURCE_WHEAT || resource_id == RESOURCE_VEGETABLES ||
                    resource_id == RESOURCE_FRUIT || resource_id == RESOURCE_MEAT_C3) {
                    cart_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER_CART_MULTIPLE_FOOD) + CART_OFFSET_MULTIPLE_LOADS_FOOD[resource_id];
                } else
                    cart_image_id = image_id_from_group(GROUP_FIGURE_CARTPUSHER_CART_MULTIPLE_RESOURCE) + CART_OFFSET_MULTIPLE_LOADS_NON_FOOD[resource_id];
                cart_image_id += resource_image_offset(resource_id, RESOURCE_IMAGE_FOOD_CART);
            }
            move_ticks(1);
            if (direction == DIR_FIGURE_AT_DESTINATION) {
                for (int i = 0; i < loads_sold_or_carrying; i++)
                    building_warehouse_add_resource(building_get(building_id), resource_id);
                state = FIGURE_STATE_DEAD;
            } else if (direction == DIR_FIGURE_REROUTE)
                route_remove();
            else if (direction == DIR_FIGURE_LOST)
                state = FIGURE_STATE_DEAD;
            break;
    }
    cart_update_image();
}
