#pragma once

#include "building/building.h"

class building_scribal_school : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_SCRIBAL_SCHOOL, building_scribal_school);
    building_scribal_school(building &b) : building_impl(b) {}

    virtual void on_create(int orientation) override;
    virtual void window_info_background(object_info &c) override;
    virtual void spawn_figure() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_SCRIBAL_SCHOOL; }
    virtual void update_day() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color mask) override;
    virtual void update_month() override;
    virtual void on_place_checks() override;
};