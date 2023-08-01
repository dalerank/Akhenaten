#ifndef WIDGET_CITY_WITHOUT_OVERLAY_H
#define WIDGET_CITY_WITHOUT_OVERLAY_H

#include "building/building.h"
#include "graphics/color.h"
#include "graphics/view/view.h"

void init_draw_context(int selected_figure_id, pixel_coordinate* figure_coord, int highlighted_formation);

void draw_flattened_footprint_anysize(int x, int y, int size_x, int size_y, int image_offset, color_t color_mask);
void draw_flattened_footprint_building(const building* b, int x, int y, int image_offset, color_t color_mask);

void draw_debug_figurecaches(pixel_coordinate pixel, map_point point);

void draw_isometrics(pixel_coordinate pixel, map_point point);
void draw_ornaments(pixel_coordinate pixel, map_point point);
void draw_figures(pixel_coordinate pixel, map_point point);

void draw_isometrics_overlay(pixel_coordinate pixel, map_point point);
void draw_ornaments_overlay(pixel_coordinate pixel, map_point point);
void draw_figures_overlay(pixel_coordinate pixel, map_point point);

#endif // WIDGET_CITY_WITHOUT_OVERLAY_H
