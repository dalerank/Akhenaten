#include "government.h"

#include "building/building.h"
#include "building/count.h"
#include "city/finance.h"
#include "core/game_environment.h"
#include "core/profiler.h"

void building_government_distribute_treasury(void) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Distribute Treasury");
    
    int units = 5 * building_count_active(BUILDING_GREATE_PALACE) + 1 * building_count_active(BUILDING_TAX_COLLECTOR)
                + 8 * building_count_active(BUILDING_GREATE_PALACE_UPGRADED)
                + 2 * building_count_active(BUILDING_TAX_COLLECTOR_UPGRADED);

    int amount_per_unit;
    int remainder;
    int treasury = city_finance_treasury();
    if (treasury > 0 && units > 0) {
        amount_per_unit = treasury / units;
        remainder = treasury - units * amount_per_unit;
    } else {
        amount_per_unit = 0;
        remainder = 0;
    }

    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_VALID || b->house_size)
            continue;

        b->tax_income_or_storage = 0;
        if (b->num_workers <= 0)
            continue;

        switch (b->type) {
        // ordered based on importance: most important gets the remainder
        case BUILDING_GREATE_PALACE_UPGRADED:
            b->tax_income_or_storage = 8 * amount_per_unit + remainder;
            remainder = 0;
            break;

        case BUILDING_GREATE_PALACE:
            if (remainder && !building_count_active(BUILDING_GREATE_PALACE_UPGRADED)) {
                b->tax_income_or_storage = 5 * amount_per_unit + remainder;
                remainder = 0;
            } else {
                b->tax_income_or_storage = 5 * amount_per_unit;
            }
            break;

        case BUILDING_TAX_COLLECTOR_UPGRADED:
            if (remainder
                && !(building_count_active(BUILDING_GREATE_PALACE_UPGRADED) || building_count_active(BUILDING_GREATE_PALACE))) {
                b->tax_income_or_storage = 2 * amount_per_unit + remainder;
                remainder = 0;
            } else {
                b->tax_income_or_storage = 2 * amount_per_unit;
            }
            break;

        case BUILDING_TAX_COLLECTOR:
            if (remainder
                && !(building_count_active(BUILDING_GREATE_PALACE_UPGRADED) || building_count_active(BUILDING_GREATE_PALACE)
                     || building_count_active(BUILDING_TAX_COLLECTOR_UPGRADED))) {
                b->tax_income_or_storage = amount_per_unit + remainder;
                remainder = 0;
            } else {
                b->tax_income_or_storage = amount_per_unit;
            }
            break;
        }
    }
}
