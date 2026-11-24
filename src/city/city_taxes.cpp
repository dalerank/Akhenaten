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
#include "io/gamestate/save_versions.h"
#include "js/js_register.h"
#include "scenario/scenario.h"

#include <utility>

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
        if (file_version >= save_version_city_sections) {
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

int city_taxes_t::tax_rate_scale() const {
    return g_scenario.city_tax_percentage() * g_city.finance.tax_percentage;
}

int city_taxes_t::apply_tax_rate(int amount) const {
    return calc_adjust_with_percentage<int>(calc_adjust_with_percentage<int>(amount, g_city.finance.tax_percentage),
      g_scenario.city_tax_percentage());
}

// OG city_finance_collect_monthly_taxes: the house adds city share * tax rate * units.
int city_taxes_t::house_tax_income(int units) const {
    return tax_rate_scale() * units;
}

int city_taxes_t::house_tax_units_from_income(int tax_income) const {
    return tax_income / std::max(tax_rate_scale(), 1);
}

void city_taxes_t::update_estimate() {
    monthly.collected_citizens = 0;
    monthly.collected_nobles = 0;
    monthly.uncollected_citizens = 0;
    monthly.uncollected_nobles = 0;

    buildings_house_do([this](auto house) {
        if (!house->hsize()) {
            return;
        }

        auto& housed = house->runtime_data();
        const int tax = housed.population * house->model().tax_multiplier;

        if (housed.tax_coverage) {
            if (house->is_nobles()) {
                monthly.collected_nobles += tax;
            } else {
                monthly.collected_citizens += tax;
            }
        } else {
            if (house->is_nobles()) {
                monthly.uncollected_nobles += tax;
            } else {
                monthly.uncollected_citizens += tax;
            }
        }
    });

    int monthly_patricians = apply_tax_rate(monthly.collected_nobles);
    int monthly_plebs = apply_tax_rate(monthly.collected_citizens);
    int estimated_rest_of_year = (12 - g_simulation.simtime.month) * (monthly_patricians + monthly_plebs);

    g_city.finance.set_tax_income_this_year(yearly.collected_citizens + yearly.collected_nobles);
    estimated_income = yearly.collected_citizens + yearly.collected_nobles + estimated_rest_of_year;

    int uncollected_patricians = apply_tax_rate(monthly.uncollected_nobles);
    int uncollected_plebs = apply_tax_rate(monthly.uncollected_citizens);
    int uncollected_rest_of_year = (12 - g_simulation.simtime.month) * (uncollected_patricians + uncollected_plebs);
    int uncollected_ytd = yearly.uncollected_citizens + yearly.uncollected_nobles;
    estimated_uncollected = uncollected_ytd + uncollected_rest_of_year;
    if (estimated_uncollected < 0) {
        estimated_uncollected = 0;
    }
}

void city_taxes_t::collect_monthly() {
    taxed_citizens = 0;
    taxed_nobles = 0;
    untaxed_citizens = 0;
    untaxed_nobles = 0;
    monthly.uncollected_citizens = 0;
    monthly.collected_citizens = 0;
    monthly.uncollected_nobles = 0;
    monthly.collected_nobles = 0;

    const bool collectors_keep_taxes = !!game_features::gameplay_change_new_tax_collection_system;
    svector<std::pair<building_id, uint32_t>, 256> collectors;
    auto collector_amount = [&collectors](building_id id) -> uint32_t* {
        for (auto& c : collectors) {
            if (c.first == id) {
                return &c.second;
            }
        }
        if (collectors.size() >= collectors.capacity()) {
            return nullptr;
        }
        collectors.push_back({id, 0});
        return &collectors.back().second;
    };

    if (collectors_keep_taxes) {
        svector<building*, 64> buildings;
        buildings_get(buildings, BUILDING_TAX_COLLECTOR, BUILDING_TAX_COLLECTOR_UPGRADED);
        for (auto& b : buildings) {
            collector_amount(b->id);
        }
    }

    buildings_house_do([&](auto house) {
        if (!house->hsize()) {
            return;
        }

        auto& housed = house->runtime_data();
        const bool is_nobles = house->is_nobles();
        int population = housed.population;

        const int tax = house_monthly_tax_units(house);
        if (housed.tax_coverage) {
            if (is_nobles) {
                taxed_nobles += population;
                monthly.collected_nobles += tax;
            } else {
                taxed_citizens += population;
                monthly.collected_citizens += tax;
            }

            if (collectors_keep_taxes) {
                if (uint32_t* amount = collector_amount(housed.tax_collector_id)) {
                    *amount += tax;
                }
                housed.tax_collector_id = 0;
            }

            housed.tax_income += house_tax_income(tax);
        } else {
            if (is_nobles) {
                untaxed_nobles += population;
                monthly.uncollected_nobles += tax;
            } else {
                untaxed_citizens += population;
                monthly.uncollected_citizens += tax;
            }
        }
    });

    int collected_nobles = apply_tax_rate(monthly.collected_nobles);
    int collected_citizens = apply_tax_rate(monthly.collected_citizens);
    int collected_total = collected_nobles + collected_citizens;

    yearly.collected_nobles += collected_nobles;
    yearly.collected_citizens += collected_citizens;
    yearly.uncollected_nobles += apply_tax_rate(monthly.uncollected_nobles);
    yearly.uncollected_citizens += apply_tax_rate(monthly.uncollected_citizens);

    if (collectors_keep_taxes) {
        for (auto& c : collectors) {
            building_get(c.first)->deben_storage += apply_tax_rate((int)c.second);
        }
    } else {
        g_city.finance.collect_taxes(collected_total);
    }

    int total_patricians = taxed_nobles + untaxed_nobles;
    int total_plebs = taxed_citizens + untaxed_citizens;
    percentage_taxed_nobles = calc_percentage(taxed_nobles, total_patricians);
    percentage_taxed_citizens = calc_percentage(taxed_citizens, total_plebs);
    percentage_taxed_people = calc_percentage(taxed_nobles + taxed_citizens, total_patricians + total_plebs);
}

void city_taxes_t::advance_year() {
    g_city.finance.close_tax_year(yearly.collected_citizens + yearly.collected_nobles);
    yearly.collected_citizens = 0;
    yearly.collected_nobles = 0;
    yearly.uncollected_citizens = 0;
    yearly.uncollected_nobles = 0;

    buildings_house_do([](auto house) {
        if (house->state() == BUILDING_STATE_VALID) {
            house->runtime_data().tax_income = 0;
        }
    });
}
