#ifndef WIDGET_CITY_WITH_OVERLAY_H
#define WIDGET_CITY_WITH_OVERLAY_H

#include "graphics/tooltip.h"
#include "map/point.h"
#include "widget/city.h"

/**
 * Update the internal state after changing overlay
 */
void city_without_overlay_draw(int selected_figure_id, pixel_coordinate *figure_coord, const map_tile *tile);
void city_with_overlay_update(void);

void city_with_overlay_draw(const map_tile *tile);

int city_with_overlay_get_tooltip_text(tooltip_context *c, int grid_offset);

#endif // WIDGET_CITY_WITH_OVERLAY_H
