#include "advisor_chief.h"

#include "city/city_floods.h"
#include "scenario/request.h"

#include "city/city.h"
#include "city/city_finance.h"
#include "city/city_health.h"
#include "city/city_labor.h"
#include "city/city_migration.h"
#include "city/military.h"
#include "city/city_population.h"
#include "city/city_resource.h"
#include "core/calc.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/view/view.h"
#include "graphics/text.h"
#include "scenario/scenario_invasion.h"
#include "scenario/scenario.h"
#include "window/advisors.h"
#include "game/game.h"
#include "io/gamefiles/lang.h"

ui::advisor_chief_window g_advisor_chief_window;

static void draw_title(int y, int text_id) {
    painter ctx = game.painter();
    ctx.img_generic(image_id_from_group(PACK_GENERAL, 158), { 26, y + 1 });
    lang_text_draw(61, text_id, 44, y, FONT_NORMAL_WHITE_ON_DARK);
}

int ui::advisor_chief_window::draw_background(UiFlags flags) {
    autoconfig_window::draw_background(flags);

    // sentiment
    {
        const int sentiment = g_city.sentiment.value;
        std::pair<int, int> sentiment_status;
        if (sentiment <= 0) { sentiment_status = {20, FONT_NORMAL_YELLOW}; } 
        else if (sentiment >= 100) { sentiment_status = {31, FONT_NORMAL_BLACK_ON_DARK}; }
        else { sentiment_status = {32 + sentiment / 10, FONT_NORMAL_BLACK_ON_DARK}; }
        ui["sentiment_info"].text((pcstr)lang_get_string(61, sentiment_status.first));
        ui["sentiment_info"].font(sentiment_status.second);
    }

    // migration
    {
        std::pair<int, int> migration_status;
        if (g_city.figures_total_invading_enemies() > 3) { migration_status = {43, FONT_NORMAL_BLACK_ON_DARK}; } 
        else if (g_city.migration.newcomers >= 5) { migration_status = {44, FONT_NORMAL_BLACK_ON_DARK}; }
        else if (g_city.migration.no_room_for_immigrants()) { migration_status = {45, FONT_NORMAL_YELLOW}; }
        else if (g_city.migration.percentage >= 80) { migration_status = {44, FONT_NORMAL_BLACK_ON_DARK}; } 
        else {
            migration_status = {43, FONT_NORMAL_BLACK_ON_DARK};
            switch (g_city.migration.problems_cause()) {
            case NO_IMMIGRATION_LOW_WAGES: migration_status.first = 46; break;
            case NO_IMMIGRATION_NO_JOBS: migration_status.first = 47; break;
            case NO_IMMIGRATION_NO_FOOD: migration_status.first = 48; break;
            case NO_IMMIGRATION_HIGH_TAXES: migration_status.first = 49; break;
            case NO_IMMIGRATION_MANY_TENTS: migration_status.first = 50; break;
            case NO_IMMIGRATION_LOW_MOOD: migration_status.first = 51; break;
            default: migration_status.first = 59; break;
            }
        }
        ui["migration_info"].text((pcstr)lang_get_string(61, migration_status.first));
        ui["migration_info"].font(migration_status.second);
    }

    // workers
    {
        int pct_unemployment = g_city.labor.unemployment_percentage;
        int needed_workers = g_city.labor.workers_needed;
        std::pair<int, int> workers_status;
        if (pct_unemployment > 0) {
            if (pct_unemployment > 10) { workers_status = {76, FONT_NORMAL_YELLOW}; }
            else if (pct_unemployment > 5) { workers_status = {77, FONT_NORMAL_YELLOW}; }
            else if (pct_unemployment > 2) { workers_status = {78, FONT_NORMAL_YELLOW}; }
            else { workers_status = {79, FONT_NORMAL_BLACK_ON_DARK}; }
            int unemployed_num = g_city.labor.workers_unemployed - needed_workers;
            ui["workers_info"].text_var("%s %d(%d)", (pcstr)lang_get_string(61, workers_status.first), pct_unemployment, unemployed_num);
        } else if (needed_workers > 0) {
            if (needed_workers > 75) { workers_status = {80, FONT_NORMAL_YELLOW}; }
            else if (needed_workers > 50) { workers_status = {81, FONT_NORMAL_YELLOW }; }
            else if (needed_workers > 25) { workers_status = {82, FONT_NORMAL_YELLOW}; }
            else { workers_status = {83, FONT_NORMAL_BLACK_ON_DARK}; }
            ui["workers_info"].text_var("%s %d", (pcstr)lang_get_string(61, workers_status.first), needed_workers);
        } else {
            workers_status = {84, FONT_NORMAL_BLACK_ON_DARK};
            ui["workers_info"].text((pcstr)lang_get_string(61, workers_status.first));
        }
       
        ui["workers_info"].font(workers_status.second);
    }

    // foodstocks
    {
        std::pair<int, int> foodstocks_status;
        if (g_scenario.kingdom_supplies_grain) {
            foodstocks_status = {26, FONT_NORMAL_BLACK_ON_DARK};
            ui["foodstocks_info"].text((pcstr)lang_get_string(61, foodstocks_status.first));
        } else if (city_resource_food_supply_months() > 0) {
            foodstocks_status = {98, FONT_NORMAL_BLACK_ON_DARK};
            ui["foodstocks_info"].text_var("%s %d", (pcstr)lang_get_string(61, foodstocks_status.first));
        } else {
            foodstocks_status = {95, FONT_NORMAL_YELLOW};
            ui["foodstocks_info"].text((pcstr)lang_get_string(61, foodstocks_status.first));
        }

        ui["foodstocks_info"].font(foodstocks_status.second);
    }

    // foodconsumption
    {
        std::pair<int, int> foodcomsuption_status;
        if (g_scenario.kingdom_supplies_grain) {
            foodcomsuption_status = {26, FONT_NORMAL_BLACK_ON_DARK};
        } else {
            int pct = g_city.resource.food_percentage_produced();
            if (pct > 150) { foodcomsuption_status = {13, FONT_NORMAL_BLACK_ON_DARK}; }
            else if (pct > 105) { foodcomsuption_status = {14, FONT_NORMAL_BLACK_ON_DARK}; }
            else if (pct > 95) { foodcomsuption_status = {15, FONT_NORMAL_BLACK_ON_DARK}; }
            else if (pct > 75) { foodcomsuption_status = {16, FONT_NORMAL_YELLOW}; }
            else if (pct > 30) { foodcomsuption_status = {17, FONT_NORMAL_YELLOW}; }
            else if (pct > 0) { foodcomsuption_status = {18, FONT_NORMAL_YELLOW}; }
            else { foodcomsuption_status = {18, FONT_NORMAL_YELLOW}; }
        }

        ui["foodconsumption_info"].text((pcstr)lang_get_string(61, foodcomsuption_status.first));
        ui["foodconsumption_info"].font(foodcomsuption_status.second);
    }

    // health
    {
        int health_rate = g_city.health.value;
        ui["health_info"].text((pcstr)lang_get_string(61, 103 + health_rate / 10));
        ui["health_info"].font(health_rate >= 40 ? FONT_NORMAL_BLACK_ON_DARK : FONT_NORMAL_YELLOW);
    }

    // religion
    {
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
        ui["religion_info"].text((pcstr)lang_get_string(61, 125));
        ui["religion_info"].font(FONT_NORMAL_BLACK_ON_DARK);
    }

    // finance
    {
        const int treasury = g_city.finance.treasury;
        int balance_last_year = g_city.finance.last_year.balance;
        if (treasury > balance_last_year) { // assets have rison by ...
            ui["finance_info"].text_var("%s %d", (pcstr)lang_get_string(61, 152), treasury - balance_last_year);
            ui["finance_info"].font(FONT_NORMAL_BLACK_ON_DARK);
        } else if (treasury < balance_last_year) { // assets have fallen by ...
            ui["finance_info"].text_var("%s %d", (pcstr)lang_get_string(61, 154), balance_last_year - treasury);
            ui["finance_info"].font(FONT_NORMAL_YELLOW);
        } else if (g_city.taxes.percentage_taxed_people < 75) { // not collecting many taxes!
            ui["finance_info"].text((pcstr)lang_get_string(61, 151));
            ui["finance_info"].font(FONT_NORMAL_BLACK_ON_DARK);
        } else { // doing about as well as last year
            ui["finance_info"].text((pcstr)lang_get_string(61, 153));
            ui["finance_info"].font(FONT_NORMAL_BLACK_ON_DARK);
        }
    }

    // crime
    {
        std::pair<bstring256, int> crime_status;
        const int criminals = g_city.sentiment.criminals;
        if (criminals > 10) {
            crime_status = {bstring256().printf("%s %d %s", (pcstr)lang_get_string(61, 159),
                                                         g_city.finance.this_year.expenses.stolen,
                                                         (pcstr)lang_get_string(61, 164)), FONT_NORMAL_YELLOW};
        } else if (criminals > 7) {
            crime_status = {bstring256().printf("%s %d %s", (pcstr)lang_get_string(61, 160),
                                                         g_city.finance.this_year.expenses.stolen,
                                                         (pcstr)lang_get_string(61, 164)), FONT_NORMAL_YELLOW};
        } else if (criminals > 5) {
            crime_status = {bstring256().printf("%s %d %s", (pcstr)lang_get_string(61, 161),
                                                         g_city.finance.this_year.expenses.stolen,
                                                         (pcstr)lang_get_string(61, 164)), FONT_NORMAL_YELLOW};
        } else if (criminals > 2) {
            crime_status = {bstring256().printf("%s %d %s", (pcstr)lang_get_string(61, 162),
                                                         g_city.finance.this_year.expenses.stolen,
                                                         (pcstr)lang_get_string(61, 164)), FONT_NORMAL_BLACK_ON_DARK};
        } else {
            crime_status = {bstring256().printf("%s", (pcstr)lang_get_string(61, 163)), FONT_NORMAL_BLACK_ON_DARK};
        }

        ui["crime_info"].text_var("%s", crime_status.first.c_str());
        ui["crime_info"].font(crime_status.second);
    }

    // military
    {
        std::pair<int, int> military_status;
        if (g_city.figures.kingdome_soldiers) { military_status = {170, FONT_NORMAL_YELLOW}; }
        else if (g_city.figures.enemies) { military_status = {170, FONT_NORMAL_YELLOW}; }
        else if (scenario_invasion_exists_upcoming()) { military_status = {170, FONT_NORMAL_YELLOW}; }
        else if (city_military_distant_battle_kingdome_army_is_traveling()) { military_status = {170, FONT_NORMAL_BLACK_ON_DARK}; }
        else if (city_military_months_until_distant_battle() > 0) { military_status = {170, FONT_NORMAL_YELLOW}; }
        else if (g_city.figures.soldiers > 0) { military_status = {177, FONT_NORMAL_BLACK_ON_DARK}; }
        else { military_status = {171, FONT_NORMAL_BLACK_ON_DARK}; }

        ui["military_info"].text((pcstr)lang_get_string(61, military_status.first));
        ui["military_info"].font(military_status.second);
    }

    // kingdom
    {
        std::pair<int, int> kingdom_status;
        int requests = scenario_requests_active_count();
        if (requests == 0) { kingdom_status = {187, FONT_NORMAL_BLACK_ON_DARK}; }
        else if (requests == 1) { kingdom_status = {186, FONT_NORMAL_WHITE_ON_DARK}; }
        else if (requests == 2) { kingdom_status = {185, FONT_NORMAL_YELLOW}; }
        else { kingdom_status = {184, FONT_NORMAL_YELLOW}; }

        ui["kingdom_info"].text((pcstr)lang_get_string(61, kingdom_status.first));
        ui["kingdom_info"].font(kingdom_status.second);
    }

    // nilometr
    {
        std::pair<int, int> nilometr_status;
        int flood_quality = g_floods.expected_quality();
        if (flood_quality == 100) { nilometr_status = {197, FONT_NORMAL_BLACK_ON_DARK}; }
        else if (flood_quality > 75) { nilometr_status = {196, FONT_NORMAL_BLACK_ON_DARK}; }
        else if (flood_quality > 50) { nilometr_status = {195, FONT_NORMAL_BLACK_ON_DARK}; }
        else if (flood_quality > 25) { nilometr_status = {194, FONT_NORMAL_BLACK_ON_DARK}; }
        else if (flood_quality > 0) { nilometr_status = {193, FONT_NORMAL_YELLOW}; }
        else { nilometr_status = {192 + flood_quality, FONT_NORMAL_YELLOW}; }

        ui["nilometr_info"].text((pcstr)lang_get_string(61, nilometr_status.first));
        ui["nilometr_info"].font(nilometr_status.second);

        if (flood_quality > 0) {
            int flood_month = g_floods.expected_month();
            ui["nilometr_info2"].text((pcstr)lang_get_string(61, 204 + flood_month));
            ui["nilometr_info2"].font(FONT_NORMAL_BLACK_ON_DARK);
        } else {
            ui["nilometr_info2"].text("");
        }
    }

    return 0;
}

void ui::advisor_chief_window::ui_draw_foreground(UiFlags flags) {
    ui.begin_widget(pos);
    ui.draw();

    int y_line = 306;
    int text_b = 20;

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

    //    // entertainment
    //    draw_title(y_line, 10);
    //    if (demands->entertainment == 1)
    //        lang_text_draw(61, 43, X_OFFSET, y_line, FONT_NORMAL_RED);
    //    else if (demands->entertainment == 2)
    //        lang_text_draw(61, 44, X_OFFSET, y_line, FONT_NORMAL_RED);
    //    else
    //        lang_text_draw(61, 45, X_OFFSET, y_line, FONT_NORMAL_GREEN);
    //    y_line += 20;

    ui.end_widget();
}

advisor_window* ui::advisor_chief_window::instance() {
    return &g_advisor_chief_window;
}
