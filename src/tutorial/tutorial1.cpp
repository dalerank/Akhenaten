#include "game/tutorial.h"

#include "city/city.h"
#include "game/game_events.h"
#include "game/game.h"
#include "city/city_building_menu_ctrl.h"
#include "building/building_granary.h"
#include "io/gamefiles/lang.h"
#include "city/city_message.h"

/** How Tutorial 1 works, from observing the OG game 
 * 1 - "Food or Famine" pop-up at the 150 citizen mark (unlocks buildings);
 * 2 - "Fire in the Village" pop-up: Hard and Very Hard, fire breaks in July. Normal breaks in Nov.
 * Very Easy takes more than 2 years (unlocks building).
 * 3 - "Water" pop-up triggers: Normal at 100 meat stored, Hard and Very H. at 400. (unlocks building); 
 * 4 - No need to see the "Fire in the Village" pop-up to complete the mission.
 * 5 - No damage risk (collapsed building), only fire.
 * 6 - The fire risk increasing in diff rates per difficulty is not a tutorial thing,
 * it's part of the difficulty system (played a random mission later in the game and it behaves the same).
 */

struct tutorial_1 : public tutorial_t {
    virtual int missionid() const override { return 1; }
    virtual void init() override;
    virtual void reset() override;
    virtual void update_step(xstring s) override;
    virtual xstring goal_text() override;
};

tutorial_1 g_tutorial_1;

void tutorial_handle_advance_day(event_advance_day ev) {
    // nothing special happens here
}

void tutorial1_popultion_cap(city_migration_t& migration) {
    auto &tut = g_tutorials_flags.tutorial_1;

    const int population_cap_firstfire = g_scenario.vars.get_int("population_cap_firstfire", 80);
    const bool tutorial_fire_handled = g_scenario.vars.get_bool("tutorial_fire_handled");
    const bool tutorial_collapsed_handle = g_scenario.vars.get_bool("tutorial_collapsed_handle");
    const int max_pop = (!tutorial_fire_handled || !tutorial_collapsed_handle) ? population_cap_firstfire : 0;
    migration.population_cap = max_pop;
}

void tutorial1_on_filled_granary(event_granary_resource_added ev) {
    auto &tut = g_tutorials_flags.tutorial_1;

    if (tut.gamemeat_stored) {
        return;
    }

    auto granary = building_get(ev.bid)->dcast_granary();
    const int meat_stored = granary ? granary->amount(RESOURCE_GAMEMEAT) : 0;

    if (meat_stored < g_scenario.vars.get_int("granary_meat_stored", 400)) {
        return;
    }

    events::unsubscribe(&tutorial1_on_filled_granary);
    events::emit(event_building_menu_update{ tutorial_stage.tutorial_water });
    g_scenario.vars.set_int("last_action", game.simtime.absolute_day(true));
    tut.gamemeat_stored = true;
    messages::popup("message_tutorial_clean_water", 0, 0);
}

void tutorial1_handle_building_create(event_building_create ev) {
    auto &tut = g_tutorials_flags.tutorial_1;
    if (tut.architector_built) {
        return;
    }

    events::unsubscribe(&tutorial1_handle_building_create);
    g_scenario.vars.set_int("last_action", game.simtime.absolute_day(true));
}

bool tutorial1_is_success() {
    const int victory_last_action_delay = g_scenario.vars.get_int("victory_last_action_delay", 3);
    const bool some_days_after_last_action = (game.simtime.absolute_day(true) - g_scenario.vars.get_int("last_action")) > victory_last_action_delay;
    return some_days_after_last_action;
}

void tutorial_1::init() {
    auto &tut = g_tutorials_flags.tutorial_1; 

    const bool architector_built = tut.architector_built;
    events::subscribe_if(!architector_built, &tutorial1_handle_building_create);

    const bool gamemeat_stored = tut.gamemeat_stored;
    events::emit_if(gamemeat_stored, event_building_menu_update{ tutorial_stage.tutorial_water });
    
    events::subscribe_if(!gamemeat_stored, &tutorial1_on_filled_granary);

    g_city.victory_state.add_condition(tutorial1_is_success);
    g_city.migration.add_condition(tutorial1_popultion_cap);

    events::subscribe(&tutorial_handle_advance_day);
}

void tutorial_1::reset() {
    auto &tut = g_tutorials_flags.tutorial_1;

    tut.gamemeat_stored = 0;
    tut.started = 0;
}

xstring tutorial_1::goal_text() {
    auto &tut = g_tutorials_flags.tutorial_1;

    if (!g_scenario.goal_tooltip.empty()) {
        return g_scenario.goal_tooltip;
    }
    
    if (!tut.gamemeat_stored)
        return lang_get_xstring(62, 19);

    return lang_get_xstring(62, 20);
}

void tutorial_1::update_step(xstring s) {
    auto &tut = g_tutorials_flags.tutorial_1;

    if (s == tutorial_stage.tutorial_water) {
        tut.gamemeat_stored = false;
        tutorial1_on_filled_granary({ 0 });
    }
}