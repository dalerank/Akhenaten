#include "figure_teacher.h"

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

        house->runtime_data().school = MAX_COVERAGE;
    });
    return houses_serviced;
}
