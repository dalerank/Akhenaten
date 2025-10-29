#include "scenario_selection.h"

#include "core/encoding.h"
#include "core/log.h"
#include "graphics/graphics.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/image_groups.h"
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
#include "game/game.h"

#include "dev/debug.h"
#include "game/mission.h"
#include "graphics/elements/scroll_list_panel.h"
#include "io/manager.h"
#include "game/player_data.h"
#include <cmath>

static void button_select_item(int index, int param2);
static void button_select_campaign(int index, int param2);
static void button_start_scenario(int param1, int param2);
static void button_scores_or_goals(int param1, int param2);
static void on_scroll(void);

static image_button start_button = {600, 440, 27, 27, IB_NORMAL, PACK_GENERAL, 193, 4, button_start_scenario, button_none, 1, 0, 1};

#define MAX_SCENARIOS 15

static scrollable_list_ui_params ui_params = [] {
    scrollable_list_ui_params ret;
    ret.pos = { 16, 210 };
    ret.blocks_x = 16;
    ret.blocks_y = MAX_SCENARIOS + 1;
    ret.scrollbar_margin_x = 10;
    return ret;
}();

struct window_scenario_selection_t {
    scroll_list_panel *panel = nullptr;
    e_map_selection_dialog_type dialog;
    int campaign_sub_dialog;
    int scores_or_goals;

    int focus_button_id;
};

window_scenario_selection_t g_window_scenario_selection;

#define CSEL_X 20
#define CSEL_Y 261
// #define CSEL_Y2 CSEL_Y + 70
#define CSEL_W 144
#define CSEL_H 25
#define CSEL_XGAP 152
#define CSEL_YGAP 30

static generic_button buttons_campaigns[] = {
  // pharaoh
  {CSEL_X + CSEL_XGAP * 0, CSEL_Y + CSEL_YGAP * 0, CSEL_W, CSEL_H, button_select_campaign, button_none, 0, 0},
  {CSEL_X + CSEL_XGAP * 0, CSEL_Y + CSEL_YGAP * 1, CSEL_W, CSEL_H, button_select_campaign, button_none, 1, 0},
  {CSEL_X + CSEL_XGAP * 0, CSEL_Y + CSEL_YGAP * 2, CSEL_W, CSEL_H, button_select_campaign, button_none, 2, 0},
  {CSEL_X + CSEL_XGAP * 0, CSEL_Y + CSEL_YGAP * 3, CSEL_W, CSEL_H, button_select_campaign, button_none, 3, 0},
  {CSEL_X + CSEL_XGAP * 0, CSEL_Y + CSEL_YGAP * 4, CSEL_W, CSEL_H, button_select_campaign, button_none, 4, 0},
  // cleopatra
  {CSEL_X + CSEL_XGAP * 1, CSEL_Y + CSEL_YGAP * 0, CSEL_W, CSEL_H, button_select_campaign, button_none, 5, 0},
  {CSEL_X + CSEL_XGAP * 1, CSEL_Y + CSEL_YGAP * 1, CSEL_W, CSEL_H, button_select_campaign, button_none, 6, 0},
  {CSEL_X + CSEL_XGAP * 1, CSEL_Y + CSEL_YGAP * 2, CSEL_W, CSEL_H, button_select_campaign, button_none, 7, 0},
  {CSEL_X + CSEL_XGAP * 1, CSEL_Y + CSEL_YGAP * 3, CSEL_W, CSEL_H, button_select_campaign, button_none, 8, 0},
};

static void init(e_map_selection_dialog_type dialog_type, int sub_dialog_selector = -1) {
    auto &data = g_window_scenario_selection;
    data.dialog = dialog_type;
    data.campaign_sub_dialog = sub_dialog_selector;
    data.scores_or_goals = 0;
    scenario_set_campaign_scenario(-1);

    if (!data.panel) {
        data.panel = new scroll_list_panel(MAX_SCENARIOS, button_select_item, button_none, button_none, button_none, ui_params, true, "Maps/", "map");
    }

    switch (dialog_type) {
    case MAP_SELECTION_CCK_LEGACY:
    case MAP_SELECTION_CUSTOM:
        g_scenario.set_mode(e_scenario_custom_map);
        data.panel->set_file_finder_usage(true);
        data.panel->change_file_path("Maps/", "map");
        break;
    case MAP_SELECTION_CAMPAIGN:
    case MAP_SELECTION_CAMPAIGN_SINGLE_LIST:
        g_scenario.set_mode(e_scenario_normal);
        data.panel->set_file_finder_usage(false);
        data.panel->clear_entry_list();
        switch (data.campaign_sub_dialog) {
        case -1:
            break;
        default: {
            for (int i = 0; i < MAX_MANUAL_ENTRIES; ++i) {
                auto mission_data = get_campaign_mission_step_data(data.campaign_sub_dialog, i);
                if (mission_data != nullptr && mission_data->scenario_id != -1) {
                    char name_utf8[MAX_FILE_NAME] = {0};
                    if (mission_data && mission_data->map_name) {
                        encoding_to_utf8(mission_data->map_name, name_utf8, MAX_FILE_NAME, 0);
                        data.panel->add_entry(name_utf8);
                    } else {
                        logs::error("Could not initialize SDL: %s", SDL_GetError());
                    }
                }
            }
            break;
        }
        }
        break;
    }
}

#define HEADER_Y 28
#define HEADER_LARGE_Y 25
#define TITLE_Y 60
// #define TITLE_LARGE_Y 58
#define SUBTITLE_Y 88
#define YEAR_Y 108
#define INFO_X 345
#define INFO_Y 140
#define INFO_W 265
#define CRITERIA_X 420
#define SCORES_Y 250
#define GOALS_BUTTON_Y 400

static generic_button button_scores_goals[] = {
  {INFO_X + INFO_W / 8 - 10, GOALS_BUTTON_Y, 6 * (INFO_W / 8) + 20, 30, button_scores_or_goals, button_none, 1, 0},
  {INFO_X + INFO_W / 8, GOALS_BUTTON_Y, 6 * (INFO_W / 8), 30, button_scores_or_goals, button_none, 0, 0},
};

#define LINE_H 17
static int draw_text_line(int* base_group, int* y, int* phrase_group, e_font font = FONT_NORMAL_BLACK_ON_DARK) {
    int width = lang_text_draw(base_group[0], base_group[1], INFO_X, *y, font) - 5;
    width += lang_text_draw(phrase_group[0], phrase_group[1], INFO_X + width, *y, font);
    return width;
}

static int draw_info_line(int base_group, int base_id, int* y, int value, int special = -1, bool colon = false, e_font font = FONT_NORMAL_BLACK_ON_DARK) {
    int width = 0;
    if (special != 5) {
        width += lang_text_draw(base_group, base_id, INFO_X, *y, font) - 5;
        if (colon)
            width += text_draw(string_from_ascii(":"), INFO_X + width, *y, font, 0);
    }
    switch (special) {
    default: // simple number
        width += text_draw_number(value, '@', "", INFO_X + width, *y, font);
        break;
    case 0:                // completion time
        if (value >= 24) { // years
            width += text_draw_number(value / 12, '@', "", INFO_X + width, *y, font);
            width += lang_text_draw(298, 9, INFO_X + width, *y, font);
        } else { // months
            width += text_draw_number(value, '@', "", INFO_X + width, *y, font);
            width += lang_text_draw(148, 15, INFO_X + width, *y, font);
        }
        break;
    case 1: // difficulty
        width += 5;
        width += lang_text_draw(153, 1 + value, INFO_X + width, *y, font);
        break;
    case 2: // lang text id
        width += 5;
        width += lang_text_draw(base_group, value, INFO_X + width, *y, font);
        break;
    case 3: // map size
        width += 5;
        value = fmin(4, fmax(0, value - 50) / 30);
        width += lang_text_draw(44, 121 + value, INFO_X + width, *y, font);
        break;
    case 4: // invasions
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
    case 5: // reverse: value first, then text
        width += text_draw_number(value, '@', " ", INFO_X + width, *y, font);
        width += lang_text_draw(base_group, base_id, INFO_X + width, *y, font);
        break;
    }

    *y += LINE_H;
    return width;
}

static void draw_scenario_thumbnail(int image_id) {
    painter ctx = game.painter();
    auto &data = g_window_scenario_selection;
    switch (data.dialog) {
    case MAP_SELECTION_CCK_LEGACY:
    case MAP_SELECTION_CUSTOM:
        ImageDraw::img_generic(ctx, image_id_from_group(GROUP_SCENARIO_IMAGE) + image_id, vec2i{78, 36});
        break;
    case MAP_SELECTION_CAMPAIGN:
    case MAP_SELECTION_CAMPAIGN_SINGLE_LIST:
        ImageDraw::img_generic(ctx, image_id_from_group(GROUP_SCENARIO_IMAGE) + image_id, vec2i{78, 56});
        break;
    case MAP_SELECTION_CAMPAIGN_UNUSED_BACKGROUND:
        ImageDraw::img_generic(ctx, image_id_from_group(GROUP_SCENARIO_IMAGE) + image_id, vec2i{78, 60});
        break;
    }
}
static void draw_scenario_info() {
    auto &data = g_window_scenario_selection;
    if (data.panel->get_selected_entry_idx() == -1)
        return;

    // map info
    int line_y = INFO_Y - 17;
    lang_text_draw_centered(44, 10, INFO_X, line_y, INFO_W, FONT_NORMAL_WHITE_ON_DARK);
    line_y += LINE_H;
    if (false) {
        draw_info_line(44, 76, &line_y, 77 + scenario_property_climate(), 2, true);
        draw_info_line(44, 120, &line_y, scenario_map_size(), 3, true);
        draw_info_line(44, 111, &line_y, scenario_invasion_count(), 4, true);
        draw_info_line(2, 6, &line_y, 0, 2, true); // TODO
    } else {
        lang_text_draw(44, 77 + scenario_property_climate(), INFO_X, line_y, FONT_NORMAL_BLACK_ON_DARK);
        line_y += LINE_H;
        lang_text_draw(
          44, 121 + fmin(4, fmax(0, scenario_map_size() - 50) / 30), INFO_X, line_y, FONT_NORMAL_BLACK_ON_DARK);
        line_y += LINE_H;
        lang_text_draw(44, 112 + scenario_invasion_count() / 2, INFO_X, line_y, FONT_NORMAL_BLACK_ON_DARK);
        line_y += LINE_H;
        lang_text_draw(2, 6, INFO_X, line_y, FONT_NORMAL_BLACK_ON_DARK);
        line_y += LINE_H; // TODO
    }

    // scenario objectives
    lang_text_draw_centered(44, 127, INFO_X, line_y, INFO_W, FONT_NORMAL_WHITE_ON_DARK);
    line_y += LINE_H;
    if (scenario_is_open_play()) {
        lang_text_draw_multiline(145, 0, vec2i{INFO_X, line_y}, INFO_W, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        if (winning_culture() > 0)
            draw_info_line(44, 129, &line_y, winning_culture(), 5);
        if (winning_prosperity() > 0)
            draw_info_line(44, 130, &line_y, winning_prosperity(), 5);
        if (winning_monuments() > 0)
            draw_info_line(44, 131, &line_y, winning_monuments(), 5);
        if (winning_kingdom() > 0)
            draw_info_line(44, 132, &line_y, winning_kingdom(), 5);
        if (winning_population() > 0)
            draw_info_line(44, 133, &line_y, winning_population(), 5);
        if (winning_housing() > 0)
            draw_info_line(29, 20 + winning_houselevel(), &line_y, winning_housing(), 5);

        if (scenario_criteria_survival_enabled())
            draw_info_line(44, 55, &line_y, scenario_criteria_survival_years() * 12, 0, true, FONT_NORMAL_YELLOW);
        else if (scenario_criteria_time_limit_enabled())
            draw_info_line(44, 54, &line_y, scenario_criteria_time_limit_years() * 12, 0, true, FONT_NORMAL_YELLOW);
    }

    // monuments
    line_y = 328;
    if (true) {
        int m = 0;
        lang_text_draw_centered(41, 48, INFO_X, line_y, INFO_W, FONT_NORMAL_WHITE_ON_DARK);
        line_y += LINE_H;
        if (scenario_property_monument(0) > 0) {
            lang_text_draw(198, scenario_property_monument(0), INFO_X, line_y, FONT_NORMAL_BLACK_ON_DARK);
            line_y += LINE_H;
            m++;
        }
        if (scenario_property_monument(1) > 0) {
            lang_text_draw(198, scenario_property_monument(1), INFO_X, line_y, FONT_NORMAL_BLACK_ON_DARK);
            line_y += LINE_H;
            m++;
        }
        if (scenario_property_monument(2) > 0) {
            lang_text_draw(198, scenario_property_monument(2), INFO_X, line_y, FONT_NORMAL_BLACK_ON_DARK);
            line_y += LINE_H;
            m++;
        }
        if (m == 0)
            lang_text_draw(198, 0, INFO_X, line_y, FONT_NORMAL_BLACK_ON_DARK);
    }
}

static void draw_scores(int scenario_id) {
    painter ctx = game.painter();
    int rank = get_scenario_mission_rank(scenario_id);
    bool unlocked = game_scenario_unlocked(scenario_id);
    bool beaten = game_scenario_beaten(scenario_id);
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

static void draw_side_panel_info() {
    auto &data = g_window_scenario_selection;
    switch (data.dialog) {
    case MAP_SELECTION_CAMPAIGN: {
        // thumbnail
        draw_scenario_thumbnail(data.focus_button_id - 1);

        int text_id_offset = 1; // 0 = description; 1 = unlocked; 2 = locked
        lang_text_draw_centered(294, (data.focus_button_id - 1) * 4, INFO_X, SUBTITLE_Y, INFO_W, FONT_LARGE_BLACK_ON_DARK);
        lang_text_draw_multiline(294, (data.focus_button_id - 1) * 4 + text_id_offset, vec2i{INFO_X, INFO_Y}, INFO_W, FONT_NORMAL_BLACK_ON_DARK);
        break;
    }
    case MAP_SELECTION_CUSTOM: {
        // thumbnail
        draw_scenario_thumbnail(scenario_image_id());

        // scenario name
        uint8_t scenario_name[MAX_FILE_NAME];
        encoding_from_utf8(data.panel->get_selected_entry_text(FILE_NO_EXT).c_str(), scenario_name, MAX_FILE_NAME);
        text_ellipsize(scenario_name, FONT_LARGE_BLACK_ON_DARK, INFO_W);
        text_draw_centered(scenario_name, INFO_X, HEADER_Y, INFO_W, FONT_LARGE_BLACK_ON_DARK, 0);

        // subtitle
        text_draw_centered(scenario_subtitle(), INFO_X, SUBTITLE_Y, INFO_W, FONT_NORMAL_WHITE_ON_DARK, 0);

        // starting year
        lang_text_draw_year(scenario_property_start_year(), INFO_X, YEAR_Y, FONT_NORMAL_BLACK_ON_DARK);

        draw_scenario_info();
        break;
    }
    case MAP_SELECTION_CAMPAIGN_SINGLE_LIST: {
        // thumbnail
        draw_scenario_thumbnail(data.campaign_sub_dialog);

        // campaign title
        lang_text_draw_centered(
          294, data.campaign_sub_dialog * 4, INFO_X, HEADER_Y, INFO_W, FONT_NORMAL_BLACK_ON_LIGHT);

        if (data.panel->get_selected_entry_idx() == -1) {
            return;
        }

        int scenario_id = scenario_campaign_scenario_id();

        // scenario name
        bstring<300> name;
        string_copy(game_mission_get_name(scenario_id), name, 300);
        int i = index_of_string(name, string_from_ascii("("), 300);
        if (i > 0)
            name[i - 1] = '\0';
        text_draw_centered(name.c_str(), INFO_X, TITLE_Y, INFO_W, FONT_LARGE_BLACK_ON_DARK, 0);

        // subtitle
        text_draw_centered(scenario_subtitle(), INFO_X, SUBTITLE_Y, INFO_W, FONT_NORMAL_WHITE_ON_DARK, 0);

        // starting year
        lang_text_draw_year(scenario_property_start_year(), INFO_X, YEAR_Y, FONT_NORMAL_BLACK_ON_DARK);

        if (data.scores_or_goals == 0)
            draw_scores(scenario_id);
        else
            draw_scenario_info();
        break;
    }
    }
}

static void draw_background(int) {
    auto &data = g_window_scenario_selection;
    painter ctx = game.painter();
    switch (data.dialog) {
    case MAP_SELECTION_CCK_LEGACY:
        ImageDraw::img_background(ctx, image_id_from_group(GROUP_MAP_SELECTION_CCK));
        break;
    case MAP_SELECTION_CUSTOM:
        ImageDraw::img_background(ctx, image_id_from_group(GROUP_MAP_SELECTION_CUSTOM));
        break;
    case MAP_SELECTION_CAMPAIGN:
    case MAP_SELECTION_CAMPAIGN_SINGLE_LIST:
        ImageDraw::img_background(ctx, image_id_from_group(GROUP_MAP_SELECTION_HISTORY));
        break;
    }
    graphics_set_to_dialog();
    if (data.dialog != MAP_SELECTION_CAMPAIGN) {
        data.panel->draw();
        draw_side_panel_info();
    }
    graphics_reset_dialog();
}
static void draw_foreground(int) {
    painter ctx = game.painter();
    auto &data = g_window_scenario_selection;
    graphics_set_to_dialog();

    switch (data.dialog) {
    case MAP_SELECTION_CUSTOM:
    case MAP_SELECTION_CAMPAIGN_SINGLE_LIST:
        data.panel->draw();
        if (data.dialog == MAP_SELECTION_CAMPAIGN_SINGLE_LIST && data.panel->get_selected_entry_idx() != -1) {
            // show scores / goals button
            int i = data.scores_or_goals;
            button_border_draw(button_scores_goals[i].x, button_scores_goals[i].y, button_scores_goals[i].width, button_scores_goals[i].height, data.focus_button_id == 1 ? 1 : 0);
            lang_text_draw_centered(44, 221 - i, button_scores_goals[i].x, button_scores_goals[i].y + 10, button_scores_goals[i].width, FONT_NORMAL_BLACK_ON_DARK);
        }
        break;
    case MAP_SELECTION_CAMPAIGN:
        // campaign buttons
        lang_text_draw_centered(294, 41, CSEL_X, CSEL_Y + 10 - CSEL_YGAP, CSEL_W, FONT_NORMAL_BLACK_ON_LIGHT);
        lang_text_draw_centered(294, 42, CSEL_X + CSEL_XGAP, CSEL_Y + 10 - CSEL_YGAP, CSEL_W, FONT_NORMAL_BLACK_ON_LIGHT);
        for (int i = 0; i < 9; ++i) {
            large_label_draw(buttons_campaigns[i].x, buttons_campaigns[i].y, buttons_campaigns[i].width / 16, data.focus_button_id == i + 1 ? 1 : 0);
            lang_text_draw_centered(294, i * 4, buttons_campaigns[i].x, buttons_campaigns[i].y + 5, buttons_campaigns[i].width, FONT_NORMAL_BLACK_ON_LIGHT);
        }
        if (data.focus_button_id > 0)
            draw_side_panel_info();
        break;
    }

    char txt[200];
    debug_text(ctx, txt, INFO_X, -120, 0, "", FILEIO.get_file_version(), COLOR_FONT_YELLOW);
    //    draw_debug_line(txt, INFO_X + 100, -120, 0, "", get_junk2(), COLOR_FONT_YELLOW);

    image_buttons_draw({0, 0}, &start_button, 1);
    graphics_reset_dialog();
}

static void button_select_campaign(int index, int param2) {
    init(MAP_SELECTION_CAMPAIGN_SINGLE_LIST, index);
}

static void button_select_item(int index, int param2) {
    auto &data = g_window_scenario_selection;
    if (index >= data.panel->get_total_entries())
        return;
    switch (data.dialog) {
    case MAP_SELECTION_CUSTOM: {
            xstring mapname = data.panel->get_selected_entry_text(FILE_WITH_EXT);
            GamestateIO::load_map(mapname.c_str(), false);
        }
        break;
    case MAP_SELECTION_CAMPAIGN_SINGLE_LIST:
        GamestateIO::load_mission(get_first_mission_in_campaign(data.campaign_sub_dialog) + data.panel->get_selected_entry_idx(), false);
        break;
    }
}

static void button_start_scenario(int param1, int param2) {
    if (scenario_campaign_scenario_id() == -1) {
        return;
    }

    GamestateIO::start_loaded_file();
}

static void button_scores_or_goals(int param1, int param2) {
    auto &data = g_window_scenario_selection;
    data.scores_or_goals = param1;
}

static void on_scroll(void) {
}

static void handle_input(const mouse* m, const hotkeys* h) {
    auto &data = g_window_scenario_selection;
    if (input_go_back_requested(m, h)) {
        switch (data.dialog) {
        case MAP_SELECTION_CUSTOM:
        case MAP_SELECTION_CAMPAIGN:
            window_go_back();
            break;
        case MAP_SELECTION_CAMPAIGN_SINGLE_LIST:
            init(MAP_SELECTION_CAMPAIGN, -1);
            break;

        default:
            assert(false);
        }
    }
    const mouse* m_dialog = mouse_in_dialog(m);

    switch (data.dialog) {
    case MAP_SELECTION_CUSTOM:
    case MAP_SELECTION_CAMPAIGN_SINGLE_LIST:
        if (data.panel->input_handle(m_dialog)) {
            return;
        }

        if (data.dialog == MAP_SELECTION_CAMPAIGN_SINGLE_LIST && data.panel->get_selected_entry_idx() != -1) {
            if (!data.scores_or_goals) {
                if (generic_buttons_handle_mouse(m_dialog, {0, 0}, &button_scores_goals[0], 1, &data.focus_button_id))
                    return;
            } else if (generic_buttons_handle_mouse(m_dialog, {0, 0}, &button_scores_goals[1], 1, &data.focus_button_id))
                return;
        }
        break;
    case MAP_SELECTION_CAMPAIGN: {
            int last_focus = data.focus_button_id;
            if (generic_buttons_handle_mouse(m_dialog, {0, 0}, buttons_campaigns, 9, &data.focus_button_id)) {
                return;
            }

            if (last_focus != data.focus_button_id) {
            }
        }
        break;

    default:
        assert(false);
    }

    if (image_buttons_handle_mouse(m_dialog, {0, 0}, &start_button, 1, 0)) {
        return;
    }

    if (h->enter_pressed) {
        button_start_scenario(0, 0);
        return;
    }
}

void window_scenario_selection_show(e_map_selection_dialog_type dialog_type) {
    // city construction kit
    window_type window = {
        WINDOW_CCK_SELECTION,
        draw_background,
        draw_foreground,
        handle_input
    };
    init(dialog_type);
    window_show(&window);
}
