#include "core/profiler.h"
#include "core/tokenum.h"
#include "game/game.h"
#include "game/mission.h"
#include "js/js_game.h"
#include "scenario/scenario.h"
#include "scenario/scenario_invasion.h"

enum e_campaign_selection_tab {
    CAMPAIGN_TAB_CAMPAIGNS = 0,
    CAMPAIGN_TAB_INDIVIDUAL = 1,
    CAMPAIGN_TAB_MAX
};
using e_campaign_selection_tab_tokens_t = token_holder<e_campaign_selection_tab, CAMPAIGN_TAB_CAMPAIGNS, CAMPAIGN_TAB_MAX>;
const e_campaign_selection_tab_tokens_t ANK_CONFIG_ENUM(e_campaign_selection_tab_tokens);

int __game_get_first_mission_in_campaign(int campaign_id) {
    return get_first_mission_in_campaign(campaign_id);
}
ANK_FUNCTION_1(__game_get_first_mission_in_campaign)

int __game_campaign_count() {
    return game_campaign_count();
}
ANK_FUNCTION(__game_campaign_count)

int __game_campaign_has_mission_step(int campaign_id, int step_index) {
    return get_campaign_mission_step_data(campaign_id, step_index) ? 1 : 0;
}
ANK_FUNCTION_2(__game_campaign_has_mission_step)

// Raw scenario_id for a campaign step. Missing step → -1. A choicescreen placeholder
// also stores scenario_id=-1 — callers must use has_mission_step and continue, not break
// (OG free_play skips invalid links and keeps walking the period).
int __game_campaign_mission_step_scenario_id(int campaign_id, int step_index) {
    const mission_step_t* d = get_campaign_mission_step_data(campaign_id, step_index);
    if (!d) {
        return -1;
    }
    return d->scenario_id;
}
ANK_FUNCTION_2(__game_campaign_mission_step_scenario_id)

int __game_scenario_invasion_count() {
    return scenario_invasion_count();
}
ANK_FUNCTION(__game_scenario_invasion_count)

int __game_mission_scenario_beaten(int scenario_id) {
    return game_scenario_beaten(scenario_id) ? 1 : 0;
}
ANK_FUNCTION_1(__game_mission_scenario_beaten)

