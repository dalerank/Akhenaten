#ifndef GRAPHICS_MENU_H
#define GRAPHICS_MENU_H

#include "input/mouse.h"

#define TOP_MENU_HEIGHT 30
#define SIDEBAR_EXPANDED_WIDTH 186

struct menu_item {
    short text_group;
    short text_number;
    void (*left_click_handler)(int param);
    int parameter;
    int hidden;
    const char *text_raw = nullptr;
};

struct menu_bar_item {
    short text_group;
    menu_item *items;
    size_t num_items;
    const char *text_raw = nullptr;
    short x_start;
    short x_end;
    int calculated_width_blocks;
    int calculated_height_blocks;
};

#endif // GRAPHICS_MENU_H
