#pragma once

#include "graphics/color.h"
#include "graphics/view/view.h"
#include "building/building_type.h"

enum e_farm_worker_state {
    FARM_WORKER_TILING,
    FARM_WORKER_SEEDING,
    FARM_WORKER_HARVESTING
};

int get_farm_image(int grid_offset);
void draw_farm_crops(painter &ctx, e_building_type type, int progress, int grid_offset, vec2i tile, color color_mask);

void draw_ornaments_and_animations(vec2i pixel, tile2i point, painter &ctx);