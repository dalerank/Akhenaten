#include "advisor_population.h"

#include "city/city.h"
#include "city/city_migration.h"
#include "city/city_population.h"
#include "city/ratings.h"
#include "city/city_resource.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "game/game_config.h"
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
        *end_month = game.simtime.month - 1;
        *end_year = game.simtime.year;

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

void ui::advisor_population_window::draw_history_graph(int full_size, vec2i pos) {
    painter ctx = game.painter();
    int max_months;
    int month_count = city_population_monthly_count();
    if (month_count <= 20) max_months = 20;
    else if (month_count <= 40) max_months = 40;
    else if (month_count <= 100) max_months = 100;
    else if (month_count <= 200) max_months = 200;
    else max_months = 400;
    
    if (!full_size) {
        max_months = std::clamp(max_months, 20, 100);
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

    int x = pos.x;
    int y = pos.y;

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

void ui::advisor_population_window::draw_census_graph(int full_size, vec2i pos) {
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

    int x = pos.x;
    int y = pos.y;

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

void ui::advisor_population_window::draw_society_graph(int full_size, vec2i pos) {
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

    int x = pos.x;
    int y = pos.y;

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
    int avg_tax_per_house = 0;
    if (calculate_total_housing_buildings() > 0) {
        avg_tax_per_house = g_city.finance.estimated_tax_income / calculate_total_housing_buildings();
    }

    // Housing prosperity cap
    ui["text1"].text_var("%s %d", translation_for(TR_ADVISOR_HOUSING_PROSPERITY_RATING), g_city.ratings.prosperity_max);

    // Percent patricians
    ui["text2"].text_var("%s %d", translation_for(TR_ADVISOR_PERCENTAGE_IN_MANORS), g_city.population.percentage_in_manors());

    // Percent impoverished
    ui["text3"].text_var("%s %d", translation_for(TR_ADVISOR_PERCENTAGE_IN_SHANTIES), g_city.population.percentage_in_shanties());

    // Average tax
    ui["text4"].text_var("%s %d", translation_for(TR_ADVISOR_AVERAGE_TAX), avg_tax_per_house);
}

void ui::advisor_population_window::print_census_info() {
    // Average age
    ui["text1"].text_var("%s %d", translation_for(TR_ADVISOR_AVERAGE_AGE), g_city.population.average_age());

    // Percent working age
    ui["text2"].text_var("%s %u", translation_for(TR_ADVISOR_PERCENT_IN_WORKFORCE), city_population_percent_in_workforce());

    // Yearly births
    ui["text3"].text_var("%s %u", translation_for(TR_ADVISOR_BIRTHS_LAST_YEAR), city_population_yearly_births());

    // Yearly deaths
    ui["text4"].text_var("%s %u", translation_for(TR_ADVISOR_DEATHS_LAST_YEAR), city_population_yearly_deaths());
}

void ui::advisor_population_window::print_history_info() {
    // food stores
    if (scenario_property_kingdom_supplies_grain()) {
        ui["text1"] = ui::str(55, 11);
    } else {
        bstring256 text;
        text.printf("%s %u", ui::str(8, 6), city_resource_operating_granaries());

        const auto &resources = g_city.resource;
        if (city_resource_food_supply_months() > 0) {
            text.append("%s %s %u", ui::str(55, 12), ui::str(8, 4), city_resource_food_supply_months());
        } else if (resources.granary_total_stored > resources.food_needed_per_month / 2)
            text.append(ui::str(55, 13));
        else if (resources.granary_total_stored > 0)
            text.append(ui::str(55, 15));
        else {
            text.append(ui::str(55, 14));
        }

        ui["text1"] = text;
    }

    // food types eaten
    ui["text2"].text_var("%s %u", ui::str(55, 16), g_city.resource.food_types_available_num());

    // immigration
    int newcomers = g_city.migration.newcomers;
    if (newcomers >= 5) {
        ui["text3"].text_var("%s %u %s", ui::str(55, 24), newcomers, ui::str(55, 17));
    } else if (g_city.migration.no_room_for_immigrants()) {
        ui["text3"].text_var("%s %s", ui::str(55, 24), ui::str(55, 19));
    } else if (g_city.migration.percentage < 80) {
        bstring256 text = ui::str(55, 25);
        int text_id;
        switch (g_city.migration.problems_cause()) {
        case NO_IMMIGRATION_LOW_WAGES: text_id = 20; break;
        case NO_IMMIGRATION_NO_JOBS: text_id = 21; break;
        case NO_IMMIGRATION_NO_FOOD: text_id = 22; break;
        case NO_IMMIGRATION_HIGH_TAXES: text_id = 23; break;
        case NO_IMMIGRATION_MANY_TENTS: text_id = 31; break;
        case NO_IMMIGRATION_LOW_MOOD: text_id = 32; break;
        default: text_id = 0; break;
        }

        if (text_id) {
            text.append(ui::str(55, text_id));
        }

        ui["text3"] = text;
    } else {
        bstring256 text;
        text.printf("%s, %u", ui::str(55, 24), newcomers);
        text.append(ui::str(55, newcomers == 1 ? 18 : 17));

        ui["text3"] = text;
    }
}

void button_graph(int next) {
    int new_order;

    switch (city_population_graph_order()) {
    default:
    case 0: new_order = next ? 5 : 2; break;
    case 1: new_order = next ? 3 : 4; break;
    case 2: new_order = next ? 4 : 0; break;
    case 3: new_order = next ? 1 : 5; break;
    case 4: new_order = next ? 2 : 1; break;
    case 5: new_order = next ? 0 : 3; break;
    }
    city_population_set_graph_order(new_order);
}

int ui::advisor_population_window::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

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

void ui::advisor_population_window::ui_draw_foreground(UiFlags flags) {
    ui.begin_widget(pos);
    ui.draw();

    using graph_function = void (advisor_population_window::*)(int, vec2i);
    using info_function = void (advisor_population_window::*)();

    graph_function big_graph;
    graph_function top_graph;
    graph_function bot_graph;
    info_function info_panel;

    int graph_order = city_population_graph_order();
    switch (graph_order) {
    default:
    case 0:
        big_graph = &advisor_population_window::draw_history_graph;
        top_graph = &advisor_population_window::draw_census_graph;
        bot_graph = &advisor_population_window::draw_society_graph;
        info_panel = &advisor_population_window::print_history_info;
        break;
    case 1:
        big_graph = &advisor_population_window::draw_history_graph;
        top_graph = &advisor_population_window::draw_society_graph;
        bot_graph = &advisor_population_window::draw_census_graph;
        info_panel = &advisor_population_window::print_history_info;
        break;
    case 2:
        big_graph = &advisor_population_window::draw_census_graph;
        top_graph = &advisor_population_window::draw_history_graph;
        bot_graph = &advisor_population_window::draw_society_graph;
        info_panel= &advisor_population_window::print_census_info;
        break;
    case 3:
        big_graph = &advisor_population_window::draw_census_graph;
        top_graph = &advisor_population_window::draw_society_graph;
        bot_graph = &advisor_population_window::draw_history_graph;
        info_panel= &advisor_population_window::print_census_info;
        break;
    case 4:
        big_graph = &advisor_population_window::draw_society_graph;
        top_graph = &advisor_population_window::draw_history_graph;
        bot_graph = &advisor_population_window::draw_census_graph;
        info_panel= &advisor_population_window::print_society_info;
        break;
    case 5:
        big_graph = &advisor_population_window::draw_society_graph;
        top_graph = &advisor_population_window::draw_census_graph;
        bot_graph = &advisor_population_window::draw_history_graph;
        info_panel= &advisor_population_window::print_society_info;
        break;
    }

    (*this.*big_graph)(1, ui["big_graph_tx"].screen_pos());
    (*this.*top_graph)(0, ui["next_graph_tx"].screen_pos());
    (*this.*bot_graph)(0, ui["prev_graph_tx"].screen_pos());

    (*this.*info_panel)();
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
