#include "game/sim_schedule.h"

#include "core/core.h"

#include <algorithm>
#include <array>
#include <vector>

static std::vector<sim_step>& sim_steps() {
    static std::vector<sim_step> steps;
    return steps;
}

static bool sim_step_before(const sim_step& a, const sim_step& b) {
    if (a.phase != b.phase) {
        return a.phase < b.phase;
    }
    if (a.slot != b.slot) {
        return a.slot < b.slot;
    }
    return a.order < b.order;
}

void sim_schedule_add(const sim_step& step) {
    auto& steps = sim_steps();
    auto it = std::lower_bound(steps.begin(), steps.end(), step, sim_step_before);
    const bool taken = it != steps.end() && !sim_step_before(step, *it);
    verify_no_crash(!taken && "two simulation steps share phase, slot and order");
    steps.insert(it, step);
}

span_const<sim_step> sim_schedule_steps() {
    const std::vector<sim_step>& steps = sim_steps();
    return make_span(steps);
}

void sim_schedule_run(e_sim_phase phase, int slot) {
    for (const sim_step& step : sim_steps()) {
        if (step.phase != phase || (phase == SIM_PHASE_TICK_SLOT && step.slot != slot)) {
            continue;
        }
        step.run();
    }
}

const char* sim_phase_name(e_sim_phase phase) {
    static const std::array<const char*, SIM_PHASE_COUNT> names = {"tick_begin", "tick_slot", "tick_city_end",
      "tick_end", "day", "week", "month_city", "month", "month_end", "year"};
    return phase < SIM_PHASE_COUNT ? names[phase] : "?";
}
