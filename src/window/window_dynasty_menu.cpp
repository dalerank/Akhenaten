#include "window_dynasty_menu.h"

#include "window_city.h"
#include "file_dialog.h"
#include "message_dialog.h"
#include "player_selection.h"
#include "scenario_selection.h"

#include "game/mission.h"
#include "game/settings.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/generic_button.h"
#include "graphics/view/view.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "io/gamefiles/lang.h"
#include "io/gamestate/boilerplate.h"
#include "io/manager.h"
#include "game/player.h"
#include "game/game.h"

#include "graphics/elements/ui.h"

ui::window_dinasty_menu g_dinasty_menu;

void ui::window_dinasty_menu::init() {
    autoconfig_window::init();

    string_copy(g_settings.player_name, player_name, MAX_PLAYER_NAME);
    text_tag_substitution tags[] = {{"[player_name]", (pcstr)player_name}};
    text_fill_in_tags((pcstr)lang_get_string(293, 5), player_name_title, tags);

    player_data_load(player_name);

    last_autosave = player_get_last_autosave();
    if (strcmp(last_autosave, "") == 0 || !vfs::file_exists(last_autosave)) {
        to_begin_history = true;
    } else {
        to_begin_history = false;
    }
    // in OG pharaoh, the "load save" button doesn't appear if there are no saves
    has_saved_games = true;

    ui["title"] = (pcstr)player_name_title;
    ui["btnresume"] = ui::str(293, to_begin_history ? 7 : 0);

    ui["btnresume"].onclick([this] {
        if (to_begin_history) {
            GamestateIO::load_mission(SCENARIO_NUBT, true);
            return;
        } 
        
        const bool ok = GamestateIO::load_savegame(last_autosave);
        if (ok) {
            window_city_show();
        }
    });

    ui["btnexplore"].onclick([] {
        window_scenario_selection_show(MAP_SELECTION_CAMPAIGN);
    });

    ui["btnload"].onclick([] {
        window_file_dialog_load_show(FILE_TYPE_SAVED_GAME);
    });

    ui["btncustom"].onclick([] {
        window_scenario_selection_show(MAP_SELECTION_CUSTOM);
    });

    ui["btnback"].onclick([] {
        window_player_selection_init();
        window_player_selection_show();
    });
}

void ui::window_dinasty_menu::ui_draw_foreground(UiFlags flag) {
    ui.begin_widget(pos);

    ui.draw();

    ui.end_widget();
}

int ui::window_dinasty_menu::ui_handle_mouse(const mouse *m) {
    int result = autoconfig_window::ui_handle_mouse(m);

    //mouse_button |= !!generic_buttons_handle_mouse(m_dialog, {0, 0}, &language_button, 1, &data.language_focus_button);

    const hotkeys *h = hotkey_state();
    if (input_go_back_requested(m, h)) {
        window_player_selection_init();
        window_player_selection_show();
    }

    return 0;
}

void ui::window_dinasty_menu::show() {
    static window_type window = {
        WINDOW_GAME_SELECTION,
        [] (int flags) { g_dinasty_menu.draw_background(flags); },
        [] (int flags) { g_dinasty_menu.ui_draw_foreground(flags); },
        [] (auto m, auto h) { g_dinasty_menu.ui_handle_mouse(m); }
    };
    g_dinasty_menu.init();
    window_show(&window);
}