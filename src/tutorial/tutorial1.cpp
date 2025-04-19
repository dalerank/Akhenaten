#include "game/tutorial.h"

#include "city/city.h"
#include "city/city_events.h"
#include "game/game.h"
#include "building/building_menu.h"
#include "building/building_granary.h"
#include "io/gamefiles/lang.h"
#include "city/city_message.h"

struct tutorial_1 : public tutorial_t {
    virtual int missionid() const override { return 1; }
    virtual void init() override;
    virtual void reset() override;
    virtual void update_step(xstring s) override;
    virtual xstring goal_text() override;
};

tutorial_1 g_tutorial_1;

void tutorial1_handle_fire(event_fire_damage) {
    if (g_tutorials_flags.tutorial_1.fire) {
        return;
    }

    events::unsubscribe(&tutorial1_handle_fire);
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day(true);
    g_tutorials_flags.tutorial_1.fire = true;
    g_scenario.extra_damage.clear();

    building_menu_update(tutorial_stage.tutorial_fire);
    messages::popup(MESSAGE_TUTORIAL_FIRE_IN_THE_VILLAGE, 0, 0);
}

void tutorial1_popultion_cap(city_migration_t& migration) {
    const int max_pop = (!g_tutorials_flags.tutorial_1.fire || !g_tutorials_flags.tutorial_1.collapse) ? 80 : 0;
    migration.population_cap = max_pop;
}

void tutorial1_handle_population_150(event_population_changed ev) {
    if (g_tutorials_flags.tutorial_1.population_150_reached || ev.value < 150) {
        return;
    }

    events::unsubscribe(&tutorial1_handle_population_150);
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day(true);
    g_tutorials_flags.tutorial_1.population_150_reached = true;
    building_menu_update(tutorial_stage.tutorial_food);
    messages::popup(MESSAGE_TUTORIAL_FOOD_OR_FAMINE, 0, 0);
}

void tutorial1_handle_collapse(event_collase_damage) {
    if (g_tutorials_flags.tutorial_1.collapse) {
        return;
    }

    events::unsubscribe(&tutorial1_handle_collapse);
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day(true);
    g_tutorials_flags.tutorial_1.collapse = true;
    building_menu_update(tutorial_stage.tutorial_collapse);
    messages::popup(MESSAGE_TUTORIAL_COLLAPSED_BUILDING, 0, 0);
}

void tutorial1_on_filled_granary(event_granary_filled ev) {
    if (g_tutorials_flags.tutorial_1.gamemeat_400_stored) {
        return;
    }

    if (ev.amount <= 400) {
        return;
    }

    events::unsubscribe(&tutorial1_on_filled_granary);
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day(true);
    g_tutorials_flags.tutorial_1.gamemeat_400_stored = true;
    building_menu_update(tutorial_stage.tutorial_water);
    messages::popup(MESSAGE_TUTORIAL_CLEAN_WATER, 0, 0);
}

void tutorial1_handle_building_create(event_building_create ev) {
    if (g_tutorials_flags.tutorial_1.architector_built) {
        return;
    }

    events::unsubscribe(&tutorial1_handle_building_create);
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day(true);
}

bool tutorial1_is_success() {
    auto &tut = g_tutorials_flags.tutorial_1;
    const bool may_finish = (tut.fire && tut.collapse && tut.population_150_reached && tut.gamemeat_400_stored);
    const bool some_days_after_last_action = (game.simtime.absolute_day(true) - g_tutorials_flags.pharaoh.last_action) > 3;
    return may_finish && some_days_after_last_action;
}

void tutorial_1::init() {
    if (g_tutorials_flags.tutorial_1.fire) building_menu_update(tutorial_stage.tutorial_fire);
    else events::subscribe(&tutorial1_handle_fire);

    if (g_tutorials_flags.tutorial_1.population_150_reached)  building_menu_update(tutorial_stage.tutorial_food);
    else events::subscribe(&tutorial1_handle_population_150);

    if (!g_tutorials_flags.tutorial_1.architector_built) {
        events::subscribe(&tutorial1_handle_building_create);
    }

    if (g_tutorials_flags.tutorial_1.collapse) building_menu_update(tutorial_stage.tutorial_collapse);
    else events::subscribe(&tutorial1_handle_collapse);

    if (g_tutorials_flags.tutorial_1.gamemeat_400_stored) building_menu_update(tutorial_stage.tutorial_water);
    else events::subscribe(&tutorial1_on_filled_granary);

    g_city.victory_state.add_condition(tutorial1_is_success);
    g_city.migration.add_condition(tutorial1_popultion_cap);
}

void tutorial_1::reset() {
    g_tutorials_flags.tutorial_1.fire = 0;
    g_tutorials_flags.tutorial_1.population_150_reached = 0;
    g_tutorials_flags.tutorial_1.gamemeat_400_stored = 0;
    g_tutorials_flags.tutorial_1.collapse = 0;
    g_tutorials_flags.tutorial_1.started = 0;
}

xstring tutorial_1::goal_text() {
    if (!g_tutorials_flags.tutorial_1.population_150_reached)
        return lang_get_xstring(62, 21);
    
    if (!g_tutorials_flags.tutorial_1.gamemeat_400_stored)
        return lang_get_xstring(62, 19);

    return lang_get_xstring(62, 20);
}

void tutorial_1::update_step(xstring s) {
    if (s == tutorial_stage.tutorial_fire) {
        g_tutorials_flags.tutorial_1.fire = false;
        tutorial1_handle_fire({ 0 });
    } else if (s == tutorial_stage.tutorial_collapse) {
        g_tutorials_flags.tutorial_1.collapse = false;
        tutorial1_handle_collapse({ 0 });
    } else if (s == tutorial_stage.tutorial_food) {
        g_tutorials_flags.tutorial_1.population_150_reached = false;
        tutorial1_handle_population_150({ 0 });
    } else if (s == tutorial_stage.tutorial_water) {
        g_tutorials_flags.tutorial_1.gamemeat_400_stored = false;
        tutorial1_on_filled_granary({ 0 });
    }
}