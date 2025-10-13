#include "figure_librarian.h"

#include "figure/service.h"
#include "city/city.h"
#include "figure/service.h"
#include "building/building_house.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_librarian);

int figure_librarian::provide_service() {
    int houses_serviced = figure_provide_culture(tile(), &base, [] (building* b, figure *f) {
        auto house = ((building *)b)->dcast_house();

        if (house) {
            auto &housed = house->runtime_data();
            housed.library = MAX_COVERAGE;
        }
    });
    return houses_serviced;
}