#include "game/simulation.h"

#include "core/archive.h"
#include "core/core.h"

#include <algorithm>
#include <cstring>

void simulation_t::register_system(sim_system* system) {
    systems.push_back(system);
    system->register_steps(schedule);
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

void simulation_t::reset_systems() const {
    for (sim_system* system : systems) {
        system->on_reset();
    }
}

void simulation_t::run_load(e_load_phase phase) const {
    for (sim_system* system : systems) {
        system->on_load(phase);
    }
}

void simulation_t::reload_config() const {
    for (sim_system* system : systems) {
        system->on_reload_config();
    }
}

ANK_DECLARE_CONFIG_ITERATOR(config_reload_systems);
void config_reload_systems() {
    g_simulation.reload_config();
}

void simulation_t::push_save_sections(int file_version) const {
    for (sim_system* system : systems) {
        system->push_save_sections(file_version);
    }
}
