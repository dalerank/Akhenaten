#include "cartpusher.h"

#include "building/granary.h"
#include "building/industry.h"
#include "building/storage_yard.h"
#include "city/buildings.h"
#include "city/resource.h"
#include "core/calc.h"
#include "figure/figure.h"
#include "figure/movement.h"
#include "game/resource.h"
#include "grid/point.h"
#include "grid/road_network.h"
#include "io/config/config.h"

void figure::determine_deliveryman_destination() {
    map_point dst;
    int road_network_id = map_road_network_get(tile.grid_offset());
    building* warehouse = home();
    int understaffed_storages = 0;

    destination_tile.set(0, 0);
    //    destination_tile.x() = 0;
    //    destination_tile.y() = 0;

    // before we start... check that resource is not empty.
    if (resource_id == RESOURCE_NONE || get_carrying_amount() == 0) {
        return advance_action(ACTION_15_RETURNING2);
    }

    // first: gold deliverers
    if (resource_id == RESOURCE_GOLD) {
        int senate_id = city_buildings_get_palace_id();
        building* b = building_get(senate_id);
        if (senate_id && b->state == BUILDING_STATE_VALID && b->num_workers >= 5) {
            set_destination(senate_id);
            return advance_action(ACTION_11_DELIVERING_GOLD);
        }
    }

    // priority 1: warehouse if resource is on stockpile
    int warehouse_id = building_storageyard_for_storing(0, tile, resource_id, warehouse->distance_from_entry, road_network_id, &understaffed_storages, &dst);
    set_destination(warehouse_id);
    if (!city_resource_is_stockpiled(resource_id)) {
        set_destination(0);
    }

    if (has_destination()) {
        return advance_action(FIGURE_ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE);
    }

    // priority 2: accepting granary for food
    set_destination(building_granary_for_storing(tile,
                                                 resource_id, warehouse->distance_from_entry,
                                                 road_network_id, 0,
                                                 &understaffed_storages, &dst));
    if (config_get(CONFIG_GP_CH_FARMS_DELIVER_CLOSE)) {
        int dist = 0;
        building* src_building = home();
        building* dst_building = destination();
        int src_int = src_building->type;
        if ((src_int >= BUILDING_BARLEY_FARM && src_int <= BUILDING_CHICKPEAS_FARM)
            || src_int == BUILDING_FISHING_WHARF) {
            dist = calc_distance_with_penalty(src_building->tile, dst_building->tile,
                                              src_building->distance_from_entry,dst_building->distance_from_entry);
        }
        if (dist >= 64) {
            set_destination(0);
        }
    }

    if (has_destination()) {
        return advance_action(FIGURE_ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY);
    }

    // priority 3: workshop for raw material
    int workshop_id = building_get_workshop_for_raw_material_with_room(tile, resource_id, warehouse->distance_from_entry, road_network_id, &dst);
    set_destination(workshop_id);
    if (has_destination()) {
        return advance_action(FIGURE_ACTION_23_CARTPUSHER_DELIVERING_TO_WORKSHOP);
    }

    // priority 4: warehouse
    set_destination(building_storageyard_for_storing(0, tile, resource_id, warehouse->distance_from_entry, road_network_id, &understaffed_storages, &dst));
    if (has_destination())
        return advance_action(FIGURE_ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE);

    // priority 5: granary forced when on stockpile
    set_destination(building_granary_for_storing(tile,
                                                 resource_id, warehouse->distance_from_entry, road_network_id, 1,
                                                 &understaffed_storages, &dst));
    if (config_get(CONFIG_GP_CH_FARMS_DELIVER_CLOSE)) {
        int dist = 0;
        building* src_building = home();
        building* dst_building = destination();
        int src_int = src_building->type;
        if ((src_int >= BUILDING_BARLEY_FARM && src_int <= BUILDING_CHICKPEAS_FARM)
            || src_int == BUILDING_FISHING_WHARF)
            dist = calc_distance_with_penalty(src_building->tile, dst_building->tile,
                                              src_building->distance_from_entry, dst_building->distance_from_entry);
        if (dist >= 64)
            set_destination(0);
    }

    if (has_destination()) {
        return advance_action(FIGURE_ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY);
    }

    // no one will accept
    min_max_seen = understaffed_storages ? 2 : 1;
    advance_action(ACTION_8_RECALCULATE);
}

void figure::determine_deliveryman_destination_food() {
    building* b = home();
    int road_network_id = map_road_network_get(tile.grid_offset());
    map_point dst;
    // priority 1: accepting granary for food
    int dst_building_id = building_granary_for_storing(tile, resource_id, b->distance_from_entry, road_network_id, 0, 0, &dst);
    if (dst_building_id && config_get(CONFIG_GP_CH_FARMS_DELIVER_CLOSE)) {
        int dist = 0;
        building* dst_building = building_get(dst_building_id);

        if ((b->type >= BUILDING_BARLEY_FARM && b->type <= BUILDING_CHICKPEAS_FARM) || b->type == BUILDING_FISHING_WHARF) {
            dist = calc_distance_with_penalty(b->tile, dst_building->tile, b->distance_from_entry, dst_building->distance_from_entry);
        }

        if (dist >= 64) {
            dst_building_id = 0;
        }
    }

    if (dst_building_id) {
        set_destination(dst_building_id);
        return advance_action(FIGURE_ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY);
    }
    // priority 2: warehouse
    dst_building_id = building_storageyard_for_storing(0, tile, resource_id, b->distance_from_entry, road_network_id, 0, &dst);
    if (dst_building_id) {
        set_destination(dst_building_id);
        return advance_action(FIGURE_ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE);
    }

    // priority 3: granary
    dst_building_id = building_granary_for_storing(tile, resource_id, b->distance_from_entry, road_network_id, 1, 0, &dst);
    if (dst_building_id) {
        set_destination(dst_building_id);
        return advance_action(FIGURE_ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY);
    }
    // no one will accept, stand idle
    advance_action(ACTION_8_RECALCULATE);
}