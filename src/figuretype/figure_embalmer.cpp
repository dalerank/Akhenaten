#include "figuretype/figure_embalmer.h"

#include "figure/service.h"
#include "building/building_house.h"
#include "building/building_mortuary.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_embalmer);

void figure_embalmer::figure_before_action() {
    auto b = home();
    if (b->state != BUILDING_STATE_VALID || !b->has_figure(0, id())) {
        poof();
    }
}

int figure_embalmer::provide_service() {
    building *mortuary_building = home();
    if (!mortuary_building) {
        return 0;
    }

    auto mortuary = mortuary_building->dcast_mortuary();
    if (!mortuary) {
        return 0;
    }

    auto &mortuary_data = mortuary->runtime_data();
    const auto &params = mortuary->current_params();

    // Check if already served max_serve_clients residents this month
    if (mortuary_data.residents_served_this_month >= params.max_serve_clients) {
        return 0;
    }

    int houses_serviced = figure_provide_culture(tile(), &base, [&] (building *b, figure *f) {
        auto house = b->dcast_house();
        if (!house || house->house_population() <= 0) {
            return;
        }

        auto &housed = house->runtime_data();

        if (housed.mortuary < MAX_COVERAGE / 2) {
            int house_population = house->house_population();
            mortuary_data.residents_served_this_month += house_population;
            housed.mortuary = MAX_COVERAGE;
        }
    });
    return houses_serviced;
}
