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
struct painter;

inline bool show_figure_none(const figure *f) { return false; }
inline int get_column_height_none(const building* b) { return NO_COLUMN; }

struct city_overlay {
    e_overlay type = OVERLAY_NONE;
    int column_type = -1;
    int (*show_figure_func)(const figure* f) = 0;
    int (*get_column_height_func)(const building* b) = 0;
    int (*get_tooltip_for_grid_offset_func)(tooltip_context* c, int grid_offset) = 0;
    int (*get_tooltip_for_building_func)(tooltip_context* c, const building* b) = 0;
    void (*draw_custom_footprint_func)(vec2i pixel, tile2i point, painter &ctx) = 0;
    void (*draw_custom_top_func)(vec2i pixel, tile2i point, painter &ctx) = 0;

    int tooltip_base;
    svector<int, 10> tooltips;
    bstring64 caption;
    svector<e_figure_type, 4> walkers;
    svector<e_building_type, 10> buildings;

    city_overlay() {}
    city_overlay(e_overlay _type,
                 int _column_type,
                 int (*_show_figure)(const figure* f),
                 int (*_get_column_height)(const building* b),
                 int (*_get_tooltip_for_grid_offset)(tooltip_context* c, int grid_offset),
                 int (*_get_tooltip_for_building)(tooltip_context* c, const building* b),
                 void (*_draw_custom_footprint)(vec2i pixel, tile2i point, painter &ctx),
                 void (*_draw_custom_top)(vec2i pixel, tile2i point, painter &ctx)) {
        type = _type;
        column_type = _column_type;
        show_figure_func = _show_figure;
        get_column_height_func = _get_column_height;
        get_tooltip_for_grid_offset_func = _get_tooltip_for_grid_offset;
        get_tooltip_for_building_func = _get_tooltip_for_building;
        draw_custom_footprint_func = _draw_custom_footprint;
        draw_custom_top_func = _draw_custom_top;
    }

    virtual bool show_figure(const figure* f) const {
        if (show_figure_func) {
            return show_figure_func(f);
        }

        return false;
    }

    virtual int get_column_height(const building *b) const {
        if (get_column_height_func) {
            return get_column_height_func(b);
        }

        return 0;
    }

    virtual int get_tooltip_for_grid_offset(tooltip_context* c, int grid_offset) const {
        if (get_tooltip_for_grid_offset_func) {
            return get_tooltip_for_grid_offset_func(c, grid_offset);
        }

        return 0;
    }

    virtual int get_tooltip_for_building(tooltip_context* c, const building* b) const {
        if (get_tooltip_for_building_func) {
            return get_tooltip_for_building_func(c, b);
        }

        return 0;
    }

    virtual bool draw_custom_footprint(vec2i pixel, tile2i point, painter &ctx) const {
        if (draw_custom_footprint_func) {
            draw_custom_footprint_func(pixel, point, ctx);
            return true;
        }

        return false;
    }

    virtual void draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const {
        if (draw_custom_top_func) {
            draw_custom_top_func(pixel, point, ctx);
        }
    }

    virtual bool show_building(const building* b) const {
        return false;
    }

    void draw_building_top(vec2i pixel, tile2i tile, painter &ctx) const;
    void draw_overlay_column(vec2i pixel, int height, int column_style, painter &ctx) const;
    void draw_building_footprint(painter &ctx, vec2i pos, tile2i tile, int image_offset) const;
    bool is_drawable_farm_corner(tile2i tile) const;
    bool is_drawable_storage_yard_corner(tile2i tile) const;
    bool is_drawable_farmhouse(tile2i tile, int map_orientation) const;
    void draw_flattened_footprint_anysize(vec2i pos, int size_x, int size_y, int image_offset, color color_mask, painter &ctx) const;
    void draw_flattened_footprint_building(const building *b, vec2i pos, int image_offset, color color_mask, painter &ctx) const;
};

const city_overlay* get_city_overlay();
city_overlay *get_city_overlay(e_overlay e);
bool select_city_overlay();
int widget_city_overlay_get_tooltip_text(tooltip_context* c, int grid_offset);