#pragma once

#include "building/building.h"
#include "figure/figure.h"
#include "graphics/elements/tooltip.h"

#define NO_COLUMN -1

enum e_column_type {
    COLUMN_TYPE_RISK,
    COLUMN_TYPE_WATER_ACCESS
};

enum e_column_color {
    COLUMN_COLOR_PLAIN = 0,
    COLUMN_COLOR_YELLOW = 3,
    COLUMN_COLOR_ORANGE = 6,
    COLUMN_COLOR_RED = 9,
    COLUMN_COLOR_BLUE = 12,
};

struct city_overlay {
    int type = -1;
    int column_type = -1;
    int (*show_building_func)(const building *b) = 0;
    int (*show_figure)(const figure *f) = 0;
    int (*get_column_height)(const building *b) = 0;
    int (*get_tooltip_for_grid_offset)(tooltip_context *c, int grid_offset) = 0;
    int (*get_tooltip_for_building)(tooltip_context *c, const building *b) = 0;
    void (*draw_custom_footprint)(pixel_coordinate pixel, map_point point) = 0;
    void (*draw_custom_top_func)(pixel_coordinate pixel, map_point point) = 0;

    city_overlay() {}
    city_overlay(
        int _type,
        int _column_type,
        int (*_show_building_func)(const building *b),
        int (*_show_figure)(const figure *f),
        int (*_get_column_height)(const building *b),
        int (*_get_tooltip_for_grid_offset)(tooltip_context *c, int grid_offset),
        int (*_get_tooltip_for_building)(tooltip_context *c, const building *b),
        void (*_draw_custom_footprint)(pixel_coordinate pixel, map_point point),
        void (*_draw_custom_top)(pixel_coordinate pixel, map_point point)) {
        type = _type;
        column_type = _column_type;
        show_building_func = _show_building_func;
        show_figure = _show_figure;
        get_column_height = _get_column_height;
        get_tooltip_for_grid_offset = _get_tooltip_for_grid_offset;
        get_tooltip_for_building = _get_tooltip_for_building;
        draw_custom_footprint = _draw_custom_footprint;
        draw_custom_top_func = _draw_custom_top;
    }

    virtual void draw_custom_top(pixel_coordinate pixel, map_point point) const {
        if (draw_custom_top_func) {
            draw_custom_top_func(pixel, point);
        }
    }

    virtual bool show_building(const building *b) const {
       return !!show_building_func(b);
    }
};

const city_overlay *get_city_overlay(void);
bool select_city_overlay(void);
int widget_city_overlay_get_tooltip_text(tooltip_context *c, int grid_offset);

void city_with_overlay_draw_building_footprint(int x, int y, int grid_offset, int image_offset);
void city_with_overlay_draw_building_top(pixel_coordinate pixel, map_point point);