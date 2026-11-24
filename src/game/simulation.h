#pragma once

#include "game/sim_schedule.h"
#include "game/sim_system.h"
#include "game/simulation_time.h"

#include <vector>

struct simulation_t {
    simulation_time_t simtime;
    bool time_runs = false;
    sim_schedule_t schedule;

    void register_system(sim_system* system);
    sim_system* find_system(const char* name) const;
    void reset_systems() const;
    void run_load(e_load_phase phase) const;
    void reload_config() const;
    void push_save_sections(int file_version) const;

private:
    std::vector<sim_system*> systems;
};

extern simulation_t g_simulation;
