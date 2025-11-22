#pragma once

#include "building/building.h"

class building_entertainment : public building_impl {
public:
    building_entertainment(building &b) : building_impl(b) {}
    virtual building_entertainment *dcast_entertainment() override { return this; }

    struct runtime_data_t {
        uint8_t spawned_entertainer_days;
        uint8_t num_shows;
        uint8_t juggler_visited;
        uint8_t musician_visited;
        uint8_t dancer_visited;
        uint8_t play_index;
        uint32_t booth_corner_grid_offset;
        uint32_t latched_venue_main_grid_offset;
        uint32_t latched_venue_add_grid_offset;
        uint8_t conservatory_help;
        bool spawned_special_figure;
        e_resource consume_material_id;
        uint16_t visitors_today;
        uint16_t visitors_month;
        uint16_t visitors_annual;
    } BUILDING_RUNTIME_DATA_T;

    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    void place_latch_on_venue(e_building_type type, int dx, int dy, int orientation, bool main_venue = false);
    int bandstand_main_img_offset(int orientation);
    int bandstand_add_img_offset(int orientation);
};