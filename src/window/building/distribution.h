#pragma once

#include "input/mouse.h"
#include "graphics/elements/image_button.h"
#include "graphics/elements/generic_button.h"

#include <array>

enum e_instr {
    INSTR_STORAGE_YARD = 0,
    INSTR_GRANARY = 1,
    INSTR_DOCK = 2,
    INSTR_OTHERS = 3,
};

struct window_building_distribution {
    int focus_button_id = 0;
    int orders_focus_button_id = 0;
    int resource_focus_button_id = 0;
    int permission_focus_button_id = 0;
    int decr_arrow_focus_button_id = 0;
    int incr_arrow_focus_button_id = 0;
    int building_id = 0;
    int partial_resource_focus_button_id = 0;

    std::array<generic_button, 20> orders_resource_buttons;
    std::array<image_button, 20> orders_decrease_arrows;
    std::array<image_button, 20> orders_increase_arrows;
    std::array<generic_button, 1> go_to_orders_button;

    window_building_distribution();
};
extern window_building_distribution g_window_building_distribution;

struct object_info;
struct storage_t;

void draw_permissions_buttons(int x, int y, int buttons);
void draw_accept_none_button(int x, int y, int focused);

int window_building_handle_mouse_granary(const mouse* m, object_info* c);
int window_building_handle_mouse_granary_orders(const mouse* m, object_info* c);

std::pair<int, int> window_building_get_tooltip_granary_orders();

int window_building_handle_mouse_warehouse(const mouse* m, object_info* c);
int window_building_handle_mouse_warehouse_orders(const mouse* m, object_info* c);

void window_building_get_tooltip_warehouse_orders(int* group_id, int* text_id);
void window_building_draw_order_instruction(int instr_kind, const storage_t *storage, int resource, int x, int y, int market_order = -1);
