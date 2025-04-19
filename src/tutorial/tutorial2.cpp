#include "game/tutorial.h"

#include "building/building_menu.h"
#include "city/city_message.h"
#include "io/gamefiles/lang.h"
#include "city/city.h"
#include "city/city_events.h"
#include "city/finance.h"
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
    if (g_tutorials_flags.tutorial_2.temples_built) {
        return;
    }

    building *b = building_get(ev.bid);
    if (!building_is_temple(b->type)) {
        return;
    }

    events::unsubscribe(&tutorial_2_on_build_temple);
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day(true);
    g_tutorials_flags.tutorial_2.temples_built = true;
    building_menu_update(tutorial_stage.tutorial_entertainment);
    events::emit(event_message{ true, MESSAGE_TUTORIAL_ENTERTAINMENT, 0, 0 });
}

void tutorial_2_on_gold_extracted(event_gold_extract ev) {
    if (g_tutorials_flags.tutorial_2.gold_mined_500) {
        return;
    }

    if (g_city.finance.this_year.income.gold_extracted < 500) {
        return;
    }

    events::unsubscribe(&tutorial_2_on_gold_extracted);
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day(true);
    g_tutorials_flags.tutorial_2.gold_mined_500 = true;
    building_menu_update(tutorial_stage.tutorial_gods);
    events::emit(event_message{ true, MESSAGE_TUTORIAL_GODS_OF_EGYPT, 0, 0 });
}

bool tutorial2_is_success() {
    auto &tut = g_tutorials_flags.tutorial_2;
    const bool may_finish = (tut.gold_mined_500 && tut.temples_built);
    const bool some_days_after_last_action = (game.simtime.absolute_day(true) - g_tutorials_flags.pharaoh.last_action) > 3;
    return may_finish && some_days_after_last_action;
}

void tutorial2_population_cap(city_migration_t& migration) {
    const int max_pops = (!g_tutorials_flags.tutorial_2.granary_built) ? 150 : 0;
    migration.population_cap = max_pops;
}

void tutorial_2::init() {
    if (g_tutorials_flags.tutorial_2.gold_mined_500) building_menu_update(tutorial_stage.tutorial_gods);
    else events::subscribe(&tutorial_2_on_gold_extracted);

    if (g_tutorials_flags.tutorial_2.temples_built) building_menu_update(tutorial_stage.tutorial_entertainment);
    else events::subscribe(&tutorial_2_on_build_temple);

    g_city.victory_state.add_condition(tutorial2_is_success);
    g_city.migration.add_condition(tutorial2_population_cap);

    const auto advisors = { ADVISOR_ENTERTAINMENT, ADVISOR_RELIGION };
    for (auto a: advisors) {
        g_city.set_advisor_available(a, AVAILABLE);
    }
}

xstring tutorial_2::goal_text() {
    if (!g_tutorials_flags.tutorial_2.gold_mined_500) {
        return lang_get_xstring(62, 24);
    } 
    
    if (!g_tutorials_flags.tutorial_2.temples_built) {
        return lang_get_xstring(62, 23);
    } 
    
    return lang_get_xstring(62, 22);
}

void tutorial_2::update_step(xstring s) {
    if (s == tutorial_stage.tutorial_gods) {
        building_menu_update(s);
        events::emit(event_message{ true, MESSAGE_TUTORIAL_GODS_OF_EGYPT, 0, 0 });
    } else if (s == tutorial_stage.tutorial_entertainment) {
        building_menu_update(s);
        events::emit(event_message{ true, MESSAGE_TUTORIAL_ENTERTAINMENT, 0, 0 });
    }
}

void tutorial_2::reset() {
    g_tutorials_flags.tutorial_2.started = 0;
    g_tutorials_flags.tutorial_2.gold_mined_500 = 0;
    g_tutorials_flags.tutorial_2.temples_built = 0;
}