#ifndef WIDGET_CITY_WITHOUT_OVERLAY_H
#define WIDGET_CITY_WITHOUT_OVERLAY_H

#include "city/view/view.h"
#include "graphics/color.h"
#include "building/building.h"

void init_draw_context(int selected_figure_id, pixel_coordinate *figure_coord, int highlighted_formation);

void draw_flattened_footprint_anysize(int x, int y, int size_x, int size_y, int image_offset, color_t color_mask);
void draw_flattened_footprint_building(const building *b, int x, int y, int image_offset, color_t color_mask);

void draw_empty_tile(pixel_coordinate pixel, map_point point);

void draw_footprint(pixel_coordinate pixel, map_point point);
void draw_top(pixel_coordinate pixel, map_point point);
void draw_ornaments(pixel_coordinate pixel, map_point point);
void draw_figures(pixel_coordinate pixel, map_point point);
void draw_elevated_figures(pixel_coordinate pixel, map_point point);

void draw_footprint_overlay(pixel_coordinate pixel, map_point point);
void draw_top_overlay(pixel_coordinate pixel, map_point point);
void draw_ornaments_overlay(pixel_coordinate pixel, map_point point);
void draw_figures_overlay(pixel_coordinate pixel, map_point point);
void draw_elevated_figures_overlay(pixel_coordinate pixel, map_point point);

void draw_debug(pixel_coordinate pixel, map_point point);
void draw_debug_figures(pixel_coordinate pixel, map_point point);

void deletion_draw_top(pixel_coordinate pixel, map_point point);
void deletion_draw_figures_animations(pixel_coordinate pixel, map_point point);

#endif // WIDGET_CITY_WITHOUT_OVERLAY_H
