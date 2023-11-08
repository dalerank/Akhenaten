#include "building_hunting_lodge.h"

#include "building/building.h"
#include "city/object_info.h"
#include "city/resource.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/boilerplate.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"

void building_hunting_lodge_draw_info(object_info &c) {
    view_context ctx = view_context_main();
    int group_id = 154;
    c.help_id = 90;
    window_building_play_sound(&c, snd::get_building_info_sound("hunting_lodge"));

    outer_panel_draw(c.x_offset, c.y_offset, c.width_blocks, c.height_blocks);
    lang_text_draw_centered(group_id, 0, c.x_offset, c.y_offset + 10, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);

    building* b = building_get(c.building_id);
    ImageDraw::img_generic(ctx, image_id_from_group(GROUP_RESOURCE_ICONS) + RESOURCE_GAMEMEAT, c.x_offset + 32, c.y_offset + 56);
    int width = lang_text_draw(group_id, 13, c.x_offset + 60, c.y_offset + 60, FONT_NORMAL_BLACK_ON_LIGHT);
    if (!b->workshop_has_resources()) {
        lang_text_draw_amount(8, 10, 0, c.x_offset + 60 + width, c.y_offset + 60, FONT_NORMAL_BLACK_ON_LIGHT);
    } else {
        lang_text_draw_amount(8, 10, b->stored_amount(), c.x_offset + 60 + width, c.y_offset + 60, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    if (!c.has_road_access)
        window_building_draw_description_at(c, 86, 69, 25);
    else if (city_resource_is_mothballed(RESOURCE_GAMEMEAT))
        window_building_draw_description_at(c, 86, group_id, 4);
    else if (b->num_workers <= 0)
        window_building_draw_description_at(c, 86, group_id, 5);
    else if (b->stored_amount() <= 0)
        window_building_draw_description_at(c, 86, group_id, 11);
    else if (c.worker_percentage >= 100)
        window_building_draw_description_at(c, 86, group_id, 6);
    else if (c.worker_percentage >= 75)
        window_building_draw_description_at(c, 86, group_id, 7);
    else if (c.worker_percentage >= 50)
        window_building_draw_description_at(c, 86, group_id, 8);
    else if (c.worker_percentage >= 25)
        window_building_draw_description_at(c, 86, group_id, 9);
    else
        window_building_draw_description_at(c, 86, group_id, 10);

    inner_panel_draw(c.x_offset + 16, c.y_offset + 136, c.width_blocks - 2, 4);
    window_building_draw_employment(&c, 142);
}
