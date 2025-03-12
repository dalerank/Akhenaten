#include "game/tutorial.h"

#include "building/building_menu.h"
#include "city/message.h"
#include "building/building_granary.h"
#include "building/building_storage_yard.h"
#include "city/city.h"
#include "game/game.h"

void tutorial_3::reset() {
    g_tutorials_flags.tutorial_3.started = 0;
    g_tutorials_flags.tutorial_3.figs_800_stored = 0;
    g_tutorials_flags.tutorial_3.pottery_made_1 = 0;
    g_tutorials_flags.tutorial_3.pottery_made_2 = 0;
}

void tutorial3_on_filled_granary(event_granary_filled ev) {
    if (g_tutorials_flags.tutorial_3.figs_800_stored) {
        return;
    }

    if (ev.amount < 800) {
        return;
    }

    auto granary = building_get(ev.bid)->dcast_granary();
    const int figs_stored = granary ? granary->amount(RESOURCE_FIGS) : 0;

    if (figs_stored < 800) {
        return;
    }

    g_city_events.removeListener<event_granary_filled>(&tutorial3_on_filled_granary);
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day();
    g_tutorials_flags.tutorial_3.figs_800_stored = true;
    building_menu_update(tutorial_stage.tutorial_industry);
    city_message_post(true, MESSAGE_TUTORIAL_INDUSTRY, 0, 0);
}

void tutorial3_on_disease(event_city_disease ev) {
    if (g_tutorials_flags.tutorial_3.disease) {
        return;
    }

    g_city_events.removeListener<event_city_disease>(&tutorial3_on_disease);
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day();
    g_tutorials_flags.tutorial_3.disease = true;
    building_menu_update(tutorial_stage.tutorial_health);
    city_message_post(true, MESSAGE_TUTORIAL_BASIC_HEALTHCARE, 0, 0);
}

void tutorial_3::update_step(xstring s) {
    if (s == tutorial_stage.tutorial_health) {
        building_menu_update(s);
        city_message_post(true, MESSAGE_TUTORIAL_BASIC_HEALTHCARE, 0, 0);
    }

    if (s == tutorial_stage.tutorial_industry) {
        building_menu_update(s);
        city_message_post(true, MESSAGE_TUTORIAL_INDUSTRY, 0, 0);
    }
}

void tutorial3_warehouse_pottery_1_check(event_warehouse_filled ev) {
    if (g_tutorials_flags.tutorial_3.pottery_made_1) {
        return;
    } 
    
    if (city_resource_warehouse_stored(RESOURCE_POTTERY) < 100) {
        return;
    }

    g_city_events.removeListener<event_warehouse_filled>(&tutorial3_warehouse_pottery_1_check);
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day();
    g_tutorials_flags.tutorial_3.pottery_made_1 = true;
    g_tutorials_flags.tutorial_3.pottery_made_year = game.simtime.year;

    city_message_post(true, MESSAGE_TUTORIAL_FOOD_OR_FAMINE, 0, 0);
}

void tutorial3_warehouse_pottery_2_check(event_warehouse_filled ev) {
    if (g_tutorials_flags.tutorial_3.pottery_made_2) {
        return;
    }
    
    if (city_resource_warehouse_stored(RESOURCE_POTTERY) < 200) {
        return;
    }

    g_city_events.removeListener<event_warehouse_filled>(&tutorial3_warehouse_pottery_2_check);
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day();
    g_tutorials_flags.tutorial_3.pottery_made_2 = true;
    building_menu_update(tutorial_stage.tutorial_gardens);
    city_message_post(true, MESSAGE_TUTORIAL_MUNICIPAL_STRUCTURES, 0, 0);
}

bool tutorial3_is_success() {
    auto &tut = g_tutorials_flags.tutorial_3;
    const bool may_finish = (tut.figs_800_stored && tut.pottery_made_1 && tut.pottery_made_2 && tut.disease);
    const bool some_days_after_last_action = (game.simtime.absolute_day() - g_tutorials_flags.pharaoh.last_action) > 3;
    return may_finish && some_days_after_last_action;
}

int tutorial_3::goal_text() {
    if (!g_tutorials_flags.tutorial_3.figs_800_stored) {
        return 28;
    } else if (!g_tutorials_flags.tutorial_3.pottery_made_1) {
        return 27;
    } else {
        return 26;
    }
}

void tutorial3_hunger_halt_immgrants(event_advance_month ev) {
    if(game.simtime.month >= 5) {
       city_message_post_with_message_delay(MESSAGE_CAT_TUTORIAL3, 1, MESSAGE_TUTORIAL_HUNGER_HALTS_IMMIGRANTS, 1200);
       g_city_events.removeListener<event_advance_month>(&tutorial3_hunger_halt_immgrants);
    }
}

void tutorial_3::init() {
    if (g_tutorials_flags.tutorial_3.figs_800_stored) building_menu_update(tutorial_stage.tutorial_industry);
    else g_city_events.appendListener<event_granary_filled>(&tutorial3_on_filled_granary);

    if (g_tutorials_flags.tutorial_3.pottery_made_1) building_menu_update(tutorial_stage.tutorial_industry);
    else g_city_events.appendListener<event_warehouse_filled>(&tutorial3_warehouse_pottery_1_check);

    if (g_tutorials_flags.tutorial_3.pottery_made_2) building_menu_update(tutorial_stage.tutorial_gardens);
    else g_city_events.appendListener<event_warehouse_filled>(&tutorial3_warehouse_pottery_2_check);

    if (g_tutorials_flags.tutorial_3.disease) building_menu_update(tutorial_stage.tutorial_health);
    else g_city_events.appendListener<event_city_disease>(&tutorial3_on_disease);

    if (game.simtime.month < 5) {
        g_city_events.appendListener<event_advance_month>(&tutorial3_hunger_halt_immgrants);
    }

    g_city.victory_state.add_condition(&tutorial3_is_success);
}