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
#include "game/game.h"

static void building_workshop_draw_info(object_info& c, int help_id, const char* type, int group_id, e_resource resource, e_resource input_resource) {
    c.help_id = help_id;
    window_building_play_sound(&c, snd::get_building_info_sound(type));

    painter ctx = game.painter();

    outer_panel_draw(c.offset.x, c.offset.y, c.width_blocks, c.height_blocks);
    ImageDraw::img_generic(ctx, image_id_resource_icon(resource), c.offset.x + 10, c.offset.y + 10);
    lang_text_draw_centered(group_id, 0, c.offset.x, c.offset.y + 10, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);

    building* b = building_get(c.building_id);
    int pct_done = calc_percentage<int>(b->data.industry.progress, 400);
    int width = lang_text_draw(group_id, 2, c.offset.x + 32, c.offset.y + 40, FONT_NORMAL_BLACK_ON_LIGHT);
    width += text_draw_percentage(pct_done, c.offset.x + 32 + width, c.offset.y + 40, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw(group_id, 3, c.offset.x + 32 + width, c.offset.y + 40, FONT_NORMAL_BLACK_ON_LIGHT);

    ImageDraw::img_generic(ctx, image_id_resource_icon(input_resource), c.offset.x + 32, c.offset.y + 56);
    width = lang_text_draw(group_id, 12, c.offset.x + 60, c.offset.y + 60, FONT_NORMAL_BLACK_ON_LIGHT);
    if (b->stored_amount() < 100) {
        lang_text_draw_amount(8, 10, 0, c.offset.x + 60 + width, c.offset.y + 60, FONT_NORMAL_BLACK_ON_LIGHT);
    } else {
        lang_text_draw_amount(8, 10, b->stored_amount(), c.offset.x + 60 + width, c.offset.y + 60, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    if (!c.has_road_access)
        window_building_draw_description_at(c, 86, 69, 25);
    else if (city_resource_is_mothballed(resource))
        window_building_draw_description_at(c, 86, group_id, 4);
    else if (b->num_workers <= 0)
        window_building_draw_description_at(c, 86, group_id, 5);
    else if (!b->workshop_has_resources())
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

    inner_panel_draw(c.offset.x + 16, c.offset.y + 136, c.width_blocks - 2, 4);
    window_building_draw_employment(&c, 142);
}

static void building_workshop_draw_info(object_info& c, int help_id, const char* type, int group_id, e_resource resource, e_resource input_resource_a, e_resource input_resource_b) {
    c.help_id = help_id;
    window_building_play_sound(&c, snd::get_building_info_sound(type));

    painter ctx = game.painter();

    outer_panel_draw(c.offset.x, c.offset.y, c.width_blocks, c.height_blocks);
    ImageDraw::img_generic(ctx, image_id_resource_icon(resource), c.offset.x + 10, c.offset.y + 10);
    lang_text_draw_centered(group_id, 0, c.offset.x, c.offset.y + 10, 16 * c.width_blocks, FONT_LARGE_BLACK_ON_LIGHT);

    building* b = building_get(c.building_id);
    int pct_done = calc_percentage<int>(b->data.industry.progress, 400);
    int width = lang_text_draw(group_id, 2, c.offset.x + 32, c.offset.y + 40, FONT_NORMAL_BLACK_ON_LIGHT);
    width += text_draw_percentage(pct_done, c.offset.x + 32 + width, c.offset.y + 40, FONT_NORMAL_BLACK_ON_LIGHT);
    lang_text_draw(group_id, 3, c.offset.x + 32 + width, c.offset.y + 40, FONT_NORMAL_BLACK_ON_LIGHT);

    ImageDraw::img_generic(ctx, image_id_resource_icon(input_resource_a), c.offset.x + 32, c.offset.y + 56);
    width = lang_text_draw(group_id, 13, c.offset.x + 60, c.offset.y + 60, FONT_NORMAL_BLACK_ON_LIGHT);

    if (b->stored_amount(input_resource_a) < 100) {
        lang_text_draw_amount(8, 10, 0, c.offset.x + 60 + width, c.offset.y + 60, FONT_NORMAL_BLACK_ON_LIGHT);
    } else {
        lang_text_draw_amount(8, 10, b->stored_amount(input_resource_a), c.offset.x + 60 + width, c.offset.y + 60, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    int y_offset = 80;
    ImageDraw::img_generic(ctx, image_id_resource_icon(input_resource_b), c.offset.x + 32, c.offset.y + y_offset);
    width = lang_text_draw(group_id, 14, c.offset.x + 60, c.offset.y + y_offset + 4, FONT_NORMAL_BLACK_ON_LIGHT);

    if (b->stored_amount(input_resource_b) < 100) {
        lang_text_draw_amount(8, 10, 0, c.offset.x + 60 + width, c.offset.y + y_offset + 4, FONT_NORMAL_BLACK_ON_LIGHT);
    } else {
        lang_text_draw_amount(8, 10, b->stored_amount(input_resource_b), c.offset.x + 60 + width, c.offset.y + y_offset + 4, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    y_offset = 110;
    if (!c.has_road_access)
        window_building_draw_description_at(c, y_offset, 69, 25);
    else if (city_resource_is_mothballed(resource))
        window_building_draw_description_at(c, y_offset, group_id, 4);
    else if (b->num_workers <= 0)
        window_building_draw_description_at(c, y_offset, group_id, 5);
    else if (b->workshop_has_resources())
        window_building_draw_description_at(c, y_offset, group_id, 11);
    else if (c.worker_percentage >= 100)
        window_building_draw_description_at(c, y_offset, group_id, 6);
    else if (c.worker_percentage >= 75)
        window_building_draw_description_at(c, y_offset, group_id, 7);
    else if (c.worker_percentage >= 50)
        window_building_draw_description_at(c, y_offset, group_id, 8);
    else if (c.worker_percentage >= 25)
        window_building_draw_description_at(c, y_offset, group_id, 9);
    else
        window_building_draw_description_at(c, y_offset, group_id, 10);

    inner_panel_draw(c.offset.x + 16, c.offset.y + y_offset + 40, c.width_blocks - 2, 4);
    window_building_draw_employment(&c, y_offset + 48);
}

void building_brewery_draw_info(object_info& c) {
    e_resource input_resource = RESOURCE_BARLEY;
    e_resource output_resource = RESOURCE_BEER;

    building_workshop_draw_info(c, 96, "brewery", 122, output_resource, input_resource);
}

void building_flax_workshop_draw_info(object_info& c) {
    e_resource input_resource = RESOURCE_FLAX;
    e_resource output_resource = RESOURCE_LINEN;
    building_workshop_draw_info(c, 97, "flax_workshop", 123, output_resource, input_resource);
}

void building_weapons_workshop_draw_info(object_info& c) {
    e_resource output_resource = RESOURCE_WEAPONS;

    building_workshop_draw_info(c, 98, "weapons_workshop", 124, output_resource, RESOURCE_COPPER);
}

void building_luxury_workshop_draw_info(object_info& c) {
    e_resource input_resource = RESOURCE_GEMS;
    e_resource output_resource = RESOURCE_LUXURY_GOODS;

    building_workshop_draw_info(c, 99, "luxury_workshop", 125, output_resource, input_resource);
}

void building_pottery_workshop_draw_info(object_info& c) {
    e_resource output_resource = RESOURCE_POTTERY;

    building_workshop_draw_info(c, 1, "pottery_workshop", 126, output_resource, RESOURCE_CLAY);
}

void building_papyrus_workshop_draw_info(object_info& c) {
    e_resource output_resource = RESOURCE_PAPYRUS;

    building_workshop_draw_info(c, 1, "papyrus_workshop", 190, output_resource, RESOURCE_REEDS);
}

void building_cattle_ranch_draw_info(object_info &c) {
    e_resource output_resource = RESOURCE_MEAT;

    building_workshop_draw_info(c, 1, "cattle_ranch", 117, output_resource, RESOURCE_STRAW);
}

void building_brick_maker_workshop_draw_info(object_info& c) {
    e_resource output_resource = RESOURCE_BRICKS;

    building_workshop_draw_info(c, 1, "brick_maker", 180, output_resource, RESOURCE_CLAY, RESOURCE_STRAW);
}

void building_workshop_draw_raw_material_storage(painter &ctx, const building* b, vec2i pos, color color_mask) {
    int amount = ceil((float)b->stored_amount() / 100.0) - 1;
    int amount2 = 0;
    switch (b->type) {
        case BUILDING_HUNTING_LODGE:
        if (amount >= 0) {
            ImageDraw::img_generic(ctx, image_id_from_group(IMG_RESOURCE_GAMEMEAT) + amount, pos + vec2i{61, 14}, color_mask);
        }
        break;

    case BUILDING_BRICKS_WORKSHOP:
        amount = std::min<int>(2, ceil((float)b->stored_amount(RESOURCE_CLAY) / 100.0) - 1);
        amount2 = std::min<int>(2, ceil((float)b->stored_amount(RESOURCE_STRAW) / 100.0) - 1);
        if (amount >= 0) {
            ImageDraw::img_generic(ctx, image_id_from_group(IMG_RESOURCE_CLAY) + amount, pos + vec2i{46, 25}, color_mask);
        }

        if (amount2 >= 0) {
            ImageDraw::img_generic(ctx, image_id_from_group(IMG_RESOURCE_STRAW) + amount, pos + vec2i{51, 18}, color_mask);
        }
        break;

    case BUILDING_WEAPONS_WORKSHOP:
        amount = std::min<int>(2, ceil((float)b->stored_amount() / 100.0) - 1);
        if (amount >= 0) {
            ImageDraw::img_generic(ctx, image_id_from_group(GROUP_RESOURCE_STOCK_COPPER_2) + amount, pos + vec2i{61, 14}, color_mask);
        }
        break;

    case BUILDING_POTTERY_WORKSHOP:
        amount = std::min<int>(2, ceil((float)b->stored_amount() / 100.0) - 1);
        if (amount >= 0) {
            ImageDraw::img_generic(ctx, image_id_from_group(IMG_RESOURCE_CLAY) + amount, pos + vec2i{65, 3}, color_mask);
        }
        break;

    case BUILDING_BEER_WORKSHOP:
        amount = std::min<int>(2, ceil((float)b->stored_amount() / 100.0) - 1);
        if (amount >= 0) {
            ImageDraw::img_generic(ctx, image_id_from_group(GROUP_RESOURCE_STOCK_BARLEY_2) + amount, pos + vec2i{65, 3}, color_mask);
        }
        break;

    case BUILDING_PAPYRUS_WORKSHOP:
        amount = std::min<int>(2, ceil((float)b->stored_amount() / 100.0) - 1);
        if (amount >= 0) {
            ImageDraw::img_generic(ctx, image_id_from_group(GROUP_RESOURCE_STOCK_REEDS_5) + amount, pos + vec2i{35, 4}, color_mask);
        }
        break;

    case BUILDING_WOOD_CUTTERS:
        if (amount >= 0) {
            ImageDraw::img_generic(ctx, image_id_from_group(GROUP_RESOURCE_STOCK_WOOD_5) + amount, pos + vec2i{65, 3}, color_mask);
        }
        break;

    case BUILDING_LINEN_WORKSHOP:
        //            ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_STOCK_FLAX_2) + amount, x + 65, y + 3,
        //            color_mask);
        break;

    case BUILDING_JEWELS_WORKSHOP:
        //            ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_STOCK_GEMS_2) + amount, x + 65, y + 3,
        //            color_mask);
        break;

    case BUILDING_SHIPYARD:
        //            ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_STOCK_WOOD_5) + amount, x + 65, y + 3,
        //            color_mask);
        break;

    case BUILDING_CHARIOTS_WORKSHOP:
        //            ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_STOCK_WOOD_5) + amount, x + 65, y + 3,
        //            color_mask);
        break;

    case BUILDING_CHARIOT_MAKER:
        //            ImageDraw::img_generic(image_id_from_group(GROUP_RESOURCE_STOCK_CHARIOTS_2) + amount, x + 65, y +
        //            3, color_mask);
        break;
    }
}
