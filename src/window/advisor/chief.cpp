#include "chief.h"
#include <city/floods.h>
#include <scenario/request.h>

#include "city/figures.h"
#include "city/finance.h"
#include "city/health.h"
#include "city/houses.h"
#include "city/labor.h"
#include "city/migration.h"
#include "city/military.h"
#include "city/population.h"
#include "city/resource.h"
#include "city/sentiment.h"
#include "core/calc.h"
#include "graphics/boilerplate.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "scenario/invasion.h"
#include "scenario/property.h"
#include "translation/translation.h"
#include "window/advisors.h"

#define ADVISOR_HEIGHT 24
#define X_OFFSET 185

static void draw_title(int y, int text_id) {
    ImageDraw::img_generic(image_id_from_group(GROUP_BULLET), 26, y + 1);
    lang_text_draw(61, text_id, 44, y, FONT_NORMAL_WHITE_ON_DARK);
}

static int draw_background(void) {
    int width;

    outer_panel_draw(0, 0, 40, ADVISOR_HEIGHT);
    ImageDraw::img_generic(image_id_from_group(GROUP_ADVISOR_ICONS) + 11, 10, 10);

    lang_text_draw(61, 0, 60, 12, FONT_LARGE_BLACK_ON_LIGHT);
    inner_panel_draw(17, 60, 38, 17);

    int y_line = 66;
    int text_b = 20;

    // sentiment
    draw_title(y_line, 1);
    int sentiment = city_sentiment();
    if (sentiment <= 0) {
        lang_text_draw(61, text_b, X_OFFSET, y_line, FONT_NORMAL_YELLOW);
    } else if (sentiment >= 100) {
        lang_text_draw(61, text_b + 11, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        lang_text_draw(61, text_b + 1 + sentiment / 10, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
    }
    y_line += 20;

    // migration
    text_b = 43;
    draw_title(y_line, 2);
    if (city_figures_total_invading_enemies() > 3) {
        lang_text_draw(61, text_b, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
    } else if (city_migration_newcomers() >= 5) {
        lang_text_draw(61, text_b + 1, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
    } else if (city_migration_no_room_for_immigrants()) {
        lang_text_draw(61, text_b + 2, X_OFFSET, y_line, FONT_NORMAL_YELLOW);
    } else if (city_migration_percentage() >= 80) {
        lang_text_draw(61, text_b + 1, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        int text_id;
        switch (city_migration_problems_cause()) {
        case NO_IMMIGRATION_LOW_WAGES:
            text_id = text_b + 3;
            break;
        case NO_IMMIGRATION_NO_JOBS:
            text_id = text_b + 4;
            break;
        case NO_IMMIGRATION_NO_FOOD:
            text_id = text_b + 5;
            break;
        case NO_IMMIGRATION_HIGH_TAXES:
            text_id = text_b + 6;
            break;
        case NO_IMMIGRATION_MANY_TENTS:
            text_id = text_b + 7;
            break;
        case NO_IMMIGRATION_LOW_MOOD:
            text_id = text_b + 8;
            break;
        default:
            text_id = text_b + 16;
            break;
        }
        if (text_id)
            lang_text_draw(61, text_id, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
    }
    y_line += 20;

    // workers
    text_b = 76;
    draw_title(y_line, 3);
    int pct_unemployment = city_labor_unemployment_percentage();
    int needed_workers = city_labor_workers_needed();
    if (pct_unemployment > 0) {
        if (pct_unemployment > 10) {
            width = lang_text_draw(61, text_b, X_OFFSET, y_line, FONT_NORMAL_YELLOW);
        } else if (pct_unemployment > 5) {
            width = lang_text_draw(61, text_b + 1, X_OFFSET, y_line, FONT_NORMAL_YELLOW);
        } else if (pct_unemployment > 2) {
            width = lang_text_draw(61, text_b + 2, X_OFFSET, y_line, FONT_NORMAL_YELLOW);
        } else {
            width = lang_text_draw(61, text_b + 3, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
        }
        width += text_draw_percentage(pct_unemployment, X_OFFSET + width, y_line, FONT_NORMAL_YELLOW);
        text_draw_number(
          city_labor_workers_unemployed() - needed_workers, '(', ")", X_OFFSET + width, y_line, FONT_NORMAL_YELLOW);
    } else if (needed_workers > 0) {
        if (needed_workers > 75) {
            width = lang_text_draw(61, text_b + 4, X_OFFSET, y_line, FONT_NORMAL_YELLOW);
        } else if (needed_workers > 50) {
            width = lang_text_draw(61, text_b + 5, X_OFFSET, y_line, FONT_NORMAL_YELLOW);
        } else if (needed_workers > 25) {
            width = lang_text_draw(61, text_b + 6, X_OFFSET, y_line, FONT_NORMAL_YELLOW);
        } else {
            width = lang_text_draw(61, text_b + 7, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
        }
        lang_text_draw_amount(8, 12, needed_workers, X_OFFSET + width, y_line, FONT_NORMAL_YELLOW);
    } else
        lang_text_draw(61, text_b + 8, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
    y_line += 20;

    //    // housing capacity
    //    imagedrawnamespace::image_draw_namespace::image_draw(image_id_from_group(GROUP_BULLET), 32, y_line + 1);
    //    text_draw(translation_for(TR_HEADER_HOUSING), 52, y_line, FONT_NORMAL_WHITE, 0);
    //
    //    if (!city_population_open_housing_capacity())
    //        width = text_draw(translation_for(TR_ADVISOR_HOUSING_NO_ROOM), X_OFFSET, y_line, FONT_NORMAL_GREEN, 0);
    //    else {
    //        width = text_draw(translation_for(TR_ADVISOR_HOUSING_ROOM), X_OFFSET, y_line, FONT_NORMAL_GREEN, 0);
    //        text_draw_number(city_population_open_housing_capacity(), '@', " ", X_OFFSET + width, y_line,
    //        FONT_NORMAL_GREEN);
    //    }
    //    y_line += 20;

    // food stocks
    text_b = 95;
    draw_title(y_line, 4);
    if (scenario_property_rome_supplies_wheat()) {
        lang_text_draw(61, 26, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
    } else if (city_resource_food_supply_months() > 0) {
        width = lang_text_draw(61, text_b + 3, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw_amount(8, 4, city_resource_food_supply_months(), X_OFFSET + width, y_line, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        lang_text_draw(61, text_b, X_OFFSET, y_line, FONT_NORMAL_YELLOW);
    }
    y_line += 20;

    // food consumption
    text_b = 13;
    draw_title(y_line, 5);
    if (scenario_property_rome_supplies_wheat()) {
        lang_text_draw(61, 26, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        int pct = city_resource_food_percentage_produced();
        if (pct > 150) {
            lang_text_draw(61, text_b, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
        } else if (pct > 105) {
            lang_text_draw(61, text_b + 1, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
        } else if (pct > 95) {
            lang_text_draw(61, text_b + 2, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
        } else if (pct > 75) {
            lang_text_draw(61, text_b + 3, X_OFFSET, y_line, FONT_NORMAL_YELLOW);
        } else if (pct > 30) {
            lang_text_draw(61, text_b + 4, X_OFFSET, y_line, FONT_NORMAL_YELLOW);
        } else if (pct > 0) {
            lang_text_draw(61, text_b + 5, X_OFFSET, y_line, FONT_NORMAL_YELLOW);
        } else {
            lang_text_draw(61, text_b + 5, X_OFFSET, y_line, FONT_NORMAL_YELLOW);
        }
    }
    y_line += 20;

    // health
    text_b = 103;
    draw_title(y_line, 6);
    int health_rate = city_health();
    if (health_rate >= 40)
        lang_text_draw(61, text_b + health_rate / 10, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
    else
        lang_text_draw(61, text_b + health_rate / 10, X_OFFSET, y_line, FONT_NORMAL_YELLOW);
    y_line += 20;

    //    // education
    //    house_demands *demands = city_houses_demands();
    //    draw_title(y_line, 8);
    //    if (demands->education == 1)
    //        lang_text_draw(61, 39, X_OFFSET, y_line, FONT_NORMAL_RED);
    //    else if (demands->education == 2)
    //        lang_text_draw(61, 40, X_OFFSET, y_line, FONT_NORMAL_RED);
    //    else if (demands->education == 3)
    //        lang_text_draw(61, 41, X_OFFSET, y_line, FONT_NORMAL_RED);
    //    else
    //        lang_text_draw(61, 42, X_OFFSET, y_line, FONT_NORMAL_GREEN);
    //    y_line += 20;

    // religion
    text_b = 125;
    draw_title(y_line, 7);
    // todo
    //    house_demands *demands = city_houses_demands();
    //    if (demands->religion == 1)
    //        lang_text_draw(61, 46, X_OFFSET, y_line, FONT_NORMAL_RED);
    //    else if (demands->religion == 2)
    //        lang_text_draw(61, 47, X_OFFSET, y_line, FONT_NORMAL_RED);
    //    else if (demands->religion == 3)
    //        lang_text_draw(61, 48, X_OFFSET, y_line, FONT_NORMAL_RED);
    //    else
    //        lang_text_draw(61, 49, X_OFFSET, y_line, FONT_NORMAL_GREEN);
    y_line += 20;

    // finance
    text_b = 151;
    draw_title(y_line, 8);
    int treasury = city_finance_treasury();
    int balance_last_year = city_finance_overview_last_year()->balance;
    if (treasury > balance_last_year) { // assets have rison by ...
        width = lang_text_draw(61, text_b + 1, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
        text_draw_money(treasury - balance_last_year, X_OFFSET + width, y_line, FONT_NORMAL_BLACK_ON_DARK);
    } else if (treasury < balance_last_year) { // assets have fallen by ...
        width = lang_text_draw(61, text_b + 3, X_OFFSET, y_line, FONT_NORMAL_YELLOW);
        text_draw_money(balance_last_year - treasury, X_OFFSET + width, y_line, FONT_NORMAL_YELLOW);
    } else if (city_finance_percentage_taxed_people() < 75) // not collecting many taxes!
        lang_text_draw(61, text_b, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
    else // doing about as well as last year
        lang_text_draw(61, text_b + 2, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
    y_line += 20;

    // crime
    text_b = 159;
    draw_title(y_line, 9);
    if (city_sentiment_criminals() > 10) {
        width = lang_text_draw(61, text_b, X_OFFSET, y_line, FONT_NORMAL_YELLOW);
        width += text_draw_number(city_finance_overview_this_year()->expenses.stolen, ' ', "", X_OFFSET + width, y_line, FONT_NORMAL_YELLOW);
        lang_text_draw(61, text_b + 5, X_OFFSET + width, y_line, FONT_NORMAL_YELLOW);
    } else if (city_sentiment_criminals() > 7) {
        width = lang_text_draw(61, text_b + 1, X_OFFSET, y_line, FONT_NORMAL_YELLOW);
        width += text_draw_number(city_finance_overview_this_year()->expenses.stolen, ' ', "", X_OFFSET + width, y_line, FONT_NORMAL_YELLOW);
        lang_text_draw(61, text_b + 5, X_OFFSET + width, y_line, FONT_NORMAL_YELLOW);
    } else if (city_sentiment_criminals() > 5) {
        width = lang_text_draw(61, text_b + 2, X_OFFSET, y_line, FONT_NORMAL_YELLOW);
        width += text_draw_number(city_finance_overview_this_year()->expenses.stolen, ' ', "", X_OFFSET + width, y_line, FONT_NORMAL_YELLOW);
        lang_text_draw(61, text_b + 5, X_OFFSET + width, y_line, FONT_NORMAL_YELLOW);
    } else if (city_sentiment_criminals() > 2) {
        width = lang_text_draw(61, text_b + 3, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
        width += text_draw_number(city_finance_overview_this_year()->expenses.stolen, ' ', "", X_OFFSET + width, y_line, FONT_NORMAL_BLACK_ON_DARK);
        lang_text_draw(61, text_b + 5, X_OFFSET + width, y_line, FONT_NORMAL_BLACK_ON_DARK);
    } else {
        lang_text_draw(61, text_b + 4, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
    }
    y_line += 20;

    // military
    text_b = 170;
    // todo
    draw_title(y_line, 10);
    if (city_figures_imperial_soldiers())
        lang_text_draw(61, text_b, X_OFFSET, y_line, FONT_NORMAL_YELLOW);
    else if (city_figures_enemies())
        lang_text_draw(61, text_b, X_OFFSET, y_line, FONT_NORMAL_YELLOW);
    else if (scenario_invasion_exists_upcoming())
        lang_text_draw(61, text_b, X_OFFSET, y_line, FONT_NORMAL_YELLOW);
    else if (city_military_distant_battle_roman_army_is_traveling())
        lang_text_draw(61, text_b, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
    else if (city_military_months_until_distant_battle() > 0)
        lang_text_draw(61, text_b, X_OFFSET, y_line, FONT_NORMAL_YELLOW);
    else if (city_figures_soldiers() > 0) // FIXED was ">=0" (always true)
        lang_text_draw(61, text_b + 7, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
    else
        lang_text_draw(61, text_b + 1, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
    y_line += 20;

    //    // entertainment
    //    draw_title(y_line, 10);
    //    if (demands->entertainment == 1)
    //        lang_text_draw(61, 43, X_OFFSET, y_line, FONT_NORMAL_RED);
    //    else if (demands->entertainment == 2)
    //        lang_text_draw(61, 44, X_OFFSET, y_line, FONT_NORMAL_RED);
    //    else
    //        lang_text_draw(61, 45, X_OFFSET, y_line, FONT_NORMAL_GREEN);
    //    y_line += 20;

    // kingdom
    text_b = 184;
    draw_title(y_line, 11);
    int requests = scenario_requests_active_count();
    if (requests == 0)
        lang_text_draw(61, text_b + 3, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
    else if (requests == 1)
        lang_text_draw(61, text_b + 2, X_OFFSET, y_line, FONT_NORMAL_WHITE_ON_DARK);
    else if (requests == 2)
        lang_text_draw(61, text_b + 1, X_OFFSET, y_line, FONT_NORMAL_YELLOW);
    else
        lang_text_draw(61, text_b + 0, X_OFFSET, y_line, FONT_NORMAL_YELLOW);
    y_line += 20;

    // nilometer
    text_b = 192;
    draw_title(y_line, 12);
    int flood_quality = floodplains_expected_quality();
    if (flood_quality == 100)
        lang_text_draw(61, text_b + 5, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
    else if (flood_quality > 75)
        lang_text_draw(61, text_b + 4, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
    else if (flood_quality > 50)
        lang_text_draw(61, text_b + 3, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
    else if (flood_quality > 25)
        lang_text_draw(61, text_b + 2, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
    else if (flood_quality > 0)
        lang_text_draw(61, text_b + 1, X_OFFSET, y_line, FONT_NORMAL_YELLOW);
    else
        lang_text_draw(61, text_b + flood_quality, X_OFFSET, y_line, FONT_NORMAL_YELLOW);
    y_line += 20;

    // nilometer #2
    text_b = 204;
    if (flood_quality > 0) {
        int flood_month = floodplains_expected_month();
        lang_text_draw(61, text_b + flood_month, X_OFFSET, y_line, FONT_NORMAL_BLACK_ON_DARK);
    }
    y_line += 20;

    return ADVISOR_HEIGHT;
}

const advisor_window_type* window_advisor_chief(void) {
    static const advisor_window_type window = {
        draw_background,
        nullptr,
        nullptr,
        nullptr
    };
    return &window;
}
