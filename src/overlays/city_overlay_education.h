#pragma once

#include "city_overlay.h"

struct city_overlay_education : public city_overlay {
    city_overlay_education();

    virtual int get_column_height(const building *b) const override;
    virtual int get_tooltip_for_building(tooltip_context *c, const building *b) const override;
    virtual bool show_building(const building *b) const override;
    virtual bool show_figure(const figure *f) const override;
};

struct city_overlay_academy : public city_overlay {
    city_overlay_academy();

    virtual bool show_figure(const figure *f) const override;
    virtual int get_tooltip_for_building(tooltip_context *c, const building *b) const override;
    virtual int get_column_height(const building *b) const override;
    bool show_building(const building *b) const override;
};

struct city_overlay_libraries : public city_overlay {
    city_overlay_libraries();

    virtual bool show_figure(const figure *f) const;
    virtual int get_column_height(const building *b) const override;
    virtual int get_tooltip_for_building(tooltip_context *c, const building *b) const override;
    bool show_building(const building *b) const override;
};

city_overlay* city_overlay_for_education();
city_overlay* city_overlay_for_scribal_school();
city_overlay* city_overlay_for_library();
city_overlay* city_overlay_for_academy();
