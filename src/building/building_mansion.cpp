#include "building_mansion.h"

#include "window/building/common.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"

void building_mansion::window_info_background(object_info &c) {
    c.help_id = 78;
    window_building_play_sound(&c, "wavs/gov_palace.wav");
    outer_panel_draw(c.offset, c.width_blocks, c.height_blocks);
    lang_text_draw_centered(103, 0, c.offset.x, c.offset.y + 10, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    window_building_draw_description_at(c, 16 * c.height_blocks - 143, 103, 1);
}