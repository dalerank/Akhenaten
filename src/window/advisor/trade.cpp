#include "trade.h"

#include "graphics/boilerplate.h"
#include "graphics/elements/rich_text.h"
#include "graphics/elements/scrollbar.h"

#include "city/resource.h"
#include "game/resource.h"
#include "graphics/boilerplate.h"
#include "graphics/elements/generic_button.h"
#include "graphics/view/view.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "city/data_private.h"
#include "empire/empire_city.h"
#include "window/empire.h"
#include "window/resource_settings.h"
#include "window/trade_prices.h"
#include "game/game.h"

#define ADVISOR_HEIGHT 27

static void button_prices(int param1, int param2);
static void button_empire(int param1, int param2);
static void button_resource(int resource_index, int param2);

#define TRADE_BUTTON_X 20
#define TRADE_BUTTON_WIDTH 569

static generic_button resource_buttons[]
  = {{400, 398, 200, 23, button_prices, button_none, 1, 0},
     {100, 398, 200, 23, button_empire, button_none, 1, 0},
     {TRADE_BUTTON_X, 56, TRADE_BUTTON_WIDTH, 20, button_resource, button_none, 0, 0},
     {TRADE_BUTTON_X, 78, TRADE_BUTTON_WIDTH, 20, button_resource, button_none, 1, 0},
     {TRADE_BUTTON_X, 100, TRADE_BUTTON_WIDTH, 20, button_resource, button_none, 2, 0},
     {TRADE_BUTTON_X, 122, TRADE_BUTTON_WIDTH, 20, button_resource, button_none, 3, 0},
     {TRADE_BUTTON_X, 144, TRADE_BUTTON_WIDTH, 20, button_resource, button_none, 4, 0},
     {TRADE_BUTTON_X, 166, TRADE_BUTTON_WIDTH, 20, button_resource, button_none, 5, 0},
     {TRADE_BUTTON_X, 188, TRADE_BUTTON_WIDTH, 20, button_resource, button_none, 6, 0},
     {TRADE_BUTTON_X, 210, TRADE_BUTTON_WIDTH, 20, button_resource, button_none, 7, 0},
     {TRADE_BUTTON_X, 232, TRADE_BUTTON_WIDTH, 20, button_resource, button_none, 8, 0},
     {TRADE_BUTTON_X, 254, TRADE_BUTTON_WIDTH, 20, button_resource, button_none, 9, 0},
     {TRADE_BUTTON_X, 276, TRADE_BUTTON_WIDTH, 20, button_resource, button_none, 10, 0},
     {TRADE_BUTTON_X, 298, TRADE_BUTTON_WIDTH, 20, button_resource, button_none, 11, 0},
     {TRADE_BUTTON_X, 320, TRADE_BUTTON_WIDTH, 20, button_resource, button_none, 12, 0},
     {TRADE_BUTTON_X, 342, TRADE_BUTTON_WIDTH, 20, button_resource, button_none, 13, 0},
     {TRADE_BUTTON_X, 364, TRADE_BUTTON_WIDTH, 20, button_resource, button_none, 14, 0}};

static int focus_button_id;

static void on_scroll(void) {
    window_invalidate();
}
static scrollbar_type scrollbar = {590, 52, 336, on_scroll};

#define IMPORT_EXPORT_X 310

static int draw_background() {
    painter ctx = game.painter();
    city_resource_determine_available();

    outer_panel_draw(vec2i{0, 0}, 40, ADVISOR_HEIGHT);
    ImageDraw::img_generic(ctx, image_id_from_group(GROUP_ADVISOR_ICONS) + 4, 10, 10);

    lang_text_draw(54, 0, 60, 12, FONT_LARGE_BLACK_ON_LIGHT);
    int width = lang_text_get_width(54, 1, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw(54, 1, 60, 38, FONT_NORMAL_BLACK_ON_LIGHT);

    return ADVISOR_HEIGHT;
}
static void draw_foreground() {
    painter ctx = game.painter();
    inner_panel_draw(17, 52, 36, 21);
    graphics_set_clip_rectangle(20, 39, 575, 346);
    const resources_list* list = city_resource_get_available();
    for (int i = scrollbar.scroll_position; i < list->size; i++) {
        int y_offset = 22 * (i - scrollbar.scroll_position);
        e_resource resource = list->items[i];
        int image_offset = resource + resource_image_offset(resource, RESOURCE_IMAGE_ICON);
        ImageDraw::img_generic(ctx, image_id_resource_icon(image_offset), 24, y_offset + 58);

        font_t font_color = FONT_NORMAL_WHITE_ON_DARK;
        if (city_resource_is_mothballed(resource))
            font_color = FONT_NORMAL_YELLOW;

        // resource name and amount in warehouses
        lang_text_draw(23, resource, 46, y_offset + 61, font_color);
        text_draw_number_centered(
          stack_proper_quantity(city_resource_count(resource), resource), 152, y_offset + 61, 60, font_color);

        // mothballed / stockpiled
        if (city_resource_is_stockpiled(resource))
            lang_text_draw_centered(54, 3, 210, y_offset + 61, 100, font_color);
        else if (city_resource_is_mothballed(resource))
            lang_text_draw_centered(18, 5, 210, y_offset + 61, 100, FONT_NORMAL_YELLOW);

        int trade_status = city_resource_trade_status(resource);
        int trade_amount = stack_proper_quantity(city_resource_trading_amount(resource), resource);
        switch (trade_status) {
        case TRADE_STATUS_NONE: {
            bool can_import = empire_can_import_resource(resource, true);
            bool can_export = empire_can_export_resource(resource, true);
            bool could_import = empire_can_import_resource(resource, false);
            bool could_export = empire_can_export_resource(resource, false);
            if (can_import && !can_export)
                lang_text_draw(54, 31, IMPORT_EXPORT_X, y_offset + 61, font_color);
            else if (!can_import && can_export)
                lang_text_draw(54, 32, IMPORT_EXPORT_X, y_offset + 61, font_color);
            else if (can_import && can_export)
                lang_text_draw(54, 33, IMPORT_EXPORT_X, y_offset + 61, font_color);
            else if (could_import && !could_export)
                lang_text_draw(54, 34, IMPORT_EXPORT_X, y_offset + 61, FONT_NORMAL_BLACK_ON_DARK);
            else if (!could_import && could_export)
                lang_text_draw(54, 35, IMPORT_EXPORT_X, y_offset + 61, FONT_NORMAL_BLACK_ON_DARK);
            else if (could_import && could_export)
                lang_text_draw(54, 36, IMPORT_EXPORT_X, y_offset + 61, FONT_NORMAL_BLACK_ON_DARK);
            break;
        }
        case TRADE_STATUS_IMPORT: { // importing
            int width = lang_text_draw(54, 5, IMPORT_EXPORT_X, y_offset + 61, font_color);
            text_draw_number(trade_amount, '@', " ", IMPORT_EXPORT_X + width, y_offset + 61, font_color);
            break;
        }
        case TRADE_STATUS_EXPORT: { // exporting
            int width = lang_text_draw(54, 6, IMPORT_EXPORT_X, y_offset + 61, font_color);
            text_draw_number(trade_amount, '@', " ", IMPORT_EXPORT_X + width, y_offset + 61, font_color);
            break;
        }
        case TRADE_STATUS_IMPORT_AS_NEEDED:
            lang_text_draw(54, 37, IMPORT_EXPORT_X, y_offset + 61, font_color);
            break;
        case TRADE_STATUS_EXPORT_SURPLUS:
            lang_text_draw(54, 38, IMPORT_EXPORT_X, y_offset + 61, font_color);
            break;
        }

        // update/draw buttons accordingly
        if (focus_button_id - 3 == i - scrollbar.scroll_position)
            button_border_draw(TRADE_BUTTON_X, y_offset + 54, TRADE_BUTTON_WIDTH, 24, true);
        resource_buttons[i + 2 - scrollbar.scroll_position].parameter1 = i;
    }
    graphics_reset_clip_rectangle();

    // scrollbar
    inner_panel_draw(scrollbar.x + 3, scrollbar.y + 20, 2, 19);
    scrollbar.max_scroll_position = city_resource_get_available()->size - 15;
    scrollbar_draw(&scrollbar);

    // prices
    button_border_draw(98, 396, 200, 24, focus_button_id == 2);
    lang_text_draw_centered(54, 30, 100, 402, 200, FONT_NORMAL_BLACK_ON_LIGHT);

    // map
    button_border_draw(398, 396, 200, 24, focus_button_id == 1);
    lang_text_draw_centered(54, 2, 400, 402, 200, FONT_NORMAL_BLACK_ON_LIGHT);
}

static int handle_mouse(const mouse* m) {
    int num_resources = city_resource_get_available()->size;
    if (num_resources > 15)
        num_resources = 15;

    bool handled = scrollbar_handle_mouse(&scrollbar, m);
    if (handled)
        return handled;

    return generic_buttons_handle_mouse(m, 0, 0, resource_buttons, num_resources + 2, &focus_button_id);
}

static void button_prices(int param1, int param2) {
    window_trade_prices_show();
}
static void button_empire(int param1, int param2) {
    window_empire_show();
}
static void button_resource(int resource_index, int param2) {
    window_resource_settings_show(city_resource_get_available()->items[resource_index]);
}

static int get_tooltip_text(void) {
    if (focus_button_id == 1)
        return 108;
    else if (focus_button_id == 2)
        return 42;
    else if (focus_button_id)
        return 109;
    else
        return 0;
}

const advisor_window_type* window_advisor_trade(void) {
    static const advisor_window_type window = {draw_background, draw_foreground, handle_mouse, get_tooltip_text};
    return &window;
}

void window_advisor_trade_draw_dialog_background(void) {
    draw_background();
    draw_foreground();
}
