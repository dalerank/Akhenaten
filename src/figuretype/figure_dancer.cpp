#include "figure_dancer.h"
#include "game/game_events.h"
#include "game/sound_effect.h"

#include "figure/service.h"
#include "building/building_entertainment.h"
#include "building/building_house.h"
#include "js/js_register.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_dancer);

void figure_dancer::update_shows() {
    auto ent = destination()->dcast_entertainment();
    ent->runtime_data().dancer_visited = 32;
}

bool figure_dancer::play_die_sound() {
    events::emit(event_sound_effect{SOUND_EFFECT_DANCER_DIE});
    return true;
}

int figure_dancer::provide_service() {
    building *b = current_destination();
    int houses_serviced = provide_entertainment(0, [] (building *b, int shows) {
        auto house = ((building *)b)->dcast_house();

        if (house) {
            auto &housed = house->runtime_data();
            housed.pavillion_dancer = MAX_COVERAGE;
        }
    });
    return houses_serviced;
}
