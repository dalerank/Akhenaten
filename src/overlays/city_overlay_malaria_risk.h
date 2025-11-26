#pragma once

#include "city_overlay.h"

struct city_overlay_malaria_risk : public city_overlay_t<OVERLAY_MALARIA_RISK> {
    virtual int get_column_height(const building *b) const override;
    virtual xstring get_tooltip_for_building(tooltip_context *c, const building *b) override;
    virtual void draw_custom_top(vec2i pixel, tile2i tile, painter &ctx) const override;
};

