#include "game/tutorial.h"

#include "building/building_menu.h"
#include "city/city_message.h"
#include "building/building_storage_yard.h"
#include "city/city.h"
#include "city/city_events.h"
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

    return "#reach_modest_houses_number";
}

void tutorial4_warehouse_beer_check(event_warehouse_filled ev) {
    if (g_tutorials_flags.tutorial_4.beer_made) {
        return;
    }

    if (g_city.resource.yards_stored(RESOURCE_BEER) < 300) {
        return;
    }

    g_tutorials_flags.tutorial_4.beer_made = true;
    events::unsubscribe(&tutorial4_warehouse_beer_check);
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day(true);
    building_menu_update(tutorial_stage.tutorial_finance);
    messages::popup(MESSAGE_TUTORIAL_FINANCES, 0, 0);
}

bool tutorial4_is_success() {
    auto &tut = g_tutorials_flags.tutorial_4;
    const bool may_finish = (tut.beer_made && tut.tax_collector_built);
    const bool some_days_after_last_action = (game.simtime.absolute_day(true) - g_tutorials_flags.pharaoh.last_action) > 3;
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

    events::unsubscribe(&tutorial_4_on_build_tax_collector);
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day(true);
    g_tutorials_flags.tutorial_4.tax_collector_built = true;
}
    
void tutorial_4::init() {
    if (g_tutorials_flags.tutorial_4.beer_made) building_menu_update(tutorial_stage.tutorial_finance);
    else events::subscribe(&tutorial4_warehouse_beer_check);

    if (!g_tutorials_flags.tutorial_4.tax_collector_built) {
        events::subscribe(&tutorial_4_on_build_tax_collector);
    }
    
    g_city.victory_state.add_condition(&tutorial4_is_success);

    const auto advisors = { ADVISOR_LABOR, ADVISOR_ENTERTAINMENT, ADVISOR_RELIGION, ADVISOR_FINANCIAL };
    for (auto a : advisors) {
        g_city.set_advisor_available(a, AVAILABLE);
    }
}