#pragma once

#include "building/building.h"

class building_wharf : public building_impl {
public:
    building_wharf(building &b) : building_impl(b) {}

    virtual building_wharf *dcast_wharf() override { return this; }

    virtual void on_create(int orientation) override;
    virtual void on_place(int orientation, int variant) override;
    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void on_tick(bool refresh_only) override;
    virtual void update_map_orientation(int orientation) override;
    virtual void highlight_waypoints() override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    virtual void update_graphic() override;
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
    virtual int get_orientation() const override { return data.dock.orientation; }

    virtual bool ship_moored() const { return false; }
};

