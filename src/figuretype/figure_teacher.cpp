#include "figure_teacher.h"

#include "city/city_health.h"
#include "city/city.h"
#include "city/ratings.h"
#include "building/building_house.h"
#include "figure/service.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_teacher)

int figure_teacher::provide_service() {
    int houses_serviced = figure_provide_service(tile(), &base, [] (building *b, figure *f) {
        auto house = b->dcast_house();
        if (!house) {
            return;
        }

        if (f->home()->stored_amount(RESOURCE_PAPYRUS) <= 0) {
            return;
        }

        const uint8_t delta_allow_papyrus = MAX_COVERAGE / 4;
        auto &housed = house->runtime_data();
        if ((MAX_COVERAGE - housed.school) > delta_allow_papyrus) {
            f->home()->consume_resource(RESOURCE_PAPYRUS, 1);
        }
        housed.school = MAX_COVERAGE;
    });
    return houses_serviced;
}