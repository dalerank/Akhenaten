#include "mission_briefing.h"

#include "city/mission.h"
#include "game/mission.h"
#include "game/tutorial.h"
#include "graphics/graphics.h"
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
#include "scenario/scenario.h"
#include "sound/music.h"
#include "sound/speech.h"
#include "window/window_city.h"
#include "window/intermezzo.h"
#include "window/mission_next.h"
#include "game/settings.h"

ANK_REGISTER_CONFIG_ITERATOR(config_load_mission_briefing);

static void button_back(int param1, int param2);
static void button_start_mission(int param1, int param2);
static void inc_dec_difficulty(int param1, int param2);

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

    auto &ui = g_mission_briefing;

    ui["title"].text((pcstr)msg->title.text);
    ui["subtitle"].text((pcstr)msg->subtitle.text);
    ui["difficulty_label"].text(ui::str(153, g_settings.difficulty + 1));

    const pcstr widgets[] = {"goal_0", "goal_1", "goal_2", "goal_3", "goal_4", "goal_5"};
    auto goal_label = widgets;

    auto setup_goal = [&] (int group, int tid, bool enabled, int value) {
        ui[*goal_label].enabled = enabled;
        if (enabled) {
            ui[*goal_label++].text_var("%s: %u", ui::str(group, tid), value);
        }
    };

    setup_goal(62, 11, winning_population() > 0, winning_population());
    setup_goal(29, 20 + winning_houselevel(), winning_housing() > 0, winning_housing());
    setup_goal(62, 12, winning_culture() > 0, winning_culture());
    setup_goal(62, 13, winning_prosperity() > 0, winning_prosperity());
    setup_goal(62, 14, winning_monuments() > 0, winning_monuments());
    setup_goal(62, 15, winning_kingdom() > 0, winning_kingdom());

    int immediate_goal_text = tutorial_get_immediate_goal_text();
    if (immediate_goal_text) {
        ui["goal_immediate"].text(ui::str(62, immediate_goal_text));
    }

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

    graphics_set_clip_rectangle(35, 187, 522, 234);
    rich_text_draw(msg->content.text, 48, 202, 512, 14, 0);
    graphics_reset_clip_rectangle();

    rich_text_draw_scrollbar();
    image_buttons_draw({516, 426}, &data.buttons.start_mission, 1);
    if (!data.is_review && game_mission_has_choice()) {
        image_buttons_draw({26, 428}, &data.buttons.back, 1);
    }

    if (!data.is_review) {
        image_buttons_draw({65, 428}, &data.buttons.dec_difficulty, 1, 0);
        image_buttons_draw({65 + 18, 428}, &data.buttons.inc_difficulty, 1, 0);
    }

    graphics_reset_dialog();
}

static void handle_input(const mouse* m, const hotkeys* h) {
    auto &data = g_mission_briefing;
    const mouse* m_dialog = mouse_in_dialog(m);

    if (image_buttons_handle_mouse(m_dialog, {516, 426}, &data.buttons.start_mission, 1, 0)) {
        return;
    }

    if (!data.is_review && game_mission_has_choice()) {
        if (image_buttons_handle_mouse(m_dialog, {26, 428}, &data.buttons.back, 1, 0))
            return;
    }

    if (!data.is_review) {
        image_buttons_handle_mouse(m_dialog, {65, 428}, &data.buttons.dec_difficulty, 1, 0);
        image_buttons_handle_mouse(m_dialog, {65 + 18, 428}, &data.buttons.inc_difficulty, 1, 0);
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
