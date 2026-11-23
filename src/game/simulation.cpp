#include "game/simulation.h"

#include "core/core.h"

#include <algorithm>
#include <cstring>

void simulation_t::register_system(sim_system* system) {
    systems.push_back(system);
    std::sort(systems.begin(), systems.end(),
      [](const sim_system* a, const sim_system* b) { return strcmp(a->name(), b->name()) < 0; });
}

sim_system* simulation_t::find_system(const char* name) const {
    for (sim_system* system : systems) {
        if (strcmp(system->name(), name) == 0) {
            return system;
        }
    }
    return nullptr;
}

void simulation_t::call_system(const char* name, e_sim_call call) const {
    sim_system* system = find_system(name);
    verify_no_crash(system != nullptr);
    switch (call) {
    case SIM_CALL_TICK:
        system->on_tick();
        break;
    case SIM_CALL_DAY:
        system->on_day();
        break;
    case SIM_CALL_WEEK:
        system->on_week();
        break;
    case SIM_CALL_MONTH:
        system->on_month();
        break;
    case SIM_CALL_YEAR:
        system->on_year();
        break;
    case SIM_CALL_NONE:
        break;
    }
}

void simulation_t::run_load(e_load_phase phase) const {
    for (sim_system* system : systems) {
        system->on_load(phase);
    }
}

void simulation_t::push_save_sections(int file_version) const {
    for (sim_system* system : systems) {
        system->push_save_sections(file_version);
    }
}
