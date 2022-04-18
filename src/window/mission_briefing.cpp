#include "mission_briefing.h"

#include "city/mission.h"
#include "core/image_group.h"
#include "core/lang.h"
#include "game/gamestate/boilerplate.h"
#include "game/mission.h"
#include "game/tutorial.h"
#include "graphics/graphics.h"
#include "graphics/image_button.h"
#include "graphics/lang_text.h"
#include "graphics/panel.h"
#include "graphics/rich_text.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "scenario/criteria.h"
#include "scenario/property.h"
#include "sound/music.h"
#include "sound/speech.h"
#include "window/city.h"
#include "window/intermezzo.h"
#include "window/mission_next.h"

static void button_back(int param1, int param2);
static void button_start_mission(int param1, int param2);

static const int GOAL_OFFSETS_X[] = {32, 288, 32, 288, 32, 288};
static const int GOAL_OFFSETS_Y[] = {90, 90, 112, 112, 134, 134};

static image_button image_button_back = {
        0, 0, 31, 20, IB_NORMAL, GROUP_MESSAGE_ICON, 8, button_back, button_none, 0, 0, 1
};
static image_button image_button_start_mission = {
        0, 0, 27, 27, IB_NORMAL, GROUP_BUTTON_EXCLAMATION, 4, button_start_mission, button_none, 1, 0, 1
};

static struct {
    int is_review;
    int focus_button;
    int campaign_mission_loaded;
} data;

static void init(void) {
    data.focus_button = 0;
    rich_text_reset(0);

    // load map!
    if (!data.campaign_mission_loaded) {
        data.campaign_mission_loaded = 1;
    }
}

#include "scenario/data.h"

static void draw_background(void) {
//    if (!data.campaign_mission_loaded) {
//        data.campaign_mission_loaded = 1;
//        if (!game_file_start_scenario_by_name(scenario_name())) {
//            window_city_show();
//            return;
//        }
//    }

    window_draw_underlying_window();

    graphics_in_dialog();
    int text_id = 200 + scenario_campaign_scenario_id();
    const lang_message *msg = lang_get_message(text_id);

    outer_panel_draw(16, 32, 38, 27);
    text_draw(msg->title.text, 32, 48, FONT_LARGE_BLACK_ON_LIGHT, 0);
    text_draw(msg->subtitle.text, 32, 78, FONT_NORMAL_BLACK_ON_LIGHT, 0);

    lang_text_draw(62, 7, 376, 433, FONT_NORMAL_BLACK_ON_LIGHT);
//    if (!data.is_review && game_mission_has_choice())
//        lang_text_draw(13, 4, 66, 435, FONT_NORMAL_BLACK_ON_LIGHT);

    inner_panel_draw(32, 96, 33, 6);
    lang_text_draw(62, 10, 48, 104, FONT_NORMAL_WHITE_ON_DARK);
    int goal_index = 0;
    if (winning_population()) {
        int x = GOAL_OFFSETS_X[goal_index];
        int y = GOAL_OFFSETS_Y[goal_index];
        goal_index++;
        label_draw(16 + x, 32 + y, 15, 1);
        int width = lang_text_draw(62, 11, 16 + x + 8, 32 + y + 3, FONT_NORMAL_YELLOW);
        text_draw_number(winning_population(), '@', " ", 16 + x + 8 + width, 32 + y + 3, FONT_NORMAL_YELLOW);
    }
    if (winning_housing()) {
        int x = GOAL_OFFSETS_X[goal_index];
        int y = GOAL_OFFSETS_Y[goal_index];
        goal_index++;
        label_draw(16 + x, 32 + y, 15, 1);
        int width = text_draw_number(winning_housing(), '@', " ", 16 + x + 8, 32 + y + 3, FONT_NORMAL_YELLOW);
        lang_text_draw(29, 20 + winning_houselevel(), 16 + x + 8 + width, 32 + y + 3, FONT_NORMAL_YELLOW);
    }
    if (winning_culture()) {
        int x = GOAL_OFFSETS_X[goal_index];
        int y = GOAL_OFFSETS_Y[goal_index];
        goal_index++;
        label_draw(16 + x, 32 + y, 15, 1);
        int width = lang_text_draw(62, 12, 16 + x + 8, 32 + y + 3, FONT_NORMAL_YELLOW);
        text_draw_number(winning_culture(), '@', " ", 16 + x + 8 + width, 32 + y + 3, FONT_NORMAL_YELLOW);
    }
    if (winning_prosperity()) {
        int x = GOAL_OFFSETS_X[goal_index];
        int y = GOAL_OFFSETS_Y[goal_index];
        goal_index++;
        label_draw(16 + x, 32 + y, 15, 1);
        int width = lang_text_draw(62, 13, 16 + x + 8, 32 + y + 3, FONT_NORMAL_YELLOW);
        text_draw_number(winning_prosperity(), '@', " ", 16 + x + 8 + width, 32 + y + 3, FONT_NORMAL_YELLOW);
    }
    if (winning_monuments()) {
        int x = GOAL_OFFSETS_X[goal_index];
        int y = GOAL_OFFSETS_Y[goal_index];
        goal_index++;
        label_draw(16 + x, 32 + y, 15, 1);
        int width = lang_text_draw(62, 14, 16 + x + 8, 32 + y + 3, FONT_NORMAL_YELLOW);
        text_draw_number(winning_monuments(), '@', " ", 16 + x + 8 + width, 32 + y + 3, FONT_NORMAL_YELLOW);
    }
    if (winning_kingdom()) {
        int x = GOAL_OFFSETS_X[goal_index];
        int y = GOAL_OFFSETS_Y[goal_index];
        goal_index++;
        label_draw(16 + x, 32 + y, 15, 1);
        int width = lang_text_draw(62, 15, 16 + x + 8, 32 + y + 3, FONT_NORMAL_YELLOW);
        text_draw_number(winning_kingdom(), '@', " ", 16 + x + 8 + width, 32 + y + 3, FONT_NORMAL_YELLOW);
    }
    int immediate_goal_text = tutorial_get_immediate_goal_text();
    if (immediate_goal_text) {
        int x = GOAL_OFFSETS_X[4];
        int y = GOAL_OFFSETS_Y[4];
        label_draw(16 + x, 32 + y, 31, 1);
        lang_text_draw(62, immediate_goal_text, 16 + x + 8, 32 + y + 3, FONT_NORMAL_YELLOW);
    }

    inner_panel_draw(32, 200, 33, 14);

    rich_text_set_fonts(FONT_NORMAL_WHITE_ON_DARK, FONT_NORMAL_YELLOW);
    rich_text_init(msg->content.text, 64, 200, 31, 14, 0);

    graphics_set_clip_rectangle(35, 187, 522, 234);
    rich_text_draw(msg->content.text, 48, 202, 496, 14, 0);
    graphics_reset_clip_rectangle();

    graphics_reset_dialog();
}
static void draw_foreground(void) {
    graphics_in_dialog();

    rich_text_draw_scrollbar();
    image_buttons_draw(516, 426, &image_button_start_mission, 1);
    if (!data.is_review && game_mission_has_choice())
        image_buttons_draw(26, 428, &image_button_back, 1);

    graphics_reset_dialog();
}

static void handle_input(const mouse *m, const hotkeys *h) {
    const mouse *m_dialog = mouse_in_dialog(m);

    if (image_buttons_handle_mouse(m_dialog, 516, 426, &image_button_start_mission, 1, 0))
        return;
    if (!data.is_review && game_mission_has_choice()) {
        if (image_buttons_handle_mouse(m_dialog, 26, 428, &image_button_back, 1, 0))
            return;
    }
    rich_text_handle_mouse(m_dialog);
}
static void button_back(int param1, int param2) {
    if (!data.is_review) {
        sound_speech_stop();
        window_mission_next_selection_show();
    }
}
static void button_start_mission(int param1, int param2) {
    sound_speech_stop();
    sound_music_update(1);
    window_city_show();
    city_mission_reset_save_start();
}

static void show(void) {
    window_type window = {
            WINDOW_MISSION_BRIEFING,
            draw_background,
            draw_foreground,
            handle_input
    };
    init();
    window_show(&window);
}
void window_mission_briefing_show(void) {
    data.is_review = 0;
    data.campaign_mission_loaded = 0;
    window_intermezzo_show(INTERMEZZO_MISSION_BRIEFING, show);
}
void window_mission_briefing_show_review(void) {
    data.is_review = 1;
    data.campaign_mission_loaded = 1;
    window_intermezzo_show(INTERMEZZO_MISSION_BRIEFING, show);
}
