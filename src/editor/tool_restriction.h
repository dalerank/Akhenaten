#ifndef EDITOR_TOOL_RESTRICTION_H
#define EDITOR_TOOL_RESTRICTION_H

#include "editor/tool.h"
#include "grid/point.h"

int editor_tool_can_place_flag(int type, map_point tile, int* warning);

int editor_tool_can_place_access_ramp(map_point tile, int* orientation_index);

int editor_tool_can_place_building(map_point tile, int num_tiles, int* blocked_tiles);

#endif // EDITOR_TOOL_RESTRICTION_H
