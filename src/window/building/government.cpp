#include "government.h"

#include "building/building.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "game/resource.h"
#include "graphics/boilerplate.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "window/building/figures.h"
#include "window/building/common.h"

void window_building_draw_triumphal_arch(object_info* c) {
    c->help_id = 79;
    window_building_play_sound(c, "wavs/statue.wav");
    outer_panel_draw(c->offset, c->width_blocks, c->height_blocks);
    lang_text_draw_centered(80, 2, c->offset.x, c->offset.y + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    window_building_draw_description_at(c, 16 * c->height_blocks - 158, 80, 3);
}

// TODO: fix courthouse panel
void window_building_draw_courthouse(object_info* c) {
    const int LANG_GROUP_ID = 176;
    c->help_id = 76;
    window_building_play_sound(c, "wavs/forum.wav");
    outer_panel_draw(c->offset, c->width_blocks, c->height_blocks);
    lang_text_draw_centered(LANG_GROUP_ID, 0, c->offset.x, c->offset.y + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);

    building* b = building_get(c->building_id);

    if (!c->has_road_access)
        window_building_draw_description(c, 69, 25);
    else if (b->num_workers <= 0)
        window_building_draw_description_at(c, 72, LANG_GROUP_ID, 10);
    else if (c->worker_percentage >= 100)
        window_building_draw_description_at(c, 72, LANG_GROUP_ID, 5);
    else if (c->worker_percentage >= 75)
        window_building_draw_description_at(c, 72, LANG_GROUP_ID, 6);
    else if (c->worker_percentage >= 50)
        window_building_draw_description_at(c, 72, LANG_GROUP_ID, 7);
    else if (c->worker_percentage >= 25)
        window_building_draw_description_at(c, 72, LANG_GROUP_ID, 8);
    else {
        window_building_draw_description_at(c, 72, LANG_GROUP_ID, 9);
    }

    inner_panel_draw(c->offset.x + 16, c->offset.y + 136, c->width_blocks - 2, 4);
    window_building_draw_employment(c, 142);
}
