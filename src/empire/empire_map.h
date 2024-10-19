#pragma once

#include "game/resource.h"
#include "core/vec2i.h"
#include "empire_object.h"

class empire_map_t {
public:
    int initial_scroll_x;
    int initial_scroll_y;
    int scroll_x;
    int scroll_y;
    int selected_obj;
    int viewport_width;
    int viewport_height;

public:
    void init_scenario();
    void scroll_map(vec2i pos);
    void set_viewport(vec2i size);
    vec2i get_scroll();
    vec2i adjust_scroll(vec2i pos);
    void set_scroll(vec2i pos);
    int selected_object();
    void clear_selected_object();
    void select_object(vec2i pos);

private:
    void check_scroll_boundaries();
};

extern empire_map_t g_empire_map;

void empire_load_editor(int empire_id, int viewport_width, int viewport_height);
