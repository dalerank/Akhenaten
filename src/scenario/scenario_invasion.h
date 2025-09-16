#pragma once

#include "core/vec2i.h"

#include <array>
#include <functional>

enum e_attack_type { 
    ATTACK_TYPE_ENEMIES, 
    ATTACK_TYPE_KINGDOME, 
    ATTACK_TYPE_NATIVES 
};

struct invasion_warning_t {
    bool in_use;
    bool handled;
    int invasion_path_id;
    int warning_years;
    vec2i pos;
    int image_id;
    int empire_object_id;
    int year_notified;
    int month_notified;
    int months_to_go;
    int invasion_id;
};

struct invasion_data_t {
    int last_internal_invasion_id;
    std::array<invasion_warning_t, 101> warnings;
};

extern invasion_data_t g_invasions;

void scenario_invasion_clear();

void scenario_invasion_init();

bool scenario_invasion_exists_upcoming();

void scenario_invasion_foreach_warning(std::function<void(vec2i, int)> callback);

int scenario_invasion_count();

int scenario_invasion_start_from_seth();

bool scenario_invasion_start_from_kingdome(int size);

void scenario_invasion_start_from_console(int attack_type, int enemy_type, int size, int invasion_point);

void scenario_invasion_process();

int scenario_start_invasion_impl(int enemy_type, int amount, int invasion_point, int attack_type, int invasion_id);
