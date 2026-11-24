#include "game/sim_schedule.h"

#include "core/core.h"
#include "core/tokenum.h"

namespace {

    const token_holder<e_sim_phase, SIM_PHASE_TICK_BEGIN, SIM_PHASE_COUNT> sim_phase_tokens;
    const token_holder<e_sim_step, sim_step_housing_type_counts, sim_step_count> sim_step_tokens;

    bool sim_step_runs_before(const sim_step& a, const sim_step& b) {
        if (a.phase != b.phase) {
            return a.phase < b.phase;
        }
        return a.slot <= b.slot;
    }

} // namespace

void sim_schedule_t::add(const sim_step& step) {
    verify_no_crash(step.id < sim_step_count && !_registered[step.id] && "simulation step registered twice");
    _steps[step.id] = step;
    _registered[step.id] = true;
}

void sim_schedule_t::check() {
    if (_checked) {
        return;
    }
    _checked = true;
    for (int i = 0; i < sim_step_count; ++i) {
        verify_no_crash(_registered[i] && "simulation step is not registered by any system");
        if (i > 0) {
            verify_no_crash(sim_step_runs_before(_steps[i - 1], _steps[i])
                            && "e_sim_step order disagrees with the steps' phase and slot");
        }
    }
}

span_const<sim_step> sim_schedule_t::steps() {
    check();
    return make_span(_steps.data(), _steps.size());
}

void sim_schedule_t::run(e_sim_phase phase, int slot) {
    check();
    for (const sim_step& step : _steps) {
        if (step.phase != phase || (phase == SIM_PHASE_TICK_SLOT && step.slot != slot)) {
            continue;
        }
        step.run();
    }
}

xstring sim_schedule_t::phase_name(e_sim_phase phase) {
    return sim_phase_tokens.name(phase);
}

xstring sim_schedule_t::step_name(e_sim_step id) {
    return sim_step_tokens.name(id);
}
