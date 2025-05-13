#include "kingdome.h"

#include "city/city.h"
#include "game/game_events.h"
#include "city/city_finance.h"
#include "city/city_message.h"
#include "city/ratings.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "figure/formation.h"
#include "game/difficulty.h"
#include "scenario/invasion.h"
#include "scenario/scenario.h"
#include "game/settings.h"
#include "game/game.h"

#include "dev/debug.h"
#include <iostream>

const int SALARY_FOR_RANK[11] = {0, 2, 5, 8, 12, 20, 30, 40, 60, 80, 100};

static int cheated_invasion = 0;

declare_console_command_p(addsavings) {
    std::string args;
    is >> args;
    int amount = atoi(!args.empty() ? args.c_str() : "100");
    g_city.kingdome.personal_savings += amount;
}

void kingdome_relation_t::init_scenario(int rank, int load_type ) {
    g_city.ratings.kingdom = scenario_starting_kingdom();
    personal_savings = scenario_starting_personal_savings();
    player_rank = rank;
    int salary_rank = rank;
    const bool custom_scenario = g_scenario.mode() != e_scenario_normal;
    
    if (custom_scenario) {
        personal_savings = 0;
        player_rank = scenario_property_player_rank();
        salary_rank = scenario_property_player_rank();
    }

    salary_rank = std::clamp(salary_rank, 0, 10);

    set_salary_rank(salary_rank);
}

void kingdome_relation_t::update_debt_state() {
    if (g_city.finance.treasury >= 0) {
        months_in_debt = -1;
        return;
    }

    const int rescue_loan = g_scenario.rescue_loan();

    switch (debt_state) {
    case e_debt_none:
        // provide bailout
        events::emit(event_finance_donation{ rescue_loan });
        g_city.finance.calculate_totals();

        debt_state = e_debt_one_time;
        months_in_debt = 0;
        messages::popup(MESSAGE_CITY_IN_DEBT, 0, 0);
        g_city.ratings.reduce_prosperity_after_bailout();
        break;

    case e_debt_one_time:
        debt_state = e_debt_twice;
        months_in_debt = 0;
        messages::popup(MESSAGE_CITY_IN_DEBT_AGAIN, 0, 0);
        g_city.ratings.change_kingdom(-5);
        break;

    case e_debt_twice:
        if (months_in_debt == -1) {
            messages::popup(MESSAGE_CITY_IN_DEBT_AGAIN, 0, 0);
            months_in_debt = 0;
        }
        if (game.simtime.day == 0) {
            months_in_debt++;
        }

        if (months_in_debt >= 12) {
            debt_state = e_debt_latest;
            months_in_debt = 0;
            if (!g_city.figures.kingdome_soldiers) {
                messages::popup(MESSAGE_CITY_STILL_IN_DEBT, 0, 0);
                g_city.ratings.change_kingdom(-10);
            }
        }
        break;

    case e_debt_latest:
        if (months_in_debt == -1) {
            messages::popup(MESSAGE_CITY_STILL_IN_DEBT, 0, 0);
            months_in_debt = 0;
        }

        if (game.simtime.day == 0) {
            months_in_debt++;
        }

        if (months_in_debt >= 12) {
            debt_state = e_debt_not_allowed;
            months_in_debt = 0;

            if (!g_city.figures.kingdome_soldiers) {
                g_city.ratings.limit_kingdom(10);
            }
        }
        break;

    case e_debt_not_allowed:
        break;
    }
}

void kingdome_relation_t::process_invasion() {
    if (g_city.figures.kingdome_soldiers && !cheated_invasion) {
        // caesar invasion in progress
        invasion.duration_day_countdown--;
        if (g_city.ratings.kingdom >= 35 && invasion.duration_day_countdown < 176)
            formation_caesar_pause();
        else if (g_city.ratings.kingdom >= 22) {
            if (invasion.duration_day_countdown > 0) {
                formation_caesar_retreat();
                if (!invasion.retreat_message_shown) {
                    invasion.retreat_message_shown = 1;
                    messages::popup(MESSAGE_CAESAR_ARMY_RETREAT, 0, 0);
                }
            } else if (invasion.duration_day_countdown == 0)
                messages::popup(MESSAGE_CAESAR_ARMY_CONTINUE, 0, 0); // a year has passed (11 months), siege goes on
        }
    } else if (invasion.soldiers_killed
               && invasion.soldiers_killed >= invasion.size) {
        // player defeated caesar army
        invasion.size = 0;
        invasion.soldiers_killed = 0;
        if (g_city.ratings.kingdom < 35) {
            g_city.ratings.change_kingdom(10);
            if (invasion.count < 2)
                messages::popup(MESSAGE_CAESAR_RESPECT_1, 0, 0);
            else if (invasion.count < 3)
                messages::popup(MESSAGE_CAESAR_RESPECT_2, 0, 0);
            else {
                messages::popup(MESSAGE_CAESAR_RESPECT_3, 0, 0);
            }
        }
    } else if (invasion.days_until_invasion <= 0) {
        if (g_city.ratings.kingdom <= 10) {
            // warn player that caesar is angry and will invade in a year
            invasion.warnings_given++;
            invasion.days_until_invasion = 192;
            if (invasion.warnings_given <= 1)
                messages::popup(MESSAGE_CAESAR_WRATH, 0, 0);
        }
    } else {
        invasion.days_until_invasion--;
        if (invasion.days_until_invasion == 0) {
            // invade!
            int size;
            if (invasion.count == 0)
                size = 32;
            else if (invasion.count == 1)
                size = 64;
            else if (invasion.count == 2)
                size = 96;
            else {
                size = 144;
            }
            if (scenario_invasion_start_from_caesar(size)) {
                cheated_invasion = 0;
                invasion.count++;
                invasion.duration_day_countdown = 192;
                invasion.retreat_message_shown = 0;
                invasion.size = size;
                invasion.soldiers_killed = 0;
            }
        }
    }
}

void kingdome_relation_t::update() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Emperor Update");
    update_debt_state();
    //if (GAME_ENV == ENGINE_ENV_C3) { // Temporary disable Caesar invasion in Egypt
    //    process_caesar_invasion();
    //}
}

void kingdome_relation_t::init_selected_gift() {
    if (selected_gift_size == GIFT_LAVISH && !g_city.kingdome.can_send_gift(GIFT_LAVISH))
        selected_gift_size = GIFT_GENEROUS;

    if (selected_gift_size == GIFT_GENEROUS && !g_city.kingdome.can_send_gift(GIFT_GENEROUS))
        selected_gift_size = GIFT_MODEST;
}

bool kingdome_relation_t::set_gift_size(int size) {
    if (gifts[size].cost <= personal_savings) {
        selected_gift_size = size;
        return 1;
    } else {
        return 0;
    }
}

int kingdome_relation_t::can_send_gift(int size) {
    return gifts[size].cost <= personal_savings;
}

void kingdome_relation_t::calculate_gift_costs() {
    int savings = personal_savings;
    gifts[GIFT_MODEST].cost = savings / 8 + 20;
    gifts[GIFT_GENEROUS].cost = savings / 4 + 50;
    gifts[GIFT_LAVISH].cost = savings / 2 + 100;
}

void kingdome_relation_t::send_gift() {
    int size = selected_gift_size;
    if (size < GIFT_MODEST || size > GIFT_LAVISH)
        return;

    int cost = gifts[size].cost;
    if (cost > personal_savings)
        return;

    if (gift_overdose_penalty <= 0) {
        gift_overdose_penalty = 1;
        if (size == GIFT_MODEST)
            g_city.ratings.change_kingdom(3);
        else if (size == GIFT_GENEROUS)
            g_city.ratings.change_kingdom(5);
        else if (size == GIFT_LAVISH)
            g_city.ratings.change_kingdom(10);

    } else if (gift_overdose_penalty == 1) {
        gift_overdose_penalty = 2;
        if (size == GIFT_MODEST)
            g_city.ratings.change_kingdom(1);
        else if (size == GIFT_GENEROUS)
            g_city.ratings.change_kingdom(3);
        else if (size == GIFT_LAVISH)
            g_city.ratings.change_kingdom(5);

    } else if (gift_overdose_penalty == 2) {
        gift_overdose_penalty = 3;
        if (size == GIFT_MODEST)
            g_city.ratings.change_kingdom(0);
        else if (size == GIFT_GENEROUS)
            g_city.ratings.change_kingdom(1);
        else if (size == GIFT_LAVISH)
            g_city.ratings.change_kingdom(3);

    } else if (gift_overdose_penalty == 3) {
        gift_overdose_penalty = 4;
        if (size == GIFT_MODEST)
            g_city.ratings.change_kingdom(0);
        else if (size == GIFT_GENEROUS)
            g_city.ratings.change_kingdom(0);
        else if (size == GIFT_LAVISH)
            g_city.ratings.change_kingdom(1);
    }

    months_since_gift = 0;
    // rotate gift type
    gifts[size].id++;
    if (gifts[size].id >= 4)
        gifts[size].id = 0;

    personal_savings -= cost;
}

int kingdome_relation_t::salary_for_rank(int rank) { 
    return SALARY_FOR_RANK[rank];
}

void kingdome_relation_t::set_salary_rank(int rank) {
    salary_rank = rank;
    salary_amount = SALARY_FOR_RANK[rank];
}

void kingdome_relation_t::init_donation_amount() {
    if (donate_amount > personal_savings)
        donate_amount = personal_savings;
}

void kingdome_relation_t::set_donation_amount(int amount) {
    donate_amount = calc_bound(amount, 0, personal_savings);
}

void kingdome_relation_t::change_donation_amount(int change) {
    g_city.kingdome.set_donation_amount(donate_amount + change);
}

void kingdome_relation_t::donate_savings_to_city() {
    events::emit(event_finance_donation{ donate_amount });
    personal_savings -= donate_amount;
    g_city.finance.calculate_totals();
}

void kingdome_relation_t::mark_soldier_killed() {
    invasion.soldiers_killed++;
}

void kingdome_relation_t::force_attack(int size) {
    if (scenario_invasion_start_from_caesar(size)) {
        cheated_invasion = 1;
        invasion.count++;
        invasion.days_until_invasion = 0;
        invasion.duration_day_countdown = 192;
        invasion.retreat_message_shown = 0;
        invasion.size = size;
        invasion.soldiers_killed = 0;
    }
}

void kingdome_relation_t::reset_gifts() {
    gifts[GIFT_MODEST].cost = 0;
    gifts[GIFT_GENEROUS].cost = 0;
    gifts[GIFT_LAVISH].cost = 0;
}
