#include "building.h"
#include "grid/building.h"
#include "grid/road_access.h"

#include "js/js_game.h"

std::optional<bvariant> __building_get_property(int bid, pcstr property) {
    return archive_helper::get(*building_get(bid), property, true);
}
ANK_FUNCTION_2(__building_get_property)

int __building_meta_text_id(int bid) { return building_get(bid)->params().meta.text_id; }\
ANK_FUNCTION_1(__building_meta_text_id)

void __building_add_fire_damage(int bid, int damage) {
    building *b = building_get(bid);
    if (b->is_valid()) {
        b->force_damage(e_damage_fire, damage);
    }
}
ANK_FUNCTION_2(__building_add_fire_damage)

void __building_add_collapse_damage(int bid, int damage) {
    building *b = building_get(bid);
    if (b->is_valid()) {
        b->force_damage(e_damage_collapse, damage);
    }
}
ANK_FUNCTION_2(__building_add_collapse_damage)

int __map_rubble_building_type(int bid) {
    building *b = building_get(bid);
    return b ? map_rubble_building_type(b->tile.grid_offset()) : 0;
}
ANK_FUNCTION_1(__map_rubble_building_type)

int __map_rubble_building_type_at_grid(int grid_offset) {
    return map_rubble_building_type(grid_offset);
}
ANK_FUNCTION_1(__map_rubble_building_type_at_grid)

tile2i __building_tile(int bid) {
    building* b = building_get(bid);
    return b ? b->tile : tile2i::invalid;
}
ANK_FUNCTION_1(__building_tile)

bool __map_road_within_radius(tile2i tile, int size, int radius) {
    return map_closest_road_within_radius(tile, size, radius).valid();
}
ANK_FUNCTION_3(__map_road_within_radius)