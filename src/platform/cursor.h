#pragma once

#include "core/xvalue.h"
#include "graphics/color.h"
#include "input/cursor.h"

struct platform_cursor_t {
    int current_id = CURSOR_ARROW;

    void init(int scale_percentage);
    void set(int cursor_id);
    cursor_shape current() const { return static_cast<cursor_shape>(current_id); }

    static cursor_scale scale_for(int scale_percentage);

private:
    struct mouse_color_t {
        char type;
        color value;
    };

    void* cursors[CURSOR_MAX] = {};
    void* surfaces[CURSOR_MAX] = {};

    static constexpr mouse_color_t mouse_colors[] = {
      {' ', ALPHA_TRANSPARENT},
      {'#', ALPHA_OPAQUE | COLOR_BLACK},
      {'$', ALPHA_OPAQUE | COLOR_MOUSE_DARK_GRAY},
      {'%', ALPHA_OPAQUE | COLOR_MOUSE_MEDIUM_GRAY},
      {'&', ALPHA_OPAQUE | COLOR_MOUSE_LIGHT_GRAY},
      {'\'', ALPHA_OPAQUE | COLOR_WHITE},
    };

    void* generate_cursor_surface(const char* data, int width, int height);
    static color color_for(char type);
};
