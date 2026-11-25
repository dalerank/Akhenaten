#include "city_finance.h"
#include "io/gamestate/save_versions.h"
#include "io/chunk_serializer.h"
#include "core/xvalue.h"
#include "city/city_finance_chunks.h"
#include "game/simulation.h"
#include "core/app_module.h"
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

void city_finance_t::init() {
    wages_kingdome = 30;
    wages = 30;
}

void city_finance_t::subscribe_events() {
    events::subscribe([](event_finance_donation ev) {
        auto& finance = city_finance();
        finance.treasury += ev.amount;
        finance.this_year.income.donated += ev.amount;
    });

    events::subscribe([](event_finance_request ev) { city_finance().process_request({ev.type, ev.deben}); });

    events::subscribe([](event_finance_change_wages ev) {
        auto& finance = city_finance();
        finance.change_wages(ev.value);
        finance.estimate_wages();
        finance.calculate_totals();
    });

    // HE2 runtime-only counters (not in save): clear after load / new mission.
    events::subscribe([](event_level_post_load) {
        auto& finance = city_finance();
        finance.wages_grain_deben_so_far = 0;
        finance.wages_grain_deben_last_year = 0;
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

bool city_finance_t::is_out_of_money() const {
    return (treasury <= -5000);
}

void city_finance_t::process_stolen(int stolen) {
    treasury -= stolen;
    this_year.expenses.stolen += stolen;
    crimes_this_month++;
    gold_stolen_this_month += stolen;
}

void city_finance_t::update_interest() {
    this_year.expenses.interest = interest_so_far;
}

void city_finance_t::calculate_totals() {
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

void city_finance_t::estimate_wages() {
    int monthly_wages = wages * city_labor().workers_employed / 10 / 12;
    this_year.expenses.wages = wages_so_far;
    estimated_wages = (12 - g_simulation.simtime.month) * monthly_wages + wages_so_far;
}

void city_finance_t::process_request(event_finance_request request) {
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

void city_finance_t::pay_monthly_wages() {
    int monthly_wages = wages * city_labor().workers_employed / 10 / 12;
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

    treasury -= treasury_pay;
    wages_so_far += monthly_wages;
    wages_grain_deben_so_far += grain_deben_paid;
    wage_rate_paid_this_year += wages;
}

void city_finance_t::pay_monthly_interest() {
    if (treasury < 0) {
        const int rate = g_scenario.debt_interest();
        int interest = calc_adjust_with_percentage(-treasury, rate) / 12;
        treasury -= interest;
        interest_so_far += interest;
    }
}

void city_finance_t::pay_monthly_salary() {
    if (is_out_of_money()) {
        return;
    }

    if (!building_mansion::exist_in_city()) {
        return;
    }

    int salary = g_city.kingdome.salary_amount;
    process_request({efinance_request_personal_salary, salary});

    building_mansion::update_money_values();
}

void city_finance_t::advance_month() {
    crimes_this_month = 0;
    gold_stolen_this_month = 0;
    pay_monthly_wages();
    pay_monthly_interest();
    pay_monthly_salary();
}

void city_finance_t::copy_amounts_to_last_year() {
    // wages
    last_year.expenses.wages = wages_so_far;
    wages_so_far = 0;
    wages_grain_deben_last_year = wages_grain_deben_so_far;
    wages_grain_deben_so_far = 0;
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

void city_finance_t::pay_tribute() {
    const int population = city_population().current;
    int income
      = last_year.income.donated + last_year.income.taxes + last_year.income.exports + last_year.income.gold_delivered;
    int expenses = last_year.expenses.stolen + last_year.expenses.mayour_salary + last_year.expenses.accountant_salary
                   + last_year.expenses.interest + last_year.expenses.construction + last_year.expenses.wages
                   + last_year.expenses.imports + last_year.expenses.festivals + last_year.expenses.kingdome
                   + last_year.expenses.disasters;

    tribute_not_paid_last_year = 0;
    if (treasury <= 0) {
        // city is in debt
        tribute_not_paid_last_year = 1;
        tribute_not_paid_total_years++;
        last_year.expenses.tribute = 0;
    } else if (income <= expenses) {
        // city made a loss: fixed tribute based on population
        tribute_not_paid_total_years = 0;
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
        tribute_not_paid_total_years = 0;
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

    treasury -= last_year.expenses.tribute;
    this_year.expenses.tribute = 0;

    last_year.balance = treasury;
    last_year.income.total = income;
    last_year.expenses.total = last_year.expenses.tribute + expenses;
}

void city_finance_t::advance_year() {
    copy_amounts_to_last_year();
    pay_tribute();
}

city_finance_t::treasury_t& city_finance_t::treasury_t::change(int v) {
    value += v;
    events::emit(event_finance_changed{value});
    return *this;
}

city_finance_t& city_finance() {
    return xvalue<city_finance_t>::ref();
}

void city_finance_t::reset() {
    *this = {};
}

class finance_sim_system : public sim_system {
public:
    const char* name() const override { return "finance"; }
    void on_reset() override { city_finance().reset(); }
    void push_save_sections(int file_version) override {
        if (file_version >= save_version_city_sections) {
            g_chunk_io.push_chunk<city_finance_chunk>(city_finance_chunk::size, false);
        }
    }
    void register_steps(sim_schedule_t& schedule) override {
        schedule.add({sim_step_finance_month, SIM_PHASE_MONTH_CITY, [](int) { city_finance().advance_month(); }});
        schedule.add({sim_step_finance_year, SIM_PHASE_YEAR, [](int) { city_finance().advance_year(); }});
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_finance_system) {
    static finance_sim_system system;
    g_simulation.register_system(&system);
}
