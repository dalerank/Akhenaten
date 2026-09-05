#include "building_shrine.h"

#include "city/city_warnings.h"
#include "grid/road_access.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_shrine_osiris);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_shrine_ra);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_shrine_ptah);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_shrine_seth);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_shrine_bast);

// Vanilla accepts a road anywhere within two tiles of a shrine, so the generic
// adjacent-tile "#needs_road_access" check is disabled through no_road_access and
// replaced by a radius check with the shrine-specific message (#639).
void building_shrine::on_place_checks() {
    constexpr int shrine_road_radius = 2;

    construction_warnings warnings;
    const tile2i road = map_closest_road_within_radius(tile(), size(), shrine_road_radius);
    warnings.add_if(!road.valid(), "#shrines_near_road_required");
}
