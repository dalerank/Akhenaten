#include "figure_juggler.h"

#include "figure/service.h"
#include "city/city.h"
#include "figure/service.h"
#include "building/building_entertainment.h"
#include "building/building_house.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_juggler);

void figure_juggler::update_shows() {
    auto ent = destination()->dcast_entertainment();
    ent->runtime_data().juggler_visited = 32;
}

svector<e_building_type, 4> figure_juggler::allow_venue_types() const {
    return {BUILDING_BOOTH, BUILDING_BANDSTAND, BUILDING_PAVILLION};
}

int figure_juggler::provide_service() {
    int houses_serviced = 0;
    building* b = home();

    if (b->type == BUILDING_BOOTH) {
        houses_serviced = figure_provide_culture(tile(), &base, [] (building *b, figure *f) {
            auto house = b->dcast_house();
            if (house) {
                house->runtime_data().booth_juggler = MAX_COVERAGE;
            }
        });

    } else if (b->type == BUILDING_BANDSTAND) {
        houses_serviced = provide_entertainment(0, [] (building * b, int shows) {
            auto house = b->dcast_house();
            if (house) {
                house->runtime_data().bandstand_juggler = MAX_COVERAGE;
            }
        });
    }
    return houses_serviced;
}

