#ifndef MAP_IMAGE_H
#define MAP_IMAGE_H

#include "core/buffer.h"

int map_image_at(int grid_offset);
void map_image_set(int grid_offset, int image_id);

void map_image_backup(void);
void map_image_restore(void);
void map_image_restore_at(int grid_offset);

void map_image_clear(void);
void map_image_init_edges(void);

void set_image_grid_correction_shift(int shift);

#endif // MAP_IMAGE_H
