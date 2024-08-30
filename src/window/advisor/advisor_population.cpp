#include "advisor_population.h"

#include "city/city.h"
#include "city/migration.h"
#include "city/population.h"
#include "city/ratings.h"
#include "city/city_resource.h"
#include "game/time.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "config/config.h"
#include "scenario/scenario.h"
#include "translation/translation.h"
#include "window/advisors.h"
#include "game/game.h"

ui::advisor_population_window g_advisor_population_window;

static vec2i get_y_axis(int max_value) {
    if (max_value <= 100) { return { 100, -1 }; }
    else if (max_value <= 200) { return {200, 0}; }
    else if (max_value <= 400) { return {400, 1}; }
    else if (max_value <= 800) { return {800, 2}; }
    else if (max_value <= 1600) { return { 1600, 3 }; }
    else if (max_value <= 3200) { return { 3200, 4 }; }
    else if (max_value <= 6400) { return { 6400, 5 }; }
    else if (max_value <= 12800) { return { 12800, 6}; } 
    else if (max_value <= 25600) { return { 25600, 7}; }
    
    return { 51200, 8 };
}

static void get_min_max_month_year(int max_months, int* start_month, int* start_year, int* end_month, int* end_year) {
    if (city_population_monthly_count() > max_months) {
        *end_month = gametime().month - 1;
        *end_year = gametime().year;

        if (*end_month < 0)
            *end_year -= 1;

        *start_month = 11 - (max_months % 12);
        *start_year = *end_year - max_months / 12;
    } else {
        *start_month = 0;
        *start_year = scenario_property_start_year();
        *end_month = (max_months + *start_month) % 12;
        *end_year = (max_months + *start_month) / 12 + *start_year;
    }
}

static void draw_history_graph(int full_size, int x, int y) {
    painter ctx = game.painter();
    int max_months;
    int month_count = city_population_monthly_count();
    if (month_count <= 20)
        max_months = 20;
    else if (month_count <= 40)
        max_months = 40;
    else if (month_count <= 100)
        max_months = 100;
    else if (month_count <= 200)
        max_months = 200;
    else {
        max_months = 400;
    }
    if (!full_size) {
        if (max_months <= 40)
            max_months = 20;
        else {
            max_months = 100;
        }
    }
    // determine max value
    int max_value = 0;
    for (int m = 0; m < max_months; m++) {
        int value = city_population_at_month(max_months, m);
        if (value > max_value)
            max_value = value;
    }
    vec2i ypx = get_y_axis(max_value);
    int y_max = ypx.x;
    int y_shift = ypx.y;

    if (full_size) {
        // y axis
        text_draw_number_centered(y_max, x - 66, y - 3, 60, FONT_SMALL_PLAIN);
        text_draw_number_centered(y_max / 2, x - 66, y + 96, 60, FONT_SMALL_PLAIN);
        text_draw_number_centered(0, x - 66, y + 196, 60, FONT_SMALL_PLAIN);
        // x axis
        int start_month, start_year, end_month, end_year;
        get_min_max_month_year(max_months, &start_month, &start_year, &end_month, &end_year);

        int width = lang_text_draw(25, start_month, x - 20, y + 210, FONT_SMALL_PLAIN);
        lang_text_draw_year(start_year, x + width - 20, y + 210, FONT_SMALL_PLAIN);

        width = lang_text_draw(25, end_month, x + 380, y + 210, FONT_SMALL_PLAIN);
        lang_text_draw_year(end_year, x + width + 380, y + 210, FONT_SMALL_PLAIN);
    }

    if (full_size) {
        graphics_set_clip_rectangle({0, 0}, {640, y + 200});
        for (int m = 0; m < max_months; m++) {
            int pop = city_population_at_month(max_months, m);
            int val;
            if (y_shift == -1)
                val = 2 * pop;
            else {
                val = pop >> y_shift;
            }
            if (val > 0) {
                switch (max_months) {
                case 20:
                    ImageDraw::img_generic(ctx, image_id_from_group(GROUP_POPULATION_GRAPH_BAR), x + 20 * m, y + 200 - val);
                    break;
                case 40:
                    ImageDraw::img_generic(ctx, image_id_from_group(GROUP_POPULATION_GRAPH_BAR) + 1, x + 10 * m, y + 200 - val);
                    break;
                case 100:
                    ImageDraw::img_generic(ctx, image_id_from_group(GROUP_POPULATION_GRAPH_BAR) + 2, x + 4 * m, y + 200 - val);
                    break;
                case 200:
                    ImageDraw::img_generic(ctx, image_id_from_group(GROUP_POPULATION_GRAPH_BAR) + 3, x + 2 * m,y + 200 - val);
                    break;
                default:
                    graphics_draw_vertical_line(vec2i{x + m, y + 200 - val}, y + 199, COLOR_RED);
                    break;
                }
            }
        }
        graphics_reset_clip_rectangle();
    } else {
        y_shift += 2;
        for (int m = 0; m < max_months; m++) {
            int val = city_population_at_month(max_months, m) >> y_shift;
            if (val > 0) {
                if (max_months == 20)
                    graphics_fill_rect(vec2i{x + m, y + 50 - val}, vec2i{4, val + 1}, COLOR_RED);
                else {
                    graphics_draw_vertical_line(vec2i{x + m, y + 50 - val}, y + 50, COLOR_RED);
                }
            }
        }
    }
}

static void draw_census_graph(int full_size, int x, int y) {
    painter ctx = game.painter();
    int max_value = 0;
    for (int i = 0; i < 100; i++) {
        int value = city_population_at_age(i);
        if (value > max_value)
            max_value = value;
    }
    vec2i ypx = get_y_axis(max_value);
    int y_max = ypx.x;
    int y_shift = ypx.y;

    if (full_size) {
        // y axis
        text_draw_number_centered(y_max, x - 66, y - 3, 60, FONT_SMALL_PLAIN);
        text_draw_number_centered(y_max / 2, x - 66, y + 96, 60, FONT_SMALL_PLAIN);
        text_draw_number_centered(0, x - 66, y + 196, 60, FONT_SMALL_PLAIN);
        // x axis
        for (int i = 0; i <= 10; i++) {
            text_draw_number_centered(i * 10, x + 40 * i - 22, y + 210, 40, FONT_SMALL_PLAIN);
        }
    }

    if (full_size) {
        graphics_set_clip_rectangle({0, 0}, {640, y + 200});
        for (int i = 0; i < 100; i++) {
            int pop = city_population_at_age(i);
            int val;
            if (y_shift == -1)
                val = 2 * pop;
            else {
                val = pop >> y_shift;
            }
            if (val > 0) {
                ImageDraw::img_generic(ctx, image_id_from_group(GROUP_POPULATION_GRAPH_BAR) + 2, x + 4 * i, y + 200 - val);
            }
        }
        graphics_reset_clip_rectangle();
    } else {
        y_shift += 2;
        for (int i = 0; i < 100; i++) {
            int val = city_population_at_age(i) >> y_shift;
            if (val > 0)
                graphics_draw_vertical_line(vec2i{x + i, y + 50 - val}, y + 50, COLOR_RED);
        }
    }
}

static void draw_society_graph(int full_size, int x, int y) {
    painter ctx = game.painter();
    int max_value = 0;
    for (int i = 0; i < 20; i++) {
        int value = city_population_at_level(i);
        if (value > max_value)
            max_value = value;
    }
    vec2i ypx = get_y_axis(max_value);
    int y_max = ypx.x;
    int y_shift = ypx.y;

    if (full_size) {
        // y axis
        text_draw_number_centered(y_max, x - 66, y - 3, 60, FONT_SMALL_PLAIN);
        text_draw_number_centered(y_max / 2, x - 66, y + 96, 60, FONT_SMALL_PLAIN);
        text_draw_number_centered(0, x - 66, y + 196, 60, FONT_SMALL_PLAIN);
        // x axis
        lang_text_draw_centered(55, 9, x - 80, y + 210, 200, FONT_SMALL_PLAIN);
        lang_text_draw_centered(55, 10, x + 280, y + 210, 200, FONT_SMALL_PLAIN);
    }

    if (full_size) {
        graphics_set_clip_rectangle({0, 0}, {640, y + 200});
        for (int i = 0; i < 20; i++) {
            int pop = city_population_at_level(i);
            int val;
            if (y_shift == -1)
                val = 2 * pop;
            else {
                val = pop >> y_shift;
            }
            if (val > 0) {
                ImageDraw::img_generic(ctx, image_id_from_group(GROUP_POPULATION_GRAPH_BAR), x + 20 * i, y + 200 - val);
            }
        }
        graphics_reset_clip_rectangle();
    } else {
        y_shift += 2;
        for (int i = 0; i < 20; i++) {
            int val = city_population_at_level(i) >> y_shift;
            if (val > 0)
                graphics_fill_rect(vec2i{x + 5 * i, y + 50 - val}, vec2i{4, val + 1}, COLOR_RED);
        }
    }
}
 void ui::advisor_population_window::print_society_info() {
    int width;
    int avg_tax_per_house = 0;
    if (calculate_total_housing_buildings() > 0)
        avg_tax_per_house = city_finance_estimated_tax_income() / calculate_total_housing_buildings();

    // Housing prosperity cap
    width = text_draw(translation_for(TR_ADVISOR_HOUSING_PROSPERITY_RATING), 75, 342, FONT_NORMAL_WHITE_ON_DARK, 0);
    text_draw_number(g_city.ratings.prosperity_max, '@', " ", 75 + width, 342, FONT_NORMAL_WHITE_ON_DARK);

    // Percent patricians
    width = text_draw(translation_for(TR_ADVISOR_PERCENTAGE_IN_MANORS), 75, 360, FONT_NORMAL_WHITE_ON_DARK, 0);
    text_draw_percentage(percentage_city_population_in_manors(), 75 + width, 360, FONT_NORMAL_WHITE_ON_DARK);

    // Percent impoverished
    width = text_draw(translation_for(TR_ADVISOR_PERCENTAGE_IN_SHANTIES), 75, 378, FONT_NORMAL_WHITE_ON_DARK, 0);
    text_draw_percentage(percentage_city_population_in_shanties(), 75 + width, 378, FONT_NORMAL_WHITE_ON_DARK);

    // Average tax
    width = text_draw(translation_for(TR_ADVISOR_AVERAGE_TAX), 75, 396, FONT_NORMAL_WHITE_ON_DARK, 0);
    text_draw_money(avg_tax_per_house, 75 + width, 396, FONT_NORMAL_WHITE_ON_DARK);
}

void ui::advisor_population_window::print_census_info() {
    int width;

    // Average age
    width = text_draw(translation_for(TR_ADVISOR_AVERAGE_AGE), 75, 342, FONT_NORMAL_WHITE_ON_DARK, 0);
    text_draw_number(city_population_average_age(), '@', " ", 75 + width, 342, FONT_NORMAL_WHITE_ON_DARK);

    // Percent working age
    width = text_draw(translation_for(TR_ADVISOR_PERCENT_IN_WORKFORCE), 75, 360, FONT_NORMAL_WHITE_ON_DARK, 0);
    text_draw_percentage(city_population_percent_in_workforce(), 75 + width, 360, FONT_NORMAL_WHITE_ON_DARK);

    // Yearly births
    width = text_draw(translation_for(TR_ADVISOR_BIRTHS_LAST_YEAR), 75, 378, FONT_NORMAL_WHITE_ON_DARK, 0);
    text_draw_number(city_population_yearly_births(), '@', "", 75 + width, 378, FONT_NORMAL_WHITE_ON_DARK);

    // Yearly deaths
    width = text_draw(translation_for(TR_ADVISOR_DEATHS_LAST_YEAR), 75, 396, FONT_NORMAL_WHITE_ON_DARK, 0);
    text_draw_number(city_population_yearly_deaths(), '@', "", 75 + width, 396, FONT_NORMAL_WHITE_ON_DARK);
}

void ui::advisor_population_window::print_history_info() {
    int width;

    // food stores
    if (scenario_property_kingdom_supplies_grain()) {
        lang_text_draw(55, 11, 75, 342, FONT_NORMAL_WHITE_ON_DARK);
    } else {
        width = lang_text_draw_amount(8, 6, city_resource_operating_granaries(), 70, 342, FONT_NORMAL_WHITE_ON_DARK);
        if (city_resource_food_supply_months() > 0) {
            width += lang_text_draw(55, 12, 70 + width, 342, FONT_NORMAL_WHITE_ON_DARK);
            lang_text_draw_amount(8, 4, city_resource_food_supply_months(), 70 + width, 342, FONT_NORMAL_WHITE_ON_DARK);
        } else if (city_resource_food_stored() > city_resource_food_needed() / 2)
            lang_text_draw(55, 13, 70 + width, 342, FONT_NORMAL_WHITE_ON_DARK);
        else if (city_resource_food_stored() > 0)
            lang_text_draw(55, 15, 70 + width, 342, FONT_NORMAL_WHITE_ON_DARK);
        else {
            lang_text_draw(55, 14, 70 + width, 342, FONT_NORMAL_WHITE_ON_DARK);
        }
    }

    // food types eaten
    width = lang_text_draw(55, 16, 75, 360, FONT_NORMAL_WHITE_ON_DARK);
    text_draw_number(city_resource_food_types_available(), '@', " ", 75 + width, 360, FONT_NORMAL_WHITE_ON_DARK);

    // immigration
    int newcomers = g_city.migration_newcomers();
    if (newcomers >= 5) {
        lang_text_draw(55, 24, 75, 378, FONT_NORMAL_WHITE_ON_DARK);
        width = text_draw_number(newcomers, '@', " ", 70, 396, FONT_NORMAL_WHITE_ON_DARK);
        lang_text_draw(55, 17, 70 + width, 396, FONT_NORMAL_WHITE_ON_DARK);
    } else if (g_city.migration_no_room_for_immigrants()) {
        lang_text_draw(55, 24, 75, 378, FONT_NORMAL_WHITE_ON_DARK);
        lang_text_draw(55, 19, 75, 396, FONT_NORMAL_WHITE_ON_DARK);
    } else if (g_city.migration_percentage() < 80) {
        lang_text_draw(55, 25, 75, 378, FONT_NORMAL_WHITE_ON_DARK);
        int text_id;
        switch (g_city.migration_problems_cause()) {
        case NO_IMMIGRATION_LOW_WAGES:
            text_id = 20;
            break;
        case NO_IMMIGRATION_NO_JOBS:
            text_id = 21;
            break;
        case NO_IMMIGRATION_NO_FOOD:
            text_id = 22;
            break;
        case NO_IMMIGRATION_HIGH_TAXES:
            text_id = 23;
            break;
        case NO_IMMIGRATION_MANY_TENTS:
            text_id = 31;
            break;
        case NO_IMMIGRATION_LOW_MOOD:
            text_id = 32;
            break;
        default:
            text_id = 0;
            break;
        }

        if (text_id) {
            lang_text_draw(55, text_id, 75, 396, FONT_NORMAL_WHITE_ON_DARK);
        }

    } else {
        lang_text_draw(55, 24, 75, 378, FONT_NORMAL_WHITE_ON_DARK);
        width = text_draw_number(newcomers, '@', " ", 70, 396, FONT_NORMAL_WHITE_ON_DARK);
        if (newcomers == 1)
            lang_text_draw(55, 18, 70 + width, 396, FONT_NORMAL_WHITE_ON_DARK);
        else {
            lang_text_draw(55, 17, 70 + width, 396, FONT_NORMAL_WHITE_ON_DARK);
        }
    }
}

void button_graph(int next) {
    int new_order;

    switch (city_population_graph_order()) {
    default:
    case 0:
        new_order = next ? 5 : 2;
        break;
    case 1:
        new_order = next ? 3 : 4;
        break;
    case 2:
        new_order = next ? 4 : 0;
        break;
    case 3:
        new_order = next ? 1 : 5;
        break;
    case 4:
        new_order = next ? 2 : 1;
        break;
    case 5:
        new_order = next ? 0 : 3;
        break;
    }
    city_population_set_graph_order(new_order);

    window_invalidate();
}

int ui::advisor_population_window::draw_background() {
    int graph_order = city_population_graph_order();
 
    // Title: depends on big graph shown
    textid titlestr{ 55, 2 };
    if (graph_order < 2) { titlestr = { 55, 0 }; } 
    else if (graph_order < 4) { titlestr = { 55, 1 }; }

    ui["title"] = titlestr;
    ui["population"].text_var("%u %s", city_population(), translation_for(TR_ADVISOR_TOTAL_POPULATION));

    struct {
        int big, top, bot;
    } textl;

    switch (graph_order) {
    default:
    case 0: textl = { 6, 4, 5 }; break;
    case 1: textl = { 6, 5, 4 }; break;
    case 2: textl = { 7, 3, 5 }; break;
    case 3: textl = { 7, 5, 3 }; break;
    case 4: textl = { 8, 3, 4 }; break;
    case 5: textl = { 8, 4, 3 }; break;
    }

    ui["housing"] = (pcstr)translation_for(TR_HEADER_HOUSING);
    ui["big_text"] = ui::str(55, textl.big);
    ui["top_text"] = ui::str(55, textl.top);
    ui["bot_text"] = ui::str(55, textl.bot);

    ui["housing_button"].onclick([] {
        window_advisors_show_advisor(ADVISOR_HOUSING);
    });

    ui["next_graph"].onclick([] {
        button_graph(true);
    });

    ui["prev_graph"].onclick([] {
        button_graph(false);
    });

    return 0;
}

void ui::advisor_population_window::ui_draw_foreground() {
    ui.begin_widget(screen_dialog_offset());
    ui.draw();

    int big_text, top_text, bot_text;
    void (*big_graph)(int, int, int);
    void (*top_graph)(int, int, int);
    void (*bot_graph)(int, int, int);
    std::function<void()> info_panel;

    int graph_order = city_population_graph_order();
    switch (graph_order) {
    default:
    case 0:
        big_text = 6;
        top_text = 4;
        bot_text = 5;
        big_graph = draw_history_graph;
        top_graph = draw_census_graph;
        bot_graph = draw_society_graph;
        info_panel = std::bind(&advisor_population_window::print_history_info, this);
        break;
    case 1:
        big_text = 6;
        top_text = 5;
        bot_text = 4;
        big_graph = draw_history_graph;
        top_graph = draw_society_graph;
        bot_graph = draw_census_graph;
        info_panel = std::bind(&advisor_population_window::print_history_info, this);
        break;
    case 2:
        big_text = 7;
        top_text = 3;
        bot_text = 5;
        big_graph = draw_census_graph;
        top_graph = draw_history_graph;
        bot_graph = draw_society_graph;
        info_panel = std::bind(&advisor_population_window::print_census_info, this);
        break;
    case 3:
        big_text = 7;
        top_text = 5;
        bot_text = 3;
        big_graph = draw_census_graph;
        top_graph = draw_society_graph;
        bot_graph = draw_history_graph;
        info_panel = std::bind(&advisor_population_window::print_census_info, this);
        break;
    case 4:
        big_text = 8;
        top_text = 3;
        bot_text = 4;
        big_graph = draw_society_graph;
        top_graph = draw_history_graph;
        bot_graph = draw_census_graph;
        info_panel = std::bind(&advisor_population_window::print_society_info, this);
        break;
    case 5:
        big_text = 8;
        top_text = 4;
        bot_text = 3;
        big_graph = draw_society_graph;
        top_graph = draw_census_graph;
        bot_graph = draw_history_graph;
        info_panel = std::bind(&advisor_population_window::print_society_info, this);
        break;
    }

    big_graph(1, 64, 64);
    top_graph(0, 505, 63);
    bot_graph(0, 505, 163);

    info_panel();
    ui.end_widget();
}

int ui::advisor_population_window::get_tooltip_text(void) {
    //if (focus_button_id && focus_button_id < 3)
    //    return 111;
    //else {
    //    return 0;
    //}

    return 0;
}

advisor_window* ui::advisor_population_window::instance() {
    return &g_advisor_population_window;
}
