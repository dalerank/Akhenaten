#include "city/building_index.h"

#include "building/building.h"
#include "city/city_buildings.h"
#include "core/log.h"

building_type_index g_building_index;

void building_type_index::clear() {
    for (auto& ids : _by_type) {
        ids.clear();
    }
}

void building_type_index::rebuild() {
    clear();
    for (int i = 1; i < MAX_BUILDINGS; ++i) {
        const building* b = building_get(i);
        if (b->state != BUILDING_STATE_UNUSED) {
            note(*b);
        }
    }
}

void building_type_index::note(const building& b) {
    if (b.id <= 0 || b.type <= BUILDING_NONE || b.type >= BUILDING_MAX) {
        return;
    }
    auto& ids = _by_type[b.type];
    auto it = std::lower_bound(ids.begin(), ids.end(), b.id);
    if (it == ids.end() || *it != b.id) {
        ids.insert(it, b.id);
    }
}

bool building_type_index::verify(const char* phase) const {
    for (int i = 1; i < MAX_BUILDINGS; ++i) {
        const building* b = building_get(i);
        if (b->state == BUILDING_STATE_UNUSED || b->type <= BUILDING_NONE || b->type >= BUILDING_MAX) {
            continue;
        }
        const auto& ids = _by_type[b->type];
        if (!std::binary_search(ids.begin(), ids.end(), b->id)) {
            logs::error("[building-index] building %d of type %d is missing from the type index %s", b->id,
              (int)b->type, phase);
            return false;
        }
    }
    return true;
}
