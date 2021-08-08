#ifndef WIDGET_CITY_WITHOUT_OVERLAY_H
#define WIDGET_CITY_WITHOUT_OVERLAY_H

//#include "map/point.h"
//#include "widget/city.h"

void init_draw_context(int selected_figure_id, pixel_coordinate *figure_coord, int highlighted_formation);

void draw_footprint(int x, int y, int grid_offset);
void draw_top(int x, int y, int grid_offset);
void draw_figures(int x, int y, int grid_offset);

void draw_debug(int x, int y, int grid_offset);
void draw_debug_figures(int x, int y, int grid_offset);

void deletion_draw_top(int x, int y, int grid_offset);
void draw_elevated_figures(int x, int y, int grid_offset);
void deletion_draw_figures_animations(int x, int y, int grid_offset);

#endif // WIDGET_CITY_WITHOUT_OVERLAY_H
