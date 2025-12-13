#pragma once

#include "grid/point.h"
#include "core/archive.h"

struct malaria_risk_t {
    uint8_t max_risk;
    uint8_t outside_map_risk;
    uint8_t max_range;

    uint8_t water_risk;
    int8_t water_step_delta;
    uint8_t water_risk_range;

    uint8_t floodplain_risk;
    int8_t floodplain_step_delta;
    uint8_t floodplain_risk_range;

    uint8_t marshland_risk;
    int8_t marshland_step_delta;
    uint8_t marshland_risk_range;

    int8_t tree_risk;
    int8_t tree_step_delta;
    uint8_t tree_risk_range;

    void update_terrain();
    void clear_map();
    void update();
    void update_buildings();

    void add_to_terrain_at_distance(tile2i tile, int size, int distance, int risk);
    void add_to_terrain(tile2i tile, int size, int risk, int step, int step_size, int range);
    int get(int grid_offset);
    inline int get(tile2i tile) { return get(tile.grid_offset()); }
    int get_max(tile2i tile, int size);
    int get_avg(tile2i tile, int size);
};
ANK_CONFIG_STRUCT(malaria_risk_t, max_risk, outside_map_risk, max_range,
    water_risk, water_step_delta, water_risk_range,
    floodplain_risk, floodplain_step_delta, floodplain_risk_range,
    marshland_risk, marshland_step_delta, marshland_risk_range,
    tree_risk, tree_step_delta, tree_risk_range)

extern malaria_risk_t g_malaria_risk;

