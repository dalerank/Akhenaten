#include "storage_yard.h"

#include "building/barracks.h"
#include "building/count.h"
#include "building/building_granary.h"
#include "building/industry.h"
#include "building/rotation.h"
#include "building/model.h"
#include "building/figure.h"
#include "building/monuments.h"
#include "building/storage.h"
#include "window/building/distribution.h"
#include "city/buildings.h"
#include "city/finance.h"
#include "city/military.h"
#include "city/resource.h"
#include "core/calc.h"
#include "core/vec2i.h"
#include "empire/trade_prices.h"
#include "game/tutorial.h"
#include "game/game.h"
#include "graphics/image.h"
#include "graphics/text.h"
#include "graphics/image_groups.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/button.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/lang_text.h"
#include "grid/image.h"
#include "figure/figure.h"
#include "grid/road_access.h"
#include "scenario/property.h"
#include "config/config.h"

#include <cmath>

int building_storageyard_get_space_info(building* storageyard) {
    int total_amounts = 0;
    int empty_spaces = 0;
    building* space = storageyard;
    for (int i = 0; i < 8; i++) {
        space = space->next();
        if (space->id <= 0) {
            return 0;
        }

        if (space->subtype.warehouse_resource_id) {
            total_amounts += space->stored_full_amount;
        } else {
            empty_spaces++;
        }
    }

    if (empty_spaces > 0)
        return STORAGEYARD_ROOM;
    else if (total_amounts < 3200)
        return STORAGEYARD_SOME_ROOM;
    else
        return STORAGEYARD_FULL;
}

int building_storageyard_get_amount(const building *storageyard, e_resource resource) {
    int total = 0;
    const building* space = storageyard;
    for (int i = 0; i < 8; i++) {
        space = (const building*)space->next();
        if (space->id <= 0)
            return 0;

        if (space->subtype.warehouse_resource_id && space->subtype.warehouse_resource_id == resource) {
            total += space->stored_full_amount;
        }
    }
    return total;
}

int building_storageyard_get_freespace(building* storageyard, e_resource resource) {
    int freespace = 0;
    building* space = storageyard;
    for (int i = 0; i < 8; i++) {
        space = space->next();
        if (space->id <= 0)
            return 0;

        if (!space->subtype.warehouse_resource_id) {
            freespace += 400;
        } else if(space->subtype.warehouse_resource_id == resource) {
            freespace += (400 - space->stored_full_amount);
        }
    }
    return freespace;
}

int building_storageyard_add_resource(building* b, e_resource resource, int amount) {
    if (b->id <= 0)
        return -1;

    building* main = b->main();
    if (building_storageyard_is_not_accepting(resource, main)) {
        return -1;
    }

    // check the initial provided space itself, first
    bool look_for_space = false;
    if (b->subtype.warehouse_resource_id && b->subtype.warehouse_resource_id != resource)
        look_for_space = true;
    else if (b->stored_full_amount >= 400)
        look_for_space = true;
    else if (b->type == BUILDING_STORAGE_YARD)
        look_for_space = true;

    // repeat until no space left... easier than calculating all amounts by hand.
    int amount_left = amount;
    int amount_last_turn = amount;
    while (amount_left > 0) {
        if (look_for_space) {
            bool space_found = false;
            building* space = b->main();
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
        city_resource_add_to_storageyard(resource, 1);
        b->subtype.warehouse_resource_id = resource;
        int space_on_tile = 400 - b->stored_full_amount;
        int unloading_amount = std::min<int>(space_on_tile, amount_left);
        b->stored_full_amount += unloading_amount;
        space_on_tile -= unloading_amount;
        if (space_on_tile == 0) {
            look_for_space = true;
        }
        
        building_storageyard_space_set_image(b, resource);
        amount_last_turn = amount_left;
        amount_left -= unloading_amount;
        if (amount_left == amount_last_turn)
            return amount_left;
    }
    return amount_left;
}

int building_storageyard_remove_resource(building* storageyard, e_resource resource, int amount) {
    // returns amount still needing removal
    if (storageyard->type != BUILDING_STORAGE_YARD)
        return amount;

    building* space = storageyard;
    for (int i = 0; i < 8; i++) {
        if (amount <= 0)
            return 0;

        space = space->next();
        if (space->id <= 0)
            continue;

        if (space->subtype.warehouse_resource_id != resource || space->stored_full_amount <= 0)
            continue;

        if (space->stored_full_amount > amount) {
            city_resource_remove_from_storageyard(resource, amount);
            space->stored_full_amount -= amount;
            amount = 0;

        } else {
            city_resource_remove_from_storageyard(resource, space->stored_full_amount);
            amount -= space->stored_full_amount;
            space->stored_full_amount = 0;
            space->subtype.warehouse_resource_id = RESOURCE_NONE;
        }
        building_storageyard_space_set_image(space, resource);
    }
    return amount;
}
void building_storageyard_remove_resource_curse(building* storageyard, int amount) {
    if (storageyard->type != BUILDING_STORAGE_YARD)
        return;
    building* space = storageyard;
    for (int i = 0; i < 8 && amount > 0; i++) {
        space = space->next();
        if (space->id <= 0 || space->stored_full_amount <= 0) {
            continue;
        }

        e_resource resource = space->subtype.warehouse_resource_id;
        if (space->stored_full_amount > amount) {
            city_resource_remove_from_storageyard(resource, amount);
            space->stored_full_amount -= amount;
            amount = 0;
        } else {
            city_resource_remove_from_storageyard(resource, space->stored_full_amount);
            amount -= space->stored_full_amount;
            space->stored_full_amount = 0;
            space->subtype.warehouse_resource_id = RESOURCE_NONE;
        }
        building_storageyard_space_set_image(space, resource);
    }
}

void building_storageyard_space_set_image(building* space, e_resource resource) {
    int image_id;
    if (space->stored_full_amount <= 0)
        image_id = image_id_from_group(GROUP_BUILDING_STORAGE_YARD_SPACE_EMPTY);
    else {
        image_id = image_id_from_group(GROUP_BUILDING_STORAGE_YARD_SPACE_FILLED) + 4 * (resource - 1)
                   + resource_image_offset(resource, RESOURCE_IMAGE_STORAGE)
                   + (int)ceil((float)space->stored_full_amount / 100.0f) - 1;
    }
    map_image_set(space->tile.grid_offset(), image_id);
}

void building_storageyard_space_add_import(building* space, e_resource resource) {
    city_resource_add_to_storageyard(resource, 100);
    space->stored_full_amount += 100;
    space->subtype.warehouse_resource_id = resource;

    int price = trade_price_buy(resource);
    city_finance_process_import(price);

    building_storageyard_space_set_image(space, resource);
}

void building_storageyard_space_remove_export(building* space, e_resource resource) {
    city_resource_remove_from_storageyard(resource, 100);
    space->stored_full_amount -= 100;
    if (space->stored_full_amount <= 0) {
        space->subtype.warehouse_resource_id = RESOURCE_NONE;
    }

    int price = trade_price_sell(resource);
    city_finance_process_export(price);

    building_storageyard_space_set_image(space, resource);
}

void building_storageyards_add_resource(e_resource resource, int amount) {
    int building_id = city_resource_last_used_storageyard();
    for (int i = 1; i < MAX_BUILDINGS && amount > 0; i++) {
        building_id++;
        if (building_id >= MAX_BUILDINGS)
            building_id = 1;

        building* b = building_get(building_id);
        if (b->state == BUILDING_STATE_VALID && b->type == BUILDING_STORAGE_YARD) {
            city_resource_set_last_used_storageyard(building_id);
            while (amount && building_storageyard_add_resource(b, resource, 100))
                amount--;
        }
    }
}

constexpr int FULL_WAREHOUSE = 3200;
constexpr int THREEQ_WAREHOUSE = 2400;
constexpr int HALF_WAREHOUSE = 1600;
constexpr int QUARTER_WAREHOUSE = 800;

bool building_storageyard_is_accepting(e_resource resource, building* b) {
    const building_storage* s = building_storage_get(b->storage_id);
    int amount = building_storageyard_get_amount(b, resource);
    bool accepting = (s->resource_state[resource] == STORAGE_STATE_PHARAOH_ACCEPT);
    bool fool_storage = (s->resource_max_accept[resource] == FULL_WAREHOUSE);
    bool threeq_storage = (s->resource_max_accept[resource] >= THREEQ_WAREHOUSE && amount < THREEQ_WAREHOUSE);
    bool half_storage = (s->resource_max_accept[resource] >= HALF_WAREHOUSE && amount < HALF_WAREHOUSE);
    bool quart_storage = (s->resource_max_accept[resource] >= QUARTER_WAREHOUSE && amount < QUARTER_WAREHOUSE);

    return (accepting && (fool_storage || threeq_storage || half_storage || quart_storage));
}

bool building_storageyard_is_getting(e_resource resource, building* b) {
    const building_storage* s = building_storage_get(b->storage_id);
    int amount = building_storageyard_get_amount(b, resource);
    if ((s->resource_state[resource] == STORAGE_STATE_PHARAOH_GET && s->resource_max_get[resource] == FULL_WAREHOUSE) 
        || (s->resource_state[resource] == STORAGE_STATE_PHARAOH_GET && s->resource_max_get[resource] >= THREEQ_WAREHOUSE && amount < THREEQ_WAREHOUSE / 100)
        || (s->resource_state[resource] == STORAGE_STATE_PHARAOH_GET && s->resource_max_get[resource] >= HALF_WAREHOUSE && amount < HALF_WAREHOUSE / 100)
        || (s->resource_state[resource] == STORAGE_STATE_PHARAOH_GET && s->resource_max_get[resource] >= QUARTER_WAREHOUSE && amount < QUARTER_WAREHOUSE / 100)) {
        return true;
    } else {
        return false;
    }
}

bool building_storageyard_is_emptying(e_resource resource, building* b) {
    const building_storage* s = building_storage_get(b->storage_id);
    return (s->resource_state[resource] == STORAGE_STATE_PHARAOH_EMPTY);
}

bool building_storageyard_is_gettable(e_resource resource, building* b) {
    const building_storage* s = building_storage_get(b->storage_id);
    return (s->resource_state[resource] == STORAGE_STATE_PHARAOH_GET);
}

bool building_storageyard_is_not_accepting(e_resource resource, building* b) {
    return !((building_storageyard_is_accepting(resource, b) || building_storageyard_is_getting(resource, b)));
}

int building_storageyard_get_accepting_amount(e_resource resource, building* b) {
    const building_storage* s = building_storage_get(b->main()->storage_id);
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

static int storageyard_is_this_space_the_best(building* space, tile2i tile, e_resource resource, int distance_from_entry) {
    building* b = space->main();

    // check storage settings first
    if (building_storageyard_is_not_accepting(resource, b))
        return 0;

    // check for spaces that already has some of the resource, first
    building* check = b;
    while (check->next_part_building_id) {
        check = check->next();
        if (check->subtype.warehouse_resource_id == resource && check->stored_full_amount < 400) {
            if (check == space)
                return calc_distance_with_penalty(space->tile, tile, distance_from_entry, space->distance_from_entry);
            else
                return 0;
        }
    }
    // second pass, return the first
    check = b;
    while (check->next_part_building_id) {
        check = check->next();
        if (check->subtype.warehouse_resource_id == RESOURCE_NONE) { // empty warehouse space
            if (check == space)
                return calc_distance_with_penalty(space->tile, tile, distance_from_entry, space->distance_from_entry);
            else
                return 0;
        }
    }
    return 0;
}

int building_storageyard_remove_resource(e_resource resource, int amount) {
    int amount_left = amount;
    int building_id = city_resource_last_used_storageyard();
    // first go for non-getting warehouses
    for (int i = 1; i < MAX_BUILDINGS && amount_left > 0; i++) {
        building_id++;
        if (building_id >= MAX_BUILDINGS) {
            building_id = 1;
        }

        building* b = building_get(building_id);
        if (b->state == BUILDING_STATE_VALID && b->type == BUILDING_STORAGE_YARD) {
            if (!building_storageyard_is_getting(resource, b)) {
                city_resource_set_last_used_storageyard(building_id);
                amount_left = building_storageyard_remove_resource(b, resource, amount_left);
            }
        }
    }
    // if that doesn't work, take it anyway
    for (int i = 1; i < MAX_BUILDINGS && amount_left > 0; i++) {
        building_id++;
        if (building_id >= MAX_BUILDINGS) {
            building_id = 1;
        }

        building* b = building_get(building_id);
        if (b->state == BUILDING_STATE_VALID && b->type == BUILDING_STORAGE_YARD) {
            city_resource_set_last_used_storageyard(building_id);
            amount_left = building_storageyard_remove_resource(b, resource, amount_left);
        }
    }
    return amount - amount_left;
}

int building_storageyard_for_storing(building* src, map_point tile, e_resource resource, int distance_from_entry, int road_network_id, int* understaffed, map_point* dst) {
    int min_dist = 10000;
    int min_building_id = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || b->type != BUILDING_STORAGE_YARD_SPACE)
            continue;

        if (!b->has_road_access || b->distance_from_entry <= 0 || b->road_network_id != road_network_id)
            continue;

        building* dest = b->main();
        //        if (src == dest)
        //            continue;

        const building_storage* s = building_storage_get(dest->storage_id);
        if (building_storageyard_is_not_accepting(resource, dest) || s->empty_all) {
            continue;
        }

        if (!config_get(CONFIG_GP_CH_UNDERSTAFFED_ACCEPT_GOODS)) {
            int pct_workers = calc_percentage<int>(dest->num_workers, model_get_building(dest->type)->laborers);
            if (pct_workers < 100) {
                if (understaffed)
                    *understaffed += 1;
                continue;
            }
        }
        int dist = storageyard_is_this_space_the_best(b, tile, resource, distance_from_entry);
        if (dist > 0 && dist < min_dist) {
            min_dist = dist;
            min_building_id = i;
        }
    }

    // abuse null building space
    building* b = building_get(min_building_id)->main();
    if (b->has_road_access == 1) {
        map_point_store_result(b->tile, *dst);
    } else if (!map_has_road_access_rotation(b->subtype.orientation, b->tile, 3, dst)) {
        return 0;
    }

    return min_building_id;
}
int building_storageyard_for_getting(building* src, e_resource resource, tile2i* dst) {
    int min_dist = 10000;
    building* min_building = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || b->type != BUILDING_STORAGE_YARD)
            continue;

        if (i == src->id)
            continue;

        int amounts_stored = 0;
        building* space = b;
        const building_storage* s = building_storage_get(b->storage_id);
        for (int t = 0; t < 8; t++) {
            space = space->next();
            if (space->id > 0 && space->stored_full_amount > 0) {
                if (space->subtype.warehouse_resource_id == resource)
                    amounts_stored += space->stored_full_amount;
            }
        }
        if (amounts_stored > 0 && !building_storageyard_is_gettable(resource, b)) {
            int dist = calc_distance_with_penalty(b->tile, src->tile, src->distance_from_entry, b->distance_from_entry);
            dist -= 4 * (amounts_stored / 100);
            if (dist < min_dist) {
                min_dist = dist;
                min_building = b;
            }
        }
    }
    if (min_building) {
        if (dst) {
            map_point_store_result(min_building->road_access, *dst);
        }
        return min_building->id;
    } else
        return 0;
}

static int determine_granary_accept_foods(int resources[8], int road_network) {
    if (scenario_property_kingdom_supplies_grain())
        return 0;

    for (e_resource i = RESOURCE_NONE; i < RESOURCES_FOODS_MAX; ++i) {
        resources[i] = 0;
    }
    int can_accept = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || b->type != BUILDING_GRANARY || !b->has_road_access)
            continue;

        if (road_network != b->road_network_id)
            continue;

        int pct_workers = calc_percentage<int>(b->num_workers, model_get_building(b->type)->laborers);
        if (pct_workers >= 100 && b->data.granary.resource_stored[RESOURCE_NONE] >= 1200) {
            const building_storage* s = building_storage_get(b->storage_id);
            if (!s->empty_all) {
                for (e_resource r = RESOURCE_MIN; r < RESOURCES_FOODS_MAX; ++r) {
                    if (!building_granary_is_not_accepting(r, b)) {
                        ++resources[r];
                        can_accept = 1;
                    }
                }
            }
        }
    }
    return can_accept;
}

static int determine_granary_get_foods(int resources[8], int road_network) {
    if (scenario_property_kingdom_supplies_grain()) {
        return 0;
    }

    for (e_resource i = RESOURCE_NONE; i < RESOURCES_FOODS_MAX; ++i) {
        resources[i] = 0;
    }

    int can_get = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || b->type != BUILDING_GRANARY || !b->has_road_access)
            continue;

        if (road_network != b->road_network_id)
            continue;

        int pct_workers = calc_percentage<int>(b->num_workers, model_get_building(b->type)->laborers);
        if (pct_workers >= 100 && b->data.granary.resource_stored[RESOURCE_NONE] > 100) {
            const building_storage* s = building_storage_get(b->storage_id);
            if (!s->empty_all) {
                for (e_resource r = RESOURCE_MIN; r < RESOURCES_FOODS_MAX; ++r) {
                    if (building_granary_is_getting(r, b)) {
                        ++resources[r];
                        can_get = 1;
                    }
                }
            }
        }
    }
    return can_get;
}

static int contains_non_stockpiled_food(building* space, const int* resources) {
    if (space->id <= 0)
        return 0;
    if (space->stored_full_amount <= 0)
        return 0;
    e_resource resource = space->subtype.warehouse_resource_id;
    if (city_resource_is_stockpiled(resource)) {
        return 0;
    }

    if (resource == RESOURCE_GRAIN || resource == RESOURCE_MEAT || resource == RESOURCE_LETTUCE
        || resource == RESOURCE_FIGS) {
        if (resources[resource] > 0)
            return 1;
    }
    return 0;
}

storage_worker_task building_storageyard_determine_getting_up_resources(building* warehouse) {
    building* space = nullptr;
    for (e_resource check_resource = RESOURCE_MIN; check_resource < RESOURCES_MAX; ++check_resource) {
        if (!building_storageyard_is_getting(check_resource, warehouse) || city_resource_is_stockpiled(check_resource)) {
            continue;
        }

        int total_stored = 0; // total amounts of resource in warehouse!
        int room = 0;         // total potential room for resource!
        space = warehouse;
        for (int i = 0; i < 8; i++) {
            space = space->next();
            if (space->id > 0) {
                if (space->stored_full_amount <= 0) { // this space (tile) is empty! FREE REAL ESTATE
                    room += 4;
                }

                if (space->subtype.warehouse_resource_id == check_resource) { // found a space (tile) with resource on it!
                    total_stored += space->stored_full_amount;   // add loads to total, if any!
                    room += 400 - space->stored_full_amount;     // add room to total, if any!
                }
            }
        }

        int requesting = building_storageyard_get_accepting_amount(check_resource, warehouse);
        int lacking = requesting - total_stored;

        // determine if there's enough room for more to accept, depending on "get up to..." settings!
        if (room >= 0 && lacking > 0 && city_resource_count(check_resource) - total_stored > 0) {
            if (!building_storageyard_for_getting(warehouse, check_resource, 0)) { // any other place contain this resource..?
                continue;
            }

            // bug in original Pharaoh: warehouses send out two cartpushers even if there is no room!
            e_storageyard_task status = lacking > requesting / 2
                                            ? STORAGEYARD_TASK_GETTING_MOAR
                                            : STORAGEYARD_TASK_GETTING;
            return {status, space, lacking, check_resource};
        }
    }

    return {STORAGEYARD_TASK_NONE};
}

storage_worker_task building_storageyard_deliver_weapons(building *warehouse) {
    building *space = warehouse;

    if (building_count_active(BUILDING_RECRUITER) > 0 
        && (city_military_has_legionary_legions() || config_get(CONFIG_GP_CH_RECRUITER_NOT_NEED_FORTS))
        && !city_resource_is_stockpiled(RESOURCE_WEAPONS)) {
        auto result = building_get_asker_for_resource(warehouse->tile, BUILDING_RECRUITER, RESOURCE_WEAPONS, warehouse->road_network_id, warehouse->distance_from_entry);
        building* barracks = building_get(result.building_id);
        int barracks_want = barracks->need_resource_amount(RESOURCE_WEAPONS);

        if (barracks_want > 0 && warehouse->road_network_id == barracks->road_network_id) {
            int available = 0;
            space = warehouse;
            for (int i = 0; i < 8; i++) {
                space = space->next();
                if (space->id > 0 && space->stored_full_amount > 0
                    && space->subtype.warehouse_resource_id == RESOURCE_WEAPONS) {
                    available += space->stored_full_amount;
                }
            }

            if (available > 0) {
                int amount = std::min(available, barracks_want);
                return {STORAGEYARD_TASK_DELIVERING, space, amount, RESOURCE_WEAPONS};
            }
        }
    }

    return {STORAGEYARD_TASK_NONE};
}

storage_worker_task building_storageyard_deliver_papyrus_to_scribal_school(building *warehouse) {
    building *space = warehouse;

    if (building_count_active(BUILDING_SCRIBAL_SCHOOL) > 0 
        //&& (config_get(CONFIG_GP_CH_SCRIBAL_SCHOOL_NEED_PAPYRUS))
        && !city_resource_is_stockpiled(RESOURCE_PAPYRUS)) {
        auto result = building_get_asker_for_resource(warehouse->tile, BUILDING_SCRIBAL_SCHOOL, RESOURCE_PAPYRUS, warehouse->road_network_id, warehouse->distance_from_entry);
        building* scribal_school = building_get(result.building_id);
        int school_want = scribal_school->need_resource_amount(RESOURCE_PAPYRUS);

        if (school_want > 0 && warehouse->road_network_id == scribal_school->road_network_id) {
            int available = 0;
            space = warehouse;
            for (int i = 0; i < 8; i++) {
                space = space->next();
                if (space->id > 0 && space->stored_full_amount > 0
                    && space->subtype.warehouse_resource_id == RESOURCE_PAPYRUS) {
                    available += space->stored_full_amount;
                }
            }

            if (available > 0) {
                int amount = std::min(available, school_want);
                return {STORAGEYARD_TASK_DELIVERING, space, amount, RESOURCE_PAPYRUS};
            }
        }
    }

    return {STORAGEYARD_TASK_NONE};
}

storage_worker_task building_storageyard_deliver_resource_to_workshop(building *warehouse) {
    building *space = warehouse;

    for (int i = 0; i < 8; i++) {
        space = space->next();
        if (space->id > 0 && space->stored_full_amount > 0) {
            e_resource check_resource = space->subtype.warehouse_resource_id;
            if (!city_resource_is_stockpiled(check_resource)) {
                storage_worker_task task = {STORAGEYARD_TASK_NONE};
                buildings_workshop_do([&] (building &b) {
                    if (!resource_required_by_workshop(&b, space->subtype.warehouse_resource_id) || b.need_resource_amount(check_resource) < 100) {
                        return;
                    }
                    task = {STORAGEYARD_TASK_DELIVERING, space, 100, space->subtype.warehouse_resource_id};
                });

                if (task.result == STORAGEYARD_TASK_DELIVERING) {
                    return task;
                }
            }
        }
    }

    return {STORAGEYARD_TASK_NONE};
}

storage_worker_task building_storageyard_deliver_food_to_gettingup_granary(building *warehouse) {
    building *space = warehouse;

    int granary_resources[RESOURCES_FOODS_MAX] = {RESOURCE_NONE};
    if (determine_granary_get_foods(granary_resources, warehouse->road_network_id)) {
        space = warehouse;
        for (int i = 0; i < 8; i++) {
            space = space->next();
            if (contains_non_stockpiled_food(space, granary_resources)) {
                // always one load only for granaries?
                return {STORAGEYARD_TASK_DELIVERING, space, 100, space->subtype.warehouse_resource_id};
            }
        }
    }

    return {STORAGEYARD_TASK_NONE};
}

storage_worker_task building_storageyard_deliver_food_to_accepting_granary(building *warehouse) {
    building *space = warehouse;

    int granary_resources[RESOURCES_FOODS_MAX] = {RESOURCE_NONE};
    if (determine_granary_accept_foods(granary_resources, warehouse->road_network_id)
        && !scenario_property_kingdom_supplies_grain()) {
        space = warehouse;
        for (int i = 0; i < 8; i++) {
            space = space->next();
            if (contains_non_stockpiled_food(space, granary_resources)) {
                // always one load only for granaries?
                return {STORAGEYARD_TASK_DELIVERING, space, 100, space->subtype.warehouse_resource_id};
            }
        }
    }

    return {STORAGEYARD_TASK_NONE};
}

storage_worker_task building_storageyard_deliver_to_monuments(building *warehouse) {
    building *space = warehouse;

    svector<building *, 10> monuments;
    buildings_valid_do([&] (building &b) { 
        if (!monuments.full() && building_is_monument(b.type) && b.data.monuments.phase != MONUMENT_FINISHED) {
            monuments.push_back(&b);
        }
    });

    if (monuments.empty()) {
        return {STORAGEYARD_TASK_NONE};
    }

    for (int i = 0; i < 8; i++) {
        space = space->next();
        int available = space->stored_full_amount;
        if (space->id <= 0 || !space->subtype.warehouse_resource_id || available <= 0) {
            continue;
        }

        e_resource resource = space->subtype.warehouse_resource_id;
        if (city_resource_is_stockpiled(resource)) {
            continue;
        }

        for (auto monument : monuments) {
            int monuments_want = building_monument_needs_resource(monument, resource);
            if (monuments_want > 0) {
                int amount = std::min(available, monuments_want);
                return {STORAGEYARD_TASK_MONUMENT, space, amount, resource, monument};
            }
        }
    }

    return {STORAGEYARD_TASK_NONE};
}

storage_worker_task building_storageyard_deliver_emptying_resources(building *warehouse) {
    building *space = warehouse;

    for (e_resource r = RESOURCE_MIN; r < RESOURCES_MAX; r = (e_resource)(r + 1)) {
        if (!building_storageyard_is_emptying(r, warehouse)) {
            continue;
        }

        int in_storage = building_storageyard_get_amount(warehouse, r);
        if (in_storage > 0) {
            int amount = building_storageyard_get_amount(warehouse, r);
            return {STORAGEYARD_TASK_EMPTYING, nullptr, amount, r};
        }
    }

    return {STORAGEYARD_TASK_NONE};
}

storage_worker_task building_storageyard_determine_worker_task(building* warehouse) {
    // check workers - if less than enough, no task will be done today.
    int pct_workers = calc_percentage<int>(warehouse->num_workers, model_get_building(warehouse->type)->laborers);
    if (pct_workers < 50) {
        return {STORAGEYARD_TASK_NONE};
    }

    using action_type = decltype(building_storageyard_deliver_weapons);
    action_type *actions[] = {
        &building_storageyard_determine_getting_up_resources,       // getting up resources
        &building_storageyard_deliver_weapons,                      // deliver weapons to barracks
        &building_storageyard_deliver_resource_to_workshop,         // deliver raw materials to workshops
        &building_storageyard_deliver_papyrus_to_scribal_school,    // deliver raw materials to workshops
        &building_storageyard_deliver_food_to_gettingup_granary,    // deliver food to getting granary
        &building_storageyard_deliver_food_to_accepting_granary,    // deliver food to accepting granary
        &building_storageyard_deliver_emptying_resources,           // emptying resource
        &building_storageyard_deliver_to_monuments,                 // monuments resource
    };

    for (const auto &action : actions) {
        storage_worker_task task = (*action)(warehouse);
        if (task.result != STORAGEYARD_TASK_NONE) {
            return task;
        }
    }
    
    // move goods to other warehouses
    const building_storage* s = building_storage_get(warehouse->storage_id);
    if (s->empty_all) {
        building *space = warehouse;
        for (int i = 0; i < 8; i++) {
            space = space->next();
            if (space->id > 0 && space->stored_full_amount > 0) {
                return {STORAGEYARD_TASK_DELIVERING, space, space->stored_full_amount, space->subtype.warehouse_resource_id};
            }
        }
    }

    return {STORAGEYARD_TASK_NONE};
}

void building_storage_yard::on_create() {
    base.subtype.orientation = building_rotation_global_rotation();
}

void building_storage_yard::spawn_figure() {
    base.check_labor_problem();
    if (!base.has_road_access) {
        return;
    }

    building *space = &base;
    for (int i = 0; i < 8; i++) {
        space = space->next();
        if (space->id) {
            space->show_on_problem_overlay = base.show_on_problem_overlay;
        }
    }

    base.common_spawn_labor_seeker(100);
    auto task = building_storageyard_determine_worker_task(&base);
    if (task.result == STORAGEYARD_TASK_NONE || task.amount <= 0) {
        return;
    }

    if (!base.has_figure(BUILDING_SLOT_SERVICE) && task.result == STORAGEYARD_TASK_MONUMENT) {
        figure *leader = base.create_figure_with_destination(FIGURE_SLED_PULLER, task.dest, FIGURE_ACTION_50_SLED_PULLER_CREATED);
        leader->set_direction_to(task.dest);
        for (int i = 0; i < 5; ++i) {
            figure *follower = base.create_figure_with_destination(FIGURE_SLED_PULLER, task.dest, FIGURE_ACTION_50_SLED_PULLER_CREATED);
            follower->set_direction_to(task.dest);
            follower->wait_ticks = i * 4;
        }
        figure *sled = figure_create(FIGURE_SLED, base.tile, 0);
        sled->set_destination(task.dest);
        sled->set_direction_to(task.dest);
        sled->load_resource(task.resource, task.amount);
        sled->leading_figure_id = leader->id;
        building_storageyard_remove_resource(&base, task.resource, task.amount);

    } else if (!base.has_figure(BUILDING_SLOT_SERVICE)) {
        figure* f = figure_create(FIGURE_STORAGE_YARD_DELIVERCART, base.road_access, DIR_4_BOTTOM_LEFT);
        f->action_state = FIGURE_ACTION_50_WAREHOUSEMAN_CREATED;

        switch (task.result) {
        case STORAGEYARD_TASK_GETTING:
        case STORAGEYARD_TASK_GETTING_MOAR:
            f->load_resource(RESOURCE_NONE, 0);
            f->collecting_item_id = task.resource;
            break;
        case STORAGEYARD_TASK_DELIVERING:
        case STORAGEYARD_TASK_EMPTYING:
            task.amount = std::min<int>(task.amount, 400);
            f->load_resource(task.resource, task.amount);
            building_storageyard_remove_resource(&base, task.resource, task.amount);
            break;
        }
        base.set_figure(0, f->id);
        f->set_home(base.id);

    } else if (task.result == STORAGEYARD_TASK_GETTING_MOAR && !base.has_figure_of_type(1, FIGURE_STORAGE_YARD_DELIVERCART)) {
        figure* f = figure_create(FIGURE_STORAGE_YARD_DELIVERCART, base.road_access, DIR_4_BOTTOM_LEFT);
        f->action_state = FIGURE_ACTION_50_WAREHOUSEMAN_CREATED;

        f->load_resource(RESOURCE_NONE, 0);
        f->collecting_item_id = task.resource;

        base.set_figure(1, f->id);
        f->set_home(base.id);
    }
}

void building_storage_yard::draw_warehouse_orders(object_info* c) {
    int y_offset = window_building_get_vertical_offset(c, 28 + 5);
    c->help_id = 4;
    outer_panel_draw(vec2i{c->offset.x, y_offset}, 29, 28 + 5);
    lang_text_draw_centered(99, 3, c->offset.x, y_offset + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    inner_panel_draw(c->offset.x + 16, y_offset + 42, c->width_blocks - 2, 21 + 5);
}

void building_storage_yard::draw_warehouse(object_info* c) {
    auto &data = g_window_building_distribution;
    c->help_id = 4;
    window_building_play_sound(c, "wavs/warehouse.wav");
    outer_panel_draw(c->offset, c->width_blocks, c->height_blocks);
    lang_text_draw_centered(99, 0, c->offset.x, c->offset.y + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    building* b = building_get(c->building_id);
    painter ctx = game.painter();
    data.building_id = c->building_id;
    if (!c->has_road_access) {
        window_building_draw_description(c, 69, 25);
    }
    //if (GAME_ENV == ENGINE_ENV_C3) {
    //    const resources_list* list = city_resource_get_available();
    //    for (int i = 0; i < list->size; i++) {
    //        e_resource resource = list->items[i];
    //        int x, y;
    //        if (i < 5) { // column 1
    //            x = c->offset.x + 20;
    //            y = c->offset.y + 24 * i + 36;
    //        } else if (i < 10) { // column 2
    //            x = c->offset.x + 170;
    //            y = c->offset.y + 24 * (i - 5) + 36;
    //        } else { // column 3
    //            x = c->offset.x + 320;
    //            y = c->offset.y + 24 * (i - 10) + 36;
    //        }
    //        int amount = building_storageyard_get_amount(b, resource);
    //        int image_id = image_id_from_group(GROUP_RESOURCE_ICONS) + resource + resource_image_offset(resource, RESOURCE_IMAGE_ICON);
    //        ImageDraw::img_generic(image_id, x, y);
    //        int width = text_draw_number(amount, '@', " ", x + 24, y + 7, FONT_SMALL_PLAIN);
    //        lang_text_draw(23, resource, x + 24 + width, y + 7, FONT_SMALL_PLAIN);
    //    }
    //} else if (GAME_ENV == ENGINE_ENV_PHARAOH) 
    {
        int x = c->offset.x + 20;
        int y = c->offset.y + 45;
        int lines = 0;

        const resources_list* list = city_resource_get_available();
        painter ctx = game.painter();
        for (int i = 0; i < list->size; i++) {
            e_resource resource = list->items[i];
            int loads = building_storageyard_get_amount(b, resource);
            if (loads) {
                int amount = stack_proper_quantity(loads, resource);
                int image_id = image_id_resource_icon(resource) + resource_image_offset(resource, RESOURCE_IMAGE_ICON);
                ImageDraw::img_generic(ctx, image_id, x, y);
                int width = text_draw_number(amount, '@', " ", x + 24, y + 7, FONT_NORMAL_BLACK_ON_LIGHT);
                lang_text_draw(23, resource, x + 24 + width, y + 7, FONT_NORMAL_BLACK_ON_LIGHT);
                y += 24;
                lines++;
                if (lines >= 4) {
                    lines = 0;
                    y = c->offset.y + 45;
                    x += 205;
                }
            }
        }
    }
    inner_panel_draw(c->offset.x + 16, c->offset.y + 168, c->width_blocks - 2, 5);
    window_building_draw_employment(c, 173);
    // cartpusher state
    figure* cartpusher = b->get_figure(0);
    if (cartpusher->state == FIGURE_STATE_ALIVE) {
        int resource = cartpusher->get_resource();
        ImageDraw::img_generic(ctx, image_id_resource_icon(resource) + resource_image_offset(resource, RESOURCE_IMAGE_ICON), c->offset.x + 32, c->offset.y + 220);
        lang_text_draw_multiline(99, 17, c->offset + vec2i{64, 223}, 16 * (c->width_blocks - 6), FONT_NORMAL_BLACK_ON_DARK);
    } else if (b->num_workers) {
        // cartpusher is waiting for orders
        lang_text_draw_multiline(99, 15, c->offset + vec2i{32, 223}, 16 * (c->width_blocks - 4), FONT_NORMAL_BLACK_ON_DARK);
    }

    // if (c->warehouse_space_text == 1) { // full
    //     lang_text_draw_multiline(99, 13, c->offset.x + 32, c->offset.y + 16 * c->height_blocks - 93,
    //         16 * (c->width_blocks - 4), FONT_NORMAL_BLACK);
    // }  else if (c->warehouse_space_text == 2) {
    //     lang_text_draw_multiline(99, 14, c->offset.x + 32, c->offset.y + 16 * c->height_blocks - 93,
    //         16 * (c->width_blocks - 4), FONT_NORMAL_BLACK);
    // }

    //    imagedrawnamespace::image_draw_namespace::image_draw(image_id_from_group(GROUP_FIGURE_MARKET_LADY) + 4,
    //    c->offset.x + 32,
    //               c->offset.y + 16 * c->height_blocks - 93);
    //    imagedrawnamespace::image_draw_namespace::image_draw(image_id_from_group(GROUP_FIGURE_TRADE_CARAVAN) + 4,
    //    c->offset.x + 128,
    //               c->offset.y + 16 * c->height_blocks - 93);
    //    imagedrawnamespace::image_draw_namespace::image_draw(image_id_from_group(GROUP_FIGURE_SHIP) + 4, c->offset.x +
    //    216,
    //               c->offset.y + 16 * c->height_blocks - 110);
}

void building_storage_yard::draw_warehouse_orders_foreground(object_info* c) {
    auto &data = g_window_building_distribution;
    draw_warehouse_orders(c);
    int y_offset = window_building_get_vertical_offset(c, 28 + 5);
    int line_x = c->offset.x + 215;

    int storage_id = building_get(c->building_id)->storage_id;
    backup_storage_settings(storage_id);
    const building_storage* storage = building_storage_get(storage_id);
    const resources_list* list = city_resource_get_available();
    painter ctx = game.painter();
    for (int i = 0; i < list->size; i++) {
        int line_y = 20 * i;

        int resource = list->items[i];
        int image_id = image_id_resource_icon(resource) + resource_image_offset(resource, RESOURCE_IMAGE_ICON);
        ImageDraw::img_generic(ctx, image_id, c->offset.x + 25, y_offset + 48 + line_y);
        lang_text_draw(23, resource, c->offset.x + 52, y_offset + 50 + line_y, FONT_NORMAL_WHITE_ON_DARK);
        if (data.resource_focus_button_id - 1 == i) {
            button_border_draw(line_x - 10, y_offset + 46 + line_y, data.orders_resource_buttons[i].width, data.orders_resource_buttons[i].height, true);
        }

        // order status
        window_building_draw_order_instruction(INSTR_STORAGE_YARD, storage, resource, line_x, y_offset + 51 + line_y);

        // arrows
        int state = storage->resource_state[resource];
        if (state == STORAGE_STATE_PHARAOH_ACCEPT || state == STORAGE_STATE_PHARAOH_GET) {
            image_buttons_draw(c->offset.x + 165, y_offset + 49, data.orders_decrease_arrows.data(), 1, i);
            image_buttons_draw(c->offset.x + 165 + 18, y_offset + 49, data.orders_increase_arrows.data(), 1, i);
        }
    }

    // emptying button
    button_border_draw(c->offset.x + 80, y_offset + 404 + 5 * 16, 16 * (c->width_blocks - 10), 20, data.orders_focus_button_id == 1 ? 1 : 0);
    if (storage->empty_all) {
        lang_text_draw_centered(99, 5, c->offset.x + 80, y_offset + 408 + 5 * 16, 16 * (c->width_blocks - 10), FONT_NORMAL_BLACK_ON_LIGHT);
    } else {
        lang_text_draw_centered(99, 4, c->offset.x + 80, y_offset + 408 + 5 * 16, 16 * (c->width_blocks - 10), FONT_NORMAL_BLACK_ON_LIGHT);
    }

    // trade center
    //if (GAME_ENV == ENGINE_ENV_C3) {
    //    button_border_draw(c->offset.x + 80, y_offset + 382 + 5 * 16, 16 * (c->width_blocks - 10), 20, data.orders_focus_button_id == 2 ? 1 : 0);
    //    int is_trade_center = c->building_id == city_buildings_get_trade_center();
    //    lang_text_draw_centered(99, is_trade_center ? 11 : 12, c->offset.x + 80, y_offset + 386 + 5 * 16, 16 * (c->width_blocks - 10), FONT_NORMAL_BLACK_ON_LIGHT);
    //    // accept none button
    //    draw_accept_none_button(c->offset.x + 394, y_offset + 404, data.orders_focus_button_id == 3);
    //} else if (GAME_ENV == ENGINE_ENV_PHARAOH) 
    {
        // accept none button
        button_border_draw(c->offset.x + 80, y_offset + 382 + 5 * 16, 16 * (c->width_blocks - 10), 20, data.orders_focus_button_id == 2 ? 1 : 0);
        lang_text_draw_centered(99, 7, c->offset.x + 80, y_offset + 386 + 5 * 16, 16 * (c->width_blocks - 10), FONT_NORMAL_BLACK_ON_LIGHT);
    }
}

void building_storage_yard::draw_warehouse_foreground(object_info* c) {
    auto &data = g_window_building_distribution;
    button_border_draw(c->offset.x + 80, c->offset.y + 16 * c->height_blocks - 34, 16 * (c->width_blocks - 10), 20, data.focus_button_id == 1 ? 1 : 0);
    lang_text_draw_centered(99, 2, c->offset.x + 80, c->offset.y + 16 * c->height_blocks - 30, 16 * (c->width_blocks - 10),FONT_NORMAL_BLACK_ON_LIGHT);

    // temp - todo: fix buttons
    //    draw_permissions_buttons(c->offset.x + 64, c->offset.y + 16 * c->height_blocks - 75, 3);
}

void building_storage_yard::window_info_background(object_info &ctx) {
    if (ctx.storage_show_special_orders)
        draw_warehouse_orders(&ctx);
    else
        draw_warehouse(&ctx);
}

void building_storage_yard::window_info_foreground(object_info &ctx) {
    if (ctx.storage_show_special_orders)
        draw_warehouse_orders_foreground(&ctx);
    else
        draw_warehouse_foreground(&ctx);
}