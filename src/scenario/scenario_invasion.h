#pragma once

#include "core/vec2i.h"
#include "grid/point.h"
#include "figure/formation.h"
#include "figure/figure_type.h"
#include "core/archive.h"

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

struct enemy_properties_t {
    int percentage_type1;
    int percentage_type2;
    int percentage_type3;
    std::array<e_figure_type, 3> figure_types;
    e_formation_layout layout;
};
ANK_CONFIG_STRUCT(enemy_properties_t, percentage_type1, percentage_type2, percentage_type3, figure_types, layout)

extern std::array<enemy_properties_t, ENEMY_COUNT> g_enemy_properties;
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

tile2i scenario_start_invasion_impl(int enemy_type, int amount, int invasion_point, int attack_type, int invasion_id);
