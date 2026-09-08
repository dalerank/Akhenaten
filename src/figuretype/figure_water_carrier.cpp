#include "figure_water_carrier.h"

#include "city/city_health.h"
#include "city/ratings.h"
#include "city/city.h"
#include "city/city_recorded_paths.h"
#include "figure/service.h"
#include "grid/building.h"
#include "graphics/animation.h"
#include "building/building_house.h"
#include "building/building_brewery.h"
#include "building/building_well.h"
#include "game/game_config.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_water_carrier);

void figure_water_carrier::figure_before_action() {
    building* b = home();
    if (!b->is_valid() || !b->has_figure(0, id())) {
        poof();
    }
}

void figure_water_carrier::figure_action() {
    building* b = home();
    switch (action_state()) {
    case ACTION_72_WATER_CARRIER_ROAMING:
        do_roam(TERRAIN_USAGE_ROADS, ACTION_73_WATER_CARRIER_RETURNING);
        break;

    case ACTION_73_WATER_CARRIER_RETURNING:
        if (do_returnhome(TERRAIN_USAGE_PREFER_ROADS)) {
            building *h = home();
            if (h && h->params().flags.keeps_visitor_paths) {
                building *main = h->main();
                if (main) {
                    g_recorded_paths.handoff_to_building(base, main->id);
                }
            }
        }
        break;

    case ACTION_150_WATER_CARRIER_ATTACKED:
        kill();
        break;

    default:
        advance_action(ACTION_72_WATER_CARRIER_ROAMING);
        break;
    }
}

int figure_water_carrier::provide_service() {
    int houses_serviced = figure_provide_service(tile(), &base, [] (building *b, figure *f) {
        auto house = b->dcast_house();

        if (house) {
            auto &housed = house->runtime_data();
            housed.water_supply = MAX_COVERAGE;
        }

        if (!!game_features::gameplay_brewery_requires_water) {
            auto brewery = b->dcast_brewery();
            if (brewery) {
                constexpr uint8_t MAX_WATER = 100;
                brewery->set_water_stored(MAX_WATER);
            }
        }

        // Refresh well ornaments immediately when nearby house coverage changes.
        if (auto well = b->dcast_well()) {
            well->update_animation();
            well->update_graphic();
        }
    });

    return houses_serviced;
}

void figure_water_carrier::acquire_attack() {
    kill();
}
