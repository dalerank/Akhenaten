#pragma once

#include "grid/point.h"

struct city_map_t {
    tile2i entry_point;
    tile2i exit_point;
    tile2i entry_flag;
    tile2i exit_flag;

    struct {
        int32_t id;
        int32_t size;
    } largest_road_networks[10];

    tile2i set_entry_flag(tile2i tile);
    tile2i set_exit_flag(tile2i tile);

    int road_network_index(int network_id);
    void clear_largest_road_networks(void);
    void add_to_largest_road_networks(int network_id, int size);
};

