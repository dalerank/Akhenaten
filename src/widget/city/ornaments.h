#ifndef OZYMANDIAS_ORNAMENTS_H
#define OZYMANDIAS_ORNAMENTS_H

#include "graphics/color.h"

int get_farm_image(int grid_offset);
void draw_farm_crops(int type, int progress, int grid_offset, int x, int y, color_t color_mask);

void draw_ornaments_and_animations(int x, int y, int grid_offset);

#endif //OZYMANDIAS_ORNAMENTS_H
