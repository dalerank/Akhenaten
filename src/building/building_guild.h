#pragma once

#include "building/building.h"

class building_guild : public building_impl {
public:
    building_guild(building &b) : building_impl(b) {}
    virtual building_guild *dcast_guild() override { return this; }

    struct runtime_data_t {
        uint8_t max_workers;
    };

    runtime_data_t &runtime_data() { return *(runtime_data_t *)data.data; }
    const runtime_data_t &runtime_data() const { return *(runtime_data_t *)data.data; }

    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
};