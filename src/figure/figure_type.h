#pragma once

#include <cstdint>
#include "figure_type_indexes.h"

enum e_enemy_type {
    ENEMY_0_BARBARIAN = 0,
    ENEMY_1_NUMIDIAN = 1,
    ENEMY_2_GAUL = 2,
    ENEMY_3_CELT = 3,
    ENEMY_4_GOTH = 4,
    ENEMY_5_PERGAMUM = 5,
    ENEMY_6_SELEUCID = 6,
    ENEMY_7_ETRUSCAN = 7,
    ENEMY_8_GREEK = 8,
    ENEMY_9_EGYPTIAN = 9,
    ENEMY_10_CARTHAGINIAN = 10,
    ENEMY_11_CAESAR = 11
};

enum e_figure_state {
    FIGURE_STATE_NONE = 0,
    FIGURE_STATE_ALIVE = 1,
    FIGURE_STATE_DEAD = 2,
    FIGURE_STATE_DYING = 3,
};

enum e_terrain_usage {
    TERRAIN_USAGE_ANY = 0,
    TERRAIN_USAGE_ROADS = 1,
    TERRAIN_USAGE_ENEMY = 2,
    TERRAIN_USAGE_PREFER_ROADS = 3,
    TERRAIN_USAGE_WALLS = 4,
    TERRAIN_USAGE_ANIMAL = 5,
};
