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

#include "graphics/view/lookup.h"
#include "city/constants.h"

static const time_millis TOOLTIP_DELAY_MILLIS = 150;

static time_millis last_update = 0;

void tooltip_context::reset_timer(void) {
    last_update = time_get_millis();
}

void tooltip_context::reset() {
    _drawtooltip = nullptr;
    text = "";
}

void tooltip_context::draw_box(int x, int y, int width, int height) {
    graphics_draw_rect(vec2i{x, y}, vec2i{width, height}, COLOR_TOOLTIP_BORDER);
    ui::fill_rect(vec2i{x + 1, y + 1}, vec2i{width - 2, height - 2}, COLOR_TOOLTIP_FILL);
}

void tooltip_context::draw_tooltip_impl() {
    if (text.empty()) {
        return;
    }

    bstring1024 ptext = text.c_str();
    const bool need_localize = ptext.find('$') >= 0;
    if (need_localize) {
        ui_scope_property holder;
        ptext = ui::format(&holder, text.c_str());
    }

    int width = 200;
    int lines = text_measure_multiline(ptext, width - 5, FONT_SMALL_SHADED);
    if (lines > 2) {
        width = 300;
        lines = text_measure_multiline(ptext, width - 5, FONT_SMALL_SHADED);
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
    text_draw_multiline(ptext.c_str(), { x + 5, y + 7 }, width - 5, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
}

void tooltip_context::draw_overlay_tooltip() {
    bstring1024 overlay_string;
    if (has_numeric_prefix) {
        overlay_string.printf("%d%s", numeric_prefix, text.c_str());
        text = overlay_string;
    } else if (num_extra_values > 0) {
        text = overlay_string;
        size_t offset = text.size();
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
    int lines = text_measure_multiline(text.c_str(), width - 5, FONT_SMALL_SHADED);
    if (lines > 2) {
        width = 300;
        lines = text_measure_multiline(text.c_str(), width - 5, FONT_SMALL_SHADED);
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
        draw_tooltip_impl();
    }
}

bool tooltip_context::should_draw_tooltip() {
    if (!text) {
        reset_timer();
        return false;
    }

    if (!high_priority && g_settings.tooltips_mode != e_tooltip_mode_full) {
        reset_timer();
        return false;
    }

    if (time_get_millis() - last_update < TOOLTIP_DELAY_MILLIS) { // delay drawing tooltip
        return false;
    }

    return true;
}

void tooltip_handle(const mouse* m, void (*func)(tooltip_context*)) {
    static tooltip_context context;
    if (m->is_touch && !m->left.is_down) {
        context.reset_timer();
        return;
    }

    context.mpos = *m;
    context.text = "";
    if (g_settings.tooltips_mode && func) {
        func(&context);
    }

    if (!context.text) {
        const tooltip_context &uitooltip = ui::get_tooltip();
        context.text = uitooltip.text;
    }

    if (context.should_draw_tooltip()) {
        context.draw_tooltip();
        context.reset();
    }
}

void tooltip_context::set(int t, textid tx) { 
    text = lang_get_string(tx);
}

void tooltip_context::set(int t, pcstr tx) {
    text = tx;
}

void tooltip_context::set(int t, const xstring &tx) {
    text = tx;
}
