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
#include "scenario/criteria.h"
#include "scenario/scenario_invasion.h"
#include "scenario/map.h"
#include "scenario/scenario.h"
#include "window/autoconfig_window.h"
#include "core/locale.h"
#include "core/string.h"
#include "game/game.h"
#include "game/mission.h"
#include "game/player.h"
#include "js/js_game.h"
#include <cmath>
#include <cstdio>

#define MAX_SCENARIOS 15

scenario_selection_info_js g_scenario_selection_info;

ANK_GLOBAL_OBJECT(g_scenario_selection_info, __scenario_selection_info, visible, is_open_play, climate_id, mapsize_id, invasion_id, culture, prosperity, monuments, kingdom, population, housing, house_level, has_culture, has_prosperity, has_monuments, has_kingdom, has_population, has_housing, time_kind, time_months, mon0, mon1, mon2, scores_or_goals, period_hover, main_bg_kind, campaign_first_mission)

window_scenario_selection g_window_scenario_selection;
window_scenario_selection_campaign g_window_scenario_selection_campaign;
window_scenario_selection_custom g_window_scenario_selection_custom;

ui::escrollable_list* window_scenario_selection::map_list_element() {
    return (*this)["scenario_map_list"].dcast_scrollable_list();
}

scrollable_list* window_scenario_selection::map_list() {
    ui::escrollable_list* sl = map_list_element();
    if (!sl) {
        return nullptr;
    }
    sl->ensure_panel();
    return sl->get_panel();
}

void window_scenario_selection::setup_dialog(e_map_selection_dialog_type dialog_type, int sub_dialog_selector) {
    dialog = dialog_type;
    campaign_sub_dialog = sub_dialog_selector;
    g_scenario_selection_info.scores_or_goals = 0;
    g_scenario.campaign_scenario_id = -1;

    ui::escrollable_list* sle = map_list_element();
    if (!sle) {
        return;
    }
    sle->ensure_panel();
    scrollable_list* panel = sle->get_panel();
    if (!panel) {
        return;
    }

    switch (dialog_type) {
    case MAP_SELECTION_CCK_LEGACY:
        g_scenario.set_mode(e_scenario_custom_map);
        panel->set_file_finder_usage(true);
        sle->change_file_path("Maps/", "map");
        break;
    case MAP_SELECTION_CAMPAIGN_SINGLE_LIST:
        g_scenario.set_mode(e_scenario_normal);
        panel->set_file_finder_usage(false);
        sle->clear();
        switch (campaign_sub_dialog) {
        case -1:
            break;
        default: {
            for (int i = 0; i < MAX_MANUAL_ENTRIES; ++i) {
                auto mission_data = get_campaign_mission_step_data(campaign_sub_dialog, i);
                if (mission_data != nullptr && mission_data->scenario_id != -1) {
                    char name_utf8[MAX_FILE_NAME] = {0};
                    if (mission_data && mission_data->map_name) {
                        const int row = panel->items_count();
                        encoding_to_utf8(mission_data->map_name, name_utf8, MAX_FILE_NAME, 0);
                        panel->add_entry(name_utf8, (uintptr_t)row);
                    } else {
                        logs::error("Could not initialize SDL: %s", SDL_GetError());
                    }
                }
            }
            break;
        }
        }
        break;
    default:
        break;
    }

    const bool show_list = (dialog == MAP_SELECTION_CCK_LEGACY || dialog == MAP_SELECTION_CAMPAIGN_SINGLE_LIST);
    (*this)["scenario_map_list"].set_enabled(show_list);

    const bool show_scores = dialog == MAP_SELECTION_CAMPAIGN_SINGLE_LIST && panel->get_selected_entry_idx() != -1;
    (*this)["btn_scores"].set_enabled(show_scores);
    (*this)["btn_goals"].set_enabled(show_scores);

    if (dialog == MAP_SELECTION_CCK_LEGACY) {
        g_scenario_selection_info.main_bg_kind = 1;
    } else if (dialog == MAP_SELECTION_CAMPAIGN_SINGLE_LIST) {
        g_scenario_selection_info.main_bg_kind = 2;
    } else {
        g_scenario_selection_info.main_bg_kind = 0;
    }

    if (dialog == MAP_SELECTION_CAMPAIGN_SINGLE_LIST) {
        g_scenario_selection_info.campaign_first_mission = get_first_mission_in_campaign(campaign_sub_dialog);
    } else {
        g_scenario_selection_info.campaign_first_mission = -1;
    }

    ui::dispatch_autoconfig_es_event(this, "main_bg", bvariant_map{});

    panel->set_onclick_entry([](int index, int p2) {
        (void)index;
        (void)p2;
        g_window_scenario_selection.update_widget_visibility_after_list_change();
    });
}

void window_scenario_selection::update_widget_visibility_after_list_change() {
    scrollable_list* panel = map_list();
    const bool show_scores = dialog == MAP_SELECTION_CAMPAIGN_SINGLE_LIST && panel && panel->get_selected_entry_idx() != -1;
    (*this)["btn_scores"].set_enabled(show_scores);
    (*this)["btn_goals"].set_enabled(show_scores);
}

void __game_ui_dispatch_autoconfig_event(pcstr section, pcstr sub_event) {
    autoconfig_window* w = autoconfig_window::find(section);
    if (!w || !sub_event) {
        return;
    }
    ui::dispatch_autoconfig_es_event(w, xstring(sub_event), bvariant_map{});
}
ANK_FUNCTION_2(__game_ui_dispatch_autoconfig_event)

int __game_window_scenario_selection_has_map_selection() {
    scrollable_list* panel = g_window_scenario_selection.map_list();
    return panel && panel->get_selected_entry_idx() != -1 ? 1 : 0;
}
ANK_FUNCTION(__game_window_scenario_selection_has_map_selection)

int __game_window_scenario_selection_custom_has_map_selection() {
    scrollable_list* panel = g_window_scenario_selection_custom.map_list();
    return panel && panel->get_selected_entry_idx() != -1 ? 1 : 0;
}
ANK_FUNCTION(__game_window_scenario_selection_custom_has_map_selection)

int __game_scenario_selection_is_campaign_mission_pick() {
    return g_window_scenario_selection.dialog == MAP_SELECTION_CAMPAIGN_SINGLE_LIST ? 1 : 0;
}
ANK_FUNCTION(__game_scenario_selection_is_campaign_mission_pick)

int __game_scenario_selection_campaign_sub_dialog() {
    return g_window_scenario_selection.campaign_sub_dialog;
}
ANK_FUNCTION(__game_scenario_selection_campaign_sub_dialog)

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

xstring __game_scenario_selection_custom_selected_map_basename() {
    scrollable_list* panel = g_window_scenario_selection_custom.map_list();
    if (!panel || panel->get_selected_entry_idx() == -1) {
        return "";
    }
    return panel->get_selected_entry_text(FILE_NO_EXT).c_str();
}
ANK_FUNCTION(__game_scenario_selection_custom_selected_map_basename)

int __game_locale_year_before_ad() {
    return locale_year_before_ad() ? 1 : 0;
}
ANK_FUNCTION(__game_locale_year_before_ad)

int __game_scenario_property_climate() {
    return scenario_property_climate();
}
ANK_FUNCTION(__game_scenario_property_climate)

int __game_scenario_map_size() {
    return scenario_map_size();
}
ANK_FUNCTION(__game_scenario_map_size)

int __game_scenario_invasion_count() {
    return scenario_invasion_count();
}
ANK_FUNCTION(__game_scenario_invasion_count)

int __game_winning_culture() {
    return winning_culture();
}
ANK_FUNCTION(__game_winning_culture)
int __game_winning_prosperity() {
    return winning_prosperity();
}
ANK_FUNCTION(__game_winning_prosperity)
int __game_winning_monuments() {
    return winning_monuments();
}
ANK_FUNCTION(__game_winning_monuments)
int __game_winning_kingdom() {
    return winning_kingdom();
}
ANK_FUNCTION(__game_winning_kingdom)
int __game_winning_population() {
    return winning_population();
}
ANK_FUNCTION(__game_winning_population)
int __game_winning_housing() {
    return winning_housing();
}
ANK_FUNCTION(__game_winning_housing)
int __game_winning_houselevel() {
    return winning_houselevel();
}
ANK_FUNCTION(__game_winning_houselevel)

int __game_scenario_criteria_survival_enabled() {
    return scenario_criteria_survival_enabled();
}
ANK_FUNCTION(__game_scenario_criteria_survival_enabled)
int __game_scenario_criteria_survival_years() {
    return scenario_criteria_survival_years();
}
ANK_FUNCTION(__game_scenario_criteria_survival_years)
int __game_scenario_criteria_time_limit_enabled() {
    return scenario_criteria_time_limit_enabled();
}
ANK_FUNCTION(__game_scenario_criteria_time_limit_enabled)
int __game_scenario_criteria_time_limit_years() {
    return scenario_criteria_time_limit_years();
}
ANK_FUNCTION(__game_scenario_criteria_time_limit_years)

int __game_scenario_property_monument_slot(int field) {
    return scenario_property_monument(field);
}
ANK_FUNCTION_1(__game_scenario_property_monument_slot)

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

ui::escrollable_list* window_scenario_selection_custom::map_list_element() {
    return (*this)["scenario_map_list"].dcast_scrollable_list();
}

scrollable_list* window_scenario_selection_custom::map_list() {
    ui::escrollable_list* sl = map_list_element();
    if (!sl) {
        return nullptr;
    }
    sl->ensure_panel();
    return sl->get_panel();
}

void window_scenario_selection_custom::update_widget_visibility_after_list_change() {}

void window_scenario_selection_show(int dialog_type) {
    const auto t = (e_map_selection_dialog_type)dialog_type;
    if (t == MAP_SELECTION_CAMPAIGN) {
        g_scenario_selection_info.period_hover = -1;
        autoconfig_window::show("window_scenario_selection_campaign");
    } else if (t == MAP_SELECTION_CUSTOM) {
        g_scenario.set_mode(e_scenario_custom_map);
        autoconfig_window::show("window_scenario_selection_custom");
    } else {
        g_window_scenario_selection.setup_dialog(t, -1);
        autoconfig_window::show("window_scenario_selection");
    }
}
ANK_FUNCTION_1(window_scenario_selection_show)

void window_scenario_selection_select_campaign(int campaign_index) {
    if (window_get_id() == "window_scenario_selection" || window_get_id() == "window_scenario_selection_custom") {
        window_go_back();
    }
    g_window_scenario_selection.setup_dialog(MAP_SELECTION_CAMPAIGN_SINGLE_LIST, campaign_index);
    autoconfig_window::show("window_scenario_selection");
}
ANK_FUNCTION_1(window_scenario_selection_select_campaign)
