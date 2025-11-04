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
};

tutorial_1 g_tutorial_1;

bool tutorial1_is_success() {
    const int victory_last_action_delay = g_scenario.vars.get_int("victory_last_action_delay", 3);
    const bool some_days_after_last_action = (game.simtime.absolute_day(true) - g_scenario.vars.get_int("last_action")) > victory_last_action_delay;
    return some_days_after_last_action;
}

void tutorial_1::init() {
    auto &tut = g_tutorials_flags.tutorial_1; 

    g_city.victory_state.add_condition(tutorial1_is_success);
}