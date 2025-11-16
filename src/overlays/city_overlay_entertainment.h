#pragma once

#include "overlays/city_overlay.h"

struct city_overlay_entertainment : public city_overlay_t<OVERLAY_ENTERTAINMENT> {
    virtual int get_column_height(const building *b) const override;
    virtual xstring get_tooltip_for_building(tooltip_context *c, const building *b) override;
};

struct city_overlay_senet_house : public city_overlay_t<OVERLAY_SENET_HOUSE> {
    virtual int get_column_height(const building *b) const override;
    virtual xstring get_tooltip_for_building(tooltip_context *c, const building *b) override;
};