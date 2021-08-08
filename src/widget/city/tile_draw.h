#ifndef WIDGET_CITY_WITHOUT_OVERLAY_H
#define WIDGET_CITY_WITHOUT_OVERLAY_H

#include "city/view.h"
#include "graphics/color.h"

void init_draw_context(int selected_figure_id, pixel_coordinate *figure_coord, int highlighted_formation);

int get_farm_image(int grid_offset);
void draw_ph_crops(int type, int progress, int grid_offset, int x, int y, color_t color_mask);

void draw_footprint(int x, int y, int grid_offset);
void draw_top(int x, int y, int grid_offset);
void draw_ornaments(int x, int y, int grid_offset);
void draw_figures(int x, int y, int grid_offset);
void draw_elevated_figures(int x, int y, int grid_offset);

void draw_footprint_overlay(int x, int y, int grid_offset);
void draw_top_overlay(int x, int y, int grid_offset);
void draw_ornaments_overlay(int x, int y, int grid_offset);
void draw_figures_overlay(int x, int y, int grid_offset);
void draw_elevated_figures_overlay(int x, int y, int grid_offset);

void draw_debug(int x, int y, int grid_offset);
void draw_debug_figures(int x, int y, int grid_offset);

void deletion_draw_top(int x, int y, int grid_offset);
void deletion_draw_figures_animations(int x, int y, int grid_offset);

#endif // WIDGET_CITY_WITHOUT_OVERLAY_H
