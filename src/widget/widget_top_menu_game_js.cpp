#include "widget_top_menu_game.h"

#include "js/js_game.h"
#include "window/popup_dialog.h"
#include "window/window_city.h"
#include "window/file_dialog_load.h"
#include "window/file_dialog_save.h"
#include "window/file_dialog_delete.h"
#include "window/main_menu.h"
#include "window/window_dynasty_menu.h"
#include "window/display_options.h"
#include "window/sound_options.h"
#include "window/speed_options.h"
#include "window/hotkey_config.h"
#include "window/difficulty_options.h"
#include "window/window_features.h"
#include "city/city.h"
#include "building/construction/build_planner.h"
#include "game/undo.h"
#include "game/settings.h"
#include "io/gamestate/boilerplate.h"

pcstr __widget_top_menu_new_game(int, int) {
    widget_top_menu_clear_state();
    popup_dialog::show_yesno("#popup_dialog_quit", [] (bool confirmed) {
        if (!confirmed) {
            window_city_show();
            return;
        }

        g_city_planner.reset();
        game_undo_disable();
        g_city.reset_overlay();
        ui::window_dinasty_menu::show();
    });

    return "";
}
ANK_FUNCTION_2(__widget_top_menu_new_game)

pcstr __widget_top_menu_replay_map(int, int) {
    widget_top_menu_clear_state();
    popup_dialog::show_yesno("#replay_mission", [] (bool confirmed) {
        if (!confirmed) {
            window_city_show();
            return;
        }

        g_city_planner.reset();
        const bool is_custom_map = (g_scenario.mode() != e_scenario_normal);
        if (is_custom_map) {
            GamestateIO::load_savegame("autosave_replay.svx");
            window_city_show();
        } else {
            int scenario_id = g_scenario.campaign_scenario_id();
            widget_top_menu_clear_state();
            GamestateIO::load_mission(scenario_id, true);
        }
    });

    return "";
}
ANK_FUNCTION_2(__widget_top_menu_replay_map)

pcstr __widget_top_menu_load_map(int, int) {
    widget_top_menu_clear_state();
    g_city_planner.reset();
    window_city_show();
    window_file_dialog_load_show(FILE_TYPE_SAVED_GAME);

    return "";
}
ANK_FUNCTION_2(__widget_top_menu_load_map)

pcstr __widget_top_menu_save_map(int, int) {
    widget_top_menu_clear_state();
    window_city_show();
    window_file_dialog_save_show(FILE_TYPE_SAVED_GAME);

    return "";
}
ANK_FUNCTION_2(__widget_top_menu_save_map)

pcstr __widget_top_menu_delete_map(int, int) {
    widget_top_menu_clear_state();
    window_city_show();
    window_file_dialog_delete_show(FILE_TYPE_SAVED_GAME);

    return "";
}
ANK_FUNCTION_2(__widget_top_menu_delete_map)

pcstr __widget_top_menu_exit_game(int, int) {
    widget_top_menu_clear_state();
    popup_dialog::show_yesno("#popup_dialog_quit", [] (bool accepted) {
        if (accepted) {
            widget_top_menu_clear_state();
            main_menu_screen::show(/*restart_music*/true);
        } else {
            window_city_show();
        }
    });

    return "";
}
ANK_FUNCTION_2(__widget_top_menu_exit_game)

pcstr __widget_top_menu_display_options(int, int) {
    widget_top_menu_clear_state();
    ui::display_options_window::show(window_city_show);

    return "";
}
ANK_FUNCTION_2(__widget_top_menu_display_options)

pcstr __widget_top_menu_sound_options(int, int) {
    widget_top_menu_clear_state();
    window_sound_options_show(window_city_show);
    return "";
}
ANK_FUNCTION_2(__widget_top_menu_sound_options)

pcstr __widget_top_menu_speed_options(int, int) {
    widget_top_menu_clear_state();
    window_speed_options_show(window_city_show);
    return "";
}
ANK_FUNCTION_2(__widget_top_menu_speed_options)

pcstr __widget_top_menu_difficulty_options(int, int) {
    widget_top_menu_clear_state();
    window_difficulty_options_show(window_city_show);
    return "";
}
ANK_FUNCTION_2(__widget_top_menu_difficulty_options)

pcstr __widget_top_menu_hotkeys_options(int, int) {
    window_hotkey_config_show([] {});
    return "";
}
ANK_FUNCTION_2(__widget_top_menu_hotkeys_options)

pcstr __widget_top_menu_features(int, int) {
    ui::window_features::show([] {});
    return "";
}
ANK_FUNCTION_2(__widget_top_menu_features)