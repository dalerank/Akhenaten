#include "city/city_recorded_paths_chunks.h"

#include "city/city_recorded_paths.h"
#include "io/io_buffer.h"

void recorded_paths_chunk::bind_data(io_buffer* iob, size_t version) {
    (void)version;
    auto& p = g_recorded_paths;
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
            auto& ring = p.building_rings[b];
            ring.clear();
            for (int i = BUILDING_RECORDED_PATHS - 1; i >= 0; i--) {
                if (ordered[i]) {
                    ring.write_tail(ordered[i]);
                }
            }
        }
    }
}

void recorded_paths_chunk::load_defaults(size_t version) {
    // saves older than v188 have no trails; without this they would inherit the
    // previous session's pool
    g_recorded_paths.clear();
}

void recorded_paths_chunk::reset() {
    g_recorded_paths.clear();
}
