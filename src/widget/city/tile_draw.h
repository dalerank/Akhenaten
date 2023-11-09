#pragma once

#include "building/building.h"
#include "graphics/color.h"
#include "graphics/view/view.h"

void init_draw_context(int selected_figure_id, vec2i* figure_coord, int highlighted_formation);

void draw_flattened_footprint_anysize(int x, int y, int size_x, int size_y, int image_offset, color color_mask);
void draw_flattened_footprint_building(const building* b, int x, int y, int image_offset, color color_mask);

void draw_debug_figurecaches(vec2i pixel, map_point point, painter &ctx);

void draw_isometrics(vec2i pixel, map_point point, painter &ctx);
void draw_ornaments(vec2i pixel, map_point point, painter &ctx);
void draw_figures(vec2i pixel, map_point point, painter &ctx);

void draw_isometrics_overlay(vec2i pixel, map_point point, painter &ctx);
void draw_ornaments_overlay(vec2i pixel, map_point point, painter &ctx);
void draw_figures_overlay(vec2i pixel, map_point point, painter &ctx);
