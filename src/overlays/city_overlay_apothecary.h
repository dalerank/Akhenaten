#pragma once

#include "city_overlay.h"

struct city_overlay_apothecary : public city_overlay_t<OVERLAY_APOTHECARY> {
    virtual int get_column_height(const building *b) const override;
    virtual xstring get_tooltip_for_building(tooltip_context *c, const building *b) const override;
};

city_overlay* city_overlay_for_apothecary();
