#pragma once

#include "city_overlay.h"

struct city_overlay_apothecary : public city_overlay {
    city_overlay_apothecary();

    bool show_figure(const figure *f) const override;
    int get_column_height(const building *b) const override;
    int get_tooltip_for_building(tooltip_context *c, const building *b) const override;
    void draw_custom_top(vec2i pixel, tile2i tile, painter &ctx) const override;
    bool show_building(const building *b) const override;
};

city_overlay* city_overlay_for_apothecary();
