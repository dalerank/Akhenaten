#include "building_booth.h"

#include "building/building.h"
#include "building/count.h"
#include "city/object_info.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "grid/property.h"
#include "grid/image.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "widget/city/ornaments.h"
#include "widget/city/building_ghost.h"
#include "sound/sound_building.h"
#include "building/building_entertainment.h"
#include "city/labor.h"

buildings::model_t<building_booth> booth_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_booth);
void config_load_building_booth() {
    booth_m.load();
}

void building_booth::window_info_background(object_info &c) {
    c.help_id = 71;
    window_building_play_sound(&c, snd::get_building_info_sound("booth"));
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(72, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    building* b = building_get(c.building_id);
    if (!c.has_road_access) {
        window_building_draw_description(c, 69, 25);
    } else if (b->num_workers <= 0) {
        window_building_draw_description(c, 72, 4);
    } else if (!b->data.entertainment.num_shows) {
        window_building_draw_description(c, 72, 2);
    } else if (b->data.entertainment.days1) {
        window_building_draw_description(c, 72, 3);
    }

    inner_panel_draw(c.offset.x + 16, c.offset.y + 136, c.bgsize.x - 2, 6);
    window_building_draw_employment(&c, 138);
    if (b->data.entertainment.days1 > 0) {
        int width = lang_text_draw(72, 6, c.offset.x + 32, c.offset.y + 182, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw_amount(8, 44, 2 * b->data.entertainment.days1, c.offset.x + width + 32, c.offset.y + 182, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw(72, 7 + b->data.entertainment.days3_or_play, c.offset.x + 32, c.offset.y + 202, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        lang_text_draw(72, 5, c.offset.x + 32, c.offset.y + 182, FONT_NORMAL_BLACK_ON_DARK);
    }
}

void building_booth::spawn_figure() {
    if (!is_main()) {
        return;
    }

    if (common_spawn_figure_trigger(100)) {
        if (data.entertainment.days1 > 0) {
            create_roaming_figure(FIGURE_JUGGLER, FIGURE_ACTION_94_ENTERTAINER_ROAMING, BUILDING_SLOT_SERVICE);
        }
    }
}

bool building_booth::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) {
    int color_mask = 0;
    if (drawing_building_as_deleted(&base) || map_property_is_deleted(tile)) {
        color_mask = COLOR_MASK_RED;
    }

    int grid_offset = tile.grid_offset();
    if (map_image_at(grid_offset) == image_group(IMG_BOOTH)) {
        building_entertainment_draw_show_jugglers(ctx, &base, point, color_mask);
    }
    return true;
}

void building_booth::update_count() const {
    building_increase_type_count(type(), num_workers() > 0);
}

bool building_booth::draw_isometric_flat_building(tile2i point, painter &ctx) {
    int img_id = image_group(IMG_BOOTH);
    int tile_id = map_image_at(point.grid_offset());
    return (img_id != tile_id);
}

void building_booth::ghost_preview(painter &ctx, tile2i tile, vec2i pixel, int orientation) {
    int size = booth_m.building_size;
    int square_id = booth_m.anim["square"].first_img();
    for (int i = 0; i < size * size; i++) {
        ImageDraw::isometric(ctx, square_id + i, pixel + vec2i{((i % size) - (i / size)) * 30, ((i % size) + (i / size)) * 15}, COLOR_MASK_GREEN);
    }
    switch (orientation / 2) {
    case 0:
        draw_building_ghost(ctx, image_group(IMG_BOOTH), pixel, COLOR_MASK_GREEN);
        break;
    case 1:
        draw_building_ghost(ctx, image_group(IMG_BOOTH), pixel + vec2i{30, 15}, COLOR_MASK_GREEN);
        break;
    case 2:
        draw_building_ghost(ctx, image_group(IMG_BOOTH), pixel + vec2i{0, 30}, COLOR_MASK_GREEN);
        break;
    case 3:
        draw_building_ghost(ctx, image_group(IMG_BOOTH), pixel + vec2i{-30, 15}, COLOR_MASK_GREEN);
        break;
    }
}
