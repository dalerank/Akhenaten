#include "scenario_selection.h"

#include "core/encoding.h"
#include "core/log.h"
#include "core/profiler.h"
#include "graphics/graphics.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/ui.h"
#include "graphics/image_groups.h"
#include "graphics/screen.h"
#include "graphics/text.h"
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
#include "game/game.h"
#include "js/js_game.h"

#include "dev/debug.h"
#include "game/mission.h"
#include "io/manager.h"
#include "game/player.h"
#include <cmath>
#include <cstdio>

#define MAX_SCENARIOS 15

/** Must match scenario selection window `pos` in ui_scenario_selection*.js (1024x768). */
static constexpr int SCENARIO_SELECTION_DIALOG_W = 1024;
static constexpr int SCENARIO_SELECTION_DIALOG_H = 768;

scenario_selection_info_js g_scenario_selection_info;

ANK_GLOBAL_OBJECT(g_scenario_selection_info, __scenario_selection_info, visible, is_open_play, climate_id, mapsize_id, invasion_id, culture, prosperity, monuments, kingdom, population, housing, house_level, has_culture, has_prosperity, has_monuments, has_kingdom, has_population, has_housing, time_kind, time_months, mon0, mon1, mon2, scores_or_goals, period_hover)

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
                        encoding_to_utf8(mission_data->map_name, name_utf8, MAX_FILE_NAME, 0);
                        panel->add_entry(name_utf8);
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

    (*this)["img_cck"].set_enabled(dialog == MAP_SELECTION_CCK_LEGACY);
    (*this)["img_history"].set_enabled(dialog == MAP_SELECTION_CAMPAIGN_SINGLE_LIST);

    sle->onclick_item([](int index, int p2) { g_window_scenario_selection.on_map_list_click(index, p2); });
    panel->set_onclick_entry([](int index, int p2) { g_window_scenario_selection.on_map_list_click(index, p2); });
}

void window_scenario_selection::on_map_list_click(int index, int param2) {
    (void)param2;
    scrollable_list* panel = map_list();
    if (!panel || index < 0 || index >= panel->items_count()) {
        return;
    }
    switch (dialog) {
    case MAP_SELECTION_CAMPAIGN_SINGLE_LIST:
        GamestateIO::load_mission(get_first_mission_in_campaign(campaign_sub_dialog) + panel->get_selected_entry_idx(), false);
        break;
    default:
        break;
    }
    update_widget_visibility_after_list_change();
}

void window_scenario_selection::update_widget_visibility_after_list_change() {
    scrollable_list* panel = map_list();
    const bool show_scores = dialog == MAP_SELECTION_CAMPAIGN_SINGLE_LIST && panel && panel->get_selected_entry_idx() != -1;
    (*this)["btn_scores"].set_enabled(show_scores);
    (*this)["btn_goals"].set_enabled(show_scores);
}

void window_scenario_selection::dispatch_scenario_info_script() {
    scenario_selection_info_js& s = g_scenario_selection_info;
    scrollable_list* panel = map_list();
    const bool have_sel = panel && panel->get_selected_entry_idx() != -1;
    const bool want_goals = (dialog == MAP_SELECTION_CAMPAIGN_SINGLE_LIST && g_scenario_selection_info.scores_or_goals == 1);
    if (!have_sel || !want_goals) {
        s.visible = 0;
    } else {
        s.visible = 1;
        s.is_open_play = g_scenario.is_open_play ? 1 : 0;
        s.climate_id = 77 + scenario_property_climate();
        s.mapsize_id = 121 + (int)fmin(4, fmax(0, scenario_map_size() - 50) / 30);
        s.invasion_id = 112 + scenario_invasion_count() / 2;
        s.culture = winning_culture();
        s.prosperity = winning_prosperity();
        s.monuments = winning_monuments();
        s.kingdom = winning_kingdom();
        s.population = winning_population();
        s.housing = winning_housing();
        s.house_level = winning_houselevel();
        s.has_culture = (winning_culture() > 0) ? 1 : 0;
        s.has_prosperity = (winning_prosperity() > 0) ? 1 : 0;
        s.has_monuments = (winning_monuments() > 0) ? 1 : 0;
        s.has_kingdom = (winning_kingdom() > 0) ? 1 : 0;
        s.has_population = (winning_population() > 0) ? 1 : 0;
        s.has_housing = (winning_housing() > 0) ? 1 : 0;
        if (scenario_criteria_survival_enabled()) {
            s.time_kind = 1;
            s.time_months = scenario_criteria_survival_years() * 12;
        } else if (scenario_criteria_time_limit_enabled()) {
            s.time_kind = 2;
            s.time_months = scenario_criteria_time_limit_years() * 12;
        } else {
            s.time_kind = 0;
            s.time_months = 0;
        }
        s.mon0 = scenario_property_monument(0);
        s.mon1 = scenario_property_monument(1);
        s.mon2 = scenario_property_monument(2);
    }

    ui::dispatch_autoconfig_es_event(this, "scenario_info", bvariant_map{});
}

#define HEADER_Y 28
#define SUBTITLE_Y 88
#define YEAR_Y 108
#define INFO_X 345
#define INFO_Y 140
#define INFO_W 265
#define SCORES_Y 250
#define GOALS_BUTTON_Y 400

#define LINE_H 17
static int draw_info_line(int base_group, int base_id, int* y, int value, int special = -1, bool colon = false, e_font font = FONT_NORMAL_BLACK_ON_DARK) {
    int width = 0;
    if (special != 5) {
        width += lang_text_draw(base_group, base_id, INFO_X, *y, font) - 5;
        if (colon)
            width += text_draw(string_from_ascii(":"), INFO_X + width, *y, font, 0);
    }
    switch (special) {
    default:
        width += text_draw_number(value, '@', "", INFO_X + width, *y, font);
        break;
    case 0:
        if (value >= 24) {
            width += text_draw_number(value / 12, '@', "", INFO_X + width, *y, font);
            width += lang_text_draw(298, 9, INFO_X + width, *y, font);
        } else {
            width += text_draw_number(value, '@', "", INFO_X + width, *y, font);
            width += lang_text_draw(148, 15, INFO_X + width, *y, font);
        }
        break;
    case 1:
        width += 5;
        width += lang_text_draw(153, 1 + value, INFO_X + width, *y, font);
        break;
    case 2:
        width += 5;
        width += lang_text_draw(base_group, value, INFO_X + width, *y, font);
        break;
    case 3:
        width += 5;
        value = fmin(4, fmax(0, value - 50) / 30);
        width += lang_text_draw(44, 121 + value, INFO_X + width, *y, font);
        break;
    case 4:
        width += 5;
        if (value <= 0)
            value = 0;
        else if (value <= 2)
            value = 1;
        else if (value <= 4)
            value = 2;
        else if (value <= 10)
            value = 3;
        else
            value = 4;
        width += lang_text_draw(44, 112 + value, INFO_X + width, *y, font);
        break;
    case 5:
        width += text_draw_number(value, '@', " ", INFO_X + width, *y, font);
        width += lang_text_draw(base_group, base_id, INFO_X + width, *y, font);
        break;
    }

    *y += LINE_H;
    return width;
}

static void draw_scenario_thumbnail(e_map_selection_dialog_type layout, int image_id) {
    painter ctx = game.painter();
    switch (layout) {
    case MAP_SELECTION_CCK_LEGACY:
    case MAP_SELECTION_CUSTOM:
        ctx.img_generic(image_id_from_group(GROUP_SCENARIO_IMAGE) + image_id, vec2i{78, 36});
        break;
    case MAP_SELECTION_CAMPAIGN:
    case MAP_SELECTION_CAMPAIGN_SINGLE_LIST:
        ctx.img_generic(image_id_from_group(GROUP_SCENARIO_IMAGE) + image_id, vec2i{78, 56});
        break;
    case MAP_SELECTION_CAMPAIGN_UNUSED_BACKGROUND:
        ctx.img_generic(image_id_from_group(GROUP_SCENARIO_IMAGE) + image_id, vec2i{78, 60});
        break;
    default:
        break;
    }
}

static void draw_scores(int scenario_id) {
    painter ctx = game.painter();
    int rank = get_scenario_mission_rank(scenario_id);
    bool unlocked = game_scenario_unlocked(scenario_id);
    bool beaten = game_scenario_beaten(scenario_id);
    (void)rank;
    (void)unlocked;
    if (beaten) {
        const player_record* record = player_get_scenario_record(scenario_id);
        lang_text_draw_multiline(297, scenario_id, vec2i{INFO_X, INFO_Y}, INFO_W, FONT_NORMAL_BLACK_ON_DARK);

        int line_y = SCORES_Y;
        draw_info_line(298, 6, &line_y, record->completion_months, 0);
        draw_info_line(298, 4, &line_y, record->final_population);
        draw_info_line(298, 5, &line_y, record->final_funds);
        draw_info_line(298, 0, &line_y, record->rating_culture);
        draw_info_line(298, 1, &line_y, record->rating_prosperity);
        draw_info_line(298, 3, &line_y, record->rating_kingdom);
        draw_info_line(298, 7, &line_y, record->difficulty, 1);
        draw_info_line(298, 8, &line_y, record->score, -1, false, FONT_NORMAL_WHITE_ON_DARK);
    } else {
        lang_text_draw_multiline(305, 0, vec2i{INFO_X, INFO_Y}, INFO_W, FONT_NORMAL_YELLOW);
    }

    char txt[200];
    debug_text(ctx, txt, INFO_X, -100, 100, "rank", rank, COLOR_FONT_YELLOW);
    debug_text(ctx, txt, INFO_X, -80, 100, "unlocked", unlocked, COLOR_FONT_YELLOW);
    debug_text(ctx, txt, INFO_X, -60, 100, "beaten", beaten, COLOR_FONT_YELLOW);
}

static void draw_campaign_hover_side(int campaign_idx) {
    draw_scenario_thumbnail(MAP_SELECTION_CAMPAIGN, campaign_idx);
    const int text_id_offset = 1;
    lang_text_draw_centered(294, campaign_idx * 4, INFO_X, SUBTITLE_Y, INFO_W, FONT_LARGE_BLACK_ON_DARK);
    lang_text_draw_multiline(294, campaign_idx * 4 + text_id_offset, vec2i{INFO_X, INFO_Y}, INFO_W, FONT_NORMAL_BLACK_ON_DARK);
}

static void draw_custom_side_panel_info() {
    window_scenario_selection_custom& data = g_window_scenario_selection_custom;
    scrollable_list* panel = data.map_list();
    draw_scenario_thumbnail(MAP_SELECTION_CUSTOM, g_scenario.image_id);

    uint8_t scenario_name[MAX_FILE_NAME];
    if (panel) {
        encoding_from_utf8(panel->get_selected_entry_text(FILE_NO_EXT).c_str(), scenario_name, MAX_FILE_NAME);
    } else {
        scenario_name[0] = 0;
    }
    text_ellipsize(scenario_name, FONT_LARGE_BLACK_ON_DARK, INFO_W);
    text_draw_centered(scenario_name, INFO_X, HEADER_Y, INFO_W, FONT_LARGE_BLACK_ON_DARK, 0);

    text_draw_centered(scenario_subtitle(), INFO_X, SUBTITLE_Y, INFO_W, FONT_NORMAL_WHITE_ON_DARK, 0);

    lang_text_draw_year(g_scenario.start_year, INFO_X, YEAR_Y, FONT_NORMAL_BLACK_ON_DARK);
}

static void draw_side_panel_info() {
    auto& data = g_window_scenario_selection;
    scrollable_list* panel = data.map_list();
    switch (data.dialog) {
    case MAP_SELECTION_CAMPAIGN_SINGLE_LIST: {
        draw_scenario_thumbnail(MAP_SELECTION_CAMPAIGN_SINGLE_LIST, data.campaign_sub_dialog);

        lang_text_draw_centered(294, data.campaign_sub_dialog * 4, INFO_X, HEADER_Y, INFO_W, FONT_NORMAL_BLACK_ON_LIGHT);

        if (!panel || panel->get_selected_entry_idx() == -1) {
            return;
        }

        const int campaign_scenario_id = g_scenario.campaign_scenario_id;

        bstring<300> name;
        string_copy(game_mission_get_name(campaign_scenario_id), name, 300);
        int i = index_of_string(name, string_from_ascii("("), 300);
        if (i > 0)
            name[i - 1] = '\0';
        text_draw_centered(name.c_str(), INFO_X, 60, INFO_W, FONT_LARGE_BLACK_ON_DARK, 0);

        text_draw_centered(scenario_subtitle(), INFO_X, SUBTITLE_Y, INFO_W, FONT_NORMAL_WHITE_ON_DARK, 0);

        lang_text_draw_year(g_scenario.start_year, INFO_X, YEAR_Y, FONT_NORMAL_BLACK_ON_DARK);

        if (g_scenario_selection_info.scores_or_goals == 0)
            draw_scores(campaign_scenario_id);
        break;
    }
    default:
        break;
    }
}

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

void window_scenario_selection_custom::setup_custom_dialog() {
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

    g_scenario.set_mode(e_scenario_custom_map);
    panel->set_file_finder_usage(true);
    sle->change_file_path("Maps/", "map");

    (*this)["scenario_map_list"].set_enabled(true);

    sle->onclick_item([](int index, int p2) { g_window_scenario_selection_custom.on_map_list_click(index, p2); });
    panel->set_onclick_entry([](int index, int p2) { g_window_scenario_selection_custom.on_map_list_click(index, p2); });
}

void window_scenario_selection_custom::on_map_list_click(int index, int param2) {
    (void)param2;
    scrollable_list* panel = map_list();
    if (!panel || index < 0 || index >= panel->items_count()) {
        return;
    }
    xstring mapname = panel->get_selected_entry_text(FILE_WITH_EXT);
    GamestateIO::load_map(mapname.c_str(), false);
    update_widget_visibility_after_list_change();
}

void window_scenario_selection_custom::update_widget_visibility_after_list_change() {}

void window_scenario_selection_custom::dispatch_scenario_info_script() {
    scenario_selection_info_js& s = g_scenario_selection_info;
    scrollable_list* panel = map_list();
    const bool have_sel = panel && panel->get_selected_entry_idx() != -1;
    if (!have_sel) {
        s.visible = 0;
    } else {
        s.visible = 1;
        s.is_open_play = g_scenario.is_open_play ? 1 : 0;
        s.climate_id = 77 + scenario_property_climate();
        s.mapsize_id = 121 + (int)fmin(4, fmax(0, scenario_map_size() - 50) / 30);
        s.invasion_id = 112 + scenario_invasion_count() / 2;
        s.culture = winning_culture();
        s.prosperity = winning_prosperity();
        s.monuments = winning_monuments();
        s.kingdom = winning_kingdom();
        s.population = winning_population();
        s.housing = winning_housing();
        s.house_level = winning_houselevel();
        s.has_culture = (winning_culture() > 0) ? 1 : 0;
        s.has_prosperity = (winning_prosperity() > 0) ? 1 : 0;
        s.has_monuments = (winning_monuments() > 0) ? 1 : 0;
        s.has_kingdom = (winning_kingdom() > 0) ? 1 : 0;
        s.has_population = (winning_population() > 0) ? 1 : 0;
        s.has_housing = (winning_housing() > 0) ? 1 : 0;
        if (scenario_criteria_survival_enabled()) {
            s.time_kind = 1;
            s.time_months = scenario_criteria_survival_years() * 12;
        } else if (scenario_criteria_time_limit_enabled()) {
            s.time_kind = 2;
            s.time_months = scenario_criteria_time_limit_years() * 12;
        } else {
            s.time_kind = 0;
            s.time_months = 0;
        }
        s.mon0 = scenario_property_monument(0);
        s.mon1 = scenario_property_monument(1);
        s.mon2 = scenario_property_monument(2);
    }

    ui::dispatch_autoconfig_es_event(this, "scenario_info", bvariant_map{});
}

void window_scenario_selection_custom::ui_draw_foreground(UiFlags flags) {
    if (draw_underlying) {
        window_draw_underlying_window(UiFlags_Readonly);
    }

    graphics_in_dialog_with_size(SCENARIO_SELECTION_DIALOG_W, SCENARIO_SELECTION_DIALOG_H);

    draw_custom_side_panel_info();

    ui.begin_widget(pos);
    dispatch_scenario_info_script();
    ui.draw(flags);
    ui.event(window_info{pos}, get_section(), __func__);
    ui.end_widget();

    painter ctx = game.painter();
    char txt[200];
    debug_text(ctx, txt, INFO_X, -120, 0, "", FILEIO.get_file_version(), COLOR_FONT_YELLOW);

    graphics_reset_dialog();
}

int window_scenario_selection_custom::ui_handle_mouse(const mouse* m) {
    const hotkeys* h = hotkey_state();

    if (input_go_back_requested(m, h)) {
        window_go_back();
        return 1;
    }

    if (h->enter_pressed && game.session.last_loaded == e_session_custom_map) {
        GamestateIO::start_loaded_file();
        return 1;
    }

    return autoconfig_window::ui_handle_mouse(m);
}

int window_scenario_selection::draw_background(UiFlags flags) {
    return autoconfig_window::draw_background(flags);
}

void window_scenario_selection::ui_draw_foreground(UiFlags flags) {
    if (draw_underlying) {
        window_draw_underlying_window(UiFlags_Readonly);
    }

    /* Same origin as autoconfig `pos` (1024x768); not g_screen.dialog_offset (640x480). */
    graphics_in_dialog_with_size(SCENARIO_SELECTION_DIALOG_W, SCENARIO_SELECTION_DIALOG_H);

    draw_side_panel_info();

    ui.begin_widget(pos);
    dispatch_scenario_info_script();
    ui.draw(flags);
    ui.event(window_info{pos}, get_section(), __func__);
    ui.end_widget();

    painter ctx = game.painter();
    char txt[200];
    debug_text(ctx, txt, INFO_X, -120, 0, "", FILEIO.get_file_version(), COLOR_FONT_YELLOW);

    graphics_reset_dialog();
}

int window_scenario_selection::ui_handle_mouse(const mouse* m) {
    const hotkeys* h = hotkey_state();

    if (input_go_back_requested(m, h)) {
        switch (dialog) {
        case MAP_SELECTION_CAMPAIGN_SINGLE_LIST:
            window_go_back();
            return 1;
        default:
            break;
        }
    }

    if (h->enter_pressed && g_scenario.campaign_scenario_id != -1) {
        GamestateIO::start_loaded_file();
        return 1;
    }

    return autoconfig_window::ui_handle_mouse(m);
}

int window_scenario_selection_campaign::draw_background(UiFlags flags) {
    return autoconfig_window::draw_background(flags);
}

void window_scenario_selection_campaign::ui_draw_foreground(UiFlags flags) {
    if (draw_underlying) {
        window_draw_underlying_window(UiFlags_Readonly);
    }

    graphics_in_dialog_with_size(SCENARIO_SELECTION_DIALOG_W, SCENARIO_SELECTION_DIALOG_H);

    ui.begin_widget(pos);
    ui.draw(flags);

    if (g_scenario_selection_info.period_hover >= 0) {
        draw_campaign_hover_side(g_scenario_selection_info.period_hover);
    }

    ui.event(window_info{pos}, get_section(), __func__);
    ui.end_widget();

    painter ctx = game.painter();
    char txt[200];
    debug_text(ctx, txt, INFO_X, -120, 0, "", FILEIO.get_file_version(), COLOR_FONT_YELLOW);

    graphics_reset_dialog();
}

int window_scenario_selection_campaign::ui_handle_mouse(const mouse* m) {
    const hotkeys* h = hotkey_state();

    if (input_go_back_requested(m, h)) {
        window_go_back();
        return 1;
    }

    return autoconfig_window::ui_handle_mouse(m);
}

void window_scenario_selection_show(int dialog_type) {
    const auto t = (e_map_selection_dialog_type)dialog_type;
    if (t == MAP_SELECTION_CAMPAIGN) {
        g_scenario_selection_info.period_hover = -1;
        autoconfig_window::show("window_scenario_selection_campaign");
    } else if (t == MAP_SELECTION_CUSTOM) {
        g_window_scenario_selection_custom.setup_custom_dialog();
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
