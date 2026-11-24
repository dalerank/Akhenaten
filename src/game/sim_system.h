#pragma once

enum e_load_phase {
    LOAD_PHASE_MAP_TILES,
};

enum e_sim_call {
    SIM_CALL_NONE,
    SIM_CALL_TICK,
    SIM_CALL_DAY,
    SIM_CALL_WEEK,
    SIM_CALL_MONTH,
    SIM_CALL_YEAR,
};

class sim_system {
public:
    virtual ~sim_system() = default;

    virtual const char* name() const = 0;
    virtual void on_tick() {}
    virtual void on_day() {}
    virtual void on_week() {}
    virtual void on_month() {}
    virtual void on_year() {}
    virtual void on_reset() {}
    virtual void on_load(e_load_phase phase) {}
    virtual void on_reload_config() {}
    virtual void push_save_sections(int file_version) {}
};
