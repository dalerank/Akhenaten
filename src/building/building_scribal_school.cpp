#include "building_scribal_school.h"

#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_scribal_school);

bool building_scribal_school::add_resource(e_resource resource, int amount) {
    if (resource != RESOURCE_PAPYRUS) {
        return false;
    }

    verify_no_crash(id() > 0);
    store_resource(RESOURCE_PAPYRUS, amount);
    return true;
}
