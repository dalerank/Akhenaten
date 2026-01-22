#include "city_kingdome_relations.h"

#include "city/city.h"
#include "core/calc.h"
#include "game/game_events.h"
#include "city/city_finance.h"
#include "city/city_message.h"
#include "city/ratings.h"
#include "core/calc.h"
#include "core/profiler.h"
#include "figure/formation.h"
#include "game/difficulty.h"
#include "scenario/scenario_invasion.h"
#include "scenario/scenario.h"
#include "game/settings.h"
#include "game/game.h"
#include "scenario/criteria.h"
#include "game/game_config.h"
#include "js/js_game.h"

#include "dev/debug.h"
#include <iostream>

static int cheated_invasion = 0;

const token_holder<e_gift, GIFT_MODEST, GIFT_COUNT> ANK_CONFIG_ENUM(e_gift_tokens);
kingdome_relation_t::static_params ANK_VARIABLE(kingdome_relation);

declare_console_command_p(updatekingdome) {
    std::string args; is >> args;
    int value = atoi(args.empty() ? (pcstr)"0" : args.c_str());
    if (!!value) {
        g_city.kingdome.advance_year();
    } else {
        g_city.kingdome.advance_month();
    }
}

declare_console_command_p(addkingdome) {
    std::string args; is >> args;
    int amount = atoi(args.empty() ? (pcstr)"10" : args.c_str());
    g_city.kingdome.change(amount);
}

declare_console_command_p(addsavings) {
    std::string args;
    is >> args;
    int amount = atoi(!args.empty() ? args.c_str() : "100");
    g_city.kingdome.personal_savings += amount;
}

void kingdome_relation_t::load_scenario(int rank, int load_type ) {
    rating = g_scenario.starting_kingdom();
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
        messages::popup("message_out_of_money", 0, 0);
        g_city.ratings.reduce_prosperity_after_bailout();
        break;

    case e_debt_one_time:
        debt_state = e_debt_twice;
        months_in_debt = 0;
        messages::popup("message_debt_again", 0, 0);
        change(params().first_debt_penalty);
        break;

    case e_debt_twice:
        if (months_in_debt == -1) {
            messages::popup("message_out_of_money_again", 0, 0);
            months_in_debt = 0;
        }
        if (game.simtime.day == 0) {
            months_in_debt++;
        }

        if (months_in_debt >= 12) {
            debt_state = e_debt_latest;
            months_in_debt = 0;
            if (!g_city.figures.kingdome_soldiers) {
                messages::popup("message_wrath_of_the_emperor", 0, 0);
                change(params().second_debt_penalty);
            }
        }
        break;

    case e_debt_latest:
        if (months_in_debt == -1) {
            messages::popup("message_wrath_of_the_emperor", 0, 0);
            months_in_debt = 0;
        }

        if (game.simtime.day == 0) {
            months_in_debt++;
        }

        if (months_in_debt >= 12) {
            debt_state = e_debt_not_allowed;
            months_in_debt = 0;

            if (!g_city.figures.kingdome_soldiers) {
                rating_cap = params().last_debt_rating_cap;
            }
        }
        break;

    case e_debt_not_allowed:
        break;
    }
}

void kingdome_relation_t::process_invasion() {
    if (g_city.figures.kingdome_soldiers && !cheated_invasion) {
        // nomes invasion in progress
        invasion.duration_day_countdown--;
        if (rating >= 35 && invasion.duration_day_countdown < 176)
            formation_kingdome_pause();
        else if (rating >= 22) {
            if (invasion.duration_day_countdown > 0) {
                formation_kingdome_retreat();
                if (!invasion.retreat_message_shown) {
                    invasion.retreat_message_shown = 1;
                    messages::popup("message_attack_called_off", 0, 0);
                }
            } else if (invasion.duration_day_countdown == 0)
                messages::popup("message_wrath_of_the_emperor", 0, 0); // a year has passed (11 months), siege goes on
        }
    } else if (invasion.soldiers_killed && invasion.soldiers_killed >= invasion.size) {
        // player defeated nomes army
        invasion.size = 0;
        invasion.soldiers_killed = 0;
        if (rating < 35) {
            change(10);
            if (invasion.count < 2)
                messages::popup("MESSAGE_CAESAR_RESPECT_1", 0, 0);
            else if (invasion.count < 3)
                messages::popup("MESSAGE_CAESAR_RESPECT_2", 0, 0);
            else {
                messages::popup("MESSAGE_CAESAR_RESPECT_3", 0, 0);
            }
        }
    } else if (invasion.days_until_invasion <= 0) {
        if (rating <= 10) {
            // warn player that caesar is angry and will invade in a year
            invasion.warnings_given++;
            invasion.days_until_invasion = 192;
            if (invasion.warnings_given <= 1)
                messages::popup("message_wrath_of_the_emperor", 0, 0);
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
            if (scenario_invasion_start_from_kingdome(size)) {
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
    OZZY_PROFILER_FUNCTION();
    update_debt_state();
    reset_gifts();
    update_gifts();
}

void kingdome_relation_t::update_gifts() {
    gifts[GIFT_MODEST].cost = get_gift_cost(GIFT_MODEST);
    gifts[GIFT_GENEROUS].cost = get_gift_cost(GIFT_GENEROUS);
    gifts[GIFT_LAVISH].cost = get_gift_cost(GIFT_LAVISH);
}

int kingdome_relation_t::get_gift_cost(int size) {
    auto it = std::find_if(params().gift_rules.begin(), params().gift_rules.end(),
        [&] (const auto &rule) { return rule.id == size; });

    if (it != params().gift_rules.end()) {
        return int(personal_savings / it->rate + it->minimum);
    }

    // Default gift cost calculation
    switch (size) {
    case GIFT_MODEST: return (personal_savings / 8 + 20);
    case GIFT_GENEROUS: return (personal_savings / 4 + 50);
    case GIFT_LAVISH: return (personal_savings / 2 + 100);
    default: return 100;
    }
}

int kingdome_relation_t::can_send_gift(int size) {
    return gifts[size].cost <= personal_savings;
}

void kingdome_relation_t::send_gift(int gift_size) {
    if (gift_size < GIFT_MODEST || gift_size > GIFT_LAVISH)
        return;

    int cost = gifts[gift_size].cost;
    if (cost > personal_savings) {
        return;
    }

    if (gift_overdose_penalty <= 0) {
        gift_overdose_penalty = 1;
        change(params().gift_relation_change_first[gift_size]);
    } else if (gift_overdose_penalty == 1) {
        gift_overdose_penalty = 2;
        change(params().gift_relation_change_second[gift_size]);
    } else if (gift_overdose_penalty == 2) {
        gift_overdose_penalty = 3;
        change(params().gift_relation_change_third[gift_size]);
    } else if (gift_overdose_penalty == 3) {
        gift_overdose_penalty = 4;
        change(params().gift_relation_change_last[gift_size]);
    }

    months_since_gift = 0;
    // rotate gift type
    gifts[gift_size].id++;
    if (gifts[gift_size].id >= 4)
        gifts[gift_size].id = 0;

    personal_savings -= cost;
}

int kingdome_relation_t::salary_for_rank(int rank) { 
    return params().salary_ranks[rank];
}

void kingdome_relation_t::set_salary_rank(int rank) {
    salary_rank = rank;
    salary_amount = params().salary_ranks[rank];
}

void kingdome_relation_t::init_donation_amount() {
    donate_amount = calc_bound(donate_amount, 0, personal_savings);
}

const kingdome_gift *kingdome_relation_t::get_gift(int size) {
    return &gifts[size];
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
    if (scenario_invasion_start_from_kingdome(size)) {
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

void kingdome_relation_t::advance_month() {
    if (scenario_is_open_play()) {
        rating = 50;
        return;
    }

    months_since_gift++;
    if (months_since_gift >= params().months_since_gift_locker) {
        gift_overdose_penalty = 0;
    }

    rating = calc_bound(rating, 0, (rating_cap == 0 ? 100 : rating_cap));
}

void kingdome_relation_t::advance_year() {
    advance_month();
    
    kingdom_salary_penalty = 0;
    kingdom_milestone_penalty = 0;
    kingdom_ignored_request_penalty = 0;

    const bool can_update_rating = !game_features::gameplay_save_year_kingdome_rating;
    if (can_update_rating && g_scenario.is_before_mission(3)) {
        rating -= 2;
    }

    // tribute penalty
    const auto &tribute_penalties = params().tribute_not_paid_years_penalty;
    if (g_city.finance.tribute_not_paid_last_year) {
        int years_missed = std::clamp<int>(g_city.finance.tribute_not_paid_total_years, 0, tribute_penalties.size() - 1);
        int penalty = tribute_penalties[years_missed];
        change(penalty);
    }

    // rank salary
    const int salary_delta = g_city.kingdome.salary_rank - g_city.kingdome.player_rank;
    if (g_city.kingdome.player_rank != 0) {
        if (salary_delta > 0) {
            // salary too high
            rating -= salary_delta;
            kingdom_salary_penalty = salary_delta + params().player_salary_above_king_penalty;
        } else if (salary_delta < 0) {
            // salary lower than rank
            rating += params().player_salary_less_king_promotion;
        }
    } else if (salary_delta > 0) {
        rating -= salary_delta;
        kingdom_salary_penalty = salary_delta;
    }

    // milestone
    int milestone_pct = 0;
    if (scenario_criteria_milestone_year(25) == game.simtime.year) {
        milestone_pct = 25;
    } else if (scenario_criteria_milestone_year(50) == game.simtime.year) {
        milestone_pct = 50;
    } else if (scenario_criteria_milestone_year(75) == game.simtime.year) {
        milestone_pct = 75;
    }

    auto &ratings = g_city.ratings;
    if (milestone_pct) {
        int bonus = 1;
        if (winning_culture() && ratings.culture < calc_adjust_with_percentage(winning_culture(), milestone_pct)) {
            bonus = 0;
        }
        if (winning_prosperity() && ratings.prosperity < calc_adjust_with_percentage(winning_prosperity(), milestone_pct)) {
            bonus = 0;
        }
        if (winning_monuments() && ratings.monument < calc_adjust_with_percentage(winning_monuments(), milestone_pct)) {
            bonus = 0;
        }
        if (winning_kingdom() && rating < calc_adjust_with_percentage(winning_kingdom(), milestone_pct)) {
            bonus = 0;
        }
        if (winning_population() && g_city.population.current < calc_adjust_with_percentage(winning_population(), milestone_pct)) {
            bonus = 0;
        }

        if (bonus) {
            rating += 5;
        } else {
            rating -= 2;
            kingdom_milestone_penalty = 2;
        }
    }

    if (rating < rating_last_year) {
        kingdom_change = e_rating_dropping;
    } else if (rating == rating_last_year) {
        kingdom_change = e_rating_stalling;
    } else {
        kingdom_change = e_rating_rising;
    }

    rating_last_year = rating;
}

void kingdome_relation_t::reduce_missed_request(int penalty) {
    change(-penalty);
    kingdom_ignored_request_penalty = penalty;
}

void kingdome_relation_t::increase_success_request(int value) {
    change(value);
}

void kingdome_relation_t::reduce_god_wrath(int value) {
    change(-value);
}

void kingdome_relation_t::increase_blessing_god(int value) {
    change(value);
}

void kingdome_relation_t::change(int amount) {
    rating = calc_bound(rating + amount, 0, rating_cap);
}

void kingdome_relation_t::update_explanation() {
    kingdom_salary_penalty = 0;
    int salary_delta = g_city.kingdome.salary_rank - g_city.kingdome.player_rank;
    if (g_city.kingdome.player_rank != 0) {
        if (salary_delta > 0) {
            kingdom_salary_penalty = salary_delta + 1;
        }

    } else if (salary_delta > 0) {
        kingdom_salary_penalty = salary_delta;
    }

    if (kingdom_salary_penalty >= 8)
        kingdom_explanation = 1;
    else if (g_city.finance.tribute_not_paid_total_years >= 3)
        kingdom_explanation = 2;
    else if (kingdom_ignored_request_penalty >= 5)
        kingdom_explanation = 3;
    else if (kingdom_salary_penalty >= 5)
        kingdom_explanation = 4;
    else if (g_city.finance.tribute_not_paid_total_years >= 2)
        kingdom_explanation = 5;
    else if (kingdom_ignored_request_penalty >= 3)
        kingdom_explanation = 6;
    else if (kingdom_salary_penalty >= 3)
        kingdom_explanation = 7;
    else if (g_city.finance.tribute_not_paid_last_year)
        kingdom_explanation = 8;
    else if (kingdom_salary_penalty >= 2)
        kingdom_explanation = 9;
    else if (kingdom_milestone_penalty)
        kingdom_explanation = 10;
    else if (kingdom_salary_penalty)
        kingdom_explanation = 11;
    else if (kingdom_change == e_rating_rising) { // rising
        kingdom_explanation = 12;
    } else if (kingdom_change == e_rating_stalling) { // the same
        kingdom_explanation = 13;
    } else {
        kingdom_explanation = 0;
    }
}

void kingdome_relation_t::init() {
    rating_cap = 100;
    reset_gifts();

    events::subscribe([this] (event_send_gift_to_kingdome ev) {
        send_gift(ev.gift_size);
    });
}

void kingdome_relation_t::on_post_load() {
    if (rating_cap == 0) { rating_cap = 100; }
}

void kingdome_relation_t::reset() {
    rating = 50;
    rating_cap = 100;
}

const kingdome_relation_t::static_params &kingdome_relation_t::params() {
    return kingdome_relation;
}