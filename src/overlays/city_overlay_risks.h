#pragma once

#include "city_overlay.h"

struct city_overlay_problems : public city_overlay_t<OVERLAY_PROBLEMS> {
    virtual bool show_figure(const figure *f) const override;
    virtual int get_column_height(const building *b) const override;
    //void draw_custom_top(vec2i pixel, tile2i tile, painter &ctx) const override;

    virtual bool show_building(const building *b) const override;
};

struct city_overlay_native : public city_overlay_t<OVERLAY_NATIVE> {
    virtual void draw_custom_top(vec2i pixel, tile2i tile, painter &ctx) const override;
    virtual bool draw_custom_footprint(vec2i pixel, tile2i point, painter &ctx) const override;
    virtual int get_column_height(const building *b) const override;
    virtual bool show_building(const building *b) const override;
};

void overlay_problems_prepare_building(building* b);