#pragma once

#include "city_overlay.h"

struct city_overlay_food_stocks : public city_overlay_t<OVERLAY_FOOD_STOCKS> {
    virtual int get_column_height(const building *b) const override;
    virtual xstring get_tooltip_for_building(tooltip_context *c, const building *b) override;
    virtual bool show_figure(const figure *f) const override;
};
