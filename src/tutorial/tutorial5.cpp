#include "game/tutorial.h"

#include "io/gamefiles/lang.h"
#include "building/building_house.h"
#include "building/building_storage_yard.h"
#include "game/game.h"
#include "city/city_message.h"
#include "city/city.h"
#include "city/city_building_menu_ctrl.h"
#include "game/game_events.h"

struct tutorial_5 : public tutorial_t {
    virtual int missionid() const override { return 5; }
    virtual void init() override;
    virtual void reset() override;
    virtual void update_step(xstring s) override;
    virtual xstring goal_text() override;
};

tutorial_5 g_tutorial_5;

void tutorial_5::reset() {
    auto &tut = g_tutorials_flags.tutorial_5;
    tut.started = 0;
    tut.spacious_apartment = 0;
    tut.papyrus_made = 0;
    tut.bricks_bought = 0;
}

void tutorial5_handle_spacious_apartment(event_advance_day) {
    auto &tut = g_tutorials_flags.tutorial_5;
    if (tut.spacious_apartment) {
        return;
    }

    const int spacious_apartment_count = g_city.buildings.count_total(BUILDING_HOUSE_SPACIOUS_APARTMENT);
    const int spacious_apartment_built = g_scenario.vars.get_int("spacious_apartment_built");
    if (spacious_apartment_count < spacious_apartment_built) {
        return;
    }

    tut.spacious_apartment = true;
    events::unsubscribe(&tutorial5_handle_spacious_apartment);
    events::emit(event_building_menu_update{ tutorial_stage.tutorial_education });

    g_city.set_advisor_available(ADVISOR_EDUCATION, AVAILABLE);
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day(true);
    messages::popup("message_tutorial_education", 0, 0);
}

void tutorial5_handle_papyrus(event_warehouse_filled ev) {
    auto &tut = g_tutorials_flags.tutorial_5;
    if (tut.papyrus_made) {
        return;
    }

    const int papyrus_amount = g_scenario.vars.get_int("papyrus_stored", 100);
    if (g_city.resource.yards_stored(RESOURCE_PAPYRUS) < papyrus_amount) {
        return;
    }

    tut.papyrus_made = true;
    events::unsubscribe(&tutorial5_handle_papyrus);
    events::emit(event_building_menu_update{ tutorial_stage.tutorial_trading });

    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day(true);
    g_city.set_advisor_available(ADVISOR_TRADE, AVAILABLE);
    
    messages::popup("message_tutorial_trade_with_other_cities", 0, 0);
}

void tutorial5_handle_bricks(event_warehouse_filled ev) {
    auto &tut = g_tutorials_flags.tutorial_5;
    if (tut.bricks_bought) {
        return;
    }

    const int bricks_amount = g_scenario.vars.get_int("bricks_stored", 100);
    if (g_city.resource.yards_stored(RESOURCE_BRICKS) < bricks_amount) {
        return;
    }

    tut.bricks_bought = true;
    events::unsubscribe(&tutorial5_handle_bricks);
    events::emit(event_building_menu_update{ "tutorial_monuments" });
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day(true);
    messages::popup("message_tutorial_monuments", 0, 0);
}

bool tutorial5_is_success() {
    auto &tut = g_tutorials_flags.tutorial_5;
    const bool may_finish = (tut.spacious_apartment && tut.papyrus_made && tut.bricks_bought);
    const int victory_last_action_delay = g_scenario.vars.get_int("victory_last_action_delay", 3);
    const bool some_days_after_last_action = (game.simtime.absolute_day(true) - g_tutorials_flags.pharaoh.last_action) > victory_last_action_delay;
    return may_finish && some_days_after_last_action;
}

void tutorial_5::init() {
    auto &tut = g_tutorials_flags.tutorial_5;
    events::emit_if(tut.spacious_apartment, event_building_menu_update{ tutorial_stage.tutorial_education });
    g_city.set_advisor_available(ADVISOR_EDUCATION, tut.spacious_apartment ? AVAILABLE : NOT_AVAILABLE);

    events::subscribe_if(!tut.spacious_apartment, &tutorial5_handle_spacious_apartment);

    events::emit_if(tut.papyrus_made, event_building_menu_update{ tutorial_stage.tutorial_trading });
    g_city.set_advisor_available(ADVISOR_TRADE, tut.papyrus_made ? AVAILABLE : NOT_AVAILABLE);
    events::subscribe_if(!tut.papyrus_made, &tutorial5_handle_papyrus);

    events::emit_if(tut.bricks_bought, event_building_menu_update{ "tutorial_monuments" });
    events::subscribe_if(!tut.bricks_bought, &tutorial5_handle_bricks);

    g_city.victory_state.add_condition(&tutorial5_is_success);

    const auto advisors = { ADVISOR_LABOR, ADVISOR_IMPERIAL, ADVISOR_RATINGS, ADVISOR_POPULATION, ADVISOR_HEALTH, ADVISOR_ENTERTAINMENT, ADVISOR_RELIGION, ADVISOR_FINANCIAL, ADVISOR_CHIEF };
    for (auto a : advisors) {
        g_city.set_advisor_available(a, AVAILABLE);
    }
}

void tutorial_5::update_step(xstring s) {

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