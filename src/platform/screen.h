#pragma once

#include "platform/platform.h"
#include "core/vec2i.h"
#include "core/xstring.h"

struct platform_screen_t {
    vec2i pos;
    int centered = 0;
    vec2i minimum = {640, 480};
    int scale_percentage = 100;

    int scale_logical_to_pixels(int logical_value) const { return logical_value * scale_percentage / 100; }
    int scale_pixels_to_logical(int pixel_value) const { return pixel_value * 100 / scale_percentage; }
    int get_scale() const { return scale_percentage; }

    int create(const xstring& title, const xstring& renderer, bool fullscreen, int display_scale_percentage,
      vec2i screen_size);
    void destroy();
    bool resize(int pixel_width, int pixel_height, int save);
    void move(int x, int y);
    void set_fullscreen();
    void set_windowed();
    void set_window_size(int logical_width, int logical_height);
    void center_window();
    void show_error_message_box(const char* title, const char* message);
    void warp_mouse(int* x, int* y);
    void* surface_format();
    vec2i get_max_resolution();
    void recreate_texture();

private:
    void* window = nullptr;

    void set_scale_percentage(int new_scale, int pixel_width, int pixel_height);
    int scale_display(int display_scale_percentage);
};

extern platform_screen_t g_platform_screen;