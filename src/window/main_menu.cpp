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

struct main_menu_data_t {
    int focus_button_id;

    vec2i button_pos;
    vec2i button_size;
    int button_offset;

    SDL_Texture *dicord_texture = nullptr;
    SDL_Texture *patreon_texture = nullptr;
    generic_button discord_button = {0, 0, 48, 48, button_click, button_none, 10, 0};
    generic_button patreon_button = {0, 0, 48, 48, button_click, button_none, 11, 0};
    std::vector<std::pair<int, int>> buttons_text;

    std::vector<generic_button> make_buttons() {
        std::vector<generic_button> buttons = {
            {(short)button_pos.x, (short)button_pos.y + (short)button_offset * 0, (short)button_size.x, (short)button_size.y, button_click, button_none, 5, 0},
            {(short)button_pos.x, (short)button_pos.y + (short)button_offset * 1, (short)button_size.x, (short)button_size.y, button_click, button_none, 1, 0},
            {(short)button_pos.x, (short)button_pos.y + (short)button_offset * 2, (short)button_size.x, (short)button_size.y, button_click, button_none, 2, 0},
            {(short)button_pos.x, (short)button_pos.y + (short)button_offset * 3, (short)button_size.x, (short)button_size.y, button_click, button_none, 3, 0},
            {(short)button_pos.x, (short)button_pos.y + (short)button_offset * 4, (short)button_size.x, (short)button_size.y, button_click, button_none, 4, 0},
        };

        return buttons;
    }
};

main_menu_data_t g_main_menu_data;
void config_load_main_menu(archive arch) {
    arch.load_global_section("main_menu_window", [] (archive arch) {
        auto &data = g_main_menu_data;
        data.button_pos.x = arch.read_integer("x_pos");
        data.button_pos.y = arch.read_integer("y_pos");
        data.button_size.x = arch.read_integer("btn_width");
        data.button_size.y = arch.read_integer("btn_height");
        data.button_offset = arch.read_integer("button_offset");

        data.buttons_text.clear();
        arch.read_object_array("buttons", [&] (archive arch) {
            int group = arch.read_integer("group");
            int id = arch.read_integer("id");
            data.buttons_text.push_back({group, id});
        });
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
        // TODO: drop casts here and handle string as UTF8
        text_draw((const uint8_t*)version.c_str(), 18, text_y + 6, FONT_SMALL_PLAIN, COLOR_BLACK);
    } else {
        // TODO: drop casts here and handle string as UTF8
        text_draw((const uint8_t*)version.c_str(), 18, text_y + 6, FONT_SMALL_PLAIN, COLOR_FONT_LIGHT_GRAY);
    }
}

static void draw_background() {
    painter ctx = game.painter();
    graphics_clear_screen();
    ImageDraw::img_background(ctx, image_id_from_group(GROUP_MAIN_MENU_BACKGROUND));

    if (window_is(WINDOW_MAIN_MENU)) {
        draw_version_string();
    }
}

static void draw_foreground() {
    auto &data = g_main_menu_data;
    graphics_set_to_dialog();

    auto buttons = data.make_buttons();
    for (int i = 0; i < buttons.size(); i++) {
        auto text = data.buttons_text[i];
        large_label_draw(buttons[i].x, buttons[i].y, buttons[i].width / 16, data.focus_button_id == i + 1 ? 1 : 0);
        lang_text_draw_centered(text.first, text.second, data.button_pos.x, data.button_pos.y + 40 * i + 6, data.button_size.x, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    graphics_reset_dialog();

    painter ctx = game.painter();
    vec2i scr_size = screen_size();
    if (data.dicord_texture) {
        ctx.draw(data.dicord_texture, scr_size.x - 50, scr_size.y - 50, {0, 0}, {48, 48}, 0xffffffff, 0.75f, false);
    }

    if (data.patreon_texture) {
        ctx.draw(data.patreon_texture, scr_size.x - 100, scr_size.y - 50, {0, 0}, {48, 48}, 0xffffffff, 0.75f, false);
    }
}

static void window_config_show_back() {
}

static void confirm_exit(bool accepted) {
    if (accepted) {
        system_exit();
    }
}

static void button_click(int type, int param2) {
    switch (type) {
    case 1:
        window_player_selection_show();
        break;

    case 2:
        window_records_show(); // TODO
        break;

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

    case 3:
        window_config_show(window_config_show_back);
        break;

    case 4:
        window_popup_dialog_show(POPUP_DIALOG_QUIT, confirm_exit, e_popup_btns_yesno);
        break;

    case 5: {
            pcstr last_save = config_get_string(CONFIG_STRING_LAST_SAVE);
            pcstr last_player = config_get_string(CONFIG_STRING_LAST_PLAYER);
            g_settings.set_player_name((const uint8_t*)last_player);
            if (GamestateIO::load_savegame(last_save)) {
                window_city_show();
            }
        }
        break;

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

static void handle_input(const mouse* m, const hotkeys* h) {
    auto &data = g_main_menu_data;
    const mouse* m_dialog = mouse_in_dialog(m);
    auto buttons = data.make_buttons();
    if (generic_buttons_handle_mouse(m_dialog, 0, 0, buttons.data(), buttons.size(), &data.focus_button_id)) {
        return;
    }

    vec2i scr_size = screen_size();
    if (generic_buttons_handle_mouse(m, scr_size.x - 50, scr_size.y - 50, &data.discord_button, 1, nullptr)) {
        return;
    }

    if (generic_buttons_handle_mouse(m, scr_size.x - 100, scr_size.y - 50, &data.patreon_button, 1, nullptr)) {
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
        draw_background,
        draw_foreground,
        handle_input
    };

    window_show(&window);
}
