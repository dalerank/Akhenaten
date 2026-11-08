#pragma once

// Map extents within the fixed-size grid. The instance lives in g_scenario.map (saved with the
// scenario), so the accessor is defined in scenario/map.cpp.
struct map_data_t {
    int width = -1;
    int height = -1;
    int start_offset = -1;
    int border_size = -1;
};

const map_data_t* scenario_map_data();
