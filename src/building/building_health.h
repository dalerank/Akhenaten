#pragma once

#include "building/building.h"

class building_apothecary : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_APOTHECARY, building_apothecary)

    building_apothecary(building &b) : building_impl(b) {}
    virtual building_apothecary *dcast_apothecary() override { return this; }

    virtual void window_info_background(object_info &c) override;
    virtual void spawn_figure() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_APOTHECARY; }
    virtual int animation_speed(int speed) const override { return 3; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};

void building_dentist_draw_info(object_info& c);
void building_mortuary_draw_info(object_info& c);