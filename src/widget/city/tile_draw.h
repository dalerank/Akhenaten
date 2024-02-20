#pragma once

#include "building/building.h"
#include "graphics/color.h"
#include "graphics/view/view.h"

void init_draw_context(int selected_figure_id, vec2i* figure_coord, int highlighted_formation);

void draw_flattened_footprint_anysize(vec2i pos, int size_x, int size_y, int image_offset, color color_mask, painter &ctx);
void draw_flattened_footprint_building(const building* b, vec2i pos, int image_offset, color color_mask, painter &ctx);

void map_render_clear();

void draw_isometric_flat(vec2i pixel, tile2i point, painter &ctx);
void draw_isometric_terrain_height(vec2i pixel, tile2i point, painter &ctx);
void draw_isometric_nonterrain_height(vec2i pixel, tile2i point, painter &ctx);
void draw_figures(vec2i pixel, tile2i point, painter &ctx);
void draw_figures(vec2i pixel, tile2i point, painter &ctx, bool force);

void draw_isometrics_overlay_flat(vec2i pixel, tile2i point, painter &ctx);
void draw_isometrics_overlay_height(vec2i pixel, tile2i point, painter &ctx);
void draw_ornaments_overlay(vec2i pixel, tile2i point, painter &ctx);
void draw_figures_overlay(vec2i pixel, tile2i point, painter &ctx);
