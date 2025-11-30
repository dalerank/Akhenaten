#pragma once

#include "city_overlay.h"

struct city_overlay_fire : public city_overlay_t<OVERLAY_FIRE> {
    virtual int get_column_height(const building *b) const override;
    virtual xstring get_tooltip_for_building(tooltip_context *c, const building *b) override;
    virtual color color_mask_building(const building *b) const override;
    virtual bool show_building(const building *b) const override;
};
