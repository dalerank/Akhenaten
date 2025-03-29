#include "select_list.h"

#include "graphics/color.h"
#include "graphics/elements/button.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"

#define MAX_ITEMS_PER_LIST 20

enum E_MODE {
    MODE_TEXT,
    MODE_GROUP,
};

static void select_item(int id, int list_id);

static generic_button buttons_list1[MAX_ITEMS_PER_LIST] = {
  {5, 8, 190, 18, select_item, button_none, 0, 0},    {5, 28, 190, 18, select_item, button_none, 1, 0},
  {5, 48, 190, 18, select_item, button_none, 2, 0},   {5, 68, 190, 18, select_item, button_none, 3, 0},
  {5, 88, 190, 18, select_item, button_none, 4, 0},   {5, 108, 190, 18, select_item, button_none, 5, 0},
  {5, 128, 190, 18, select_item, button_none, 6, 0},  {5, 148, 190, 18, select_item, button_none, 7, 0},
  {5, 168, 190, 18, select_item, button_none, 8, 0},  {5, 188, 190, 18, select_item, button_none, 9, 0},
  {5, 208, 190, 18, select_item, button_none, 10, 0}, {5, 228, 190, 18, select_item, button_none, 11, 0},
  {5, 248, 190, 18, select_item, button_none, 12, 0}, {5, 268, 190, 18, select_item, button_none, 13, 0},
  {5, 288, 190, 18, select_item, button_none, 14, 0}, {5, 308, 190, 18, select_item, button_none, 15, 0},
  {5, 328, 190, 18, select_item, button_none, 16, 0}, {5, 348, 190, 18, select_item, button_none, 17, 0},
  {5, 368, 190, 18, select_item, button_none, 18, 0}, {5, 388, 190, 18, select_item, button_none, 19, 0},
};

static generic_button buttons_list2[MAX_ITEMS_PER_LIST] = {
  {205, 8, 190, 18, select_item, button_none, 0, 1},    {205, 28, 190, 18, select_item, button_none, 1, 1},
  {205, 48, 190, 18, select_item, button_none, 2, 1},   {205, 68, 190, 18, select_item, button_none, 3, 1},
  {205, 88, 190, 18, select_item, button_none, 4, 1},   {205, 108, 190, 18, select_item, button_none, 5, 1},
  {205, 128, 190, 18, select_item, button_none, 6, 1},  {205, 148, 190, 18, select_item, button_none, 7, 1},
  {205, 168, 190, 18, select_item, button_none, 8, 1},  {205, 188, 190, 18, select_item, button_none, 9, 1},
  {205, 208, 190, 18, select_item, button_none, 10, 1}, {205, 228, 190, 18, select_item, button_none, 11, 1},
  {205, 248, 190, 18, select_item, button_none, 12, 1}, {205, 268, 190, 18, select_item, button_none, 13, 1},
  {205, 288, 190, 18, select_item, button_none, 14, 1}, {205, 308, 190, 18, select_item, button_none, 15, 1},
  {205, 328, 190, 18, select_item, button_none, 16, 1}, {205, 348, 190, 18, select_item, button_none, 17, 1},
  {205, 368, 190, 18, select_item, button_none, 18, 1}, {205, 388, 190, 18, select_item, button_none, 19, 1},
};

struct select_list_t {
    int x;
    int y;
    int mode;
    int group;
    custom_span<xstring> items;
    void (*callback)(int);
    int focus_button_id;
};

select_list_t g_select_list;

static void init_group(int x, int y, int group, int num_items, void (*callback)(int)) {
    auto &data = g_select_list;
    data.x = x;
    data.y = y;
    data.mode = MODE_GROUP;
    data.group = group;
    //data.items = items;
    data.callback = callback;
}

static void init_text(int x, int y, const custom_span<xstring> &items, void (*callback)(int)) {
    auto &data = g_select_list;
    data.x = x;
    data.y = y;
    data.mode = MODE_TEXT;
    data.items = items;
    data.callback = callback;
}

static void draw_item(int item_id, int x, int y, int selected) {
    auto &data = g_select_list;

    if (data.items[item_id].empty()) {
        return;
    }

    color color = selected ? COLOR_FONT_BLUE : COLOR_BLACK;
    if (data.mode == MODE_GROUP)
        lang_text_draw_centered_colored(data.group, item_id, data.x + x, data.y + y, 190, FONT_SMALL_PLAIN, color);
    else {
        text_draw_centered((uint8_t*)data.items[item_id].c_str(), data.x + x, data.y + y, 190, FONT_SMALL_PLAIN, color);
    }
}

static void draw_foreground(int) {
    auto &data = g_select_list;
    assert(data.items.size() <= MAX_ITEMS_PER_LIST);
    //if (data.num_items > MAX_ITEMS_PER_LIST) {
    //    int max_first = items_in_first_list();
    //    outer_panel_draw(vec2i{data.x, data.y}, 26, (20 * max_first + 24) / 16);
    //    for (int i = 0; i < max_first; i++) {
    //        draw_item(i, 5, 11 + 20 * i, i + 1 == data.focus_button_id);
    //    }
    //    for (int i = 0; i < data.num_items - max_first; i++) {
    //        draw_item(i + max_first, 205, 11 + 20 * i, MAX_ITEMS_PER_LIST + i + 1 == data.focus_button_id);
    //    }
    //} else 
    {
        outer_panel_draw(vec2i{data.x, data.y}, 13, (20 * data.items.size() + 24) / 16);
        for (int i = 0; i < data.items.size(); i++) {
            draw_item(i, 5, 11 + 20 * i, i + 1 == data.focus_button_id);
        }
    }
}

static void handle_input(const mouse* m, const hotkeys* h) {
    auto &data = g_select_list;
    assert(data.items.size() <= MAX_ITEMS_PER_LIST);
    //if (data.num_items > MAX_ITEMS_PER_LIST) {
    //    int items_first = items_in_first_list();
    //    if (generic_buttons_handle_mouse(m, {data.x, data.y}, buttons_list1, items_first, &data.focus_button_id))
    //        return;
    //    int second_id = 0;
    //    generic_buttons_handle_mouse(m, {data.x, data.y}, buttons_list2, data.num_items - items_first, &second_id);
    //    if (second_id > 0)
    //        data.focus_button_id = second_id + MAX_ITEMS_PER_LIST;
    //
    //} else 
    {
        if (generic_buttons_handle_mouse(m, {data.x, data.y}, buttons_list1, data.items.size(), &data.focus_button_id))
            return;
    }
    if (input_go_back_requested(m, h))
        window_go_back();
}

void select_item(int id, int list_id) {
    auto &data = g_select_list;
    window_go_back();
    //if (list_id == 0)
        data.callback(id);
    //else {
    //    data.callback(id + items_in_first_list());
    //}
}

void window_select_list_show(int x, int y, int group, int num_items, void (*callback)(int)) {
    window_type window = {
        WINDOW_SELECT_LIST,
        window_draw_underlying_window,
        draw_foreground,
        handle_input
    };
    init_group(x, y, group, num_items, callback);
    window_show(&window);
}

void window_select_list_show_text(int x, int y, const custom_span<xstring>& items, void (*callback)(int)) {
    window_type window = {
        WINDOW_SELECT_LIST,
        window_draw_underlying_window,
        draw_foreground,
        handle_input
    };
    init_text(x, y, items, callback);
    window_show(&window);
}
