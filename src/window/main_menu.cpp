#include "main_menu.h"

#include "editor/editor.h"
#include "core/log.h"
#include "game/game.h"
#include "game/system.h"
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
#include "resource/icons.h"

static void button_click(int type, int param2);

#define MAX_BUTTONS 4
#define BUTTONS_X 192
#define BUTTONS_Y 125
#define BUTTONS_WIDTH 256
#define BUTTONS_HEIGHT 25

struct main_menu_data_t {
    int focus_button_id;

    generic_button buttons[MAX_BUTTONS] = {
        {BUTTONS_X, BUTTONS_Y + 40 * 0, BUTTONS_WIDTH, BUTTONS_HEIGHT, button_click, button_none, 1, 0},
        {BUTTONS_X, BUTTONS_Y + 40 * 1, BUTTONS_WIDTH, BUTTONS_HEIGHT, button_click, button_none, 2, 0},
        {BUTTONS_X, BUTTONS_Y + 40 * 2, BUTTONS_WIDTH, BUTTONS_HEIGHT, button_click, button_none, 3, 0},
        {BUTTONS_X, BUTTONS_Y + 40 * 3, BUTTONS_WIDTH, BUTTONS_HEIGHT, button_click, button_none, 4, 0},
    };

    SDL_Texture *dicord_texture = nullptr;
    SDL_Texture *patreon_texture = nullptr;
    generic_button discord_button = {0, 0, 48, 48, button_click, button_none, 10, 0};
    generic_button patreon_button = {0, 0, 48, 48, button_click, button_none, 11, 0};
};

main_menu_data_t g_main_menu_data;

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

    int groups[6][2] = {
      {30, 0},
      {30, 5}, //{1, 3},
               //                    {30, 3},
               //                    {9,  8},
      {2, 0},
      {30, 4},
    };

    for (int i = 0; i < 4; i++) {
        large_label_draw(data.buttons[i].x, data.buttons[i].y, data.buttons[i].width / 16, data.focus_button_id == i + 1 ? 1 : 0);
        lang_text_draw_centered(groups[i][0], groups[i][1], BUTTONS_X, BUTTONS_Y + 40 * i + 6, BUTTONS_WIDTH, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    graphics_reset_dialog();

    painter ctx = game.painter();
    vec2i scr_size = screen_size();
    if (data.dicord_texture) {
        graphics_renderer()->draw_image(ctx, data.dicord_texture, scr_size.x - 50, scr_size.y - 50, {0, 0}, {48, 48}, 0xffffffff, 0.75f, false);
    }

    if (data.patreon_texture) {
        graphics_renderer()->draw_image(ctx, data.patreon_texture, scr_size.x - 100, scr_size.y - 50, {0, 0}, {48, 48}, 0xffffffff, 0.75f, false);
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
    if (generic_buttons_handle_mouse(m_dialog, 0, 0, data.buttons, MAX_BUTTONS, &data.focus_button_id)) {
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
