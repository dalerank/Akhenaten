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
#include "game/game.h"
#include "core/runtime_item.h"

#include "js/js_game.h"

ui::advisor_population_window g_advisor_population_window;

struct advisor_population_graph {
    int y_axis_height;
    int x_axis_width;
    vec2i y_axis_offset;
    vec2i x_axis_offset;
    int y_axis_label_w;
};
ANK_CONFIG_STRUCT(advisor_population_graph, 
    y_axis_height, y_axis_height, y_axis_offset, 
    y_axis_label_w, x_axis_offset, x_axis_width)

advisor_population_graph ANK_VARIABLE(advisor_population_graph_census);
advisor_population_graph ANK_VARIABLE(advisor_population_graph_history);
advisor_population_graph ANK_VARIABLE(advisor_population_society_history);

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

struct month_year {
    int month;
    int year;
};

struct month_year_range {
    month_year start;
    month_year end;
};

month_year_range get_min_max_month_year(int max_months) {
    month_year_range result;
    if (g_city.population.monthly.count > max_months) {
        result.end.month = game.simtime.month - 1;
        result.end.year = game.simtime.year;

        if (result.end.month < 0)
            result.end.year -= 1;

        result.start.month = 11 - (max_months % 12);
        result.start.year = result.end.year - max_months / 12;
    } else {
        result.start.month = 0;
        result.start.year = g_scenario.start_year;
        result.end.month = (max_months + result.start.month) % 12;
        result.end.year = (max_months + result.start.month) / 12 + result.start.year;
    }

    return result;
}

void ui::advisor_population_window::draw_history_graph(int full_size, pcstr body, pcstr title) {
    struct columnc {
        int count;
        int max;
        int wline;
        int graphid;
    } population = { 0, 0 };;

    const std::array<columnc, 5> thresholds = { {
        {20, 20, 20, 1},
        {40, 40, 10, 2},
        {100, 100, 4, 3},
        {200, 200, 2, 4},
        {std::numeric_limits<int>::max(), 400}
    } };

    const int month_count = g_city.population.monthly.count;
    auto it = std::find_if(thresholds.begin(), thresholds.end(), [month_count] (const auto& pair) {
        return month_count <= pair.count;
    });

    const int max_months = full_size ? it->max : std::clamp(it->max, 20, 200);
    const int wline = it->wline;

    // determine max value
    int max_value = 0;
    for (int m = 0; m < max_months; m++) {
        int value = g_city.population.at_month(max_months, m);
        if (value > max_value)
            max_value = value;
    }

    vec2i ypx = get_y_axis(max_value);
    int y_max = ypx.x;
    int y_shift = ypx.y;

    const auto& graph = advisor_population_graph_history;
    const vec2i bpos = ui[body].pos;


    if (full_size) {
        ui[title].text(ui::str(55, 6));
        // y axis
        ui.label(bstring32(y_max).c_str(), bpos + graph.y_axis_offset, FONT_SMALL_PLAIN, UiFlags_AlignCentered, graph.y_axis_label_w);
        ui.label(bstring32(y_max / 2).c_str(), bpos + graph.y_axis_offset + vec2i{ 0, graph.y_axis_height / 2 }, FONT_SMALL_PLAIN, UiFlags_AlignCentered, graph.y_axis_label_w);
        ui.label("0", bpos + graph.y_axis_offset + vec2i{ 0, graph.y_axis_height }, FONT_SMALL_PLAIN, UiFlags_AlignCentered, graph.y_axis_label_w);

        // x axis
        auto range = get_min_max_month_year(max_months);
        ui.label(bpos + graph.x_axis_offset, FONT_SMALL_PLAIN, 0, 0, "%s %d", ui::str(25, range.start.month), range.start.year);
        ui.label(bpos + graph.x_axis_offset + vec2i{ graph.x_axis_width, 0 }, FONT_SMALL_PLAIN, 0, 0, "%s %d", ui::str(25, range.end.month), range.end.year);
    }
    else {
        ui[title].text(ui::str(55, 3));
    }

    if (full_size) {
        ui.set_clip_rectangle({0, 0}, {640, bpos.y + 200});
        for (int m = 0; m < max_months; m++) {
            int pop = g_city.population.at_month(max_months, m);
            int val = (y_shift == -1) ? (2 * pop) : (pop >> y_shift);

            if (val > 0) {
                if (max_months >= 200) {
                    ui.vline(bpos + vec2i{ m, 200 - val }, bpos.y + 199, COLOR_RED);
                } else {
                    ui.image(graph_bar[it->graphid], bpos + vec2i{ wline * m, 200 - val });
                }
            }
        }
        ui.reset_clip_rectangle();
    } else {
        y_shift += 2;
        for (int m = 0; m < max_months; m++) {
            int val = g_city.population.at_month(max_months, m) >> y_shift;
            if (val > 0) {
                if (max_months == 20)
                    ui.rect(bpos + vec2i{m, 50 - val}, vec2i{4, val + 1}, COLOR_RED, COLOR_RED);
                else {
                    ui.vline(bpos + vec2i{m, 50 - val}, bpos.y + 50, COLOR_RED);
                }
            }
        }
    }
}

void ui::advisor_population_window::draw_census_graph(int full_size, pcstr body, pcstr title) {
    const auto &population = g_city.population;
    const int max_value = *std::max_element(population.at_age.begin(), population.at_age.end());

    vec2i ypx = get_y_axis(max_value);
    int y_max = ypx.x;
    int y_shift = ypx.y;

    const auto &graph = advisor_population_graph_census;
    const vec2i bpos = ui[body].pos;
    if (full_size) {
        ui[title].text(ui::str(55, 7));
        // y axis
        ui.label(bstring32(y_max).c_str(), bpos + graph.y_axis_offset + vec2i{0, 0}, FONT_SMALL_PLAIN, UiFlags_AlignCentered, graph.y_axis_label_w);
        ui.label(bstring32(y_max / 2).c_str(), bpos + graph.y_axis_offset + vec2i{0, graph.y_axis_height / 2}, FONT_SMALL_PLAIN, UiFlags_AlignCentered, graph.y_axis_label_w);
        ui.label("0", bpos + graph.y_axis_offset + vec2i{ 0, graph.y_axis_height}, FONT_SMALL_PLAIN, UiFlags_AlignCentered, graph.y_axis_label_w);

        // x axis
        for (int i = 0; i <= 10; i++) {
            ui.label(bstring32(i * 10).c_str(), bpos + graph.x_axis_offset + vec2i{ 40 * i, 0 }, FONT_SMALL_PLAIN, UiFlags_AlignCentered, graph.y_axis_label_w);
        }
    } else {
        ui[title].text(ui::str(55, 4));
    }

    if (full_size) {
        ui[title].text(ui::str(55, 6));
        ui.set_clip_rectangle({0, 0}, {640, bpos.y + 200});
        for (int i = 0; i < 100; i++) {
            int pop = population.at_age[i];
            int val = (y_shift == -1) ? (2 * pop) : (pop >> y_shift);

            if (val > 0) {
                ui.image(graph_bar[2], bpos + vec2i{ 4 * i, 200 - val });
            }
        }
        ui.reset_clip_rectangle();
    } else {
        y_shift += 2;
        for (int i = 0; i < 100; i++) {
            int val = population.at_age[i] >> y_shift;
            if (val > 0) {
                ui.vline(bpos + vec2i{ i, 50 - val }, val, COLOR_RED);
            }
        }
    }
}

void ui::advisor_population_window::draw_society_graph(int full_size, pcstr body, pcstr title) {
    const auto &population = g_city.population;
    const int max_value = *std::max_element(population.at_level.begin(), population.at_level.end());

    vec2i ypx = get_y_axis(max_value);
    int y_max = ypx.x;
    int y_shift = ypx.y;


    const auto& graph = advisor_population_society_history;
    const vec2i bpos = ui[body].pos;
    if (full_size) {
        ui[title].text(ui::str(55, 8));
        // y axis
        ui.label(bstring32(y_max).c_str(), bpos + graph.y_axis_offset, FONT_SMALL_PLAIN, UiFlags_AlignCentered, graph.y_axis_label_w);
        ui.label(bstring32(y_max / 2).c_str(), bpos + graph.y_axis_offset + vec2i{ 0, graph.y_axis_height / 2 }, FONT_SMALL_PLAIN, UiFlags_AlignCentered, graph.y_axis_label_w);
        ui.label("0", bpos + graph.y_axis_offset + vec2i{ 0, graph.y_axis_height }, FONT_SMALL_PLAIN, UiFlags_AlignCentered, graph.y_axis_label_w);
        // x axis
        ui.label(bpos + graph.x_axis_offset, FONT_SMALL_PLAIN, 0, 0, "%s", ui::str(55, 9));
        ui.label(bpos + graph.x_axis_offset + vec2i{ graph.x_axis_width, 0 }, FONT_SMALL_PLAIN, 0, 0, "%s", ui::str(55, 10));
    } else {
        ui[title].text(ui::str(55, 5));
    }

    if (full_size) {
        ui.set_clip_rectangle({0, 0}, {640, bpos.y + 200});
        for (int i = 0; i < HOUSE_LEVEL_MAX; i++) {
            int pop = population.at_level[i];
            int val = (y_shift == -1) ? 2 * pop : (pop >> y_shift);

            if (val > 0) {
                ui.image(graph_bar[1], bpos + vec2i{ 20 * i, 200 - val });
            }
        }
        ui.reset_clip_rectangle();
    } else {
        y_shift += 2;
        for (int i = 0; i < HOUSE_LEVEL_MAX; i++) {
            int val = population.at_level[i] >> y_shift;
            if (val > 0) {
                ui.rect(bpos + vec2i{ 5 * i, 50 - val }, vec2i{ 4, val + 1 }, COLOR_RED, COLOR_RED);
            }
        }
    }
}
 void ui::advisor_population_window::print_society_info() {
    int avg_tax_per_house = 0;
    if (calculate_total_housing_buildings() > 0) {
        avg_tax_per_house = g_city.finance.estimated_tax_income / calculate_total_housing_buildings();
    }

    // Housing prosperity cap
    ui["text1"].text_var("%s %d", "#TR_ADVISOR_HOUSING_PROSPERITY_RATING", g_city.ratings.prosperity_max);

    // Percent patricians
    ui["text2"].text_var("%s %d", "#TR_ADVISOR_PERCENTAGE_IN_MANORS", g_city.population.percentage_in_manors());

    // Percent impoverished
    ui["text3"].text_var("%s %d", "#TR_ADVISOR_PERCENTAGE_IN_SHANTIES", g_city.population.percentage_in_shanties());

    // Average tax
    ui["text4"].text_var("%s %d", "#TR_ADVISOR_AVERAGE_TAX", avg_tax_per_house);
}

void ui::advisor_population_window::print_census_info() {
    // Average age
    ui["text1"].text_var("%s %d", "#TR_ADVISOR_AVERAGE_AGE", g_city.population.average_age());

    // Percent working age
    ui["text2"].text_var("%s %u", "#TR_ADVISOR_PERCENT_IN_WORKFORCE", city_population_percent_in_workforce());

    // Yearly births
    ui["text3"].text_var("%s %u", "#TR_ADVISOR_BIRTHS_LAST_YEAR", city_population_yearly_births());

    // Yearly deaths
    ui["text4"].text_var("%s %u", "#TR_ADVISOR_DEATHS_LAST_YEAR", city_population_yearly_deaths());
}

void ui::advisor_population_window::print_history_info() {
    // food stores
    if (g_scenario.kingdom_supplies_grain) {
        ui["text1"] = ui::str(55, 11);
    } else {
        bstring256 text;
        text.printf("%s %u", ui::str(8, 6), city_resource_operating_granaries());

        const auto &resources = g_city.resource;
        if (city_resource_food_supply_months() > 0) {
            text.append_fmt("%s %s %u", ui::str(55, 12), ui::str(8, 4), city_resource_food_supply_months());
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

int ui::advisor_population_window::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    // Title: depends on big graph shown
    const int city_population = g_city.population.current;

    ui["title"] = ui::str(55, graph_order);

    ui["housing"] = "#TR_HEADER_HOUSING";
    ui["housing_button"].onclick([] {
        window_advisors_show_advisor(ADVISOR_HOUSING);
    });

    ui["next_graph"].onclick([this] { ++graph_order; graph_order %= 3; });
    ui["prev_graph"].onclick([this] { --graph_order; if (graph_order < 0) graph_order = 2; });

    return 0;
}

void ui::advisor_population_window::ui_draw_foreground(UiFlags flags) {
    ui.begin_widget(pos);
    ui.draw();

    using graph_function = void (advisor_population_window::*)(int, pcstr body, pcstr title);
    using info_function = void (advisor_population_window::*)();

    graph_function big_graph;
    graph_function top_graph;
    graph_function bot_graph;
    info_function info_panel;

    switch (graph_order) {
    default:
    case 0:
        big_graph = &advisor_population_window::draw_history_graph;
        top_graph = &advisor_population_window::draw_census_graph;
        bot_graph = &advisor_population_window::draw_society_graph;
        info_panel = &advisor_population_window::print_history_info;
        break;
    case 1:
        big_graph = &advisor_population_window::draw_census_graph;
        top_graph = &advisor_population_window::draw_society_graph;
        bot_graph = &advisor_population_window::draw_history_graph;
        info_panel = &advisor_population_window::print_census_info;
        break;
    case 2:
        big_graph = &advisor_population_window::draw_society_graph;
        top_graph = &advisor_population_window::draw_history_graph;
        bot_graph = &advisor_population_window::draw_census_graph;
        info_panel = &advisor_population_window::print_society_info;
        break;
    }

    (*this.*big_graph)(1, "big_graph_tx", "big_text");
    (*this.*top_graph)(0, "next_graph_tx", "top_text");
    (*this.*bot_graph)(0, "prev_graph_tx", "bot_text");

    (*this.*info_panel)();
    ui.end_widget();
}

void ui::advisor_population_window::archive_load(archive arch) {
    advisor_window::archive_load(arch);

    arch.r_desc("graph_bar_1", graph_bar[1]);
    arch.r_desc("graph_bar_2", graph_bar[2]);
    arch.r_desc("graph_bar_3", graph_bar[3]);
    arch.r_desc("graph_bar_4", graph_bar[4]);
}

void ui::advisor_population_window::init() {
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
