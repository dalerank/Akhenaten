#include "game/tutorial.h"

#include "building/building_menu.h"
#include "city/message.h"
#include "building/building_storage_yard.h"
#include "city/city.h"
#include "game/game.h"

void tutorial_4::reset() {
    g_tutorials_flags.tutorial_4.started = 0;
    g_tutorials_flags.tutorial_4.beer_made = 0;
}

int tutorial_4::goal_text() {
    if (!g_tutorials_flags.tutorial_4.beer_made) {
        return 33;
    }
}

void tutorial4_warehouse_beer_check(event_warehouse_filled ev) {
    if (g_tutorials_flags.tutorial_4.beer_made) {
        return;
    }

    if (city_resource_warehouse_stored(RESOURCE_BEER) < 300) {
        return;
    }

    g_tutorials_flags.tutorial_4.beer_made = true;
    g_city_events.removeListener<event_warehouse_filled>(&tutorial4_warehouse_beer_check);
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day();
    building_menu_update(tutorial_stage.tutorial_finance);
    city_message_post(true, MESSAGE_TUTORIAL_FINANCES, 0, 0);
}
    
void tutorial_4::init() {
    if (g_tutorials_flags.tutorial_4.beer_made) building_menu_update(tutorial_stage.tutorial_finance);
    else g_city_events.appendListener<event_warehouse_filled>(&tutorial4_warehouse_beer_check);;
}