#pragma once

#include "building/building.h"
#include "core/circullar_buffer.h"
#include "core/hvector.h"
#include "grid/point.h"

#include <cstdint>

constexpr int RECORDED_PATH_POOL_SIZE = 512;
constexpr int RECORDED_PATH_MAX_TILES = 254;
// circular_buffer 2nd param is pow2 exponent: 1<<2 = 4 slots
constexpr int BUILDING_RECORDED_PATHS_POW2 = 2;
constexpr int BUILDING_RECORDED_PATHS = 1 << BUILDING_RECORDED_PATHS_POW2;

using recorded_path_tiles_t = hvector<uint16_t, RECORDED_PATH_MAX_TILES>;
using building_path_ring_t = circular_buffer<uint16_t, BUILDING_RECORDED_PATHS_POW2>;

struct recorded_paths_t {
    struct slot_t {
        bool used = false;
        uint16_t figure_type = 0;
        recorded_path_tiles_t tiles;
    };

    slot_t slots[RECORDED_PATH_POOL_SIZE];
    building_path_ring_t building_rings[MAX_BUILDINGS];

    void clear();
    int acquire();
    void release(int id);
    void clear_tiles(int id);
    void append(int id, int grid_offset);
    const recorded_path_tiles_t &tiles(int id) const;
    uint16_t figure_type(int id) const;
    int duplicate(int id);

    void building_push(building_id bid, int path_id);
    int building_path_at(building_id bid, int index) const; // 0 = newest
    void building_clear(building_id bid);

    // Transfer figure's trail to building; figure gets a fresh empty trail if still alive.
    void handoff_to_building(figure& f, building_id bid);

    void figure_acquire(figure& f);
    void figure_append_tile(figure& f);
    void figure_release(figure& f);
};

recorded_paths_t& recorded_paths();
