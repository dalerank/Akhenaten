#pragma once

#include <cstdint>

#include "core/archive.h"
#include "game/difficulty.h"

class building_house;
struct finance_state;
struct city_population_t;

struct taxes_state {
    int32_t taxed_citizens;
    int32_t taxed_nobles;
    int32_t untaxed_citizens;
    int32_t untaxed_nobles;
    int32_t estimated_uncollected;
    int32_t estimated_income;
    int house_tax_bonus_percentage = 110;
    int8_t percentage_taxed_citizens;
    int8_t percentage_taxed_nobles;
    int8_t percentage_taxed_people;
    struct {
        int32_t collected_citizens;
        int32_t collected_nobles;
        int32_t uncollected_citizens;
        int32_t uncollected_nobles;
    } yearly;
    struct {
        int32_t collected_citizens;
        int32_t collected_nobles;
        int32_t uncollected_citizens;
        int32_t uncollected_nobles;
    } monthly;
};
ANK_CONFIG_PROPERTY(taxes_state, percentage_taxed_people, estimated_uncollected, estimated_income,
  house_tax_bonus_percentage)

// tax_percentage: per difficulty, the percent of the taxed amount the city keeps (OG
// difficulty_tax_percentages); a mission may override it. house_tax_income_unit: a house's yearly tax
// income is kept in 1/unit deben (OG HOUSE_TAX_INCOME_UNIT).
struct finance_tax_rules_t {
    int_dcy tax_percentage;
    int house_tax_income_unit;
};
ANK_CONFIG_STRUCT(finance_tax_rules_t, tax_percentage, house_tax_income_unit)
extern finance_tax_rules_t finance_tax_rules;

struct taxes_context {
    finance_state& finance;
    city_population_t& population;
    int month;
    int city_tax_percentage;
};

class taxes_system {
public:
    taxes_system(taxes_state& state, const taxes_context& ctx) : _state(state), _ctx(ctx) {}

    void update_estimate();
    void collect_monthly();
    void advance_year();
    int house_monthly_tax_units(building_house* house) const;
    int apply_tax_rate(int amount) const;
    int house_tax_income(int units) const;
    int house_tax_units_from_income(int tax_income) const;

private:
    taxes_state& _state;
    taxes_context _ctx;
};
