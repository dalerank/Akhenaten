#include "building_police_station.h"

#include "city/object_info.h"
#include "window/building/common.h"
#include "graphics/elements/ui.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_police_station);

void building_police_station::spawn_figure() {
    common_spawn_roamer(FIGURE_CONSTABLE, 50, FIGURE_ACTION_70_FIREMAN_CREATED);
}
