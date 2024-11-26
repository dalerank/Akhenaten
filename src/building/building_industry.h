#pragma once

#include "building/building.h"

class building_industry : public building_impl {
public:
    building_industry(building &b) : building_impl(b) {}
    virtual building_industry *dcast_industry() override { return this; }

    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    virtual void update_graphic() override;
    virtual void on_create(int orientation) override;
};