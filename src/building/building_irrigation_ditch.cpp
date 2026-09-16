#include "building_irrigation_ditch.h"

#include "grid/routing/routing.h"
#include "grid/routing/routing_terrain.h"
#include "building/construction/routed.h"
#include "grid/canals.h"
#include "game/undo.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_irrigation_ditch);

building_irrigation_ditch::image_set g_canal_images;

void building_irrigation_ditch::static_params::archive_load(archive arch) {
    g_canal_images.begin = first_img("set_begin");
}

int building_construction_place_canal(bool measure_only, tile2i start, tile2i end) {
    game_undo_restore_map(0);
    if (!map_routing_calculate_distances_for_building(ROUTED_BUILDING_CANALS, start)) {
        return 0;
    }

    auto result = place_routed_building(start, end, ROUTED_BUILDING_CANALS);
    if (result.ok && !measure_only) {
        map_canal_update_all_tiles(0);
        map_routing_update_land();
    }

    return result.items;
}

routed_building_result building_construction_place_canal_for_lift(bool measure_only, tile2i start, tile2i end) {
    e_routed_mode type = measure_only ? ROUTED_BUILDING_CANALS_WITHOUT_GRAPHIC : ROUTED_BUILDING_CANALS;
    return place_routed_building(start, end, type);
}

const building_irrigation_ditch::image_set &building_irrigation_ditch::images() {
    return g_canal_images;
}
