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

#define OVERLAY_TEXT_MAX 1000

static const int DEFAULT_TEXT_GROUP = 68;
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
    if (c->type != TOOLTIP_NONE)
        c->type = TOOLTIP_NONE;
}

static void restore_window_under_tooltip_from_buffer(void) {
    if (button_tooltip_info.is_active) {
        graphics_draw_from_texture(button_tooltip_info.buffer_id,
                                   vec2i{button_tooltip_info.x, button_tooltip_info.y},
                                   vec2i{button_tooltip_info.width, button_tooltip_info.height});
    }
}

static void save_window_under_tooltip_to_buffer(int x, int y, int width, int height) {
    if (button_tooltip_info.is_active && x == button_tooltip_info.x && y == button_tooltip_info.y
        && width == button_tooltip_info.width && height == button_tooltip_info.height)
        return;
    restore_window_under_tooltip_from_buffer();
    button_tooltip_info.is_active = true;
    button_tooltip_info.x = x;
    button_tooltip_info.y = y;
    button_tooltip_info.width = width;
    button_tooltip_info.height = height;
    button_tooltip_info.buffer_id = graphics_save_to_texture(button_tooltip_info.buffer_id, {x, y}, {width, height});
}

static void draw_tooltip_box(int x, int y, int width, int height) {
    graphics_draw_rect(vec2i{x, y}, vec2i{width, height}, COLOR_TOOLTIP_BORDER);
    graphics_fill_rect(vec2i{x + 1, y + 1}, vec2i{width - 2, height - 2}, COLOR_TOOLTIP_FILL);
}

static void draw_button_tooltip(tooltip_context* c) {
    if (!c->text.empty()) {
        return;
    }

    int width = 200;
    int lines = text_measure_multiline(c->text, width - 5, FONT_SMALL_SHADED);
    if (lines > 2) {
        width = 300;
        lines = text_measure_multiline(c->text, width - 5, FONT_SMALL_SHADED);
    }

    int height = 16 * lines + 10;
    int x, y;
    if (c->mpos.x < screen_dialog_offset_x() + width + 100) {
        if (window_is(WINDOW_ADVISORS))
            x = c->mpos.x + 50;
        else
            x = c->mpos.x + 20;
    } else {
        x = c->mpos.x - width - 20;
    }

    switch (window_get_id()) {
    case WINDOW_ADVISORS:
        if (c->mpos.y < screen_dialog_offset_y() + 432) {
            y = c->mpos.y;
            switch (window_advisors_get_advisor()) {
            case ADVISOR_LABOR:
                y -= 74;
                break;
            case ADVISOR_TRADE:
                y -= 54;
                break;
            case ADVISOR_POPULATION:
                y -= 58;
                break;
            default:
                y -= 64;
                break;
            }
        } else
            y = screen_dialog_offset_y() + 432;
        break;
    case WINDOW_TRADE_PRICES: // FIXED used to cause ghosting
        y = c->mpos.y - 42;
        break;
    case WINDOW_DONATE_TO_CITY:
        y = c->mpos.y - 52;
        break;
    case WINDOW_LABOR_PRIORITY:
        x = c->mpos.x - width / 2 - 10;
        if (c->mpos.y < screen_dialog_offset_y() + 200)
            y = c->mpos.y + 40;
        else
            y = c->mpos.y - 72;
        break;
    default:
        if (c->mpos.y < screen_dialog_offset_y() + 200)
            y = c->mpos.y + 40;
        else
            y = c->mpos.y - 62;
        break;
    }

    //save_window_under_tooltip_to_buffer(x, y, width, height);
    draw_tooltip_box(x, y, width, height);
    text_draw_multiline(c->text, x + 5, y + 7, width - 5, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
}

static void draw_overlay_tooltip(tooltip_context* c) {
    bstring1024 text = c->text.c_str();
    overlay_string.clear();
    if (c->has_numeric_prefix) {
        string_from_int((uint8_t*)overlay_string, c->numeric_prefix, 0);
        overlay_string.append(text);
        text = overlay_string;
    } else if (c->num_extra_values > 0) {
        text = overlay_string;
        int offset = text.len();
        overlay_string[offset++] = ':';
        overlay_string[offset++] = '\n';
        for (int i = 0; i < c->num_extra_values; i++) {
            if (i) {
                overlay_string[offset++] = ',';
                overlay_string[offset++] = ' ';
            }
            pcstr extra_value = (pcstr)lang_get_string(c->extra_value_text_groups[i], c->extra_value_text_ids[i]);
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
    if (c->mpos.x < width + 20)
        x = c->mpos.x + 20;
    else {
        x = c->mpos.x - width - 20;
    }
    if (c->mpos.y < 200)
        y = c->mpos.y + 50;
    else if (c->mpos.y + height - 72 > screen_height())
        y = screen_height() - height;
    else {
        y = c->mpos.y - 72;
    }

    //save_window_under_tooltip_to_buffer(x, y, width, height);
    draw_tooltip_box(x, y, width, height);
    text_draw_multiline(text, x + 5, y + 7, width - 5, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
}
static void draw_tile_tooltip(tooltip_context* c) {
    screen_tile screen = pixel_to_screentile({c->mpos.x, c->mpos.y});
    if (screen.x != -1 && screen.y != -1) {
        int grid_offset = screentile_to_mappoint(screen).grid_offset();
        city_view_set_selected_view_tile(&screen);
        int x_tile = MAP_X(grid_offset);
        int y_tile = MAP_Y(grid_offset);

        int x, y;
        int width = 60;
        int height = 40;
        if (c->mpos.x < width + 20)
            x = c->mpos.x + 20;
        else {
            x = c->mpos.x - width - 20;
        }
        if (c->mpos.y < 40)
            y = c->mpos.y + 10;
        else if (c->mpos.y + height - 32 > screen_height())
            y = screen_height() - height;
        else
            y = c->mpos.y - 32;

        save_window_under_tooltip_to_buffer(x, y, width, height);
        draw_tooltip_box(x, y, width, height);
        text_draw_label_and_number("x: ", x_tile, " ", x + 2, y + 5, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
        text_draw_label_and_number("y: ", y_tile, " ", x + 2, y + 19, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    }
}
static void draw_senate_tooltip(tooltip_context* c) {
    int x, y;
    int width = 220;
    int height = 80;

    if (c->mpos.x < width + 20)
        x = c->mpos.x + 20;
    else {
        x = c->mpos.x - width - 20;
    }

    if (c->mpos.y < 200) {
        y = c->mpos.y + 10;
    } else if (c->mpos.y + height - 32 > screen_height()) {
        y = screen_height() - height;
    } else {
        y = c->mpos.y - 32;
    }

    //save_window_under_tooltip_to_buffer(x, y, width, height);
    draw_tooltip_box(x, y, width, height);

    // unemployment
    lang_text_draw_colored(e_text_senate_tooltip, e_text_senate_tooltip_unemployed, x + 5, y + 5, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    width = text_draw_number_colored(g_city.labor.unemployment_percentage, '@', "%", x + 140, y + 5, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    text_draw_number_colored(g_city.labor.workers_unemployed - g_city.labor.workers_needed, '(', ")", x + 140 + width, y + 5, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);

    // ratings
    lang_text_draw_colored(e_text_senate_tooltip, e_text_senate_tooltip_culture, x + 5, y + 19, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    text_draw_number_colored(g_city.ratings.culture, '@', " ", x + 140, y + 19, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    if (!scenario_is_open_play() && winning_culture()) {
        text_draw_number_colored(winning_culture(), '(', ")", x + 140 + width, y + 19, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    }

    lang_text_draw_colored(e_text_senate_tooltip, e_text_senate_tooltip_prosperity, x + 5, y + 33, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    text_draw_number_colored(g_city.ratings.prosperity, '@', " ", x + 140, y + 33, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);

    if (!scenario_is_open_play() && winning_prosperity()) {
        text_draw_number_colored(winning_prosperity(), '(', ")", x + 140 + width, y + 33, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    }

    lang_text_draw_colored(e_text_senate_tooltip, e_text_senate_tooltip_monuments, x + 5, y + 47, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    text_draw_number_colored(g_city.ratings.monument, '@', " ", x + 140, y + 47, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    if (!scenario_is_open_play() && winning_monuments()) {
        text_draw_number_colored(winning_monuments(), '(', ")", x + 140 + width, y + 47, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    }

    lang_text_draw_colored(e_text_senate_tooltip, e_text_senate_tooltip_kingdom, x + 5, y + 61, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    text_draw_number_colored(g_city.ratings.kingdom, '@', " ", x + 140, y + 61, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    if (!scenario_is_open_play() && winning_kingdom()) {
        text_draw_number_colored(winning_kingdom(), '(', ")", x + 140 + width, y + 61, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    }
}

static void draw_tooltip(tooltip_context* c) {
    switch (c->type) {
    case TOOLTIP_BUTTON: draw_button_tooltip(c); break;
    case TOOLTIP_OVERLAY: draw_overlay_tooltip(c); break;
    case TOOLTIP_TILES: draw_tile_tooltip(c); break;
    case TOOLTIP_SENATE: draw_senate_tooltip(c); break;
    }
}

static bool should_draw_tooltip(tooltip_context* c) {
    if (c->type == TOOLTIP_NONE) {
        reset_timer();
        return false;
    }
    if (!c->high_priority && g_settings.tooltips != e_tooltip_show_full) {
        reset_timer();
        return false;
    }
    if (time_get_millis() - last_update < TOOLTIP_DELAY_MILLIS) // delay drawing tooltip
        return false;
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

    const tooltip_context &uitooltip = ui::get_tooltip();
    if (uitooltip.type) {
        context.set(uitooltip.type, uitooltip.text);
    }

    if (should_draw_tooltip(&context)) {
        draw_tooltip(&context);
        reset_tooltip(&context);
    } else {
        restore_window_under_tooltip_from_buffer();
        button_tooltip_info.is_active = false;
    }
}

void tooltip_context::set(int t, textid tx) { 
    type = t;
    text = (pcstr)lang_get_string(tx);
}

void tooltip_context::set(int t, pcstr tx) {
    type = t;
    text = tx;
}
