#include "empire.h"
#include "core/app_module.h"
#include "game/sim_schedule.h"

#include "city/city_message.h"
#include "empire/empire.h"
#include "game/simulation.h"
#include "scenario/scenario.h"

int scenario_empire_id() {
    return g_scenario.empire.id;
}

int scenario_empire_is_expanded() {
    return g_scenario.empire.is_expanded;
}

void scenario_empire_process_expansion() {
    if (g_scenario.empire.is_expanded || g_scenario.empire.expansion_year <= 0) {
        return;
    }

    if (g_simulation.simtime.year < g_scenario.empire.expansion_year + g_scenario.start_year) {
        return;
    }

    g_empire.expand();

    g_scenario.empire.is_expanded = 1;
    messages::popup("message_empire_has_expanded", 0, 0);
}

class scenario_empire_system : public sim_system {
public:
    const char* name() const override { return "scenario_empire"; }
    void register_steps(sim_schedule_t& schedule) override {
        schedule.add({sim_step_empire_expansion, SIM_PHASE_YEAR, [](int) { scenario_empire_process_expansion(); }});
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_scenario_empire_system) {
    static scenario_empire_system system;
    g_simulation.register_system(&system);
}
