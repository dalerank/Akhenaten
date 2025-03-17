#pragma once

#include "editor/tool.h"
#include "grid/point.h"
#include "core/xstring.h"

int editor_tool_can_place_flag(int type, map_point tile, xstring& warning);

int editor_tool_can_place_access_ramp(map_point tile, int* orientation_index);

int editor_tool_can_place_building(map_point tile, int num_tiles, int* blocked_tiles);
