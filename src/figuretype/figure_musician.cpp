#include "figure_musician.h"

#include "figure/service.h"
#include "city/city_health.h"
#include "city/ratings.h"
#include "city/city.h"
#include "building/building_entertainment.h"
#include "building/building_house.h"
#include "building/building_dance_school.h"
#include "game/game_config.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_musician);

void figure_musician::update_shows() {
    building_entertainment* ent = destination()->dcast_entertainment();
    if (!ent) {
        return;
    }

    ent->runtime_data().musician_visited = 32;
}

svector<e_building_type, 4> figure_musician::allow_venue_types() const {
    return {BUILDING_BANDSTAND, BUILDING_PAVILLION};
}

int figure_musician::provide_service() {
    int houses_serviced = 0;
    building *b = current_destination();
    
    // If musician visits dance school, increase conservatory help parameter to 100
    if (!!game_features::gameplay_conservatory_helps_dance_school && b->type == BUILDING_DANCE_SCHOOL) {
        building_dancer_school* dance_school = b->dcast_dancer_school();
        if (dance_school) {
            auto &d = dance_school->runtime_data();
            d.conservatory_help = 100;
        }
        return 0; // No houses serviced, but help was provided
    }
    
    if (b->type == BUILDING_BANDSTAND) {
        houses_serviced = provide_entertainment(0, [] (building *b, int shows) {
            auto house = b->dcast_house();
            if (house) {
                house->runtime_data().bandstand_musician = MAX_COVERAGE;
            }
        });
    } else if (b->type == BUILDING_PAVILLION) {
        houses_serviced = provide_entertainment(0, [] (building *b, int shows) {
            auto house = b->dcast_house();
            if (house) {
                house->runtime_data().pavillion_musician = MAX_COVERAGE;
            }
        });
    }

    return houses_serviced;
}

