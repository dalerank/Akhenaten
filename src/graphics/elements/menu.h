#ifndef GRAPHICS_MENU_H
#define GRAPHICS_MENU_H

#include "input/mouse.h"

#define TOP_MENU_HEIGHT 30
#define SIDEBAR_EXPANDED_WIDTH 186

typedef struct {
    short text_group;
    short text_number;
    void (*left_click_handler)(int param);
    int parameter;
    int hidden;
} menu_item;

typedef struct {
    short text_group;
    menu_item *items;
    int num_items;
    short x_start;
    short x_end;
    int calculated_width_blocks;
    int calculated_height_blocks;
} menu_bar_item;

#endif // GRAPHICS_MENU_H
