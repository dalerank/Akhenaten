#include "building_police_station.h"

#include "city/object_info.h"
#include "window/building/common.h"
#include "graphics/elements/ui.h"

buildings::model_t<building_police_station> police_station_m;

void building_police_station::window_info_background(object_info &c) {
    c.help_id = 86;
    window_building_play_sound(&c, "Wavs/prefecture.wav");
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(88, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);

    building* b = building_get(c.building_id);
    if (!b->has_road_access)
        window_building_draw_description(c, 69, 25);
    else if (!b->num_workers)
        window_building_draw_description(c, 88, 9);
    else {
        if (b->has_figure(0))
            window_building_draw_description(c, 88, 2);
        else
            window_building_draw_description(c, 88, 3);

        if (b->worker_percentage() >= 100)
            window_building_draw_description_at(c, 72, 88, 4);
        else if (b->worker_percentage() >= 75)
            window_building_draw_description_at(c, 72, 88, 5);
        else if (b->worker_percentage() >= 50)
            window_building_draw_description_at(c, 72, 88, 6);
        else if (b->worker_percentage() >= 25)
            window_building_draw_description_at(c, 72, 88, 7);
        else
            window_building_draw_description_at(c, 72, 88, 8);
    }

    inner_panel_draw(c.offset + vec2i{ 16, 136 }, { c.bgsize.x - 2, 4 });
    window_building_draw_employment(&c, 142);
}

void building_police_station::spawn_figure() {
    common_spawn_roamer(FIGURE_CONSTABLE, 50, FIGURE_ACTION_70_FIREMAN_CREATED);
}
