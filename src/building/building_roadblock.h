#pragma once

#include "building/building.h"
#include "city/constants.h"

class building_routeblock : public building_impl {
public:
    building_routeblock(building &b) : building_impl(b) {}

    struct runtime_data_t {
        short exceptions;
    };

    virtual building_routeblock *dcast_routeblock() override { return this; }

    virtual void set_permission(e_permission) {}
    virtual bool get_permission(e_permission) { return false; }

    runtime_data_t &runtime_data() { return *(runtime_data_t *)data.data; }
    const runtime_data_t &runtime_data() const { return *(runtime_data_t *)data.data; }
};

class building_roadblock : public building_routeblock {
public:
    BUILDING_METAINFO(BUILDING_ROADBLOCK, building_roadblock)
    building_roadblock(building &b) : building_routeblock(b) {}

    virtual building_roadblock *dcast_roadblock() override { return this; }

    virtual void on_place_checks() override;
    virtual bool force_draw_flat_tile(painter &ctx, tile2i tile, vec2i pixel, color mask) override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    virtual void set_permission(e_permission p) override;
    virtual bool get_permission(e_permission p) override;
};