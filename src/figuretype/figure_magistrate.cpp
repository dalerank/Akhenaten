#include "figure_magistrate.h"

#include "building/building_house.h"
#include "figure/service.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_magistrate);

int figure_magistrate::provide_service() {
    const int crime_seen = figure_provide_crime_coverage(tile(), current_params().crime_reduction);
    figure_provide_service(tile(), nullptr, [](building* b, figure*) {
        auto house = b->dcast_house();
        if (house && house->house_population() > 0) {
            house->runtime_data().magistrate = MAX_COVERAGE;
        }
    });
    base.min_max_seen = (uint8_t)crime_seen;
    return 0;
}
