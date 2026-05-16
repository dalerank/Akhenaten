#include "scenario_selection.h"

#include "core/encoding.h"
#include "core/log.h"
#include "core/profiler.h"
#include "graphics/elements/ui.h"
#include "graphics/window.h"
#include "input/input.h"
#include "content/vfs.h"
#include "io/gamestate/boilerplate.h"
#include "message_dialog.h"
#include "scenario/scenario_invasion.h"
#include "scenario/scenario.h"
#include "window/autoconfig_window.h"
#include "core/string.h"
#include "game/game.h"
#include "game/mission.h"
#include "game/player.h"
#include "js/js_game.h"
#include <cmath>
#include <cstdio>

#define MAX_SCENARIOS 15

scenario_selection_info_js g_scenario_selection_info;

ANK_GLOBAL_OBJECT(g_scenario_selection_info, __scenario_selection_info, dialog, visible, is_open_play, climate_id, mapsize_id, invasion_id, culture, prosperity, monuments, kingdom, population, housing, house_level, has_culture, has_prosperity, has_monuments, has_kingdom, has_population, has_housing, time_kind, time_months, mon0, mon1, mon2, scores_or_goals, period_hover, main_bg_kind, campaign_first_mission, campaign_sub_dialog)

window_scenario_selection g_window_scenario_selection;
window_scenario_selection_campaign g_window_scenario_selection_campaign;
window_scenario_selection_custom g_window_scenario_selection_custom;

int __game_get_first_mission_in_campaign(int campaign_id) {
    return get_first_mission_in_campaign(campaign_id);
}
ANK_FUNCTION_1(__game_get_first_mission_in_campaign)

int __game_campaign_mission_step_scenario_id(int campaign_id, int step_index) {
    const mission_step_t* d = get_campaign_mission_step_data(campaign_id, step_index);
    if (!d || d->scenario_id < 0) {
        return -1;
    }
    return d->scenario_id;
}
ANK_FUNCTION_2(__game_campaign_mission_step_scenario_id)

xstring __game_campaign_mission_step_map_name_utf8(int campaign_id, int step_index) {
    const mission_step_t* mission_data = get_campaign_mission_step_data(campaign_id, step_index);
    if (!mission_data || mission_data->scenario_id < 0 || !mission_data->map_name) {
        return xstring();
    }
    char name_utf8[MAX_FILE_NAME] = {0};
    encoding_to_utf8(mission_data->map_name, name_utf8, MAX_FILE_NAME, 0);
    return xstring(name_utf8);
}
ANK_FUNCTION_2(__game_campaign_mission_step_map_name_utf8)

xstring __game_scenario_selection_mission_title_trimmed() {
    const int sid = g_scenario.campaign_scenario_id;
    bstring<300> name;
    string_copy(game_mission_get_name(sid), name, 300);
    const int i = index_of_string(name.c_str(), string_from_ascii("("), 300);
    if (i > 0) {
        name[i - 1] = '\0';
    }
    char utf8[600];
    encoding_to_utf8((const uint8_t*)name.c_str(), utf8, sizeof(utf8), 0);
    return utf8;
}
ANK_FUNCTION(__game_scenario_selection_mission_title_trimmed)

xstring __game_scenario_subtitle_display_utf8() {
    char utf8[MAX_FILE_NAME * 4];
    encoding_to_utf8(scenario_subtitle(), utf8, sizeof(utf8), 0);
    return utf8;
}
ANK_FUNCTION(__game_scenario_subtitle_display_utf8)

int __game_scenario_invasion_count() {
    return scenario_invasion_count();
}
ANK_FUNCTION(__game_scenario_invasion_count)

int __game_mission_scenario_beaten(int scenario_id) {
    return game_scenario_beaten(scenario_id) ? 1 : 0;
}
ANK_FUNCTION_1(__game_mission_scenario_beaten)

int __game_player_scenario_record_completion_months(int scenario_id) {
    return (int)player_get_scenario_record(scenario_id)->completion_months;
}
ANK_FUNCTION_1(__game_player_scenario_record_completion_months)
int __game_player_scenario_record_final_population(int scenario_id) {
    return (int)player_get_scenario_record(scenario_id)->final_population;
}
ANK_FUNCTION_1(__game_player_scenario_record_final_population)
int __game_player_scenario_record_final_funds(int scenario_id) {
    return (int)player_get_scenario_record(scenario_id)->final_funds;
}
ANK_FUNCTION_1(__game_player_scenario_record_final_funds)
int __game_player_scenario_record_rating_culture(int scenario_id) {
    return (int)player_get_scenario_record(scenario_id)->rating_culture;
}
ANK_FUNCTION_1(__game_player_scenario_record_rating_culture)
int __game_player_scenario_record_rating_prosperity(int scenario_id) {
    return (int)player_get_scenario_record(scenario_id)->rating_prosperity;
}
ANK_FUNCTION_1(__game_player_scenario_record_rating_prosperity)
int __game_player_scenario_record_rating_kingdom(int scenario_id) {
    return (int)player_get_scenario_record(scenario_id)->rating_kingdom;
}
ANK_FUNCTION_1(__game_player_scenario_record_rating_kingdom)
int __game_player_scenario_record_difficulty(int scenario_id) {
    return (int)player_get_scenario_record(scenario_id)->difficulty;
}
ANK_FUNCTION_1(__game_player_scenario_record_difficulty)
int __game_player_scenario_record_score(int scenario_id) {
    return (int)player_get_scenario_record(scenario_id)->score;
}
ANK_FUNCTION_1(__game_player_scenario_record_score)
