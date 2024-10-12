#pragma once

#include "graphics/elements/ui.h"

#include <array>

enum e_instr {
    INSTR_STORAGE_YARD = 0,
    INSTR_GRANARY = 1,
    INSTR_DOCK = 2,
    INSTR_OTHERS = 3,
    INSTR_MARKET = 4,
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

int window_building_handle_mouse_granary_orders(const mouse* m, object_info* c);

textid window_building_get_tooltip_granary_orders();
textid window_building_get_tooltip_warehouse_orders();

void window_building_draw_order_instruction(int instr_kind, const storage_t *storage, e_resource resource, vec2i pos, int market_order = -1);

std::pair<bstring64, e_font> window_market_get_order_instruction(int instr_kind, e_resource resource, int market_order);
std::pair<bstring64, e_font> window_building_get_order_instruction(int instr_kind, const storage_t &storage, e_resource resource);
std::pair<bstring64, e_font> window_dock_get_order_instruction(int instr_kind, e_resource resource, int dock_order);
