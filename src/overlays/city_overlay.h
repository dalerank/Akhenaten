#pragma once

#include "building/building.h"
#include "figure/figure.h"
#include "graphics/elements/tooltip.h"

constexpr int NO_COLUMN = -1;

enum e_column_type {
    COLUMN_TYPE_RISK,
    COLUMN_TYPE_POSITIVE,
    COLUMN_TYPE_WATER_ACCESS
};

enum e_column_color {
    COLUMN_COLOR_PLAIN = 0,
    COLUMN_COLOR_YELLOW = 3,
    COLUMN_COLOR_ORANGE = 6,
    COLUMN_COLOR_RED = 9,
    COLUMN_COLOR_BLUE = 12,
};

enum e_overlay {
    OVERLAY_NONE = 0,
    OVERLAY_WATER = 2,
    OVERLAY_RELIGION = 4,
    OVERLAY_FIRE = 8,
    OVERLAY_DAMAGE = 9,
    OVERLAY_CRIME = 10,
    OVERLAY_ENTERTAINMENT = 11,
    OVERLAY_BOOTH = 12,
    OVERLAY_BANDSTAND = 13,
    OVERLAY_PAVILION = 14,
    OVERLAY_HIPPODROME = 15,
    OVERLAY_EDUCATION = 16,
    OVERLAY_SCHOOL = 17,
    OVERLAY_LIBRARY = 18,
    OVERLAY_ACADEMY = 19,
    OVERLAY_APOTHECARY = 20,
    OVERLAY_DENTIST = 21,
    OVERLAY_PHYSICIAN = 22,
    OVERLAY_MORTUARY = 23,
    OVERLAY_TAX_INCOME = 24,
    OVERLAY_FOOD_STOCKS = 25,
    OVERLAY_DESIRABILITY = 26,
    OVERLAY_WORKERS_UNUSED = 27,
    OVERLAY_NATIVE = 28,
    OVERLAY_PROBLEMS = 29,
    OVERLAY_RELIGION_OSIRIS = 30,
    OVERLAY_RELIGION_RA = 31,
    OVERLAY_RELIGION_PTAH = 32,
    OVERLAY_RELIGION_SETH = 33,
    OVERLAY_RELIGION_BAST = 34,
    OVERLAY_FERTILITY = 35,
    OVERLAY_BAZAAR_ACCESS = 36,
    OVERLAY_ROUTING = 37,
    OVERLAY_HEALTH = 38,
    OVERLAY_LABOR = 39,
};

inline bool show_figure_none(const figure *f) { return false; }
inline int get_column_height_none(const building* b) { return NO_COLUMN; }

struct city_overlay {
    int type = -1;
    int column_type = -1;
    int (*show_building_func)(const building* b) = 0;
    int (*show_figure_func)(const figure* f) = 0;
    int (*get_column_height)(const building* b) = 0;
    int (*get_tooltip_for_grid_offset)(tooltip_context* c, int grid_offset) = 0;
    int (*get_tooltip_for_building)(tooltip_context* c, const building* b) = 0;
    void (*draw_custom_footprint)(vec2i pixel, map_point point) = 0;
    void (*draw_custom_top_func)(vec2i pixel, map_point point) = 0;

    city_overlay() {}
    city_overlay(int _type,
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

const city_overlay* get_city_overlay(void);
bool select_city_overlay();
int widget_city_overlay_get_tooltip_text(tooltip_context* c, int grid_offset);

void city_with_overlay_draw_building_footprint(int x, int y, int grid_offset, int image_offset);
void city_with_overlay_draw_building_top(vec2i pixel, map_point point);