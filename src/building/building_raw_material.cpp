#include "building_raw_material.h"

#include "building/building.h"
#include "city/object_info.h"
#include "city/resource.h"
#include "core/calc.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/boilerplate.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "graphics/text.h"
#include "sound/sound_building.h"
#include "game/game.h"

static void building_raw_material_draw_info(object_info& c, const char* type, e_resource resource) {
    auto &meta = building::get_info(type);
    painter ctx = game.painter();
    c.help_id = meta.help_id;
    window_building_play_sound(&c, snd::get_building_info_sound(type));

    outer_panel_draw(c.offset, c.width_blocks, c.height_blocks);
    ImageDraw::img_generic(ctx, image_id_resource_icon(resource), c.offset.x + 10, c.offset.y + 10);
    lang_text_draw_centered(meta.text_id, 0, c.offset.x, c.offset.y + 10, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);

    building* b = building_get(c.building_id);
    int pct_done = calc_percentage<int>(b->data.industry.progress, 200);
    int width = lang_text_draw(meta.text_id, 2, c.offset.x + 32, c.offset.y + 44, FONT_NORMAL_BLACK_ON_LIGHT);
    width += text_draw_percentage(pct_done, c.offset.x + 32 + width, c.offset.y + 44, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw(meta.text_id, 3, c.offset.x + 32 + width, c.offset.y + 44, FONT_NORMAL_BLACK_ON_LIGHT);

    if (!c.has_road_access)
        window_building_draw_description_at(c, 70, 69, 25);
    else if (city_resource_is_mothballed(resource))
        window_building_draw_description_at(c, 70, meta.text_id, 4);
    else if (b->data.industry.curse_days_left > 4)
        window_building_draw_description_at(c, 70, meta.text_id, 11);
    else if (b->num_workers <= 0)
        window_building_draw_description_at(c, 70, meta.text_id, 5);
    else if (c.worker_percentage >= 100)
        window_building_draw_description_at(c, 70, meta.text_id, 6);
    else if (c.worker_percentage >= 75)
        window_building_draw_description_at(c, 70, meta.text_id, 7);
    else if (c.worker_percentage >= 50)
        window_building_draw_description_at(c, 70, meta.text_id, 8);
    else if (c.worker_percentage >= 25)
        window_building_draw_description_at(c, 70, meta.text_id, 9);
    else
        window_building_draw_description_at(c, 70, meta.text_id, 10);

    inner_panel_draw(c.offset.x + 16, c.offset.y + 136, c.width_blocks - 2, 4);
    window_building_draw_employment(&c, 142);
    window_building_draw_description_at(c, 16 * c.height_blocks - 136, meta.text_id, 1);
}

void building_marble_quarry_draw_info(object_info& c) {
    building_raw_material_draw_info(c, "marble_quarry", RESOURCE_MARBLE);
}
void building_limestone_quarry_draw_info(object_info& c) {
    building_raw_material_draw_info(c, "limestone_quarry", RESOURCE_LIMESTONE);
}
void building_gold_mine_draw_info(object_info& c) {
    building_raw_material_draw_info(c, "gold_mine", RESOURCE_GOLD);
}
void building_copper_mine_draw_info(object_info& c) {
    building_raw_material_draw_info(c, "copper_mine", RESOURCE_COPPER);
}
void building_timber_yard_draw_info(object_info& c) {
    building_raw_material_draw_info(c, "timber_yard", RESOURCE_TIMBER);
}
void building_clay_pit_draw_info(object_info& c) {
    building_raw_material_draw_info(c, "clay_pit", RESOURCE_CLAY);
}
void building_reed_gatherer_draw_info(object_info& c) {
    building_raw_material_draw_info(c, "reed_farm", RESOURCE_REEDS);
}
void building_sandstone_quarry_draw_info(object_info& c) {
    building_raw_material_draw_info(c, "sandstone_quarry", RESOURCE_SANDSTONE);
}
void building_granite_quarry_draw_info(object_info& c) {
    building_raw_material_draw_info(c, "granite_quarry", RESOURCE_SANDSTONE);
}
void building_plainstone_quarry_draw_info(object_info& c) {
    building_raw_material_draw_info(c, "plainstone_quarry", RESOURCE_STONE);
}