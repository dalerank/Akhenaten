#include "figure_zookeeper.h"

#include "building/building_entertainment.h"
#include "building/building_house.h"
#include "city/city.h"
#include "figure/service.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_zookeeper);

void figure_zookeeper::update_shows() {
    building *dest = destination();
    if (!dest) {
        return;
    }

    building_entertainment *entertainment = dest->dcast_entertainment();
    if (!entertainment) {
        return;
    }

    // Reuse juggler_visited as "animals present / show active" timer (same pattern as senet).
    entertainment->runtime_data().juggler_visited = 32;
}

int figure_zookeeper::provide_service() {
    return figure_provide_culture(tile(), &base, [](building *b, figure * /*f*/) {
        auto house = b->dcast_house();
        if (house) {
            house->runtime_data().zookeeper = MAX_COVERAGE;
        }
    });
}
