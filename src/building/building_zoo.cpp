#include "building_zoo.h"

#include "city/city.h"
#include "city/city_warnings.h"
#include "empire/empire.h"
#include "figuretype/figure_entertainer.h"
#include "game/game.h"
#include "game/game_events.h"
#include "game/resource.h"
#include "graphics/graphics.h"
#include "grid/building_tiles.h"
#include "grid/road_access.h"
#include "js/js_game.h"
#include "window/popup_dialog.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(building_zoo);

int building_zoo::resource_consume_amount() {
    switch (game.difficulty()) {
    case DIFFICULTY_VERY_HARD:
        return 60;
    case DIFFICULTY_HARD:
        return 40;
    default:
        return 20;
    }
}

bool building_zoo::add_resource(e_resource resource, int amount) {
    if (resource != RESOURCE_STRAW && resource != RESOURCE_GAMEMEAT) {
        return false;
    }

    store_resource(resource, amount);
    return true;
}

void building_zoo::spawn_figure() {
    const int need = resource_consume_amount();
    if (stored_amount(RESOURCE_STRAW) < need || stored_amount(RESOURCE_GAMEMEAT) < need) {
        return;
    }

    tile2i road = map_get_road_access_tile(tile(), size());
    if (!road.valid()) {
        return;
    }
    base.road_access = road;
    base.has_road_access = true;

    if (!common_spawn_figure_trigger(100, BUILDING_SLOT_SERVICE)) {
        return;
    }

    consume_resource(RESOURCE_STRAW, need);
    consume_resource(RESOURCE_GAMEMEAT, need);
    // Animals are present once feed is consumed; ACTION_94 roamers never hit update_shows().
    runtime_data().juggler_visited = 32;
    create_roaming_figure(FIGURE_ZOOKEEPER, (e_figure_action)ACTION_94_ENTERTAINER_ROAMING, BUILDING_SLOT_SERVICE);
}