#include "building_farm.h"

#include "core/calc.h"
#include "core/profiler.h"
#include "game/game.h"
#include "graphics/graphics.h"
#include "grid/floodplain.h"
#include "js/js_game.h"

int __building_farm_progress_pct(int bid) {
    building_farm *farm = building_get(bid)->dcast_farm();
    if (!farm) {
        return 0;
    }

    return calc_percentage<int>(farm->progress(), farm->progress_max());
}
ANK_FUNCTION_1(__building_farm_progress_pct)

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

int __farm_get_image(int type, tile2i tile) {
    return building_farm::get_farm_image((e_building_type)type, tile);
}
ANK_FUNCTION_2(__farm_get_image)

void __farm_draw_crops(int type, int progress, tile2i tile, vec2i pixel, int color_mask) {
    painter ctx = game.painter();
    building_farm::draw_crops(ctx, (e_building_type)type, progress, tile, pixel, (color)color_mask);
}
ANK_FUNCTION_5(__farm_draw_crops)