#include "building_raw_material.h"

#include "building/building.h"
#include "city/object_info.h"
#include "city/resource.h"
#include "core/calc.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/boilerplate.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "graphics/text.h"
#include "sound/sound_building.h"

static void building_raw_material_draw_info(object_info& c, int help_id, const char* type, int group_id, e_resource resource) {
    c.help_id = help_id;
    window_building_play_sound(&c, snd::get_building_info_sound(type));

    outer_panel_draw(c.x_offset, c.y_offset, c.width_blocks, c.height_blocks);
    ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_ICONS) + resource, c.x_offset + 10, c.y_offset + 10);
    lang_text_draw_centered(group_id, 0, c.x_offset, c.y_offset + 10, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);

    building* b = building_get(c.building_id);
    int pct_done = calc_percentage(b->data.industry.progress, 200);
    int width = lang_text_draw(group_id, 2, c.x_offset + 32, c.y_offset + 44, FONT_NORMAL_BLACK_ON_LIGHT);
    width += text_draw_percentage(pct_done, c.x_offset + 32 + width, c.y_offset + 44, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw(group_id, 3, c.x_offset + 32 + width, c.y_offset + 44, FONT_NORMAL_BLACK_ON_LIGHT);

    if (!c.has_road_access)
        window_building_draw_description_at(c, 70, 69, 25);
    else if (city_resource_is_mothballed(resource))
        window_building_draw_description_at(c, 70, group_id, 4);
    else if (b->data.industry.curse_days_left > 4)
        window_building_draw_description_at(c, 70, group_id, 11);
    else if (b->num_workers <= 0)
        window_building_draw_description_at(c, 70, group_id, 5);
    else if (c.worker_percentage >= 100)
        window_building_draw_description_at(c, 70, group_id, 6);
    else if (c.worker_percentage >= 75)
        window_building_draw_description_at(c, 70, group_id, 7);
    else if (c.worker_percentage >= 50)
        window_building_draw_description_at(c, 70, group_id, 8);
    else if (c.worker_percentage >= 25)
        window_building_draw_description_at(c, 70, group_id, 9);
    else
        window_building_draw_description_at(c, 70, group_id, 10);

    inner_panel_draw(c.x_offset + 16, c.y_offset + 136, c.width_blocks - 2, 4);
    window_building_draw_employment(&c, 142);
    window_building_draw_description_at(c, 16 * c.height_blocks - 136, group_id, 1);
}

void building_marble_quarry_draw_info(object_info& c) {
    building_raw_material_draw_info(c, 95, "marble_quarry", 118, RESOURCE_MARBLE);
}
void building_limestone_quarry_draw_info(object_info& c) {
    building_raw_material_draw_info(c, 93, "limestone_quarry", 119, RESOURCE_COPPER);
}
void building_gold_mine_draw_info(object_info& c) {
    building_raw_material_draw_info(c, 93, "gold_mine", e_text_info_gold_mine, RESOURCE_GOLD);
}
void building_timber_yard_draw_info(object_info& c) {
    building_raw_material_draw_info(c, 94, "timber_yard", 120, RESOURCE_TIMBER);
}
void building_clay_pit_draw_info(object_info& c) {
    building_raw_material_draw_info(c, 92, "clay_pit", e_text_info_clay_pit, RESOURCE_CLAY);
}
// TODO: fix reed gatherer panel
void building_reed_gatherer_draw_info(object_info& c) {
    building_raw_material_draw_info(c, 92, "reed_farm", 116, RESOURCE_REEDS);
}
