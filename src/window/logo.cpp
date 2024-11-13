#include "logo.h"

#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/window.h"
#include "config/config.h"
#include "sound/music.h"
#include "window/main_menu.h"
#include "window/plain_message_dialog.h"
#include "game/game.h"

#include <cmath>


static void init() {
    sound_music_play_intro();
}

static void draw_logo_background(int) {
    graphics_clear_screen();
    painter ctx = game.painter();

    ImageDraw::img_background(ctx, image_id_from_group(GROUP_LOGO));
}

static void draw_logo_foreground(int) {
    static int logo_tick_count = 0;
    graphics_set_to_dialog();
    int current_color = 128 + std::cos(logo_tick_count * 0.03f) * 128;
    logo_tick_count++;
    lang_text_draw_centered_colored(13, 7, 160, 462, 320, FONT_SMALL_PLAIN, (0xff000000 + (current_color << 16) + (current_color << 8) + current_color));
    graphics_reset_dialog();
}

static void handle_input(const mouse* m, const hotkeys* h) {
    if (m->left.went_up || m->right.went_up) {
        window_main_menu_show(0);
        return;
    }

    if (h->escape_pressed) {
        hotkey_handle_escape();
    }
}

void window_logo_show(int show_patch_message) {
    window_type window = {
        WINDOW_LOGO,
        draw_logo_background,
        draw_logo_foreground,
        handle_input
    };

    init(); // play menu track
    window_show(&window);

    if (show_patch_message == MESSAGE_MISSING_PATCH) {
        window_plain_message_dialog_show(TR_NO_PATCH_TITLE, TR_NO_PATCH_MESSAGE);
    } else if (show_patch_message == MESSAGE_MISSING_FONTS) {
        window_plain_message_dialog_show(TR_MISSING_FONTS_TITLE, TR_MISSING_FONTS_MESSAGE);
    }

    if (config_get(CONFIG_UI_SHOW_INTRO_VIDEO)) {
        //        window_intro_video_show();
    }
}
