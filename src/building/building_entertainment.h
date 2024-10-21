#pragma once

#include "building/building.h"

class building_entertainment : public building_impl {
public:
    building_entertainment(building &b) : building_impl(b) {}
    virtual building_entertainment *dcast_entertainment() override { return this; }

    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
};