#pragma once

#include "building.h"

enum { MONUMENT_PYRAMID = 0, MONUMENT_MASTABA = 1 };

enum {
    MONUMENT_PART_CORNERS = 0,
    MONUMENT_PART_SIDES = 1,
    MONUMENT_PART_CENTER = 2,
    MONUMENT_PART_EXTRA = 3,
    MONUMENT_PART_EXTERIORS = 4,
    MONUMENT_PART_CORNERS_2 = 5,
    MONUMENT_PART_SIDES_2 = 6,
};

enum {
    TEMPLE_COMPLEX_ALTAR_ATTACHMENT = 1,
    TEMPLE_COMPLEX_ORACLE_ATTACHMENT = 2,
};

int next_statue_variant(int type, int variant);

int get_statue_image(int type, int orientation, int variant);
int get_statue_image_from_value(int type, int combined, int map_orientation);
int get_statue_variant_value(int orientation, int variant);

int get_monument_part_image(int part, int orientation, int level);

int get_temple_complex_part_image(int type, int part, int orientation, int level);
building* get_temple_complex_front_facing_part(building* b);
