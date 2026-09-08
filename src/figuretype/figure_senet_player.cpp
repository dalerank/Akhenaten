#include "figure_senet_player.h"

#include "figure/service.h"
#include "city/city.h"
#include "figure/service.h"
#include "building/building_house.h"
#include "building/building_entertainment.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_senet_player);

void figure_senet_player::update_shows() {
    building_entertainment *entertainment = destination()->dcast_entertainment();
    auto &d = entertainment->runtime_data();
    d.juggler_visited = 32;
}

int figure_senet_player::provide_service() {
    int houses_serviced = 0;
    houses_serviced = figure_provide_culture(tile(), &base, [] (building *b, figure *f) {
        auto house = ((building *)b)->dcast_house();

        if (house) {
            auto &housed = house->runtime_data();
            housed.senet_player = MAX_COVERAGE;
        }
    });
    return houses_serviced;
}

