#include "utility.h"

#include "building/building_roadblock.h"
#include "graphics/graphics.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/image.h"
#include "graphics/window.h"
#include "grid/water_supply.h"
#include "window/building/common.h"

void window_building_draw_fountain(object_info* c) {
    c->help_id = 61;
    window_building_play_sound(c, "Wavs/fountain.wav");
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(108, 0, c->offset.x, c->offset.y + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    int text_id;
    building* b = building_get(c->building_id);
    if (b->has_water_access) {
        if (b->num_workers > 0)
            text_id = 1;
        else
            text_id = 2;
    } else if (c->has_reservoir_pipes)
        text_id = 2;
    else
        text_id = 3;
    window_building_draw_description(c, 108, text_id);
    inner_panel_draw(c->offset + vec2i{ 16, 166 }, { c->bgsize.x - 2, 4 });
    window_building_draw_employment_without_house_cover(c, 172);
}