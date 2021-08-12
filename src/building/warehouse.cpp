#include "warehouse.h"

#include "building/barracks.h"
#include "building/count.h"
#include "building/granary.h"
#include "building/model.h"
#include "building/storage.h"
#include "city/buildings.h"
#include "city/finance.h"
#include "city/military.h"
#include "city/resource.h"
#include "core/calc.h"
#include "core/image.h"
#include "empire/trade_prices.h"
#include "game/tutorial.h"
#include "map/image.h"
#include "map/road_access.h"
#include "scenario/property.h"

#include <math.h>
#include <core/config.h>

int building_warehouse_get_space_info(building *warehouse) {
    int total_amounts = 0;
    int empty_spaces = 0;
    building *space = warehouse;
    for (int i = 0; i < 8; i++) {
        space = space->next();
        if (space->id <= 0)
            return 0;
        if (space->subtype.warehouse_resource_id)
            total_amounts += space->stored_full_amount;
        else
            empty_spaces++;
    }
    if (empty_spaces > 0)
        return WAREHOUSE_ROOM;
    else if (total_amounts < 3200)
        return WAREHOUSE_SOME_ROOM;
    else
        return WAREHOUSE_FULL;
}
int building_warehouse_get_amount(building *warehouse, int resource) {
    int total = 0;
    building *space = warehouse;
    for (int i = 0; i < 8; i++) {
        space = space->next();
        if (space->id <= 0)
            return 0;
        if (space->subtype.warehouse_resource_id && space->subtype.warehouse_resource_id == resource)
            total += space->stored_full_amount;
    }
    return total;
}

int building_warehouse_add_resource(building *b, int resource, int amount) {
    if (b->id <= 0)
        return -1;

    building *main = b->main();
    if (building_warehouse_is_not_accepting(resource, main))
        return -1;

    // check the initial provided space itself, first
    bool look_for_space = false;
    if (b->subtype.warehouse_resource_id && b->subtype.warehouse_resource_id != resource)
        look_for_space = true;
    else if (b->stored_full_amount >= 400)
        look_for_space = true;
    else if (b->type == BUILDING_WAREHOUSE)
        look_for_space = true;

    // repeat until no space left... easier than calculating all amounts by hand.
    int amount_left = amount;
    int amount_last_turn = amount;
    while (amount_left > 0) {
        if (look_for_space) {
            bool space_found = false;
            building *space = b->main();
            for (int i = 0; i < 8; i++) {
                space = space->next();
                if (!space->id)
                    return -1;
                if (!space->subtype.warehouse_resource_id || space->subtype.warehouse_resource_id == resource) {
                    if (space->stored_full_amount < 400) {
                        space_found = true;
                        b = space;
                        break;
                    }
                }
            }
            if (!space_found)
                return -1; // no space found at all!
        }
        city_resource_add_to_warehouse(resource, 1);
        b->subtype.warehouse_resource_id = resource;
        int space_on_tile = 400 - b->stored_full_amount;
        int unloading_amount = fmin(space_on_tile, amount_left);
        b->stored_full_amount += unloading_amount;
        space_on_tile -= unloading_amount;
        if (space_on_tile == 0)
            look_for_space = true;
        tutorial_on_add_to_warehouse();
        building_warehouse_space_set_image(b, resource);
        amount_last_turn = amount_left;
        amount_left -= unloading_amount;
        if (amount_left == amount_last_turn)
            return amount_left;
    }
    return amount_left;
}
int building_warehouse_remove_resource(building *warehouse, int resource, int amount) {
    // returns amount still needing removal
    if (warehouse->type != BUILDING_WAREHOUSE)
        return amount;

    building *space = warehouse;
    for (int i = 0; i < 8; i++) {
        if (amount <= 0)
            return 0;

        space = space->next();
        if (space->id <= 0)
            continue;

        if (space->subtype.warehouse_resource_id != resource || space->stored_full_amount <= 0)
            continue;

        if (space->stored_full_amount > amount) {
            city_resource_remove_from_warehouse(resource, amount);
            space->stored_full_amount -= amount;
            amount = 0;
        } else {
            city_resource_remove_from_warehouse(resource, space->stored_full_amount);
            amount -= space->stored_full_amount;
            space->stored_full_amount = 0;
            space->subtype.warehouse_resource_id = RESOURCE_NONE;
        }
        building_warehouse_space_set_image(space, resource);
    }
    return amount;
}
void building_warehouse_remove_resource_curse(building *warehouse, int amount) {
    if (warehouse->type != BUILDING_WAREHOUSE)
        return;
    building *space = warehouse;
    for (int i = 0; i < 8 && amount > 0; i++) {
        space = space->next();
        if (space->id <= 0 || space->stored_full_amount <= 0)
            continue;

        int resource = space->subtype.warehouse_resource_id;
        if (space->stored_full_amount > amount) {
            city_resource_remove_from_warehouse(resource, amount);
            space->stored_full_amount -= amount;
            amount = 0;
        } else {
            city_resource_remove_from_warehouse(resource, space->stored_full_amount);
            amount -= space->stored_full_amount;
            space->stored_full_amount = 0;
            space->subtype.warehouse_resource_id = RESOURCE_NONE;
        }
        building_warehouse_space_set_image(space, resource);
    }
}
void building_warehouse_space_set_image(building *space, int resource) {
    int image_id;
    if (space->stored_full_amount <= 0)
        image_id = image_id_from_group(GROUP_BUILDING_WAREHOUSE_STORAGE_EMPTY);
    else {
        image_id = image_id_from_group(GROUP_BUILDING_WAREHOUSE_STORAGE_FILLED) +
                   4 * (resource - 1) + resource_image_offset(resource, RESOURCE_IMAGE_STORAGE) +
                   ceil((float)space->stored_full_amount / 100.0) - 1;
    }
    map_image_set(space->grid_offset, image_id);
}
void building_warehouse_space_add_import(building *space, int resource) {
    city_resource_add_to_warehouse(resource, 100);
    space->stored_full_amount += 100;
    space->subtype.warehouse_resource_id = resource;

    int price = trade_price_buy(resource);
    city_finance_process_import(price);

    building_warehouse_space_set_image(space, resource);
}
void building_warehouse_space_remove_export(building *space, int resource) {
    city_resource_remove_from_warehouse(resource, 100);
    space->stored_full_amount -= 100;
    if (space->stored_full_amount <= 0)
        space->subtype.warehouse_resource_id = RESOURCE_NONE;


    int price = trade_price_sell(resource);
    city_finance_process_export(price);

    building_warehouse_space_set_image(space, resource);
}
void building_warehouses_add_resource(int resource, int amount) {
    int building_id = city_resource_last_used_warehouse();
    for (int i = 1; i < MAX_BUILDINGS[GAME_ENV] && amount > 0; i++) {
        building_id++;
        if (building_id >= MAX_BUILDINGS[GAME_ENV])
            building_id = 1;

        building *b = building_get(building_id);
        if (b->state == BUILDING_STATE_VALID && b->type == BUILDING_WAREHOUSE) {
            city_resource_set_last_used_warehouse(building_id);
            while (amount && building_warehouse_add_resource(b, resource, 100))
                amount--;
        }
    }
}

int FULL_WAREHOUSE = 3200;
int THREEQ_WAREHOUSE = 2400;
int HALF_WAREHOUSE = 1600;
int QUARTER_WAREHOUSE = 800;

bool building_warehouse_is_accepting(int resource, building *b) {
    const building_storage *s = building_storage_get(b->storage_id);
    int amount = building_warehouse_get_amount(b, resource);
    if ((s->resource_state[resource] == STORAGE_STATE_PHARAOH_ACCEPT && s->resource_max_accept[resource] == FULL_WAREHOUSE) ||
        (s->resource_state[resource] == STORAGE_STATE_PHARAOH_ACCEPT && s->resource_max_accept[resource] >= THREEQ_WAREHOUSE && amount < THREEQ_WAREHOUSE / 100) ||
        (s->resource_state[resource] == STORAGE_STATE_PHARAOH_ACCEPT && s->resource_max_accept[resource] >= HALF_WAREHOUSE && amount < HALF_WAREHOUSE / 100) ||
        (s->resource_state[resource] == STORAGE_STATE_PHARAOH_ACCEPT && s->resource_max_accept[resource] >= QUARTER_WAREHOUSE && amount < QUARTER_WAREHOUSE / 100))
        return true;
    else
        return false;
}
bool building_warehouse_is_getting(int resource, building *b) {
    const building_storage *s = building_storage_get(b->storage_id);
    int amount = building_warehouse_get_amount(b, resource);
    if ((s->resource_state[resource] == STORAGE_STATE_PHARAOH_GET && s->resource_max_get[resource] == FULL_WAREHOUSE) ||
        (s->resource_state[resource] == STORAGE_STATE_PHARAOH_GET && s->resource_max_get[resource] >= THREEQ_WAREHOUSE && amount < THREEQ_WAREHOUSE / 100) ||
        (s->resource_state[resource] == STORAGE_STATE_PHARAOH_GET && s->resource_max_get[resource] >= HALF_WAREHOUSE && amount < HALF_WAREHOUSE / 100) ||
        (s->resource_state[resource] == STORAGE_STATE_PHARAOH_GET && s->resource_max_get[resource] >= QUARTER_WAREHOUSE && amount < QUARTER_WAREHOUSE / 100))
        return true;
    else
        return false;
}
bool building_warehouse_is_emptying(int resource, building *b) {
    const building_storage *s = building_storage_get(b->storage_id);
    if (s->resource_state[resource] == STORAGE_STATE_PHARAOH_EMPTY)
        return true;
    else
        return false;
}
bool building_warehouse_is_gettable(int resource, building *b) {
    const building_storage *s = building_storage_get(b->storage_id);
    if (s->resource_state[resource] == STORAGE_STATE_PHARAOH_GET)
        return true;
    else
        return false;
}
bool building_warehouse_is_not_accepting(int resource, building *b) {
    return !((building_warehouse_is_accepting(resource, b) || building_warehouse_is_getting(resource, b)));
}
int building_warehouse_get_accepting_amount(int resource, building *b) {
    const building_storage *s = building_storage_get(b->main()->storage_id);
    switch (s->resource_state[resource]) {
        case STORAGE_STATE_PHARAOH_ACCEPT:
            return s->resource_max_accept[resource];
            break;
        case STORAGE_STATE_PHARAOH_GET:
            return s->resource_max_get[resource];
            break;
        default:
            return 0;
    }
}

static int warehouse_is_this_space_the_best(building *space, int x, int y, int resource, int distance_from_entry) {
    building *b = space->main();

    // check storage settings first
    if (building_warehouse_is_not_accepting(resource, b))
        return 0;

    // check for spaces that already has some of the resource, first
    building *check = b;
    while (check->next_part_building_id) {
        check = check->next();
        if (check->subtype.warehouse_resource_id == resource && check->stored_full_amount < 400) {
            if (check == space)
                return calc_distance_with_penalty(space->x, space->y, x, y, distance_from_entry, space->distance_from_entry);
            else
                return 0;
        }
    }
    // second pass, return the first
    check = b;
    while (check->next_part_building_id) {
        check = check->next();
        if (check->subtype.warehouse_resource_id == RESOURCE_NONE) {// empty warehouse space
            if (check == space)
                return calc_distance_with_penalty(space->x, space->y, x, y, distance_from_entry, space->distance_from_entry);
            else
                return 0;
        }
    }
    return 0;
}

int building_warehouses_remove_resource(int resource, int amount) {
    int amount_left = amount;
    int building_id = city_resource_last_used_warehouse();
    // first go for non-getting warehouses
    for (int i = 1; i < MAX_BUILDINGS[GAME_ENV] && amount_left > 0; i++) {
        building_id++;
        if (building_id >= MAX_BUILDINGS[GAME_ENV])
            building_id = 1;

        building *b = building_get(building_id);
        if (b->state == BUILDING_STATE_VALID && b->type == BUILDING_WAREHOUSE) {
            if (!building_warehouse_is_getting(resource, b)) {
                city_resource_set_last_used_warehouse(building_id);
                amount_left = building_warehouse_remove_resource(b, resource, amount_left);
            }
        }
    }
    // if that doesn't work, take it anyway
    for (int i = 1; i < MAX_BUILDINGS[GAME_ENV] && amount_left > 0; i++) {
        building_id++;
        if (building_id >= MAX_BUILDINGS[GAME_ENV])
            building_id = 1;

        building *b = building_get(building_id);
        if (b->state == BUILDING_STATE_VALID && b->type == BUILDING_WAREHOUSE) {
            city_resource_set_last_used_warehouse(building_id);
            amount_left = building_warehouse_remove_resource(b, resource, amount_left);
        }
    }
    return amount - amount_left;
}
int building_warehouse_for_storing(building *src, int x, int y, int resource, int distance_from_entry, int road_network_id, int *understaffed, map_point *dst) {
    int min_dist = 10000;
    int min_building_id = 0;
    for (int i = 1; i < MAX_BUILDINGS[GAME_ENV]; i++) {
        building *b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || b->type != BUILDING_WAREHOUSE_SPACE)
            continue;

        if (!b->has_road_access || b->distance_from_entry <= 0 || b->road_network_id != road_network_id)
            continue;

        building *dest = b->main();
//        if (src == dest)
//            continue;

        const building_storage *s = building_storage_get(dest->storage_id);
        if (building_warehouse_is_not_accepting(resource, dest) || s->empty_all)
            continue;

        if (!config_get(CONFIG_GP_CH_UNDERSTAFFED_ACCEPT_GOODS)) {
            int pct_workers = calc_percentage(dest->num_workers, model_get_building(dest->type)->laborers);
            if (pct_workers < 100) {
                if (understaffed)
                    *understaffed += 1;
                continue;
            }
        }
        int dist = warehouse_is_this_space_the_best(b, x, y, resource, distance_from_entry);
        if (dist > 0 && dist < min_dist) {
            min_dist = dist;
            min_building_id = i;
        }
    }

    // abuse null building space
    building *b = building_get(min_building_id)->main();
    if (b->has_road_access == 1)
        map_point_store_result(b->x, b->y, dst);
    else if (!map_has_road_access_rotation(b->subtype.orientation, b->x, b->y, 3, dst))
        return 0;

    return min_building_id;
}
int building_warehouse_for_getting(building *src, int resource, map_point *dst) {
    int min_dist = 10000;
    building *min_building = 0;
    for (int i = 1; i < MAX_BUILDINGS[GAME_ENV]; i++) {
        building *b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || b->type != BUILDING_WAREHOUSE)
            continue;

        if (i == src->id)
            continue;

        int amounts_stored = 0;
        building *space = b;
        const building_storage *s = building_storage_get(b->storage_id);
        for (int t = 0; t < 8; t++) {
            space = space->next();
            if (space->id > 0 && space->stored_full_amount > 0) {
                if (space->subtype.warehouse_resource_id == resource)
                    amounts_stored += space->stored_full_amount;
            }
        }
        if (amounts_stored > 0 && !building_warehouse_is_gettable(resource, b)) {
            int dist = calc_distance_with_penalty(b->x, b->y, src->x, src->y,
                                                  src->distance_from_entry, b->distance_from_entry);
            dist -= 4 * (amounts_stored / 100);
            if (dist < min_dist) {
                min_dist = dist;
                min_building = b;
            }
        }
    }
    if (min_building) {
        if (dst)
            map_point_store_result(min_building->road_access_x, min_building->road_access_y, dst);
        return min_building->id;
    } else
        return 0;
}

static int determine_granary_accept_foods(int resources[8], int road_network) {
    if (scenario_property_rome_supplies_wheat())
        return 0;

    for (int i = 0; i < RESOURCE_MAX_FOOD[GAME_ENV]; i++) {
        resources[i] = 0;
    }
    int can_accept = 0;
    for (int i = 1; i < MAX_BUILDINGS[GAME_ENV]; i++) {
        building *b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || b->type != BUILDING_GRANARY || !b->has_road_access)
            continue;

        if (road_network != b->road_network_id)
            continue;

        int pct_workers = calc_percentage(b->num_workers, model_get_building(b->type)->laborers);
        if (pct_workers >= 100 && b->data.granary.resource_stored[RESOURCE_NONE] >= 1200) {
            const building_storage *s = building_storage_get(b->storage_id);
            if (!s->empty_all) {
                for (int r = 0; r < RESOURCE_MAX_FOOD[GAME_ENV]; r++) {
                    if (!building_granary_is_not_accepting(r, b)) {
                        resources[r]++;
                        can_accept = 1;
                    }
                }
            }
        }
    }
    return can_accept;
}
static int determine_granary_get_foods(int resources[8], int road_network) {
    if (scenario_property_rome_supplies_wheat())
        return 0;

    for (int i = 0; i < RESOURCE_MAX_FOOD[GAME_ENV]; i++) {
        resources[i] = 0;
    }
    int can_get = 0;
    for (int i = 1; i < MAX_BUILDINGS[GAME_ENV]; i++) {
        building *b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || b->type != BUILDING_GRANARY || !b->has_road_access)
            continue;

        if (road_network != b->road_network_id)
            continue;

        int pct_workers = calc_percentage(b->num_workers, model_get_building(b->type)->laborers);
        if (pct_workers >= 100 && b->data.granary.resource_stored[RESOURCE_NONE] > 100) {
            const building_storage *s = building_storage_get(b->storage_id);
            if (!s->empty_all) {
                for (int r = 0; r < RESOURCE_MAX_FOOD[GAME_ENV]; r++) {
                    if (building_granary_is_getting(r, b)) {
                        resources[r]++;
                        can_get = 1;
                    }
                }
            }
        }
    }
    return can_get;
}
static int contains_non_stockpiled_food(building *space, const int *resources) {
    if (space->id <= 0)
        return 0;
    if (space->stored_full_amount <= 0)
        return 0;
    int resource = space->subtype.warehouse_resource_id;
    if (city_resource_is_stockpiled(resource))
        return 0;
    if (resource == RESOURCE_WHEAT || resource == RESOURCE_VEGETABLES ||
        resource == RESOURCE_FRUIT || resource == RESOURCE_MEAT_C3) {
        if (resources[resource] > 0)
            return 1;
    }
    return 0;
}
int building_warehouse_determine_worker_task(building *warehouse, int *resource, int *amount) {
    // check workers - if less than enough, no task will be done today.
    int pct_workers = calc_percentage(warehouse->num_workers, model_get_building(warehouse->type)->laborers);
    if (pct_workers < 50)
        return WAREHOUSE_TASK_NONE;
    const building_storage *s = building_storage_get(warehouse->storage_id);
    building *space;

    // get resources
    for (int r = RESOURCE_MIN; r < RESOURCE_MAX[GAME_ENV]; r++) {
        if (!building_warehouse_is_getting(r, warehouse) || city_resource_is_stockpiled(r))
            continue;
        int total_stored = 0; // total amounts of resource in warehouse!
        int room = 0; // total potential room for resource!
        space = warehouse;
        for (int i = 0; i < 8; i++) {
            space = space->next();
            if (space->id > 0) {
                if (space->stored_full_amount <= 0) // this space (tile) is empty! FREE REAL ESTATE
                    room += 4;
                if (space->subtype.warehouse_resource_id == r) { // found a space (tile) with resource on it!
                    total_stored += space->stored_full_amount; // add loads to total, if any!
                    room += 400 - space->stored_full_amount; // add room to total, if any!
                }
            }
        }

        int requesting = building_warehouse_get_accepting_amount(r, warehouse);
        int lacking = requesting - total_stored;

        // determine if there's enough room for more to accept, depending on "get up to..." settings!
        if (room >= 0 && lacking > 0 && city_resource_count(r) - total_stored > 0) {
            if (!building_warehouse_for_getting(warehouse, r, 0)) // any other place contain this resource..?
                continue;
            *resource = r;
            *amount = lacking;

            // bug in original Pharaoh: warehouses send out two cartpushers even if there is no room!
            if (lacking > requesting / 2)
                return WAREHOUSE_TASK_GETTING_MOAR;
            else
                return WAREHOUSE_TASK_GETTING;
        }
    }
    // deliver weapons to barracks
    if (building_count_active(BUILDING_BARRACKS) > 0 && city_military_has_legionary_legions() &&
        !city_resource_is_stockpiled(RESOURCE_WEAPONS_C3)) {
        building *barracks = building_get(building_get_barracks_for_weapon(warehouse->x, warehouse->y, RESOURCE_WEAPONS_C3,
                                                 warehouse->road_network_id, warehouse->distance_from_entry, 0));
        int barracks_want = (100 * MAX_WEAPONS_BARRACKS) - barracks->stored_full_amount;
        if (barracks_want > 0 && warehouse->road_network_id == barracks->road_network_id) {
            int available = 0;
            space = warehouse;
            for (int i = 0; i < 8; i++) {
                space = space->next();
                if (space->id > 0 && space->stored_full_amount > 0 && space->subtype.warehouse_resource_id == RESOURCE_WEAPONS_C3) {
                    available += space->stored_full_amount;
                }
            }
            if (available > 0) {
                *resource = RESOURCE_WEAPONS_C3;
                *amount = fmin(available, barracks_want);
                return WAREHOUSE_TASK_DELIVERING;
            }
        }
    }
    // deliver raw materials to workshops
    space = warehouse;
    for (int i = 0; i < 8; i++) {
        space = space->next();
        if (space->id > 0 && space->stored_full_amount > 0) {
            if (!city_resource_is_stockpiled(space->subtype.warehouse_resource_id)) {
                int workshop_type = resource_to_workshop_type(space->subtype.warehouse_resource_id);
                if (workshop_type != WORKSHOP_NONE && city_resource_has_workshop_with_room(workshop_type)) {
                    *resource = space->subtype.warehouse_resource_id;
                    *amount = 100; // always one load only for industry!!
                    return WAREHOUSE_TASK_DELIVERING;
                }
            }
        }
    }
    // deliver food to getting granary
    int granary_resources[RESOURCE_MAX_FOOD[GAME_ENV]];
    if (determine_granary_get_foods(granary_resources, warehouse->road_network_id)) {
        space = warehouse;
        for (int i = 0; i < 8; i++) {
            space = space->next();
            if (contains_non_stockpiled_food(space, granary_resources)) {
                *resource = space->subtype.warehouse_resource_id;
                *amount = 100; // always one load only for granaries?
                return WAREHOUSE_TASK_DELIVERING;
            }
        }
    }
    // deliver food to accepting granary
    if (determine_granary_accept_foods(granary_resources, warehouse->road_network_id) &&
        !scenario_property_rome_supplies_wheat()) {
        space = warehouse;
        for (int i = 0; i < 8; i++) {
            space = space->next();
            if (contains_non_stockpiled_food(space, granary_resources)) {
                *resource = space->subtype.warehouse_resource_id;
                *amount = 100; // always one load only for granaries?
                return WAREHOUSE_TASK_DELIVERING;
            }
        }
    }
    // emptying resource
    for (int r = RESOURCE_MIN; r < RESOURCE_MAX[GAME_ENV]; r++) {
        if (!building_warehouse_is_emptying(r, warehouse))
            continue;

        int in_storage = building_warehouse_get_amount(warehouse, r);
        if (in_storage > 0) {
            *resource = r;
            *amount = building_warehouse_get_amount(warehouse, r);
            return WAREHOUSE_TASK_EMPTYING;
        }
    }
    // move goods to other warehouses
    if (s->empty_all) {
        space = warehouse;
        for (int i = 0; i < 8; i++) {
            space = space->next();
            if (space->id > 0 && space->stored_full_amount > 0) {
                *resource = space->subtype.warehouse_resource_id;
                *amount = space->stored_full_amount;
                return WAREHOUSE_TASK_DELIVERING;
            }
        }
    }
    return WAREHOUSE_TASK_NONE;
}
