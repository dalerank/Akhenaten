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

io_buffer *iob_recorded_paths = new io_buffer([](io_buffer *iob, size_t version) {
    (void)version;
    auto &p = g_recorded_paths;
    for (int i = 0; i < RECORDED_PATH_POOL_SIZE; i++) {
        uint8_t used = p.slots[i].used ? 1 : 0;
        iob->bind(BIND_SIGNATURE_UINT8, &used);
        uint16_t len = 0;
        uint16_t figure_type = p.slots[i].figure_type;
        uint16_t reserved = 0;
        if (iob->is_read_access()) {
            iob->bind(BIND_SIGNATURE_UINT16, &len);
            p.slots[i].used = used != 0;
            p.slots[i].tiles.clear();
            for (uint16_t t = 0; t < RECORDED_PATH_MAX_TILES; t++) {
                uint16_t off = 0;
                iob->bind(BIND_SIGNATURE_UINT16, &off);
                if (p.slots[i].used && t < len) {
                    p.slots[i].tiles.push_back(off);
                }
            }
            iob->bind(BIND_SIGNATURE_UINT16, &figure_type);
            iob->bind(BIND_SIGNATURE_UINT16, &reserved);
            p.slots[i].figure_type = p.slots[i].used ? figure_type : 0;
        } else {
            len = p.slots[i].used ? (uint16_t)p.slots[i].tiles.size() : 0;
            iob->bind(BIND_SIGNATURE_UINT16, &len);
            for (uint16_t t = 0; t < RECORDED_PATH_MAX_TILES; t++) {
                uint16_t off = (p.slots[i].used && t < len) ? p.slots[i].tiles[t] : 0;
                iob->bind(BIND_SIGNATURE_UINT16, &off);
            }
            if (!p.slots[i].used) {
                figure_type = 0;
            }
            iob->bind(BIND_SIGNATURE_UINT16, &figure_type);
            iob->bind(BIND_SIGNATURE_UINT16, &reserved);
        }
    }
    // File layout: newest-first fixed slots (BUILDING_RECORDED_PATHS).
    for (int b = 0; b < MAX_BUILDINGS; b++) {
        uint16_t ordered[BUILDING_RECORDED_PATHS] = {};
        if (!iob->is_read_access()) {
            for (int i = 0; i < BUILDING_RECORDED_PATHS; i++) {
                ordered[i] = (uint16_t)p.building_path_at(b, i);
            }
        }
        for (int i = 0; i < BUILDING_RECORDED_PATHS; i++) {
            iob->bind(BIND_SIGNATURE_UINT16, &ordered[i]);
        }
        if (iob->is_read_access()) {
            auto &ring = p.building_rings[b];
            ring.clear();
            for (int i = BUILDING_RECORDED_PATHS - 1; i >= 0; i--) {
                if (ordered[i]) {
                    ring.write_tail(ordered[i]);
                }
            }
        }
    }
}, [](size_t version) {
    // saves older than v188 have no trails; without this they would inherit the
    // previous session's pool
    g_recorded_paths.clear();
});
