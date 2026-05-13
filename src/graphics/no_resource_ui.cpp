#include "no_resource_ui.h"

#include "graphics/color.h"
#include "graphics/graphics.h"
#include "graphics/screen.h"
#include "graphics/painter.h"
void ui::no_resource::graphics_draw_background(painter& ctx, int image_id, float scale, vec2i offset) {
    (void)image_id;
    (void)scale;
    (void)offset;
    // Solid backdrop when Pharaoh menu textures are unavailable (same warm tone family as UI chrome).
    ctx.fill_rect(vec2i{0, 0}, vec2i{screen_width(), screen_height()}, COLOR_SIDEBAR);
}

void ui::no_resource::button_border_fill(vec2i pos, vec2i size, bool hovered) {
    painter ctx = game.painter();
    const color fill = hovered ? COLOR_LIGHT_BLUE : 0xff505050;
    ctx.fill_rect(pos, size, fill);

    if (size.x <= 0 || size.y <= 0) {
        return;
    }

    const vec2i end = pos + size - vec2i{1, 1};
    const color hi = hovered ? COLOR_WHITE : COLOR_INSET_LIGHT;
    const color lo = hovered ? COLOR_FONT_LIGHT_GRAY : COLOR_INSET_DARK;

    graphics_draw_line(pos, vec2i{end.x, pos.y}, hi);
    graphics_draw_line(pos, vec2i{pos.x, end.y}, hi);
    graphics_draw_line(vec2i{end.x, pos.y}, end, lo);
    graphics_draw_line(vec2i{pos.x, end.y}, end, lo);
}

void ui::no_resource::large_label_fill(int x, int y, int width_blocks, int type, vec2i pixel_size) {
    const vec2i sz = (pixel_size.y > 0) ? pixel_size : vec2i{width_blocks * 16, 25};
    button_border_fill({x, y}, sz, type != 0);
}

void ui::no_resource::large_label_fill(vec2i pos, int width_blocks, int type) {
    const vec2i size{width_blocks * 16, 25};
    button_border_fill(pos, size, type != 0);
}