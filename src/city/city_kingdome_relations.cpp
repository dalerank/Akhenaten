#include "city_kingdome_relations.h"
#include "city/city_population.h"
#include "game/simulation.h"
#include "core/app_module.h"
#include "game/sim_schedule.h"

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

#include <algorithm>

kingdome_state::static_params ANK_VARIABLE(kingdome_relation);

void kingdome_system::load_scenario(int rank, int load_type) {
    _state.rating = _ctx.starting_kingdom;
    _state.personal_savings = 0;
    const bool custom_scenario = _ctx.custom_scenario;

    if (custom_scenario) {
        _state.personal_savings = 0;
        _state.player_rank = (int8_t)scenario_property_player_rank();
    } else if (load_type == e_session_mission) {
        // player_rank already set from mission JS in load_metadata.
        // Accept override only for a valid salary rank (0..10) — never scenario_id.
        if (rank >= 0 && rank <= 10) {
            _state.player_rank = (int8_t)rank;
        }
        _state.personal_savings = _state.campaign_carry_personal_savings;
    } else if (rank >= 0 && rank <= 10) {
        _state.player_rank = (int8_t)rank;
    }

    const int salary_rank = std::clamp((int)_state.player_rank, 0, 10);
    _state.salary_rank = (uint8_t)salary_rank;
    _state.salary_amount = (uint8_t)_state.params().salary_ranks[salary_rank];
}

void kingdome_system::update_debt_state() {
    if (_ctx.finance.treasury >= 0) {
        _state.months_in_debt = -1;
        return;
    }

    const int rescue_loan = _ctx.rescue_loan;

    switch (_state.debt_state) {
    case e_debt_none:
        // provide bailout
        events::emit(event_finance_donation{ rescue_loan });
        _ctx.finance_sys.calculate_totals();

        _state.debt_state = e_debt_one_time;
        _state.months_in_debt = 0;
        messages::popup("message_out_of_money", 0, 0);
        _ctx.ratings.reduce_prosperity_after_bailout();
        break;

    case e_debt_one_time:
        _state.debt_state = e_debt_twice;
        _state.months_in_debt = 0;
        messages::popup("message_debt_again", 0, 0);
        _state.change(_state.params().first_debt_penalty);
        break;

    case e_debt_twice:
        if (_state.months_in_debt == -1) {
            messages::popup("message_out_of_money_again", 0, 0);
            _state.months_in_debt = 0;
        }
        if (_ctx.day == 0) {
            _state.months_in_debt++;
        }

        if (_state.months_in_debt >= 12) {
            _state.debt_state = e_debt_latest;
            _state.months_in_debt = 0;
            if (!_ctx.figures.kingdome_soldiers) {
                messages::popup("message_wrath_of_the_emperor", 0, 0);
                _state.change(_state.params().second_debt_penalty);
            }
        }
        break;

    case e_debt_latest:
        if (_state.months_in_debt == -1) {
            messages::popup("message_wrath_of_the_emperor", 0, 0);
            _state.months_in_debt = 0;
        }

        if (_ctx.day == 0) {
            _state.months_in_debt++;
        }

        if (_state.months_in_debt >= 12) {
            _state.debt_state = e_debt_not_allowed;
            _state.months_in_debt = 0;

            if (!_ctx.figures.kingdome_soldiers) {
                const uint8_t debt_ceiling = (uint8_t)std::clamp((int)_state.params().last_debt_rating_cap, 0, 100);
                _state.rating = std::min(_state.rating, debt_ceiling);
            }
        }
        break;

    case e_debt_not_allowed:
        break;
    }
}

void kingdome_system::process_invasion() {
    if (_ctx.figures.kingdome_soldiers) {
        // cheated (console force_attack): skip duration/pause/retreat only —
        // do NOT fall through to wipe or Caesar countdown while troops remain.
        if (!_state.invasion.cheated) {
            _state.invasion.duration_day_countdown--;
            // Caesar wrath only: favour/scenario waves must not auto-pause/retreat at KR≥22
            // (Heh/Bubastis favour triggers at KR<30 — otherwise the army flees on day one).
            if (!_state.invasion.favour_only) {
                if (_state.rating >= 35 && _state.invasion.duration_day_countdown < 176)
                    formation_kingdome_pause();
                else if (_state.rating >= 22) {
                    if (_state.invasion.duration_day_countdown > 0) {
                        formation_kingdome_retreat();
                        if (!_state.invasion.retreat_message_shown) {
                            _state.invasion.retreat_message_shown = 1;
                            messages::popup("message_attack_called_off", 0, 0);
                        }
                    } else if (_state.invasion.duration_day_countdown == 0)
                        messages::popup("message_wrath_of_the_emperor", 0, 0); // a year has passed (11 months), siege goes on
                }
            }
        }
    } else if (_state.invasion.soldiers_killed && _state.invasion.soldiers_killed >= _state.invasion.size) {
        _state.finish_army_defeated();
    } else if (_state.invasion.favour_only && _state.invasion.size > 0) {
        // Active favour/scenario bookkeeping with no counted soldiers yet.
        // duration == 192: just spawned / not yet in kingdome_soldiers (same-day gap) /
        // embarked sea troops still invisible — must not start a wrath countdown.
        // duration != 192: army left the map without a full kill wipe — clear slot.
        // Use != 192 (not < 192): duration may go negative; field is saved as UINT16.
        if (_state.invasion.duration_day_countdown != 192) {
            _state.invasion.size = 0;
            _state.invasion.soldiers_killed = 0;
            _state.invasion.duration_day_countdown = 0;
            _state.invasion.favour_only = 0;
            _state.invasion.cheated = 0;
        }
    } else if (_state.invasion.days_until_invasion != 0) {
        // Drop Caesar-3 auto-wrath countdown. Pharaoh sends a low-KR army only via
        // favour events (update_kingdom_favour) / map KNGDOME events (Men-nefer has neither).
        _state.invasion.days_until_invasion = 0;
        _state.invasion.warnings_given = 0;
    }
}

void kingdome_system::update() {
    OZZY_PROFILER_FUNCTION();
    update_debt_state();
    _ctx.scenario_events.update_kingdom_favour();
    process_invasion();
    events::emit(event_kingdome_update_gifts{(int)_state.personal_savings});
}

void kingdome_state::mark_soldier_killed() {
    invasion.soldiers_killed++;
}

void kingdome_state::finish_army_defeated() {
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

void kingdome_system::begin_invasion(int size, bool cheated) {
    // Live kingdom troops already on the map: grow kill tally, do not replace size
    // (force_attack / overlapping wrath would otherwise finish early while ghosts remain).
    if (_state.invasion.size > 0 && _ctx.figures.kingdome_soldiers > 0) {
        _state.invasion.size += size;
        _state.invasion.favour_only = 0;
        _state.invasion.cheated = cheated ? 1 : 0;
        _state.invasion.count++;
        _state.invasion.days_until_invasion = 0;
        _state.invasion.retreat_message_shown = 0;
        return;
    }

    // Pending wipe from the previous army: award respect before overwriting.
    if (!_state.invasion.favour_only && _state.invasion.soldiers_killed
        && _state.invasion.soldiers_killed >= _state.invasion.size && _state.invasion.size > 0) {
        _state.finish_army_defeated();
    }

    _state.invasion.favour_only = 0;
    _state.invasion.cheated = cheated ? 1 : 0;
    _state.invasion.count++;
    _state.invasion.days_until_invasion = 0;
    _state.invasion.duration_day_countdown = 192;
    _state.invasion.retreat_message_shown = 0;
    _state.invasion.size = size;
    _state.invasion.soldiers_killed = 0;
}

void kingdome_system::begin_favour_army(int size) {
    // Kill tally + duration only — leave Caesar wrath countdown and invasion.count alone.
    // Pause/retreat stay Caesar-only (!favour_only in process_invasion).
    //
    // Accumulate onto an army that is still on the map. Require kingdome_soldiers>0 —
    // otherwise a same-day gap after wipe (kills tallied, process_invasion not yet run)
    // would grow size onto a dead slot. Always mark favour_only: a favour wave joining
    // an active Caesar army must not pick up pause/retreat or Caesar respect on wipe.
    if (_state.invasion.size > 0 && _ctx.figures.kingdome_soldiers > 0) {
        _state.invasion.size += size;
        _state.invasion.favour_only = 1;
        return;
    }

    // Pending Caesar wipe (no soldiers left): award respect before favour overwrites.
    if (!_state.invasion.favour_only && _state.invasion.soldiers_killed
        && _state.invasion.soldiers_killed >= _state.invasion.size && _state.invasion.size > 0) {
        _state.finish_army_defeated();
    }

    _state.invasion.cheated = 0;
    _state.invasion.favour_only = 1;
    _state.invasion.duration_day_countdown = 192;
    _state.invasion.retreat_message_shown = 0;
    _state.invasion.size = size;
    _state.invasion.soldiers_killed = 0;
}

bool kingdome_system::force_attack(int size) {
    if (scenario_invasion_start_from_kingdome(size)) {
        begin_invasion(size, true);
        return true;
    }
    return false;
}

void kingdome_system::advance_month() {
    if (_ctx.open_play) {
        _state.rating = 50;
        return;
    }

    _state.months_since_gift++;
    if (_state.months_since_gift >= _state.params().months_since_gift_locker) {
        _state.gift_overdose_penalty = 0;
    }

    _state.rating = calc_bound(_state.rating, 0, (_state.rating_cap == 0 ? 100 : _state.rating_cap));
}

// OG update_kingdom_yearly; the monthly part (gift timer, clamp) already ran in advance_month.
void kingdome_system::advance_year() {
    if (_ctx.open_play) {
        _state.rating = 50;
        return;
    }

    _state.kingdom_salary_penalty = 0;
    _state.kingdom_milestone_penalty = 0;
    _state.kingdom_ignored_request_penalty = 0;

    int r = _state.rating;
    const bool can_update_rating = !game_features::gameplay_save_year_kingdome_rating;
    const bool is_custom_map = (_ctx.custom_scenario);
    if (
      can_update_rating && (is_custom_map || _ctx.campaign_scenario_id >= _state.params().yearly_decay_from_mission)) {
        r += _state.params().yearly_decay;
    }

    const auto& finance = _ctx.finance;
    if (!finance.tribute_not_paid_last_year) {
        if (finance.last_year.expenses.total < finance.last_year.income.total) {
            r += _state.params().yearly_profit_bonus;
        }
    } else {
        const auto& tribute_penalties = _state.params().tribute_not_paid_years_penalty;
        int years_missed = std::clamp<int>(finance.tribute_not_paid_total_years, 0, tribute_penalties.size() - 1);
        r += tribute_penalties[years_missed];
    }

    // rank salary
    const int salary_delta = _state.salary_rank - _state.player_rank;
    if (_state.player_rank != 0) {
        if (salary_delta > 0) {
            // salary too high
            r -= salary_delta;
            _state.kingdom_salary_penalty = salary_delta + _state.params().player_salary_above_king_penalty;
        } else if (salary_delta < 0) {
            // salary lower than rank
            r += _state.params().player_salary_less_king_promotion;
        }
    } else if (salary_delta > 0) {
        r -= salary_delta;
        _state.kingdom_salary_penalty = salary_delta;
    }

    // milestone
    int milestone_pct = 0;
    if (scenario_criteria_milestone_year(25) == _ctx.year) {
        milestone_pct = 25;
    } else if (scenario_criteria_milestone_year(50) == _ctx.year) {
        milestone_pct = 50;
    } else if (scenario_criteria_milestone_year(75) == _ctx.year) {
        milestone_pct = 75;
    }

    auto& ratings = _ctx.ratings;
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
        if (winning_kingdom() && r < calc_adjust_with_percentage(winning_kingdom(), milestone_pct)) {
            bonus = 0;
        }
        if (winning_population()
            && _ctx.population.current < calc_adjust_with_percentage(winning_population(), milestone_pct)) {
            bonus = 0;
        }

        if (bonus) {
            r += 5;
        } else {
            r -= 2;
            _state.kingdom_milestone_penalty = 2;
        }
    }

    if (r < _state.rating_last_year) {
        _state.kingdom_change = e_rating_dropping;
    } else if (r == _state.rating_last_year) {
        _state.kingdom_change = e_rating_stalling;
    } else {
        _state.kingdom_change = e_rating_rising;
    }

    _state.rating = (uint8_t)calc_bound(r, 0, (_state.rating_cap == 0 ? 100 : _state.rating_cap));
    _state.rating_last_year = _state.rating;
}

void kingdome_state::reduce_missed_request(int penalty) {
    change(-penalty);
    kingdom_ignored_request_penalty = penalty;
}

void kingdome_state::increase_success_request(int value) {
    change(value);
}

void kingdome_state::reduce_god_wrath(int value) {
    change(-value);
}

void kingdome_state::increase_blessing_god(int value) {
    change(value);
}

void kingdome_state::change(int amount) {
    rating = calc_bound(rating + amount, 0, rating_cap);
}

void kingdome_state::init() {
    rating_cap = 100;
}

void kingdome_state::on_post_load() {
    if (rating_cap == 0) {
        rating_cap = 100;
    }
}

void kingdome_state::reset() {
    rating = 50;
    rating_cap = 100;
}

const kingdome_state::static_params& kingdome_state::params() {
    return kingdome_relation;
}

class kingdome_relations_system : public sim_system {
public:
    const char* name() const override { return "kingdome_relations"; }
    void register_steps(sim_schedule_t& schedule) override {
        schedule.add({sim_step_kingdome, SIM_PHASE_TICK, [](int tick) {
                          if (tick != 4) {
                              return;
                          }
                          g_city.kingdome_sys().update();
                      }});
        schedule.add(
          {sim_step_kingdome_month, SIM_PHASE_MONTH_CITY, [](int) { g_city.kingdome_sys().advance_month(); }});
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_kingdome_relations_system) {
    static kingdome_relations_system system;
    g_simulation.register_system(&system);
}
