#include "screen.h"

#include "graphics/image.h"
#include "city/city_warnings.h"
#include "graphics/view/view.h"
#include "platform/renderer.h"
#include "graphics/graphics.h"
#include "window.h"

struct screen_data_t {
    int width;
    int height;
    vec2i dialog_offset;
};

screen_data_t g_screen_data;

void screen_set_resolution(int width, int height) {
    g_screen_data.width = width;
    g_screen_data.height = height;
    g_screen_data.dialog_offset.x = (width - 640) / 2;
    g_screen_data.dialog_offset.y = (height - 480) / 2;

    graphics_clear_screen();
    graphics_renderer()->set_clip_rectangle({ 0, 0 }, width, height);

    city_view_set_viewport(width, height);
    g_warning_manager.clear_all();
}

int screen_width(void) {
    return g_screen_data.width;
}
int screen_height(void) {
    return g_screen_data.height;
}
vec2i screen_size() {
    return {g_screen_data.width, g_screen_data.height};
}

int screen_dialog_offset_x(void) {
    return g_screen_data.dialog_offset.x;
}
int screen_dialog_offset_y(void) {
    return g_screen_data.dialog_offset.y;
}
