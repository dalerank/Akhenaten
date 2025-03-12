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

    bool is_out_of_money() const;
    void update_estimate_taxes();
    void estimate_wages();
};

constexpr uint32_t MAX_HOUSE_LEVELS = 20;
class figure;

struct event_gold_extract { int amount; };

void city_finance_change_tax_percentage(int change);
int city_finance_percentage_taxed_people();

int city_finance_estimated_tax_income();
int city_finance_estimated_tax_uncollected();
int city_finance_estimated_wages();

void city_finance_process_import(int price);
void city_finance_process_export(int price);
void city_finance_process_gold_extraction(int amount, figure *f);
void city_finance_process_cheat();
void city_finance_process_console(int amount);
void city_finance_process_stolen(int stolen);
void city_finance_process_donation(int amount);
void city_finance_process_requests_and_festivals(int cost);
void city_finance_process_construction(int cost);

void city_finance_update_interest(void);
void city_finance_update_salary(void);

void city_finance_calculate_totals(void);

void city_finance_handle_month_change(void);
void city_finance_handle_year_change(void);

const finance_overview* city_finance_overview_last_year();
const finance_overview* city_finance_overview_this_year();
