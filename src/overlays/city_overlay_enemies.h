#pragma once

#include "city_overlay.h"

struct city_overlay_enemies : public city_overlay_t<OVERLAY_ENEMIES> {
    virtual bool show_figure(const figure *f) const override;
    virtual int get_column_height(const building *b) const override;
    virtual bool show_building(const building *b) const override;
};
