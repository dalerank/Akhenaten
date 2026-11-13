#pragma once

#include "building/building.h"

struct venue_place_offset {
    struct item {
        e_building_type type = BUILDING_NONE;
        vec2i offset;
        bool main = false;
    };
    svector<item, 8> items;
};
ANK_CONFIG_STRUCT(venue_place_offset::item, type, offset, main)
ANK_CONFIG_STRUCT(venue_place_offset, items)

class building_entertainment : public building_impl {
public:
    using inherited = building_impl;

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

    virtual void on_post_load() override;
    virtual void bind_dynamic(io_buffer *iob, size_t version) override;
    void place_latch_on_venue(e_building_type type, int dx, int dy, int orientation, bool main_venue = false);
    void map_add_bandstand_tiles(int stand_orientation);
    int bandstand_main_img_offset(int orientation);
    int bandstand_add_img_offset(int orientation);
    void latch_stand_offsets(vec2i main_offset, vec2i add_offset);
    void latch_stand_offsets(const venue_place_offset& place);
    void place_venue_items(const venue_place_offset& place, int stand_orientation);
};

ANK_CONFIG_PROPERTY(building_entertainment::runtime_data_t, spawned_entertainer_days, num_shows, juggler_visited,
  musician_visited, dancer_visited, play_index, booth_corner_grid_offset, latched_venue_main_grid_offset,
  latched_venue_add_grid_offset, conservatory_help, consume_material_id)