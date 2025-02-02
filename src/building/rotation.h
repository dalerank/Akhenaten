#pragma once

#include "grid/point.h"
#include "building/building_type.h"

void building_rotation_update_road_orientation();
int building_rotation_global_rotation();
int building_rotation_get_road_orientation();
void building_rotation_rotate_by_hotkey();

void building_rotation_force_two_orientations();
int building_rotation_get_storage_fort_orientation(int);
int building_rotation_get_delta_with_rotation(int default_delta);
void building_rotation_get_offset_with_rotation(int offset, int rotation, int* x, int* y);

int building_rotation_get_corner(int rot);
void building_rotation_reset_rotation();