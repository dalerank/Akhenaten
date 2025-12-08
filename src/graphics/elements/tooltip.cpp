#include "tooltip.h"

#include "city/city.h"
#include "city/ratings.h"
#include "core/bstring.h"
#include "game/settings.h"
#include "graphics/graphics.h"
#include "graphics/elements/lang_text.h"
#include "graphics/screen.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "grid/grid.h"
#include "io/gamefiles/lang.h"
#include "scenario/criteria.h"
#include "scenario/scenario.h"
#include "window/advisors.h"

#include "graphics/view/lookup.h"
#include "city/constants.h"

static const time_millis TOOLTIP_DELAY_MILLIS = 150;

static time_millis last_update = 0;
static bstring1024 overlay_string;

struct button_tooltip_data_t {
    bool is_active;
    int x;
    int y;
    int width;
    int height;
    int buffer_id;
};

button_tooltip_data_t button_tooltip_info;

static void reset_timer(void) {
    last_update = time_get_millis();
}
static void reset_tooltip(tooltip_context* c) {
    c->_drawtooltip = nullptr;
    c->text = "";
}

void tooltip_context::draw_box(int x, int y, int width, int height) {
    graphics_draw_rect(vec2i{x, y}, vec2i{width, height}, COLOR_TOOLTIP_BORDER);
    ui::fill_rect(vec2i{x + 1, y + 1}, vec2i{width - 2, height - 2}, COLOR_TOOLTIP_FILL);
}

void tooltip_context::draw_button_tooltip() {
    if (text.empty()) {
        return;
    }

    int width = 200;
    int lines = text_measure_multiline((const uint8_t *)text.c_str(), width - 5, FONT_SMALL_SHADED);
    if (lines > 2) {
        width = 300;
        lines = text_measure_multiline((const uint8_t*)text.c_str(), width - 5, FONT_SMALL_SHADED);
    }

    int height = 16 * lines + 10;
    int x, y;
    if (mpos.x < screen_dialog_offset_x() + width + 100) {
        if (window_is(WINDOW_ADVISORS))
            x = mpos.x + 50;
        else
            x = mpos.x + 20;
    } else {
        x = mpos.x - width - 20;
    }

    switch (window_get_id()) {
    case WINDOW_TRADE_PRICES: // FIXED used to cause ghosting
        y = mpos.y - 42;
        break;
    case WINDOW_DONATE_TO_CITY:
        y = mpos.y - 52;
        break;
    case WINDOW_LABOR_PRIORITY:
        x = mpos.x - width / 2 - 10;
        if (mpos.y < screen_dialog_offset_y() + 200)
            y = mpos.y + 40;
        else
            y = mpos.y - 72;
        break;
    default:
        if (mpos.y < screen_dialog_offset_y() + 200)
            y = mpos.y + 40;
        else
            y = mpos.y - 62;
        break;
    }

    //save_window_under_tooltip_to_buffer(x, y, width, height);
    draw_box(x, y, width, height);
    text_draw_multiline(text, { x + 5, y + 7 }, width - 5, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
}

void tooltip_context::draw_overlay_tooltip() {
    bstring1024 text;  // Default-initialize (empty) [web:8][web:11]
    overlay_string.clear();
    if (has_numeric_prefix) {
        string_from_int((uint8_t*)overlay_string, numeric_prefix, 0);
        overlay_string.append(text);
        text = overlay_string;
    } else if (num_extra_values > 0) {
        text = overlay_string;
        size_t offset = text.len();
        overlay_string[offset++] = ':';
        overlay_string[offset++] = '\n';
        for (int i = 0; i < num_extra_values; i++) {
            if (i) {
                overlay_string[offset++] = ',';
                overlay_string[offset++] = ' ';
            }
            pcstr extra_value = (pcstr)lang_get_string(extra_value_text_groups[i], extra_value_text_ids[i]);
            overlay_string.append(extra_value);
        }
        text = overlay_string;
    }

    int width = 200;
    int lines = text_measure_multiline(text, width - 5, FONT_SMALL_SHADED);
    if (lines > 2) {
        width = 300;
        lines = text_measure_multiline(text, width - 5, FONT_SMALL_SHADED);
    }
    int height = 16 * lines + 10;

    int x, y;
    if (mpos.x < width + 20)
        x = mpos.x + 20;
    else {
        x = mpos.x - width - 20;
    }
    if (mpos.y < 200)
        y = mpos.y + 50;
    else if (mpos.y + height - 72 > screen_height())
        y = screen_height() - height;
    else {
        y = mpos.y - 72;
    }

    draw_box(x, y, width, height);
    text_draw_multiline(text.c_str(), { x + 5, y + 7 }, width - 5, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
}


void tooltip_context::draw_tile_tooltip() {
    screen_tile screen = pixel_to_screentile({mpos.x, mpos.y});
    if (screen.x != -1 && screen.y != -1) {
        int grid_offset = screen_to_tile(screen).grid_offset();
        city_view_set_selected_view_tile(&screen);
        int x_tile = MAP_X(grid_offset);
        int y_tile = MAP_Y(grid_offset);

        int x, y;
        int width = 60;
        int height = 40;
        if (mpos.x < width + 20)
            x = mpos.x + 20;
        else {
            x = mpos.x - width - 20;
        }
        if (mpos.y < 40)
            y = mpos.y + 10;
        else if (mpos.y + height - 32 > screen_height())
            y = screen_height() - height;
        else
            y = mpos.y - 32;

        draw_box(x, y, width, height);
        text_draw_label_and_number("x: ", x_tile, " ", x + 2, y + 5, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
        text_draw_label_and_number("y: ", y_tile, " ", x + 2, y + 19, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    }
}

void tooltip_context::draw_tooltip() {
    if (_drawtooltip) {
        _drawtooltip();
    } else {
        draw_button_tooltip();
    }
}

bool tooltip_context::should_draw_tooltip() {
    if (!text) {
        reset_timer();
        return false;
    }

    if (!high_priority && g_settings.tooltips != e_tooltip_show_full) {
        reset_timer();
        return false;
    }

    if (time_get_millis() - last_update < TOOLTIP_DELAY_MILLIS) { // delay drawing tooltip
        return false;
    }

    return true;
}

void tooltip_invalidate(void) {
    button_tooltip_info.is_active = false;
}

void tooltip_handle(const mouse* m, void (*func)(tooltip_context*)) {
    if (m->is_touch && !m->left.is_down) {
        reset_timer();
        return;
    }

    static tooltip_context context;
    context.mpos = *m;
    context.text = "";
    if (g_settings.tooltips && func) {
        func(&context);
    }

    if (!context.text) {
        const tooltip_context &uitooltip = ui::get_tooltip();
        context.text = uitooltip.text;
    }

    if (context.should_draw_tooltip()) {
        context.draw_tooltip();
        reset_tooltip(&context);
    } else {
        button_tooltip_info.is_active = false;
    }
}

void tooltip_context::set(int t, textid tx) { 
    text = (pcstr)lang_get_string(tx);
}

void tooltip_context::set(int t, pcstr tx) {
    text = tx;
}

void tooltip_context::set(int t, const xstring &tx) {
    text = tx;
}
