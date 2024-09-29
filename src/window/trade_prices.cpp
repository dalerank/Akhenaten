#include "trade_prices.h"

#include "empire/trade_prices.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/elements/panel.h"
#include "graphics/screen.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "window/advisors.h"
#include "io/gamefiles/lang.h"
#include "game/game.h"

static void draw_background() {
    window_draw_underlying_window();

    graphics_set_to_dialog();

    graphics_shade_rect(vec2i{33, 53}, vec2i{574, 334}, 0x80);
    outer_panel_draw(vec2i{16, 144}, 38, 11);
    lang_text_draw(54, 21, 26, 153, FONT_LARGE_BLACK_ON_LIGHT);
    lang_text_draw(54, 22, 26, 228, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw(54, 23, 26, 253, FONT_NORMAL_BLACK_ON_LIGHT);

    painter ctx = game.painter();
    for (int i = 1; i < 16; i++) {
        int image_offset = i + resource_image_offset(i, RESOURCE_IMAGE_ICON);
        ImageDraw::img_generic(ctx, image_id_resource_icon(image_offset), vec2i{126 + 30 * i, 194});
        text_draw_number_centered(trade_price_buy(i), 120 + 30 * i, 229, 30, FONT_SMALL_OUTLINED);
        text_draw_number_centered(trade_price_sell(i), 120 + 30 * i, 254, 30, FONT_SMALL_OUTLINED);
    }
    lang_text_draw_centered(13, 1, 16, 296, 608, FONT_NORMAL_BLACK_ON_LIGHT);

    graphics_reset_dialog();
}

static void handle_input(const mouse* m, const hotkeys* h) {
    if (input_go_back_requested(m, h))
        window_advisors_show();
}

static int get_tooltip_resource(tooltip_context* c) {
    int x_base = screen_dialog_offset_x() + 124;
    int y = screen_dialog_offset_y() + 192;
    int x_mouse = c->mpos.x;
    int y_mouse = c->mpos.y;

    for (int i = 1; i < 16; i++) {
        int x = x_base + 30 * i;
        if (x <= x_mouse && x + 24 > x_mouse && y <= y_mouse && y + 24 > y_mouse)
            return i;
    }
    return 0;
}

static void get_tooltip(tooltip_context* c) {
    int resource = get_tooltip_resource(c);
    if (!resource) {
        return;
    }

    c->text = (pcstr)lang_get_string(0, 131 + resource);
}

void window_trade_prices_show(void) {
    static window_type window = {
        WINDOW_TRADE_PRICES,
        draw_background,
        0,
        handle_input,
        get_tooltip
    };
    window_show(&window);
}
