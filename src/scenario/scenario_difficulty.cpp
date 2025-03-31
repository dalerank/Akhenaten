#include "scenario_difficulty.h"

#include "core/calc.h"
#include "game/settings.h"
#include "scenario/scenario.h"

#include <array>

std::array<uint16_t, 5> g_difficulty_ajust_money = { 300, 200, 150, 100, 75 };

int scenario_difficulty_t::adjust_money(int money) const {
    const int difficulty = g_settings.difficulty();
    return calc_adjust_with_percentage<int>(money, g_difficulty_ajust_money[difficulty]);
}

int scenario_difficulty_t::loan_money(int money) const {
    const int rescue_loan = g_scenario.finance.rescue_loan;
    return adjust_money(rescue_loan);
}
