#include "city_taxes.h"

#include "building/building.h"
#include "building/building_house.h"
#include "city/buildings.h"
#include "city/city.h"
#include "city/city_finance.h"
#include "city/city_population.h"
#include "city/city_taxes_chunks.h"
#include "core/app_module.h"
#include "core/calc.h"
#include "core/svector.h"
#include "core/xvalue.h"
#include "game/game_config.h"
#include "game/simulation.h"
#include "io/chunk_serializer.h"
#include "js/js_register.h"
#include "scenario/scenario.h"

#include <map>

finance_tax_rules_t ANK_VARIABLE(finance_tax_rules);

city_taxes_t& city_taxes() {
    return xvalue<city_taxes_t>::ref();
}

class taxes_system : public sim_system {
public:
    const char* name() const override { return "taxes"; }
    void on_reset() override { city_taxes().reset(); }
    void on_month() override { city_taxes().collect_monthly(); }
    void on_year() override { city_taxes().advance_year(); }
    void push_save_sections(int file_version) override {
        if (file_version >= 203) {
            g_chunk_io.push_chunk<city_taxes_chunk>(city_taxes_chunk::size, false);
        }
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_taxes_system) {
    static taxes_system system;
    g_simulation.register_system(&system);
}

void city_taxes_t::reset() {
    *this = {};
}

int city_taxes_t::house_monthly_tax_units(building_house* house) const {
    auto& housed = house->runtime_data();
    int tax_mult = house->model().tax_multiplier;
    // OG city_finance_collect_monthly_taxes: model tax × house_tax_bonus_percentage when tax_bonus set.
    if (housed.tax_bonus) {
        tax_mult = calc_adjust_with_percentage(tax_mult, house_tax_bonus_percentage);
    }
    return housed.population * tax_mult;
}

int city_taxes_t::apply_tax_rate(int amount) const {
    return calc_adjust_with_percentage<int>(calc_adjust_with_percentage<int>(amount, g_city.finance.tax_percentage),
      g_scenario.city_tax_percentage());
}

// OG city_finance_collect_monthly_taxes: the house adds city share * tax rate * units.
int city_taxes_t::house_tax_income(int units) const {
    return g_scenario.city_tax_percentage() * g_city.finance.tax_percentage * units;
}

int city_taxes_t::house_tax_units_from_income(int tax_income) const {
    const int scale = std::max(g_scenario.city_tax_percentage() * g_city.finance.tax_percentage, 1);
    return tax_income / scale;
}

void city_taxes_t::update_estimate() {
    auto& taxes = *this;
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
    int estimated_rest_of_year = (12 - g_simulation.simtime.month) * (monthly_patricians + monthly_plebs);

    g_city.finance.this_year.income.taxes = taxes.yearly.collected_citizens + taxes.yearly.collected_nobles;
    taxes.estimated_income = g_city.finance.this_year.income.taxes + estimated_rest_of_year;

    int uncollected_patricians = apply_tax_rate(taxes.monthly.uncollected_nobles);
    int uncollected_plebs = apply_tax_rate(taxes.monthly.uncollected_citizens);
    int uncollected_rest_of_year = (12 - g_simulation.simtime.month) * (uncollected_patricians + uncollected_plebs);
    int uncollected_ytd = taxes.yearly.uncollected_citizens + taxes.yearly.uncollected_nobles;
    taxes.estimated_uncollected = uncollected_ytd + uncollected_rest_of_year;
    if (taxes.estimated_uncollected < 0) {
        taxes.estimated_uncollected = 0;
    }
}

void city_taxes_t::collect_monthly() {
    auto& taxes = *this;
    taxes.taxed_citizens = 0;
    taxes.taxed_nobles = 0;
    taxes.untaxed_citizens = 0;
    taxes.untaxed_nobles = 0;
    taxes.monthly.uncollected_citizens = 0;
    taxes.monthly.collected_citizens = 0;
    taxes.monthly.uncollected_nobles = 0;
    taxes.monthly.collected_nobles = 0;

    for (int i = 0; i < HOUSE_LEVEL_MAX; i++) {
        g_city.population.at_level[i] = 0;
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
        g_city.population.at_level[house->house_level()] += population;

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
        g_city.finance.treasury += collected_total;
    }

    int total_patricians = taxes.taxed_nobles + taxes.untaxed_nobles;
    int total_plebs = taxes.taxed_citizens + taxes.untaxed_citizens;
    taxes.percentage_taxed_nobles = calc_percentage(taxes.taxed_nobles, total_patricians);
    taxes.percentage_taxed_citizens = calc_percentage(taxes.taxed_citizens, total_plebs);
    taxes.percentage_taxed_people
      = calc_percentage(taxes.taxed_nobles + taxes.taxed_citizens, total_patricians + total_plebs);
}

void city_taxes_t::advance_year() {
    g_city.finance.last_year.income.taxes = yearly.collected_citizens + yearly.collected_nobles;
    yearly.collected_citizens = 0;
    yearly.collected_nobles = 0;
    yearly.uncollected_citizens = 0;
    yearly.uncollected_nobles = 0;

    // reset tax income in building list
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        auto house = building_get(i)->dcast_house();
        if (house && house->state() == BUILDING_STATE_VALID) {
            house->runtime_data().tax_income = 0;
        }
    }
}
