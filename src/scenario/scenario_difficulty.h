#pragma once

struct scenario_difficulty_t {
    int adjust_money(int v) const;
    int loan_money(int v) const;
    int house_tax_multiplier(int v) const;
};