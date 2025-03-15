#include "game/tutorial.h"

#include "building/building_menu.h"
#include "city/message.h"
#include "building/building_storage_yard.h"
#include "city/city.h"
#include "io/gamefiles/lang.h"
#include "game/game.h"

void tutorial_4::reset() {
    g_tutorials_flags.tutorial_4.started = 0;
    g_tutorials_flags.tutorial_4.beer_made = 0;
    g_tutorials_flags.tutorial_4.tax_collector_built = 0;
}

xstring tutorial_4::goal_text() {
    if (!g_tutorials_flags.tutorial_4.beer_made) {
        return lang_get_xstring(62, 33);
    }

    if (!g_tutorials_flags.tutorial_4.tax_collector_built) {
        return "#build_tax_collector";
    }

    return "#read_modest_houses_number";
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

bool tutorial4_is_success() {
    auto &tut = g_tutorials_flags.tutorial_4;
    const bool may_finish = (tut.beer_made && tut.tax_collector_built);
    const bool some_days_after_last_action = (game.simtime.absolute_day() - g_tutorials_flags.pharaoh.last_action) > 3;
    return may_finish && some_days_after_last_action;
}

void tutorial_4_on_build_tax_collector(event_building_create ev) {
    if (g_tutorials_flags.tutorial_4.tax_collector_built) {
        return;
    }

    building *b = building_get(ev.bid);
    if (b->type != BUILDING_TAX_COLLECTOR) {
        return;
    }

    g_city_events.unsubscribe<event_building_create>(&tutorial_4_on_build_tax_collector);
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day();
    g_tutorials_flags.tutorial_4.tax_collector_built = true;
}
    
void tutorial_4::init() {
    if (g_tutorials_flags.tutorial_4.beer_made) building_menu_update(tutorial_stage.tutorial_finance);
    else g_city_events.subscribe<event_warehouse_filled>(&tutorial4_warehouse_beer_check);

    if (!g_tutorials_flags.tutorial_4.tax_collector_built) {
        g_city_events.subscribe<event_building_create>(&tutorial_4_on_build_tax_collector);
    }
    
    g_city.victory_state.add_condition(&tutorial4_is_success);
}