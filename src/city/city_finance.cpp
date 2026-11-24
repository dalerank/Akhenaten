#include "city_finance.h"
#include "city/city.h"
#include "game/sim_schedule.h"

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

using e_finance_request_type_tokens_t = token_holder<e_finance_request_type, efinance_request_none, efinance_request_max>;
const e_finance_request_type_tokens_t ANK_CONFIG_ENUM(e_finance_request_type_tokens);

palace_treasury_shares_t ANK_VARIABLE(palace_treasury_shares);

void finance_system::init() {
    _state.wages_kingdome = 30;
    _state.wages = 30;
}

void finance_system::subscribe_events(finance_system (*make)()) {
    events::subscribe([make](event_finance_donation ev) {
        finance_system finance = make();
        finance._state.treasury += ev.amount;
        finance._state.this_year.income.donated += ev.amount;
    });

    events::subscribe([make](event_finance_request ev) { make().process_request({ev.type, ev.deben}); });

    events::subscribe([make](event_finance_change_wages ev) {
        finance_system finance = make();
        finance.change_wages(ev.value);
        finance.estimate_wages();
        finance.calculate_totals();
    });

    // HE2 runtime-only counters (not in save): clear after load / new mission.
    events::subscribe([make](event_level_post_load) {
        finance_system finance = make();
        finance._state.wages_grain_deben_so_far = 0;
        finance._state.wages_grain_deben_last_year = 0;
    });
}

void finance_system::change_wages(int amount) {
    _state.wages += amount;
    _state.wages = calc_bound(_state.wages, 0, 100);
}

int finance_system::raise_wages_kingdome() {
    if (_state.wages_kingdome >= 45)
        return 0;

    _state.wages_kingdome += 1 + (random_byte_alt() & 3);
    if (_state.wages_kingdome > 45)
        _state.wages_kingdome = 45;

    return 1;
}

int finance_system::lower_wages_kingdome() {
    if (_state.wages_kingdome <= 5)
        return 0;

    _state.wages_kingdome -= 1 + (random_byte_alt() & 3);
    return 1;
}

bool finance_system::is_out_of_money() const {
    return (_state.treasury <= -5000);
}

void finance_system::process_stolen(int stolen) {
    _state.treasury -= stolen;
    _state.this_year.expenses.stolen += stolen;
    _state.crimes_this_month++;
    _state.gold_stolen_this_month += stolen;
}

void finance_system::update_interest() {
    _state.this_year.expenses.interest = _state.interest_so_far;
}

void finance_system::calculate_totals() {
    auto& this_year = _state.this_year;
    auto& last_year = _state.last_year;
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

void finance_system::estimate_wages() {
    int monthly_wages = _state.wages * _ctx.labor.workers_employed / 10 / 12;
    _state.this_year.expenses.wages = _state.wages_so_far;
    _state.estimated_wages = (12 - _ctx.month) * monthly_wages + _state.wages_so_far;
}

void finance_system::process_request(event_finance_request request) {
    auto& treasury = _state.treasury;
    auto& this_year = _state.this_year;
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
        _ctx.kingdome.personal_savings += request.deben;
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

void finance_system::pay_monthly_wages() {
    int monthly_wages = _state.wages * _ctx.labor.workers_employed / 10 / 12;
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

    _state.treasury -= treasury_pay;
    _state.wages_so_far += monthly_wages;
    _state.wages_grain_deben_so_far += grain_deben_paid;
    _state.wage_rate_paid_this_year += _state.wages;
}

void finance_system::pay_monthly_interest() {
    if (_state.treasury < 0) {
        const int rate = _ctx.debt_interest;
        int interest = calc_adjust_with_percentage(-_state.treasury, rate) / 12;
        _state.treasury -= interest;
        _state.interest_so_far += interest;
    }
}

void finance_system::pay_monthly_salary() {
    if (is_out_of_money()) {
        return;
    }

    if (!building_mansion::exist_in_city()) {
        return;
    }

    int salary = _ctx.kingdome.salary_amount;
    process_request({efinance_request_personal_salary, salary});

    building_mansion::update_money_values();
}

void finance_system::advance_month() {
    _state.crimes_this_month = 0;
    _state.gold_stolen_this_month = 0;
    pay_monthly_wages();
    pay_monthly_interest();
    pay_monthly_salary();
}

void finance_system::copy_amounts_to_last_year() {
    auto& this_year = _state.this_year;
    auto& last_year = _state.last_year;
    // wages
    last_year.expenses.wages = _state.wages_so_far;
    _state.wages_so_far = 0;
    _state.wages_grain_deben_last_year = _state.wages_grain_deben_so_far;
    _state.wages_grain_deben_so_far = 0;
    _state.wage_rate_paid_last_year = _state.wage_rate_paid_this_year;
    _state.wage_rate_paid_this_year = 0;

    // import/export
    last_year.income.exports = this_year.income.exports;
    this_year.income.exports = 0;
    last_year.expenses.imports = this_year.expenses.imports;
    this_year.expenses.imports = 0;

    // construction
    last_year.expenses.construction = this_year.expenses.construction;
    this_year.expenses.construction = 0;

    // interest
    last_year.expenses.interest = _state.interest_so_far;
    _state.interest_so_far = 0;

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

    last_year.income.gold_delivered = this_year.income.gold_delivered;
    this_year.income.gold_delivered = 0;
}

void finance_system::pay_tribute() {
    auto& last_year = _state.last_year;
    const int population = _ctx.population.current;
    int income
      = last_year.income.donated + last_year.income.taxes + last_year.income.exports + last_year.income.gold_delivered;
    int expenses = last_year.expenses.stolen + last_year.expenses.mayour_salary + last_year.expenses.accountant_salary
                   + last_year.expenses.interest + last_year.expenses.construction + last_year.expenses.wages
                   + last_year.expenses.imports + last_year.expenses.festivals + last_year.expenses.kingdome
                   + last_year.expenses.disasters;

    _state.tribute_not_paid_last_year = 0;
    if (_state.treasury <= 0) {
        // city is in debt
        _state.tribute_not_paid_last_year = 1;
        _state.tribute_not_paid_total_years++;
        last_year.expenses.tribute = 0;
    } else if (income <= expenses) {
        // city made a loss: fixed tribute based on population
        _state.tribute_not_paid_total_years = 0;
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
        _state.tribute_not_paid_total_years = 0;
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

    _state.treasury -= last_year.expenses.tribute;
    _state.this_year.expenses.tribute = 0;

    last_year.balance = _state.treasury;
    last_year.income.total = income;
    last_year.expenses.total = last_year.expenses.tribute + expenses;
}

void finance_system::advance_year() {
    copy_amounts_to_last_year();
    pay_tribute();
}

finance_state::treasury_t& finance_state::treasury_t::change(int v) {
    value += v;
    events::emit(event_finance_changed{value});
    return *this;
}

ANK_SIM_STEP(finance_month, SIM_PHASE_MONTH_CITY, -1, 50, SIM_AREA_FINANCE) {
    g_city.finance_sys().advance_month();
}

ANK_SIM_STEP(finance_year, SIM_PHASE_YEAR, -1, 60, SIM_AREA_FINANCE) {
    g_city.finance_sys().advance_year();
}
