#pragma once

#define IMAGE_CANAL_FULL_OFFSET 48
#define IMAGE_CANAL_FLOODPLAIN_OFFSET 21

int map_canal_at(int grid_offset);

void map_canal_set(int grid_offset, int value);

void map_canal_remove(int grid_offset);
void map_canal_clear(void);

void map_canal_backup(void);
void map_canal_restore(void);

void map_update_canals(void);
void map_canal_fill_from_offset(int grid_offset);