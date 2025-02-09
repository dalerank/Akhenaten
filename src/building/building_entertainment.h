#pragma once

#include "building/building.h"

class building_entertainment : public building_impl {
public:
    building_entertainment(building &b) : building_impl(b) {}
    virtual building_entertainment *dcast_entertainment() override { return this; }

    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    void place_latch_on_venue(e_building_type type, int dx, int dy, int orientation, bool main_venue = false);
    int bandstand_main_img_offset(int orientation);
    int bandstand_add_img_offset(int orientation);
};