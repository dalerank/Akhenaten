#include "simulation_time.h"
#include "core/app_module.h"
#include "game/game_events.h"
#include "core/random.h"
#include "game/sim_schedule.h"

#include "io/io_buffer.h"
#include "scenario/scenario.h"
#include "game/simulation.h"
#include "js/js_register.h"

e_month_tokens_t ANK_CONFIG_ENUM(e_month_tokens);

simulation_t g_simulation;

void simulation_time_t::init(int y) {
    tick = 0;
    day = 0;
    month = 0;
    total_days = 0;
    year = y;
}

int16_t simulation_time_t::years_since_start() const {
    return year - g_scenario.start_year;
}

int simulation_time_t::absolute_day(bool since_start) const {
    int days = month * days_in_month + day;
    if (since_start)
        days += (days_in_month * months_in_year)/*192*/ * years_since_start();
    return days;
}

int simulation_time_t::absolute_tick_year_start() const {
    return (ticks_in_day * days_in_month * months_in_year) /*9792*/ * years_since_start();
}

int simulation_time_t::absolute_tick(bool since_start) const {
    const int ticks = absolute_day(since_start) * ticks_in_day + tick;
    return ticks;
}

bool simulation_time_t::advance_tick() {
    if (++tick >= simulation_time_t::ticks_in_day) {
        tick = 0;
        return true;
    }
    return false;
}

day_result simulation_time_t::advance_day() {
    total_days++;
    bool is_week_advanced = false;
    ++day;
    is_week_advanced = (day > 0) && ((day % days_in_week) == 0);
    if (day >= simulation_time_t::days_in_month) {
        day = 0;
        return { is_week_advanced, true };
    }
    return { is_week_advanced, false };
}

bool simulation_time_t::advance_month() {
    if (++month >= 12) {
        month = 0;
        return true;
    }
    return false;
}

void simulation_time_t::advance_year() {
    ++year;
}

class simulation_time_system : public sim_system {
public:
    const char* name() const override { return "simulation_time"; }
    void on_reset() override { g_simulation.simtime.init(2098); }
    void register_steps(sim_schedule_t& schedule) override {
        schedule.add({sim_step_random, SIM_PHASE_TICK_BEGIN, [](int) { random_generate_next(); }});
        schedule.add({sim_step_event_advance_day, SIM_PHASE_DAY,
          [](int) { events::emit(event_advance_day::from_simtime(g_simulation.simtime)); }});
        schedule.add({sim_step_event_advance_week, SIM_PHASE_WEEK,
          [](int) { events::emit(event_advance_week::from_simtime(g_simulation.simtime)); }});
        schedule.add({sim_step_random_month, SIM_PHASE_MONTH, [](int) { random_generate_next(); }});
        schedule.add({sim_step_event_advance_month, SIM_PHASE_MONTH_END,
          [](int) { events::emit(event_advance_month::from_simtime(g_simulation.simtime)); }});
        schedule.add({sim_step_simtime_year, SIM_PHASE_YEAR, [](int) { g_simulation.simtime.advance_year(); }});
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_simulation_time_system) {
    static simulation_time_system system;
    g_simulation.register_system(&system);
}
