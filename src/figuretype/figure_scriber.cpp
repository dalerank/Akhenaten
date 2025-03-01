#include "figuretype/figure_scriber.h"

#include "figure/service.h"
#include "building/building_house.h"

figures::model_t<figure_scriber> scriber_m;

void figure_scriber::figure_action() {
    switch (action_state()) {
    case FIGURE_ACTION_125_ROAMING:
        base.roam_length++;
        if (base.roam_length >= base.max_roam_length) {
            advance_action(FIGURE_ACTION_126_ROAMER_RETURNING);
        }

        break;

    case FIGURE_ACTION_126_ROAMER_RETURNING:
        ; // nothing here
        break;

    }
}

void academy_coverage(building* b, figure *f, int&) {
    auto house = ((building *)b)->dcast_house();

    if (house) {
        auto &housed = house->runtime_data();
        housed.academy = MAX_COVERAGE;
    }
}

int figure_scriber::provide_service() {
    int houses_serviced = figure_provide_culture(tile(), &base, academy_coverage);
    return houses_serviced;
}
