#include "finance.h"

#include "core/svector.h"
#include "building/building.h"
#include "building/building_house.h"
#include "building/model.h"
#include "buildings.h"
#include "city/city.h"
#include "core/calc.h"
#include "game/difficulty.h"
#include "game/tutorial.h"
#include "game/game.h"
#include "config/config.h"
#include "figure/figure.h"

#include <map>

static auto &city_data = g_city;
int city_finance_treasury() {
    return city_data.finance.treasury;
}

int city_finance_out_of_money() {
    return city_data.finance.treasury <= -5000;
}

int city_finance_tax_percentage() {
    return city_data.finance.tax_percentage;
}

void city_finance_change_tax_percentage(int change) {
    city_data.finance.tax_percentage = calc_bound(city_data.finance.tax_percentage + change, 0, 25);
}

int city_finance_percentage_taxed_people() {
    return city_data.taxes.percentage_taxed_people;
}

int city_finance_estimated_tax_income() {
    return city_data.finance.estimated_tax_income;
}

int city_finance_estimated_tax_uncollected(void) {
    return city_data.finance.estimated_tax_uncollected;
}

int city_finance_estimated_wages(void) {
    return city_data.finance.estimated_wages;
}

void city_finance_process_import(int price) {
    city_data.finance.treasury -= price;
    city_data.finance.this_year.expenses.imports += price;
}

void city_finance_process_export(int price) {
    city_data.finance.treasury += price;
    city_data.finance.this_year.income.exports += price;
}

void city_finance_process_gold_extraction(int amount, figure *f) {
    city_data.finance.treasury += amount;

    if (building_type_any_of(*f->home(), BUILDING_GOLD_MINE)) {
        city_data.finance.this_year.income.gold_extracted += amount;

        if (city_data.finance.this_year.income.gold_extracted >= 500) {
            tutorial_on_gold_extracted();
        }
    } else if (building_type_any_of(*f->home(), BUILDING_TAX_COLLECTOR, BUILDING_TAX_COLLECTOR_UPGRADED)) {
        city_data.finance.this_year.income.taxes += amount;
    }
}

void city_finance_process_cheat() {
    if (city_data.finance.treasury < 5000) {
        city_data.finance.treasury += 1000;
        city_data.finance.cheated_money += 1000;
    }
}

void city_finance_process_console(int amount) {
    city_data.finance.treasury += amount;
    city_data.finance.cheated_money += amount;
}

void city_finance_process_stolen(int stolen) {
    city_data.finance.treasury -= stolen;
    city_data.finance.stolen_this_year += stolen;
    city_data.finance.this_year.expenses.stolen += stolen;
}

void city_finance_process_donation(int amount) {
    city_data.finance.treasury += amount;
    city_data.finance.this_year.income.donated += amount;
}

void city_finance_process_requests_and_festivals(int cost) {
    city_data.finance.treasury -= cost;
    city_data.finance.this_year.expenses.requests_and_festivals += cost;
}

void city_finance_process_construction(int cost) {
    city_data.finance.treasury -= cost;
    city_data.finance.this_year.expenses.construction += cost;
}

void city_finance_update_interest() {
    city_data.finance.this_year.expenses.interest = city_data.finance.interest_so_far;
}

void city_finance_update_salary() {
    city_data.finance.this_year.expenses.salary = city_data.finance.salary_so_far;
}

void city_finance_calculate_totals() {
    finance_overview* this_year = &city_data.finance.this_year;
    this_year->income.total = this_year->income.donated + this_year->income.taxes + this_year->income.exports
                              + this_year->income.gold_extracted;

    this_year->expenses.total = this_year->expenses.stolen + this_year->expenses.salary + this_year->expenses.interest
                                + this_year->expenses.construction + this_year->expenses.wages
                                + this_year->expenses.imports + this_year->expenses.requests_and_festivals;

    finance_overview* last_year = &city_data.finance.last_year;
    last_year->income.total = last_year->income.donated + last_year->income.taxes + last_year->income.exports
                              + last_year->income.gold_extracted;

    last_year->expenses.total = last_year->expenses.stolen + last_year->expenses.salary + last_year->expenses.interest
                                + last_year->expenses.construction + last_year->expenses.wages
                                + last_year->expenses.imports + last_year->expenses.requests_and_festivals;

    last_year->net_in_out = last_year->income.total - last_year->expenses.total;
    this_year->net_in_out = this_year->income.total - this_year->expenses.total;
    this_year->balance = last_year->balance + this_year->net_in_out;

    this_year->expenses.tribute = 0;
}

void city_finance_estimate_wages() {
    int monthly_wages = city_data.labor.wages * city_data.labor.workers_employed / 10 / 12;
    city_data.finance.this_year.expenses.wages = city_data.finance.wages_so_far;
    city_data.finance.estimated_wages = (12 - game.simtime.month) * monthly_wages + city_data.finance.wages_so_far;
}

void city_finance_estimate_taxes() {
    city_data.taxes.monthly.collected_citizens = 0;
    city_data.taxes.monthly.collected_nobles = 0;

    buildings_valid_do([] (building &b) {
        auto house = b.dcast_house();
        if (!house) {
            return;
        }

        auto &housed = house->runtime_data();
        if (!housed.tax_coverage) {
            return;
        }

        int is_nobles = (housed.level >= HOUSE_COMMON_MANOR);
        int tax_multiplier = model_get_house(housed.level)->tax_multiplier;
        int level_tax_rate_multiplier = difficulty_adjust_money(tax_multiplier);

        if (is_nobles) {
            city_data.taxes.monthly.collected_nobles += housed.population * level_tax_rate_multiplier;
        } else {
            city_data.taxes.monthly.collected_citizens += housed.population * level_tax_rate_multiplier;
        }
    });

    int monthly_patricians = calc_adjust_with_percentage(city_data.taxes.monthly.collected_nobles / 2, city_data.finance.tax_percentage);
    int monthly_plebs = calc_adjust_with_percentage(city_data.taxes.monthly.collected_citizens/ 2, city_data.finance.tax_percentage);
    int estimated_rest_of_year = (12 - game.simtime.month) * (monthly_patricians + monthly_plebs);

    city_data.finance.this_year.income.taxes = city_data.taxes.yearly.collected_citizens + city_data.taxes.yearly.collected_nobles;
    city_data.finance.estimated_tax_income = city_data.finance.this_year.income.taxes + estimated_rest_of_year;

    // TODO: fix this calculation
    int uncollected_patricians = calc_adjust_with_percentage(city_data.taxes.monthly.uncollected_nobles / 2, city_data.finance.tax_percentage);
    int uncollected_plebs = calc_adjust_with_percentage(city_data.taxes.monthly.uncollected_citizens / 2, city_data.finance.tax_percentage);
    city_data.finance.estimated_tax_uncollected = (game.simtime.month) * (uncollected_patricians + uncollected_plebs) - city_data.finance.this_year.income.taxes;
}

static void city_finance_collect_monthly_taxes() {
    city_data.taxes.taxed_citizens = 0;
    city_data.taxes.taxed_nobles = 0;
    city_data.taxes.untaxed_citizens = 0;
    city_data.taxes.untaxed_nobles = 0;
    city_data.taxes.monthly.uncollected_citizens = 0;
    city_data.taxes.monthly.collected_citizens = 0;
    city_data.taxes.monthly.uncollected_nobles = 0;
    city_data.taxes.monthly.collected_nobles = 0;

    for (int i = 0; i < MAX_HOUSE_LEVELS; i++) {
        city_data.population.at_level[i] = 0;
    }

    std::map<int, uint32_t> tax_collectors; 
    if (config_get(CONFIG_GP_CH_NEW_TAX_COLLECTION_SYSTEM)) {
        svector<building *, 64> buildings;
        buildings_get(buildings, BUILDING_TAX_COLLECTOR, BUILDING_TAX_COLLECTOR_UPGRADED);
        for (auto &b : buildings) {
            tax_collectors.insert({b->id, 0});
        }
    }

    buildings_valid_do([&] (building &b) {
        auto house = b.dcast_house();

        if (!house || !house->hsize()) {
            return;
        }

        auto &housed = house->runtime_data();
        int is_nobles = (housed.level >= HOUSE_COMMON_MANOR);
        int population = housed.population;
        int trm = difficulty_adjust_money(model_get_house(house->house_level())->tax_multiplier);
        city_data.population.at_level[housed.level] += population;

        int tax = population * trm;
        if (housed.tax_coverage) {
            if (is_nobles) {
                city_data.taxes.taxed_nobles += population;
                city_data.taxes.monthly.collected_nobles += tax;
            } else {
                city_data.taxes.taxed_citizens += population;
                city_data.taxes.monthly.collected_citizens += tax;
            }

            if (config_get(CONFIG_GP_CH_NEW_TAX_COLLECTION_SYSTEM)) {
                tax_collectors[housed.tax_collector_id] += tax;
                housed.tax_collector_id = 0;
            }

            housed.tax_income_or_storage += tax;
        } else {
            if (is_nobles) {
                city_data.taxes.untaxed_nobles += population;
                city_data.taxes.monthly.uncollected_nobles += tax;
            } else {
                city_data.taxes.untaxed_citizens += population;
                city_data.taxes.monthly.uncollected_citizens += tax;
            }
        }
    });

    int tax_city_divider = 2;
    int collected_nobles = calc_adjust_with_percentage(city_data.taxes.monthly.collected_nobles / tax_city_divider, city_data.finance.tax_percentage);
    int collected_citizens = calc_adjust_with_percentage(city_data.taxes.monthly.collected_citizens / tax_city_divider, city_data.finance.tax_percentage);
    int collected_total = collected_nobles + collected_citizens;

    city_data.taxes.yearly.collected_nobles += collected_nobles;
    city_data.taxes.yearly.collected_citizens += collected_citizens;
    city_data.taxes.yearly.uncollected_nobles += calc_adjust_with_percentage(city_data.taxes.monthly.uncollected_nobles / tax_city_divider, city_data.finance.tax_percentage);
    city_data.taxes.yearly.uncollected_citizens += calc_adjust_with_percentage(city_data.taxes.monthly.uncollected_citizens / tax_city_divider, city_data.finance.tax_percentage);

    if (config_get(CONFIG_GP_CH_NEW_TAX_COLLECTION_SYSTEM)) {
        for (auto &it : tax_collectors) {
            building *b = building_get(it.first);
            b->deben_storage += calc_adjust_with_percentage<uint32_t>(it.second / tax_city_divider, city_data.finance.tax_percentage);
        }
    } else {
        city_data.finance.treasury += collected_total;
    }

    int total_patricians = city_data.taxes.taxed_nobles + city_data.taxes.untaxed_nobles;
    int total_plebs = city_data.taxes.taxed_citizens + city_data.taxes.untaxed_citizens;
    city_data.taxes.percentage_taxed_nobles = calc_percentage(city_data.taxes.taxed_nobles, total_patricians);
    city_data.taxes.percentage_taxed_citizens = calc_percentage(city_data.taxes.taxed_citizens, total_plebs);
    city_data.taxes.percentage_taxed_people = calc_percentage(city_data.taxes.taxed_nobles + city_data.taxes.taxed_citizens, total_patricians + total_plebs);
}

static void pay_monthly_wages() {
    int wages = city_data.labor.wages * city_data.labor.workers_employed / 10 / 12;
    city_data.finance.treasury -= wages;
    city_data.finance.wages_so_far += wages;
    city_data.finance.wage_rate_paid_this_year += city_data.labor.wages;
}

static void pay_monthly_interest() {
    if (city_data.finance.treasury < 0) {
        int interest = calc_adjust_with_percentage(-city_data.finance.treasury, 10) / 12;
        city_data.finance.treasury -= interest;
        city_data.finance.interest_so_far += interest;
    }
}

static void pay_monthly_salary() {
    if (!city_finance_out_of_money() && city_buildings_has_mansion()) {
        city_data.finance.salary_so_far += city_data.kingdome.salary_amount;
        city_data.kingdome.personal_savings += city_data.kingdome.salary_amount;
        city_data.finance.treasury -= city_data.kingdome.salary_amount;
    }
}

static void reset_taxes() {
    city_data.finance.last_year.income.taxes = city_data.taxes.yearly.collected_citizens + city_data.taxes.yearly.collected_nobles;
    city_data.taxes.yearly.collected_citizens = 0;
    city_data.taxes.yearly.collected_nobles = 0;
    city_data.taxes.yearly.uncollected_citizens = 0;
    city_data.taxes.yearly.uncollected_citizens = 0;

    // reset tax income in building list
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        auto house = building_get(i)->dcast_house();
        if (house && house->state() == BUILDING_STATE_VALID) {
            house->runtime_data().tax_income_or_storage = 0;
        }
    }
}

void city_finance_handle_month_change() {
    city_finance_collect_monthly_taxes();
    pay_monthly_wages();
    pay_monthly_interest();
    pay_monthly_salary();
}

static void copy_amounts_to_last_year() {
    finance_overview* last_year = &city_data.finance.last_year;
    finance_overview* this_year = &city_data.finance.this_year;

    // wages
    last_year->expenses.wages = city_data.finance.wages_so_far;
    city_data.finance.wages_so_far = 0;
    city_data.finance.wage_rate_paid_last_year = city_data.finance.wage_rate_paid_this_year;
    city_data.finance.wage_rate_paid_this_year = 0;

    // import/export
    last_year->income.exports = this_year->income.exports;
    this_year->income.exports = 0;
    last_year->expenses.imports = this_year->expenses.imports;
    this_year->expenses.imports = 0;

    // construction
    last_year->expenses.construction = this_year->expenses.construction;
    this_year->expenses.construction = 0;

    // interest
    last_year->expenses.interest = city_data.finance.interest_so_far;
    city_data.finance.interest_so_far = 0;

    // salary
    city_data.finance.last_year.expenses.salary = city_data.finance.salary_so_far;
    city_data.finance.salary_so_far = 0;

    // sundries
    last_year->expenses.requests_and_festivals = this_year->expenses.requests_and_festivals;
    this_year->expenses.requests_and_festivals = 0;
    last_year->expenses.stolen = this_year->expenses.stolen;
    this_year->expenses.stolen = 0;
    city_data.finance.stolen_last_year = city_data.finance.stolen_this_year;
    city_data.finance.stolen_this_year = 0;

    // donations
    last_year->income.donated = this_year->income.donated;
    this_year->income.donated = 0;
}

static void pay_tribute() {
    finance_overview* last_year = &city_data.finance.last_year;

    int income = last_year->income.donated + last_year->income.taxes + last_year->income.exports + last_year->income.gold_extracted;
    int expenses = last_year->expenses.stolen + last_year->expenses.salary + last_year->expenses.interest
                   + last_year->expenses.construction + last_year->expenses.wages + last_year->expenses.imports
                   + last_year->expenses.requests_and_festivals;

    city_data.finance.tribute_not_paid_last_year = 0;
    if (city_data.finance.treasury <= 0) {
        // city is in debt
        city_data.finance.tribute_not_paid_last_year = 1;
        city_data.finance.tribute_not_paid_total_years++;
        last_year->expenses.tribute = 0;
    } else if (income <= expenses) {
        // city made a loss: fixed tribute based on population
        city_data.finance.tribute_not_paid_total_years = 0;
        if (city_data.population.population > 2000)
            last_year->expenses.tribute = 200;
        else if (city_data.population.population > 1000)
            last_year->expenses.tribute = 100;
        else {
            last_year->expenses.tribute = 0;
        }
    } else {
        // city made a profit: tribute is max of: 25% of profit, fixed tribute based on population
        city_data.finance.tribute_not_paid_total_years = 0;
        if (city_data.population.population > 5000)
            last_year->expenses.tribute = 500;
        else if (city_data.population.population > 3000)
            last_year->expenses.tribute = 400;
        else if (city_data.population.population > 2000)
            last_year->expenses.tribute = 300;
        else if (city_data.population.population > 1000)
            last_year->expenses.tribute = 225;
        else if (city_data.population.population > 500)
            last_year->expenses.tribute = 150;
        else {
            last_year->expenses.tribute = 50;
        }
        int pct_profit = calc_adjust_with_percentage(income - expenses, 25);
        if (pct_profit > last_year->expenses.tribute)
            last_year->expenses.tribute = pct_profit;
    }

    city_data.finance.treasury -= last_year->expenses.tribute;
    city_data.finance.this_year.expenses.tribute = 0;

    last_year->balance = city_data.finance.treasury;
    last_year->income.total = income;
    last_year->expenses.total = last_year->expenses.tribute + expenses;
}

void city_finance_handle_year_change() {
    reset_taxes();
    copy_amounts_to_last_year();
    pay_tribute();
}

const finance_overview* city_finance_overview_last_year() {
    return &city_data.finance.last_year;
}

const finance_overview* city_finance_overview_this_year() {
    return &city_data.finance.this_year;
}
