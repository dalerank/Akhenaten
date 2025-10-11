#pragma once

#include "building/building.h"

class building_scribal_school : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_SCRIBAL_SCHOOL, building_scribal_school, building_impl);
    virtual building_scribal_school *dcast_scribal_school() override { return this; }

    virtual void spawn_figure() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_SCRIBAL_SCHOOL; }
    virtual void update_graphic() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual void update_month() override;
    virtual void on_place_checks() override;
    virtual bool add_resource(e_resource resource, int amount) override;
};