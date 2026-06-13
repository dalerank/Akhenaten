#pragma once

#include "city_overlay.h"

struct city_overlay_crime : public city_overlay_t<OVERLAY_CRIME> {
    city_overlay_crime() { es_name = "overlay_crime"; }

    virtual bool show_figure(const figure *f) const override;
    virtual int get_column_height(const building *b) const override;
    virtual bool draw_custom_footprint(vec2i pixel, tile2i point, painter &ctx) const override;
    virtual bool show_building(const building *b) const override;
};

struct city_overlay_criminal : public city_overlay_t<OVERLAY_CRIMINAL> {
    city_overlay_criminal() { es_name = "overlay_criminal"; }

    virtual bool show_figure(const figure *f) const override;
    virtual int get_column_height(const building *b) const override;
    virtual void draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const override;
    virtual bool show_building(const building *b) const override;
};