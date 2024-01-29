#include "main_menu.h"

#include "editor/editor.h"
#include "core/log.h"
#include "config/config.h"
#include "game/game.h"
#include "game/system.h"
#include "game/settings.h"
#include "graphics/boilerplate.h"
#include "graphics/graphics.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/view/view.h"
#include "graphics/screen.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "platform/version.hpp"
#include "platform/renderer.h"
#include "records.h"
#include "sound/music.h"
#include "window/config.h"
#include "window/file_dialog.h"
#include "window/plain_message_dialog.h"
#include "window/player_selection.h"
#include "window/popup_dialog.h"
#include "window/scenario_selection.h"
#include "window/city.h"
#include "resource/icons.h"
#include "io/gamestate/boilerplate.h"

#include "js/js_game.h"

static void button_click(int type, int param2);

ANK_REGISTER_CONFIG_ITERATOR(config_load_main_menu);

struct main_menu_data : public ui::widget {
    SDL_Texture *dicord_texture = nullptr;
    SDL_Texture *patreon_texture = nullptr;
    generic_button discord_button[1] = { {0, 0, 48, 48, button_click, button_none, 10, 0} };
    generic_button patreon_button[1] = { {0, 0, 48, 48, button_click, button_none, 11, 0} };
};

main_menu_data g_main_menu_data;

void config_load_main_menu() {
    g_config_arch.r_section("main_menu_window", [] (archive arch) {
        g_main_menu_data.load(arch);
    });
}

static void draw_version_string() {
    static bstring64 version = get_version();
    int text_y = screen_height() - 30;

    // TODO: drop casts here and handle string as UTF8
    int text_width = text_get_width((const uint8_t*)version.c_str(), FONT_SMALL_PLAIN);

    if (text_y <= 500 && (screen_width() - 640) / 2 < text_width + 18) {
        graphics_draw_rect(10, text_y, text_width + 14, 20, COLOR_BLACK);
        graphics_fill_rect(11, text_y + 1, text_width + 12, 18, COLOR_WHITE);

        text_draw((const uint8_t*)version.c_str(), 18, text_y + 6, FONT_SMALL_PLAIN, COLOR_BLACK);
    } else {
        text_draw((const uint8_t*)version.c_str(), 18, text_y + 6, FONT_SMALL_PLAIN, COLOR_FONT_LIGHT_GRAY);
    }
}

static void main_menu_confirm_exit(bool accepted) {
    if (accepted) {
        system_exit();
    }
}

static void window_config_show_back() {
}

static void main_menu_draw_background() {
    painter ctx = game.painter();
    graphics_clear_screen();
    ImageDraw::img_background(ctx, image_id_from_group(GROUP_MAIN_MENU_BACKGROUND));

    g_main_menu_data["continue_game"].onclick([] (int, int) {
        pcstr last_save = config_get_string(CONFIG_STRING_LAST_SAVE);
        pcstr last_player = config_get_string(CONFIG_STRING_LAST_PLAYER);
        g_settings.set_player_name((const uint8_t *)last_player);
        if (GamestateIO::load_savegame(last_save)) {
            window_city_show();
        }
    });

    g_main_menu_data["select_player"].onclick([] (int, int) {
        window_player_selection_show();
    });

    g_main_menu_data["show_records"].onclick([] (int, int) {
        window_records_show();
    });

    g_main_menu_data["show_config"].onclick([] (int, int) {
        window_config_show(window_config_show_back);
    });

    g_main_menu_data["quit_game"].onclick([] (int, int) {
        window_popup_dialog_show(POPUP_DIALOG_QUIT, main_menu_confirm_exit, e_popup_btns_yesno);
    });

    if (window_is(WINDOW_MAIN_MENU)) {
        draw_version_string();
    }
}

static void main_menu_draw_foreground() {
    auto &data = g_main_menu_data;

    ui::begin_widget(screen_dialog_offset());
    g_main_menu_data.draw();

    painter ctx = game.painter();
    vec2i scr_size = screen_size();
    if (data.dicord_texture) {
        ctx.draw(data.dicord_texture, scr_size - vec2i(50, 50), {0, 0}, {48, 48}, 0xffffffff, 0.75f, false, true);
    }

    if (data.patreon_texture) {
        ctx.draw(data.patreon_texture, scr_size - vec2i(100, 50), {0, 0}, {48, 48}, 0xffffffff, 0.75f, false, true);
    }
}

static void button_click(int type, int param2) {
    switch (type) {

//    case 3:
//        window_scenario_selection_show(MAP_SELECTION_CUSTOM);
//        break;
//
//    case 4:
//        if (!editor_is_present() || !game_init_editor()) {
//            window_plain_message_dialog_show(TR_NO_EDITOR_TITLE, TR_NO_EDITOR_MESSAGE);
//        } else {
//            sound_music_play_editor();
//        }
//        break;


    case 10:
        platform_open_url("https://discord.gg/HS4njmBvpb", "");
        break;

    case 11:
        platform_open_url("https://www.patreon.com/imspinner", "");
        break;

    default:
        logs::error("Unknown button index");
    }
}

static void main_menu_handle_input(const mouse* m, const hotkeys* h) {
    const mouse* m_dialog = mouse_in_dialog(m);
    int tmp_button_id = 0;

    ui::handle_mouse(m);

    vec2i scr_size = screen_size();
    if (generic_buttons_handle_mouse(m, scr_size - vec2i(50, 50), g_main_menu_data.discord_button, tmp_button_id)) {
        return;
    }

    if (generic_buttons_handle_mouse(m, scr_size - vec2i(100, 50), g_main_menu_data.patreon_button, tmp_button_id)) {
        return;
    }

    if (h->escape_pressed) {
        hotkey_handle_escape();
    }

    if (h->load_file) {
        window_file_dialog_show(FILE_TYPE_SAVED_GAME, FILE_DIALOG_LOAD);
    }
}

void window_main_menu_show(bool restart_music) {
    auto &data = g_main_menu_data;
    if (restart_music) {
        sound_music_play_intro();
    }

    if (!data.dicord_texture) {
        data.dicord_texture = load_icon_texture("discord");
    }

    if (!data.patreon_texture) {
        data.patreon_texture = load_icon_texture(":patreon_48.png");
    }

    window_type window = {
        WINDOW_MAIN_MENU,
        main_menu_draw_background,
        main_menu_draw_foreground,
        main_menu_handle_input
    };

    window_show(&window);
}
