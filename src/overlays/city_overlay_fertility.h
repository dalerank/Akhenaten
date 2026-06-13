#pragma once

#include "city_overlay.h"

struct city_overlay_fertility : public city_overlay_t<OVERLAY_FERTILITY> {
    city_overlay_fertility() { es_name = "overlay_fertility"; }

    virtual bool show_figure(const figure *f) const override;
    virtual void draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const override;
    virtual int get_column_height(const building *b) const override;
    virtual bool show_building(const building *b) const override;
};