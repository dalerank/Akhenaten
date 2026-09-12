#pragma once

#include "building/building.h"

class building_festival_square : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_FESTIVAL_SQUARE, building_festival_square, building_impl)

    virtual building_festival_square *dcast_festival_square() override { return this; }

    struct runtime_data_t {
        int booth_corner_grid_offset;
        uint8_t num_shows;
        uint8_t juggler_visited;
        uint8_t musician_visited;
        uint8_t dancer_visited;
    } BUILDING_RUNTIME_DATA_T;

    virtual void on_place_update_tiles(int orientation, int variant) override;
    virtual void update_day() override;
    virtual void on_undo() override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    virtual void update_map_orientation(int map_orientation) override;
    virtual bool target_route_tile_blocked(int grid_offset) const override;
};
ANK_CONFIG_PROPERTY(building_festival_square::runtime_data_t, num_shows)