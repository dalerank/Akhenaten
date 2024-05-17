#include "culture.h"

#include "building/building.h"
#include "graphics/graphics.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "io/gamefiles/lang.h"
#include "window/building/common.h"

void window_building_draw_oracle(object_info* c) {
    c->help_id = 67;
    window_building_play_sound(c, "wavs/oracle.wav");
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(110, 0, c->offset.x, c->offset.y + 12, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    window_building_draw_description_at(c, 16 * c->bgsize.y - 158, 110, 1);
}