#include "game/tutorial.h"

#include "city/city_building_menu_ctrl.h"
#include "city/city_message.h"
#include "building/building_storage_yard.h"
#include "city/city.h"
#include "game/game_events.h"
#include "io/gamefiles/lang.h"
#include "game/game.h"

struct tutorial_4 : public tutorial_t {
    virtual int missionid() const override { return 4; }
    virtual void init() override;
    virtual void reset() override;
    virtual void update_step(xstring s) override {}
    virtual xstring goal_text() override;
};

tutorial_4 g_tutorial_4;

void tutorial_4::reset() {
    auto& tut = g_tutorials_flags.tutorial_4;
    tut.started = 0;
    tut.beer_made = 0;
    tut.tax_collector_built = 0;
}

xstring tutorial_4::goal_text() {
    auto& tut = g_tutorials_flags.tutorial_4;
    if (!tut.beer_made) {
        return lang_get_xstring(62, 33);
    }

    if (!tut.tax_collector_built) {
        return "#build_tax_collector";
    }

    return "#reach_modest_houses_number";
}

void tutorial4_warehouse_beer_check(event_warehouse_filled ev) {
    auto& tut = g_tutorials_flags.tutorial_4;
    if (tut.beer_made) {
        return;
    }

    const int beer_amount = g_scenario.vars.get_int("beer_stored", 300);
    if (g_city.resource.yards_stored(RESOURCE_BEER) < beer_amount) {
        return;
    }

    tut.beer_made = true;
    events::unsubscribe(&tutorial4_warehouse_beer_check);
    events::emit(event_building_menu_update{ tutorial_stage.tutorial_finance });

    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day(true);
    messages::popup("message_tutorial_finances", 0, 0);
}

bool tutorial4_is_success() {
    auto &tut = g_tutorials_flags.tutorial_4;
    const bool may_finish = (tut.beer_made && tut.tax_collector_built);
    const int victory_last_action_delay = g_scenario.vars.get_int("victory_last_action_delay", 3);
    const bool some_days_after_last_action = (game.simtime.absolute_day(true) - g_tutorials_flags.pharaoh.last_action) > victory_last_action_delay;
    return may_finish && some_days_after_last_action;
}

void tutorial_4_on_build_tax_collector(event_building_create ev) {
    auto& tut = g_tutorials_flags.tutorial_4;
    if (tut.tax_collector_built) {
        return;
    }

    building *b = building_get(ev.bid);
    if (b->type != BUILDING_TAX_COLLECTOR) {
        return;
    }

    events::unsubscribe(&tutorial_4_on_build_tax_collector);
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day(true);
    tut.tax_collector_built = true;
}
    
void tutorial_4::init() {
    auto& tut = g_tutorials_flags.tutorial_4;
    events::emit_if(tut.beer_made, event_building_menu_update{ tutorial_stage.tutorial_finance });

    events::subscribe_if(!tut.beer_made , &tutorial4_warehouse_beer_check);
    events::subscribe_if(!tut.tax_collector_built , &tutorial_4_on_build_tax_collector);
    
    g_city.victory_state.add_condition(&tutorial4_is_success);

    const auto advisors = { ADVISOR_LABOR, ADVISOR_ENTERTAINMENT, ADVISOR_RELIGION, ADVISOR_FINANCIAL };
    for (auto a : advisors) {
        g_city.set_advisor_available(a, AVAILABLE);
    }
}