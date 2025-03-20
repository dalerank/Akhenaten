#include "mission_end.h"

#include "city/city.h"
#include "city/finance.h"
#include "city/city_population.h"
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

ui::window_mission_end g_mission_end;
ui::window_mission_won g_mission_won;
ui::window_mission_lost g_mission_lost;

void ui::window_mission_lost::init() {
    ui["replay_mission"].onclick([] {
        g_city_planner.reset();
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

int ui::window_mission_won::ui_handle_mouse(const mouse *m) {
    const hotkeys *h = hotkey_state();
    if (input_go_back_requested(m, h)) {
        sound_music_stop();
        g_sound.speech_stop();
        advance_to_next_mission();
        return 0;
    }

    return 0;
}

void ui::window_mission_won::init() {
    ui["subtitle"] = scenario_is_custom() ? textid{ 147, 20 } : textid{ 147, (uint8_t)scenario_campaign_scenario_id() };
}

void ui::window_mission_won::advance_to_next_mission() {
    const int next_mission_rank = scenario_campaign_rank() + 1;

    g_settings.set_personal_savings_for_mission(next_mission_rank, g_city.kingdome.personal_savings);
    scenario_set_campaign_rank(next_mission_rank);
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
        int next_mission = g_scenario_data.win_criteria.next_mission;
        if (!next_mission) {
            next_mission = scenario_campaign_scenario_id() + 1;
        }
        ui::mission_choice_window::show(next_mission);
    }
}

autoconfig_window &ui::window_mission_end::getui() {
    autoconfig_window &mission_won = g_mission_won;
    autoconfig_window &mission_lost = g_mission_lost;
    return (g_city.victory_state.state == e_victory_state_won) ? mission_won : mission_lost;
}

//static void button_fired(int param1, int param2) {
//    sound_music_stop();
//    g_sound.speech_stop();
//    g_city.victory_state.stop_governing();
//    game_undo_disable();
//    if (scenario_is_custom()) {
//        window_main_menu_show(1);
//    } else {
//        window_mission_next_selection_show();
//    }
//}

static void show_end_dialog(void) {
    window_type window = {
        WINDOW_MISSION_END,
        [] (int flags) {  
            auto &ui = g_mission_end.getui();
            ui.format_all(&g_city);
            ui.draw_background(flags);
        },
        [] (int flags) { 
            window_draw_underlying_window(UiFlags_None);

            auto &ui = g_mission_end.getui();
            ui.ui_draw_foreground(flags); 
        },
        [] (const mouse *m, const hotkeys *h) {
            auto &ui = g_mission_end.getui();
            ui.ui_handle_mouse(m); 
        }
    };

    auto &ui = g_mission_end.getui();
    ui.init();

    window_show(&window);
}

static void show_intermezzo() {
    int scenario_id = scenario_campaign_scenario_id();
    window_intermezzo_show(scenario_id, INTERMEZZO_WON, show_end_dialog);
}

void ui::window_mission_won::show() {
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

void window_mission_end_show_fired() {
    int scenario_id = scenario_campaign_scenario_id();
    window_intermezzo_show(scenario_id, INTERMEZZO_FIRED, show_end_dialog);
}