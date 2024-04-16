#include "building_entertainment.h"

#include "building/building.h"
#include "city/object_info.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "widget/city/ornaments.h"
#include "graphics/animation.h"

void building_entertainment_school_draw_info(object_info& c, pcstr type, int group_id) {
    c.help_id = 75;
    window_building_play_sound(&c, snd::get_building_info_sound(type));

    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(group_id, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    if (!c.has_road_access) {
        window_building_draw_description(c, 69, 25);
    } else if (building_get(c.building_id)->num_workers <= 0) {
        window_building_draw_description(c, group_id, 7);
    } else if (c.worker_percentage >= 100) {
        window_building_draw_description(c, group_id, 2);
    } else if (c.worker_percentage >= 75) {
        window_building_draw_description(c, group_id, 3);
    } else if (c.worker_percentage >= 50) {
        window_building_draw_description(c, group_id, 4);
    } else if (c.worker_percentage >= 25) {
        window_building_draw_description(c, group_id, 5);
    } else {
        window_building_draw_description(c, group_id, 6);
    }
    inner_panel_draw(c.offset.x + 16, c.offset.y + 136, c.bgsize.x - 2, 4);
    window_building_draw_employment(&c, 142);
}

void building_dancer_school_draw_info(object_info& c) {
    building_entertainment_school_draw_info(c, "dancer_school", 76);
}

void building_bullfight_school_draw_info(object_info& c) {
    building_entertainment_school_draw_info(c, "bullfight_school", 78);
}
