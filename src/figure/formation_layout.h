#pragma once

#include "figure/figure_type.h"
#include "grid/point.h"

tile2i formation_layout_position(int layout, int index);
// OG military.c soldier_layout_offset: chariots (LEG_HEAVY) use wider tables for double-line.
tile2i formation_layout_position_for_figure(e_figure_type type, int layout, int index);
