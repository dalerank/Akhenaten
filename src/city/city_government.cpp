#include "city/city.h"

#include "building/building_tax_collector.h"
#include "building/building_palace.h"
#include "city/city_finance.h"
#include "core/profiler.h"
#include "game/game_config.h"

void city_t::government_distribute_treasury() {
    OZZY_PROFILER_FUNCTION();

    constexpr int greate_palace_units = 8;
    constexpr int palace_units = 5;
    constexpr int tax_collectpr_up_units = 2;
    constexpr int tax_collector_units = 1;

    const uint32_t vil_palace_count = g_city.buildings.count_active(BUILDING_VILLAGE_PALACE);
    const uint32_t town_palace_count = g_city.buildings.count_active(BUILDING_TOWN_PALACE);
    const uint32_t city_palace_count = g_city.buildings.count_active(BUILDING_CITY_PALACE);
    const uint32_t tax_col_count = g_city.buildings.count_active(BUILDING_TAX_COLLECTOR);
    const uint32_t tax_col_up_count = g_city.buildings.count_active(BUILDING_TAX_COLLECTOR_UPGRADED);

    int units = palace_units * (vil_palace_count + town_palace_count + city_palace_count);
                    //+ greate_palace_units * palace_up_count;

    if (!game_features::gameplay_change_new_tax_collection_system) {
        units += tax_collector_units * tax_col_count 
                    + tax_collectpr_up_units * tax_col_up_count;
    }

    int amount_per_unit = 0;
    int remainder = 0;
    const int treasury = finance.treasury;

    if (treasury > 0 && units > 0) {
        amount_per_unit = treasury / units;
        remainder = treasury - units * amount_per_unit;
    } 

    buildings_valid_do([&] (building &b) {
        if (b.num_workers <= 0) {
            return;
        }

        switch (b.type) {
        // ordered based on importance: most important gets the remainder
        //case BUILDING_GREATE_PALACE_UPGRADED:
        //    b.tax_income_or_storage = greate_palace_units * amount_per_unit + remainder;
        //    remainder = 0;
        //    break;

        case BUILDING_VILLAGE_PALACE:
        case BUILDING_TOWN_PALACE:
        case BUILDING_CITY_PALACE:
            {
                auto palace = b.dcast_palace();    
                palace->runtime_data().tax_income_or_storage = palace_units * amount_per_unit + remainder;
                remainder = 0;
            }
            break;

        case BUILDING_TAX_COLLECTOR_UPGRADED:
            if (!game_features::gameplay_change_new_tax_collection_system) {
                auto collector = b.dcast_tax_collector();
                collector->runtime_data().tax_income_or_storage = tax_collectpr_up_units * amount_per_unit + remainder;
                remainder = 0;
            }
            break;

        case BUILDING_TAX_COLLECTOR:
            if (!game_features::gameplay_change_new_tax_collection_system) {
                auto collector = b.dcast_tax_collector();
                collector->runtime_data().tax_income_or_storage = amount_per_unit + remainder;
                remainder = 0;
            }
            break;

        default:
            ; // nothing
        }
    });
}
