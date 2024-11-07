#pragma once

#include "overlays/city_overlay.h"

struct city_overlay_schools : public city_overlay {
    city_overlay_schools();

    virtual int get_column_height(const building *b) const override;
    virtual xstring get_tooltip_for_building(tooltip_context *c, const building *b) const override;
};