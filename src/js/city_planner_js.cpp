#include "js_game.h"

#include "building/building.h"
#include "building/construction/build_planner.h"
#include "core/profiler.h"

ANK_GLOBAL_OBJECT(g_city_planner, __city_planner,
    build_type,
    in_progress
);

void __city_planner_update(int x, int y) {
    g_city_planner.update(tile2i(x, y));
}
ANK_FUNCTION_2(__city_planner_update);

int __city_planner_can_be_placed() {
    return g_city_planner.can_be_placed();
}
ANK_FUNCTION(__city_planner_can_be_placed);

void __city_planner_construction_start(int x, int y) {
    g_city_planner.construction_start(tile2i(x, y));
}
ANK_FUNCTION_2(__city_planner_construction_start);

void __city_planner_construction_update(int x, int y) {
    g_city_planner.construction_update(tile2i(x, y));
}
ANK_FUNCTION_2(__city_planner_construction_update);

void __city_planner_construction_finalize() {
    g_city_planner.construction_finalize();
}
ANK_FUNCTION(__city_planner_construction_finalize);

void __city_planner_construction_cancel() {
    g_city_planner.construction_cancel();
}
ANK_FUNCTION(__city_planner_construction_cancel);

int __city_planner_last_created_building_id() {
    building *b = g_city_planner.last_created_building;
    return (b && b->id > 0) ? b->id : 0;
}
ANK_FUNCTION(__city_planner_last_created_building_id);

void __city_planner_validate_last_created() {
    building *b = g_city_planner.last_created_building;
    if (b && b->id > 0) {
        b->state = BUILDING_STATE_VALID;
    }
}
ANK_FUNCTION(__city_planner_validate_last_created);
