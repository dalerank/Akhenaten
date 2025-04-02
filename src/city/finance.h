#pragma once

#include <cstdint>

struct finance_overview {
    struct {
        int taxes;
        int exports;
        uint32_t gold_extracted;
        int donated;
        int total;
    } income;

    struct {
        int imports;
        int wages;
        int construction;
        int interest;
        int salary;
        int stolen;
        int tribute;
        int requests_and_festivals;
        int total;
    } expenses;

    int net_in_out;
    int balance;
};

struct event_finance_changed { int value; };
struct event_finance_donation { int amount; };

struct city_taxes_t {
    int32_t taxed_citizens;
    int32_t taxed_nobles;
    int32_t untaxed_citizens;
    int32_t untaxed_nobles;
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

struct city_finance_t {
    struct treasury_t {
        int value;
        treasury_t &change(int v);
        treasury_t &operator-=(int v) { return change(-v); }
        treasury_t &operator+=(int v) { return change(v); }
        treasury_t &operator=(int v) { value = 0; return change(v); }
        operator int() const { return value; }
    } treasury;
    int8_t tax_percentage;
    int32_t estimated_tax_uncollected;
    int32_t estimated_tax_income;
    int32_t estimated_wages;
    finance_overview last_year;
    finance_overview this_year;
    int32_t interest_so_far;
    int32_t salary_so_far;
    int32_t wages_so_far;
    int32_t cheated_money;
    int32_t tribute_not_paid_last_year;
    int32_t tribute_not_paid_total_years;
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
};

constexpr uint32_t MAX_HOUSE_LEVELS = 20;
class figure;

struct event_gold_extract { int amount; };

void city_finance_change_tax_percentage(int change);

int city_finance_estimated_tax_uncollected();
int city_finance_estimated_wages();

void city_finance_process_import(int price);
void city_finance_process_export(int price);
void city_finance_process_gold_extraction(int amount, figure *f);
void city_finance_process_cheat();
void city_finance_process_console(int amount);
void city_finance_process_stolen(int stolen);
void city_finance_process_requests_and_festivals(int cost);
void city_finance_process_construction(int cost);

void city_finance_update_interest(void);
void city_finance_update_salary(void);

void city_finance_calculate_totals(void);

const finance_overview* city_finance_overview_last_year();
const finance_overview* city_finance_overview_this_year();
