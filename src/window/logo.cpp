#include "logo.h"

#include "graphics/boilerplate.h"
#include "graphics/elements/lang_text.h"
#include "graphics/window.h"
#include "io/config/config.h"
#include "sound/music.h"
#include "window/main_menu.h"
#include "window/plain_message_dialog.h"

static void init(void) {
    sound_music_play_intro();
}
static void draw_logo(void) {
    graphics_clear_screen();

    ImageDraw::img_background(image_id_from_group(GROUP_LOGO));
    graphics_set_to_dialog();
    lang_text_draw_centered_colored(13, 7, 160, 462, 320, FONT_SMALL_PLAIN, COLOR_WHITE);
    graphics_reset_dialog();
}
static void handle_input(const mouse* m, const hotkeys* h) {
    if (m->left.went_up || m->right.went_up) {
        window_main_menu_show(0);
        return;
    }
    if (h->escape_pressed)
        hotkey_handle_escape();
}
void window_logo_show(int show_patch_message) {
    window_type window = {WINDOW_LOGO, draw_logo, 0, handle_input};
    init(); // play menu track
    window_show(&window);
    if (show_patch_message == MESSAGE_MISSING_PATCH)
        window_plain_message_dialog_show(TR_NO_PATCH_TITLE, TR_NO_PATCH_MESSAGE);
    else if (show_patch_message == MESSAGE_MISSING_FONTS)
        window_plain_message_dialog_show(TR_MISSING_FONTS_TITLE, TR_MISSING_FONTS_MESSAGE);

    if (config_get(CONFIG_UI_SHOW_INTRO_VIDEO)) {
        //        window_intro_video_show();
    }
}
