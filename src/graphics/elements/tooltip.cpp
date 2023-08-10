#include "tooltip.h"

#include "city/labor.h"
#include "city/ratings.h"
#include "core/string.h"
#include "game/settings.h"
#include "graphics/boilerplate.h"
#include "graphics/elements/lang_text.h"
#include "graphics/screen.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "grid/grid.h"
#include "io/gamefiles/lang.h"
#include "scenario/criteria.h"
#include "scenario/property.h"
#include "window/advisors.h"

#include "graphics/view/lookup.h"

#define OVERLAY_TEXT_MAX 1000

static const int DEFAULT_TEXT_GROUP = 68;
static const time_millis TOOLTIP_DELAY_MILLIS = 150;

static time_millis last_update = 0;
static uint8_t overlay_string[OVERLAY_TEXT_MAX];
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
                                   button_tooltip_info.x,
                                   button_tooltip_info.y,
                                   button_tooltip_info.width,
                                   button_tooltip_info.height);
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
    button_tooltip_info.buffer_id = graphics_save_to_texture(button_tooltip_info.buffer_id, x, y, width, height);
}

static void draw_tooltip_box(int x, int y, int width, int height) {
    graphics_draw_rect(x, y, width, height, COLOR_TOOLTIP_BORDER);
    graphics_fill_rect(x + 1, y + 1, width - 2, height - 2, COLOR_TOOLTIP_FILL);
}

static void draw_button_tooltip(tooltip_context* c) {
    const uint8_t* text = lang_get_string(c->text_group, c->text_id);

    int width = 200;
    int lines = text_measure_multiline(text, width - 5, FONT_SMALL_SHADED);
    if (lines > 2) {
        width = 300;
        lines = text_measure_multiline(text, width - 5, FONT_SMALL_SHADED);
    }
    int height = 16 * lines + 10;

    int x, y;
    if (c->mouse_x < screen_dialog_offset_x() + width + 100) {
        if (window_is(WINDOW_ADVISORS))
            x = c->mouse_x + 50;
        else
            x = c->mouse_x + 20;
    } else
        x = c->mouse_x - width - 20;

    switch (window_get_id()) {
    case WINDOW_ADVISORS:
        if (c->mouse_y < screen_dialog_offset_y() + 432) {
            y = c->mouse_y;
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
        y = c->mouse_y - 42;
        break;
    case WINDOW_DONATE_TO_CITY:
        y = c->mouse_y - 52;
        break;
    case WINDOW_LABOR_PRIORITY:
        x = c->mouse_x - width / 2 - 10;
        if (c->mouse_y < screen_dialog_offset_y() + 200)
            y = c->mouse_y + 40;
        else
            y = c->mouse_y - 72;
        break;
    default:
        if (c->mouse_y < screen_dialog_offset_y() + 200)
            y = c->mouse_y + 40;
        else
            y = c->mouse_y - 62;
        break;
    }

    save_window_under_tooltip_to_buffer(x, y, width, height);
    draw_tooltip_box(x, y, width, height);
    text_draw_multiline(text, x + 5, y + 7, width - 5, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
}
static void draw_overlay_tooltip(tooltip_context* c) {
    const uint8_t* text = lang_get_string(c->text_group, c->text_id);
    if (c->has_numeric_prefix) {
        int offset = string_from_int(overlay_string, c->numeric_prefix, 0);
        string_copy(text, &overlay_string[offset], OVERLAY_TEXT_MAX - offset);
        text = overlay_string;
    } else if (c->num_extra_values > 0) {
        string_copy(text, overlay_string, OVERLAY_TEXT_MAX);
        int offset = string_length(overlay_string);
        overlay_string[offset++] = ':';
        overlay_string[offset++] = '\n';
        for (int i = 0; i < c->num_extra_values; i++) {
            if (i) {
                overlay_string[offset++] = ',';
                overlay_string[offset++] = ' ';
            }
            const uint8_t* extra_value = lang_get_string(c->extra_value_text_groups[i], c->extra_value_text_ids[i]);
            string_copy(extra_value, &overlay_string[offset], OVERLAY_TEXT_MAX - offset);
            offset += string_length(extra_value);
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
    if (c->mouse_x < width + 20)
        x = c->mouse_x + 20;
    else {
        x = c->mouse_x - width - 20;
    }
    if (c->mouse_y < 200)
        y = c->mouse_y + 50;
    else if (c->mouse_y + height - 72 > screen_height())
        y = screen_height() - height;
    else {
        y = c->mouse_y - 72;
    }

    save_window_under_tooltip_to_buffer(x, y, width, height);
    draw_tooltip_box(x, y, width, height);
    text_draw_multiline(text, x + 5, y + 7, width - 5, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
}
static void draw_tile_tooltip(tooltip_context* c) {
    screen_tile screen = pixel_to_screentile({c->mouse_x, c->mouse_y});
    if (screen.x != -1 && screen.y != -1) {
        int grid_offset = screentile_to_mappoint(screen).grid_offset();
        city_view_set_selected_view_tile(&screen);
        int x_tile = MAP_X(grid_offset);
        int y_tile = MAP_Y(grid_offset);

        int x, y;
        int width = 60;
        int height = 40;
        if (c->mouse_x < width + 20)
            x = c->mouse_x + 20;
        else {
            x = c->mouse_x - width - 20;
        }
        if (c->mouse_y < 40)
            y = c->mouse_y + 10;
        else if (c->mouse_y + height - 32 > screen_height())
            y = screen_height() - height;
        else
            y = c->mouse_y - 32;

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
    if (c->mouse_x < width + 20)
        x = c->mouse_x + 20;
    else {
        x = c->mouse_x - width - 20;
    }
    if (c->mouse_y < 200)
        y = c->mouse_y + 10;
    else if (c->mouse_y + height - 32 > screen_height())
        y = screen_height() - height;
    else
        y = c->mouse_y - 32;

    save_window_under_tooltip_to_buffer(x, y, width, height);
    draw_tooltip_box(x, y, width, height);

    // unemployment
    lang_text_draw_colored(68, 148, x + 5, y + 5, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    width = text_draw_number_colored(
      city_labor_unemployment_percentage(), '@', "%", x + 140, y + 5, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    text_draw_number_colored(city_labor_workers_unemployed() - city_labor_workers_needed(),
                             '(',
                             ")",
                             x + 140 + width,
                             y + 5,
                             FONT_SMALL_SHADED,
                             COLOR_TOOLTIP_TEXT);

    // ratings
    lang_text_draw_colored(68, 149, x + 5, y + 19, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    text_draw_number_colored(city_rating_culture(), '@', " ", x + 140, y + 19, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    if (!scenario_is_open_play() && winning_culture()) {
        text_draw_number_colored(
          winning_culture(), '(', ")", x + 140 + width, y + 19, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    }

    lang_text_draw_colored(68, 150, x + 5, y + 33, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    text_draw_number_colored(
      city_rating_prosperity(), '@', " ", x + 140, y + 33, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    if (!scenario_is_open_play() && winning_prosperity()) {
        text_draw_number_colored(
          winning_prosperity(), '(', ")", x + 140 + width, y + 33, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    }

    lang_text_draw_colored(68, 151, x + 5, y + 47, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    text_draw_number_colored(city_rating_monument(), '@', " ", x + 140, y + 47, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    if (!scenario_is_open_play() && winning_monuments()) {
        text_draw_number_colored(
          winning_monuments(), '(', ")", x + 140 + width, y + 47, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    }

    lang_text_draw_colored(68, 152, x + 5, y + 61, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    text_draw_number_colored(city_rating_kingdom(), '@', " ", x + 140, y + 61, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    if (!scenario_is_open_play() && winning_kingdom()) {
        text_draw_number_colored(
          winning_kingdom(), '(', ")", x + 140 + width, y + 61, FONT_SMALL_SHADED, COLOR_TOOLTIP_TEXT);
    }
}

static void draw_tooltip(tooltip_context* c) {
    switch (c->type) {
    case TOOLTIP_BUTTON:
        draw_button_tooltip(c);
        break;
    case TOOLTIP_OVERLAY:
        draw_overlay_tooltip(c);
        break;
    case TOOLTIP_TILES:
        draw_tile_tooltip(c);
        break;
    case TOOLTIP_SENATE:
        draw_senate_tooltip(c);
        break;
    }
}

static bool should_draw_tooltip(tooltip_context* c) {
    if (c->type == TOOLTIP_NONE) {
        reset_timer();
        return false;
    }
    if (!c->high_priority && setting_tooltips() != TOOLTIPS_FULL) {
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
    tooltip_context context = {m->x, m->y, 0, 0, 0, 0, 0, 0};
    context.text_group = DEFAULT_TEXT_GROUP;
    if (setting_tooltips() && func)
        func(&context);

    if (should_draw_tooltip(&context)) {
        draw_tooltip(&context);
        reset_tooltip(&context);
    } else {
        restore_window_under_tooltip_from_buffer();
        button_tooltip_info.is_active = false;
    }
}
