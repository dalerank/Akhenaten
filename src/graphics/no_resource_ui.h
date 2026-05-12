#pragma once

#include "core/cstring.h"
#include "core/vec2i.h"
#include "graphics/color.h"
#include "graphics/image.h"

struct painter;

namespace ui {
    namespace no_resource {
        void button_border_fill(vec2i pos, vec2i size, bool hovered);
        void graphics_draw_background(painter& ctx, int image_id, float scale, vec2i offset);
        void large_label_fill(vec2i pos, int width_blocks, int type);
    }
}
