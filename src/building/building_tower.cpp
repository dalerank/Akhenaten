#include "building_tower.h"

#include "grid/terrain.h"
#include "grid/road_access.h"
#include "grid/building_tiles.h"
#include "grid/tiles.h"
#include "graphics/elements/ui.h"
#include "window/building/common.h"
#include "io/gamefiles/lang.h"
#include "core/direction.h"
#include "figure/figure.h"
#include "building/building_barracks.h"
#include "city/city_warnings.h"
#include "building/building_wall.h"
#include "figuretype/figure_ballista.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_brick_tower);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_mud_tower);

void building_tower::on_create(int orientation) {
    map_terrain_remove_with_radius(tile(), current_params().building_size, 0, TERRAIN_WALL);
    const int imgid = base_img();
    map_building_tiles_add(id(), tile(), current_params().building_size, imgid, TERRAIN_BUILDING | TERRAIN_GATEHOUSE);

    building_mud_wall::update_area_walls(tile(), 5);
}

void building_tower::on_place_checks() {
    building_impl::on_place_checks();

    construction_warnings warnings;
    const bool near_walls = !map_terrain_is_adjacent_to_wall(tilex(), tiley(), size());
    warnings.add_if(!near_walls, "#warning_shipwright_needed");
}

void building_tower::spawn_figure() {
    check_labor_problem();
    tile2i road = map_get_road_access_tile(tile(), base.size);
    if (!road.valid()) {
        return;
    }

    common_spawn_labor_seeker(current_params().min_houses_coverage);
    if (num_workers() <= 0) {
        return;
    }

    if (base.has_figure(0) && !base.has_figure(BUILDING_SLOT_BALLISTA)) { // has sentry but no ballista -> create
        create_figure_generic(FIGURE_BALLISTA, (e_figure_action)ACTION_180_BALLISTA_CREATED, BUILDING_SLOT_BALLISTA, DIR_0_TOP_RIGHT);
    }

    if (!base.has_figure(0)) {
        building_barracks_request_tower_sentry();
    }
}
