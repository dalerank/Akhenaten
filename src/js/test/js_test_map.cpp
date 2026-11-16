#include "js/test/js_test_common.h"

#include "building/building_road.h"
#include "city/city.h"
#include "city/city_figures.h"
#include "city/city_malaria_risk.h"
#include "city/city_recorded_paths.h"
#include "grid/building.h"
#include "grid/figure.h"
#include "grid/gems.h"
#include "grid/golden.h"
#include "grid/granite.h"
#include "grid/grid.h"
#include "grid/image.h"
#include "grid/limestone.h"
#include "grid/malaria_risk.h"
#include "grid/property.h"
#include "grid/road_access.h"
#include "grid/road_network.h"
#include "grid/routing/routing.h"
#include "grid/routing/routing_terrain.h"
#include "grid/sandstone.h"
#include "grid/stone.h"
#include "grid/terrain.h"
#include "grid/tiles.h"
#include "grid/vegetation.h"

static void __test_make_wall(int x, int y) {
    map_terrain_add(tile2i(x, y), TERRAIN_WALL);
}
ANK_FUNCTION_2(__test_make_wall);

static void __test_make_road(int x, int y) {
    map_terrain_add(tile2i(x, y), TERRAIN_ROAD);
}
ANK_FUNCTION_2(__test_make_road);

static void __test_map_building_damage_set(int x, int y, int value) {
    map_building_damage_set(tile2i(x, y).grid_offset(), value);
}
ANK_FUNCTION_3(__test_map_building_damage_set);

static int __test_map_building_damage_get(int x, int y) {
    return map_get_building_damage(tile2i(x, y).grid_offset());
}
ANK_FUNCTION_2(__test_map_building_damage_get);

static void __test_map_gems_init() {
    map_gems_init();
}
ANK_FUNCTION(__test_map_gems_init);

static void __test_map_golden_init() {
    map_golden_init();
}
ANK_FUNCTION(__test_map_golden_init);

static void __test_map_quarry_deposits_init() {
    map_sandstone_init();
    map_stone_init();
    map_limestone_init();
    map_granite_init();
}
ANK_FUNCTION(__test_map_quarry_deposits_init);

static int __test_resolve_building_road_access(int type, int x, int y, int size, int orientation) {
    if (type <= BUILDING_NONE || type >= BUILDING_MAX) {
        return 0;
    }
    tile2i tile(x, y);
    if (!tile.valid()) {
        return 0;
    }
    building_road_access_result r = resolve_building_road_access(tile, (e_building_type)type, size, orientation, 0,
      road_access_resolve_mode::Preview, false);
    return r.valid ? 1 : 0;
}
ANK_FUNCTION_5(__test_resolve_building_road_access);

static void __test_map_set_vegetation_growth(int x, int y, int growth) {
    tile2i tile(x, y);
    if (!map_grid_is_inside(tile, 1)) {
        return;
    }
    map_vegetation_set_growth(tile, growth);
}
ANK_FUNCTION_3(__test_map_set_vegetation_growth);

static void __test_map_routing_update_land() {
    map_routing_update_land();
}
ANK_FUNCTION(__test_map_routing_update_land);

static void __test_map_routing_update_water() {
    map_routing_update_water();
}
ANK_FUNCTION(__test_map_routing_update_water);

static void __test_check_kingdome_access() {
    g_city.maintenance.check_kingdome_access();
}
ANK_FUNCTION(__test_check_kingdome_access);

static void __test_update_road_network() {
    map_tiles_update_all_roads();
    map_routing_update_land();
    g_city.map.update_road_network();
}
ANK_FUNCTION(__test_update_road_network);

// OG: floodplain roads are never paved (0x0047B8E0), even at high desirability.
static int __test_road_is_paved(int x, int y) {
    return building_road::is_paved(tile2i(x, y)) ? 1 : 0;
}
ANK_FUNCTION_2(__test_road_is_paved);

extern grid_xx g_desirability_grid;
static void __test_set_desirability(int x, int y, int value) {
    map_grid_set(g_desirability_grid, tile2i(x, y).grid_offset(), value);
}
ANK_FUNCTION_3(__test_set_desirability);

// OG building_tiles.c: placed buildings keep 3 tiles inside the map and the play diamond.
static int __test_map_inside_building_area(int x, int y) {
    return map_grid_is_inside_building_area(tile2i(x, y)) ? 1 : 0;
}
ANK_FUNCTION_2(__test_map_inside_building_area);

// Mark a road tile as plaza (same bookkeeping as building_plaza::planer_place).
static void __test_plaza_mark_tile(int x, int y) {
    tile2i tile(x, y);
    map_image_set(tile, 0);
    map_property_mark_plaza_or_earthquake(tile.grid_offset());
    map_property_set_multi_tile_size(tile.grid_offset(), 1);
    map_property_mark_draw_tile(tile.grid_offset());
}
ANK_FUNCTION_2(__test_plaza_mark_tile);

static void __test_plaza_update_all() {
    map_tiles_update_all_plazas();
}
ANK_FUNCTION(__test_plaza_update_all);

static int __test_map_multi_tile_size(int x, int y) {
    return map_property_multi_tile_size(tile2i(x, y).grid_offset());
}
ANK_FUNCTION_2(__test_map_multi_tile_size);

static int __test_tile_road_network(int grid_offset) {
    if (grid_offset < 0) {
        return 0;
    }
    return map_road_network_get(grid_offset);
}
ANK_FUNCTION_1(__test_tile_road_network);

static int __test_grid_offset_xy(int x, int y) {
    if (x < 0 || y < 0) {
        return -1;
    }
    return tile2i(x, y).grid_offset();
}
ANK_FUNCTION_2(__test_grid_offset_xy);

static void __test_update_malaria_risk() {
    g_malaria_risk.update();
    building_update_malaria_risk();
}
ANK_FUNCTION(__test_update_malaria_risk);

static int __test_recorded_path_acquire() {
    return g_recorded_paths.acquire();
}
ANK_FUNCTION(__test_recorded_path_acquire);

static void __test_recorded_path_append(int path_id, int x, int y) {
    g_recorded_paths.append(path_id, MAP_OFFSET(x, y));
}
ANK_FUNCTION_3(__test_recorded_path_append);

static int __test_recorded_path_tile_count(int path_id) {
    return (int)g_recorded_paths.tiles(path_id).size();
}
ANK_FUNCTION_1(__test_recorded_path_tile_count);

static int __test_recorded_path_used(int path_id) {
    if (path_id <= 0 || path_id >= RECORDED_PATH_POOL_SIZE) {
        return 0;
    }
    return g_recorded_paths.slots[path_id].used ? 1 : 0;
}
ANK_FUNCTION_1(__test_recorded_path_used);

// Unlinks the figure from the figure grid first, so the stray tile leaves no dangling grid entry.
static void __test_figure_set_tile_raw(int fid, int x, int y) {
    figure* f = figure_get(fid);
    if (!f || f->id <= 0) {
        return;
    }
    f->map_figure_remove();
    f->tile = tile2i(x, y);
}
ANK_FUNCTION_3(__test_figure_set_tile_raw);

static void __test_map_figure_sort_by_y() {
    map_figure_sort_by_y();
}
ANK_FUNCTION(__test_map_figure_sort_by_y);

static int __test_figure_tile_x(int fid) {
    figure* f = figure_get(fid);
    return (f && f->id > 0) ? f->tile.x() : -1;
}
ANK_FUNCTION_1(__test_figure_tile_x);

static bool __test_animal_can_travel(int sx, int sy, int dx, int dy) {
    return map_routing_animal_can_travel(tile2i(sx, sy), tile2i(dx, dy));
}
ANK_FUNCTION_4(__test_animal_can_travel);
