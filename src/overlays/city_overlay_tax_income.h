#pragma once

#include "overlays/city_overlay.h"

struct city_overlay_tax_income : public city_overlay_t<OVERLAY_TAX_INCOME> {
    virtual int get_column_height(const building *b) const override;
    virtual xstring get_tooltip_for_building(tooltip_context *c, const building *b) override;
};