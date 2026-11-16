#include "building_zoo.h"

#include "city/city.h"
#include "game/resource.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_zoo);

void building_zoo::add_ambient_sound(int direction) const {
    // OG scores a zoo as housing ambient; the band follows population, apart from zoo_r.wav.
    const int population = g_city.population.current;
    int channel = SOUND_CHANNEL_CITY_HOUSE_SLUM;
    if (population >= 8000) {
        channel = SOUND_CHANNEL_CITY_HOUSE_POSH;
    } else if (population >= 5000) {
        channel = SOUND_CHANNEL_CITY_HOUSE_GOOD;
    } else if (population >= 2000) {
        channel = SOUND_CHANNEL_CITY_HOUSE_MEDIUM;
    } else if (population >= 500) {
        channel = SOUND_CHANNEL_CITY_HOUSE_POOR;
    }
    sound_city_add_channel(channel, direction);
}

bool building_zoo::add_resource(e_resource resource, int amount, figure_id fid) {
    if (resource != RESOURCE_STRAW && resource != RESOURCE_GAMEMEAT) {
        return false;
    }

    store_resource(resource, amount);
    return true;
}
