#pragma once

#include "grid/point.h"
#include "core/archive.h"

struct formation;

struct animal_herds_t {
    bool herd_migration;

    void update();

    void update_herd_formation(formation *m);
};
ANK_CONFIG_STRUCT(animal_herds_t, herd_migration)

extern animal_herds_t g_animal_herds;

bool formation_herd_breeding_ground_at(tile2i tile, int size);
