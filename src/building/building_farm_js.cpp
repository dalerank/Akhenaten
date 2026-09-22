#include "building_farm.h"

#include "core/calc.h"
#include "core/profiler.h"
#include "grid/floodplain.h"
#include "js/js_game.h"

#include <algorithm>

bool __building_farm_is_irrigated(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid() || !b->is_farm()) {
        return false;
    }
    return map_is_irrigated_for_farm(b->tile);
}
ANK_FUNCTION_1(__building_farm_is_irrigated)

int __building_farm_progress_pct(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid() || !b->dcast_farm()) {
        return 0;
    }

    return calc_percentage<int>(b->progress, b->progress_max);
}
ANK_FUNCTION_1(__building_farm_progress_pct)

int __building_farm_progress(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid() || !b->dcast_farm()) {
        return 0;
    }
    return b->progress;
}
ANK_FUNCTION_1(__building_farm_progress)

void __building_farm_set_labor_days(int bid, int days) {
    building_farm *farm = building_get(bid)->dcast_farm();
    if (!farm) {
        return;
    }
    auto &d = farm->runtime_data();
    d.labor_days_left = (uint8_t)std::clamp(days, 0, 255);
    d.labor_state = d.labor_days_left > 0 ? LABOR_STATE_PRESENT : LABOR_STATE_NONE;
}
ANK_FUNCTION_2(__building_farm_set_labor_days)

void __building_farm_set_progress(int bid, int progress) {
    building *b = building_get(bid);
    if (!b || !b->is_valid() || !b->dcast_farm()) {
        return;
    }
    b->progress = (uint16_t)std::clamp(progress, 0, (int)b->progress_max);
}
ANK_FUNCTION_2(__building_farm_set_progress)

int __building_farm_fertility(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid()) {
        return 0;
    }

    return map_get_fertility_for_farm(b->tile);
}
ANK_FUNCTION_1(__building_farm_fertility)

void __farm_set_worker(int bid, int action, vec2i coords) {
    building_farm* farm = building_get(bid)->dcast_farm();
    if (farm) {
        farm->runtime_data().worker_tile = coords;
        farm->runtime_data().worker_action = action;
    }
}
ANK_FUNCTION_3(__farm_set_worker)

bool __farm_requested_workers(int bid) {
    building_farm *farm = building_get(bid)->dcast_farm();
    return farm && farm->requested_workers();
}
ANK_FUNCTION_1(__farm_requested_workers)
