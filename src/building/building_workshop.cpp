#include "building_plaza.h"

#include "building/building.h"
#include "city/object_info.h"
#include "city/resource.h"
#include "core/calc.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/boilerplate.h"
#include "graphics/text.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"

static void building_workshop_draw_info(object_info& c, int help_id, const char* type, int group_id, int resource, int input_resource) {
    c.help_id = help_id;
    window_building_play_sound(&c, snd::get_building_info_sound(type));

    outer_panel_draw(c.x_offset, c.y_offset, c.width_blocks, c.height_blocks);
    ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_ICONS) + resource, c.x_offset + 10, c.y_offset + 10);
    lang_text_draw_centered(group_id, 0, c.x_offset, c.y_offset + 10, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);

    building* b = building_get(c.building_id);
    int pct_done = calc_percentage(b->data.industry.progress, 400);
    int width = lang_text_draw(group_id, 2, c.x_offset + 32, c.y_offset + 40, FONT_NORMAL_BLACK_ON_LIGHT);
    width += text_draw_percentage(pct_done, c.x_offset + 32 + width, c.y_offset + 40, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw(group_id, 3, c.x_offset + 32 + width, c.y_offset + 40, FONT_NORMAL_BLACK_ON_LIGHT);

    ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_ICONS) + input_resource, c.x_offset + 32, c.y_offset + 56);
    width = lang_text_draw(group_id, 12, c.x_offset + 60, c.y_offset + 60, FONT_NORMAL_BLACK_ON_LIGHT);
    if (b->stored_full_amount < 100)
        lang_text_draw_amount(8, 10, 0, c.x_offset + 60 + width, c.y_offset + 60, FONT_NORMAL_BLACK_ON_LIGHT);
    else
        lang_text_draw_amount(8, 10, b->stored_full_amount, c.x_offset + 60 + width, c.y_offset + 60, FONT_NORMAL_BLACK_ON_LIGHT);

    if (!c.has_road_access)
        window_building_draw_description_at(c, 86, 69, 25);
    else if (city_resource_is_mothballed(resource))
        window_building_draw_description_at(c, 86, group_id, 4);
    else if (b->num_workers <= 0)
        window_building_draw_description_at(c, 86, group_id, 5);
    else if (b->stored_full_amount <= 0)
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

void building_brewery_draw_info(object_info& c) {
    int input_resource = RESOURCE_BARLEY;
    int output_resource = RESOURCE_BEER;

    building_workshop_draw_info(c, 96, "brewery", 122, output_resource, input_resource);
}
void building_flax_workshop_draw_info(object_info& c) {
    int input_resource = RESOURCE_FLAX;
    int output_resource = RESOURCE_LINEN;
    building_workshop_draw_info(c, 97, "flax_workshop", 123, output_resource, input_resource);
}
void building_weapons_workshop_draw_info(object_info& c) {
    int output_resource = RESOURCE_WEAPONS;

    building_workshop_draw_info(c, 98, "weapons_workshop", 124, output_resource, RESOURCE_COPPER);
}
void building_luxury_workshop_draw_info(object_info& c) {
    int input_resource = RESOURCE_GEMS;
    int output_resource = RESOURCE_LUXURY_GOODS;

    building_workshop_draw_info(c, 99, "luxury_workshop", 125, output_resource, input_resource);
}
void building_pottery_workshop_draw_info(object_info& c) {
    int output_resource = RESOURCE_POTTERY;

    building_workshop_draw_info(c, 1, "pottery_workshop", 126, output_resource, RESOURCE_CLAY);
}
// TODO: fix brick maker panel
void building_brick_maker_workshop_draw_info(object_info& c) {
    int output_resource = RESOURCE_POTTERY;

    building_workshop_draw_info(c, 1, "brick_maker", 126, output_resource, RESOURCE_CLAY);
}
