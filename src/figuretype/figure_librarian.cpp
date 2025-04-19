#include "figure_librarian.h"

#include "city/labor.h"
#include "figure/service.h"
#include "city/city.h"
#include "figure/service.h"
#include "building/building_house.h"

figures::model_t<figure_librarian> librarian_m;

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

const animations_t &figure_librarian::anim() const {
    return librarian_m.anim;
}
