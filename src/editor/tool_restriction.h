#pragma once

#include "editor/tool.h"
#include "grid/point.h"
#include "core/xstring.h"

int editor_tool_can_place_flag(int type, tile2i tile, xstring& warning);

int editor_tool_can_place_access_ramp(tile2i tile, int* orientation_index);

int editor_tool_can_place_building(tile2i tile, int num_tiles, int* blocked_tiles);
