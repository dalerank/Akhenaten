#include "building/building_house.h"

#include "building/model.h"
#include "window/building/common.h"
#include "city/city.h"
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
#include "io/gamefiles/lang.h"
#include "game/game.h"

struct house_info_window_t : ui::widget {
    int resource_text_group;
    int help_id;
} house_info_window;

ANK_REGISTER_CONFIG_ITERATOR(config_load_house_info_window);
void config_load_house_info_window() {
    g_config_arch.r_section("house_info_window", [] (archive arch) {
        house_info_window.load(arch);
        house_info_window.resource_text_group = arch.r_int("resource_text_group");
        house_info_window.help_id = arch.r_int("help_id");
    });
}

static void draw_vacant_lot(object_info &c) {
    window_building_prepare_figure_list(&c);
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(128, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    window_building_draw_figure_list(&c);

    int text_id = 2;
    building* b = building_get(c.building_id);
    map_point road_tile = map_closest_road_within_radius(b->tile, 1, 2);
    if (road_tile.valid()) {
        text_id = 1;
    }

    window_building_draw_description_at(c, 16 * c.bgsize.y - 113, 128, text_id);
}

static void draw_happiness_info(object_info &c, int y_offset) {
    int happiness = building_get(c.building_id)->sentiment.house_happiness;
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
    lang_text_draw(127, text_id, c.offset.x + 36, y_offset, FONT_NORMAL_BLACK_ON_DARK);
}

#define Y_COMPLAINTS 40      // 70
#define Y_FOODS 100          // 234
#define Y_GOODS Y_FOODS + 20 // 174 //274

void building_house::window_info_background(object_info &c) {
    auto &ui = house_info_window;

    c.help_id = ui.help_id;
    window_building_play_sound(&c, "wavs/housing.wav");

    building* b = building_get(c.building_id);
    if (b->house_population <= 0) {
        draw_vacant_lot(c);
        return;
    }

    ui["background"].size = c.bgsize;
    ui["title"].size.x = c.bgsize.x * 16;
    ui["tenants_panel"].size.x = c.bgsize.x - 2;
    ui["evolve_reason"].size.x = c.bgsize.x * 16;

    int level = b->type - 10;
    ui["title"].text(ui::str(29, level));
}

void building_house::window_info_foreground(object_info &c) {
    auto &ui = house_info_window;
    ui.draw();

    painter ctx = game.painter();
    building* b = building_get(c.building_id);

    if (b->data.house.evolve_text_id == 62) { // is about to devolve
        bstring512 text;
        text.printf("%s @Y%s&) %s", 
                        ui::str(127, 40 + b->data.house.evolve_text_id),
                        ui::str(41, building_get(c.worst_desirability_building_id)->type),
                        ui::str(127, 41 + b->data.house.evolve_text_id));
        ui["evolve_reason"].text(text);
    } else { // needs something to evolve 
        ui["evolve_reason"].text(ui::str(127, 40 + b->data.house.evolve_text_id));
    }

    int resource_image = image_id_resource_icon(0);

    auto food_icon = [] (int i) { bstring32 id_icon; id_icon.printf("food%u_icon", i); return id_icon; };
    auto food_text = [] (int i) { bstring32 id_text; id_text.printf("food%u_text", i); return id_text; };
      
    for (int i = 0; i < 4; ++i) {
        e_resource resource = g_city.allowed_foods(i);
        int stored = b->data.house.inventory[i];
        ui[food_icon(i)].image(resource);
        ui[food_text(i)].text_var(resource ? "%u" : "", stored);
    }

    auto good_icon = [] (int i) { bstring32 id_icon; id_icon.printf("good%u_icon", i); return id_icon; };
    auto good_text = [] (int i) { bstring32 id_text; id_text.printf("good%u_text", i); return id_text; };

    // goods inventory
    e_resource house_goods[] = {RESOURCE_POTTERY, RESOURCE_LUXURY_GOODS, RESOURCE_LINEN, RESOURCE_BEER};
    for (int i = 0; i < 4; ++i) {
        e_resource resource = house_goods[i];
        int stored = b->data.house.inventory[INVENTORY_GOOD1 + i];
        ui[good_icon(i)].image(resource);
        ui[good_text(i)].text_var("%u", stored);
    }

    bstring256 people_text, adv_people_text;
    people_text.printf("%u %s", b->house_population, ui::str(127, 20));
    if (b->house_population_room < 0) {
        adv_people_text.printf("%u %s", -b->house_population_room, ui::str(127, 21));
    } else if (b->house_population_room > 0) {
        adv_people_text.printf("%s %u", ui::str(127, 22), b->house_population_room);
    }
    ui["people_text"].text_var("%s ( %s )", people_text, adv_people_text);

    bstring256 tax_info_text;
    if (b->house_tax_coverage) {
        int pct = calc_adjust_with_percentage(b->tax_income_or_storage / 2, city_finance_tax_percentage());
        tax_info_text.printf("%s %u %s", ui::str(127, 24), pct, ui::str(127, 25));
    } else {
        tax_info_text = ui::str(127, 23);
    }
    ui["tax_info"].text(tax_info_text);

    draw_happiness_info(c, c.offset.y + 214);
    if (!model_get_house(b->subtype.house_level)->food_types) { // no foods
        lang_text_draw_multiline(127, 33, c.offset + vec2i{36, 234}, 16 * (c.bgsize.x - 6), FONT_NORMAL_BLACK_ON_DARK);
    }
}
