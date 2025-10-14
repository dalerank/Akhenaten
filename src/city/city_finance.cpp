#include "city_finance.h"

#include "core/svector.h"
#include "building/building.h"
#include "building/building_house.h"
#include "building/model.h"
#include "buildings.h"
#include "city/city.h"
#include "game/game_events.h"
#include "core/calc.h"
#include "game/difficulty.h"
#include "game/tutorial.h"
#include "game/game.h"
#include "game/game_config.h"
#include "core/random.h"
#include "figure/figure.h"

#include <map>

static auto &city_data = g_city;

void city_finance_t::init() {
    wages_kingdome = 30;
    wages = 30;

    events::subscribe([this] (event_finance_donation ev) {
        treasury += ev.amount;
        this_year.income.donated += ev.amount;
    });

    events::subscribe([this] (event_finance_process_request ev) {
        process_request({ ev.type, ev.deben });
    });

    events::subscribe([this] (event_finance_change_wages ev) {
        change_wages(ev.value);
        estimate_wages();
        calculate_totals();
    });

    events::subscribe([this] (event_finance_change_tax ev) {
        tax_percentage = calc_bound(tax_percentage + ev.value, 0, 25);

        update_estimate_taxes();
        calculate_totals();
    });
}

void city_finance_t::change_wages(int amount) {
    wages += amount;
    wages = calc_bound(wages, 0, 100);
}

int city_finance_t::raise_wages_kingdome() {
    if (wages_kingdome >= 45)
        return 0;

    wages_kingdome += 1 + (random_byte_alt() & 3);
    if (wages_kingdome > 45)
        wages_kingdome = 45;

    return 1;
}

int city_finance_t::lower_wages_kingdome() {
    if (wages_kingdome <= 5)
        return 0;

    wages_kingdome -= 1 + (random_byte_alt() & 3);
    return 1;
}

bool city_finance_t::is_out_of_money() const{
    return (treasury <= -5000);
}

void city_finance_process_gold_extraction(int amount, figure *f) {
    city_data.finance.treasury += amount;

    if (building_type_any_of(*f->home(), { BUILDING_GOLD_MINE })) {
        city_data.finance.this_year.income.gold_extracted += amount;
        events::emit(event_gold_extract{ amount });
    } else if (building_type_any_of(*f->home(), { BUILDING_TAX_COLLECTOR, BUILDING_TAX_COLLECTOR_UPGRADED })) {
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
    city_data.finance.this_year.expenses.stolen += stolen;
}

void city_finance_process_construction(int cost) {
    city_data.finance.treasury -= cost;
    city_data.finance.this_year.expenses.construction += cost;
}

void city_finance_update_interest() {
    city_data.finance.this_year.expenses.interest = city_data.finance.interest_so_far;
}

void city_finance_t::calculate_totals() {
    finance_overview& this_year = city_data.finance.this_year;
    this_year.income.total = this_year.income.donated + this_year.income.taxes + this_year.income.exports
                              + this_year.income.gold_extracted;

    this_year.expenses.total = this_year.expenses.stolen + this_year.expenses.salary + this_year.expenses.interest
                                + this_year.expenses.construction + this_year.expenses.wages
                                + this_year.expenses.imports + this_year.expenses.festivals + this_year.expenses.kingdome + this_year.expenses.disasters;

    finance_overview& last_year = city_data.finance.last_year;
    last_year.income.total = last_year.income.donated + last_year.income.taxes + last_year.income.exports
                              + last_year.income.gold_extracted;

    last_year.expenses.total = last_year.expenses.stolen + last_year.expenses.salary + last_year.expenses.interest
                                + last_year.expenses.construction + last_year.expenses.wages
                                + last_year.expenses.imports + last_year.expenses.festivals + last_year.expenses.kingdome + last_year.expenses.disasters;

    last_year.net_in_out = last_year.income.total - last_year.expenses.total;
    this_year.net_in_out = this_year.income.total - this_year.expenses.total;
    this_year.balance = last_year.balance + this_year.net_in_out;

    this_year.expenses.tribute = 0;
}

void city_finance_t::estimate_wages() {
    int monthly_wages = wages * g_city.labor.workers_employed / 10 / 12;
    this_year.expenses.wages = wages_so_far;
    estimated_wages = (12 - game.simtime.month) * monthly_wages + wages_so_far;
}


void city_finance_t::process_request(finance_request_t request) {
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
        g_city.kingdome.personal_savings += request.deben;
        treasury -= request.deben;
        break;

    default:
        assert(false && "something strange");
    }
}

void city_finance_t::update_estimate_taxes() {
    auto &taxes = g_city.taxes;
    taxes.monthly.collected_citizens = 0;
    taxes.monthly.collected_nobles = 0;

    buildings_house_do([&taxes] (auto house) {
        auto &housed = house->runtime_data();
        if (!housed.tax_coverage) {
            return;
        }

        const int house_tax_multiplier = house->model().tax_multiplier;
        const int scenario_tax_rate_multiplier = g_scenario.house_tax_multiplier(house_tax_multiplier);

        if (house->is_nobles()) {
            taxes.monthly.collected_nobles += housed.population * scenario_tax_rate_multiplier;
        } else {
            taxes.monthly.collected_citizens += housed.population * scenario_tax_rate_multiplier;
        }
    });

    int monthly_patricians = calc_adjust_with_percentage<int>(taxes.monthly.collected_nobles / 2, tax_percentage);
    int monthly_plebs = calc_adjust_with_percentage<int>(taxes.monthly.collected_citizens/ 2, tax_percentage);
    int estimated_rest_of_year = (12 - game.simtime.month) * (monthly_patricians + monthly_plebs);

    this_year.income.taxes = taxes.yearly.collected_citizens + city_data.taxes.yearly.collected_nobles;
    estimated_tax_income = this_year.income.taxes + estimated_rest_of_year;

    // TODO: fix this calculation
    int uncollected_patricians = calc_adjust_with_percentage<int>(taxes.monthly.uncollected_nobles / 2, tax_percentage);
    int uncollected_plebs = calc_adjust_with_percentage<int>(taxes.monthly.uncollected_citizens / 2, tax_percentage);
    estimated_tax_uncollected = (game.simtime.month) * (uncollected_patricians + uncollected_plebs) - this_year.income.taxes;
}

void city_finance_t::collect_monthly_taxes() {
    city_data.taxes.taxed_citizens = 0;
    city_data.taxes.taxed_nobles = 0;
    city_data.taxes.untaxed_citizens = 0;
    city_data.taxes.untaxed_nobles = 0;
    city_data.taxes.monthly.uncollected_citizens = 0;
    city_data.taxes.monthly.collected_citizens = 0;
    city_data.taxes.monthly.uncollected_nobles = 0;
    city_data.taxes.monthly.collected_nobles = 0;

    for (int i = 0; i < HOUSE_LEVEL_MAX; i++) {
        city_data.population.at_level[i] = 0;
    }

    std::map<int, uint32_t> tax_collectors; 
    if (!!game_features::gameplay_change_new_tax_collection_system) {
        svector<building *, 64> buildings;
        buildings_get(buildings, BUILDING_TAX_COLLECTOR, BUILDING_TAX_COLLECTOR_UPGRADED);
        for (auto &b : buildings) {
            tax_collectors.insert({b->id, 0});
        }
    }

    buildings_house_do([&] (auto house) {
        if (!house->hsize()) {
            return;
        }

        auto &housed = house->runtime_data();
        int is_nobles = (house->house_level() >= HOUSE_COMMON_MANOR);
        int population = housed.population;
        const int scenario_tax_multiplier = g_scenario.house_tax_multiplier(house->model().tax_multiplier);
        city_data.population.at_level[house->house_level()] += population;

        const int tax = population * scenario_tax_multiplier;
        if (housed.tax_coverage) {
            if (is_nobles) {
                city_data.taxes.taxed_nobles += population;
                city_data.taxes.monthly.collected_nobles += tax;
            } else {
                city_data.taxes.taxed_citizens += population;
                city_data.taxes.monthly.collected_citizens += tax;
            }

            if (!!game_features::gameplay_change_new_tax_collection_system) {
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
    int collected_nobles = calc_adjust_with_percentage<int>(city_data.taxes.monthly.collected_nobles / tax_city_divider, city_data.finance.tax_percentage);
    int collected_citizens = calc_adjust_with_percentage<int>(city_data.taxes.monthly.collected_citizens / tax_city_divider, city_data.finance.tax_percentage);
    int collected_total = collected_nobles + collected_citizens;

    city_data.taxes.yearly.collected_nobles += collected_nobles;
    city_data.taxes.yearly.collected_citizens += collected_citizens;
    city_data.taxes.yearly.uncollected_nobles += calc_adjust_with_percentage<int>(city_data.taxes.monthly.uncollected_nobles / tax_city_divider, city_data.finance.tax_percentage);
    city_data.taxes.yearly.uncollected_citizens += calc_adjust_with_percentage<int>(city_data.taxes.monthly.uncollected_citizens / tax_city_divider, city_data.finance.tax_percentage);

    if (!!game_features::gameplay_change_new_tax_collection_system) {
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

void city_finance_t::pay_monthly_wages() {
    int montly_wages = wages * g_city.labor.workers_employed / 10 / 12;
    treasury -= montly_wages;
    wages_so_far += montly_wages;
    wage_rate_paid_this_year += montly_wages;
}

void city_finance_t::pay_monthly_interest() {
    if (treasury < 0) {
        int interest = calc_adjust_with_percentage(-treasury, 10) / 12;
        treasury -= interest;
        interest_so_far += interest;
    }
}

void city_finance_t::pay_monthly_salary() {
    if (is_out_of_money()) {
        return;
    }

    if (!city_buildings_has_mansion()) {
        return;
    }

    process_request({ efinance_request_personal_salary, g_city.kingdome.salary_amount });
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

void city_finance_t::advance_month() {
    collect_monthly_taxes();
    pay_monthly_wages();
    pay_monthly_interest();
    pay_monthly_salary();
}

void city_finance_t::copy_amounts_to_last_year() {
    // wages
    last_year.expenses.wages = wages_so_far;
    wages_so_far = 0;
    wage_rate_paid_last_year = wage_rate_paid_this_year;
    wage_rate_paid_this_year = 0;

    // import/export
    last_year.income.exports = this_year.income.exports;
    this_year.income.exports = 0;
    last_year.expenses.imports = this_year.expenses.imports;
    this_year.expenses.imports = 0;

    // construction
    last_year.expenses.construction = this_year.expenses.construction;
    this_year.expenses.construction = 0;

    // interest
    last_year.expenses.interest = interest_so_far;
    interest_so_far = 0;

    // salary
    last_year.expenses.salary = this_year.expenses.salary;
    this_year.expenses.salary = 0;

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

void city_finance_t::pay_tribute() {
    int income = last_year.income.donated + last_year.income.taxes + last_year.income.exports + last_year.income.gold_extracted;
    int expenses = last_year.expenses.stolen + last_year.expenses.salary + last_year.expenses.interest
                   + last_year.expenses.construction + last_year.expenses.wages + last_year.expenses.imports
                   + last_year.expenses.festivals + last_year.expenses.kingdome + last_year.expenses.disasters;

    tribute_not_paid_last_year = 0;
    if (treasury <= 0) {
        // city is in debt
        tribute_not_paid_last_year = 1;
        tribute_not_paid_total_years++;
        last_year.expenses.tribute = 0;
    } else if (income <= expenses) {
        // city made a loss: fixed tribute based on population
        tribute_not_paid_total_years = 0;
        if (g_city.population.current > 2000)
            last_year.expenses.tribute = 200;
        else if (g_city.population.current > 1000)
            last_year.expenses.tribute = 100;
        else {
            last_year.expenses.tribute = 0;
        }
    } else {
        // city made a profit: tribute is max of: 25% of profit, fixed tribute based on population
        tribute_not_paid_total_years = 0;
        if (g_city.population.current > 5000)
            last_year.expenses.tribute = 500;
        else if (g_city.population.current > 3000)
            last_year.expenses.tribute = 400;
        else if (g_city.population.current > 2000)
            last_year.expenses.tribute = 300;
        else if (g_city.population.current > 1000)
            last_year.expenses.tribute = 225;
        else if (g_city.population.current > 500)
            last_year.expenses.tribute = 150;
        else {
            last_year.expenses.tribute = 50;
        }
        int pct_profit = calc_adjust_with_percentage(income - expenses, 25);
        if (pct_profit > last_year.expenses.tribute)
            last_year.expenses.tribute = pct_profit;
    }

    treasury -= last_year.expenses.tribute;
    this_year.expenses.tribute = 0;

    last_year.balance = treasury;
    last_year.income.total = income;
    last_year.expenses.total = last_year.expenses.tribute + expenses;
}

void city_finance_t::advance_year() {
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

city_finance_t::treasury_t &city_finance_t::treasury_t::change(int v) {
    value += v;
    events::emit(event_finance_changed{ value });
    return *this;
}
