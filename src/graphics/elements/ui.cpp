#include "ui.h"

#include "generic_button.h"
#include "image_button.h"
#include "lang_text.h"
#include "panel.h"
#include "game/game.h"
#include "graphics/boilerplate.h"

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

void ui::label(int group, int number, vec2i pos, int box_width, font_t font, UiFlags_ flags) {
    const vec2i offset = g_state.offset;
    if (!!(flags & UiFlags_LabelCentered)) {
        lang_text_draw_centered(group, number, offset.x + pos.x, offset.y + pos.y, box_width, font);
    }
}

void ui::panel(vec2i pos, vec2i size, UiFlags_ flags) {
    const vec2i offset = g_state.offset;
    if (!!(flags & UiFlags_PanelOuter)) {
        outer_panel_draw(offset + pos, size.x, size.y);
    }
}

void ui::icon(vec2i pos, e_resource img) {
    const vec2i offset = g_state.offset;
    painter ctx = game.painter();
    ImageDraw::img_generic(ctx, image_id_resource_icon(RESOURCE_DEBEN), offset.x + pos.x, offset.y + pos.y);
}
