#include "difficulty.h"

#include "core/calc.h"
#include "game/settings.h"

#include <array>

struct difficulty_data_t {
    int enemies;
    int starting_kingdom;
    int sentiment;
    float risk_multiplier;
};

// time for a house to catch fire, tested on og game install:
// very easy - 51 months (lets round to 50)
// easy - 12 months
// normal - 10 months
// hard - 7 months
// very hard - 7 months
static const difficulty_data_t g_difficulty_data[] = {
  {40, 70, 80, 0.2},  // very easy
  {60, 60, 70, 0.8},  // easy
  {80, 50, 60, 1.0},  // normal
  {100, 50, 50, 1.2}, // hard
  {120, 40, 40, 1.2}   // very hard
};

int difficulty_starting_kingdom(void) {
    return g_difficulty_data[g_settings.difficulty()].starting_kingdom;
}

int difficulty_sentiment(void) {
    return g_difficulty_data[g_settings.difficulty()].sentiment;
}

int difficulty_adjust_enemies(int enemies) {
    return calc_adjust_with_percentage(enemies, g_difficulty_data[g_settings.difficulty()].enemies);
}

int difficulty_adjust_wolf_attack(int attack) {
    switch (g_settings.difficulty()) {
    case DIFFICULTY_VERY_EASY:
        return 2;
    case DIFFICULTY_EASY:
        return 4;
    case DIFFICULTY_NORMAL:
        return 6;
    default:
        return attack;
    }
}

int difficulty_multiply_risk(int risk_delta) {
    return int(g_difficulty_data[g_settings.difficulty()].risk_multiplier * risk_delta);
}
