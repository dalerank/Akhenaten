#include "js_game.h"

#include "building/building.h"
#include "building/construction/build_planner.h"
#include "core/calc.h"
#include "game/game.h"
#include "game/undo.h"
#include "graphics/graphics.h"
#include "graphics/view/lookup.h"
#include "grid/routing/routing.h"
#include "core/profiler.h"
#include "mujs/mujs.h"

ANK_GLOBAL_OBJECT(g_city_planner, __city_planner,
    build_type,
    in_progress,
    construction_update_items
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

void __city_planner_draw_blocked(vec2i pixel) {
    painter ctx = game.painter();
    g_city_planner.draw_flat_tile(ctx, pixel, COLOR_MASK_RED);
}
ANK_FUNCTION_1(__city_planner_draw_blocked);

void __city_planner_draw_ghost(vec2i pixel, int image_id) {
    painter ctx = game.painter();
    g_city_planner.draw_building_ghost(ctx, image_id, pixel);
}
ANK_FUNCTION_2(__city_planner_draw_ghost);

vec2i __lookup_tile_to_pixel(tile2i t) {
    return lookup_tile_to_pixel(t);
}
ANK_FUNCTION_1(__lookup_tile_to_pixel);

int __map_routing_distance(tile2i tile) {
    return map_routing_distance(tile);
}
ANK_FUNCTION_1(__map_routing_distance);

int __calc_general_direction(tile2i from, tile2i to) {
    return calc_general_direction(from, to);
}
ANK_FUNCTION_2(__calc_general_direction);

void __game_undo_restore_map(int include_properties) {
    game_undo_restore_map(include_properties);
}
ANK_FUNCTION_1(__game_undo_restore_map);

bool __map_routing_calculate_distances_for_building(int mode, tile2i tile) {
    return map_routing_calculate_distances_for_building((e_routed_mode)mode, tile);
}
ANK_FUNCTION_2(__map_routing_calculate_distances_for_building);
