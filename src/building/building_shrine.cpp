#include "building_shrine.h"

#include "building/count.h"
#include "city/city_warnings.h"
#include "grid/road_access.h"

buildings::model_t<building_shrine_osiris> shrine_osiris_m;
buildings::model_t<building_shrine_ra>   shrine_ra_m;
buildings::model_t<building_shrine_ptah> shrine_ptah_m;
buildings::model_t<building_shrine_seth> shrine_seth_m;
buildings::model_t<building_shrine_bast> shrine_bast_m;

void building_shrine::on_place_checks() {
    construction_warnings warnings;

    const bool has_road = map_has_road_access(tile(), 2);
    warnings.add_if(!has_road, WARNING_ROAD_ACCESS_NEEDED);
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

void building_shrine::update_count() const {
    building_increase_type_count(type(), true);
}
