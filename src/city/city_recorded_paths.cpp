#include "city/city_recorded_paths.h"

#include "core/calc.h"
#include "figure/figure.h"
#include "grid/grid.h"
#include "io/io_buffer.h"

recorded_paths_t g_recorded_paths;

void recorded_paths_t::clear() {
    for (int i = 0; i < RECORDED_PATH_POOL_SIZE; i++) {
        slots[i].used = false;
        slots[i].figure_type = 0;
        slots[i].tiles.clear();
    }
    for (int b = 0; b < MAX_BUILDINGS; b++) {
        building_rings[b].clear();
    }
}

int recorded_paths_t::acquire() {
    for (int i = 1; i < RECORDED_PATH_POOL_SIZE; i++) {
        if (!slots[i].used) {
            slots[i].used = true;
            slots[i].figure_type = 0;
            slots[i].tiles.clear();
            return i;
        }
    }
    return 0;
}

void recorded_paths_t::release(int id) {
    if (id <= 0 || id >= RECORDED_PATH_POOL_SIZE) {
        return;
    }
    slots[id].used = false;
    slots[id].figure_type = 0;
    slots[id].tiles.clear();
}

void recorded_paths_t::clear_tiles(int id) {
    if (id <= 0 || id >= RECORDED_PATH_POOL_SIZE || !slots[id].used) {
        return;
    }
    slots[id].tiles.clear();
}

void recorded_paths_t::append(int id, int grid_offset) {
    if (id <= 0 || id >= RECORDED_PATH_POOL_SIZE || !slots[id].used) {
        return;
    }
    if (grid_offset < 0) {
        return;
    }
    auto &t = slots[id].tiles;
    if (!t.empty() && t.back() == (uint16_t)grid_offset) {
        return;
    }
    if ((int)t.size() >= RECORDED_PATH_MAX_TILES) {
        return;
    }
    t.push_back((uint16_t)grid_offset);
}

const recorded_path_tiles_t &recorded_paths_t::tiles(int id) const {
    static recorded_path_tiles_t empty;
    if (id <= 0 || id >= RECORDED_PATH_POOL_SIZE || !slots[id].used) {
        return empty;
    }
    return slots[id].tiles;
}

uint16_t recorded_paths_t::figure_type(int id) const {
    if (id <= 0 || id >= RECORDED_PATH_POOL_SIZE || !slots[id].used) {
        return 0;
    }
    return slots[id].figure_type;
}

int recorded_paths_t::duplicate(int id) {
    if (id <= 0 || id >= RECORDED_PATH_POOL_SIZE || !slots[id].used) {
        return 0;
    }
    const int copy = acquire();
    if (!copy) {
        return 0;
    }
    slots[copy].figure_type = slots[id].figure_type;
    slots[copy].tiles = slots[id].tiles;
    return copy;
}

void recorded_paths_t::building_push(building_id bid, int path_id) {
    if (bid <= 0 || bid >= MAX_BUILDINGS || path_id <= 0) {
        return;
    }
    auto &ring = building_rings[bid];
    if (ring.full()) {
        release(ring.head());
    }
    ring.push_tail((uint16_t)path_id);
}

int recorded_paths_t::building_path_at(building_id bid, int index) const {
    if (bid <= 0 || bid >= MAX_BUILDINGS || index < 0 || index >= BUILDING_RECORDED_PATHS) {
        return 0;
    }
    const auto &ring = building_rings[bid];
    if ((uint32_t)index >= ring.size()) {
        return 0;
    }
    // ring[0] = oldest; expose newest-first for UI/tests
    return ring[ring.size() - 1 - (uint32_t)index];
}

void recorded_paths_t::building_clear(building_id bid) {
    if (bid <= 0 || bid >= MAX_BUILDINGS) {
        return;
    }
    auto &ring = building_rings[bid];
    ring.for_each([this](uint16_t path_id) {
        if (path_id) {
            release(path_id);
        }
    });
    ring.clear();
}

void recorded_paths_t::handoff_to_building(figure &f, building_id bid) {
    if (!bid || f.trail_path_id <= 0) {
        return;
    }
    const int path_id = f.trail_path_id;
    f.trail_path_id = 0;
    building_push(bid, path_id);
}

void figure_recorded_path_acquire(figure &f) {
    if (f.trail_path_id > 0) {
        g_recorded_paths.release(f.trail_path_id);
        f.trail_path_id = 0;
    }
    f.trail_path_id = (uint16_t)g_recorded_paths.acquire();
    if (f.trail_path_id) {
        g_recorded_paths.slots[f.trail_path_id].figure_type = (uint16_t)f.type;
        if (f.tile.valid()) {
            g_recorded_paths.append(f.trail_path_id, f.tile.grid_offset());
        }
    }
}

void figure_recorded_path_append_tile(figure &f) {
    if (f.trail_path_id <= 0 || !f.tile.valid()) {
        return;
    }
    g_recorded_paths.append(f.trail_path_id, f.tile.grid_offset());
}

void figure_recorded_path_release(figure &f) {
    if (f.trail_path_id <= 0) {
        return;
    }
    g_recorded_paths.release(f.trail_path_id);
    f.trail_path_id = 0;
}
