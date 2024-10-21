#pragma once

#include "building/building.h"

class building_guild : public building_impl {
public:
    building_guild(building &b) : building_impl(b) {}
    virtual building_guild *dcast_guild() override { return this; }

    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
};