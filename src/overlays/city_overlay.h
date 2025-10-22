#pragma once

#include "building/building.h"
#include "graphics/elements/tooltip.h"
#include "core/vec2i.h"
#include "city_overlay_fwd.h"
#include "core/xstring.h"
#include "core/svector.h"
#include "core/tokenum.h"

extern const token_holder<e_overlay, OVERLAY_NONE, OVERLAY_SIZE> e_overlay_tokens;
extern const token_holder<e_column_type, COLUMN_TYPE_RISK, COLUMN_TYPE_SIZE> e_column_type_tokens;

class figure;
class building;
struct painter;

inline bool show_figure_none(const figure *f) { return false; }
using overlay_list = std::array<struct city_overlay *, OVERLAY_SIZE>;

struct city_overlay {
    e_overlay id;
    svector<e_figure_type, 10> walkers;
    svector<e_building_type, 10> buildings;
    e_column_type column_type = COLUMN_TYPE_NONE;
    animation_t column_anim;
    xstring caption;

    city_overlay(e_overlay t);

    virtual bool show_figure(const figure *f) const;
    virtual int get_column_height(const building *b) const { return COLUMN_TYPE_NONE; }
    virtual e_column_color get_column_color(const building *b) const { return COLUMN_COLOR_NONE; }
    virtual xstring get_tooltip(tooltip_context *c, tile2i tile) const { return {}; }
    virtual xstring get_tooltip_for_building(tooltip_context *c, const building *b) const { return {}; }
    virtual bool draw_custom_footprint(vec2i pixel, tile2i point, painter &ctx) const { return false; }
    virtual void draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const;
    virtual bool show_building(const building *b) const;
    virtual e_overlay get_type() const { return OVERLAY_NONE; }
    virtual void draw_building_top(vec2i pixel, tile2i tile, painter &ctx) const;
    virtual void draw_overlay_building_column(building *b, vec2i pixel, tile2i tile, painter &ctx) const;

    xstring title() const;
    void draw_overlay_column(e_column_color c, vec2i pixel, int height, int column_style, painter &ctx) const;
    void draw_building_footprint(painter &ctx, vec2i pos, tile2i tile, int image_offset) const;
    bool is_drawable_farm_corner(tile2i tile) const;
    bool is_drawable_building_corner(tile2i tile, tile2i main, int size) const;
    bool is_drawable_farmhouse(tile2i tile, int map_orientation) const;
    void draw_flattened_footprint_anysize(vec2i pos, int size_x, int size_y, int image_offset, color color_mask, painter &ctx) const;
    void draw_flattened_footprint_building(const building *b, vec2i pos, int image_offset, color color_mask, painter &ctx) const;

    static city_overlay *get(e_overlay e);
    static overlay_list &overlays();
};
ANK_CONFIG_STRUCT(city_overlay, id, walkers, buildings, column_type, column_anim, caption)

template<e_overlay TYPE>
struct city_overlay_t : public city_overlay {
    virtual e_overlay get_type() const override { return TYPE; }

    city_overlay_t() : city_overlay(TYPE) {}
};
