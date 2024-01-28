#include "mission_briefing.h"

#include "city/mission.h"
#include "game/mission.h"
#include "game/tutorial.h"
#include "graphics/boilerplate.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/rich_text.h"
#include "graphics/image_groups.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "io/gamefiles/lang.h"
#include "io/gamestate/boilerplate.h"
#include "scenario/criteria.h"
#include "scenario/property.h"
#include "scenario/scenario_data.h"
#include "sound/music.h"
#include "sound/speech.h"
#include "window/city.h"
#include "window/intermezzo.h"
#include "window/mission_next.h"
#include "game/settings.h"

ANK_REGISTER_CONFIG_ITERATOR(config_load_mission_briefing);

static void button_back(int param1, int param2);
static void button_start_mission(int param1, int param2);
static void inc_dec_difficulty(int param1, int param2);

static const vec2i GOAL_OFFSET[] = {{32, 90}, {288, 90}, {32, 112}, {288, 112}, {32, 134}, {288, 134}};

struct mission_briefing : ui::widget {
    struct {
        image_button back = {0, 0, 31, 20, IB_NORMAL, GROUP_MESSAGE_ICON, 8, button_back, button_none, 0, 0, 1};
        image_button start_mission = {0, 0, 27, 27, IB_NORMAL, GROUP_BUTTON_EXCLAMATION, 4, button_start_mission, button_none, 1, 0, 1};
        image_button inc_difficulty = {0, 0, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, inc_dec_difficulty, inc_dec_difficulty, 1,  0, true};
        image_button dec_difficulty = {0, 0, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, inc_dec_difficulty, inc_dec_difficulty, -1,  0, true};
    } buttons;

    int is_review;
    int focus_button;
    int campaign_mission_loaded;
    int difficulty;
};

mission_briefing g_mission_briefing;

void config_load_mission_briefing() {
    g_config_arch.r_section("mission_briefing_window", [] (archive arch) {
        g_mission_briefing.load(arch);
    });
}

static void init() {
    g_mission_briefing.focus_button = 0;
    rich_text_reset(0);

    // load map!
    if (!g_mission_briefing.campaign_mission_loaded) {
        g_mission_briefing.campaign_mission_loaded = 1;
    }
}

static void draw_background() {
    auto &data = g_mission_briefing;
    window_draw_underlying_window();

    graphics_set_to_dialog();

    int text_id = 200 + scenario_campaign_scenario_id();
    const lang_message* msg = lang_get_message(text_id);

    g_mission_briefing["title"].text((pcstr)msg->title.text);
    g_mission_briefing["subtitle"].text((pcstr)msg->subtitle.text);

    rich_text_set_fonts(FONT_NORMAL_WHITE_ON_DARK, FONT_NORMAL_YELLOW);
    rich_text_init(msg->content.text, 64, 200, 31, 14, 0);

    graphics_reset_dialog();
}

static void draw_foreground(void) {
    auto &data = g_mission_briefing;
    int text_id = 200 + scenario_campaign_scenario_id();
    const lang_message* msg = lang_get_message(text_id);

    graphics_set_to_dialog();

    g_mission_briefing.draw();

    lang_text_draw(62, 10, 48, 104, FONT_NORMAL_WHITE_ON_DARK);
    int goal_index = 0;

    if (winning_population()) {
        vec2i offset = GOAL_OFFSET[goal_index];
        goal_index++;
        label_draw(16 + offset.x, 32 + offset.y, 15, 1);
        int width = lang_text_draw(62, 11, 16 + offset.x + 8, 32 + offset.y + 3, FONT_NORMAL_YELLOW);
        text_draw_number(winning_population(), '@', " ", 16 + offset.x + 8 + width, 32 + offset.y + 3, FONT_NORMAL_YELLOW);
    }

    if (winning_housing()) {
        vec2i offset = GOAL_OFFSET[goal_index];
        goal_index++;
        label_draw(16 + offset.x, 32 + offset.y, 15, 1);
        int width = text_draw_number(winning_housing(), '@', " ", 16 + offset.x + 8, 32 + offset.y + 3, FONT_NORMAL_YELLOW);
        lang_text_draw(29, 20 + winning_houselevel(), 16 + offset.x + 8 + width, 32 + offset.y + 3, FONT_NORMAL_YELLOW);
    }

    if (winning_culture()) {
        vec2i offset = GOAL_OFFSET[goal_index];
        goal_index++;
        label_draw(16 + offset.x, 32 + offset.y, 15, 1);
        int width = lang_text_draw(62, 12, 16 + offset.x + 8, 32 + offset.y + 3, FONT_NORMAL_YELLOW);
        text_draw_number(winning_culture(), '@', " ", 16 + offset.x + 8 + width, 32 + offset.y + 3, FONT_NORMAL_YELLOW);
    }

    if (winning_prosperity()) {
        vec2i offset = GOAL_OFFSET[goal_index];
        goal_index++;
        label_draw(16 + offset.x, 32 + offset.y, 15, 1);
        int width = lang_text_draw(62, 13, 16 + offset.x + 8, 32 + offset.y + 3, FONT_NORMAL_YELLOW);
        text_draw_number(winning_prosperity(), '@', " ", 16 + offset.x + 8 + width, 32 + offset.y + 3, FONT_NORMAL_YELLOW);
    }

    if (winning_monuments()) {
        vec2i offset = GOAL_OFFSET[goal_index];
        goal_index++;
        label_draw(16 + offset.x, 32 + offset.y, 15, 1);
        int width = lang_text_draw(62, 14, 16 + offset.x + 8, 32 + offset.y + 3, FONT_NORMAL_YELLOW);
        text_draw_number(winning_monuments(), '@', " ", 16 + offset.x + 8 + width, 32 + offset.y + 3, FONT_NORMAL_YELLOW);
    }

    if (winning_kingdom()) {
        vec2i offset = GOAL_OFFSET[goal_index];
        goal_index++;
        label_draw(16 + offset.x, 32 + offset.y, 15, 1);
        int width = lang_text_draw(62, 15, 16 + offset.x + 8, 32 + offset.y + 3, FONT_NORMAL_YELLOW);
        text_draw_number(winning_kingdom(), '@', " ", 16 + offset.x + 8 + width, 32 + offset.y + 3, FONT_NORMAL_YELLOW);
    }
    int immediate_goal_text = tutorial_get_immediate_goal_text();
    if (immediate_goal_text) {
        vec2i offset = GOAL_OFFSET[4];
        label_draw(16 + offset.x, 32 + offset.y, 31, 1);
        lang_text_draw(62, immediate_goal_text, 16 + offset.x + 8, 32 + offset.y + 3, FONT_NORMAL_YELLOW);
    }

    inner_panel_draw(32, 200, 33, 14);
    lang_text_draw(153, g_settings.difficulty + 1, 65 + 45, 433, FONT_NORMAL_BLACK_ON_LIGHT);

    graphics_set_clip_rectangle(35, 187, 522, 234);
    rich_text_draw(msg->content.text, 48, 202, 512, 14, 0);
    graphics_reset_clip_rectangle();

    rich_text_draw_scrollbar();
    image_buttons_draw(516, 426, &data.buttons.start_mission, 1);
    if (!data.is_review && game_mission_has_choice()) {
        image_buttons_draw(26, 428, &data.buttons.back, 1);
    }

    if (!data.is_review) {
        image_buttons_draw( 65, 428, &data.buttons.dec_difficulty, 1, 0);
        image_buttons_draw( 65 + 18, 428, &data.buttons.inc_difficulty, 1, 0);
    }

    graphics_reset_dialog();
}

static void handle_input(const mouse* m, const hotkeys* h) {
    auto &data = g_mission_briefing;
    const mouse* m_dialog = mouse_in_dialog(m);

    if (image_buttons_handle_mouse(m_dialog, 516, 426, &data.buttons.start_mission, 1, 0)) {
        return;
    }

    if (!data.is_review && game_mission_has_choice()) {
        if (image_buttons_handle_mouse(m_dialog, 26, 428, &data.buttons.back, 1, 0))
            return;
    }

    if (!data.is_review) {
        image_buttons_handle_mouse(m_dialog, 65, 428, &data.buttons.dec_difficulty, 1, 0);
        image_buttons_handle_mouse(m_dialog, 65 + 18, 428, &data.buttons.inc_difficulty, 1, 0);
    }

    rich_text_handle_mouse(m_dialog);
}
static void button_back(int param1, int param2) {
    if (!g_mission_briefing.is_review) {
        sound_speech_stop();
        window_mission_next_selection_show();
    }
}
static void button_start_mission(int param1, int param2) {
    sound_speech_stop();
    sound_music_update(true);
    window_city_show();
    city_mission_reset_save_start();
}

static void inc_dec_difficulty(int param1, int param2) {
    if (param1 > 0) { g_settings.increase_difficulty(); }
    else { g_settings.decrease_difficulty(); }
    window_invalidate();
}

static void show(void) {
    window_type window = {WINDOW_MISSION_BRIEFING, draw_background, draw_foreground, handle_input};
    init();
    window_show(&window);
}

void window_mission_briefing_show() {
    auto &data = g_mission_briefing;
    data.is_review = 0;
    data.campaign_mission_loaded = 0;
    window_intermezzo_show(INTERMEZZO_MISSION_BRIEFING, show);
}

void window_mission_briefing_show_review() {
    auto &data = g_mission_briefing;
    data.is_review = 1;
    data.campaign_mission_loaded = 1;
    window_intermezzo_show(INTERMEZZO_MISSION_BRIEFING, show);
}
