#pragma once

#include "city_overlay.h"

struct city_overlay_education : public city_overlay_t<OVERLAY_EDUCATION> {
    virtual int get_column_height(const building *b) const override;
    virtual xstring get_tooltip_for_building(tooltip_context *c, const building *b) override;
};

struct city_overlay_academy : public city_overlay_t<OVERLAY_ACADEMY> {
    virtual int get_column_height(const building *b) const override;
    virtual xstring get_tooltip_for_building(tooltip_context *c, const building *b) override;
};

struct city_overlay_libraries : public city_overlay_t<OVERLAY_LIBRARY> {
    virtual int get_column_height(const building *b) const override;
    virtual xstring get_tooltip_for_building(tooltip_context *c, const building *b) override;
};
