#pragma once

#include "building/building.h"

int generic_sprite_offset(int grid_offset, int max_frames, int anim_speed);
int building_animation_offset(building* b, int image_id, int grid_offset, int max_frames = 0);
