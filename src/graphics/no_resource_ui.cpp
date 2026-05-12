#include "no_resource_ui.h"

#include "font.h"
#include "graphics/color.h"
#include "graphics/graphics.h"
#include "graphics/screen.h"
#include "graphics/painter.h"

#include <algorithm>
#include <cstring>

void ui::no_resource::graphics_draw_background(painter& ctx, int image_id, float scale, vec2i offset) {
    (void)image_id;
    (void)scale;
    (void)offset;
    // Solid backdrop when Pharaoh menu textures are unavailable (same warm tone family as UI chrome).
    ctx.fill_rect(vec2i{0, 0}, vec2i{screen_width(), screen_height()}, COLOR_SIDEBAR);
}

void ui::no_resource::button_border_fill(vec2i pos, vec2i size, bool hovered) {
    const color fill = hovered ? COLOR_LIGHT_BLUE : 0xff505050;
    graphics_fill_rect(pos, size, fill);
    graphics_draw_rect(pos, size, COLOR_WHITE);
}