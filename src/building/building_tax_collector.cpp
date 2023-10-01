#include "building_tax_collector.h"

#include "building/building.h"
#include "city/object_info.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/boilerplate.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "sound/sound_building.h"

void building_tax_collector_draw_info(object_info* c) {
    c->help_id = e_text_building_tax_collector;
    window_building_play_sound(c, snd::get_building_info_sound("tax_collector"));
    outer_panel_draw(c->x_offset, c->y_offset, c->width_blocks, c->height_blocks);
    lang_text_draw_centered(106, 0, c->x_offset, c->y_offset + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    ImageDraw::img_generic(image_id_resource_icon(RESOURCE_DEBEN), c->x_offset + 16, c->y_offset + 36);

    building* b = building_get(c->building_id);
    int width = lang_text_draw(106, 2, c->x_offset + 44, c->y_offset + 43, FONT_NORMAL_BLACK_ON_LIGHT);
    if (config_get(CONFIG_GP_CH_NEW_TAX_COLLECTION_SYSTEM)) {
        lang_text_draw_amount(8, 0, b->deben_storage, c->x_offset + 44 + width, c->y_offset + 43, FONT_NORMAL_BLACK_ON_LIGHT);
    } else {
        lang_text_draw_amount(8, 0, b->tax_income_or_storage, c->x_offset + 44 + width, c->y_offset + 43, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    if (!c->has_road_access) {
        window_building_draw_description(c, 69, 25);
    } else if (b->num_workers <= 0) {
        window_building_draw_description_at(c, 72, 106, 10);
    } else if (c->worker_percentage >= 100) {
        window_building_draw_description_at(c, 72, 106, 5);
    } else if (c->worker_percentage >= 75) {
        window_building_draw_description_at(c, 72, 106, 6);
    } else if (c->worker_percentage >= 50) {
        window_building_draw_description_at(c, 72, 106, 7);
    } else if (c->worker_percentage >= 25) {
        window_building_draw_description_at(c, 72, 106, 8);
    } else {
        window_building_draw_description_at(c, 72, 106, 9);
    }

    inner_panel_draw(c->x_offset + 16, c->y_offset + 136, c->width_blocks - 2, 4);
    window_building_draw_employment(c, 142);
}
