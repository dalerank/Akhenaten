#include "building_irrigation_ditch.h"

building_irrigation_ditch::static_params irrigation_ditch_m;

building_irrigation_ditch::building_irrigation_ditch(building &b) : building_impl(b) {
}

void building_irrigation_ditch::on_place_checks() {
    // nothing
}
