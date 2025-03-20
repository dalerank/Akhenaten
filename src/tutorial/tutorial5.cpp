#include "game/tutorial.h"

#include "io/gamefiles/lang.h"
#include "building/building_house.h"
#include "building/building_menu.h"
#include "building/building_storage_yard.h"
#include "game/game.h"
#include "city/message.h"
#include "building/count.h"
#include "city/city.h"

void tutorial_5::reset() {
    g_tutorials_flags.tutorial_5.started = 0;
    g_tutorials_flags.tutorial_5.spacious_apartment = 0;
    g_tutorials_flags.tutorial_5.papyrus_made = 0;
    g_tutorials_flags.tutorial_5.bricks_bought = 0;
}

void tutorial5_handle_spacious_apartment(event_advance_day) {
    if (g_tutorials_flags.tutorial_5.spacious_apartment) {
        return;
    }

    if (building_count_total(BUILDING_HOUSE_SPACIOUS_APARTMENT) < 1) {
        return;
    }

    g_tutorials_flags.tutorial_5.spacious_apartment = true;
    events::unsubscribe(&tutorial5_handle_spacious_apartment);
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day();
    building_menu_update(tutorial_stage.tutorial_education);
    city_message_post(true, MESSAGE_TUTORIAL_EDUCATION, 0, 0);
}

void tutorial5_handle_papyrus(event_warehouse_filled ev) {
    if (g_tutorials_flags.tutorial_5.papyrus_made) {
        return;
    }

    if (g_city.resource.yards_stored(RESOURCE_PAPYRUS) < 100) {
        return;
    }

    g_tutorials_flags.tutorial_5.papyrus_made = true;
    events::unsubscribe(&tutorial5_handle_papyrus);
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day();
    building_menu_update(tutorial_stage.tutorial_trading);
    city_message_post(true, MESSAGE_TUTORIAL_TRADE_WITH_OTHER_CITIES, 0, 0);
}

void tutorial5_handle_bricks(event_warehouse_filled ev) {
    if (g_tutorials_flags.tutorial_5.bricks_bought) {
        return;
    }

    if (g_city.resource.yards_stored(RESOURCE_BRICKS) < 100) {
        return;
    }

    g_tutorials_flags.tutorial_5.bricks_bought = true;
    events::unsubscribe(&tutorial5_handle_bricks);
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day();
    building_menu_update(tutorial_stage.tutorial_monuments);
    city_message_post(true, MESSAGE_TUTORIAL_MONUMENTS, 0, 0);
}

bool tutorial5_is_success() {
    auto &tut = g_tutorials_flags.tutorial_5;
    const bool may_finish = (tut.spacious_apartment && tut.papyrus_made && tut.bricks_bought);
    const bool some_days_after_last_action = (game.simtime.absolute_day() - g_tutorials_flags.pharaoh.last_action) > 3;
    return may_finish && some_days_after_last_action;
}

void tutorial_5::init() {
    if (g_tutorials_flags.tutorial_5.spacious_apartment) building_menu_update(tutorial_stage.tutorial_education);
    else events::subscribe(&tutorial5_handle_spacious_apartment);

    if (g_tutorials_flags.tutorial_5.papyrus_made) building_menu_update(tutorial_stage.tutorial_trading);
    else events::subscribe(&tutorial5_handle_papyrus);

    if (g_tutorials_flags.tutorial_5.bricks_bought) building_menu_update(tutorial_stage.tutorial_monuments);
    else events::subscribe(&tutorial5_handle_bricks);

    g_city.victory_state.add_condition(&tutorial5_is_success);
}

xstring tutorial_5::goal_text() {
    if (!g_tutorials_flags.tutorial_5.spacious_apartment) {
        return lang_get_xstring(62, 31);
    } 
    
    if (!g_tutorials_flags.tutorial_5.papyrus_made) {
        return lang_get_xstring(62, 30);
    } 
    
    if (!g_tutorials_flags.tutorial_5.bricks_bought) {
        return lang_get_xstring(62, 29);
    }

    return lang_get_xstring(62, 34);
}