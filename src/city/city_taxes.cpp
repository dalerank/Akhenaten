#include "city_taxes.h"

#include "building/building.h"
#include "building/building_house.h"
#include "city/buildings.h"
#include "city/city_finance.h"
#include "city/city_population.h"
#include "core/calc.h"
#include "core/svector.h"
#include "game/game_config.h"
#include "js/js_register.h"

#include <map>

finance_tax_rules_t ANK_VARIABLE(finance_tax_rules);

int taxes_system::house_monthly_tax_units(building_house* house) const {
    auto& housed = house->runtime_data();
    int tax_mult = house->model().tax_multiplier;
    // OG city_finance_collect_monthly_taxes: model tax × house_tax_bonus_percentage when tax_bonus set.
    if (housed.tax_bonus) {
        tax_mult = calc_adjust_with_percentage(tax_mult, _state.house_tax_bonus_percentage);
    }
    return housed.population * tax_mult;
}

int taxes_system::apply_tax_rate(int amount) const {
    return calc_adjust_with_percentage<int>(calc_adjust_with_percentage<int>(amount, _ctx.finance.tax_percentage),
      _ctx.city_tax_percentage);
}

// OG city_finance_collect_monthly_taxes: the house adds city share * tax rate * units.
int taxes_system::house_tax_income(int units) const {
    return _ctx.city_tax_percentage * _ctx.finance.tax_percentage * units;
}

int taxes_system::house_tax_units_from_income(int tax_income) const {
    const int scale = std::max(_ctx.city_tax_percentage * _ctx.finance.tax_percentage, 1);
    return tax_income / scale;
}

void taxes_system::update_estimate() {
    auto& taxes = _state;
    taxes.monthly.collected_citizens = 0;
    taxes.monthly.collected_nobles = 0;
    taxes.monthly.uncollected_citizens = 0;
    taxes.monthly.uncollected_nobles = 0;

    buildings_house_do([&taxes](auto house) {
        if (!house->hsize()) {
            return;
        }

        auto& housed = house->runtime_data();
        const int tax = housed.population * house->model().tax_multiplier;

        if (housed.tax_coverage) {
            if (house->is_nobles()) {
                taxes.monthly.collected_nobles += tax;
            } else {
                taxes.monthly.collected_citizens += tax;
            }
        } else {
            if (house->is_nobles()) {
                taxes.monthly.uncollected_nobles += tax;
            } else {
                taxes.monthly.uncollected_citizens += tax;
            }
        }
    });

    int monthly_patricians = apply_tax_rate(taxes.monthly.collected_nobles);
    int monthly_plebs = apply_tax_rate(taxes.monthly.collected_citizens);
    int estimated_rest_of_year = (12 - _ctx.month) * (monthly_patricians + monthly_plebs);

    _ctx.finance.this_year.income.taxes = taxes.yearly.collected_citizens + taxes.yearly.collected_nobles;
    taxes.estimated_income = _ctx.finance.this_year.income.taxes + estimated_rest_of_year;

    int uncollected_patricians = apply_tax_rate(taxes.monthly.uncollected_nobles);
    int uncollected_plebs = apply_tax_rate(taxes.monthly.uncollected_citizens);
    int uncollected_rest_of_year = (12 - _ctx.month) * (uncollected_patricians + uncollected_plebs);
    int uncollected_ytd = taxes.yearly.uncollected_citizens + taxes.yearly.uncollected_nobles;
    taxes.estimated_uncollected = uncollected_ytd + uncollected_rest_of_year;
    if (taxes.estimated_uncollected < 0) {
        taxes.estimated_uncollected = 0;
    }
}

void taxes_system::collect_monthly() {
    auto& taxes = _state;
    taxes.taxed_citizens = 0;
    taxes.taxed_nobles = 0;
    taxes.untaxed_citizens = 0;
    taxes.untaxed_nobles = 0;
    taxes.monthly.uncollected_citizens = 0;
    taxes.monthly.collected_citizens = 0;
    taxes.monthly.uncollected_nobles = 0;
    taxes.monthly.collected_nobles = 0;

    for (int i = 0; i < HOUSE_LEVEL_MAX; i++) {
        _ctx.population.at_level[i] = 0;
    }

    std::map<int, uint32_t> tax_collectors;
    if (!!game_features::gameplay_change_new_tax_collection_system) {
        svector<building*, 64> buildings;
        buildings_get(buildings, BUILDING_TAX_COLLECTOR, BUILDING_TAX_COLLECTOR_UPGRADED);
        for (auto& b : buildings) {
            tax_collectors.insert({b->id, 0});
        }
    }

    buildings_house_do([&](auto house) {
        if (!house->hsize()) {
            return;
        }

        auto& housed = house->runtime_data();
        int is_nobles = (house->house_level() >= HOUSE_COMMON_MANOR);
        int population = housed.population;
        _ctx.population.at_level[house->house_level()] += population;

        const int tax = house_monthly_tax_units(house);
        if (housed.tax_coverage) {
            if (is_nobles) {
                taxes.taxed_nobles += population;
                taxes.monthly.collected_nobles += tax;
            } else {
                taxes.taxed_citizens += population;
                taxes.monthly.collected_citizens += tax;
            }

            if (!!game_features::gameplay_change_new_tax_collection_system) {
                tax_collectors[housed.tax_collector_id] += tax;
                housed.tax_collector_id = 0;
            }

            housed.tax_income += house_tax_income(tax);
        } else {
            if (is_nobles) {
                taxes.untaxed_nobles += population;
                taxes.monthly.uncollected_nobles += tax;
            } else {
                taxes.untaxed_citizens += population;
                taxes.monthly.uncollected_citizens += tax;
            }
        }
    });

    int collected_nobles = apply_tax_rate(taxes.monthly.collected_nobles);
    int collected_citizens = apply_tax_rate(taxes.monthly.collected_citizens);
    int collected_total = collected_nobles + collected_citizens;

    taxes.yearly.collected_nobles += collected_nobles;
    taxes.yearly.collected_citizens += collected_citizens;
    taxes.yearly.uncollected_nobles += apply_tax_rate(taxes.monthly.uncollected_nobles);
    taxes.yearly.uncollected_citizens += apply_tax_rate(taxes.monthly.uncollected_citizens);

    if (!!game_features::gameplay_change_new_tax_collection_system) {
        for (auto& it : tax_collectors) {
            building* b = building_get(it.first);
            b->deben_storage += apply_tax_rate((int)it.second);
        }
    } else {
        _ctx.finance.treasury += collected_total;
    }

    int total_patricians = taxes.taxed_nobles + taxes.untaxed_nobles;
    int total_plebs = taxes.taxed_citizens + taxes.untaxed_citizens;
    taxes.percentage_taxed_nobles = calc_percentage(taxes.taxed_nobles, total_patricians);
    taxes.percentage_taxed_citizens = calc_percentage(taxes.taxed_citizens, total_plebs);
    taxes.percentage_taxed_people
      = calc_percentage(taxes.taxed_nobles + taxes.taxed_citizens, total_patricians + total_plebs);
}

void taxes_system::advance_year() {
    _ctx.finance.last_year.income.taxes = _state.yearly.collected_citizens + _state.yearly.collected_nobles;
    _state.yearly.collected_citizens = 0;
    _state.yearly.collected_nobles = 0;
    _state.yearly.uncollected_citizens = 0;
    _state.yearly.uncollected_nobles = 0;

    // reset tax income in building list
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        auto house = building_get(i)->dcast_house();
        if (house && house->state() == BUILDING_STATE_VALID) {
            house->runtime_data().tax_income = 0;
        }
    }
}
