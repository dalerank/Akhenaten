#include "city_migration.h"
#include "core/app_module.h"
#include "game/sim_schedule.h"

#include "building/building_house.h"
#include "city/city.h"
#include "city/city_message.h"
#include "city/city_warnings.h"
#include "core/calc.h"
#include "core/log.h"
#include "game/simulation.h"
#include "game/game_config.h"
#include "game/game_events.h"
#include "js/js_register.h"

svector<migration_system::condition, 16> g_migration_conditions;
city_migration_defaults_t ANK_VARIABLE(migration_defaults);
svector<sentiment_step_t, 16> ANK_VARIABLE(migration_sentiment_influence);
svector<unemployment_step_t, 16> ANK_VARIABLE(migration_unemployment_percentage);
std::unordered_map<xstring, int> g_migration_cap_reasons;
std::unordered_map<xstring, std::pair<int, int>> g_migration_unemployment_cap_reasons;

e_no_immigration_reason_tokens_t ANK_CONFIG_ENUM(no_immigration_reason_tokens);

void migration_system::nobles_leave_city(int num_people) {
    _state.nobles_leave_city_this_year += num_people;
}

void migration_system::update_status() {
    auto& params = migration_defaults;

    const auto& sentiment = _ctx.sentiment;
    auto sent_it = std::find_if(migration_sentiment_influence.begin(), migration_sentiment_influence.end(), [sentiment = sentiment.value] (const auto& t) {
        return sentiment >= t.s;
    });

    const int8_t unemployment_percentage = _ctx.labor.unemployment_percentage;
    auto unemployment_it = std::find_if(migration_unemployment_percentage.begin(), migration_unemployment_percentage.end(), [unemployment_percentage] (const auto &t) {
        return unemployment_percentage > t.u;
    });

    int want_percentage_by_unemployments = (unemployment_it != migration_unemployment_percentage.end()) ? unemployment_it->p : 0;
    std::pair<int, int> range_percentage_by_unemployments{ -9999, 9999 };
    for (const auto &it : g_migration_unemployment_cap_reasons) {
        range_percentage_by_unemployments.first = std::max(range_percentage_by_unemployments.first, it.second.first);
        range_percentage_by_unemployments.second = std::min(range_percentage_by_unemployments.second, it.second.second);
    }
    if (!!game_features::gameplay_change_migration_unemployment) {
        _state.percentage_by_unemployments = std::clamp(want_percentage_by_unemployments,
          range_percentage_by_unemployments.first, range_percentage_by_unemployments.second);
    } else {
        _state.percentage_by_unemployments = 0;
    }

    _state.percentage_by_sentiment = (sent_it != migration_sentiment_influence.end()) ? sent_it->i : 0;
    _state.percentage = (_state.percentage_by_sentiment + _state.percentage_by_unemployments);

    _state.immigration_amount_per_batch = 0;
    _state.emigration_amount_per_batch = 0;

    int cur_population_cap = 999999;
    for (const auto &it: g_migration_cap_reasons) {
        if (it.second > 0) {
            cur_population_cap = std::min(cur_population_cap, it.second);
        }
    }

    if (_state.population_cap > 0) {
        cur_population_cap = std::min(cur_population_cap, _state.population_cap);
    }

    if (cur_population_cap > 0 && _ctx.population.current >= cur_population_cap) {
        _state.percentage = 0;
        if (!_state.migration_cap && _ctx.population.room_in_houses > 0) {
            events::emit(event_city_warning{ "#immigration_people_wont_come" });
        }
        _state.migration_cap = true;
        return;
    }
    _state.migration_cap = false;

    // war scares immigrants away
    if (_ctx.figures.total_invading_enemies() > 3 && _state.percentage > 0) {
        _state.percentage = 0;
        _state.invading_cap = true;
        return;
    }
    _state.invading_cap = false;

    if (_state.percentage > 0) {
        // immigration
        if (_state.emigration_duration) {
            _state.emigration_duration--;
        } else {
            _state.immigration_amount_per_batch
              = calc_adjust_with_percentage<int>(params.max_newcomers_per_update, _state.percentage);
            _state.immigration_duration = 2;
        }
    } else if (_state.percentage < 0) {
        // emigration
        if (_state.immigration_duration) {
            _state.immigration_duration--;
        } else if (_ctx.population.current > 100) {
            _state.emigration_amount_per_batch
              = calc_adjust_with_percentage<int>(params.max_leftovers_per_update, -_state.percentage);
            _state.emigration_duration = 2;
        }
    }
}

void migration_system::create_immigrants(int num_people) {
    int immigrated = _ctx.population_sys.create_immigrants(num_people);
    _state.immigrated_today += immigrated;
    _state.newcomers += _state.immigrated_today;
    if (immigrated == 0) {
        _state.refused_immigrants_today += num_people;
    }
}

void migration_system::set_unemployments_cap(xstring reason, int min, int max) {
    if (min == 0 && max == 0) {
        g_migration_unemployment_cap_reasons.erase(reason);
        return;
    }

    g_migration_unemployment_cap_reasons[reason] = { min, max };
}

void migration_system::set_migration_cap(xstring reason, int cap) {
    if (cap == 0) {
        g_migration_cap_reasons.erase(reason);
        return;
    }

    g_migration_cap_reasons[reason] = cap;
}

const std::unordered_map<xstring, int>& migration_system::get_migration_caps() {
    return g_migration_cap_reasons;
}

city_migration_defaults_t& migration_system::current_params() {
    return migration_defaults;
}

void migration_system::create_emigrants(int num_people) {
    _state.emigrated_today += _ctx.population_sys.create_emigrants(num_people);
}

void migration_system::create_migrants() {
    _state.immigrated_today = 0;
    _state.emigrated_today = 0;
    _state.refused_immigrants_today = 0;

    auto& params = migration_defaults;
    if (_state.immigration_amount_per_batch > 0) {
        if (_state.immigration_amount_per_batch >= params.max_immigration_amount_per_batch) {
            create_immigrants(_state.immigration_amount_per_batch);

        } else if (_state.immigration_amount_per_batch + _state.immigration_queue_size
                   >= params.max_immigration_amount_per_batch) {
            create_immigrants(_state.immigration_amount_per_batch + _state.immigration_queue_size);
            _state.immigration_queue_size = 0;

        } else { // queue them for next round
            _state.immigration_queue_size += _state.immigration_amount_per_batch;
        }
    }

    if (_state.emigration_amount_per_batch > 0) {
        if (_state.emigration_amount_per_batch >= params.max_emigration_amount_per_batch) {
            create_emigrants(_state.emigration_amount_per_batch);

        } else if (
          _state.emigration_amount_per_batch + _state.emigration_queue_size >= params.max_emigration_amount_per_batch) {
            create_emigrants(_state.emigration_amount_per_batch + _state.emigration_queue_size);
            _state.emigration_queue_size = 0;
            if (!_state.emigration_message_shown) {
                _state.emigration_message_shown = 1;
                //                city_message_post(true, MESSAGE_EMIGRATION, 0, 0);
            }
        } else { // queue them for next round
            _state.emigration_queue_size += _state.emigration_amount_per_batch;
        }
    }

    _state.immigration_amount_per_batch = 0;
    _state.emigration_amount_per_batch = 0;
}

void migration_system::reset() {
    g_migration_conditions.clear();
    g_migration_cap_reasons.clear();
    g_migration_unemployment_cap_reasons.clear();
    _state.migration_cap = false;
    _state.invading_cap = false;
}

void migration_system::update_conditions() {
    for (const auto &condition : g_migration_conditions) {
        condition(_state);
    }
}

void migration_system::update_month() {
    int houses_total = 0;
    int houses_with_room = 0;
    int houses_no_entry = 0;
    int houses_immigrant_slot = 0;
    int houses_immigrant_slot_dead = 0;
    int vacant_lots = 0;
    int vacant_lots_with_room = 0;
    int room_reachable = 0;

    buildings_house_do([&](building_house *house) {
        if (house->state() != BUILDING_STATE_VALID) {
            return;
        }

        ++houses_total;
        const int room = house->population_room();
        const bool no_entry = house->distance_from_entry() <= 0;
        const bool vacant = house->is_vacant_lot();

        if (vacant) {
            ++vacant_lots;
            if (room > 0) {
                ++vacant_lots_with_room;
            }
        }

        if (no_entry) {
            ++houses_no_entry;
        } else if (room > 0) {
            ++houses_with_room;
            room_reachable += room;
        }

        if (house->base.has_figure(BUILDING_SLOT_IMMIGRANT, -1)) {
            ++houses_immigrant_slot;
            if (house->get_figure(BUILDING_SLOT_IMMIGRANT)->state != FIGURE_STATE_ALIVE) {
                ++houses_immigrant_slot_dead;
            }
        }
    });

    logs::info("[migration] %d.%02d pop=%d room=%d/%d reachable_room=%d sentiment=%d unemp=%d%%", _ctx.year,
      _ctx.month + 1, _ctx.population.current, _ctx.population.room_in_houses, _ctx.population.total_capacity,
      room_reachable, _ctx.sentiment.value, _ctx.labor.unemployment_percentage);
    logs::info("[migration] pct=%d (sent=%d unemp=%d) queue=%d/%d batch=%d/%d duration=%d/%d", _state.percentage,
      _state.percentage_by_sentiment, _state.percentage_by_unemployments, _state.immigration_queue_size,
      _state.emigration_queue_size, _state.immigration_amount_per_batch, _state.emigration_amount_per_batch,
      _state.immigration_duration, _state.emigration_duration);
    logs::info("[migration] newcomers=%d last_day immigrated=%d emigrated=%d refused=%d cause=%d cap=%d "
               "invading=%d pop_cap=%d",
      _state.newcomers, _state.immigrated_today, _state.emigrated_today, _state.refused_immigrants_today,
      _state.no_immigration_cause, _state.migration_cap ? 1 : 0, _state.invading_cap ? 1 : 0, _state.population_cap);
    logs::info("[migration] houses=%d with_room=%d no_entry=%d immigrant_slot=%d (dead=%d) vacant=%d/%d",
               houses_total, houses_with_room, houses_no_entry,
               houses_immigrant_slot, houses_immigrant_slot_dead,
               vacant_lots_with_room, vacant_lots);

    for (const auto &it : g_migration_cap_reasons) {
        logs::info("[migration] cap_reason '%s'=%d", it.first.c_str(), it.second);
    }
    for (const auto &it : g_migration_unemployment_cap_reasons) {
        logs::info("[migration] unemp_cap '%s'=[%d,%d]", it.first.c_str(), it.second.first, it.second.second);
    }

    reset_newcomers();
}

void migration_system::update() {
    update_conditions();
    update_status();
    create_migrants();

    events::emit(event_migration_update{_ctx.population.current});
}

void migration_system::determine_reason() {
    switch (_ctx.sentiment.low_mood_cause) {
    case LOW_MOOD_NO_FOOD:
        _state.no_immigration_cause = 2;
        break;
    case LOW_MOOD_NO_JOBS:
        _state.no_immigration_cause = 1;
        break;
    case LOW_MOOD_HIGH_TAXES:
        _state.no_immigration_cause = 3;
        break;
    case LOW_MOOD_LOW_WAGES:
        _state.no_immigration_cause = 0;
        break;
    case LOW_MOOD_MANY_TENTS:
        _state.no_immigration_cause = 4;
        break;
    default:
        _state.no_immigration_cause = 5;
        break;
    }
}

int migration_system::no_room_for_immigrants() {
    return _state.refused_immigrants_today || _ctx.population.room_in_houses <= 0;
}

void migration_system::add_condition(condition cond) {
    g_migration_conditions.push_back(cond);
}

class migration_sim_system : public sim_system {
public:
    const char* name() const override { return "migration"; }
    void register_steps(sim_schedule_t& schedule) override {
        schedule.add(
          {sim_step_migration, SIM_PHASE_TICK_SLOT, 23, SIM_AREA_MIGRATION, [] { g_city.migration_sys().update(); }});
        schedule.add({sim_step_migration_month, SIM_PHASE_MONTH_CITY, -1, SIM_AREA_MIGRATION,
          [] { g_city.migration_sys().update_month(); }});
        schedule.add({sim_step_migration_year, SIM_PHASE_YEAR, -1, SIM_AREA_MIGRATION,
          [] { g_city.migration_sys().advance_year(); }});
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_migration_system) {
    static migration_sim_system system;
    g_simulation.register_system(&system);
}
