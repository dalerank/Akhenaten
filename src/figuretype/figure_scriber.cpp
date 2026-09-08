#include "figuretype/figure_scriber.h"

#include "figure/service.h"
#include "building/building_house.h"
#include "city/city.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_scriber);

int figure_scriber::provide_service() {
    int houses_serviced = figure_provide_culture(tile(), &base, [] (building *b, figure *f) {
        auto house = ((building *)b)->dcast_house();

        if (house) {
            auto &housed = house->runtime_data();
            housed.academy = MAX_COVERAGE;
        }
    });
    return houses_serviced;
}
