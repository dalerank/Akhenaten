#include "figure_zookeeper.h"

#include "building/building_house.h"
#include "city/city.h"
#include "figure/service.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_zookeeper);

void figure_zookeeper::update_shows() {
    // figure_entertainer_update_shows writes show days only for juggler, musician and dancer.
}

int figure_zookeeper::provide_service() {
    return figure_provide_culture(tile(), &base, [](building *b, figure * /*f*/) {
        auto house = b->dcast_house();
        if (house) {
            house->runtime_data().zookeeper = MAX_COVERAGE;
        }
    });
}
