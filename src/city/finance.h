#pragma once

#include <cstdint>

constexpr uint32_t MAX_HOUSE_LEVELS = 20;
class figure;

struct event_gold_extract { int amount; };

int city_finance_treasury();
int city_finance_out_of_money(void);

int city_finance_tax_percentage(void);
void city_finance_change_tax_percentage(int change);
int city_finance_percentage_taxed_people(void);

int city_finance_estimated_tax_income(void);
int city_finance_estimated_tax_uncollected(void);
int city_finance_estimated_wages(void);

void city_finance_process_import(int price);
void city_finance_process_export(int price);
void city_finance_process_gold_extraction(int amount, figure *f);
void city_finance_process_cheat(void);
void city_finance_process_console(int amount);
void city_finance_process_stolen(int stolen);
void city_finance_process_donation(int amount);
void city_finance_process_requests_and_festivals(int cost);
void city_finance_process_construction(int cost);

void city_finance_update_interest(void);
void city_finance_update_salary(void);

void city_finance_calculate_totals(void);
void city_finance_estimate_wages(void);
void city_finance_estimate_taxes(void);

void city_finance_handle_month_change(void);
void city_finance_handle_year_change(void);

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
        //        int sundries;
        int tribute;
        int requests_and_festivals;
        int total;
    } expenses;

    int net_in_out;
    int balance;
};

const finance_overview* city_finance_overview_last_year(void);
const finance_overview* city_finance_overview_this_year(void);
