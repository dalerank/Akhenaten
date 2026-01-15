#pragma once

#include <cstdint>

#include "core/archive.h"

enum e_finance_request_type {
    efinance_request_none = 0,
    efinance_request_festival,
    efinance_request_kigdome,
    efinance_request_disasters,
    efinance_request_import,
    efinance_request_export,
    efinance_request_personal_salary,
    efinance_request_gold_delivered,
    efinance_request_tax_collected,
};

struct event_finance_changed { int value; };
struct event_finance_donation { int amount; };

struct event_finance_change_wages { int value; };
struct event_finance_change_tax { int value; };
struct event_finance_request { e_finance_request_type type; uint32_t deben; };

enum e_finance_value {
    e_finance_value_gold_delivered = 0,

    e_finance_value_max
};

struct finance_overview {
    struct income_t {
        int taxes;
        int exports;
        uint16_t gold_delivered;
        int donated;
        int total;
    } income;

    struct expenses_t {
        int imports;
        int wages;
        uint16_t construction;
        uint16_t interest;
        uint16_t accountant_salary;
        uint16_t stolen;
        int tribute;
        uint16_t festivals;
        uint16_t kingdome;
        uint16_t disasters;
        uint16_t mayour_salary;
        int total;
    } expenses;

    int net_in_out;
    int balance;
};
ANK_CONFIG_PROPERTY(finance_overview::income_t,
    taxes, exports, donated, gold_delivered)
    
ANK_CONFIG_PROPERTY(finance_overview::expenses_t,
    imports, wages, construction, interest, accountant_salary, stolen, tribute, festivals, kingdome, disasters, mayour_salary, total)

struct city_taxes_t {
    int32_t taxed_citizens;
    int32_t taxed_nobles;
    int32_t untaxed_citizens;
    int32_t untaxed_nobles;
    int32_t estimated_uncollected;
    int32_t estimated_income;
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
ANK_CONFIG_PROPERTY(city_taxes_t,
    percentage_taxed_people, estimated_uncollected, estimated_income)

struct city_finance_t {
    struct treasury_t {
        int value;
        treasury_t &change(int v);
        treasury_t &operator-=(int v) { return change(-v); }
        treasury_t &operator+=(int v) { return change(v); }
        treasury_t &operator=(int v) { value = 0; return change(v); }
        operator int() const { return value; }
    } treasury;
    int8_t wages;
    int8_t wages_kingdome;
    int8_t tax_percentage;
    int32_t estimated_wages;
    finance_overview last_year;
    finance_overview this_year;
    int32_t interest_so_far;
    int32_t wages_so_far;
    int32_t cheated_money;
    bool tribute_not_paid_last_year;
    uint8_t tribute_not_paid_total_years;
    int32_t wage_rate_paid_this_year;
    int32_t wage_rate_paid_last_year;

    void init();
    bool is_out_of_money() const;
    void update_estimate_taxes();
    void estimate_wages();
    void collect_monthly_taxes();
    void advance_month();
    void pay_monthly_wages();
    void pay_monthly_interest();
    void pay_monthly_salary();
    void copy_amounts_to_last_year();
    void pay_tribute();
    void advance_year();
    void change_wages(int amount);
    int raise_wages_kingdome();
    int lower_wages_kingdome();
    void process_stolen(int stolen);
    void process_construction(int cost);
    void update_interest();
    void change_tax(int value);

    void process_request(event_finance_request request);
    void calculate_totals();
};
ANK_CONFIG_PROPERTY(city_finance_t,
    treasury, tax_percentage)