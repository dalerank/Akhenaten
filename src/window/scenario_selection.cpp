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

#define MAX_SCENARIOS 15

static void button_select_item(int index, int param2);
static void button_start_scenario(int param1, int param2);
static void on_scroll(void);

static image_button start_button =
        {600, 440, 27, 27, IB_NORMAL, GROUP_BUTTON_EXCLAMATION, 4, button_start_scenario, button_none, 1, 0, 1};

//#define LIST_X 18
//#define LIST_Y 220
//#define LIST_WIDTH 16

// These braced-init-list initializations work ONLY in C++14.
// C++11 allows for EITHER complete initialization, or partial
// initialization without default member values!
scrollable_list_ui_params ui_params = {
        .x = 16,
        .y = 210,
        .blocks_x = 16,
        .blocks_y = MAX_SCENARIOS + 1,
        .scrollbar_margin_x = 10,
        .draw_scrollbar_always = true
};
scroll_list_panel *scroll_list = new scroll_list_panel(MAX_SCENARIOS, 1000, button_select_item, button_select_item, ui_params,
                                                       true, "Maps/", "map");

//static generic_button file_buttons[] = {
//        {LIST_X, LIST_Y + 16 * 0, LIST_WIDTH * 16, 16, button_select_item, button_none, 0,  0},
//        {LIST_X, LIST_Y + 16 * 1, LIST_WIDTH * 16, 16, button_select_item, button_none, 1,  0},
//        {LIST_X, LIST_Y + 16 * 2, LIST_WIDTH * 16, 16, button_select_item, button_none, 2,  0},
//        {LIST_X, LIST_Y + 16 * 3, LIST_WIDTH * 16, 16, button_select_item, button_none, 3,  0},
//        {LIST_X, LIST_Y + 16 * 4, LIST_WIDTH * 16, 16, button_select_item, button_none, 4,  0},
//        {LIST_X, LIST_Y + 16 * 5, LIST_WIDTH * 16, 16, button_select_item, button_none, 5,  0},
//        {LIST_X, LIST_Y + 16 * 6, LIST_WIDTH * 16, 16, button_select_item, button_none, 6,  0},
//        {LIST_X, LIST_Y + 16 * 7, LIST_WIDTH * 16, 16, button_select_item, button_none, 7,  0},
//        {LIST_X, LIST_Y + 16 * 8, LIST_WIDTH * 16, 16, button_select_item, button_none, 8,  0},
//        {LIST_X, LIST_Y + 16 * 9, LIST_WIDTH * 16, 16, button_select_item, button_none, 9,  0},
//        {LIST_X, LIST_Y + 16 * 10, LIST_WIDTH * 16, 16, button_select_item, button_none, 10, 0},
//        {LIST_X, LIST_Y + 16 * 11, LIST_WIDTH * 16, 16, button_select_item, button_none, 11, 0},
//        {LIST_X, LIST_Y + 16 * 12, LIST_WIDTH * 16, 16, button_select_item, button_none, 12, 0},
//        {LIST_X, LIST_Y + 16 * 13, LIST_WIDTH * 16, 16, button_select_item, button_none, 13, 0},
//        {LIST_X, LIST_Y + 16 * 14, LIST_WIDTH * 16, 16, button_select_item, button_none, 14, 0},
//};

//static scrollbar_type scrollbar = {LIST_X + LIST_WIDTH * 16 + 4, LIST_Y - 12, (MAX_SCENARIOS + 1) * 16, on_scroll, 8, 1};

static struct {
    map_selection_dialog_type dialog;

//    int focus_button_id;
//    int selected_item;
    char selected_scenario_filename[FILE_NAME_MAX];
    uint8_t selected_scenario_display[FILE_NAME_MAX];

//    const dir_listing *scenarios;
} data;

static void init(map_selection_dialog_type dialog_type) {
//    data.focus_button_id = 0;
    scroll_list->unfocus();
    data.dialog = dialog_type;
    scroll_list->refresh_dir_list();
    switch (dialog_type) {
        case MAP_SELECTION_CCK_LEGACY:
        case MAP_SELECTION_CUSTOM:
            scenario_set_custom(2);
//            data.scenarios = dir_find_files_with_extension("Maps/", "map");
//            button_select_item(0, 0);
//            scrollbar_init(&scrollbar, 0, data.scenarios->num_files - MAX_SCENARIOS);
            break;
        case MAP_SELECTION_CAMPAIGN:
        case MAP_SELECTION_CAMPAIGN_SINGLE_LIST:
            scenario_set_custom(0);
//            data.scenarios = dir_find_files_with_extension(".", "map"); // TODO
//            button_select_item(0, 0);
//            scrollbar_init(&scrollbar, 0, data.scenarios->num_files - MAX_SCENARIOS);
            break;
    }
}

static void draw_scenario_thumbnail() {
    switch (data.dialog) {
        case MAP_SELECTION_CCK_LEGACY:
        case MAP_SELECTION_CUSTOM:
            ImageDraw::img_generic(image_id_from_group(GROUP_SCENARIO_IMAGE) + scenario_image_id(), 78, 36);
            break;
        case MAP_SELECTION_CAMPAIGN:
        case MAP_SELECTION_CAMPAIGN_SINGLE_LIST:
            ImageDraw::img_generic(image_id_from_group(GROUP_SCENARIO_IMAGE) + scenario_image_id(), 78, 56);
            break;
        case MAP_SELECTION_CAMPAIGN_UNUSED_BACKGROUND:
            ImageDraw::img_generic(image_id_from_group(GROUP_SCENARIO_IMAGE) + scenario_image_id(), 78, 60);
            break;
    }
}
static void draw_scenario_list(void) {
//    scroll_list->draw();
//    inner_panel_draw(LIST_X - 2, LIST_Y - 10, LIST_WIDTH, MAX_SCENARIOS + 1);
//    char file[FILE_NAME_MAX];
//    uint8_t displayable_file[FILE_NAME_MAX];
//    for (int i = 0; i < MAX_SCENARIOS; i++) {
//        font_t font = FONT_NORMAL_BLACK_ON_DARK;
//        if (data.selected_item == i + scrollbar.scroll_position)
//            font = FONT_NORMAL_WHITE_ON_DARK;
//        else if (data.focus_button_id == i + 1)
//            font = FONT_NORMAL_YELLOW;
//        strcpy(file, data.scenarios->files[i + scrollbar.scroll_position]);
//        encoding_from_utf8(file, displayable_file, FILE_NAME_MAX);
//        file_remove_extension(displayable_file);
//        text_ellipsize(displayable_file, font, 240);
//        text_draw(displayable_file, LIST_X + 6, LIST_Y + 16 * i, font, 0);
//    }
}
static void draw_scenario_info(void) {
    const int scenario_info_x = 335;
    const int scenario_info_width = 280;
    const int scenario_criteria_x = 420;

    // thumbnail
    draw_scenario_thumbnail();

    // headers
    text_ellipsize(data.selected_scenario_display, FONT_LARGE_BLACK_ON_DARK, scenario_info_width + 10);
    text_draw_centered(data.selected_scenario_display, scenario_info_x, 25, scenario_info_width + 10, FONT_LARGE_BLACK_ON_DARK, 0);
    text_draw_centered(scenario_subtitle(), scenario_info_x, 60, scenario_info_width, FONT_NORMAL_WHITE_ON_DARK, 0);
    lang_text_draw_year(scenario_property_start_year(), scenario_criteria_x, 90, FONT_LARGE_BLACK_ON_DARK);
    lang_text_draw_centered(44, 77 + scenario_property_climate(), scenario_info_x, 150, scenario_info_width, FONT_LARGE_BLACK_ON_DARK);

    // map size
    int text_id;
    switch (scenario_map_size()) {
        case 40:
            text_id = 121;
            break;
        case 60:
            text_id = 122;
            break;
        case 80:
            text_id = 123;
            break;
        case 100:
            text_id = 124;
            break;
        case 120:
            text_id = 125;
            break;
        default:
            text_id = 126;
            break;
    }
    lang_text_draw_centered(44, text_id, scenario_info_x, 170, scenario_info_width, FONT_NORMAL_BLACK_ON_DARK);

    // military
    int num_invasions = scenario_invasion_count();
    if (num_invasions <= 0)
        text_id = 112;
    else if (num_invasions <= 2)
        text_id = 113;
    else if (num_invasions <= 4)
        text_id = 114;
    else if (num_invasions <= 10)
        text_id = 115;
    else
        text_id = 116;
    lang_text_draw_centered(44, text_id, scenario_info_x, 190, scenario_info_width, FONT_NORMAL_BLACK_ON_LIGHT);

    lang_text_draw_centered(32, 11 + scenario_property_player_rank(), scenario_info_x, 210, scenario_info_width,
                            FONT_NORMAL_BLACK_ON_LIGHT);
    if (scenario_is_open_play()) {
        if (scenario_open_play_id() < 12)
            lang_text_draw_multiline(145, scenario_open_play_id(), scenario_info_x + 10, 270, scenario_info_width - 10,
                                     FONT_NORMAL_BLACK_ON_LIGHT);
    } else {
        lang_text_draw_centered(44, 127, scenario_info_x, 262, scenario_info_width, FONT_NORMAL_BLACK_ON_LIGHT);
        int width;
        if (winning_culture()) {
            width = text_draw_number(winning_culture(), '@', " ", scenario_criteria_x, 290,
                                     FONT_NORMAL_BLACK_ON_LIGHT);
            lang_text_draw(44, 129, scenario_criteria_x + width, 290, FONT_NORMAL_BLACK_ON_LIGHT);
        }
        if (winning_prosperity()) {
            width = text_draw_number(winning_prosperity(), '@', " ", scenario_criteria_x, 306,
                                     FONT_NORMAL_BLACK_ON_LIGHT);
            lang_text_draw(44, 130, scenario_criteria_x + width, 306, FONT_NORMAL_BLACK_ON_LIGHT);
        }
        if (winning_peace()) {
            width = text_draw_number(winning_peace(), '@', " ", scenario_criteria_x, 322, FONT_NORMAL_BLACK_ON_LIGHT);
            lang_text_draw(44, 131, scenario_criteria_x + width, 322, FONT_NORMAL_BLACK_ON_LIGHT);
        }
        if (winning_favor()) {
            width = text_draw_number(winning_favor(), '@', " ", scenario_criteria_x, 338, FONT_NORMAL_BLACK_ON_LIGHT);
            lang_text_draw(44, 132, scenario_criteria_x + width, 338, FONT_NORMAL_BLACK_ON_LIGHT);
        }
        if (winning_population()) {
            width = text_draw_number(winning_population(), '@', " ", scenario_criteria_x, 354,
                                     FONT_NORMAL_BLACK_ON_LIGHT);
            lang_text_draw(44, 133, scenario_criteria_x + width, 354, FONT_NORMAL_BLACK_ON_LIGHT);
        }
        if (scenario_criteria_time_limit_enabled()) {
            width = text_draw_number(scenario_criteria_time_limit_years(), '@', " ", scenario_criteria_x, 370,
                                     FONT_NORMAL_BLACK_ON_LIGHT);
            lang_text_draw(44, 134, scenario_criteria_x + width, 370, FONT_NORMAL_BLACK_ON_LIGHT);
        }
        if (scenario_criteria_survival_enabled()) {
            width = text_draw_number(scenario_criteria_survival_years(), '@', " ", scenario_criteria_x, 386,
                                     FONT_NORMAL_BLACK_ON_LIGHT);
            lang_text_draw(44, 135, scenario_criteria_x + width, 386, FONT_NORMAL_BLACK_ON_LIGHT);
        }
    }
    lang_text_draw_centered(44, 136, scenario_info_x, 446, scenario_info_width, FONT_NORMAL_BLACK_ON_LIGHT);
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
        scroll_list->draw();
//        draw_scenario_list();
    }
    draw_scenario_info();
    graphics_reset_dialog();
}
static void draw_foreground(void) {
    graphics_in_dialog();
    if (data.dialog != MAP_SELECTION_CAMPAIGN) {
        scroll_list->draw();
//        scrollbar_draw(&scrollbar);
//        draw_scenario_list();
    }
    image_buttons_draw(0, 0, &start_button, 1);
    graphics_reset_dialog();
}

static void button_select_item(int index, int param2) {
    if (index >= scroll_list->get_total_entries())
        return;
//    data.selected_item = scrollbar.scroll_position + index;
    strcpy(data.selected_scenario_filename, scroll_list->get_selected_entry_text_utf8());
    game_file_load_scenario_data(data.selected_scenario_filename);
    encoding_from_utf8(data.selected_scenario_filename, data.selected_scenario_display, FILE_NAME_MAX);
    file_remove_extension(data.selected_scenario_display);
    window_invalidate();
}
static void button_start_scenario(int param1, int param2) {
    if (game_file_start_scenario(data.selected_scenario_filename)) {
        sound_music_update(1);
        window_city_show();
    }
}

static void on_scroll(void) {
    window_invalidate();
}
static void handle_input(const mouse *m, const hotkeys *h) {
    const mouse *m_dialog = mouse_in_dialog(m);
    scroll_list->input_handle(m_dialog);
//    if (scrollbar_handle_mouse(&scrollbar, m_dialog))
//        return;
    if (image_buttons_handle_mouse(m_dialog, 0, 0, &start_button, 1, 0))
        return;
//    if (generic_buttons_handle_mouse(m_dialog, 0, 0, file_buttons, MAX_SCENARIOS, &data.focus_button_id))
//        return;
    if (h->enter_pressed) {
        button_start_scenario(0, 0);
        return;
    }
    if (input_go_back_requested(m, h))
        window_go_back();
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
