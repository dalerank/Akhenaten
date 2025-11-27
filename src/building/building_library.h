#pragma once

#include "building/building.h"

class building_library : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_LIBRARY, building_library, building_impl);

    virtual void spawn_figure() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_LIBRARY; }
    virtual void update_graphic() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
};