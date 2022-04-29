#include <cmath>
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
#include "map/routing/routing_terrain.h"

static const int CART_OFFSET_MULTIPLE_LOADS_FOOD[] = {0, 0, 8, 16, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static const int CART_OFFSET_MULTIPLE_LOADS_NON_FOOD[] = {0, 0, 0, 0, 0, 8, 0, 16, 24, 32, 40, 48, 56, 64, 72, 80};
static const int CART_OFFSET_8_LOADS_FOOD[] = {0, 40, 48, 56, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0};

#include "city/buildings.h"

void figure::set_resource(int resource) {
    resource_id = resource;
}
int figure::get_resource() const {
    return resource_id;
}
void figure::load_resource(int amount, int resource) {
    resource_id = resource;
    resource_amount_full = amount;
//    resource_amount_loads = amount / 100;
}
int figure::dump_resource(int amount) {
    amount = fmin(amount, resource_amount_full);
    resource_amount_full -= amount;
//    resource_amount_loads -= amount / 100;

    // automatically clear field if carrying nothing
    if (resource_amount_full == 0)
        resource_id = RESOURCE_NONE;
    return resource_amount_full;
}
int figure::get_carrying_amount() {
    return resource_amount_full;
}

#include "city/finance.h"

// cartpushers abstract generic actions
void figure::cartpusher_calculate_destination(bool warehouseman) {
    set_destination(0);
    anim_frame = 0;
    wait_ticks++;

    if (!warehouseman) {
        if (wait_ticks > 30) {
            wait_ticks = 0;
            determine_deliveryman_destination();
        }
    } else {
        building *b = home();
        if (wait_ticks > 2) {
            wait_ticks = 0;
            if (home()->type == BUILDING_GRANARY)
                determine_granaryman_destination();
            else
                determine_warehouseman_destination();
        }
    }
}
void figure::cartpusher_do_deliver(bool warehouseman, int ACTION_DONE) {
    anim_frame = 0;
    wait_ticks++;

    if ((!warehouseman && wait_ticks >= 10) || (warehouseman && wait_ticks >= 4)) {
        wait_ticks = 0;

        int carrying = get_carrying_amount();
        int resource = get_resource();

        // carrying nothing? done!
        if (resource == RESOURCE_NONE || carrying <= 0)
            return advance_action(ACTION_DONE);
        else {
            building *dest = destination();

            int accepting = 0;
            switch (dest->type) {
                case BUILDING_WAREHOUSE:
                case BUILDING_WAREHOUSE_SPACE:
                    accepting = building_warehouse_get_accepting_amount(resource_id, dest);
                    break;
                default:
                    accepting = 200 - dest->stored_full_amount;
//                    accepting = stack_proper_quantity(2 - dest->loads_stored, resource);
                    break;
            }

            int total_depositable = fmin(carrying, accepting);
            if (total_depositable <= 0)
                return advance_action(ACTION_8_RECALCULATE);

            int max_single_turn = 100;
            if (true) // TODO: more than 100 at once?????
                max_single_turn = total_depositable;

            int amount_single_turn = fmin(total_depositable, max_single_turn);
            int times = total_depositable / amount_single_turn;

            switch (dest->type) {
                case BUILDING_GRANARY:
                    if (building_granary_add_resource(dest, resource_id, 0, amount_single_turn) != -1)
                        dump_resource(amount_single_turn);
                    else
                        return advance_action(ACTION_8_RECALCULATE);
                    break;
                case BUILDING_RECRUITER:
                    for (int i = 0; i < times; i++) { // do one by one...
                        dest->barracks_add_weapon();
                        dump_resource(amount_single_turn); // assume barracks will ALWAYS accept a weapon
                    }
                case BUILDING_WAREHOUSE:
                case BUILDING_WAREHOUSE_SPACE:
                    for (int i = 0; i < times; i++) { // do one by one...
                        int amount_refused = building_warehouse_add_resource(dest, resource_id, amount_single_turn);
                        if (amount_refused != -1)
                            dump_resource(amount_single_turn - amount_refused);
                        else
                            return advance_action(ACTION_8_RECALCULATE);
                    }
                    break;
                case BUILDING_VILLAGE_PALACE:
                case BUILDING_TOWN_PALACE:
                case BUILDING_CITY_PALACE:
                    city_finance_process_gold_extraction(amount_single_turn);
                    break;
                default: // workshop
                    for (int i = 0; i < times; i++) { // do one by one...
                        if (dest->stored_full_amount < 200) {
                            building_workshop_add_raw_material(dest, 100);
                            dump_resource(100);
                            if (i + 1 == times)
                                advance_action(ACTION_DONE);
                        } else
                            return advance_action(ACTION_8_RECALCULATE);
                    }
                    advance_action(ACTION_8_RECALCULATE);
                    break;
            }
        }
        // am I done?
        if (resource == RESOURCE_NONE || carrying <= 0)
            return advance_action(ACTION_DONE);
    }
}
void figure::cartpusher_do_retrieve(int ACTION_DONE) {
    wait_ticks++;
    anim_frame = 0;
    if (wait_ticks > 4) {
        building *dest = destination();
        switch (dest->type) {
            case BUILDING_WAREHOUSE:
            case BUILDING_WAREHOUSE_SPACE: {
                int home_accepting_quantity = building_warehouse_get_accepting_amount(collecting_item_id, home());
                int carry_amount_goal_max = fmin(100, home_accepting_quantity);
                int load_single_turn = 1;

                if (true) // TODO: multiple loads setting?????
                    carry_amount_goal_max = fmin(400, home_accepting_quantity);

                if (true) // TODO: more than 100 at once?????
                    load_single_turn = 4;

                // grab goods, quantity & max load changed by above settings;
                // if load is finished, go back home - otherwise, recalculate
                if (get_carrying_amount() < carry_amount_goal_max) {
                    if (building_warehouse_remove_resource(destination(), collecting_item_id, load_single_turn) == 0) {
                        load_resource(load_single_turn * 100, collecting_item_id);
                        if (get_carrying_amount() >= carry_amount_goal_max)
                            advance_action(ACTION_DONE);
                    } else
                        advance_action(ACTION_8_RECALCULATE);
                }
                break;
            }
            case BUILDING_GRANARY: {
                int resource;
                int loads = building_granary_remove_for_getting_deliveryman(destination(), home(), &resource);
                load_resource(loads * 100, resource);
                advance_action(FIGURE_ACTION_56_WAREHOUSEMAN_RETURNING_WITH_FOOD);
                break;
            }
        }
    }
}

void figure::determine_deliveryman_destination() {
    map_point dst;
    int road_network_id = map_road_network_get(tile.grid_offset());
    building *warehouse = home();
    int understaffed_storages = 0;

    destination_tile.set(0, 0);
//    destination_tile.x() = 0;
//    destination_tile.y() = 0;

    // before we start... check that resource is not empty.
    if (resource_id == RESOURCE_NONE || get_carrying_amount() == 0)
        return advance_action(ACTION_15_RETURNING2);

    // first: gold deliverers
    if (resource_id == RESOURCE_GOLD) {
        int senate_id = city_buildings_get_palace_id();
        building *b = building_get(senate_id);
        if (senate_id && b->state == BUILDING_STATE_VALID && b->num_workers >= 5) {
            set_destination(senate_id);
            return advance_action(11);
        }
    }

    // priority 1: warehouse if resource is on stockpile
    set_destination(building_warehouse_for_storing(0, tile.x(), tile.y(), resource_id, warehouse->distance_from_entry, road_network_id, &understaffed_storages, &dst));
    if (!city_resource_is_stockpiled(resource_id))
        set_destination(0);
    if (has_destination())
        return advance_action(FIGURE_ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE);

    // priority 2: accepting granary for food
    set_destination(building_granary_for_storing(tile.x(), tile.y(), resource_id, warehouse->distance_from_entry, road_network_id, 0, &understaffed_storages, &dst));
    if (config_get(CONFIG_GP_CH_FARMS_DELIVER_CLOSE)) {
        int dist = 0;
        building *src_building = home();
        building *dst_building = destination();
        int src_int = src_building->type;
        if ((src_int >= BUILDING_BARLEY_FARM && src_int <= BUILDING_CHICKPEAS_FARM) || src_int == BUILDING_FISHING_WHARF)
            dist = calc_distance_with_penalty(src_building->x, src_building->y, dst_building->x, dst_building->y, src_building->distance_from_entry, dst_building->distance_from_entry);
        if (dist >= 64)
            set_destination(0);
    }
    if (has_destination())
        return advance_action(FIGURE_ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY);

    // priority 3: workshop for raw material
    set_destination(building_get_workshop_for_raw_material_with_room(tile.x(), tile.y(), resource_id, warehouse->distance_from_entry, road_network_id, &dst));
    if (has_destination())
        return advance_action(FIGURE_ACTION_23_CARTPUSHER_DELIVERING_TO_WORKSHOP);

    // priority 4: warehouse
    set_destination(building_warehouse_for_storing(0, tile.x(), tile.y(), resource_id, warehouse->distance_from_entry, road_network_id, &understaffed_storages, &dst));
    if (has_destination())
        return advance_action(FIGURE_ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE);

    // priority 5: granary forced when on stockpile
    set_destination(building_granary_for_storing(tile.x(), tile.y(), resource_id, warehouse->distance_from_entry, road_network_id, 1, &understaffed_storages, &dst));
    if (config_get(CONFIG_GP_CH_FARMS_DELIVER_CLOSE)) {
        int dist = 0;
        building *src_building = home();
        building *dst_building = destination();
        int src_int = src_building->type;
        if ((src_int >= BUILDING_BARLEY_FARM && src_int <= BUILDING_CHICKPEAS_FARM) || src_int == BUILDING_FISHING_WHARF)
            dist = calc_distance_with_penalty(src_building->x, src_building->y, dst_building->x, dst_building->y, src_building->distance_from_entry, dst_building->distance_from_entry);
        if (dist >= 64)
            set_destination(0);
    }
    if (has_destination())
        return advance_action(FIGURE_ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY);

    // no one will accept
    min_max_seen = understaffed_storages ? 2 : 1;
    advance_action(ACTION_8_RECALCULATE);
}
void figure::determine_deliveryman_destination_food() {
    building *b = home();
    int road_network_id = map_road_network_get(tile.grid_offset());
    map_point dst;
    // priority 1: accepting granary for food
    int dst_building_id = building_granary_for_storing(tile.x(), tile.y(), resource_id, b->distance_from_entry, road_network_id, 0, 0, &dst);
    if (dst_building_id && config_get(CONFIG_GP_CH_FARMS_DELIVER_CLOSE)) {
        int dist = 0;
        building *dst_building = building_get(dst_building_id);
        if ((b->type >= BUILDING_BARLEY_FARM && b->type <= BUILDING_CHICKPEAS_FARM) || b->type == BUILDING_FISHING_WHARF)
            dist = calc_distance_with_penalty(b->x, b->y, dst_building->x, dst_building->y, b->distance_from_entry, dst_building->distance_from_entry);
        if (dist >= 64)
            dst_building_id = 0;
    }
    if (dst_building_id) {
        set_destination(dst_building_id);
        return advance_action(FIGURE_ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY);
    }
    // priority 2: warehouse
    dst_building_id = building_warehouse_for_storing(0, tile.x(), tile.y(), resource_id, b->distance_from_entry, road_network_id, 0, &dst);
    if (dst_building_id) {
        set_destination(dst_building_id);
        return advance_action(FIGURE_ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE);
    }
    // priority 3: granary
    dst_building_id = building_granary_for_storing(tile.x(), tile.y(), resource_id, b->distance_from_entry, road_network_id, 1, 0, &dst);
    if (dst_building_id) {
        set_destination(dst_building_id);
        return advance_action(FIGURE_ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY);
    }
    // no one will accept, stand idle
    advance_action(ACTION_8_RECALCULATE);
}
void figure::determine_granaryman_destination() {
    map_point dst;
    int road_network_id = map_road_network_get(tile.grid_offset());
    building *granary = home();
    if (!resource_id) {
        // getting granaryman
        set_destination(building_granary_for_getting(granary, &dst));
        if (has_destination()) {
            advance_action(FIGURE_ACTION_54_WAREHOUSEMAN_GETTING_FOOD);
//            set_destination(FIGURE_ACTION_54_WAREHOUSEMAN_GETTING_FOOD, dst_building_id, dst.x, dst.y);
            if (config_get(CONFIG_GP_CH_GETTING_GRANARIES_GO_OFFROAD))
                terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
        } else
            poof();
        return;
    }
    // delivering resource
    // priority 1: another granary
    set_destination(building_granary_for_storing(tile.x(), tile.y(), resource_id, granary->distance_from_entry, road_network_id, 0, 0, &dst));
    if (has_destination()) {
        building_granary_remove_resource(granary, resource_id, 100);
        return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
    }
    // priority 2: warehouse
    set_destination(building_warehouse_for_storing(0, tile.x(), tile.y(), resource_id, granary->distance_from_entry, road_network_id, 0, &dst));
    if (has_destination()) {
        building_granary_remove_resource(granary, resource_id, 100);
        return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
    }
    // priority 3: granary even though resource is on stockpile
    set_destination(building_granary_for_storing(tile.x(), tile.y(), resource_id, granary->distance_from_entry, road_network_id, 1, 0, &dst));
    if (has_destination()) {
        building_granary_remove_resource(granary, resource_id, 100);
        return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
    }
    // nowhere to go to: recalculate
    advance_action(FIGURE_ACTION_56_WAREHOUSEMAN_RETURNING_WITH_FOOD);
}
void figure::determine_warehouseman_destination() {
    map_point dst;
    int road_network_id = map_road_network_get(tile.grid_offset());

    ////// getting resources!
    if (!resource_id) {
        set_destination(building_warehouse_for_getting(home(), collecting_item_id, &dst));
        if (has_destination()) {
            advance_action(FIGURE_ACTION_57_WAREHOUSEMAN_GETTING_RESOURCE);
            terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
        } else
            advance_action(FIGURE_ACTION_53_WAREHOUSEMAN_RETURNING_EMPTY);
        return;
    }
    building *warehouse = home();

    ////// delivering resource!
    // priority 1: weapons to barracks
    set_destination(building_get_barracks_for_weapon(tile.x(), tile.y(), resource_id, road_network_id, warehouse->distance_from_entry, &dst));
    if (has_destination())
        return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);

    // priority 2: raw materials to workshop
    set_destination(building_get_workshop_for_raw_material_with_room(tile.x(), tile.y(), resource_id, warehouse->distance_from_entry, road_network_id, &dst));
    if (has_destination())
        return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);

    // priority 3: food to granary
    set_destination(building_granary_for_storing(tile.x(), tile.y(), resource_id, warehouse->distance_from_entry, road_network_id, 0, 0, &dst));
    if (has_destination())
        return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);

    // priority 4: food to getting granary
    set_destination(building_getting_granary_for_storing(tile.x(), tile.y(), resource_id, warehouse->distance_from_entry, road_network_id, &dst));
    if (has_destination())
        return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);

    // priority 5: resource to other warehouse
    set_destination(building_warehouse_for_storing(home(), tile.x(), tile.y(), resource_id, warehouse->distance_from_entry, road_network_id, 0, &dst));
    if (has_destination())
        return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
//    int empty_warehouse = building_storage_get(home()->storage_id)->empty_all; // deliver to another warehouse because this one is being emptied
//    if (has_destination() && empty_warehouse) {
//        if (homeID() == destinationID())
//            poof();
//        else
//            advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
//        return;
//    }

//    // priority 6: raw material to well-stocked workshop
//    set_destination(building_get_workshop_for_raw_material(tile_x, tile_y, resource_id, warehouse->distance_from_entry, road_network_id, &dst);
//    if (destination_building_id) {
//        remove_resource_from_warehouse();
//        return advance_action(FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE);
//    }

    // no destination: recalculate
//    advance_action(FIGURE_ACTION_59_WAREHOUSEMAN_RETURNING_WITH_RESOURCE);
}

void figure::cartpusher_action() {
    building *b = home();
    int road_network_id = map_road_network_get(tile.grid_offset());
    switch (action_state) {
        case ACTION_8_RECALCULATE:
        case FIGURE_ACTION_20_CARTPUSHER_INITIAL:
            cartpusher_calculate_destination(false);
            break;
        case ACTION_9_DELIVERING_GOODS:
            do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, ACTION_12_UNLOADING1, ACTION_8_RECALCULATE);
            break;
        case ACTION_10_DELIVERING_FOOD:
            do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, ACTION_13_UNLOADING2, ACTION_8_RECALCULATE);
            break;
        case 11: // delivering gold
            do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, 14, ACTION_8_RECALCULATE);
            break;
        case FIGURE_ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE:
            do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, FIGURE_ACTION_24_CARTPUSHER_AT_WAREHOUSE, ACTION_8_RECALCULATE);
            break;
        case FIGURE_ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY:
            do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, FIGURE_ACTION_25_CARTPUSHER_AT_GRANARY, ACTION_8_RECALCULATE);
            break;
        case FIGURE_ACTION_23_CARTPUSHER_DELIVERING_TO_WORKSHOP:
            do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, FIGURE_ACTION_26_CARTPUSHER_AT_WORKSHOP, ACTION_8_RECALCULATE);
            break;
        case 12: // storage yard
        case 13: // granary
        case 14: // palace
        case FIGURE_ACTION_24_CARTPUSHER_AT_WAREHOUSE:
        case FIGURE_ACTION_25_CARTPUSHER_AT_GRANARY:
        case FIGURE_ACTION_26_CARTPUSHER_AT_WORKSHOP:
            cartpusher_do_deliver(false, ACTION_15_RETURNING2);
            break;
//        case ACTION_11_RETURNING_EMPTY:
        case ACTION_15_RETURNING2:
        case FIGURE_ACTION_27_CARTPUSHER_RETURNING:
            // the CARTPUSHER figure will never be retrieving goods to carry back.
            // that's job for the WAREHOUSEMAN figure!
            // so there is no need for `cartpusher_do_deliver` action.
            if (building_is_floodplain_farm(b)) // do not return to floodplain farms
                poof();
            else
                do_returnhome();
            break;
    }
    cart_update_image();
}
void figure::warehouseman_action() {
    int road_network_id = map_road_network_get(tile.grid_offset());
    switch (action_state) {
        case ACTION_8_RECALCULATE:
        case FIGURE_ACTION_50_WAREHOUSEMAN_CREATED:
            cartpusher_calculate_destination(true);
            break;
        case ACTION_9_DELIVERING_GOODS:
        case FIGURE_ACTION_51_WAREHOUSEMAN_DELIVERING_RESOURCE:
            do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, FIGURE_ACTION_52_WAREHOUSEMAN_AT_DELIVERY_BUILDING, ACTION_8_RECALCULATE);
            break;
        case ACTION_12_UNLOADING1:
        case FIGURE_ACTION_52_WAREHOUSEMAN_AT_DELIVERY_BUILDING:
            cartpusher_do_deliver(true, ACTION_11_RETURNING_EMPTY);
            break;
        case ACTION_11_RETURNING_EMPTY:
        case FIGURE_ACTION_53_WAREHOUSEMAN_RETURNING_EMPTY:
            do_returnhome();
            break;
        case FIGURE_ACTION_54_WAREHOUSEMAN_GETTING_FOOD:
            do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, FIGURE_ACTION_55_WAREHOUSEMAN_AT_GRANARY_GETTING, ACTION_8_RECALCULATE);
            break;
        case FIGURE_ACTION_55_WAREHOUSEMAN_AT_GRANARY_GETTING:
            cartpusher_do_retrieve(FIGURE_ACTION_56_WAREHOUSEMAN_RETURNING_WITH_FOOD);
            break;
        case ACTION_14_RETURNING_WITH_FOOD:
        case FIGURE_ACTION_56_WAREHOUSEMAN_RETURNING_WITH_FOOD:
        case FIGURE_ACTION_59_WAREHOUSEMAN_RETURNING_WITH_RESOURCE:
            if (do_returnhome()) {
                set_destination(home());
                cartpusher_do_deliver(true, 0);
            }
            break;
        case ACTION_15_GETTING_GOODS:
        case FIGURE_ACTION_57_WAREHOUSEMAN_GETTING_RESOURCE:
            do_gotobuilding(destination(), true, TERRAIN_USAGE_ROADS, FIGURE_ACTION_58_WAREHOUSEMAN_AT_WAREHOUSE_GETTING_GOODS, ACTION_8_RECALCULATE);
            break;
        case FIGURE_ACTION_58_WAREHOUSEMAN_AT_WAREHOUSE_GETTING_GOODS: // used exclusively for getting resources
            cartpusher_do_retrieve(FIGURE_ACTION_59_WAREHOUSEMAN_RETURNING_WITH_RESOURCE);
            break;
    }
    cart_update_image();
}
