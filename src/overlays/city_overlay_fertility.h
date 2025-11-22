#pragma once

#include "city_overlay.h"

struct city_overlay_fertility : public city_overlay_t<OVERLAY_FERTILITY> {
    virtual bool show_figure(const figure *f) const override;
    virtual void draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const override;
    virtual xstring get_tooltip(tooltip_context *c, tile2i) const override;
    virtual xstring get_tooltip_for_building(tooltip_context *c, const building *b) override;
    virtual int get_column_height(const building *b) const override;
    virtual bool show_building(const building *b) const override;
};