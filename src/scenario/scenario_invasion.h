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

struct enemy_properties_t {
    int percentage_type1;
    int percentage_type2;
    int percentage_type3;
    std::array<e_figure_type, 3> figure_types;
    xstring army_title;
    e_formation_layout layout;
};
ANK_CONFIG_STRUCT(enemy_properties_t, percentage_type1, percentage_type2, percentage_type3, figure_types, army_title, layout)

struct invasion_data_t {
    int last_internal_invasion_id;
    int min_invasion_amount;
    int max_invasion_amount;
    std::array<invasion_warning_t, 101> warnings;

    void clear();
    void init();

    const enemy_properties_t &get_prop(e_enemy_type type);
};
ANK_CONFIG_STRUCT(invasion_data_t, min_invasion_amount, max_invasion_amount)
extern invasion_data_t g_invasions;

extern const int LOCAL_UPRISING_NUM_ENEMIES[20];


bool scenario_invasion_exists_upcoming();

void scenario_invasion_foreach_warning(std::function<void(vec2i, int)> callback);

int scenario_invasion_count();

bool scenario_invasion_start_from_kingdome(int size);

void scenario_invasion_start_from_console(int attack_type, e_enemy_type enemy_type, int size, tile2i invasion_point);

void scenario_invasion_process();

int map_invasion_point(tile2i point);

tile2i scenario_start_invasion_impl(e_enemy_type enemy_type, int amount, int invasion_point, e_formation_attack_type attack_type, int invasion_id, tile2i tile_inv);
