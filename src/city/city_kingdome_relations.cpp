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
#include "game/game.h"
#include "scenario/criteria.h"
#include "game/game_config.h"

#include "dev/debug.h"
#include <algorithm>

kingdome_relation_t::static_params ANK_VARIABLE(kingdome_relation);

declare_console_command_p(updatekingdome) {
    int value = args.next_int(0);
    if (!!value) {
        g_city.kingdome.advance_year();
    } else {
        g_city.kingdome.advance_month();
    }
}

declare_console_command_p(addkingdome) {
    int amount = args.next_int(10);
    g_city.kingdome.change(amount);
}

declare_console_command_p(addsavings) {
    int amount = args.next_int(100);
    g_city.kingdome.personal_savings += amount;
}

void kingdome_relation_t::load_scenario(int rank, int load_type) {
    rating = g_scenario.starting_kingdom();
    personal_savings = 0;
    const bool custom_scenario = g_scenario.mode() != e_scenario_normal;

    if (custom_scenario) {
        personal_savings = 0;
        player_rank = (int8_t)scenario_property_player_rank();
    } else if (load_type == e_session_mission) {
        // player_rank already set from mission JS in load_metadata.
        // Accept override only for a valid salary rank (0..10) — never scenario_id.
        if (rank >= 0 && rank <= 10) {
            player_rank = (int8_t)rank;
        }
        personal_savings = campaign_carry_personal_savings;
    } else if (rank >= 0 && rank <= 10) {
        player_rank = (int8_t)rank;
    }

    const int salary_rank = std::clamp((int)player_rank, 0, 10);
    this->salary_rank = (uint8_t)salary_rank;
    this->salary_amount = (uint8_t)params().salary_ranks[salary_rank];
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
                const uint8_t debt_ceiling =
                    (uint8_t)std::clamp((int)params().last_debt_rating_cap, 0, 100);
                rating = std::min(rating, debt_ceiling);
            }
        }
        break;

    case e_debt_not_allowed:
        break;
    }
}

void kingdome_relation_t::process_invasion() {
    if (g_city.figures.kingdome_soldiers) {
        // cheated (console force_attack): skip duration/pause/retreat only —
        // do NOT fall through to wipe or Caesar countdown while troops remain.
        if (!invasion.cheated) {
            invasion.duration_day_countdown--;
            // Caesar wrath only: favour/scenario waves must not auto-pause/retreat at KR≥22
            // (Heh/Bubastis favour triggers at KR<30 — otherwise the army flees on day one).
            if (!invasion.favour_only) {
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
            }
        }
    } else if (invasion.soldiers_killed && invasion.soldiers_killed >= invasion.size) {
        finish_army_defeated();
    } else if (invasion.favour_only && invasion.size > 0) {
        // Active favour/scenario bookkeeping with no counted soldiers yet.
        // duration == 192: just spawned / not yet in kingdome_soldiers (same-day gap) /
        // embarked sea troops still invisible — must not start a wrath countdown.
        // duration != 192: army left the map without a full kill wipe — clear slot.
        // Use != 192 (not < 192): duration may go negative; field is saved as UINT16.
        if (invasion.duration_day_countdown != 192) {
            invasion.size = 0;
            invasion.soldiers_killed = 0;
            invasion.duration_day_countdown = 0;
            invasion.favour_only = 0;
            invasion.cheated = 0;
        }
    } else if (invasion.days_until_invasion != 0) {
        // Drop Caesar-3 auto-wrath countdown. Pharaoh sends a low-KR army only via
        // mission favour scripts / map KNGDOME events (Men-nefer has neither).
        invasion.days_until_invasion = 0;
        invasion.warnings_given = 0;
    }
}

void kingdome_relation_t::update() {
    OZZY_PROFILER_FUNCTION();
    update_debt_state();
    process_invasion();
    events::emit(event_kingdome_update_gifts{ (int)personal_savings });
}

void kingdome_relation_t::mark_soldier_killed() {
    invasion.soldiers_killed++;
}

void kingdome_relation_t::finish_army_defeated() {
    // Player wiped the kingdom army (kills >= size). Favour waves skip Caesar respect.
    invasion.size = 0;
    invasion.soldiers_killed = 0;
    invasion.duration_day_countdown = 0;
    invasion.cheated = 0;
    if (invasion.favour_only) {
        invasion.favour_only = 0;
        return;
    }
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
}

void kingdome_relation_t::begin_invasion(int size, bool cheated) {
    // Live kingdom troops already on the map: grow kill tally, do not replace size
    // (force_attack / overlapping wrath would otherwise finish early while ghosts remain).
    if (invasion.size > 0 && g_city.figures.kingdome_soldiers > 0) {
        invasion.size += size;
        invasion.favour_only = 0;
        invasion.cheated = cheated ? 1 : 0;
        invasion.count++;
        invasion.days_until_invasion = 0;
        invasion.retreat_message_shown = 0;
        return;
    }

    // Pending wipe from the previous army: award respect before overwriting.
    if (!invasion.favour_only && invasion.soldiers_killed
        && invasion.soldiers_killed >= invasion.size && invasion.size > 0) {
        finish_army_defeated();
    }

    invasion.favour_only = 0;
    invasion.cheated = cheated ? 1 : 0;
    invasion.count++;
    invasion.days_until_invasion = 0;
    invasion.duration_day_countdown = 192;
    invasion.retreat_message_shown = 0;
    invasion.size = size;
    invasion.soldiers_killed = 0;
}

void kingdome_relation_t::begin_favour_army(int size) {
    // Kill tally + duration only — leave Caesar wrath countdown and invasion.count alone.
    // Pause/retreat stay Caesar-only (!favour_only in process_invasion).
    //
    // Accumulate onto an army that is still on the map. Require kingdome_soldiers>0 —
    // otherwise a same-day gap after wipe (kills tallied, process_invasion not yet run)
    // would grow size onto a dead slot. Always mark favour_only: a favour wave joining
    // an active Caesar army must not pick up pause/retreat or Caesar respect on wipe.
    if (invasion.size > 0 && g_city.figures.kingdome_soldiers > 0) {
        invasion.size += size;
        invasion.favour_only = 1;
        return;
    }

    // Pending Caesar wipe (no soldiers left): award respect before favour overwrites.
    if (!invasion.favour_only && invasion.soldiers_killed
        && invasion.soldiers_killed >= invasion.size && invasion.size > 0) {
        finish_army_defeated();
    }

    invasion.cheated = 0;
    invasion.favour_only = 1;
    invasion.duration_day_countdown = 192;
    invasion.retreat_message_shown = 0;
    invasion.size = size;
    invasion.soldiers_killed = 0;
}

bool kingdome_relation_t::force_attack(int size) {
    if (scenario_invasion_start_from_kingdome(size)) {
        begin_invasion(size, true);
        return true;
    }
    return false;
}

void kingdome_relation_t::advance_month() {
    if (g_scenario.is_open_play) {
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

void kingdome_relation_t::init() {
    rating_cap = 100;
}

void kingdome_relation_t::on_post_load() {
    if (rating_cap == 0) {
        rating_cap = 100;
    }
}

void kingdome_relation_t::reset() {
    rating = 50;
    rating_cap = 100;
}

const kingdome_relation_t::static_params &kingdome_relation_t::params() {
    return kingdome_relation;
}