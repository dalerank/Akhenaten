#include "window_gift_to_kingdome.h"

#include "city/city.h"
#include "game/resource.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/view/view.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "window/advisors.h"
#include "game/game.h"

static void button_set_gift(int gift_id, int param2);
static void button_send_gift(int param1, int param2);
static void button_cancel(int param1, int param2);

static generic_button buttons[] = {
  {208, 213, 300, 20, button_set_gift, button_none, 1, 0},
  {208, 233, 300, 20, button_set_gift, button_none, 2, 0},
  {208, 253, 300, 20, button_set_gift, button_none, 3, 0},
  {118, 336, 260, 20, button_send_gift, button_none, 0, 0},
  {400, 336, 160, 20, button_cancel, button_none, 0, 0},
};

static int focus_button_id;

static void window_gift_to_kingdome_init(void) {
    g_city.kingdome.init_selected_gift();
}

static void window_gift_to_kingdome_draw_background() {
    window_advisors_draw_dialog_background();

    graphics_set_to_dialog();

    outer_panel_draw(vec2i{96, 144}, 30, 15);
    painter ctx = game.painter();
    ImageDraw::img_generic(ctx, image_id_resource_icon(RESOURCE_DEBEN), vec2i{112, 160});
    lang_text_draw_centered(52, 69, 144, 160, 416, FONT_LARGE_BLACK_ON_LIGHT);

    int width = lang_text_draw(52, 50, 144, 304, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw_amount(8, 4, g_city.kingdome.months_since_gift, 144 + width, 304, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw_centered(13, 4, 400, 341, 160, FONT_NORMAL_BLACK_ON_LIGHT);

    graphics_reset_dialog();
}

static void window_gift_to_kingdome_draw_foreground(void) {
    graphics_set_to_dialog();

    inner_panel_draw(112, 208, 28, 5);

    if (g_city.kingdome.can_send_gift(GIFT_MODEST)) {
        const auto* gift = g_city.kingdome.get_gift(GIFT_MODEST);
        lang_text_draw(52, 63, 128, 218, FONT_NORMAL_WHITE_ON_DARK);
        e_font font = focus_button_id == 1 ? FONT_NORMAL_YELLOW : FONT_NORMAL_WHITE_ON_DARK;
        int width = lang_text_draw(52, 51 + gift->id, 224, 218, font);
        text_draw_money(gift->cost, 224 + width, 218, font);
    } else {
        lang_text_draw_multiline(52, 70, vec2i{160, 224}, 352, FONT_NORMAL_WHITE_ON_DARK);
    }
    if (g_city.kingdome.can_send_gift(GIFT_GENEROUS)) {
        const auto* gift = g_city.kingdome.get_gift(GIFT_GENEROUS);
        lang_text_draw(52, 64, 128, 238, FONT_NORMAL_WHITE_ON_DARK);
        e_font font = focus_button_id == 2 ? FONT_NORMAL_YELLOW : FONT_NORMAL_WHITE_ON_DARK;
        int width = lang_text_draw(52, 55 + gift->id, 224, 238, font);
        text_draw_money(gift->cost, 224 + width, 238, font);
    }
    if (g_city.kingdome.can_send_gift(GIFT_LAVISH)) {
        const auto* gift = g_city.kingdome.get_gift(GIFT_LAVISH);
        lang_text_draw(52, 65, 128, 258, FONT_NORMAL_WHITE_ON_DARK);
        e_font font = focus_button_id == 3 ? FONT_NORMAL_YELLOW : FONT_NORMAL_WHITE_ON_DARK;
        int width = lang_text_draw(52, 59 + gift->id, 224, 258, font);
        text_draw_money(gift->cost, 224 + width, 258, font);
    }
    // can give at least one type
    if (g_city.kingdome.can_send_gift(GIFT_MODEST)) {
        lang_text_draw_centered(52, 66 + g_city.kingdome.selected_gift_size, 118, 341, 260, FONT_NORMAL_BLACK_ON_LIGHT);
        button_border_draw(118, 336, 260, 20, focus_button_id == 4);
    }
    button_border_draw(400, 336, 160, 20, focus_button_id == 5);

    graphics_reset_dialog();
}

static void window_gift_to_kingdome_handle_input(const mouse* m, const hotkeys* h) {
    if (generic_buttons_handle_mouse(mouse_in_dialog(m), 0, 0, buttons, 5, &focus_button_id))
        return;
    if (input_go_back_requested(m, h))
        window_advisors_show();
}

static void button_set_gift(int gift_id, int param2) {
    if (g_city.kingdome.set_gift_size(gift_id - 1))
        window_invalidate();
}

static void button_send_gift(int param1, int param2) {
    if (g_city.kingdome.can_send_gift(GIFT_MODEST)) {
        g_city.kingdome.send_gift();
        window_advisors_show();
    }
}

static void button_cancel(int param1, int param2) {
    window_advisors_show();
}

void window_gift_to_kingdome_show(void) {
    window_type window = {
        WINDOW_GIFT_TO_EMPEROR,
        window_gift_to_kingdome_draw_background,
        window_gift_to_kingdome_draw_foreground,
        window_gift_to_kingdome_handle_input
    };
    window_gift_to_kingdome_init();
    window_show(&window);
}
