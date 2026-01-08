#pragma once

#include "input/mouse.h"
#include "core/xstring.h"
#include "core/svector.h"
#include <functional>

#define TOP_MENU_HEIGHT 30

struct menu_item {
    short text_group;
    short text_number;
    std::function<void(int)> _onclick;
    int parameter;
    int hidden = false;
    
    xstring text;
    xstring id;

    xstring _js_onclick;
    xstring _js_text;
};

struct menu_header {
    svector<menu_item, 48> items;
    xstring text;
    short x_start;
    short x_end;
    int calculated_width_blocks;
    int calculated_height_blocks;
    std::function<void(menu_item&)> _onclick;
};
