#pragma once

#include "core/vec2i.h"
#include "grid/grid.h"

#include <array>
#include <atomic>

struct sound_view_queue_t {
    void push(int building_id, int grid_offset, int direction, vec2i pixel);
    void apply();

private:
    struct entry {
        int building_id;
        int grid_offset;
        int direction;
        vec2i pixel;
    };
    std::array<entry, GRID_SIZE_TOTAL> entries;
    std::atomic<int> count{0};
};
