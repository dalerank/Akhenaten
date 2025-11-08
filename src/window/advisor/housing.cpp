#include "housing.h"

#include "city/city_population.h"
#include "city/city_resource.h"
#include "city/city.h"
#include "game/resource.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "scenario/scenario.h"
#include "game/game.h"

#define ADVISOR_HEIGHT 27

ui::advisor_housing_window g_advisor_housing_window;

static void go_back(int param1, int param2);

static generic_button back_button[] = {{545, 260, 60, 51, go_back, button_none, 0, 1}};

static int focus_button_id;

static void draw_housing_table() {
    int* housing_type_counts;
    int* houses_demanding_goods;
    int width;
    int y_offset = 68;
    int rows = 0;
    pcstr goods_demand_strings[4] = {"#TR_ADVISOR_RESIDENCES_DEMANDING_POTTERY",
                                     "#TR_ADVISOR_RESIDENCES_DEMANDING_FURNITURE",
                                     "#TR_ADVISOR_RESIDENCES_DEMANDING_OIL",
                                     "#TR_ADVISOR_RESIDENCES_DEMANDING_WINE"};
    int goods_icons[4] = {RESOURCE_POTTERY, RESOURCE_LUXURY_GOODS, RESOURCE_MEAT, RESOURCE_BEER};

    housing_type_counts = calculate_number_of_each_housing_type();
    houses_demanding_goods = calculate_houses_demanding_goods(housing_type_counts);

    for (int i = 0; i <= 11; i++) {
        if (housing_type_counts[i]) {
            width = lang_text_draw(29, i, 70, y_offset + (20 * rows), FONT_NORMAL_BLACK_ON_DARK);
            text_draw_number(housing_type_counts[i], '@', " ", 215, y_offset + (20 * rows), FONT_NORMAL_WHITE_ON_DARK);
            rows += 1;
        }
    }

    rows = 0;

    for (int i = 12; i <= 19; i++) {
        if (housing_type_counts[i]) {
            width = lang_text_draw(29, i, 270, y_offset + (20 * rows), FONT_NORMAL_BLACK_ON_DARK);
            text_draw_number(housing_type_counts[i], '@', " ", 450, y_offset + (20 * rows), FONT_NORMAL_WHITE_ON_DARK);
            rows += 1;
        }
    }

    text_draw("#TR_ADVISOR_TOTAL_NUM_HOUSES", 270, y_offset + 180, FONT_NORMAL_BLACK_ON_DARK, 0);
    text_draw_number(calculate_total_housing_buildings(), '@', " ", 450, y_offset + 180, FONT_NORMAL_WHITE_ON_DARK);

    text_draw("#TR_ADVISOR_AVAILABLE_HOUSING_CAPACITY", 270, y_offset + 200, FONT_NORMAL_BLACK_ON_DARK, 0);
    text_draw_number(city_population_open_housing_capacity(), '@', " ", 450, y_offset + 200, FONT_NORMAL_WHITE_ON_DARK);

    text_draw("#TR_ADVISOR_TOTAL_HOUSING_CAPACITY", 270, y_offset + 220, FONT_NORMAL_BLACK_ON_DARK, 0);
    text_draw_number(city_population_total_housing_capacity(), '@', " ", 450, y_offset + 220, FONT_NORMAL_WHITE_ON_DARK);

    painter ctx = game.painter();
    for (int i = 0; i <= 3; i++) {
        ctx.img_generic(image_id_resource_icon(goods_icons[i]), vec2i{54, y_offset + 260 + (23 * i)});
        text_draw(goods_demand_strings[i], 90, y_offset + 263 + (23 * i), FONT_NORMAL_BLACK_ON_LIGHT, 0);
        text_draw_number(houses_demanding_goods[i], '@', " ", 450, y_offset + 263 + (23 * i), FONT_NORMAL_BLACK_ON_LIGHT);
    }
}

int ui::advisor_housing_window::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    painter ctx = game.painter();

    int val;
    int width;

    outer_panel_draw(vec2i{0, 0}, 40, ADVISOR_HEIGHT);
    inner_panel_draw({ 24, 60 }, { 32, 16 });
    ctx.img_generic(image_id_from_group(GROUP_ADVISOR_ICONS) + 5, vec2i{10, 10});
    ctx.img_generic(image_id_from_group(GROUP_ADVISOR_ICONS) + 5, vec2i{555, 265});

    const int city_population = g_city.population.current;
    width = text_draw_number(city_population, '@', " ", 450, 25, FONT_NORMAL_BLACK_ON_LIGHT);
    text_draw("#TR_ADVISOR_TOTAL_POPULATION", 450 + width, 25, FONT_NORMAL_BLACK_ON_LIGHT, 0);

    for (int i = 0; i < 58; i++) {
        val = i / 2;
        graphics_draw_vertical_line(vec2i{545 + i, 260 + 50 - val}, 260 + 50, COLOR_RED);
    }

    text_draw("#TR_ADVISOR_ADVISOR_HEADER_HOUSING", 60, 12, FONT_LARGE_BLACK_ON_LIGHT, 0);
    text_draw_centered("#TR_ADVISOR_BUTTON_GRAPHS", 545, 315, 61, FONT_NORMAL_BLACK_ON_LIGHT, 0);

    draw_housing_table();

    return ADVISOR_HEIGHT;
}

void ui::advisor_housing_window::draw_foreground(UiFlags flags) {
    if (focus_button_id == 0)
        button_border_draw({ 545, 260 }, { 60, 51 }, 0);
    else if (focus_button_id == 1)
        button_border_draw({ 545, 260 }, { 60, 51 }, 1);
}

int ui::advisor_housing_window::handle_mouse(const mouse* m) {
    return generic_buttons_handle_mouse(m, {0, 0}, back_button, 1, &focus_button_id);
}

static void go_back(int param1, int param2) {
    window_advisors_show_advisor(ADVISOR_POPULATION);
}

int ui::advisor_housing_window::get_tooltip_text(void) {
    return 0;
}

advisor_window* ui::advisor_housing_window::instance() {
    return &g_advisor_housing_window;
}
