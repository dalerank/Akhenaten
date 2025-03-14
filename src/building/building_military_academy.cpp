#include "building_military_academy.h"

#include "building/count.h"
#include "graphics/elements/ui.h"
#include "window/building/common.h"

void building_military_academy::window_info_background(object_info &c) {
    c.help_id = 88;
    window_building_play_sound(&c, "Wavs/mil_acad.wav");
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(135, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);

    building* b = building_get(c.building_id);
    if (!b->has_road_access)
        window_building_draw_description(c, 69, 25);
    else if (b->num_workers <= 0)
        window_building_draw_description(c, 135, 2);
    else if (b->worker_percentage() >= 100)
        window_building_draw_description(c, 135, 1);
    else {
        window_building_draw_description(c, 135, 3);
    }
    inner_panel_draw(c.offset + vec2i{ 16, 136 }, { c.bgsize.x - 2, 4 });
    window_building_draw_employment(&c, 142);
}

void building_military_academy::spawn_figure() {
    common_spawn_figure_trigger(100);
}