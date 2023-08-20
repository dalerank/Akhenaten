#pragma once

#include "building/type.h"
#include "core/buffer.h"
#include "grid/point.h"

/**
 * Returns the building at the given offset
 * @param grid_offset Map offset
 * @return Building ID of building at offset, 0 means no building
 */
int map_building_at(int grid_offset);
int map_building_at(map_point tile);

void map_building_set(int grid_offset, int building_id);

/**
 * Increases building damage by 1
 * @param grid_offset Map offset
 * @return New damage amount
 */
int map_building_damage_increase(int grid_offset);

void map_building_damage_clear(int grid_offset);

int map_rubble_building_type(int grid_offset);

void map_set_rubble_building_type(int grid_offset, int type);

/**
 * Clears the maps related to buildings
 */
void map_building_clear(void);

void map_highlight_set(int grid_offset);
void map_highlight_clear(int grid_offset);
int map_is_highlighted(int grid_offset);
void map_clear_highlights(void);

int map_building_is_reservoir(int x, int y);