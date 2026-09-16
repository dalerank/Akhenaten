#include "grid/terrain.h"
#include "grid/property.h"
#include "grid/road_canal.h"
#include "grid/point.h"
#include "grid/grid.h"
#include "grid/water.h"
#include "grid/water_supply.h"
#include "grid/sprite.h"
#include "grid/bridge.h"
#include "grid/bridge_grid.h"
#include "building/building_bridge.h"
#include "grid/wall_material.h"
#include "grid/basin.h"
#include "grid/floodplain.h"
#include "grid/canals.h"
#include "grid/tiles.h"
#include "grid/irrigation_value.h"
#include "grid/gardens.h"
#include "grid/routing/routing.h"
#include "grid/routing/routing_terrain.h"
#include "grid/building.h"
#include "building/building_irrigation_ditch.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "core/profiler.h"
#include "mujs/mujs.h"
#include "js/js_game.h"

bool __map_terrain_is(tile2i tile, int terrain_mask) {
    return map_terrain_is(tile, terrain_mask);
}
ANK_FUNCTION_2(__map_terrain_is)

bool __map_property_is_plaza_or_earthquake(tile2i tile) {
    return map_property_is_plaza_or_earthquake(tile);
}
ANK_FUNCTION_1(__map_property_is_plaza_or_earthquake)

void __map_terrain_add(tile2i tile, int terrain) {
    map_terrain_add(tile, terrain);
}
ANK_FUNCTION_2(__map_terrain_add)

void __map_terrain_remove(tile2i tile, int terrain) {
    map_terrain_remove(tile, terrain);
}
ANK_FUNCTION_2(__map_terrain_remove)

void __map_water_rebuild_shores() {
    map_water_rebuild_shores();
}
ANK_FUNCTION(__map_water_rebuild_shores)

int __map_water_supply_is_well_unnecessary(int bid, int radius) {
    return map_water_supply_is_well_unnecessary(bid, radius);
}
ANK_FUNCTION_2(__map_water_supply_is_well_unnecessary)

void __map_tiles_set_water(tile2i tile) {
    map_tiles_set_water(tile.grid_offset());
}
ANK_FUNCTION_1(__map_tiles_set_water)

int __map_tiles_set_canal(tile2i tile) {
    return map_tiles_set_canal(tile);
}
ANK_FUNCTION_1(__map_tiles_set_canal)

bool __map_can_place_canal_on_road(tile2i tile) {
    return map_can_place_canal_on_road(tile);
}
ANK_FUNCTION_1(__map_can_place_canal_on_road)

bool __map_terrain_has_adjacent_x_with_type(tile2i tile, int terrain) {
    return map_terrain_has_adjacent_x_with_type(tile.grid_offset(), terrain);
}
ANK_FUNCTION_2(__map_terrain_has_adjacent_x_with_type)

bool __map_terrain_has_adjacent_y_with_type(tile2i tile, int terrain) {
    return map_terrain_has_adjacent_y_with_type(tile.grid_offset(), terrain);
}
ANK_FUNCTION_2(__map_terrain_has_adjacent_y_with_type)

bool __map_terrain_has_adjacent_with_type(tile2i tile, int terrain) {
    return map_terrain_has_adjecent_with_type(tile.grid_offset(), terrain);
}
ANK_FUNCTION_2(__map_terrain_has_adjacent_with_type)

int __map_terrain_count_directly_adjacent_with_type(tile2i tile, int terrain) {
    return map_terrain_count_directly_adjacent_with_type(tile.grid_offset(), terrain);
}
ANK_FUNCTION_2(__map_terrain_count_directly_adjacent_with_type)

bool __map_terrain_exists_in_area(tile2i tile, int size, int terrain) {
    return map_terrain_exists_tile_in_area_with_type(tile, size, terrain);
}
ANK_FUNCTION_3(__map_terrain_exists_in_area)

bool __map_terrain_exists_in_radius(tile2i tile, int size, int radius, int terrain) {
    return map_terrain_exists_tile_in_radius_with_type(tile, size, radius, terrain);
}
ANK_FUNCTION_4(__map_terrain_exists_in_radius)

bool __map_can_place_road_under_canal(tile2i tile) {
    return map_can_place_road_under_canal(tile);
}
ANK_FUNCTION_1(__map_can_place_road_under_canal)

int __map_get_canal_with_road_image(tile2i tile) {
    return map_get_canal_with_road_image(tile.grid_offset());
}
ANK_FUNCTION_1(__map_get_canal_with_road_image)

int __terrain_dirt_road_image_base() {
    return image_id_from_group(GROUP_TERRAIN_DIRT_ROAD);
}
ANK_FUNCTION(__terrain_dirt_road_image_base)

int __terrain_canal_image_begin() {
    return building_irrigation_ditch::images().begin;
}
ANK_FUNCTION(__terrain_canal_image_begin)

int __map_grid_offset(tile2i tile) {
    return MAP_OFFSET(tile.x(), tile.y());
}
ANK_FUNCTION_1(__map_grid_offset);

int __map_grid_direction_delta(int direction) {
    return map_grid_direction_delta(direction);
}
ANK_FUNCTION_1(__map_grid_direction_delta);

int __map_grid_tiledir_offset(tile2i tile, int direction) {
    return MAP_OFFSET(tile.x(), tile.y()) + map_grid_direction_delta(direction);
}
ANK_FUNCTION_2(__map_grid_tiledir_offset);

tile2i __map_tile_at_grid_offset(int grid_offset) {
    return tile2i(grid_offset);
}
ANK_FUNCTION_1(__map_tile_at_grid_offset);

int __map_routing_distance_at_grid_offset(int grid_offset) {
    return map_routing_distance(grid_offset);
}
ANK_FUNCTION_1(__map_routing_distance_at_grid_offset);

void __map_sprite_animation_set(tile2i tile, int value) {
    map_sprite_animation_set(tile, value);
}
ANK_FUNCTION_2(__map_sprite_animation_set);

bool __map_is_bridge(tile2i tile) {
    return map_is_bridge(tile);
}
ANK_FUNCTION_1(__map_is_bridge);

int __map_bridge_part_at(tile2i tile) {
    return map_bridge_part_at(tile);
}
ANK_FUNCTION_1(__map_bridge_part_at);

int __map_bridge_type_at(tile2i tile) {
    return map_bridge_type_at(tile);
}
ANK_FUNCTION_1(__map_bridge_type_at);

int __map_bridge_calculate_length(tile2i tile, bool is_ship_bridge) {
    int length = 0;
    int direction = 0;
    map_bridge_calculate_length_direction(tile.x(), tile.y(), &length, &direction, is_ship_bridge);
    return length;
}
ANK_FUNCTION_2(__map_bridge_calculate_length);

bool __map_bridge_calculate_valid(tile2i tile, bool is_ship_bridge) {
    int length = 0;
    int direction = 0;
    if (!map_bridge_calculate_length_direction(tile.x(), tile.y(), &length, &direction, is_ship_bridge)) {
        return false;
    }
    return length >= bridge_span_min_length(is_ship_bridge)
        && length <= bridge_span_max_length(is_ship_bridge);
}
ANK_FUNCTION_2(__map_bridge_calculate_valid);

int __map_bridge_add(tile2i tile, bool is_ship_bridge) {
    int length = 0;
    int direction = 0;
    if (!map_bridge_calculate_length_direction(tile.x(), tile.y(), &length, &direction, is_ship_bridge)) {
        return 0;
    }
    return map_bridge_add(tile.x(), tile.y(), is_ship_bridge);
}
ANK_FUNCTION_2(__map_bridge_add);

bool __map_routing_citizen_is_road(tile2i tile) {
    return map_routing_citizen_is_road(tile);
}
ANK_FUNCTION_1(__map_routing_citizen_is_road);

int __map_wall_building_type(tile2i tile) {
    return (int)wall_building_type_from_material(map_wall_material_at(tile));
}
ANK_FUNCTION_1(__map_wall_building_type);

int __map_wall_material(tile2i tile) {
    return (int)map_wall_material_at(tile);
}
ANK_FUNCTION_1(__map_wall_material);

int __map_basin_id_at(tile2i tile) {
    return (int)map_basin_id_at(tile);
}
ANK_FUNCTION_1(__map_basin_id_at);

bool __map_basin_is_sealed_at(tile2i tile) {
    return map_basin_is_sealed_at(tile);
}
ANK_FUNCTION_1(__map_basin_is_sealed_at);

int __map_basin_count() {
    return map_basin_count();
}
ANK_FUNCTION(__map_basin_count);

int __map_basin_area(int basin_id) {
    return map_basin_area((uint16_t)basin_id);
}
ANK_FUNCTION_1(__map_basin_area);

int __map_basin_farm_count(int basin_id) {
    return map_basin_farm_count((uint16_t)basin_id);
}
ANK_FUNCTION_1(__map_basin_farm_count);

int __map_basin_adjacent_id(tile2i tile) {
    return (int)map_basin_adjacent_id(tile);
}
ANK_FUNCTION_1(__map_basin_adjacent_id);

void __map_basin_rebuild() {
    map_basin_rebuild();
}
ANK_FUNCTION(__map_basin_rebuild);

int __map_basin_breach_perimeter(int max_tiles) {
    return map_basin_breach_perimeter(max_tiles, nullptr);
}
ANK_FUNCTION_1(__map_basin_breach_perimeter);

int __map_get_fertility_at(tile2i tile, int tally_type) {
    return map_get_fertility(tile.grid_offset(), tally_type);
}
ANK_FUNCTION_2(__map_get_fertility_at);

void __map_soil_set_depletion(tile2i tile, int malus) {
    map_soil_set_depletion(tile.grid_offset(), malus);
}
ANK_FUNCTION_2(__map_soil_set_depletion);

void __map_floodplain_apply_basin_fertility_bonus(tile2i tile) {
    map_floodplain_apply_basin_fertility_bonus(tile);
}
ANK_FUNCTION_1(__map_floodplain_apply_basin_fertility_bonus);

void __map_set_fertility_at(tile2i tile, int value) {
    map_update_tile_fertility(tile.grid_offset(), value - map_get_fertility(tile.grid_offset(), FERT_WITH_MALUS));
}
ANK_FUNCTION_2(__map_set_fertility_at);

int __map_floodplain_rebuild_rows() {
    return map_floodplain_rebuild_rows();
}
ANK_FUNCTION(__map_floodplain_rebuild_rows);

int __map_canal_at(tile2i tile) {
    return map_canal_at(tile);
}
ANK_FUNCTION_1(__map_canal_at);

void __map_canal_set(tile2i tile, int level) {
    map_canal_set(tile, level);
}
ANK_FUNCTION_2(__map_canal_set);

void __map_canals_decrease_water_level() {
    canals_decrease_water_level();
}
ANK_FUNCTION(__map_canals_decrease_water_level);

void __map_update_canals() {
    map_update_canals();
}
ANK_FUNCTION(__map_update_canals);

void __map_canal_update_all_tiles(int include_construction) {
    map_canal_update_all_tiles(include_construction);
}
ANK_FUNCTION_1(__map_canal_update_all_tiles);

bool __map_can_place_initial_road_or_canal(tile2i tile, int is_canal) {
    return map_can_place_initial_road_or_canal(tile.grid_offset(), is_canal);
}
ANK_FUNCTION_2(__map_can_place_initial_road_or_canal);

int __map_canal_ghost_image(tile2i tile) {
    const terrain_image img = map_image_context_get_canal(tile.grid_offset());
    const bool is_road = map_terrain_is(tile, TERRAIN_ROAD);
    return get_canal_image(tile.grid_offset(), is_road, 0, img);
}
ANK_FUNCTION_1(__map_canal_ghost_image);

void __map_tiles_update_region_canals(tile2i pmin, tile2i pmax) {
    map_tiles_update_region_canals(pmin, pmax);
}
ANK_FUNCTION_2(__map_tiles_update_region_canals);

void __irrigation_value_update() {
    g_irrigation_value.update();
}
ANK_FUNCTION(__irrigation_value_update);

int __irrigation_value_get(tile2i tile) {
    return g_irrigation_value.get(tile);
}
ANK_FUNCTION_1(__irrigation_value_get);

bool __map_grid_is_inside(tile2i tile) {
    return map_grid_is_inside(tile, 1);
}
ANK_FUNCTION_1(__map_grid_is_inside)

void __map_property_clear_constructing_and_deleted() {
    map_property_clear_constructing_and_deleted();
}
ANK_FUNCTION(__map_property_clear_constructing_and_deleted)

void __map_tiles_gardens_update_all() {
    map_tiles_gardens_update_all();
}
ANK_FUNCTION(__map_tiles_gardens_update_all)

void __map_highlight_set(tile2i tile, int mode) {
    map_highlight_set(tile, (e_highlight_mode)mode);
}
ANK_FUNCTION_2(__map_highlight_set)

int __map_is_highlighted(tile2i tile) {
    return (int)map_is_highlighted(tile);
}
ANK_FUNCTION_1(__map_is_highlighted)
