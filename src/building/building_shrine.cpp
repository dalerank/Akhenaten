#include "building_shrine.h"

#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_shrine_osiris);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_shrine_ra);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_shrine_ptah);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_shrine_seth);
REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_shrine_bast);

void building_shrine::on_place_checks() {
    // chain to base: emits #needs_road_access (with the correct size()-based
    // footprint) and dispatches the es() JS on_place_checks event. Shrines have
    // no workers, so the base #city_needs_more_workers warning self-suppresses.
    building_impl::on_place_checks();
}

e_overlay building_shrine::get_overlay() const {
    switch (type()) {
    case BUILDING_SHRINE_OSIRIS: return OVERLAY_RELIGION_OSIRIS;
    case BUILDING_SHRINE_RA:   return OVERLAY_RELIGION_RA;
    case BUILDING_SHRINE_PTAH: return OVERLAY_RELIGION_PTAH;
    case BUILDING_SHRINE_SETH: return OVERLAY_RELIGION_SETH;
    case BUILDING_SHRINE_BAST: return OVERLAY_RELIGION_BAST;
    default:
        break;
    }

    return OVERLAY_NONE;
}
