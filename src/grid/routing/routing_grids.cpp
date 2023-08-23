#include "routing_grids.h"

grid_xx routing_distance = {0, {FS_INT16, FS_INT16}};
grid_xx water_drag = {0, {FS_UINT8, FS_UINT8}};

grid_xx terrain_land_citizen = {0, {FS_INT8, FS_INT8}};
grid_xx terrain_land_noncitizen = {0, {FS_INT8, FS_INT8}};
grid_xx routing_tiles_water = {0, {FS_INT8, FS_INT8}};
grid_xx routing_tiles_walls = {0, {FS_INT8, FS_INT8}};
