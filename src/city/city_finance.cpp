#include "city_finance.h"

#include "core/svector.h"
#include "building/building.h"
#include "building/building_house.h"
#include "buildings.h"
#include "city/city_kingdome_relations.h"
#include "city/city_labor.h"
#include "city/city_population.h"
#include "game/game_events.h"
#include "core/calc.h"
#include "game/difficulty.h"
#include "game/game_config.h"
#include "core/random.h"
#include "figure/figure.h"
#include "building/building_mansion.h"
#include "city/city_resource.h"
#include "empire/trade_prices.h"
#include "game/resource.h"
#include "js/js_register.h"
#include "scenario/scenario.h"

#include <map>

using e_finance_value_tokens_t = token_holder<e_finance_value, e_finance_value_gold_delivered, e_finance_value_max>;
const e_finance_value_tokens_t ANK_CONFIG_ENUM(e_finance_value_tokens);

int finance_system::house_monthly_tax_units(const finance_context& ctx, building_house* house) {
    auto &housed = house->runtime_data();
    int tax_mult = house->model().tax_multiplier;
    // OG city_finance_collect_monthly_taxes: model tax × house_tax_bonus_percentage when tax_bonus set.
    if (housed.tax_bonus) {
        tax_mult = calc_adjust_with_percentage(tax_mult, ctx.taxes.house_tax_bonus_percentage);
    }
    return housed.population * tax_mult;
}

int finance_system::apply_tax_rate(const finance_state& f, const finance_context& ctx, int amount) {
    return calc_adjust_with_percentage<int>(calc_adjust_with_percentage<int>(amount, f.tax_percentage),
      ctx.city_tax_percentage);
}

// OG city_finance_collect_monthly_taxes: the house adds city share * tax rate * units.
int finance_system::house_tax_income(const finance_state& f, const finance_context& ctx, int units) {
    return ctx.city_tax_percentage * f.tax_percentage * units;
}

int finance_system::house_tax_units_from_income(const finance_state& f, const finance_context& ctx, int tax_income) {
    const int scale = std::max(ctx.city_tax_percentage * f.tax_percentage, 1);
    return tax_income / scale;
}

using e_finance_request_type_tokens_t = token_holder<e_finance_request_type, efinance_request_none, efinance_request_max>;
const e_finance_request_type_tokens_t ANK_CONFIG_ENUM(e_finance_request_type_tokens);

palace_treasury_shares_t ANK_VARIABLE(palace_treasury_shares);
finance_tax_rules_t ANK_VARIABLE(finance_tax_rules);

void finance_system::init(finance_state& f) {
    f.wages_kingdome = 30;
    f.wages = 30;
}

void finance_system::subscribe_events(finance_state& f, finance_context (*make_context)()) {
    events::subscribe([&f](event_finance_donation ev) {
        f.treasury += ev.amount;
        f.this_year.income.donated += ev.amount;
    });

    events::subscribe(
      [&f, make_context](event_finance_request ev) { process_request(f, make_context(), {ev.type, ev.deben}); });

    events::subscribe([&f, make_context](event_finance_change_wages ev) {
        change_wages(f, ev.value);
        estimate_wages(f, make_context());
        calculate_totals(f);
    });

    // HE2 runtime-only counters (not in save): clear after load / new mission.
    events::subscribe([&f](event_level_post_load) {
        f.wages_grain_deben_so_far = 0;
        f.wages_grain_deben_last_year = 0;
    });
}

void finance_system::change_wages(finance_state& f, int amount) {
    f.wages += amount;
    f.wages = calc_bound(f.wages, 0, 100);
}

int finance_system::raise_wages_kingdome(finance_state& f) {
    if (f.wages_kingdome >= 45)
        return 0;

    f.wages_kingdome += 1 + (random_byte_alt() & 3);
    if (f.wages_kingdome > 45)
        f.wages_kingdome = 45;

    return 1;
}

int finance_system::lower_wages_kingdome(finance_state& f) {
    if (f.wages_kingdome <= 5)
        return 0;

    f.wages_kingdome -= 1 + (random_byte_alt() & 3);
    return 1;
}

bool finance_system::is_out_of_money(const finance_state& f) {
    return (f.treasury <= -5000);
}

void finance_system::process_stolen(finance_state& f, int stolen) {
    f.treasury -= stolen;
    f.this_year.expenses.stolen += stolen;
    f.crimes_this_month++;
    f.gold_stolen_this_month += stolen;
}

void finance_system::update_interest(finance_state& f) {
    f.this_year.expenses.interest = f.interest_so_far;
}

void finance_system::calculate_totals(finance_state& f) {
    auto& this_year = f.this_year;
    auto& last_year = f.last_year;
    this_year.income.total
      = this_year.income.donated + this_year.income.taxes + this_year.income.exports + this_year.income.gold_delivered;

    this_year.expenses.total = this_year.expenses.stolen + this_year.expenses.mayour_salary
                               + this_year.expenses.accountant_salary + this_year.expenses.interest
                               + this_year.expenses.construction + this_year.expenses.wages + this_year.expenses.imports
                               + this_year.expenses.festivals + this_year.expenses.kingdome
                               + this_year.expenses.disasters;

    last_year.income.total
      = last_year.income.donated + last_year.income.taxes + last_year.income.exports + last_year.income.gold_delivered;

    last_year.expenses.total = last_year.expenses.stolen + last_year.expenses.mayour_salary
                               + last_year.expenses.accountant_salary + last_year.expenses.interest
                               + last_year.expenses.construction + last_year.expenses.wages + last_year.expenses.imports
                               + last_year.expenses.festivals + last_year.expenses.kingdome
                               + last_year.expenses.disasters;

    last_year.net_in_out = last_year.income.total - last_year.expenses.total;
    this_year.net_in_out = this_year.income.total - this_year.expenses.total;
    this_year.balance = last_year.balance + this_year.net_in_out;

    this_year.expenses.tribute = 0;
}

void finance_system::estimate_wages(finance_state& f, const finance_context& ctx) {
    int monthly_wages = f.wages * ctx.labor.workers_employed / 10 / 12;
    f.this_year.expenses.wages = f.wages_so_far;
    f.estimated_wages = (12 - ctx.month) * monthly_wages + f.wages_so_far;
}

void finance_system::process_request(finance_state& f, const finance_context& ctx, event_finance_request request) {
    auto& treasury = f.treasury;
    auto& this_year = f.this_year;
    switch (request.type) {
    case efinance_request_festival:
        treasury -= request.deben;
        this_year.expenses.festivals += request.deben;
        break;

    case efinance_request_kigdome:
        treasury -= request.deben;
        this_year.expenses.kingdome += request.deben;
        break;

    case efinance_request_disasters:
        treasury -= request.deben;
        this_year.expenses.disasters += request.deben;
        break;

    case efinance_request_import:
        treasury -= request.deben;
        this_year.expenses.imports += request.deben;
        break;

    case efinance_request_export:
        treasury += request.deben;
        this_year.income.exports += request.deben;
        break;

    case efinance_request_personal_salary:
        this_year.expenses.mayour_salary += request.deben;
        ctx.kingdome.personal_savings += request.deben;
        treasury -= request.deben;
        break;

    case efinance_request_gold_delivered:
        treasury += request.deben;
        this_year.income.gold_delivered += request.deben;
        break;

    case efinance_request_tax_collected:
        this_year.income.taxes += request.deben;
        treasury += request.deben;
        break;

    case efinance_request_construction:
        treasury -= request.deben;
        this_year.expenses.construction += request.deben;
        break;

    default:
        verify_no_crash(false && "something strange");
    }
}

void finance_system::update_estimate_taxes(finance_state& f, const finance_context& ctx) {
    auto& taxes = ctx.taxes;
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

    int monthly_patricians = apply_tax_rate(f, ctx, taxes.monthly.collected_nobles);
    int monthly_plebs = apply_tax_rate(f, ctx, taxes.monthly.collected_citizens);
    int estimated_rest_of_year = (12 - ctx.month) * (monthly_patricians + monthly_plebs);

    f.this_year.income.taxes = taxes.yearly.collected_citizens + taxes.yearly.collected_nobles;
    taxes.estimated_income = f.this_year.income.taxes + estimated_rest_of_year;

    int uncollected_patricians = apply_tax_rate(f, ctx, taxes.monthly.uncollected_nobles);
    int uncollected_plebs = apply_tax_rate(f, ctx, taxes.monthly.uncollected_citizens);
    int uncollected_rest_of_year = (12 - ctx.month) * (uncollected_patricians + uncollected_plebs);
    int uncollected_ytd = taxes.yearly.uncollected_citizens + taxes.yearly.uncollected_nobles;
    taxes.estimated_uncollected = uncollected_ytd + uncollected_rest_of_year;
    if (taxes.estimated_uncollected < 0) {
        taxes.estimated_uncollected = 0;
    }
}

void finance_system::collect_monthly_taxes(finance_state& f, const finance_context& ctx) {
    auto& taxes = ctx.taxes;
    taxes.taxed_citizens = 0;
    taxes.taxed_nobles = 0;
    taxes.untaxed_citizens = 0;
    taxes.untaxed_nobles = 0;
    taxes.monthly.uncollected_citizens = 0;
    taxes.monthly.collected_citizens = 0;
    taxes.monthly.uncollected_nobles = 0;
    taxes.monthly.collected_nobles = 0;

    for (int i = 0; i < HOUSE_LEVEL_MAX; i++) {
        ctx.population.at_level[i] = 0;
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
        ctx.population.at_level[house->house_level()] += population;

        const int tax = house_monthly_tax_units(ctx, house);
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

            housed.tax_income += house_tax_income(f, ctx, tax);
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

    int collected_nobles = apply_tax_rate(f, ctx, taxes.monthly.collected_nobles);
    int collected_citizens = apply_tax_rate(f, ctx, taxes.monthly.collected_citizens);
    int collected_total = collected_nobles + collected_citizens;

    taxes.yearly.collected_nobles += collected_nobles;
    taxes.yearly.collected_citizens += collected_citizens;
    taxes.yearly.uncollected_nobles += apply_tax_rate(f, ctx, taxes.monthly.uncollected_nobles);
    taxes.yearly.uncollected_citizens += apply_tax_rate(f, ctx, taxes.monthly.uncollected_citizens);

    if (!!game_features::gameplay_change_new_tax_collection_system) {
        for (auto& it : tax_collectors) {
            building* b = building_get(it.first);
            b->deben_storage += apply_tax_rate(f, ctx, (int)it.second);
        }
    } else {
        f.treasury += collected_total;
    }

    int total_patricians = taxes.taxed_nobles + taxes.untaxed_nobles;
    int total_plebs = taxes.taxed_citizens + taxes.untaxed_citizens;
    taxes.percentage_taxed_nobles = calc_percentage(taxes.taxed_nobles, total_patricians);
    taxes.percentage_taxed_citizens = calc_percentage(taxes.taxed_citizens, total_plebs);
    taxes.percentage_taxed_people
      = calc_percentage(taxes.taxed_nobles + taxes.taxed_citizens, total_patricians + total_plebs);
}

void finance_system::pay_monthly_wages(finance_state& f, const finance_context& ctx) {
    int monthly_wages = f.wages * ctx.labor.workers_employed / 10 / 12;
    int treasury_pay = monthly_wages;
    int grain_deben_paid = 0;

    if (!!game_features::gameplay_enhanced_historical_economy && monthly_wages > 0) {
        const int grain_budget = monthly_wages / 2;
        int price = trade_price_buy(RESOURCE_GRAIN);
        if (price < 1) {
            price = 1;
        }
        const int want_units = grain_budget / price;
        if (want_units > 0) {
            event_granaries_remove_resource ev{RESOURCE_GRAIN, want_units};
            city_granaries_remove_resource(ev);
            const int removed = want_units - ev.amount;
            if (removed > 0) {
                grain_deben_paid = removed * price;
                if (grain_deben_paid > monthly_wages) {
                    grain_deben_paid = monthly_wages;
                }
                treasury_pay = monthly_wages - grain_deben_paid;
            }
        }
    }

    f.treasury -= treasury_pay;
    f.wages_so_far += monthly_wages;
    f.wages_grain_deben_so_far += grain_deben_paid;
    f.wage_rate_paid_this_year += f.wages;
}

static void pay_monthly_interest(finance_state& f, const finance_context& ctx) {
    if (f.treasury < 0) {
        const int rate = ctx.debt_interest;
        int interest = calc_adjust_with_percentage(-f.treasury, rate) / 12;
        f.treasury -= interest;
        f.interest_so_far += interest;
    }
}

static void pay_monthly_salary(finance_state& f, const finance_context& ctx) {
    if (finance_system::is_out_of_money(f)) {
        return;
    }

    if (!building_mansion::exist_in_city()) {
        return;
    }

    int salary = ctx.kingdome.salary_amount;
    finance_system::process_request(f, ctx, {efinance_request_personal_salary, salary});

    building_mansion::update_money_values();
}

static void reset_taxes(finance_state& f, const finance_context& ctx) {
    f.last_year.income.taxes = ctx.taxes.yearly.collected_citizens + ctx.taxes.yearly.collected_nobles;
    ctx.taxes.yearly.collected_citizens = 0;
    ctx.taxes.yearly.collected_nobles = 0;
    ctx.taxes.yearly.uncollected_citizens = 0;
    ctx.taxes.yearly.uncollected_nobles = 0;

    // reset tax income in building list
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        auto house = building_get(i)->dcast_house();
        if (house && house->state() == BUILDING_STATE_VALID) {
            house->runtime_data().tax_income = 0;
        }
    }
}

void finance_system::advance_month(finance_state& f, const finance_context& ctx) {
    f.crimes_this_month = 0;
    f.gold_stolen_this_month = 0;
    collect_monthly_taxes(f, ctx);
    pay_monthly_wages(f, ctx);
    pay_monthly_interest(f, ctx);
    pay_monthly_salary(f, ctx);
}

static void copy_amounts_to_last_year(finance_state& f) {
    auto& this_year = f.this_year;
    auto& last_year = f.last_year;
    // wages
    last_year.expenses.wages = f.wages_so_far;
    f.wages_so_far = 0;
    f.wages_grain_deben_last_year = f.wages_grain_deben_so_far;
    f.wages_grain_deben_so_far = 0;
    f.wage_rate_paid_last_year = f.wage_rate_paid_this_year;
    f.wage_rate_paid_this_year = 0;

    // import/export
    last_year.income.exports = this_year.income.exports;
    this_year.income.exports = 0;
    last_year.expenses.imports = this_year.expenses.imports;
    this_year.expenses.imports = 0;

    // construction
    last_year.expenses.construction = this_year.expenses.construction;
    this_year.expenses.construction = 0;

    // interest
    last_year.expenses.interest = f.interest_so_far;
    f.interest_so_far = 0;

    // salary
    last_year.expenses.accountant_salary = this_year.expenses.accountant_salary;
    this_year.expenses.accountant_salary = 0;
    last_year.expenses.mayour_salary = this_year.expenses.mayour_salary;
    this_year.expenses.mayour_salary = 0;

    // sundries
    last_year.expenses.festivals = this_year.expenses.festivals;
    this_year.expenses.festivals = 0;
    last_year.expenses.disasters = this_year.expenses.disasters;
    this_year.expenses.disasters = 0;
    last_year.expenses.kingdome = this_year.expenses.kingdome;
    this_year.expenses.kingdome = 0;
    last_year.expenses.stolen = this_year.expenses.stolen;
    this_year.expenses.stolen = 0;

    // donations
    last_year.income.donated = this_year.income.donated;
    this_year.income.donated = 0;
}

static void pay_tribute(finance_state& f, const finance_context& ctx) {
    auto& last_year = f.last_year;
    const int population = ctx.population.current;
    int income
      = last_year.income.donated + last_year.income.taxes + last_year.income.exports + last_year.income.gold_delivered;
    int expenses = last_year.expenses.stolen + last_year.expenses.mayour_salary + last_year.expenses.accountant_salary
                   + last_year.expenses.interest + last_year.expenses.construction + last_year.expenses.wages
                   + last_year.expenses.imports + last_year.expenses.festivals + last_year.expenses.kingdome
                   + last_year.expenses.disasters;

    f.tribute_not_paid_last_year = 0;
    if (f.treasury <= 0) {
        // city is in debt
        f.tribute_not_paid_last_year = 1;
        f.tribute_not_paid_total_years++;
        last_year.expenses.tribute = 0;
    } else if (income <= expenses) {
        // city made a loss: fixed tribute based on population
        f.tribute_not_paid_total_years = 0;
        if (population > 2000)
            last_year.expenses.tribute = 200;
        else if (population > 1000)
            last_year.expenses.tribute = 100;
        else {
            last_year.expenses.tribute = 0;
        }
    } else {
        // city made a profit: tribute is max of: 25% of profit, fixed tribute based
        // on population
        f.tribute_not_paid_total_years = 0;
        if (population > 5000)
            last_year.expenses.tribute = 500;
        else if (population > 3000)
            last_year.expenses.tribute = 400;
        else if (population > 2000)
            last_year.expenses.tribute = 300;
        else if (population > 1000)
            last_year.expenses.tribute = 225;
        else if (population > 500)
            last_year.expenses.tribute = 150;
        else {
            last_year.expenses.tribute = 50;
        }
        int pct_profit = calc_adjust_with_percentage(income - expenses, 25);
        if (pct_profit > last_year.expenses.tribute)
            last_year.expenses.tribute = pct_profit;
    }

    f.treasury -= last_year.expenses.tribute;
    f.this_year.expenses.tribute = 0;

    last_year.balance = f.treasury;
    last_year.income.total = income;
    last_year.expenses.total = last_year.expenses.tribute + expenses;
}

void finance_system::advance_year(finance_state& f, const finance_context& ctx) {
    reset_taxes(f, ctx);
    copy_amounts_to_last_year(f);
    pay_tribute(f, ctx);
}

finance_state::treasury_t& finance_state::treasury_t::change(int v) {
    value += v;
    events::emit(event_finance_changed{value});
    return *this;
}
