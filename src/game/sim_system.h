#pragma once

enum e_load_phase {
    LOAD_PHASE_MAP_TILES,
};

class sim_system {
public:
    virtual ~sim_system() = default;

    virtual const char* name() const = 0;
    virtual void register_steps() {}
    virtual void on_reset() {}
    virtual void on_load(e_load_phase phase) {}
    virtual void on_reload_config() {}
    virtual void push_save_sections(int file_version) {}
};
