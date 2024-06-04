#include "house.h"

#include "building/building.h"
#include "building/model.h"
#include "city/city.h"
#include "common.h"
#include "core/calc.h"
#include "core/game_environment.h"
#include "game/resource.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/view/view.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "grid/road_access.h"
#include "window/building/figures.h"
#include "game/game.h"

static void draw_vacant_lot(object_info* c) {
    window_building_prepare_figure_list(c);
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(128, 0, c->offset.x, c->offset.y + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    window_building_draw_figure_list(c);

    int text_id = 2;
    building* b = building_get(c->building_id);
    map_point road_tile = map_closest_road_within_radius(b->tile, 1, 2);
    if (road_tile.valid()) {
        text_id = 1;
    }

    window_building_draw_description_at(c, 16 * c->bgsize.y - 113, 128, text_id);
}
static void draw_population_info(object_info* c, int y_offset) {
    painter ctx = game.painter();
    building* b = building_get(c->building_id);
    ImageDraw::img_generic(ctx, image_id_from_group(GROUP_CONTEXT_ICONS) + 13, vec2i{c->offset.x + 34, y_offset + 4});
    int width = text_draw_number(b->house_population, '@', " ", c->offset.x + 50, y_offset + 14, FONT_NORMAL_BLACK_ON_DARK);
    width += lang_text_draw(127, 20, c->offset.x + 50 + width, y_offset + 14, FONT_NORMAL_BLACK_ON_DARK);

    if (b->house_population_room < 0) {
        width += text_draw_number(-b->house_population_room, '@', " ", c->offset.x + 50 + width, y_offset + 14, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw(127, 21, c->offset.x + 50 + width, y_offset + 14, FONT_NORMAL_BLACK_ON_DARK);
    } else if (b->house_population_room > 0) {
        width += lang_text_draw(127, 22, c->offset.x + 50 + width, y_offset + 14, FONT_NORMAL_BLACK_ON_DARK);
        text_draw_number(b->house_population_room, '@', " ", c->offset.x + 50 + width, y_offset + 14, FONT_NORMAL_BLACK_ON_DARK);
    }
}
static void draw_tax_info(object_info* c, int y_offset) {
    building* b = building_get(c->building_id);
    if (b->house_tax_coverage) {
        int pct = calc_adjust_with_percentage(b->tax_income_or_storage / 2, city_finance_tax_percentage());
        int width = lang_text_draw(127, 24, c->offset.x + 36, y_offset, FONT_NORMAL_BLACK_ON_DARK);
        width += lang_text_draw_amount(8, 0, pct, c->offset.x + 36 + width, y_offset, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw(127, 25, c->offset.x + 36 + width, y_offset, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        lang_text_draw(127, 23, c->offset.x + 36, y_offset, FONT_NORMAL_BLACK_ON_DARK);
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
    lang_text_draw(127, text_id, c->offset.x + 36, y_offset, FONT_NORMAL_BLACK_ON_DARK);
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
    outer_panel_draw(c->offset, c->bgsize.x, c->bgsize.y);
    lang_text_draw_centered(29, level, c->offset.x, c->offset.y + 10, 16 * c->bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    inner_panel_draw(c->offset.x + 16, c->offset.y + 148, c->bgsize.x - 2, 10);

    if (b->data.house.evolve_text_id == 62) { // is about to devolve
        int width = lang_text_draw(127, 40 + b->data.house.evolve_text_id, c->offset.x + 32, c->offset.y + Y_COMPLAINTS, FONT_NORMAL_BLACK_ON_LIGHT);
        width += lang_text_draw_colored(41, building_get(c->worst_desirability_building_id)->type, c->offset.x + 32 + width, c->offset.y + Y_COMPLAINTS, FONT_NORMAL_YELLOW, 0);
        text_draw((uint8_t*)")", c->offset.x + 32 + width, c->offset.y + Y_COMPLAINTS, FONT_NORMAL_BLACK_ON_LIGHT, 0);
        lang_text_draw_multiline(127, 41 + b->data.house.evolve_text_id, c->offset + vec2i{32, Y_COMPLAINTS + 16}, 16 * (c->bgsize.x - 4), FONT_NORMAL_BLACK_ON_LIGHT);
    } else { // needs something to evolve 
        lang_text_draw_multiline(127, 40 + b->data.house.evolve_text_id, c->offset + vec2i{32, Y_COMPLAINTS}, 16 * (c->bgsize.x - 4), FONT_NORMAL_BLACK_ON_LIGHT);
    }

    int resource_image = image_id_resource_icon(0);
    // food inventory
    // todo: fetch map available foods?
    int food1 = g_city.allowed_foods(0);
    int food2 = g_city.allowed_foods(1);
    int food3 = g_city.allowed_foods(2);
    int food4 = g_city.allowed_foods(3);

    if (food1) { // wheat
        ImageDraw::img_generic(ctx, resource_image + food1, c->offset + vec2i{32, Y_FOODS});
        text_draw_number(b->data.house.inventory[0], '@', " ", c->offset.x + 64, c->offset.y + Y_FOODS + 4, FONT_NORMAL_BLACK_ON_LIGHT);
    }
    if (food2) { // vegetables
        ImageDraw::img_generic(ctx, resource_image + food2, c->offset + vec2i{142, Y_FOODS});
        text_draw_number(b->data.house.inventory[1], '@', " ", c->offset.x + 174, c->offset.y + Y_FOODS + 4, FONT_NORMAL_BLACK_ON_LIGHT);
    }
    if (food3) { // fruit
        ImageDraw::img_generic(ctx, resource_image + food3, c->offset + vec2i{252, Y_FOODS});
        text_draw_number(b->data.house.inventory[2], '@', " ", c->offset.x + 284, c->offset.y + Y_FOODS + 4, FONT_NORMAL_BLACK_ON_LIGHT);
    }
    if (food4) { // meat/fish
        ImageDraw::img_generic(ctx, resource_image + food4, c->offset + vec2i{362, Y_FOODS});
        text_draw_number(b->data.house.inventory[3], '@', " ", c->offset.x + 394, c->offset.y + Y_FOODS + 4, FONT_NORMAL_BLACK_ON_LIGHT);
    }

    // goods inventory
    // pottery
    ImageDraw::img_generic(ctx, resource_image + INV_RESOURCES[0], c->offset + vec2i{32, Y_GOODS});
    text_draw_number(b->data.house.inventory[INVENTORY_GOOD1], '@', " ", c->offset.x + 64, c->offset.y + Y_GOODS + 4, FONT_NORMAL_BLACK_ON_LIGHT);
    // furniture
    ImageDraw::img_generic(ctx, resource_image + INV_RESOURCES[1], c->offset + vec2i{142, Y_GOODS});
    text_draw_number(b->data.house.inventory[INVENTORY_GOOD2], '@', " ", c->offset.x + 174, c->offset.y + Y_GOODS + 4, FONT_NORMAL_BLACK_ON_LIGHT);
    // oil
    ImageDraw::img_generic(ctx, resource_image + INV_RESOURCES[2], c->offset + vec2i{252, Y_GOODS});
    text_draw_number(b->data.house.inventory[INVENTORY_GOOD3], '@', " ", c->offset.x + 284, c->offset.y + Y_GOODS + 4, FONT_NORMAL_BLACK_ON_LIGHT);
    // wine
    ImageDraw::img_generic(ctx, resource_image + INV_RESOURCES[3], c->offset + vec2i{362, Y_GOODS});
    text_draw_number(b->data.house.inventory[INVENTORY_GOOD4], '@', " ", c->offset.x + 394, c->offset.y + Y_GOODS + 4, FONT_NORMAL_BLACK_ON_LIGHT);

    draw_population_info(c, c->offset.y + 154);
    draw_tax_info(c, c->offset.y + 194);
    draw_happiness_info(c, c->offset.y + 214);
    if (!model_get_house(b->subtype.house_level)->food_types) { // no foods
        lang_text_draw_multiline(127, 33, c->offset + vec2i{36, 234}, 16 * (c->bgsize.x - 6), FONT_NORMAL_BLACK_ON_DARK);
    }
}
