#pragma once

#include "grid/point.h"

void map_orientation_change(int counter_clockwise);

int map_orientation_for_gatehouse(int x, int y);

int map_orientation_for_triumphal_arch(int x, int y);

void map_orientation_update_buildings(void);

enum e_venue_mode_orientation {
    e_venue_mode_booth,
    e_venue_mode_bandstand,
    e_venue_mode_pavilion,
    e_venue_mode_festival_square,
};

bool map_orientation_for_venue(int x, int y, e_venue_mode_orientation mode, int* building_orientation);
bool map_orientation_for_venue_with_map_orientation(tile2i tile, e_venue_mode_orientation mode, int* building_orientation);
