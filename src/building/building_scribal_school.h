#pragma once

#include "building/building.h"

class building_scribal_school : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_SCRIBAL_SCHOOL, building_scribal_school, building_impl);
    virtual building_scribal_school *dcast_scribal_school() override { return this; }

    virtual void spawn_figure() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_SCRIBAL_SCHOOL; }
    virtual bool add_resource(e_resource resource, int amount) override;
};