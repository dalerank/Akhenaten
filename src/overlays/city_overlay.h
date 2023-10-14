#pragma once

#include "building/building.h"
#include "graphics/elements/tooltip.h"
#include "core/vec2i.h"
#include "city_overlay_fwd.h"
#include "core/bstring.h"
#include "core/svector.h"

constexpr int NO_COLUMN = -1;

class figure;
class building;

inline bool show_figure_none(const figure *f) { return false; }
inline int get_column_height_none(const building* b) { return NO_COLUMN; }

struct city_overlay {
    e_overlay type = OVERLAY_NONE;
    int column_type = -1;
    int (*show_building_func)(const building* b) = 0;
    int (*show_figure_func)(const figure* f) = 0;
    int (*get_column_height)(const building* b) = 0;
    int (*get_tooltip_for_grid_offset)(tooltip_context* c, int grid_offset) = 0;
    int (*get_tooltip_for_building)(tooltip_context* c, const building* b) = 0;
    void (*draw_custom_footprint)(vec2i pixel, map_point point) = 0;
    void (*draw_custom_top_func)(vec2i pixel, map_point point) = 0;

    int tooltip_base;
    svector<int, 10> tooltips;
    bstring64 caption;
    svector<e_figure_type, 4> walkers;
    svector<e_building_type, 10> buildings;

    city_overlay() {}
    city_overlay(e_overlay _type,
                 int _column_type,
                 int (*_show_building_func)(const building* b),
                 int (*_show_figure)(const figure* f),
                 int (*_get_column_height)(const building* b),
                 int (*_get_tooltip_for_grid_offset)(tooltip_context* c, int grid_offset),
                 int (*_get_tooltip_for_building)(tooltip_context* c, const building* b),
                 void (*_draw_custom_footprint)(vec2i pixel, map_point point),
                 void (*_draw_custom_top)(vec2i pixel, map_point point)) {
        type = _type;
        column_type = _column_type;
        show_building_func = _show_building_func;
        show_figure_func = _show_figure;
        get_column_height = _get_column_height;
        get_tooltip_for_grid_offset = _get_tooltip_for_grid_offset;
        get_tooltip_for_building = _get_tooltip_for_building;
        draw_custom_footprint = _draw_custom_footprint;
        draw_custom_top_func = _draw_custom_top;
    }

    virtual bool show_figure(const figure* f) const {
        if (show_figure_func) {
            return show_figure_func(f);
        }

        return false;
    }

    virtual void draw_custom_top(vec2i pixel, map_point point) const {
        if (draw_custom_top_func) {
            draw_custom_top_func(pixel, point);
        }
    }

    virtual bool show_building(const building* b) const {
        return !!show_building_func(b);
    }
};

const city_overlay* get_city_overlay();
city_overlay *get_city_overlay(e_overlay e);
bool select_city_overlay();
int widget_city_overlay_get_tooltip_text(tooltip_context* c, int grid_offset);

void city_with_overlay_draw_building_footprint(int x, int y, int grid_offset, int image_offset);
void city_with_overlay_draw_building_top(vec2i pixel, map_point point);