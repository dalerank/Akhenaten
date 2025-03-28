#include "main_menu.h"

#include "editor/editor.h"
#include "core/log.h"
#include "platform/platform.h"
#include "graphics/elements/ui.h"
#include "graphics/graphics.h"
#include "graphics/window.h"
#include "graphics/screen.h"
#include "graphics/image.h"
#include "game/game.h"
#include "game/settings.h"
#include "game/game_config.h"
#include "core/app.h"
#include "js/js_game.h"
#include "window/records.h"
#include "window/popup_dialog.h"
#include "window/player_selection.h"
#include "window/file_dialog.h"
#include "window/config.h"
#include "window/window_city.h"
#include "sound/music.h"
#include "io/gamestate/boilerplate.h"
#include "resource/icons.h"

ui::widget g_main_menu_data;

ANK_REGISTER_CONFIG_ITERATOR(config_load_main_menu);
void config_load_main_menu() {
    g_config_arch.r_section("main_menu_window", [] (archive arch) {
        g_main_menu_data.load(arch);
    });
}

static void main_menu_draw_background(int) {
    graphics_clear_screen();

    auto &ui = g_main_menu_data;
    ui["continue_game"].onclick([] {
        const xstring last_save = g_ankh_config.get(CONFIG_STRING_LAST_SAVE);
        const xstring last_player = g_ankh_config.get(CONFIG_STRING_LAST_PLAYER);
        g_settings.set_player_name((const uint8_t *)last_player.c_str());
        if (GamestateIO::load_savegame(last_save.c_str())) {
            window_city_show();
        }
    });

    ui["select_player"].onclick([] {
        window_player_selection_show(); 
    });

    ui["show_records"].onclick([] {
        window_records_show();
    });

    ui["show_config"].onclick([] {
        window_config_show([] {
        
        });
    });

    ui["quit_game"].onclick([] { 
        popup_dialog::show_yesno("#popup_dialog_quit", [] {
            app_request_exit(); 
        });
    });

    ui["discord"].onclick([] {
        platform_open_url("https://discord.gg/HS4njmBvpb", "");
    });

    ui["patreon"].onclick([] {
        platform_open_url("https://www.patreon.com/imspinner", "");
    });
}

void main_menu_draw_foreground(int) {
    auto &ui = g_main_menu_data;

    ui.begin_frame();
    ui.draw();
}

void main_menu_handle_input(const mouse* m, const hotkeys* h) {
    ui::handle_mouse(m);

    if (h->escape_pressed) {
        popup_dialog::show_yesno("#popup_dialog_quit", [] {
            app_request_exit();
        });
    }

    if (h->load_file) {
        window_file_dialog_show(FILE_TYPE_SAVED_GAME, FILE_DIALOG_LOAD);
    }
}

void window_main_menu_show(bool restart_music) {
    if (restart_music) {
        sound_music_play_intro();
    }

    static window_type window = {
        WINDOW_MAIN_MENU,
        main_menu_draw_background,
        main_menu_draw_foreground,
        main_menu_handle_input
    };

    window_show(&window);
}
