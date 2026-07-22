#pragma once

#include "city_overlay.h"

#include <cstdint>

struct city_overlay_architect_reach : public city_overlay_t<OVERLAY_ARCHITECT_REACH> {
    city_overlay_architect_reach();

    virtual bool show_figure(const figure *f) const override;
    virtual int get_column_height(const building *b) const override;
    virtual bool draw_custom_footprint(vec2i pixel, tile2i point, painter &ctx) const override;
    virtual bool show_building(const building *b) const override;
    virtual void get_tooltip(tooltip_context *c, tile2i tile, xstring &tooltip) override;

    building_id source_building_id() const { return source_bid; }

private:
    void ensure_up_to_date() const;

    mutable building_id source_bid = 0;
    mutable uint32_t last_update_frame = UINT32_MAX;
    mutable int last_max_tiles = 0;
};
