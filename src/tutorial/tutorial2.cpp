#include "game/tutorial.h"

#include "city/city_building_menu_ctrl.h"
#include "city/city_message.h"
#include "io/gamefiles/lang.h"
#include "city/city.h"
#include "game/game_events.h"
#include "city/city_finance.h"
#include "game/game.h"

struct tutorial_2 : public tutorial_t {
    virtual int missionid() const override { return 2; }
    virtual void init() override;
    virtual void reset() override;
    virtual void update_step(xstring s) override;
    virtual xstring goal_text() override;
};

tutorial_2 g_tutorial_2;

void tutorial_2_on_build_temple(event_building_create ev) {
    auto &tut = g_tutorials_flags.tutorial_2;

    if (tut.temples_built) {
        return;
    }

    building *b = building_get(ev.bid);
    if (!building_is_temple(b->type)) {
        return;
    }

    events::unsubscribe(&tutorial_2_on_build_temple);
    events::emit(event_building_menu_update{ tutorial_stage.tutorial_entertainment });
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day(true);
    tut.temples_built = true;
    events::emit(event_message{ true, MESSAGE_TUTORIAL_ENTERTAINMENT, 0, 0 });
}

void tutorial_2_on_update_day(event_advance_day ev) {
    auto &tut = g_tutorials_flags.tutorial_2;

    if (tut.gold_mined) {
        return;
    }

    if (g_city.finance.this_year.income.gold_delivered < g_scenario.vars.get_int("gold_mined", 500)) {
        return;
    }

    events::unsubscribe(&tutorial_2_on_update_day);
    events::emit(event_building_menu_update{ tutorial_stage.tutorial_gods });
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day(true);
    tut.gold_mined = true;
    events::emit(event_message{ true, MESSAGE_TUTORIAL_GODS_OF_EGYPT, 0, 0 });
}

bool tutorial2_is_success() {
    auto &tut = g_tutorials_flags.tutorial_2;

    const bool may_finish = (tut.gold_mined && tut.temples_built);
    const int victory_last_action_delay = g_scenario.vars.get_int("victory_last_action_delay", 3);
    const bool some_days_after_last_action = (game.simtime.absolute_day(true) - g_tutorials_flags.pharaoh.last_action) > victory_last_action_delay;
    return may_finish && some_days_after_last_action;
}

void tutorial2_population_cap(city_migration_t& migration) {
    auto &tut = g_tutorials_flags.tutorial_2;

    const int nogranary_populcation_cap = g_scenario.vars.get_int("nogranary_populcation_cap", 150);
    const bool granary_built = g_city.buildings.count_active(BUILDING_GRANARY) > 0;
    const int max_pops = granary_built ? 0 : nogranary_populcation_cap;
    migration.population_cap = max_pops;
}

void tutorial_2::init() {
    auto &tut = g_tutorials_flags.tutorial_2;

    const bool gold_mined_500 = tut.gold_mined;
    events::emit_if(gold_mined_500, event_building_menu_update{ tutorial_stage.tutorial_gods });
    events::subscribe_if(!gold_mined_500, &tutorial_2_on_update_day);

    const bool temples_built = tut.temples_built;
    events::emit_if(temples_built, event_building_menu_update{ tutorial_stage.tutorial_entertainment });
    events::subscribe_if(!temples_built, &tutorial_2_on_build_temple);

    g_city.victory_state.add_condition(tutorial2_is_success);
    g_city.migration.add_condition(tutorial2_population_cap);

    const auto advisors = { ADVISOR_ENTERTAINMENT, ADVISOR_RELIGION };
    for (auto a: advisors) {
        g_city.set_advisor_available(a, AVAILABLE);
    }
}

xstring tutorial_2::goal_text() {
    auto &tut = g_tutorials_flags.tutorial_2;

    if (!tut.gold_mined) {
        return lang_get_xstring(62, 24);
    } 
    
    if (!tut.temples_built) {
        return lang_get_xstring(62, 23);
    } 
    
    return lang_get_xstring(62, 22);
}

void tutorial_2::update_step(xstring s) {
    if (s == tutorial_stage.tutorial_gods) {
        events::emit(event_building_menu_update{ s });
        events::emit(event_message{ true, MESSAGE_TUTORIAL_GODS_OF_EGYPT, 0, 0 });
    } else if (s == tutorial_stage.tutorial_entertainment) {
        events::emit(event_building_menu_update{ s });
        events::emit(event_message{ true, MESSAGE_TUTORIAL_ENTERTAINMENT, 0, 0 });
    }
}

void tutorial_2::reset() {
    auto &tut = g_tutorials_flags.tutorial_2;

    tut.started = 0;
    tut.gold_mined = 0;
    tut.temples_built = 0;
}