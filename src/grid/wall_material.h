#pragma once

#include <cstdint>

#include "building/building_type.h"
#include "core/tokenum.h"
#include "grid/point.h"

enum e_wall_material : uint8_t {
    WALL_MATERIAL_NONE = 0,
    WALL_MATERIAL_MUD = 1,
    WALL_MATERIAL_BRICK = 2,
    WALL_MATERIAL_STRONG = 3,

    WALL_MATERIAL_COUNT
};
using e_wall_material_tokens_t = token_holder<e_wall_material, WALL_MATERIAL_NONE, WALL_MATERIAL_COUNT>;
extern const e_wall_material_tokens_t e_wall_material_tokens;

e_wall_material map_wall_material_at(int grid_offset);
inline e_wall_material map_wall_material_at(tile2i tile) { return map_wall_material_at(tile.grid_offset()); }

void map_wall_material_set(int grid_offset, e_wall_material material);
inline void map_wall_material_set(tile2i tile, e_wall_material material) {
    map_wall_material_set(tile.grid_offset(), material);
}

void map_wall_material_clear(int grid_offset);
inline void map_wall_material_clear(tile2i tile) { map_wall_material_clear(tile.grid_offset()); }

void map_wall_material_clear_all();
void map_wall_material_backup();
void map_wall_material_restore();
void map_wall_material_migrate_from_terrain();

e_wall_material wall_material_from_building_type(e_building_type type);
e_building_type wall_building_type_from_material(e_wall_material material);

extern struct io_buffer *iob_wall_material_grid;
