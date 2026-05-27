#include "building/building.h"
#include "building/monuments.h"
#include "game/resource.h"

#include "core/profiler.h"
#include "js/js_game.h"

#include <algorithm>

static building_monument *monument_from_building(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid() || !b->is_monument()) {
        return nullptr;
    }

    return b->main()->dcast_monument();
}

bool __monument_need_workers(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        return false;
    }

    building_monument *monument = b->dcast_monument();
    return monument && monument->need_workers();
}
ANK_FUNCTION_1(__monument_need_workers)

int __monument_phase_code(int bid) {
    building_monument *m = monument_from_building(bid);
    if (!m) {
        return -99;
    }

    return m->runtime_data().phase;
}
ANK_FUNCTION_1(__monument_phase_code)

int __monument_phases_total(int bid) {
    building_monument *m = monument_from_building(bid);
    return m ? m->phases() : 0;
}
ANK_FUNCTION_1(__monument_phases_total)

int __monument_material_pct_min(int bid) {
    building_monument *m = monument_from_building(bid);
    if (!m || m->runtime_data().phase == MONUMENT_FINISHED) {
        return 100;
    }

    auto &d = m->runtime_data();
    int min_pct = 100;
    bool any = false;
    for (int ri = (int)RESOURCES_MIN; ri <= (int)RESOURCES_MAX; ++ri) {
        const auto r = (e_resource)ri;
        if (m->needs_resource(r) <= 0) {
            continue;
        }
        any = true;
        min_pct = std::min(min_pct, (int)d.resources_pct[r]);
    }
    return any ? min_pct : 100;
}
ANK_FUNCTION_1(__monument_material_pct_min)
