#include "house.h"

#include "building/building.h"
#include "building/model.h"
#include "city/finance.h"
#include "common.h"
#include "core/calc.h"
#include "core/game_environment.h"
#include "game/resource.h"
#include "graphics/boilerplate.h"
#include "graphics/view/view.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "grid/road_access.h"
#include "window/building/figures.h"
#include "game/game.h"

static void draw_vacant_lot(object_info* c) {
    window_building_prepare_figure_list(c);
    outer_panel_draw(c->x_offset, c->y_offset, c->width_blocks, c->height_blocks);
    lang_text_draw_centered(128, 0, c->x_offset, c->y_offset + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    window_building_draw_figure_list(c);

    int text_id = 2;
    building* b = building_get(c->building_id);
    map_point road_tile;
    if (map_closest_road_within_radius(b->tile, 1, 2, road_tile)) {
        text_id = 1;
    }

    window_building_draw_description_at(c, 16 * c->height_blocks - 113, 128, text_id);
}
static void draw_population_info(object_info* c, int y_offset) {
    painter ctx = game.painter();
    building* b = building_get(c->building_id);
    ImageDraw::img_generic(ctx, image_id_from_group(GROUP_CONTEXT_ICONS) + 13, c->x_offset + 34, y_offset + 4);
    int width = text_draw_number(b->house_population, '@', " ", c->x_offset + 50, y_offset + 14, FONT_NORMAL_BLACK_ON_DARK);
    width += lang_text_draw(127, 20, c->x_offset + 50 + width, y_offset + 14, FONT_NORMAL_BLACK_ON_DARK);

    if (b->house_population_room < 0) {
        width += text_draw_number(-b->house_population_room, '@', " ", c->x_offset + 50 + width, y_offset + 14, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw(127, 21, c->x_offset + 50 + width, y_offset + 14, FONT_NORMAL_BLACK_ON_DARK);
    } else if (b->house_population_room > 0) {
        width += lang_text_draw(127, 22, c->x_offset + 50 + width, y_offset + 14, FONT_NORMAL_BLACK_ON_DARK);
        text_draw_number(b->house_population_room, '@', " ", c->x_offset + 50 + width, y_offset + 14, FONT_NORMAL_BLACK_ON_DARK);
    }
}
static void draw_tax_info(object_info* c, int y_offset) {
    building* b = building_get(c->building_id);
    if (b->house_tax_coverage) {
        int pct = calc_adjust_with_percentage(b->tax_income_or_storage / 2, city_finance_tax_percentage());
        int width = lang_text_draw(127, 24, c->x_offset + 36, y_offset, FONT_NORMAL_BLACK_ON_DARK);
        width += lang_text_draw_amount(8, 0, pct, c->x_offset + 36 + width, y_offset, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw(127, 25, c->x_offset + 36 + width, y_offset, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        lang_text_draw(127, 23, c->x_offset + 36, y_offset, FONT_NORMAL_BLACK_ON_DARK);
    }
}
static void draw_happiness_info(object_info* c, int y_offset) {
    int happiness = building_get(c->building_id)->sentiment.house_happiness;
    int text_id;
    if (happiness >= 50)
        text_id = 26;
    else if (happiness >= 40)
        text_id = 27;
    else if (happiness >= 30)
        text_id = 28;
    else if (happiness >= 20)
        text_id = 29;
    else if (happiness >= 10)
        text_id = 30;
    else if (happiness >= 1)
        text_id = 31;
    else {
        text_id = 32;
    }
    lang_text_draw(127, text_id, c->x_offset + 36, y_offset, FONT_NORMAL_BLACK_ON_DARK);
}

#define Y_COMPLAINTS 40      // 70
#define Y_FOODS 100          // 234
#define Y_GOODS Y_FOODS + 20 // 174 //274

void window_building_draw_house(object_info* c) {
    painter ctx = game.painter();
    c->help_id = 56;
    window_building_play_sound(c, "wavs/housing.wav");
    building* b = building_get(c->building_id);
    if (b->house_population <= 0) {
        draw_vacant_lot(c);
        return;
    }
    int level = b->type - 10;
    outer_panel_draw(c->x_offset, c->y_offset, c->width_blocks, c->height_blocks);
    lang_text_draw_centered(29, level, c->x_offset, c->y_offset + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    inner_panel_draw(c->x_offset + 16, c->y_offset + 148, c->width_blocks - 2, 10);

    if (b->data.house.evolve_text_id == 62) { // is about to devolve
        int width = lang_text_draw(127,
                                   40 + b->data.house.evolve_text_id,
                                   c->x_offset + 32,
                                   c->y_offset + Y_COMPLAINTS,
                                   FONT_NORMAL_BLACK_ON_LIGHT);
        width += lang_text_draw_colored(41,
                                        building_get(c->worst_desirability_building_id)->type,
                                        c->x_offset + 32 + width,
                                        c->y_offset + Y_COMPLAINTS,
                                        FONT_NORMAL_YELLOW,
                                        0);
        text_draw((uint8_t*)")", c->x_offset + 32 + width, c->y_offset + Y_COMPLAINTS, FONT_NORMAL_BLACK_ON_LIGHT, 0);
        lang_text_draw_multiline(127,
                                 41 + b->data.house.evolve_text_id,
                                 c->x_offset + 32,
                                 c->y_offset + Y_COMPLAINTS + 16,
                                 16 * (c->width_blocks - 4),
                                 FONT_NORMAL_BLACK_ON_LIGHT);
    } else // needs something to evolve
        lang_text_draw_multiline(127,
                                 40 + b->data.house.evolve_text_id,
                                 c->x_offset + 32,
                                 c->y_offset + Y_COMPLAINTS,
                                 16 * (c->width_blocks - 4),
                                 FONT_NORMAL_BLACK_ON_LIGHT);

    int resource_image = image_id_resource_icon(0);
    // food inventory
    // todo: fetch map available foods?
    int food1 = ALLOWED_FOODS(0);
    int food2 = ALLOWED_FOODS(1);
    int food3 = ALLOWED_FOODS(2);
    int food4 = ALLOWED_FOODS(3);

    if (food1) { // wheat
        ImageDraw::img_generic(ctx, resource_image + food1, c->x_offset + 32, c->y_offset + Y_FOODS);
        text_draw_number(b->data.house.inventory[0], '@', " ", c->x_offset + 64, c->y_offset + Y_FOODS + 4, FONT_NORMAL_BLACK_ON_LIGHT);
    }
    if (food2) { // vegetables
        ImageDraw::img_generic(ctx, resource_image + food2, c->x_offset + 142, c->y_offset + Y_FOODS);
        text_draw_number(b->data.house.inventory[1], '@', " ", c->x_offset + 174, c->y_offset + Y_FOODS + 4, FONT_NORMAL_BLACK_ON_LIGHT);
    }
    if (food3) { // fruit
        ImageDraw::img_generic(ctx, resource_image + food3, c->x_offset + 252, c->y_offset + Y_FOODS);
        text_draw_number(b->data.house.inventory[2], '@', " ", c->x_offset + 284, c->y_offset + Y_FOODS + 4, FONT_NORMAL_BLACK_ON_LIGHT);
    }
    if (food4) { // meat/fish
        ImageDraw::img_generic(ctx, resource_image + food4, c->x_offset + 362, c->y_offset + Y_FOODS);
        text_draw_number(b->data.house.inventory[3], '@', " ", c->x_offset + 394, c->y_offset + Y_FOODS + 4, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    // goods inventory
    // pottery
    ImageDraw::img_generic(ctx, resource_image + INV_RESOURCES[0], c->x_offset + 32, c->y_offset + Y_GOODS);
    text_draw_number(b->data.house.inventory[INVENTORY_GOOD1], '@', " ", c->x_offset + 64, c->y_offset + Y_GOODS + 4, FONT_NORMAL_BLACK_ON_LIGHT);
    // furniture
    ImageDraw::img_generic(ctx, resource_image + INV_RESOURCES[1], c->x_offset + 142, c->y_offset + Y_GOODS);
    text_draw_number(b->data.house.inventory[INVENTORY_GOOD2], '@', " ", c->x_offset + 174, c->y_offset + Y_GOODS + 4, FONT_NORMAL_BLACK_ON_LIGHT);
    // oil
    ImageDraw::img_generic(ctx, resource_image + INV_RESOURCES[2], c->x_offset + 252, c->y_offset + Y_GOODS);
    text_draw_number(b->data.house.inventory[INVENTORY_GOOD3], '@', " ", c->x_offset + 284, c->y_offset + Y_GOODS + 4, FONT_NORMAL_BLACK_ON_LIGHT);
    // wine
    ImageDraw::img_generic(ctx, resource_image + INV_RESOURCES[3], c->x_offset + 362, c->y_offset + Y_GOODS);
    text_draw_number(b->data.house.inventory[INVENTORY_GOOD4], '@', " ", c->x_offset + 394, c->y_offset + Y_GOODS + 4, FONT_NORMAL_BLACK_ON_LIGHT);

    draw_population_info(c, c->y_offset + 154);
    draw_tax_info(c, c->y_offset + 194);
    draw_happiness_info(c, c->y_offset + 214);
    if (!model_get_house(b->subtype.house_level)->food_types) { // no foods
        lang_text_draw_multiline(127, 33, c->x_offset + 36, c->y_offset + 234, 16 * (c->width_blocks - 6), FONT_NORMAL_BLACK_ON_DARK);
    }
}
