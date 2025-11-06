#include "city/city.h"

#include "core/calc.h"
#include "game/game.h"
#include "scenario/scenario.h"
#include "building/building_house.h"

void city_t::update_prosperity_explanation() {
    int change = 0;
    int profit = 0;
    // unemployment: -1 for too high, +1 for low
    if (labor.unemployment_percentage < 5) {
        change += 1;
    } else if (labor.unemployment_percentage >= 15) {
        change -= 1;
    }

    // losing/earning money: -1 for losing, +5 for profit
    if (has_made_money()) {
        change += 5;
        profit = 1;
    } else {
        change -= 1;
    }
    // food types: +1 for multiple foods
    //    if (city_data.resource.food_types_eaten >= 2) todo
    //        change += 1;

    // wages: +1 for wages 2+ above Rome, -1 for wages below Kingdome
    int avg_wage = finance.wage_rate_paid_last_year / 12;
    if (avg_wage >= finance.wages_kingdome + 2) {
        change += 1;
    } else if (avg_wage < finance.wages_kingdome) {
        change -= 1;
    }

    // high percentage poor: -1, high percentage rich: +1
    int pct_shanties = calc_percentage(population.people_in_shanties, population.current);
    if (pct_shanties > 30) {
        change -= 1;
    }

    if (calc_percentage(population.people_in_manors, population.current) > 10) {
        change += 1;
    }

    // tribute not paid: -1
    if (finance.tribute_not_paid_last_year)
        change -= 1;

    // working hippodrome: +1
    if (entertainment.senet_house_plays > 0)
        change += 1;

    int reason;
    if (ratings.prosperity <= 0 && game.simtime.year == g_scenario.start_year)
        reason = 0;
    else if (ratings.prosperity >= ratings.prosperity_max)
        reason = 1;
    else if (change > 0)
        reason = 2;
    else if (!profit)
        reason = 3;
    else if (labor.unemployment_percentage >= 15)
        reason = 4;
    else if (avg_wage < finance.wages_kingdome)
        reason = 5;
    else if (pct_shanties > 30)
        reason = 6;
    else if (finance.tribute_not_paid_last_year)
        reason = 7;
    else {
        reason = 9;
    }
    // 8 = for bailout
    ratings.prosperity_explanation = reason;
}

void city_t::update_prosperity_rating() {
    int change = 0;
    // unemployment: -1 for too high, +1 for low
    if (labor.unemployment_percentage < 5)
        change += 1;
    else if (labor.unemployment_percentage >= 15)
        change -= 1;

    // losing/earning money: -1 for losing, +5 for profit
    if (has_made_money())
        change += 5;
    else {
        change -= 1;
    }
    ratings.prosperity_treasury_last_year = finance.treasury;
    // food types: +1 for multiple foods
    //    if (city_data.resource.food_types_eaten >= 2) todo
    //        change += 1;

    // wages: +1 for wages 2+ above Rome, -1 for wages below Rome
    int avg_wage = finance.wage_rate_paid_last_year / 12;
    if (avg_wage >= finance.wages_kingdome + 2)
        change += 1;
    else if (avg_wage < finance.wages_kingdome)
        change -= 1;

    // high percentage poor: -1, high percentage rich: +1
    if (calc_percentage(population.people_in_shanties, population.current) > 30) {
        change -= 1;
    }

    if (calc_percentage(population.people_in_manors, population.current) > 10) {
        change += 1;
    }

    // tribute not paid: -1
    if (finance.tribute_not_paid_last_year)
        change -= 1;

    // working hippodrome: +1
    if (entertainment.senet_house_plays > 0)
        change += 1;

    ratings.prosperity += change;
    if (ratings.prosperity > ratings.prosperity_max)
        ratings.prosperity = ratings.prosperity_max;

    ratings.prosperity = calc_bound(ratings.prosperity, 0, 100);

    update_prosperity_explanation();
}

void city_t::calculate_max_prosperity() {
    int points = 0;
    int houses = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        auto house = building_get(i)->dcast_house();
        if (house && house->state() && house->hsize()) {
            points += house->model().prosperity;
            houses++;
        }
    }

    if (houses > 0) {
        ratings.prosperity_max = points / houses;
    } else {
        ratings.prosperity_max = 0;
    }
}

