#include "government.h"

#include "building/building.h"
#include "io/gamefiles/lang.h"
#include "game/game_config.h"
#include "game/resource.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "window/building/figures.h"
#include "window/building/common.h"

void window_building_draw_triumphal_arch(object_info* c) {
    c->help_id = 79;
    window_building_play_sound(c, "Wavs/statue.wav");
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(80, 2, c->offset.x, c->offset.y + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    window_building_draw_description_at(c, 16 * c->bgsize.y - 158, 80, 3);
}
