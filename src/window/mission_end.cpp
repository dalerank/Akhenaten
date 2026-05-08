#include "mission_end.h"

#include "city/city.h"
#include "city/city_finance.h"
#include "city/city_population.h"
#include "city/ratings.h"
#include "city/victory.h"
#include "game/mission.h"
#include "game/game_config.h"
#include "game/state.h"
#include "game/game.h"
#include "game/undo.h"
#include "graphics/graphics.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "game/game_events.h"
#include "scenario/scenario.h"
#include "sound/music.h"
#include "sound/sound.h"
#include "window/intermezzo.h"
#include "window/main_menu.h"
#include "window/victory_video.h"
#include "window/autoconfig_window.h"
#include "js/js.h"
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
        const bool is_custom_map = (g_scenario.mode() != e_scenario_normal);
        if (is_custom_map) {
            GamestateIO::load_savegame("autosave_replay.sav");
            window_city_show();
        } else {
            widget_top_menu_clear_state();
            GamestateIO::load_mission(g_scenario.campaign_scenario_id, true);
        }
    });
}

int ui::window_mission_won::ui_handle_mouse(const mouse *m) {
    const hotkeys *h = hotkey_state();
    if (input_go_back_requested(m, h)) {
        g_sound.music_stop();
        g_sound.speech_stop();
        advance_to_next_mission();
        return 0;
    }

    return 0;
}

void ui::window_mission_won::init() {
    const bool is_custom_map = (g_scenario.mode() != e_scenario_normal);
    ui["subtitle"] = is_custom_map ? textid{ 147, 20 } : textid{ 147, (uint8_t)g_scenario.campaign_scenario_id };
}

void ui::window_mission_won::advance_to_next_mission() {
    const int next_mission_rank = g_scenario.settings.campaign_mission_rank + 1;

    const int completed_scenario_id = g_scenario.campaign_scenario_id;
    const uint16_t savings = g_city.kingdome.personal_savings;
    const bool is_custom_map = (g_scenario.mode() != e_scenario_normal);

    int next_scenario_id = -1;
    if (!is_custom_map && next_mission_rank < 11) {
        next_scenario_id = g_scenario.win_criteria.next_mission;
        if (!next_scenario_id) {
            next_scenario_id = completed_scenario_id + 1;
        }
    }

    // remember savings so the next campaign mission (or a replay) can restore them
    if (!is_custom_map) {
        g_city.kingdome.campaign_carry_personal_savings = savings;
    }

    events::emit(event_mission_won{ completed_scenario_id, next_scenario_id });
    events::process();
    // all events are processed at this point

    g_scenario.set_campaign_rank(next_mission_rank);
    city_save_campaign_player_name();

    g_city.victory_state.stop_governing();

    game_undo_disable();
    g_city.reset_overlay();

    if (g_scenario.settings.campaign_mission_rank >= 11 || is_custom_map) {
        main_menu_screen::show(/*restart_music*/true);
        if (!is_custom_map) {
            g_scenario.init();
            g_scenario.set_campaign_rank(2);
        }
    } else {
        js_vm_exec_function_args("game_show_mission_choice", "i", next_scenario_id);
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
        "window_mission_end",
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

void window_mission_show_intermezzo() {
    window_intermezzo_show(g_scenario.campaign_scenario_id, INTERMEZZO_WON, show_end_dialog);
}

void ui::window_mission_won::show() {
    mouse::ref().reset_up_state();

    if (!g_scenario.meta.hide_won_screen) {
        window_mission_show_intermezzo();
        return;
    } 
    
    const bool is_custom_map = (g_scenario.mode() != e_scenario_normal);
    if (!is_custom_map && g_scenario.settings.campaign_mission_rank >= 10) {
        // Won campaign
        window_victory_video_show("smk/win_game.smk", 400, 292, window_mission_show_intermezzo);
        return;
    } 
    
    game_features::gameopt_victory_video.set(!game_features::gameopt_victory_video.to_bool());
    if (game_features::gameopt_victory_video.to_bool()) {
        window_victory_video_show("smk/victory_balcony.smk", 400, 292, window_mission_show_intermezzo);
        return;
    }
    
    window_victory_video_show("smk/victory_senate.smk", 400, 292, window_mission_show_intermezzo);
}

void window_mission_end_show_fired() {
    const int scenario_id = g_scenario.campaign_scenario_id;
    window_intermezzo_show(scenario_id, INTERMEZZO_FIRED, show_end_dialog);
}