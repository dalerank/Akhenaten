#include "widget_top_menu_game.h"

#include "js/js_game.h"
#include "window/popup_dialog.h"
#include "window/window_city.h"
#include "window/file_dialog_load.h"
#include "window/file_dialog_save.h"
#include "window/window_dynasty_menu.h"
#include "city/city.h"
#include "building/construction/build_planner.h"
#include "game/undo.h"
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