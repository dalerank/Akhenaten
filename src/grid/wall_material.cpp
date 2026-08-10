#include "wall_material.h"

#include "grid/grid.h"
#include "grid/terrain.h"
#include "io/io_buffer.h"
#include "scenario/map.h"

grid_xx g_wall_material_grid(FS_UINT8);
grid_xx g_wall_material_grid_backup(FS_UINT8);

e_wall_material map_wall_material_at(int grid_offset) {
    if (!map_grid_is_valid_offset(grid_offset)) {
        return WALL_MATERIAL_NONE;
    }
    return (e_wall_material)map_grid_get(g_wall_material_grid, grid_offset);
}

void map_wall_material_set(int grid_offset, e_wall_material material) {
    if (!map_grid_is_valid_offset(grid_offset)) {
        return;
    }
    map_grid_set(g_wall_material_grid, grid_offset, material);
}

void map_wall_material_clear(int grid_offset) {
    map_wall_material_set(grid_offset, WALL_MATERIAL_NONE);
}

void map_wall_material_clear_all() {
    map_grid_clear(g_wall_material_grid);
}

void map_wall_material_backup() {
    map_grid_copy(g_wall_material_grid, g_wall_material_grid_backup);
}

void map_wall_material_restore() {
    map_grid_copy(g_wall_material_grid_backup, g_wall_material_grid);
}

void map_wall_material_migrate_from_terrain() {
    int grid_offset = scenario_map_data()->start_offset;
    for (int y = 0; y < scenario_map_data()->height; y++, grid_offset += scenario_map_data()->border_size) {
        for (int x = 0; x < scenario_map_data()->width; x++, grid_offset++) {
            if (!map_terrain_is(grid_offset, TERRAIN_WALL)) {
                map_wall_material_clear(grid_offset);
                continue;
            }
            const e_wall_material material = map_wall_material_at(grid_offset);
            if (material != WALL_MATERIAL_MUD && material != WALL_MATERIAL_BRICK) {
                map_wall_material_set(grid_offset, WALL_MATERIAL_MUD);
            }
        }
    }
}

e_wall_material wall_material_from_building_type(e_building_type type) {
    switch (type) {
    case BUILDING_BRICK_WALL:
        return WALL_MATERIAL_BRICK;
    case BUILDING_MUD_WALL:
    default:
        return WALL_MATERIAL_MUD;
    }
}

e_building_type wall_building_type_from_material(e_wall_material material) {
    switch (material) {
    case WALL_MATERIAL_BRICK:
        return BUILDING_BRICK_WALL;
    case WALL_MATERIAL_MUD:
    case WALL_MATERIAL_NONE:
    default:
        return BUILDING_MUD_WALL;
    }
}

io_buffer *iob_wall_material_grid = new io_buffer([](io_buffer *iob, size_t version) {
    iob->bind(BIND_SIGNATURE_GRID, &g_wall_material_grid);
}, [](size_t version) {
    // older saves have no material grid; post_load migrates it from terrain bits
    map_grid_clear(g_wall_material_grid);
});
