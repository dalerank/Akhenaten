#include "logo_screen.h"

#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/window.h"
#include "game/game_config.h"
#include "sound/sound.h"
#include "window/main_menu.h"
#include "window/plain_message_dialog.h"
#include "window/autoconfig_window.h"
#include "game/game.h"
#include "core/core.h"

#include <cmath>

struct logo_screen : autoconfig_window_t<logo_screen> {
    virtual int handle_mouse(const mouse *m) override { return 0; }
    
    virtual void draw_foreground(UiFlags flags) override;
    virtual void ui_draw_foreground(UiFlags flags) override {}
    virtual int get_tooltip_text() override { return 0; }
    virtual int ui_handle_mouse(const mouse *m) override;
    virtual void init() override {};
};

logo_screen g_logo_screen;

void logo_screen::draw_foreground(UiFlags) {
    graphics_clear_screen();
    painter ctx = game.painter();

    ImageDraw::img_background(ctx, image_id_from_group(GROUP_LOGO));

    static int logo_tick_count = 0;
    graphics_set_to_dialog();
    int current_color = 128 + std::cos(logo_tick_count * 0.03f) * 128;
    logo_tick_count++;
    lang_text_draw_centered_colored(13, 7, 160, 462, 320, FONT_SMALL_PLAIN, (0xff000000 + (current_color << 16) + (current_color << 8) + current_color));
    graphics_reset_dialog();
}

int logo_screen::ui_handle_mouse(const mouse *m){
    if (m->left.went_up || m->right.went_up) {
        main_menu_screen::show(/*restart_music*/false);
        return 0;
    }

    const hotkeys *h = hotkey_state();
    if (h->escape_pressed) {
        hotkey_handle_escape();
    }

    return 0;
}

void window_logo_show(int show_patch_message) {
    static window_type window = {
        WINDOW_LOGO,
        [] (int f) { g_logo_screen.draw_background(f); } ,
        [] (int f) { g_logo_screen.draw_foreground(f); } ,
        [] (auto m, auto h) { g_logo_screen.ui_handle_mouse(m); }
    };

    g_sound.play_intro(); // play menu track
    window_show(&window);

    if (show_patch_message == MESSAGE_MISSING_FONTS) {
        window_plain_message_dialog_show("#TR_MISSING_FONTS_TITLE", "#TR_MISSING_FONTS_MESSAGE", SOURCE_LOCATION);
    }

    if (!!game_features::gameui_show_intro_video) {
        //        window_intro_video_show();
    }
}
