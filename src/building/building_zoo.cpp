#include "building_zoo.h"

#include "city/city.h"
#include "city/city_population.h"
#include "game/resource.h"
#include "js/js_register.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_zoo);

bool building_zoo::add_resource(e_resource resource, int amount, figure_id fid) {
    if (resource != RESOURCE_STRAW && resource != RESOURCE_GAMEMEAT) {
        return false;
    }

    store_resource(resource, amount);
    return true;
}
