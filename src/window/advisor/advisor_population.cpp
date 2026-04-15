#include "advisor_population.h"

#include <algorithm>

#include "city/city.h"
#include "city/city_migration.h"
#include "city/city_population.h"
#include "city/ratings.h"
#include "city/city_resource.h"
#include "graphics/image.h"
#include "graphics/elements/lang_text.h"
#include "graphics/text.h"
#include "scenario/scenario.h"
#include "game/game.h"
#include "core/runtime_item.h"

#include "js/js_game.h"

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

namespace {

vec2i get_y_axis(int max_value) {
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

image_desc graph_bar_image(ui::widget& w, int index) {
    bstring32 key;
    key.printf("graph_bar_%d", index);
    return w[key.c_str()].image();
}

} // namespace

void advisor_population::draw_census_graph(ui::widget& w, int full_size, pcstr body, pcstr title) {
    const auto &population = g_city.population;
    const int max_value = *std::max_element(population.at_age.begin(), population.at_age.end());

    vec2i ypx = get_y_axis(max_value);
    int y_max = ypx.x;
    int y_shift = ypx.y;

    const auto &graph = advisor_population_graph_census;
    const vec2i bpos = w[body].pos;
    if (full_size) {
        w[title].text(ui::str(55, 7));
        w.label(bstring32(y_max).c_str(), bpos + graph.y_axis_offset + vec2i{0, 0}, FONT_SMALL_PLAIN, UiFlags_AlignCentered, graph.y_axis_label_w);
        w.label(bstring32(y_max / 2).c_str(), bpos + graph.y_axis_offset + vec2i{0, graph.y_axis_height / 2}, FONT_SMALL_PLAIN, UiFlags_AlignCentered, graph.y_axis_label_w);
        w.label("0", bpos + graph.y_axis_offset + vec2i{ 0, graph.y_axis_height}, FONT_SMALL_PLAIN, UiFlags_AlignCentered, graph.y_axis_label_w);

        for (int i = 0; i <= 10; i++) {
            w.label(bstring32(i * 10).c_str(), bpos + graph.x_axis_offset + vec2i{ 40 * i, 0 }, FONT_SMALL_PLAIN, UiFlags_AlignCentered, graph.y_axis_label_w);
        }
    } else {
        w[title].text(ui::str(55, 4));
    }

    if (full_size) {
        w[title].text(ui::str(55, 6));
        w.set_clip_rectangle({0, 0}, {640, bpos.y + 200});
        for (int i = 0; i < 100; i++) {
            int pop = population.at_age[i];
            int val = (y_shift == -1) ? (2 * pop) : (pop >> y_shift);

            if (val > 0) {
                w.image(graph_bar_image(w, 2), bpos + vec2i{ 4 * i, 200 - val });
            }
        }
        w.reset_clip_rectangle();
    } else {
        y_shift += 2;
        for (int i = 0; i < 100; i++) {
            int val = population.at_age[i] >> y_shift;
            if (val > 0) {
                w.vline(bpos + vec2i{ i, 50 - val }, val, COLOR_RED);
            }
        }
    }
}

void advisor_population::draw_society_graph(ui::widget& w, int full_size, pcstr body, pcstr title) {
    const auto &population = g_city.population;
    const int max_value = *std::max_element(population.at_level.begin(), population.at_level.end());

    vec2i ypx = get_y_axis(max_value);
    int y_max = ypx.x;
    int y_shift = ypx.y;

    const auto& graph = advisor_population_society_history;
    const vec2i bpos = w[body].pos;
    if (full_size) {
        w[title].text(ui::str(55, 8));
        w.label(bstring32(y_max).c_str(), bpos + graph.y_axis_offset, FONT_SMALL_PLAIN, UiFlags_AlignCentered, graph.y_axis_label_w);
        w.label(bstring32(y_max / 2).c_str(), bpos + graph.y_axis_offset + vec2i{ 0, graph.y_axis_height / 2 }, FONT_SMALL_PLAIN, UiFlags_AlignCentered, graph.y_axis_label_w);
        w.label("0", bpos + graph.y_axis_offset + vec2i{ 0, graph.y_axis_height }, FONT_SMALL_PLAIN, UiFlags_AlignCentered, graph.y_axis_label_w);
        w.label(bpos + graph.x_axis_offset, FONT_SMALL_PLAIN, 0, 0, "%s", ui::str(55, 9));
        w.label(bpos + graph.x_axis_offset + vec2i{ graph.x_axis_width, 0 }, FONT_SMALL_PLAIN, 0, 0, "%s", ui::str(55, 10));
    } else {
        w[title].text(ui::str(55, 5));
    }

    if (full_size) {
        w.set_clip_rectangle({0, 0}, {640, bpos.y + 200});
        for (int i = 0; i < HOUSE_LEVEL_MAX; i++) {
            int pop = population.at_level[i];
            int val = (y_shift == -1) ? 2 * pop : (pop >> y_shift);

            if (val > 0) {
                w.image(graph_bar_image(w, 1), bpos + vec2i{ 20 * i, 200 - val });
            }
        }
        w.reset_clip_rectangle();
    } else {
        y_shift += 2;
        for (int i = 0; i < HOUSE_LEVEL_MAX; i++) {
            int val = population.at_level[i] >> y_shift;
            if (val > 0) {
                w.rect(bpos + vec2i{ 5 * i, 50 - val }, vec2i{ 4, val + 1 }, COLOR_RED, COLOR_RED);
            }
        }
    }
}

void advisor_population::print_society_info(ui::widget& w) {
    int avg_tax_per_house = 0;
    if (calculate_total_housing_buildings() > 0) {
        avg_tax_per_house = g_city.taxes.estimated_income / calculate_total_housing_buildings();
    }

    w["text1"].text_var("%s %d", "#TR_ADVISOR_HOUSING_PROSPERITY_RATING", g_city.ratings.prosperity_max);
    w["text2"].text_var("%s %d", "#TR_ADVISOR_PERCENTAGE_IN_MANORS", g_city.population.percentage_in_manors());
    w["text3"].text_var("%s %d", "#TR_ADVISOR_PERCENTAGE_IN_SHANTIES", g_city.population.percentage_in_shanties());
    w["text4"].text_var("%s %d", "#TR_ADVISOR_AVERAGE_TAX", avg_tax_per_house);
}

void advisor_population::print_census_info(ui::widget& w) {
    w["text1"].text_var("%s %d", "#TR_ADVISOR_AVERAGE_AGE", g_city.population.average_age());
    w["text2"].text_var("%s %u", "#TR_ADVISOR_PERCENT_IN_WORKFORCE", city_population_percent_in_workforce());
    w["text3"].text_var("%s %u", "#TR_ADVISOR_BIRTHS_LAST_YEAR", city_population_yearly_births());
    w["text4"].text_var("%s %u", "#TR_ADVISOR_DEATHS_LAST_YEAR", city_population_yearly_deaths());
}

void advisor_population::print_history_info(ui::widget& w) {
    if (g_scenario.kingdom_supplies_grain) {
        w["text1"] = ui::str(55, 11);
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

        w["text1"] = text;
    }

    w["text2"].text_var("%s %u", ui::str(55, 16), g_city.resource.food_types_available_num());

    int newcomers = g_city.migration.newcomers;
    if (newcomers >= 5) {
        w["text3"].text_var("%s %u %s", ui::str(55, 24), newcomers, ui::str(55, 17));
    } else if (g_city.migration.no_room_for_immigrants()) {
        w["text3"].text_var("%s %s", ui::str(55, 24), ui::str(55, 19));
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

        w["text3"] = text;
    } else {
        bstring256 text;
        text.printf("%s, %u", ui::str(55, 24), newcomers);
        text.append(ui::str(55, newcomers == 1 ? 18 : 17));

        w["text3"] = text;
    }
}

void __advisor_population_draw_graph(int kind, int full_size, pcstr body, pcstr title) {
    ui::widget* w = ui::get_current_widget();
    if (!w) {
        return;
    }
    switch (kind) {
    case 1:
        advisor_population::draw_census_graph(*w, full_size, body, title);
        break;
    case 2:
        advisor_population::draw_society_graph(*w, full_size, body, title);
        break;
    default:
        break;
    }
}
ANK_FUNCTION_4(__advisor_population_draw_graph)

void __advisor_population_print_info(int kind) {
    ui::widget* w = ui::get_current_widget();
    if (!w) {
        return;
    }
    switch (kind) {
    case 0:
        advisor_population::print_history_info(*w);
        break;
    case 1:
        advisor_population::print_census_info(*w);
        break;
    case 2:
        advisor_population::print_society_info(*w);
        break;
    default:
        break;
    }
}
ANK_FUNCTION_1(__advisor_population_print_info)
