#include "button.h"

#include "graphics/boilerplate.h"
#include "graphics/view/view.h"
#include "game/game.h"
#include "generic_button.h"
#include "image_button.h"

void button_none(int param1, int param2) {
}

void button_border_draw(int x, int y, int width_pixels, int height_pixels, bool has_focus) {
    painter ctx = game.painter();
    int width_blocks = width_pixels / 16;
    if (width_pixels % 16)
        width_blocks++;

    int height_blocks = height_pixels / 16;
    if (height_pixels % 16)
        height_blocks++;

    int last_block_offset_x = 16 * width_blocks - width_pixels;
    int last_block_offset_y = 16 * height_blocks - height_pixels;

    int image_base = image_id_from_group(GROUP_BORDERED_BUTTON);
    if (has_focus)
        image_base += 8;

    for (int yy = 0; yy < height_blocks; yy++) {
        vec2i draw_offset = {0, y + 16 * yy};
        for (int xx = 0; xx < width_blocks; xx++) {
            draw_offset.x = x + 16 * xx;
            if (yy == 0) {
                if (xx == 0)
                    ImageDraw::img_generic(ctx, image_base, draw_offset);
                else if (xx < width_blocks - 1)
                    ImageDraw::img_generic(ctx, image_base + 1, draw_offset);
                else
                    ImageDraw::img_generic(ctx, image_base + 2, draw_offset - vec2i{last_block_offset_x, 0});
            } else if (yy < height_blocks - 1) {
                if (xx == 0)
                    ImageDraw::img_generic(ctx, image_base + 7, draw_offset);
                else if (xx >= width_blocks - 1)
                    ImageDraw::img_generic(ctx, image_base + 3, draw_offset - vec2i{last_block_offset_x, 0});
            } else {
                if (xx == 0)
                    ImageDraw::img_generic(ctx, image_base + 6, draw_offset - vec2i{0, last_block_offset_y});
                else if (xx < width_blocks - 1)
                    ImageDraw::img_generic(ctx, image_base + 5, draw_offset - vec2i{0, last_block_offset_y});
                else
                    ImageDraw::img_generic(ctx, image_base + 4, draw_offset - vec2i{last_block_offset_x, last_block_offset_y});
            }
        }
    }
}

namespace ui {
    struct state {
        vec2i offset;
        std::vector<generic_button> buttons;
        std::vector<image_button> img_buttons;
    };

    state g_state;
    generic_button dummy;
}

void ui::begin_window(vec2i offset) {
    g_state.offset = offset;
    g_state.buttons.clear();
    g_state.img_buttons.clear();
}

bool ui::handle_mouse(const mouse *m) {
    bool handle = false;
    int tmp_btn = 0;
    handle |= !!generic_buttons_handle_mouse(m, g_state.offset, g_state.buttons, tmp_btn);
    handle |= image_buttons_handle_mouse(m, g_state.offset, g_state.img_buttons, tmp_btn);

    return handle;
}

int ui::button_hover(const mouse *m) {
    for (auto &btn : g_state.buttons) {
        if (is_button_hover(btn, g_state.offset)) {
            return (std::distance(&g_state.buttons.front(), &btn) + 1);
        }
    }

    return 0;
}

generic_button &ui::button(pcstr label, vec2i pos, vec2i size) {
    const vec2i offset = g_state.offset;

    g_state.buttons.push_back({pos.x, pos.y, size.x + 4, size.y + 4, button_none, button_none, 0, 0});
    int focused = is_button_hover(g_state.buttons.back(), offset);

    button_border_draw(offset.x + pos.x, offset.y + pos.y, size.x, size.y, focused ? 1 : 0);
    text_draw_centered((uint8_t *)label, offset.x + pos.x + 1, offset.y + pos.y + 4, 20, FONT_NORMAL_BLACK_ON_LIGHT, 0);

    return g_state.buttons.back();
}

generic_button &ui::button(uint32_t id) {
    return (id < g_state.buttons.size()) ? g_state.buttons[id] : dummy;
}

image_button &ui::img_button(uint32_t group, uint32_t id, vec2i pos, vec2i size, int offset) {
    const vec2i img_offset = g_state.offset;
    const mouse *m = mouse_get();

    g_state.img_buttons.push_back({pos.x, pos.y, size.x + 4, size.y + 4, IB_NORMAL, group, id, offset, button_none, button_none, 0, 0, true});
    auto &button = g_state.img_buttons.back();
    button.focused = is_button_hover(g_state.img_buttons.back(), img_offset);
    button.pressed = button.focused && m->left.is_down;
    image_buttons_draw(img_offset, button);

    return g_state.img_buttons.back();
}