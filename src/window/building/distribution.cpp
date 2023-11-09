#include "distribution.h"

#include "graphics/elements/image_button.h"
#include "graphics/elements/scrollbar.h"

#include "building/building.h"
#include "building/market.h"
#include "building/storage.h"
#include "building/storage_yard.h"
#include "city/buildings.h"
#include "city/resource.h"
#include "figure/figure.h"
#include "game/resource.h"
#include "graphics/boilerplate.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "scenario/property.h"
#include "window/window_building_info.h"

static void go_to_orders(int param1, int param2);
static void toggle_resource_state(int index, int param2);
static void toggle_resource_state_backwards(int index, int param2);
static void order_quantity_increase_decrease(int index, int param2);
static void granary_orders(int param1, int param2);
static void warehouse_orders(int index, int param2);
static void market_orders(int index, int param2);
static void storage_toggle_permissions(int index, int param2);

static generic_button go_to_orders_button[] = {{0, 0, 304, 20, go_to_orders, button_none, 0, 0}};

static generic_button orders_resource_buttons[] = {
  {0, 20 * 0, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 1, 0},
  {0, 20 * 1, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 2, 0},
  {0, 20 * 2, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 3, 0},
  {0, 20 * 3, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 4, 0},
  {0, 20 * 4, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 5, 0},
  {0, 20 * 5, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 6, 0},
  {0, 20 * 6, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 7, 0},
  {0, 20 * 7, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 8, 0},
  {0, 20 * 8, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 9, 0},
  {0, 20 * 9, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 10, 0},
  {0, 20 * 10, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 11, 0},
  {0, 20 * 11, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 12, 0},
  {0, 20 * 12, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 13, 0},
  {0, 20 * 13, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 14, 0},
  {0, 20 * 14, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 15, 0},
  {0, 20 * 15, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 16, 0},
  {0, 20 * 16, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 17, 0},
  {0, 20 * 17, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 18, 0},
  {0, 20 * 18, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 19, 0},
  {0, 20 * 19, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 20, 0},
};

static image_button orders_decrease_arrows[] = {
  {0, 20 * 0,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 1,  0, true},
  {0, 20 * 1,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 2,  0, true},
  {0, 20 * 2,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 3,  0, true},
  {0, 20 * 3,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 4,  0, true},
  {0, 20 * 4,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 5,  0, true},
  {0, 20 * 5,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 6,  0, true},
  {0, 20 * 6,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 7,  0, true},
  {0, 20 * 7,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 8,  0, true},
  {0, 20 * 8,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 9,  0, true},
  {0, 20 * 9,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 10, 0, true},
  {0, 20 * 10, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 11, 0, true},
  {0, 20 * 11, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 12, 0, true},
  {0, 20 * 12, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 13, 0, true},
  {0, 20 * 13, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 14, 0, true},
  {0, 20 * 14, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 15, 0, true},
  {0, 20 * 15, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 16, 0, true},
  {0, 20 * 16, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 17, 0, true},
  {0, 20 * 17, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 18, 0, true},
  {0, 20 * 18, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 19, 0, true},
  {0, 20 * 19, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 20, 0, true},
};

static image_button orders_increase_arrows[] = {
  {0, 20 * 0,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 1,  1, true},
  {0, 20 * 1,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 2,  1, true},
  {0, 20 * 2,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 3,  1, true},
  {0, 20 * 3,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 4,  1, true},
  {0, 20 * 4,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 5,  1, true},
  {0, 20 * 5,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 6,  1, true},
  {0, 20 * 6,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 7,  1, true},
  {0, 20 * 7,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 8,  1, true},
  {0, 20 * 8,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 9,  1, true},
  {0, 20 * 9,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 10, 1, true},
  {0, 20 * 10, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 11, 1, true},
  {0, 20 * 11, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 12, 1, true},
  {0, 20 * 12, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 13, 1, true},
  {0, 20 * 13, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 14, 1, true},
  {0, 20 * 14, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 15, 1, true},
  {0, 20 * 15, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 16, 1, true},
  {0, 20 * 16, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 17, 1, true},
  {0, 20 * 17, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 18, 1, true},
  {0, 20 * 18, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 19, 1, true},
  {0, 20 * 19, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 20, 1, true},
};

static generic_button warehouse_distribution_permissions_buttons[] = {
  {0, 0, 20, 22, storage_toggle_permissions, button_none, 1, 0},
  {96, 0, 20, 22, storage_toggle_permissions, button_none, 2, 0},
  {228, 0, 20, 22, storage_toggle_permissions, button_none, 3, 0},
};

static generic_button granary_order_buttons[] = {
  {0, -15 * 16, 304, 20, granary_orders, button_none, 0, 0},
  {0, -22 - 15 * 16, 304, 20, warehouse_orders, button_none, 1, 0},
  {314, -15 * 16, 20, 20, granary_orders, button_none, 2, 0},
};

static generic_button market_order_buttons[] = {
  {314, -15 * 16, 20, 20, market_orders, button_none, 0, 0},
};

static generic_button warehouse_order_buttons[] = {
  {0, 5 * 16, 304, 20, warehouse_orders, button_none, 0, 0},
  {0, -22 + 5 * 16, 304, 20, warehouse_orders, button_none, 1, 0},
  {314, 5 * 16, 20, 20, warehouse_orders, button_none, 2, 0}, //
};

struct window_building_distribution_t {
    int focus_button_id;
    int orders_focus_button_id;
    int resource_focus_button_id;
    int permission_focus_button_id;
    int decr_arrow_focus_button_id;
    int incr_arrow_focus_button_id;
    int building_id;
    int partial_resource_focus_button_id;
};

window_building_distribution_t g_window_building_distribution = {0, 0, 0, 0, 0, 0};

uint8_t warehouse_full_button_text[] = "32";
uint8_t warehouse_3quarters_button_text[] = "24";
uint8_t warehouse_half_button_text[] = "16";
uint8_t warehouse_quarter_button_text[] = "8";
uint8_t granary_full_button_text[] = "24";
uint8_t granary_3quarters_button_text[] = "18";
uint8_t granary_half_button_text[] = "12";
uint8_t granary_quarter_button_text[] = "6";

enum e_instr {
    INSTR_STORAGE_YARD = 0,
    INSTR_GRANARY = 1,
    INSTR_DOCK = 2,
    INSTR_OTHERS = 3,
};

static void draw_order_instruction(int instr_kind,
                                   const building_storage* storage,
                                   int resource,
                                   int x,
                                   int y,
                                   int market_order = -1) {
    font_t font_nope = FONT_NORMAL_BLACK_ON_DARK;
    font_t font_yes = FONT_NORMAL_WHITE_ON_DARK;
    font_t font_get = FONT_NORMAL_YELLOW;

    if (storage != nullptr) {
        switch (storage->resource_state[resource]) {
        case STORAGE_STATE_PHARAOH_ACCEPT: {
            int width = lang_text_draw(99, 18, x, y, font_yes);
            int max_accept = storage->resource_max_accept[resource];
            if (max_accept == 3200)
                width += lang_text_draw(99, 28, x + width, y, font_yes);
            else if (max_accept == 2400)
                width += lang_text_draw(99, 27, x + width, y, font_yes);
            else if (max_accept == 1600)
                width += lang_text_draw(99, 26, x + width, y, font_yes);
            else if (max_accept == 800)
                width += lang_text_draw(99, 25, x + width, y, font_yes);
            else
                width += text_draw_number(max_accept, '@', " ", x + width, y, font_yes);
            if (max_accept == 2400 || max_accept == 1600 || max_accept == 800)
                lang_text_draw(99, 29, x + width, y, font_yes);
            break;
        }
        case STORAGE_STATE_PHARAOH_REFUSE:
            lang_text_draw(99, 8, x, y, font_nope);
            break;

        case STORAGE_STATE_PHARAOH_GET: {
            int width = lang_text_draw(99, 19, x, y, font_get);
            int max_get = storage->resource_max_get[resource];
            if (max_get == 3200)
                width += lang_text_draw(99, 31, x + width, y, font_get);
            else if (max_get == 2400)
                width += lang_text_draw(99, 27, x + width, y, font_get);
            else if (max_get == 1600)
                width += lang_text_draw(99, 26, x + width, y, font_get);
            else if (max_get == 800)
                width += lang_text_draw(99, 25, x + width, y, font_get);
            else
                width += text_draw_number(max_get, '@', " ", x + width, y, font_get);
            if (max_get == 2400 || max_get == 1600 || max_get == 800)
                lang_text_draw(99, 29, x + width, y, font_get);
            break;
        }
        case STORAGE_STATE_PHARAOH_EMPTY:
            lang_text_draw(99, 21, x, y, font_nope);
            break;
        }
    } else {
        switch (market_order) {
        case BAZAAR_ORDER_STATE_BUY:
            lang_text_draw(97, 8, x, y, font_yes);
            break;

        case BAZAAR_ORDER_STATE_DONT_BUY:
            lang_text_draw(97, 9, x, y, font_nope);
            break;
        }
    }
}

static void draw_accept_none_button(int x, int y, int focused) {
    //    return; // temp - todo: fix buttons
    uint8_t refuse_button_text[] = {'x', 0};
    button_border_draw(x, y, 20, 20, focused ? 1 : 0);
    text_draw_centered(refuse_button_text, x + 1, y + 4, 20, FONT_NORMAL_BLACK_ON_LIGHT, 0);
}
static void draw_permissions_buttons(int x, int y, int buttons) {
    auto &data = g_window_building_distribution;
    return; // temp - todo: fix buttons
    uint8_t permission_button_text[] = {'x', 0};
    int offsets[] = {96, 132, 96};
    for (int i = 0; i < buttons; i++) {
        button_border_draw(x, y, 20, 20, data.permission_focus_button_id == i + 1 ? 1 : 0);
        if (building_storage_get_permission(i, building_get(data.building_id))) {
            text_draw_centered(permission_button_text, x + 1, y + 4, 20, FONT_NORMAL_BLACK_ON_LIGHT, 0);
        }

        x += offsets[i];
    }
}

int window_building_handle_mouse_dock(const mouse* m, object_info* c) {
    auto &data = g_window_building_distribution;
    return generic_buttons_handle_mouse(m, c->x_offset + 80, c->y_offset + 16 * c->height_blocks - 34, go_to_orders_button, 1, &data.focus_button_id);
}
int window_building_handle_mouse_dock_orders(const mouse* m, object_info* c) {
    auto &data = g_window_building_distribution;
    int y_offset = window_building_get_vertical_offset(c, 28);

    data.building_id = c->building_id;
    if (generic_buttons_handle_mouse(m, c->x_offset + 180, y_offset + 46, orders_resource_buttons, 15, &data.resource_focus_button_id)) {
        return 1;
    }
    return generic_buttons_handle_mouse(m, c->x_offset + 80, y_offset + 404, market_order_buttons, 1, &data.orders_focus_button_id);
}
void window_building_draw_dock(object_info* c) {
    c->help_id = 83;
    window_building_play_sound(c, "wavs/dock.wav");
    outer_panel_draw(c->x_offset, c->y_offset, c->width_blocks, c->height_blocks);
    lang_text_draw_centered(101, 0, c->x_offset, c->y_offset + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);

    building* b = building_get(c->building_id);

    if (!c->has_road_access) {
        window_building_draw_description(c, 69, 25);
    } else if (b->data.dock.trade_ship_id) {
        if (c->worker_percentage <= 0)
            window_building_draw_description(c, 101, 2);
        else if (c->worker_percentage < 50)
            window_building_draw_description(c, 101, 3);
        else if (c->worker_percentage < 75)
            window_building_draw_description(c, 101, 4);
        else {
            window_building_draw_description(c, 101, 5);
        }
    } else {
        if (c->worker_percentage <= 0)
            window_building_draw_description(c, 101, 6);
        else if (c->worker_percentage < 50)
            window_building_draw_description(c, 101, 7);
        else if (c->worker_percentage < 75)
            window_building_draw_description(c, 101, 8);
        else {
            window_building_draw_description(c, 101, 9);
        }
    }

    inner_panel_draw(c->x_offset + 16, c->y_offset + 136, c->width_blocks - 2, 4);
    window_building_draw_employment(c, 142);
}
void window_building_draw_dock_foreground(object_info* c) {
    auto &data = g_window_building_distribution;
    button_border_draw(c->x_offset + 80, c->y_offset + 16 * c->height_blocks - 34, 16 * (c->width_blocks - 10), 20, data.focus_button_id == 1 ? 1 : 0);
    lang_text_draw_centered(98, 5, c->x_offset + 80, c->y_offset + 16 * c->height_blocks - 30, 16 * (c->width_blocks - 10), FONT_NORMAL_BLACK_ON_LIGHT);
}
void window_building_draw_dock_orders(object_info* c) {
    c->help_id = 83;
    int y_offset = window_building_get_vertical_offset(c, 28);
    outer_panel_draw(c->x_offset, y_offset, 29, 28);
    lang_text_draw_centered(101, 0, c->x_offset, y_offset + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    inner_panel_draw(c->x_offset + 16, y_offset + 42, c->width_blocks - 2, 21);
}

void window_building_draw_dock_orders_foreground(object_info* c) {
    auto &data = g_window_building_distribution;
    int y_offset = window_building_get_vertical_offset(c, 28);
    int line_x = c->x_offset + 215;

    draw_accept_none_button(c->x_offset + 394, y_offset + 404, data.orders_focus_button_id == 1);

    for (int i = 0; i < 15; i++) {
        int line_y = 20 * i;
        int resource = i + 1;
        int image_id= image_id_resource_icon(resource) + resource_image_offset(resource, RESOURCE_IMAGE_ICON);
        ImageDraw::img_generic(image_id, c->x_offset + 32, y_offset + 46 + line_y);
        ImageDraw::img_generic(image_id, c->x_offset + 408, y_offset + 46 + line_y);
        lang_text_draw(23, resource, c->x_offset + 72, y_offset + 50 + line_y, FONT_NORMAL_WHITE_ON_DARK);
        button_border_draw(c->x_offset + 180, y_offset + 46 + line_y, 210, 22, data.resource_focus_button_id == i + 1);
        building* b = building_get(c->building_id);
        int state = is_good_accepted(i, b);
        if (state)
            lang_text_draw(99, 7, line_x, y_offset + 51 + line_y, FONT_NORMAL_WHITE_ON_DARK);
        else
            lang_text_draw(99, 8, line_x, y_offset + 51 + line_y, FONT_NORMAL_YELLOW);
    }
}

#define Y_FOODS 90           // 234
#define Y_GOODS Y_FOODS + 20 // 174 //274

void window_building_handle_mouse_market(const mouse* m, object_info* c) {
    auto &data = g_window_building_distribution;
    generic_buttons_handle_mouse(m, c->x_offset + 80, c->y_offset + 16 * c->height_blocks - 34, go_to_orders_button, 1, &data.focus_button_id);
}
void window_building_handle_mouse_market_orders(const mouse* m, object_info* c) {
    auto &data = g_window_building_distribution;
    int y_offset = window_building_get_vertical_offset(c, 28 - 11);
    data.resource_focus_button_id = 0;

    // resources
    int num_resources = city_resource_get_available_market_goods()->size;
    data.building_id = c->building_id;
    if (generic_buttons_handle_mouse(m, c->x_offset + 205, y_offset + 46, orders_resource_buttons, num_resources, &data.resource_focus_button_id)) {
        return;
    }

    // extra instructions
    //if (GAME_ENV == ENGINE_ENV_C3)
    //    generic_buttons_handle_mouse(
    //      m, c->x_offset + 80, y_offset + 404, market_order_buttons, 1, &data.orders_focus_button_id);
}
void window_building_draw_market(object_info* c) {
    c->help_id = 2;
    window_building_play_sound(c, "wavs/market.wav");
    outer_panel_draw(c->x_offset, c->y_offset, c->width_blocks, c->height_blocks);
    lang_text_draw_centered(97, 0, c->x_offset, c->y_offset + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    building* b = building_get(c->building_id);
    font_t font;
    if (!c->has_road_access)
        window_building_draw_description(c, 69, 25);
    else if (b->num_workers <= 0)
        window_building_draw_description(c, 97, 2);
    else {
        int image_id = image_id_resource_icon(0);
        if (b->data.market.inventory[0] || b->data.market.inventory[1] || b->data.market.inventory[2]
            || b->data.market.inventory[3]) {
            {
                //
            }
        } else {
            window_building_draw_description_at(c, 48, 97, 4);
        }

        // food stocks
        // todo: fetch map available foods?
        int food1 = ALLOWED_FOODS(0);
        int food2 = ALLOWED_FOODS(1);
        int food3 = ALLOWED_FOODS(2);
        int food4 = ALLOWED_FOODS(3);

        if (food1) {
            font = is_good_accepted(0, b) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW;
            ImageDraw::img_generic(image_id + food1, c->x_offset + 32, c->y_offset + Y_FOODS);
            text_draw_number(b->data.market.inventory[0], '@', " ", c->x_offset + 64, c->y_offset + Y_FOODS + 4, font);
        }

        if (food2) {
            font = is_good_accepted(1, b) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW;
            ImageDraw::img_generic(image_id + food2, c->x_offset + 142, c->y_offset + Y_FOODS);
            text_draw_number(b->data.market.inventory[1], '@', " ", c->x_offset + 174, c->y_offset + Y_FOODS + 4, font);
        }

        if (food3) {
            font = is_good_accepted(2, b) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW;
            ImageDraw::img_generic(image_id + food3, c->x_offset + 252, c->y_offset + Y_FOODS);
            text_draw_number(b->data.market.inventory[2], '@', " ", c->x_offset + 284, c->y_offset + Y_FOODS + 4, font);
        }

        if (food4) {
            font = is_good_accepted(3, b) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW;
            ImageDraw::img_generic(image_id + food4, c->x_offset + 362, c->y_offset + Y_FOODS);
            text_draw_number(b->data.market.inventory[3], '@', " ", c->x_offset + 394, c->y_offset + Y_FOODS + 4, font);
        }

        // good stocks
        font = is_good_accepted(INVENTORY_GOOD1, b) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW;
        ImageDraw::img_generic(image_id + INV_RESOURCES[0], c->x_offset + 32, c->y_offset + Y_GOODS);
        text_draw_number(b->data.market.inventory[INVENTORY_GOOD1], '@', " ", c->x_offset + 64, c->y_offset + Y_GOODS + 4, font);

        font = is_good_accepted(INVENTORY_GOOD2, b) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW;
        ImageDraw::img_generic(image_id + INV_RESOURCES[1], c->x_offset + 142, c->y_offset + Y_GOODS);
        text_draw_number(b->data.market.inventory[INVENTORY_GOOD2], '@', " ", c->x_offset + 174, c->y_offset + Y_GOODS + 4, font);

        font = is_good_accepted(INVENTORY_GOOD3, b) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW;
        ImageDraw::img_generic(image_id + INV_RESOURCES[2], c->x_offset + 252, c->y_offset + Y_GOODS);
        text_draw_number(b->data.market.inventory[INVENTORY_GOOD3], '@', " ", c->x_offset + 284, c->y_offset + Y_GOODS + 4, font);

        font = is_good_accepted(INVENTORY_GOOD4, b) ? FONT_NORMAL_BLACK_ON_LIGHT : FONT_NORMAL_YELLOW;
        ImageDraw::img_generic(image_id + INV_RESOURCES[3], c->x_offset + 362, c->y_offset + Y_GOODS);
        text_draw_number(b->data.market.inventory[INVENTORY_GOOD4], '@', " ", c->x_offset + 394, c->y_offset + Y_GOODS + 4, font);
    }
    inner_panel_draw(c->x_offset + 16, c->y_offset + 136, c->width_blocks - 2, 4);
    window_building_draw_employment(c, 142);
}
void window_building_draw_market_foreground(object_info* c) {
    auto &data = g_window_building_distribution;
    button_border_draw(c->x_offset + 80, c->y_offset + 16 * c->height_blocks - 34, 16 * (c->width_blocks - 10), 20, data.focus_button_id == 1 ? 1 : 0);
    lang_text_draw_centered(98, 5, c->x_offset + 80, c->y_offset + 16 * c->height_blocks - 30, 16 * (c->width_blocks - 10), FONT_NORMAL_BLACK_ON_LIGHT);
}
void window_building_draw_market_orders(object_info* c) {
    c->help_id = 2;
    int y_offset = window_building_get_vertical_offset(c, 28 - 11);
    outer_panel_draw(c->x_offset, y_offset, 29, 28 - 11);
    lang_text_draw_centered(97, 7, c->x_offset, y_offset + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    inner_panel_draw(c->x_offset + 16, y_offset + 42, c->width_blocks - 2, 21 - 10);
}
void window_building_draw_market_orders_foreground(object_info* c) {
    auto &data = g_window_building_distribution;
    window_building_draw_market_orders(c);
    int line_x = c->x_offset + 215;
    int y_offset = window_building_get_vertical_offset(c, 28 - 11);

    building* b = building_get(c->building_id);
    //    backup_storage_settings(storage_id); // TODO: market state backup
    const resources_list* list = city_resource_get_available_market_goods();
    for (int i = 0; i < list->size; i++) {
        int line_y = 20 * i;
        int resource = list->items[i];
        int image_id = image_id_resource_icon(resource) + resource_image_offset(resource, RESOURCE_IMAGE_ICON);

        ImageDraw::img_generic(image_id, c->x_offset + 25, y_offset + 48 + line_y);
        lang_text_draw(23, resource, c->x_offset + 52, y_offset + 50 + line_y, FONT_NORMAL_WHITE_ON_DARK);
        if (data.resource_focus_button_id - 1 == i)
            button_border_draw(line_x - 10, y_offset + 46 + line_y, orders_resource_buttons[i].width, orders_resource_buttons[i].height, true);

        // order status
        draw_order_instruction(INSTR_STORAGE_YARD, nullptr, resource, line_x, y_offset + 51 + line_y, is_good_accepted(i, b));
    }

    // accept none button
    //if (GAME_ENV == ENGINE_ENV_C3) {
    //    draw_accept_none_button(c->x_offset + 394, y_offset + 404, data.orders_focus_button_id == 1);
    //}
    //    else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
    //        button_border_draw(c->x_offset + 80, y_offset + 382 - 10 * 16, 16 * (c->width_blocks - 10), 20,
    //                           data.orders_focus_button_id == 2 ? 1 : 0);
    //        lang_text_draw_centered(99, 7, c->x_offset + 80, y_offset + 386 - 10 * 16,
    //                                16 * (c->width_blocks - 10), FONT_NORMAL_BLACK);
    //    }
}

int window_building_handle_mouse_granary(const mouse* m, object_info* c) {
    auto &data = g_window_building_distribution;
    data.building_id = c->building_id;
    generic_buttons_handle_mouse(m, c->x_offset + 58, c->y_offset + 19 * c->height_blocks - 82, warehouse_distribution_permissions_buttons, 1, &data.permission_focus_button_id);
    generic_buttons_handle_mouse(m, c->x_offset + 80, c->y_offset + 16 * c->height_blocks - 34, go_to_orders_button, 1, &data.focus_button_id);
    return 0;
}

int window_building_handle_mouse_granary_orders(const mouse* m, object_info* c) {
    auto &data = g_window_building_distribution;
    int y_offset = window_building_get_vertical_offset(c, 28 - 15);
    data.resource_focus_button_id = 0;

    // arrows
    bool handled = false;
    if (image_buttons_handle_mouse(m, c->x_offset + 165, y_offset + 49, orders_decrease_arrows, 20, &data.decr_arrow_focus_button_id)) {
        handled = true;
    }

    if (image_buttons_handle_mouse(m, c->x_offset + 165 + 18, y_offset + 49, orders_increase_arrows, 20, &data.decr_arrow_focus_button_id)) {
        handled = true;
    }

    if (handled) {
        return 1;
    }

    // resources
    int num_resources = city_resource_get_available_foods()->size;
    data.building_id = c->building_id;
    if (generic_buttons_handle_mouse(m, c->x_offset + 205, y_offset + 46, orders_resource_buttons, num_resources, &data.resource_focus_button_id)) {
        return 1;
    }

    // extra instructions
    return generic_buttons_handle_mouse(m, c->x_offset + 80, y_offset + 404, granary_order_buttons, 2, &data.orders_focus_button_id);
}
void window_building_draw_granary(object_info* c) {
    auto &data = g_window_building_distribution;
    c->help_id = 3;
    data.building_id = c->building_id;
    window_building_play_sound(c, "wavs/granary.wav");
    outer_panel_draw(c->x_offset, c->y_offset, c->width_blocks, c->height_blocks);
    lang_text_draw_centered(98, 0, c->x_offset, c->y_offset + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    building* b = building_get(c->building_id);
    if (!c->has_road_access) {
        window_building_draw_description_at(c, 40, 69, 25);
    } else if (scenario_property_rome_supplies_wheat()) {
        window_building_draw_description_at(c, 40, 98, 4);
    } else {
        int total_stored = 0;
        for (int i = RESOURCE_MIN_FOOD; i < RESOURCES_FOODS_MAX; i++) {
            total_stored += b->data.granary.resource_stored[i];
        }

        int width = lang_text_draw(98, 2, c->x_offset + 34, c->y_offset + 40, FONT_NORMAL_BLACK_ON_LIGHT);
        lang_text_draw_amount(8, 16, total_stored, c->x_offset + 34 + width, c->y_offset + 40, FONT_NORMAL_BLACK_ON_LIGHT);

        width = lang_text_draw(98, 3, c->x_offset + 220, c->y_offset + 40, FONT_NORMAL_BLACK_ON_LIGHT);
        lang_text_draw_amount(8, 16, b->data.granary.resource_stored[RESOURCE_NONE], c->x_offset + 220 + width, c->y_offset + 40, FONT_NORMAL_BLACK_ON_LIGHT);

        // todo: fetch map available foods?
        int food1 = ALLOWED_FOODS(0);
        int food2 = ALLOWED_FOODS(1);
        int food3 = ALLOWED_FOODS(2);
        int food4 = ALLOWED_FOODS(3);
        //        resource_image_offset(RESOURCE_FIGS, RESOURCE_IMAGE_ICON);

        int image_id = image_id_resource_icon(0);
        if (food1) { // wheat
            ImageDraw::img_generic(image_id + food1, c->x_offset + 34, c->y_offset + 68);
            width = text_draw_number(b->data.granary.resource_stored[food1], '@', " ", c->x_offset + 68, c->y_offset + 75, FONT_NORMAL_BLACK_ON_LIGHT);
            lang_text_draw(23, food1, c->x_offset + 68 + width, c->y_offset + 75, FONT_NORMAL_BLACK_ON_LIGHT);
        }
        if (food2) { // fruit
            ImageDraw::img_generic(image_id + food2, c->x_offset + 240, c->y_offset + 68);
            width = text_draw_number(b->data.granary.resource_stored[food2], '@', " ", c->x_offset + 274, c->y_offset + 75,FONT_NORMAL_BLACK_ON_LIGHT);
            lang_text_draw(23, food2, c->x_offset + 274 + width, c->y_offset + 75, FONT_NORMAL_BLACK_ON_LIGHT);
        }
        if (food3) { // vegetables
            ImageDraw::img_generic(image_id + food3, c->x_offset + 34, c->y_offset + 92);
            width = text_draw_number(b->data.granary.resource_stored[food3], '@', " ", c->x_offset + 68, c->y_offset + 99, FONT_NORMAL_BLACK_ON_LIGHT);
            lang_text_draw(23, food3, c->x_offset + 68 + width, c->y_offset + 99, FONT_NORMAL_BLACK_ON_LIGHT);
        }
        if (food4) { // meat/fish
            ImageDraw::img_generic(image_id + food4, c->x_offset + 240, c->y_offset + 92);
            width = text_draw_number(b->data.granary.resource_stored[food4], '@', " ", c->x_offset + 274, c->y_offset + 99,FONT_NORMAL_BLACK_ON_LIGHT);
            lang_text_draw(23, food4, c->x_offset + 274 + width, c->y_offset + 99, FONT_NORMAL_BLACK_ON_LIGHT);
        }
    }
    inner_panel_draw(c->x_offset + 16, c->y_offset + 136, c->width_blocks - 2, 5);
    window_building_draw_employment(c, 142);
    //    imagedrawnamespace::image_draw_namespace::image_draw(image_id_from_group(GROUP_FIGURE_MARKET_LADY) + 4,
    //    c->x_offset + 28,
    //               c->y_offset + 19 * c->height_blocks - 93);
}
void window_building_draw_granary_foreground(object_info* c) {
    auto &data = g_window_building_distribution;
    button_border_draw(c->x_offset + 80, c->y_offset + 16 * c->height_blocks - 34, 16 * (c->width_blocks - 10), 20, data.focus_button_id == 1 ? 1 : 0);
    lang_text_draw_centered(98, 5, c->x_offset + 80, c->y_offset + 16 * c->height_blocks - 30, 16 * (c->width_blocks - 10), FONT_NORMAL_BLACK_ON_LIGHT);
    draw_permissions_buttons(c->x_offset + 58, c->y_offset + 19 * c->height_blocks - 82, 1);
}
void window_building_draw_granary_orders(object_info* c) {
    c->help_id = 3;
    int y_offset = window_building_get_vertical_offset(c, 28 - 15);
    outer_panel_draw(c->x_offset, y_offset, 29, 28 - 15);
    lang_text_draw_centered(98, 6, c->x_offset, y_offset + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    inner_panel_draw(c->x_offset + 16, y_offset + 42, c->width_blocks - 2, 21 - 15);
}
void window_building_draw_granary_orders_foreground(object_info* c) {
    auto &data = g_window_building_distribution;
    window_building_draw_granary_orders(c);
    int line_x = c->x_offset + 215;
    int y_offset = window_building_get_vertical_offset(c, 28 - 15);

    int storage_id = building_get(c->building_id)->storage_id;
    backup_storage_settings(storage_id);
    const building_storage* storage = building_storage_get(storage_id);
    const resources_list* list = city_resource_get_available_foods();
    for (int i = 0; i < list->size; i++) {
        int line_y = 20 * i;
        int resource = list->items[i];
        int image_id = image_id_resource_icon(resource) + resource_image_offset(resource, RESOURCE_IMAGE_ICON);

        ImageDraw::img_generic(image_id, c->x_offset + 25, y_offset + 48 + line_y);
        lang_text_draw(23, resource, c->x_offset + 52, y_offset + 50 + line_y, FONT_NORMAL_WHITE_ON_DARK);
        if (data.resource_focus_button_id - 1 == i) {
            button_border_draw(line_x - 10, y_offset + 46 + line_y, orders_resource_buttons[i].width, orders_resource_buttons[i].height, true);
        }

        // order status
        draw_order_instruction(INSTR_STORAGE_YARD, storage, resource, line_x, y_offset + 51 + line_y);

        // arrows
        int state = storage->resource_state[resource];
        if (state == STORAGE_STATE_PHARAOH_ACCEPT || state == STORAGE_STATE_PHARAOH_GET) {
            image_buttons_draw(c->x_offset + 165, y_offset + 49, orders_decrease_arrows, 1, i);
            image_buttons_draw(c->x_offset + 165 + 18, y_offset + 49, orders_increase_arrows, 1, i);
        }
    }

    // emptying button
    button_border_draw(c->x_offset + 80, y_offset + 404 - 15 * 16, 16 * (c->width_blocks - 10), 20, data.orders_focus_button_id == 1 ? 1 : 0);
    if (storage->empty_all) {
        lang_text_draw_centered(98, 8, c->x_offset + 80, y_offset + 408 - 15 * 16, 16 * (c->width_blocks - 10), FONT_NORMAL_BLACK_ON_LIGHT);
    } else {
        lang_text_draw_centered(98, 7, c->x_offset + 80, y_offset + 408 - 15 * 16, 16 * (c->width_blocks - 10), FONT_NORMAL_BLACK_ON_LIGHT);
    }

    // accept none button
    button_border_draw(c->x_offset + 80, y_offset + 382 - 15 * 16, 16 * (c->width_blocks - 10), 20, data.orders_focus_button_id == 2 ? 1 : 0);
    lang_text_draw_centered(99, 7, c->x_offset + 80, y_offset + 386 - 15 * 16, 16 * (c->width_blocks - 10), FONT_NORMAL_BLACK_ON_LIGHT);
}
void window_building_get_tooltip_granary_orders(int* group_id, int* text_id) {
    auto &data = g_window_building_distribution;
    if (data.orders_focus_button_id == 2) {
        *group_id = 143;
        *text_id = 1;
    }
}

static void on_scroll(void) {
    //    window_invalidate();
}
static scrollbar_type scrollbar = {590, 52, 336, on_scroll};

int window_building_handle_mouse_warehouse(const mouse* m, object_info* c) {
    auto &data = g_window_building_distribution;
    data.building_id = c->building_id;
    if (generic_buttons_handle_mouse(m, c->x_offset + 80, c->y_offset + 16 * c->height_blocks - 34, go_to_orders_button, 1, &data.focus_button_id)) {
    }
    // temp - todo: fix buttons
    //    if (generic_buttons_handle_mouse(m, c->x_offset + 64, c->y_offset + 16 * c->height_blocks - 75,
    //                                     warehouse_distribution_permissions_buttons, 3,
    //                                     &data.permission_focus_button_id)) {
    //    }
    return 0;
}
int window_building_handle_mouse_warehouse_orders(const mouse* m, object_info* c) {
    auto &data = g_window_building_distribution;
    int y_offset = window_building_get_vertical_offset(c, 28 + 5);
    data.resource_focus_button_id = 0;

    bool handled = false;
    //    bool handled = scrollbar_handle_mouse(&scrollbar, m);
    //    if (handled)
    //        return handled;

    // arrows
    if (image_buttons_handle_mouse(m, c->x_offset + 165, y_offset + 49, orders_decrease_arrows, 20, &data.decr_arrow_focus_button_id)) {
        handled = true;
    }

    if (image_buttons_handle_mouse(m, c->x_offset + 165 + 18, y_offset + 49, orders_increase_arrows, 20, &data.decr_arrow_focus_button_id)) {
        handled = true;
    }

    if (handled)
        return 1;

    // resources
    int num_resources = city_resource_get_available()->size;
    if (num_resources > 20) {
        num_resources = 20;
    }
    data.building_id = c->building_id;

    if (generic_buttons_handle_mouse(m, c->x_offset + 205, y_offset + 46, orders_resource_buttons, num_resources, &data.resource_focus_button_id)) {
        return 1;
    }

    // extra instructions
    return generic_buttons_handle_mouse(m, c->x_offset + 80, y_offset + 404, warehouse_order_buttons, 2, &data.orders_focus_button_id);
}
void window_building_draw_warehouse(object_info* c) {
    auto &data = g_window_building_distribution;
    c->help_id = 4;
    window_building_play_sound(c, "wavs/warehouse.wav");
    outer_panel_draw(c->x_offset, c->y_offset, c->width_blocks, c->height_blocks);
    lang_text_draw_centered(99, 0, c->x_offset, c->y_offset + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    building* b = building_get(c->building_id);
    data.building_id = c->building_id;
    if (!c->has_road_access) {
        window_building_draw_description(c, 69, 25);
    }
    //if (GAME_ENV == ENGINE_ENV_C3) {
    //    const resources_list* list = city_resource_get_available();
    //    for (int i = 0; i < list->size; i++) {
    //        e_resource resource = list->items[i];
    //        int x, y;
    //        if (i < 5) { // column 1
    //            x = c->x_offset + 20;
    //            y = c->y_offset + 24 * i + 36;
    //        } else if (i < 10) { // column 2
    //            x = c->x_offset + 170;
    //            y = c->y_offset + 24 * (i - 5) + 36;
    //        } else { // column 3
    //            x = c->x_offset + 320;
    //            y = c->y_offset + 24 * (i - 10) + 36;
    //        }
    //        int amount = building_storageyard_get_amount(b, resource);
    //        int image_id = image_id_from_group(GROUP_RESOURCE_ICONS) + resource + resource_image_offset(resource, RESOURCE_IMAGE_ICON);
    //        ImageDraw::img_generic(image_id, x, y);
    //        int width = text_draw_number(amount, '@', " ", x + 24, y + 7, FONT_SMALL_PLAIN);
    //        lang_text_draw(23, resource, x + 24 + width, y + 7, FONT_SMALL_PLAIN);
    //    }
    //} else if (GAME_ENV == ENGINE_ENV_PHARAOH) 
    {
        int x = c->x_offset + 20;
        int y = c->y_offset + 45;
        int lines = 0;

        const resources_list* list = city_resource_get_available();
        for (int i = 0; i < list->size; i++) {
            e_resource resource = list->items[i];
            int loads = building_storageyard_get_amount(b, resource);
            if (loads) {
                int amount = stack_proper_quantity(loads, resource);
                int image_id = image_id_resource_icon(resource) + resource_image_offset(resource, RESOURCE_IMAGE_ICON);
                ImageDraw::img_generic(image_id, x, y);
                int width = text_draw_number(amount, '@', " ", x + 24, y + 7, FONT_NORMAL_BLACK_ON_LIGHT);
                lang_text_draw(23, resource, x + 24 + width, y + 7, FONT_NORMAL_BLACK_ON_LIGHT);
                y += 24;
                lines++;
                if (lines >= 4) {
                    lines = 0;
                    y = c->y_offset + 45;
                    x += 205;
                }
            }
        }
    }
    inner_panel_draw(c->x_offset + 16, c->y_offset + 168, c->width_blocks - 2, 5);
    window_building_draw_employment(c, 173);
    // cartpusher state
    figure* cartpusher = b->get_figure(0);
    if (cartpusher->state == FIGURE_STATE_ALIVE) {
        int resource = cartpusher->get_resource();
        ImageDraw::img_generic(image_id_resource_icon(resource) + resource_image_offset(resource, RESOURCE_IMAGE_ICON), c->x_offset + 32, c->y_offset + 220);
        lang_text_draw_multiline(99, 17, c->x_offset + 64, c->y_offset + 223, 16 * (c->width_blocks - 6), FONT_NORMAL_BLACK_ON_DARK);
    } else if (b->num_workers) {
        // cartpusher is waiting for orders
        lang_text_draw_multiline(99, 15, c->x_offset + 32, c->y_offset + 223, 16 * (c->width_blocks - 4), FONT_NORMAL_BLACK_ON_DARK);
    }

    // if (c->warehouse_space_text == 1) { // full
    //     lang_text_draw_multiline(99, 13, c->x_offset + 32, c->y_offset + 16 * c->height_blocks - 93,
    //         16 * (c->width_blocks - 4), FONT_NORMAL_BLACK);
    // }  else if (c->warehouse_space_text == 2) {
    //     lang_text_draw_multiline(99, 14, c->x_offset + 32, c->y_offset + 16 * c->height_blocks - 93,
    //         16 * (c->width_blocks - 4), FONT_NORMAL_BLACK);
    // }

    //    imagedrawnamespace::image_draw_namespace::image_draw(image_id_from_group(GROUP_FIGURE_MARKET_LADY) + 4,
    //    c->x_offset + 32,
    //               c->y_offset + 16 * c->height_blocks - 93);
    //    imagedrawnamespace::image_draw_namespace::image_draw(image_id_from_group(GROUP_FIGURE_TRADE_CARAVAN) + 4,
    //    c->x_offset + 128,
    //               c->y_offset + 16 * c->height_blocks - 93);
    //    imagedrawnamespace::image_draw_namespace::image_draw(image_id_from_group(GROUP_FIGURE_SHIP) + 4, c->x_offset +
    //    216,
    //               c->y_offset + 16 * c->height_blocks - 110);
}
void window_building_draw_warehouse_foreground(object_info* c) {
    auto &data = g_window_building_distribution;
    button_border_draw(c->x_offset + 80, c->y_offset + 16 * c->height_blocks - 34, 16 * (c->width_blocks - 10), 20, data.focus_button_id == 1 ? 1 : 0);
    lang_text_draw_centered(99, 2, c->x_offset + 80, c->y_offset + 16 * c->height_blocks - 30, 16 * (c->width_blocks - 10),FONT_NORMAL_BLACK_ON_LIGHT);

    // temp - todo: fix buttons
    //    draw_permissions_buttons(c->x_offset + 64, c->y_offset + 16 * c->height_blocks - 75, 3);
}
void window_building_draw_warehouse_orders(object_info* c) {
    int y_offset = window_building_get_vertical_offset(c, 28 + 5);
    c->help_id = 4;
    outer_panel_draw(c->x_offset, y_offset, 29, 28 + 5);
    lang_text_draw_centered(99, 3, c->x_offset, y_offset + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    inner_panel_draw(c->x_offset + 16, y_offset + 42, c->width_blocks - 2, 21 + 5);
}

void window_building_draw_warehouse_orders_foreground(object_info* c) {
    auto &data = g_window_building_distribution;
    window_building_draw_warehouse_orders(c);
    int y_offset = window_building_get_vertical_offset(c, 28 + 5);
    int line_x = c->x_offset + 215;

    int storage_id = building_get(c->building_id)->storage_id;
    backup_storage_settings(storage_id);
    const building_storage* storage = building_storage_get(storage_id);
    const resources_list* list = city_resource_get_available();
    for (int i = 0; i < list->size; i++) {
        int line_y = 20 * i;

        int resource = list->items[i];
        int image_id = image_id_resource_icon(resource) + resource_image_offset(resource, RESOURCE_IMAGE_ICON);
        ImageDraw::img_generic(image_id, c->x_offset + 25, y_offset + 48 + line_y);
        lang_text_draw(23, resource, c->x_offset + 52, y_offset + 50 + line_y, FONT_NORMAL_WHITE_ON_DARK);
        if (data.resource_focus_button_id - 1 == i) {
            button_border_draw(line_x - 10, y_offset + 46 + line_y, orders_resource_buttons[i].width, orders_resource_buttons[i].height, true);
        }

        // order status
        draw_order_instruction(INSTR_STORAGE_YARD, storage, resource, line_x, y_offset + 51 + line_y);

        // arrows
        int state = storage->resource_state[resource];
        if (state == STORAGE_STATE_PHARAOH_ACCEPT || state == STORAGE_STATE_PHARAOH_GET) {
            image_buttons_draw(c->x_offset + 165, y_offset + 49, orders_decrease_arrows, 1, i);
            image_buttons_draw(c->x_offset + 165 + 18, y_offset + 49, orders_increase_arrows, 1, i);
        }
    }

    // emptying button
    button_border_draw(c->x_offset + 80, y_offset + 404 + 5 * 16, 16 * (c->width_blocks - 10), 20, data.orders_focus_button_id == 1 ? 1 : 0);
    if (storage->empty_all) {
        lang_text_draw_centered(99, 5, c->x_offset + 80, y_offset + 408 + 5 * 16, 16 * (c->width_blocks - 10), FONT_NORMAL_BLACK_ON_LIGHT);
    } else {
        lang_text_draw_centered(99, 4, c->x_offset + 80, y_offset + 408 + 5 * 16, 16 * (c->width_blocks - 10), FONT_NORMAL_BLACK_ON_LIGHT);
    }

    // trade center
    if (GAME_ENV == ENGINE_ENV_C3) {
        button_border_draw(c->x_offset + 80, y_offset + 382 + 5 * 16, 16 * (c->width_blocks - 10), 20, data.orders_focus_button_id == 2 ? 1 : 0);
        int is_trade_center = c->building_id == city_buildings_get_trade_center();
        lang_text_draw_centered(99, is_trade_center ? 11 : 12, c->x_offset + 80, y_offset + 386 + 5 * 16, 16 * (c->width_blocks - 10), FONT_NORMAL_BLACK_ON_LIGHT);
        // accept none button
        draw_accept_none_button(c->x_offset + 394, y_offset + 404, data.orders_focus_button_id == 3);
    } else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
        // accept none button
        button_border_draw(c->x_offset + 80, y_offset + 382 + 5 * 16, 16 * (c->width_blocks - 10), 20, data.orders_focus_button_id == 2 ? 1 : 0);
        lang_text_draw_centered(99, 7, c->x_offset + 80, y_offset + 386 + 5 * 16, 16 * (c->width_blocks - 10), FONT_NORMAL_BLACK_ON_LIGHT);
    }
}

void window_building_get_tooltip_warehouse_orders(int* group_id, int* text_id) {
    auto &data = g_window_building_distribution;
    if (data.orders_focus_button_id == 1) {
        *group_id = 99;
        *text_id = 6;
    }

    if (data.orders_focus_button_id == 2) {
        *group_id = 15;
        *text_id = 1;
    }
}

static void go_to_orders(int param1, int param2) {
    window_building_info_show_storage_orders();
}

static void storage_toggle_permissions(int index, int param2) {
    auto &data = g_window_building_distribution;
    building* b = building_get(data.building_id);
    building_storage_set_permission(index - 1, b);
    //    window_invalidate();
}

static void toggle_resource_state(int index, int param2) {
    auto &data = g_window_building_distribution;
    building* b = building_get(data.building_id);
    int resource;
    if (b->type == BUILDING_MARKET || b->type == BUILDING_DOCK)
        toggle_good_accepted(index - 1, b);
    else {
        if (b->type == BUILDING_STORAGE_YARD)
            resource = city_resource_get_available()->items[index - 1];
        else
            resource = city_resource_get_available_foods()->items[index - 1];
        building_storage_cycle_resource_state(b->storage_id, resource, false);
    }
    //    window_invalidate();
}
static void toggle_resource_state_backwards(int index, int param2) {
    auto &data = g_window_building_distribution;
    building* b = building_get(data.building_id);
    int resource;
    if (b->type == BUILDING_MARKET || b->type == BUILDING_DOCK)
        toggle_good_accepted(index - 1, b);
    else {
        if (b->type == BUILDING_STORAGE_YARD)
            resource = city_resource_get_available()->items[index - 1];
        else
            resource = city_resource_get_available_foods()->items[index - 1];
        building_storage_cycle_resource_state(b->storage_id, resource, true);
    }
    //    window_invalidate();
}
static void order_quantity_increase_decrease(int index, int param2) {
    auto &data = g_window_building_distribution;
    building* b = building_get(data.building_id);
    int resource;
    if (b->type == BUILDING_MARKET || b->type == BUILDING_DOCK)
        return;
    else {
        if (b->type == BUILDING_STORAGE_YARD)
            resource = city_resource_get_available()->items[index - 1];
        else
            resource = city_resource_get_available_foods()->items[index - 1];
        building_storage_increase_decrease_resource_state(b->storage_id, resource, param2);
    }
    //    window_invalidate();
}

static void market_orders(int index, int param2) {
    auto &data = g_window_building_distribution;
    building* b = building_get(data.building_id);
    if (index == 0)
        unaccept_all_goods(b);

    //    window_invalidate();
}
static void granary_orders(int index, int param2) {
    auto &data = g_window_building_distribution;
    int storage_id = building_get(data.building_id)->storage_id;
    if (index == 0)
        building_storage_toggle_empty_all(storage_id);
    else if (index == 1)
        building_storage_accept_none(storage_id);

    //    window_invalidate();
}
static void warehouse_orders(int index, int param2) {
    auto &data = g_window_building_distribution;
    if (index == 0) {
        int storage_id = building_get(data.building_id)->storage_id;
        building_storage_toggle_empty_all(storage_id);
    } else if (index == 1) {
        if (GAME_ENV == ENGINE_ENV_C3)
            city_buildings_set_trade_center(data.building_id);
        else if (GAME_ENV == ENGINE_ENV_PHARAOH) {
            int storage_id = building_get(data.building_id)->storage_id;
            building_storage_accept_none(storage_id);
        }
    } else if (index == 2) {
        int storage_id = building_get(data.building_id)->storage_id;
        building_storage_accept_none(storage_id);
    }
    //    window_invalidate();
}
