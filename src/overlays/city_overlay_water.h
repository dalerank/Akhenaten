#pragma once

#include "overlays/city_overlay.h"

struct city_overlay_water : public city_overlay_t<OVERLAY_WATER> {
    virtual void draw_custom_top(vec2i pixel, tile2i tile, painter &ctx) const override;
    virtual bool draw_custom_footprint(vec2i pixel, tile2i point, painter &ctx) const override;
    virtual xstring get_tooltip(tooltip_context* c, tile2i) const override;
    virtual int get_column_height(const building *b) const override;
    virtual void draw_overlay_building_column(building *b, vec2i pixel, tile2i tile, painter &ctx) const override {
        // do nothing
    }
};