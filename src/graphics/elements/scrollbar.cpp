#include "scrollbar.h"

#include "core/calc.h"
#include "graphics/graphics.h"
#include "graphics/elements/image_button.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "game/game.h"

#define SCROLL_BUTTON_HEIGHT 26
#define SCROLL_BUTTON_WIDTH 39
#define SCROLL_DOT_SIZE 25
#define TOTAL_BUTTON_HEIGHT (2 * SCROLL_BUTTON_HEIGHT + SCROLL_DOT_SIZE)

static void text_scroll(int is_down, int num_lines);

static image_button image_button_scroll_up = {0, 0, SCROLL_BUTTON_WIDTH, SCROLL_BUTTON_HEIGHT, IB_SCROLL, GROUP_OK_CANCEL_SCROLL_BUTTONS, 8, text_scroll, button_none, 0, 1, 1};
static image_button image_button_scroll_down = {0, 0, SCROLL_BUTTON_WIDTH, SCROLL_BUTTON_HEIGHT, IB_SCROLL, GROUP_OK_CANCEL_SCROLL_BUTTONS, 12, text_scroll, button_none, 1, 1, 1};
static image_button image_button_scroll_up_thin = {0, 0, SCROLL_BUTTON_WIDTH, SCROLL_BUTTON_HEIGHT, IB_SCROLL, GROUP_SYSTEM_GRAPHICS, 15, text_scroll, button_none, 0, 1, 1};
static image_button image_button_scroll_down_thin = {0, 0, SCROLL_BUTTON_WIDTH, SCROLL_BUTTON_HEIGHT, IB_SCROLL, GROUP_SYSTEM_GRAPHICS, 17, text_scroll, button_none, 1, 1, 1};

static scrollbar_t* g_scrollbar_current;

void scrollbar_t::init(int position, int max_position) {
    if (max_position < 0)
        max_position = 0;

    scroll_position = calc_bound(position, 0, max_position);
    max_scroll_position = max_position;
    is_dragging_scroll = 0;
}

void scrollbar_reset(scrollbar_t* scrollbar, int scroll_position) {
    scrollbar->scroll_position = scroll_position;
    scrollbar->is_dragging_scroll = 0;
}

void scrollbar_update_max(scrollbar_t* scrollbar, int max_scroll_position) {
    if (max_scroll_position < 0)
        max_scroll_position = 0;

    scrollbar->max_scroll_position = max_scroll_position;
    if (scrollbar->scroll_position > max_scroll_position)
        scrollbar->scroll_position = max_scroll_position;
}

void scrollbar_draw(vec2i offset, scrollbar_t* scrollbar) {
    painter ctx = game.painter();
    if (scrollbar->max_scroll_position > 0 || scrollbar->always_visible) {
        if (!scrollbar->thin) {
            image_buttons_draw(scrollbar->pos + offset, &image_button_scroll_up, 1);
            image_buttons_draw(offset + scrollbar->pos + vec2i{0, scrollbar->height - SCROLL_BUTTON_HEIGHT}, &image_button_scroll_down, 1);
        } else {
            image_buttons_draw(scrollbar->pos + offset, &image_button_scroll_up_thin, 1);
            image_buttons_draw(offset + scrollbar->pos + vec2i{0, scrollbar->height - SCROLL_BUTTON_HEIGHT}, &image_button_scroll_down_thin, 1);
        }

        int pct;
        if (scrollbar->scroll_position <= 0) { pct = 0; }
        else if (scrollbar->scroll_position >= scrollbar->max_scroll_position) { pct = 100; }
        else { pct = calc_percentage(scrollbar->scroll_position, scrollbar->max_scroll_position); }

        int drag_offset = calc_adjust_with_percentage(scrollbar->height - TOTAL_BUTTON_HEIGHT - 2 * scrollbar->dot_padding, pct);
        if (scrollbar->is_dragging_scroll) {
            drag_offset = scrollbar->scroll_position_drag;
        }

        ImageDraw::img_generic(ctx, image_id_from_group(GROUP_PANEL_BUTTON) + 39, offset + scrollbar->pos + vec2i{ (SCROLL_BUTTON_WIDTH - SCROLL_DOT_SIZE) / 2, drag_offset + SCROLL_BUTTON_HEIGHT + scrollbar->dot_padding });
    }
}

static bool handle_scrollbar_dot(vec2i offset, scrollbar_t* scrollbar, const mouse* m) {
    if (scrollbar->max_scroll_position <= 0 || !m->left.is_down) {
        return false;
    }

    int track_height = scrollbar->height - TOTAL_BUTTON_HEIGHT - 2 * scrollbar->dot_padding;
    if (m->x < scrollbar->pos.x || m->x >= scrollbar->pos.x + SCROLL_BUTTON_WIDTH) {
        return false;
    }

    if (m->y < scrollbar->pos.y + SCROLL_BUTTON_HEIGHT + scrollbar->dot_padding
        || m->y > scrollbar->pos.y + scrollbar->height - SCROLL_BUTTON_HEIGHT - scrollbar->dot_padding) {
        return false;
    }

    int dot_offset = m->y - scrollbar->pos.y - SCROLL_DOT_SIZE / 2 - SCROLL_BUTTON_HEIGHT;
    dot_offset = std::clamp(dot_offset, 0, track_height);

    int pct_scrolled = calc_percentage(dot_offset, track_height);
    scrollbar->scroll_position = calc_adjust_with_percentage(scrollbar->max_scroll_position, pct_scrolled);
    scrollbar->is_dragging_scroll = 1;
    scrollbar->scroll_position_drag = dot_offset;
    if (scrollbar->scroll_position_drag < 0) {
        scrollbar->scroll_position_drag = 0;
    }

    if (scrollbar->on_scroll_callback) {
        scrollbar->on_scroll_callback();
    }

    return true;
}

int scrollbar_handle_mouse(vec2i offset, scrollbar_t* scrollbar, const mouse* m) {
    if (scrollbar->max_scroll_position <= 0) {
        return 0;
    }

    g_scrollbar_current = scrollbar;
    if (m->scrolled == SCROLL_DOWN) {
        text_scroll(1, 3);
    } else if (m->scrolled == SCROLL_UP) {
        text_scroll(0, 3);
    }

    int tmp_btn_id;
    if (!scrollbar->thin) {
        if (image_buttons_handle_mouse(m, scrollbar->pos + offset, &image_button_scroll_up, 1, &tmp_btn_id))
            return 1;

        if (image_buttons_handle_mouse(m, scrollbar->pos + offset + vec2i{0, scrollbar->height - SCROLL_BUTTON_HEIGHT}, &image_button_scroll_down, 1, &tmp_btn_id))
            return 1;

    } else {
        if (image_buttons_handle_mouse(m, scrollbar->pos + offset, &image_button_scroll_up_thin, 1, &tmp_btn_id))
            return 1;

        if (image_buttons_handle_mouse(m, scrollbar->pos + offset + vec2i{0, scrollbar->height - SCROLL_BUTTON_HEIGHT}, &image_button_scroll_down_thin, 1, &tmp_btn_id))
            return 1;
    }

    return handle_scrollbar_dot(offset, scrollbar, m);
}

static void text_scroll(int is_down, int num_lines) {
    scrollbar_t* scrollbar = g_scrollbar_current;
    scrollbar->scroll_position = std::clamp(scrollbar->scroll_position + (is_down ? num_lines : -num_lines), 0, scrollbar->max_scroll_position);
    scrollbar->is_dragging_scroll = 0;

    if (scrollbar->on_scroll_callback) {
        scrollbar->on_scroll_callback();
    }

    if (scrollbar->_onscroll) {
        scrollbar->_onscroll();
    }
}
