#pragma once

#include "city_overlay.h"

struct city_overlay_fire : public city_overlay {
public:
    city_overlay_fire();

    virtual int get_column_height(const building *b) const override;
    virtual xstring get_tooltip_for_building(tooltip_context *c, const building *b) const override;
};

city_overlay* city_overlay_for_fire();