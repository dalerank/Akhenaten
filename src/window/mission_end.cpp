#include "mission_end.h"

#include "city/city.h"
#include "city/finance.h"
#include "city/population.h"
#include "city/ratings.h"
#include "city/victory.h"
#include "game/mission.h"
#include "game/settings.h"
#include "game/state.h"
#include "game/undo.h"
#include "graphics/graphics.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "scenario/scenario.h"
#include "sound/music.h"
#include "sound/sound.h"
#include "window/intermezzo.h"
#include "window/main_menu.h"
#include "window/mission_next.h"
#include "window/victory_video.h"
#include "core/game_environment.h"
#include "building/construction/build_planner.h"
#include "io/gamestate/boilerplate.h"
#include "window/window_city.h"
#include "widget/widget_top_menu_game.h"

ui::mission_end_window g_mission_end;
ui::mission_won_window g_mission_won;
ui::mission_lost_window g_mission_lost;

static void button_fired(int param1, int param2);

static generic_button fired_buttons[] = {
  {80, 224, 480, 25, button_fired, button_none, 0, 0},
};

static int focus_button_id;

static int get_max(int value1, int value2, int value3) {
    int max = value1;
    if (value2 > max) {
        max = value2;
    }

    if (value3 > max) {
        max = value3;
    }

    return max;
}

int ui::mission_won_window::draw_background(UiFlags flags) {
    outer_panel_draw(vec2i{48, 128}, 34, 18);
    lang_text_draw_centered(62, 0, 48, 144, 544, FONT_LARGE_BLACK_ON_LIGHT);

    inner_panel_draw({ 64, 184 }, { 32, 7 });

    if (scenario_is_custom()) {
        lang_text_draw_multiline(147, 20, vec2i{80, 192}, 488, FONT_NORMAL_WHITE_ON_DARK);
    } else {
        lang_text_draw_multiline(147, scenario_campaign_scenario_id(), vec2i{80, 192}, 488, FONT_NORMAL_WHITE_ON_DARK);
    }

    int left_width = get_max(lang_text_get_width(148, 0, FONT_NORMAL_BLACK_ON_LIGHT),
                             lang_text_get_width(148, 2, FONT_NORMAL_BLACK_ON_LIGHT),
                             lang_text_get_width(148, 4, FONT_NORMAL_BLACK_ON_LIGHT));
    int right_width = get_max(lang_text_get_width(148, 1, FONT_NORMAL_BLACK_ON_LIGHT),
                              lang_text_get_width(148, 3, FONT_NORMAL_BLACK_ON_LIGHT),
                              lang_text_get_width(148, 5, FONT_NORMAL_BLACK_ON_LIGHT));
    int left_offset = 68;
    int right_offset = left_offset + 10 + 512 * left_width / (left_width + right_width);
    int width = lang_text_draw(148, 0, left_offset, 308, FONT_NORMAL_BLACK_ON_LIGHT);
    text_draw_number(g_city.ratings.culture, '@', " ", left_offset + width, 308, FONT_NORMAL_BLACK_ON_LIGHT);

    width = lang_text_draw(148, 1, right_offset, 308, FONT_NORMAL_BLACK_ON_LIGHT);
    text_draw_number(g_city.ratings.prosperity, '@', " ", right_offset + width, 308, FONT_NORMAL_BLACK_ON_LIGHT);

    width = lang_text_draw(148, 2, left_offset, 328, FONT_NORMAL_BLACK_ON_LIGHT);
    text_draw_number(g_city.ratings.monument, '@', " ", left_offset + width, 328, FONT_NORMAL_BLACK_ON_LIGHT);

    width = lang_text_draw(148, 3, right_offset, 328, FONT_NORMAL_BLACK_ON_LIGHT);
    text_draw_number(g_city.ratings.kingdom, '@', " ", right_offset + width, 328, FONT_NORMAL_BLACK_ON_LIGHT);

    width = lang_text_draw(148, 4, left_offset, 348, FONT_NORMAL_BLACK_ON_LIGHT);
    text_draw_number(city_population(), '@', " ", left_offset + width, 348, FONT_NORMAL_BLACK_ON_LIGHT);

    width = lang_text_draw(148, 5, right_offset, 348, FONT_NORMAL_BLACK_ON_LIGHT);
    text_draw_number(city_finance_treasury(), '@', " ", right_offset + width, 348, FONT_NORMAL_BLACK_ON_LIGHT);

    lang_text_draw_centered(13, 1, 64, 388, 512, FONT_NORMAL_BLACK_ON_LIGHT);

    return 0;
}

void ui::mission_end_window::init() {
    autoconfig_window &cui = getui();

    cui["replay_mission"].onclick([] {
        Planner.reset();
        if (scenario_is_custom()) {
            GamestateIO::load_savegame("autosave_replay.sav");
            window_city_show();
        } else {
            int scenario_id = scenario_campaign_scenario_id();
            widget_top_menu_clear_state();
            GamestateIO::load_mission(scenario_id, true);
        }
    });
}

void ui::mission_end_window::draw_foreground(UiFlags flags) {
    window_draw_underlying_window(UiFlags_None);

    if (g_city.victory_state.state == e_victory_state_won) {
        g_mission_won.draw(flags);
    } else {
        g_mission_lost.ui_draw_foreground(flags);
    }
}

int ui::mission_end_window::draw_background(UiFlags flags) {
    autoconfig_window &cui = getui();

    cui.format_all(&g_city);
    return cui.draw_background(flags);
}

static void advance_to_next_mission(void) {
    g_settings.set_personal_savings_for_mission(scenario_campaign_rank() + 1, g_city.kingdome.personal_savings);
    scenario_set_campaign_rank(scenario_campaign_rank() + 1);
    city_save_campaign_player_name();

    g_city.victory_state.stop_governing();

    game_undo_disable();
    game_state_reset_overlay();

    if (scenario_campaign_rank() >= 11 || scenario_is_custom()) {
        window_main_menu_show(1);
        if (!scenario_is_custom()) {
            g_settings.clear_personal_savings();
            scenario_settings_init();
            scenario_set_campaign_rank(2);
        }
    } else {
        //        scenario_set_campaign_mission(game_mission_peaceful());
        window_mission_next_selection_show();
    }
}

int ui::mission_end_window::handle_mouse(const mouse* m) {
    const hotkeys* h = hotkey_state();

    if (g_city.victory_state.state == e_victory_state_won) {
        if (input_go_back_requested(m, h)) {
            sound_music_stop();
            g_sound.speech_stop();
            advance_to_next_mission();
        }
    } else {
        generic_buttons_handle_mouse(mouse_in_dialog(m), {0, 0}, fired_buttons, 1, &focus_button_id);
    }

    return 0;
}

int ui::mission_end_window::ui_handle_mouse(const mouse *m) {
    autoconfig_window &cui = getui();
    return cui.ui_handle_mouse(m);
}

autoconfig_window &ui::mission_end_window::getui() {
    autoconfig_window &mission_won = g_mission_won;
    autoconfig_window &mission_lost = g_mission_lost;
    return (g_city.victory_state.state == e_victory_state_won) ? mission_won : mission_lost;
}

static void button_fired(int param1, int param2) {
    sound_music_stop();
    g_sound.speech_stop();
    g_city.victory_state.stop_governing();
    game_undo_disable();
    if (scenario_is_custom()) {
        window_main_menu_show(1);
    } else {
        window_mission_next_selection_show();
    }
}

static void show_end_dialog(void) {
    window_type window = {
        WINDOW_MISSION_END,
        [] (int flags) { g_mission_end.draw_background(flags); },
        [] (int flags) { g_mission_end.draw_foreground(flags); },
        [] (const mouse *m, const hotkeys *h) { g_mission_end.ui_handle_mouse(m); }
    };

    g_mission_end.init();
    window_show(&window);
}

static void show_intermezzo(void) {
    window_intermezzo_show(INTERMEZZO_WON, show_end_dialog);
}

void window_mission_end_show_won(void) {
    mouse_reset_up_state();
    if (scenario_is_mission_rank(1) || scenario_is_mission_rank(2)) {
        // tutorials: immediately go to next mission
        show_intermezzo();
    } else if (!scenario_is_custom() && scenario_campaign_rank() >= 10) {
        // Won campaign
        window_victory_video_show("smk/win_game.smk", 400, 292, show_intermezzo);
    } else {
        if (g_settings.show_victory_video())
            window_victory_video_show("smk/victory_balcony.smk", 400, 292, show_intermezzo);
        else {
            window_victory_video_show("smk/victory_senate.smk", 400, 292, show_intermezzo);
        }
    }
}
void window_mission_end_show_fired(void) {
    window_intermezzo_show(INTERMEZZO_FIRED, show_end_dialog);
}
