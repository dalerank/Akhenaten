#include "graphics/graphics.h"

#include "core/profiler.h"
#include "platform/renderer.h"

void graphics_clear_screen() {
    OZZY_PROFILER_SECTION("Render/Frame/Clear Screen");
    graphics_renderer()->clear_screen();
}

void graphics_draw_line(vec2i start, vec2i end, color color) {
    graphics_renderer()->draw_line(start, end, color);
}
void graphics_draw_vertical_line(vec2i start, int ny, color color) {
    graphics_renderer()->draw_line(start, vec2i{start.x, start.y + ny}, color);
}
void graphics_draw_horizontal_line(vec2i start, int nx, color color) {
    graphics_renderer()->draw_line(start, vec2i{start.x + nx, start.y}, color);
}
void graphics_draw_pixel(vec2i pixel, color color) {
    graphics_renderer()->draw_pixel(pixel, color);
}
void graphics_draw_rect(vec2i start, vec2i size, color color) {
    graphics_renderer()->draw_rect(start, size, color);
}

void graphics_fill_rect(vec2i start, vec2i size, color color) {
    graphics_renderer()->fill_rect(start, size, color);
}

void graphics_shade_rect(vec2i start, vec2i size, int darkness) {
    color alpha = (darkness << COLOR_BITSHIFT_ALPHA);
    graphics_renderer()->fill_rect(start, size, alpha);
}