#pragma once

#include "core/string.h"
#include "core/vec2i.h"

void button_none(int param1, int param2);

void button_border_draw(int x, int y, int width_pixels, int height_pixels, bool has_focus);

struct generic_button;
struct image_button;
struct mouse;

namespace ui {

void begin_window(vec2i offset);
bool handle_mouse(const mouse *m);
int button_hover(const mouse *m);
generic_button &button(pcstr label, vec2i pos, vec2i size);
generic_button &button(uint32_t id);
image_button &img_button(uint32_t group, uint32_t id, vec2i pos, vec2i size, int offset = 0);

}
