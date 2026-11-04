#include "city/city.h"

#include "building/building.h"
#include "building/building_mansion.h"
#include "city/city_finance.h"
#include "core/profiler.h"
#include "game/game_config.h"

#include <algorithm>
#include <cstdint>

void city_t::government_distribute_treasury() {
    OZZY_PROFILER_FUNCTION();

    building_mansion::update_money_values();

    // OG building_update_money_values + city_finance_building_money_value / palace_share_table.
    // No worker gate — unstaffed vaults still show their share.
    const auto &shares = palace_treasury_shares;
    const int tax_w = shares.tax_collector_weight;
    const int court_w = shares.courthouse_weight;
    const int palace_w = shares.palace_weight;

    auto &blds = buildings;
    const int tax_count = blds.count_total(BUILDING_TAX_COLLECTOR)
        + blds.count_total(BUILDING_TAX_COLLECTOR_UPGRADED);
    const int court_count = blds.count_total(BUILDING_COURTHOUSE);
    const int palace_count = blds.count_total({
        BUILDING_VILLAGE_PALACE,
        BUILDING_TOWN_PALACE,
        BUILDING_CITY_PALACE,
        BUILDING_VILLAGE_PALACE_UP,
        BUILDING_TOWN_PALACE_UP,
    });

    int total_weight = tax_w * tax_count + court_w * court_count + palace_w * palace_count;

    // Remake optional tax vault system: exclude tax offices from the display split.
    if (!!game_features::gameplay_change_new_tax_collection_system) {
        total_weight -= tax_w * tax_count;
    }

    const int treasury = finance.treasury;

    buildings_valid_do([&](building &b) {
        int weight = 0;
        switch (b.type) {
        case BUILDING_VILLAGE_PALACE:
        case BUILDING_TOWN_PALACE:
        case BUILDING_CITY_PALACE:
        case BUILDING_VILLAGE_PALACE_UP:
        case BUILDING_TOWN_PALACE_UP:
            weight = palace_w;
            break;
        case BUILDING_COURTHOUSE:
            weight = court_w;
            break;
        case BUILDING_TAX_COLLECTOR:
        case BUILDING_TAX_COLLECTOR_UPGRADED:
            if (!!game_features::gameplay_change_new_tax_collection_system) {
                return;
            }
            weight = tax_w;
            break;
        default:
            return;
        }

        int value = 0;
        if (treasury > 0 && total_weight > 0 && weight > 0) {
            value = (int)(((double)weight / (double)total_weight) * (double)treasury);
        }
        b.tax_income_or_storage = (int16_t)std::clamp(value, 0, (int)INT16_MAX);
    });
}
