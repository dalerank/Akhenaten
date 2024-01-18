#include "building_firehouse.h"

void building_firehouse::spawn_figure() {
    base.common_spawn_roamer(FIGURE_FIREMAN, 50, FIGURE_ACTION_70_FIREMAN_CREATED);
}