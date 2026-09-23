#pragma once

#include "building/building.h"

class building_guild : public building_impl {
public:
    using inherited = building_impl;

    building_guild(building &b) : building_impl(b) {}
    virtual building_guild *dcast_guild() override { return this; }

    struct runtime_data_t {
        uint8_t max_walkers;
    } BUILDING_RUNTIME_DATA_T;

    virtual void on_create(int orientation) override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;

    bool has_resources() const;
};

ANK_CONFIG_PROPERTY(building_guild::runtime_data_t, max_walkers)
