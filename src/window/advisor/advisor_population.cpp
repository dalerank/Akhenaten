#include "advisor_population.h"

#include "city/city.h"
#include "city/city_migration.h"
#include "city/city_resource.h"
#include "graphics/elements/lang_text.h"
#include "graphics/text.h"
#include "scenario/scenario.h"
#include "game/game.h"

#include "js/js_game.h"

namespace advisor_population {

void print_history_info(ui::widget& w) {
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

} // namespace advisor_population

void __advisor_population_print_info(int kind) {
    ui::widget* w = ui::get_current_widget();
    if (!w) {
        return;
    }
    switch (kind) {
    case 0:
        advisor_population::print_history_info(*w);
        break;
    default:
        break;
    }
}
ANK_FUNCTION_1(__advisor_population_print_info)
