#include "button.h"

#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/view/view.h"
#include "game/game.h"

void button_none(int param1, int param2) {
}

void button_border_draw(vec2i pos, vec2i size, bool has_focus) {
    painter ctx = game.painter();
    int width_blocks = size.x / 16;
    width_blocks += (size.x % 16) ? 1 : 0;

    int height_blocks = size.y / 16;
    height_blocks += (size.y % 16) ? 1 : 0;

    int last_block_offset_x = 16 * width_blocks - size.x;
    int last_block_offset_y = 16 * height_blocks - size.y;

    int image_base = image_id_from_group(GROUP_BORDERED_BUTTON);
    if (has_focus) {
        image_base += 8;
    }

    for (int yy = 0; yy < height_blocks; yy++) {
        vec2i draw_offset = {0, pos.y + 16 * yy};
        for (int xx = 0; xx < width_blocks; xx++) {
            draw_offset.x = pos.x + 16 * xx;
            if (yy == 0) {
                if (xx == 0) ctx.img_generic(image_base, draw_offset);
                else if (xx < width_blocks - 1) ctx.img_generic(image_base + 1, draw_offset);
                else ctx.img_generic(image_base + 2, draw_offset - vec2i{last_block_offset_x, 0});
            } else if (yy < height_blocks - 1) {
                if (xx == 0) ctx.img_generic(image_base + 7, draw_offset);
                else if (xx >= width_blocks - 1) ctx.img_generic(image_base + 3, draw_offset - vec2i{last_block_offset_x, 0});
            } else {
                if (xx == 0)ctx.img_generic(image_base + 6, draw_offset - vec2i{0, last_block_offset_y});
                else if (xx < width_blocks - 1) ctx.img_generic(image_base + 5, draw_offset - vec2i{0, last_block_offset_y});
                else ctx.img_generic(image_base + 4, draw_offset - vec2i{last_block_offset_x, last_block_offset_y});
            }
        }
    }
}

bool button_inside_clip(vec2i p) {
    return graphics_inside_clip_rectangle(p);
}
