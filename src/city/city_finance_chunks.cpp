#include "city/city_finance_chunks.h"
#include "city/city_taxes.h"

#include "city/city_finance.h"
#include "io/io_buffer.h"

void city_finance_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& finance = city_finance();
    iob->bind(BIND_SIGNATURE_INT8, &city_taxes().tax_percentage);
    iob->bind(BIND_SIGNATURE_INT32, &finance.treasury.value);
    iob->bind(BIND_SIGNATURE_INT8, &finance.wages);
    iob->bind(BIND_SIGNATURE_INT8, &finance.wages_kingdome);
    iob->bind(BIND_SIGNATURE_INT32, &finance.this_year.income.taxes);
    iob->bind(BIND_SIGNATURE_INT32, &finance.last_year.income.taxes);
    iob->bind(BIND_SIGNATURE_UINT16, &finance.this_year.income.exports);
    iob->bind(BIND_SIGNATURE_UINT16, &finance.last_year.income.exports);
    iob->bind(BIND_SIGNATURE_UINT16, &finance.this_year.expenses.imports);
    iob->bind(BIND_SIGNATURE_UINT16, &finance.last_year.expenses.imports);
    iob->bind(BIND_SIGNATURE_INT16, &finance.interest_so_far);
    iob->bind(BIND_SIGNATURE_UINT16, &finance.last_year.expenses.interest);
    iob->bind(BIND_SIGNATURE_UINT16, &finance.this_year.expenses.interest);
    iob->bind(BIND_SIGNATURE_UINT16, &finance.last_year.expenses.stolen);
    iob->bind(BIND_SIGNATURE_UINT16, &finance.this_year.expenses.stolen);
    iob->bind(BIND_SIGNATURE_UINT16, &finance.last_year.expenses.construction);
    iob->bind(BIND_SIGNATURE_UINT16, &finance.this_year.expenses.construction);
    iob->bind(BIND_SIGNATURE_UINT16, &finance.last_year.expenses.accountant_salary);
    iob->bind(BIND_SIGNATURE_UINT16, &finance.this_year.expenses.accountant_salary);
    iob->bind_u16(finance.this_year.expenses.mayour_salary);
    iob->bind(BIND_SIGNATURE_INT32, &finance.last_year.income.total);
    iob->bind(BIND_SIGNATURE_INT32, &finance.this_year.income.total);
    iob->bind(BIND_SIGNATURE_INT32, &finance.last_year.expenses.total);
    iob->bind(BIND_SIGNATURE_INT32, &finance.this_year.expenses.total);
    iob->bind(BIND_SIGNATURE_INT32, &finance.last_year.net_in_out);
    iob->bind(BIND_SIGNATURE_INT32, &finance.this_year.net_in_out);
    iob->bind(BIND_SIGNATURE_INT32, &finance.last_year.balance);
    iob->bind(BIND_SIGNATURE_INT32, &finance.this_year.balance);
    iob->bind(BIND_SIGNATURE_INT32, &finance.cheated_money);
    iob->bind(BIND_SIGNATURE_UINT16, &finance.last_year.expenses.festivals);
    iob->bind(BIND_SIGNATURE_UINT16, &finance.this_year.expenses.festivals);
    iob->bind(BIND_SIGNATURE_UINT16, &finance.last_year.expenses.kingdome);
    iob->bind(BIND_SIGNATURE_UINT16, &finance.this_year.expenses.kingdome);
    iob->bind(BIND_SIGNATURE_UINT16, &finance.this_year.expenses.tribute);
    iob->bind(BIND_SIGNATURE_UINT16, &finance.last_year.expenses.tribute);
    iob->bind(BIND_SIGNATURE_INT32, &finance.wages_so_far);
    iob->bind(BIND_SIGNATURE_UINT16, &finance.this_year.expenses.wages);
    iob->bind(BIND_SIGNATURE_UINT16, &finance.last_year.expenses.wages);
    iob->bind(BIND_SIGNATURE_UINT16, &finance.this_year.income.gold_delivered);
    iob->bind(BIND_SIGNATURE_UINT16, &finance.last_year.income.gold_delivered);
    iob->bind(BIND_SIGNATURE_UINT16, &finance.this_year.expenses.disasters);
    iob->bind(BIND_SIGNATURE_UINT16, &finance.last_year.expenses.disasters);
    iob->bind(BIND_SIGNATURE_INT32, &finance.last_year.income.donated);
    iob->bind(BIND_SIGNATURE_INT32, &finance.this_year.income.donated);
    iob->bind(BIND_SIGNATURE_INT32, &finance.wage_rate_paid_this_year);
    iob->bind(BIND_SIGNATURE_UINT8, &finance.tribute_not_paid_last_year);
    iob->bind(BIND_SIGNATURE_UINT8, &finance.tribute_not_paid_total_years);
    iob->bind(BIND_SIGNATURE_INT32, &finance.wage_rate_paid_last_year);
    iob->bind(BIND_SIGNATURE_INT32, &finance.estimated_wages);
    iob->bind(BIND_SIGNATURE_INT32, &finance.crimes_this_month);
    iob->bind(BIND_SIGNATURE_INT32, &finance.gold_stolen_this_month);
    verify_no_crash(iob->get_offset() == city_finance_chunk::size);
}
