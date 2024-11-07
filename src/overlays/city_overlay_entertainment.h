#pragma once

#include "overlays/city_overlay.h"

city_overlay* city_overlay_for_entertainment();
struct city_overlay_entertainment : public city_overlay {
    city_overlay_entertainment();

    virtual int get_column_height(const building *b) const override;
    virtual xstring get_tooltip_for_building(tooltip_context *c, const building *b) const override;
};

city_overlay* city_overlay_for_senet_house();
struct city_overlay_senet_house : public city_overlay {
    city_overlay_senet_house();

    virtual int get_column_height(const building *b) const override;
    virtual xstring get_tooltip_for_building(tooltip_context *c, const building *b) const override;
};