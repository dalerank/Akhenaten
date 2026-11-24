#include "game/sim_schedule.h"

#include "core/core.h"
#include "core/tokenum.h"

#include <array>

namespace {

    struct sim_schedule_t {
        std::array<sim_step, sim_step_count> steps{};
        std::array<bool, sim_step_count> registered{};
        bool checked = false;
    };

    sim_schedule_t& sim_schedule() {
        static sim_schedule_t schedule;
        return schedule;
    }

    const token_holder<e_sim_phase, SIM_PHASE_TICK_BEGIN, SIM_PHASE_COUNT> sim_phase_tokens;
    const token_holder<e_sim_step, sim_step_housing_type_counts, sim_step_count> sim_step_tokens;

    bool sim_step_runs_before(const sim_step& a, const sim_step& b) {
        if (a.phase != b.phase) {
            return a.phase < b.phase;
        }
        return a.slot <= b.slot;
    }

    void sim_schedule_check() {
        auto& schedule = sim_schedule();
        if (schedule.checked) {
            return;
        }
        schedule.checked = true;
        for (int i = 0; i < sim_step_count; ++i) {
            verify_no_crash(schedule.registered[i] && "simulation step is not registered by any system");
            if (i > 0) {
                verify_no_crash(sim_step_runs_before(schedule.steps[i - 1], schedule.steps[i])
                                && "e_sim_step order disagrees with the steps' phase and slot");
            }
        }
    }

} // namespace

void sim_schedule_add(const sim_step& step) {
    auto& schedule = sim_schedule();
    verify_no_crash(step.id < sim_step_count && !schedule.registered[step.id] && "simulation step registered twice");
    schedule.steps[step.id] = step;
    schedule.registered[step.id] = true;
}

span_const<sim_step> sim_schedule_steps() {
    sim_schedule_check();
    auto& steps = sim_schedule().steps;
    return make_span(steps.data(), steps.size());
}

void sim_schedule_run(e_sim_phase phase, int slot) {
    sim_schedule_check();
    for (const sim_step& step : sim_schedule().steps) {
        if (step.phase != phase || (phase == SIM_PHASE_TICK_SLOT && step.slot != slot)) {
            continue;
        }
        step.run();
    }
}

xstring sim_phase_name(e_sim_phase phase) {
    return sim_phase_tokens.name(phase);
}

xstring sim_step_name(e_sim_step id) {
    return sim_step_tokens.name(id);
}
