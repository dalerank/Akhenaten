#include "city_difficulty.h"

#include "core/calc.h"

#include <array>

std::array<uint16_t, 5> g_difficulty_ajust_money = { 300, 200, 150, 100, 75 };

int city_difficulty_t::adjust_money(int money, int mode) const {
    return calc_adjust_with_percentage<int>(money, g_difficulty_ajust_money[mode]);
}