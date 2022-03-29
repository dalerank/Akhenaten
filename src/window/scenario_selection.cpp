#include "scenario_selection.h"

#include "core/dir.h"
#include "core/encoding.h"
#include "core/file.h"
#include "core/image_group.h"
#include "game/file.h"
#include "graphics/generic_button.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/image_button.h"
#include "graphics/lang_text.h"
#include "graphics/panel.h"
#include "graphics/scrollbar.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "scenario/criteria.h"
#include "scenario/invasion.h"
#include "scenario/map.h"
#include "scenario/property.h"
#include "sound/music.h"
#include "window/city.h"

#include <string.h>
#include <graphics/scroll_list_panel.h>
#include <game/mission.h>
#include <game/player_data.h>

static void button_select_item(int index, int param2);
static void button_select_campaign(int index, int param2);
static void button_start_scenario(int param1, int param2);
static void on_scroll(void);

static image_button start_button =
        {600, 440, 27, 27, IB_NORMAL, GROUP_BUTTON_EXCLAMATION, 4, button_start_scenario, button_none, 1, 0, 1};

#define MAX_SCENARIOS 15

// These braced-init-list style initializations work ONLY in C++14.
// C++11 allows for EITHER complete braced initialization, or partial
// braced initialization with NO default member values, since they
// override the default (implicit) constructor.
static scrollable_list_ui_params ui_params = {
        .x = 16,
        .y = 210,
        .blocks_x = 16,
        .blocks_y = MAX_SCENARIOS + 1,
        .scrollbar_margin_x = 10,
//        .draw_scrollbar_always = true
};
static scroll_list_panel *panel = new scroll_list_panel(MAX_SCENARIOS, button_select_item, button_none, button_none, button_none,
                                                        ui_params, true, "Maps/", "map");

#define CSEL_X 20
#define CSEL_Y 261
//#define CSEL_Y2 CSEL_Y + 70
#define CSEL_W 144
#define CSEL_H 25
#define CSEL_XGAP 152
#define CSEL_YGAP 30

static generic_button buttons_campaigns[] = {
        // pharaoh
        {CSEL_X + CSEL_XGAP * 0, CSEL_Y + CSEL_YGAP * 0, CSEL_W, CSEL_H, button_select_campaign, button_none, 0,  0},
        {CSEL_X + CSEL_XGAP * 0, CSEL_Y + CSEL_YGAP * 1, CSEL_W, CSEL_H, button_select_campaign, button_none, 1,  0},
        {CSEL_X + CSEL_XGAP * 0, CSEL_Y + CSEL_YGAP * 2, CSEL_W, CSEL_H, button_select_campaign, button_none, 2,  0},
        {CSEL_X + CSEL_XGAP * 0, CSEL_Y + CSEL_YGAP * 3, CSEL_W, CSEL_H, button_select_campaign, button_none, 3,  0},
        {CSEL_X + CSEL_XGAP * 0, CSEL_Y + CSEL_YGAP * 4, CSEL_W, CSEL_H, button_select_campaign, button_none, 4,  0},
        // cleopatra
        {CSEL_X + CSEL_XGAP * 1, CSEL_Y + CSEL_YGAP * 0, CSEL_W, CSEL_H, button_select_campaign, button_none, 5,  0},
        {CSEL_X + CSEL_XGAP * 1, CSEL_Y + CSEL_YGAP * 1, CSEL_W, CSEL_H, button_select_campaign, button_none, 6,  0},
        {CSEL_X + CSEL_XGAP * 1, CSEL_Y + CSEL_YGAP * 2, CSEL_W, CSEL_H, button_select_campaign, button_none, 7,  0},
        {CSEL_X + CSEL_XGAP * 1, CSEL_Y + CSEL_YGAP * 3, CSEL_W, CSEL_H, button_select_campaign, button_none, 8,  0},
};

static struct {
    map_selection_dialog_type dialog;
    int campaign_sub_dialog;

    int focus_button_id;
//    char selected_scenario_filename[FILE_NAME_MAX];
//    uint8_t selected_scenario_display[FILE_NAME_MAX];
} data;

static void init(map_selection_dialog_type dialog_type, int sub_dialog_selector = -1) {
    data.dialog = dialog_type;
    data.campaign_sub_dialog = sub_dialog_selector;
    switch (dialog_type) {
        case MAP_SELECTION_CCK_LEGACY:
        case MAP_SELECTION_CUSTOM:
            scenario_set_custom(2);
            panel->set_file_finder_usage(true);
            panel->change_file_path("Maps/", "map");
            break;
        case MAP_SELECTION_CAMPAIGN:
        case MAP_SELECTION_CAMPAIGN_SINGLE_LIST:
            scenario_set_custom(0);
            panel->set_file_finder_usage(false);
            panel->clear_entry_list();
            switch (data.campaign_sub_dialog) {
                case -1:
                    break;
                default:
                {
                    for (int i = get_first_mission_in_campaign(data.campaign_sub_dialog); i <= get_last_mission_in_campaign(data.campaign_sub_dialog); ++i) {
                        const char *name = player_get_cached_scenario_name(i); // TODO
                        panel->add_entry(name);
                    }
                    break;
                }
            }
            break;
    }
    window_invalidate();
}

#define TITLE_Y 25
#define SUBTITLE_Y 60
#define YEAR_Y 80
#define INFO_X 345
#define INFO_Y 105
#define INFO_W 265
#define CRITERIA_X 420
static void draw_scenario_thumbnail(int image_id) {
    switch (data.dialog) {
        case MAP_SELECTION_CCK_LEGACY:
        case MAP_SELECTION_CUSTOM:
            ImageDraw::img_generic(image_id_from_group(GROUP_SCENARIO_IMAGE) + image_id, 78, 36);
            break;
        case MAP_SELECTION_CAMPAIGN:
        case MAP_SELECTION_CAMPAIGN_SINGLE_LIST:
            ImageDraw::img_generic(image_id_from_group(GROUP_SCENARIO_IMAGE) + image_id, 78, 56);
            break;
        case MAP_SELECTION_CAMPAIGN_UNUSED_BACKGROUND:
            ImageDraw::img_generic(image_id_from_group(GROUP_SCENARIO_IMAGE) + image_id, 78, 60);
            break;
    }
}
static void draw_side_panel_info() {

    // thumbnail
    draw_scenario_thumbnail(scenario_image_id());

    switch (data.dialog) {
        case MAP_SELECTION_CAMPAIGN: {
            int text_id_offset = 1; // 0 = description; 1 = unlocked; 2 = locked
            lang_text_draw_centered(294, data.focus_button_id * 4, INFO_X, SUBTITLE_Y, INFO_W, FONT_LARGE_BLACK_ON_DARK);
            lang_text_draw_multiline(294, data.focus_button_id * 4 + text_id_offset, INFO_X, INFO_Y, INFO_W, FONT_NORMAL_BLACK_ON_DARK);
            break;
        }
        case MAP_SELECTION_CUSTOM: { // TODO
            // scenario name
            uint8_t scenario_name[FILE_NAME_MAX];
            encoding_from_utf8(panel->get_selected_entry_text(FILE_NO_EXT), scenario_name, FILE_NAME_MAX);
            text_ellipsize(scenario_name, FONT_LARGE_BLACK_ON_DARK, INFO_W);
            text_draw_centered(scenario_name, INFO_X, TITLE_Y, INFO_W, FONT_LARGE_BLACK_ON_DARK, 0);

            // subtitle
            text_draw_centered(scenario_subtitle(), INFO_X, SUBTITLE_Y, INFO_W, FONT_NORMAL_WHITE_ON_DARK, 0);

            // starting year
            lang_text_draw_year(scenario_property_start_year(), INFO_X, YEAR_Y, FONT_NORMAL_BLACK_ON_DARK);

            // climate
            lang_text_draw_centered(44, 77 + scenario_property_climate(), INFO_X, INFO_Y, INFO_W, FONT_LARGE_BLACK_ON_DARK);
            break;
        }
        case MAP_SELECTION_CAMPAIGN_SINGLE_LIST: {
            int scenario_id = scenario_campaign_scenario_id();

            // scenario name
            text_draw_centered(scenario_name(), INFO_X, TITLE_Y, INFO_W, FONT_LARGE_BLACK_ON_DARK, 0);

            // subtitle
            text_draw_centered(scenario_subtitle(), INFO_X, SUBTITLE_Y, INFO_W, FONT_NORMAL_WHITE_ON_DARK, 0);

            // starting year
            lang_text_draw_year(scenario_property_start_year(), INFO_X, YEAR_Y, FONT_NORMAL_BLACK_ON_DARK);

            bool beaten = game_scenario_beaten(scenario_id);
            if (beaten) {
                const player_record *record = player_get_scenario_record(scenario_id);
                lang_text_draw_multiline(297, scenario_id, INFO_X, INFO_Y, INFO_W, FONT_NORMAL_BLACK_ON_DARK);
            } else {
                lang_text_draw_multiline(305, 0, INFO_X, INFO_Y, INFO_W, FONT_NORMAL_BLACK_ON_DARK);
            }
            break;
        }
    }



    // headers
//    char selected_scenario_filename[FILE_NAME_MAX];
//    text_ellipsize(selected_scenario_display, FONT_LARGE_BLACK_ON_LIGHT, INFO_W + 10);
//    text_draw_centered(selected_scenario_display, INFO_X, TITLE_Y, INFO_W + 10, FONT_LARGE_BLACK_ON_LIGHT, 0);
//    text_draw_centered(scenario_subtitle(), INFO_X, SUBTITLE_Y, INFO_W, FONT_NORMAL_WHITE_ON_DARK, 0);
//    lang_text_draw_year(scenario_property_start_year(), CRITERIA_X, 90, FONT_LARGE_BLACK_ON_DARK);
//    lang_text_draw_centered(44, 77 + scenario_property_climate(), INFO_X, 150, INFO_W, FONT_LARGE_BLACK_ON_DARK);

//    // map size
//    int text_id;
//    switch (scenario_map_size()) {
//        case 40:
//            text_id = 121;
//            break;
//        case 60:
//            text_id = 122;
//            break;
//        case 80:
//            text_id = 123;
//            break;
//        case 100:
//            text_id = 124;
//            break;
//        case 120:
//            text_id = 125;
//            break;
//        default:
//            text_id = 126;
//            break;
//    }
//    lang_text_draw_centered(44, text_id, INFO_X, 170, INFO_W, FONT_NORMAL_BLACK_ON_DARK);
//
//    // military
//    int num_invasions = scenario_invasion_count();
//    if (num_invasions <= 0)
//        text_id = 112;
//    else if (num_invasions <= 2)
//        text_id = 113;
//    else if (num_invasions <= 4)
//        text_id = 114;
//    else if (num_invasions <= 10)
//        text_id = 115;
//    else
//        text_id = 116;
//    lang_text_draw_centered(44, text_id, INFO_X, 190, INFO_W, FONT_NORMAL_BLACK_ON_LIGHT);
//
//    lang_text_draw_centered(32, 11 + scenario_property_player_rank(), INFO_X, 210, INFO_W,
//                            FONT_NORMAL_BLACK_ON_LIGHT);
//    if (scenario_is_open_play()) {
//        if (scenario_open_play_id() < 12)
//            lang_text_draw_multiline(145, scenario_open_play_id(), INFO_X + 10, 270, INFO_W - 10,
//                                     FONT_NORMAL_BLACK_ON_LIGHT);
//    } else {
//        lang_text_draw_centered(44, 127, INFO_X, 262, INFO_W, FONT_NORMAL_BLACK_ON_LIGHT);
//        int width;
//        if (winning_culture()) {
//            width = text_draw_number(winning_culture(), '@', " ", CRITERIA_X, 290,
//                                     FONT_NORMAL_BLACK_ON_LIGHT);
//            lang_text_draw(44, 129, CRITERIA_X + width, 290, FONT_NORMAL_BLACK_ON_LIGHT);
//        }
//        if (winning_prosperity()) {
//            width = text_draw_number(winning_prosperity(), '@', " ", CRITERIA_X, 306,
//                                     FONT_NORMAL_BLACK_ON_LIGHT);
//            lang_text_draw(44, 130, CRITERIA_X + width, 306, FONT_NORMAL_BLACK_ON_LIGHT);
//        }
//        if (winning_peace()) {
//            width = text_draw_number(winning_peace(), '@', " ", CRITERIA_X, 322, FONT_NORMAL_BLACK_ON_LIGHT);
//            lang_text_draw(44, 131, CRITERIA_X + width, 322, FONT_NORMAL_BLACK_ON_LIGHT);
//        }
//        if (winning_favor()) {
//            width = text_draw_number(winning_favor(), '@', " ", CRITERIA_X, 338, FONT_NORMAL_BLACK_ON_LIGHT);
//            lang_text_draw(44, 132, CRITERIA_X + width, 338, FONT_NORMAL_BLACK_ON_LIGHT);
//        }
//        if (winning_population()) {
//            width = text_draw_number(winning_population(), '@', " ", CRITERIA_X, 354,
//                                     FONT_NORMAL_BLACK_ON_LIGHT);
//            lang_text_draw(44, 133, CRITERIA_X + width, 354, FONT_NORMAL_BLACK_ON_LIGHT);
//        }
//        if (scenario_criteria_time_limit_enabled()) {
//            width = text_draw_number(scenario_criteria_time_limit_years(), '@', " ", CRITERIA_X, 370,
//                                     FONT_NORMAL_BLACK_ON_LIGHT);
//            lang_text_draw(44, 134, CRITERIA_X + width, 370, FONT_NORMAL_BLACK_ON_LIGHT);
//        }
//        if (scenario_criteria_survival_enabled()) {
//            width = text_draw_number(scenario_criteria_survival_years(), '@', " ", CRITERIA_X, 386,
//                                     FONT_NORMAL_BLACK_ON_LIGHT);
//            lang_text_draw(44, 135, CRITERIA_X + width, 386, FONT_NORMAL_BLACK_ON_LIGHT);
//        }
//    }
//    lang_text_draw_centered(44, 136, INFO_X, 446, INFO_W, FONT_NORMAL_BLACK_ON_LIGHT);
}

static void draw_background(void) {
    graphics_reset_dialog();
    switch (data.dialog) {
        case MAP_SELECTION_CCK_LEGACY:
            ImageDraw::img_background(image_id_from_group(GROUP_MAP_SELECTION_CCK));
            break;
        case MAP_SELECTION_CUSTOM:
            ImageDraw::img_background(image_id_from_group(GROUP_MAP_SELECTION_CUSTOM));
            break;
        case MAP_SELECTION_CAMPAIGN:
        case MAP_SELECTION_CAMPAIGN_SINGLE_LIST:
            ImageDraw::img_background(image_id_from_group(GROUP_MAP_SELECTION_HISTORY));
            break;
    }
    graphics_in_dialog();
    if (data.dialog != MAP_SELECTION_CAMPAIGN) {
        panel->draw();
        draw_side_panel_info();
//        draw_side_panel_info(panel->get_selected_entry_text());
    }
    graphics_reset_dialog();
}
static void draw_foreground(void) {
    graphics_in_dialog();

    switch (data.dialog) {
        case MAP_SELECTION_CUSTOM:
        case MAP_SELECTION_CAMPAIGN_SINGLE_LIST:
            panel->draw();
            break;
        case MAP_SELECTION_CAMPAIGN:
            // campaign buttons
            lang_text_draw_centered(294, 41, CSEL_X, CSEL_Y + 10 - CSEL_YGAP, CSEL_W, FONT_NORMAL_BLACK_ON_LIGHT);
            lang_text_draw_centered(294, 42, CSEL_X + CSEL_XGAP, CSEL_Y + 10 - CSEL_YGAP, CSEL_W, FONT_NORMAL_BLACK_ON_LIGHT);
            for (int i = 0; i < 9; ++i) {
//                button_border_draw(buttons_campaigns[i].x, buttons_campaigns[i].y, buttons_campaigns[i].width, buttons_campaigns[i].height,
//                                   data.focus_button_id == i + 1 ? 1 : 0);
                large_label_draw(buttons_campaigns[i].x, buttons_campaigns[i].y, buttons_campaigns[i].width / 16,
                                 data.focus_button_id == i + 1 ? 1 : 0);
                lang_text_draw_centered(294, i * 4, buttons_campaigns[i].x, buttons_campaigns[i].y + 5, buttons_campaigns[i].width,
                                        FONT_NORMAL_BLACK_ON_LIGHT);
            }
            if (data.focus_button_id > 0)
                draw_side_panel_info();
            break;
    }

    image_buttons_draw(0, 0, &start_button, 1);
    graphics_reset_dialog();
}

static void button_select_campaign(int index, int param2) {
    init(MAP_SELECTION_CAMPAIGN_SINGLE_LIST, index);
}
static void button_select_item(int index, int param2) {
    if (index >= panel->get_total_entries())
        return;

    switch (data.dialog) {
        case MAP_SELECTION_CUSTOM:
            game_file_load_scenario_data(panel->get_selected_entry_text(FILE_FULL_PATH)); // TODO
            break;
        case MAP_SELECTION_CAMPAIGN_SINGLE_LIST:
            break;
    }

//    strcpy(data.selected_scenario_filename, panel->get_selected_entry_text());
//    game_file_load_scenario_data(data.selected_scenario_filename);
//    encoding_from_utf8(data.selected_scenario_filename, data.selected_scenario_display, FILE_NAME_MAX);
//    file_remove_extension(data.selected_scenario_display);
    window_invalidate();
}
static void button_start_scenario(int param1, int param2) {
    // TODO
//    if (game_file_start_scenario(data.selected_scenario_filename)) {
//        sound_music_update(1);
//        window_city_show();
//    }
}

static void on_scroll(void) {
    window_invalidate();
}
static void handle_input(const mouse *m, const hotkeys *h) {
    if (input_go_back_requested(m, h)) {
        switch (data.dialog) {
            case MAP_SELECTION_CUSTOM:
            case MAP_SELECTION_CAMPAIGN:
                window_go_back();
                break;
            case MAP_SELECTION_CAMPAIGN_SINGLE_LIST:
                init(MAP_SELECTION_CAMPAIGN, -1);
                break;
        }

    }
    const mouse *m_dialog = mouse_in_dialog(m);

    switch (data.dialog) {
        case MAP_SELECTION_CUSTOM:
        case MAP_SELECTION_CAMPAIGN_SINGLE_LIST:
            if (panel->input_handle(m_dialog))
                return;
            break;
        case MAP_SELECTION_CAMPAIGN:
            int last_focus = data.focus_button_id;
            if (generic_buttons_handle_mouse(m_dialog, 0, 0, buttons_campaigns, 9, &data.focus_button_id))
                return;
            if (last_focus != data.focus_button_id)
                window_invalidate();
            break;
    }

    if (image_buttons_handle_mouse(m_dialog, 0, 0, &start_button, 1, 0))
        return;
    if (h->enter_pressed) {
        button_start_scenario(0, 0);
        return;
    }
}
void window_scenario_selection_show(map_selection_dialog_type dialog_type) {
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
