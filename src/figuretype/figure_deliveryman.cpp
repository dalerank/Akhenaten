#include "figure_cartpusher.h"

#include "building/building_granary.h"
#include "building/industry.h"
#include "building/building_storage_yard.h"
#include "city/buildings.h"
#include "city/city_resource.h"
#include "core/calc.h"
#include "figure/figure.h"
#include "figure/movement.h"
#include "game/resource.h"
#include "grid/point.h"
#include "grid/road_network.h"
#include "game/game_config.h"

void figure::determine_deliveryman_destination_food() {
    building* b = home();
    int road_network_id = map_road_network_get(tile.grid_offset());
    tile2i dst;
    // priority 1: accepting granary for food
    int dst_building_id = building_granary_for_storing(tile, resource_id, b->distance_from_entry, road_network_id, 0, 0, &dst);
    if (dst_building_id && g_ankh_config.get(CONFIG_GP_CH_FARMS_DELIVER_CLOSE)) {
        int dist = 0;
        building* dst_building = building_get(dst_building_id);

        if (dst_building->dcast_farm() || dst_building->dcast_fishing_wharf()) {
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
    dst_building_id = building_storage_yard_for_storing(tile, resource_id, b->distance_from_entry, road_network_id, 0, dst);
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