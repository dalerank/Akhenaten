#include "building_plaza.h"

#include "building/building.h"
#include "building/count.h"
#include "city/object_info.h"
#include "city/labor.h"
#include "city/warnings.h"
#include "grid/road_access.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "game/game.h"
#include "building_shrine.h"

buildings::model_t<building_shrine_osiris> shrine_osiris_m;
buildings::model_t<building_shrine_ra>   shrine_ra_m;
buildings::model_t<building_shrine_ptah> shrine_ptah_m;
buildings::model_t<building_shrine_seth> shrine_seth_m;
buildings::model_t<building_shrine_bast> shrine_bast_m;

void building_shrine::on_place_checks() {
    if (!map_has_road_access(tile(), 2)) {
        building_construction_warning_show(WARNING_ROAD_ACCESS_NEEDED);
    }
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
