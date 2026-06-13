#pragma once

#include "city_overlay.h"

struct city_overlay_desirability : public city_overlay_t<OVERLAY_DESIRABILITY> {
    city_overlay_desirability() { es_name = "overlay_desirability"; }

    virtual bool show_figure(const figure *f) const override;
    virtual int get_column_height(const building *b) const override;
    virtual void draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const override;
    virtual bool draw_custom_footprint(vec2i pixel, tile2i point, painter &ctx) const override;
    virtual bool show_building(const building *b) const override;
};