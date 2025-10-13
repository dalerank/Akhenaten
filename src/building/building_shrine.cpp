#include "building_shrine.h"

#include "city/city_warnings.h"
#include "grid/road_access.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_shrine_osiris);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_shrine_ra);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_shrine_ptah);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_shrine_seth);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_shrine_bast);

void building_shrine::on_place_checks() {
    construction_warnings warnings;

    const bool has_road = map_has_road_access(tile(), 2);
    warnings.add_if(!has_road, "#needs_road_access");
}

e_overlay building_shrine::get_overlay() const {
    switch (type()) {
    case BUILDING_SHRINE_OSIRIS: return OVERLAY_RELIGION_OSIRIS;
    case BUILDING_SHRINE_RA:   return OVERLAY_RELIGION_RA;
    case BUILDING_SHRINE_PTAH: return OVERLAY_RELIGION_PTAH;
    case BUILDING_SHRINE_SETH: return OVERLAY_RELIGION_SETH;
    case BUILDING_SHRINE_BAST: return OVERLAY_RELIGION_BAST;
    }

    return OVERLAY_NONE;
}
