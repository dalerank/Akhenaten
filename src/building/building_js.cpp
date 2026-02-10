#include "building.h"

#include "js/js_game.h"

std::optional<bvariant> __building_get_property(int bid, pcstr property) {
    return archive_helper::get(*building_get(bid), property, true);
}
ANK_FUNCTION_2(__building_get_property)

int __building_meta_text_id(int bid) { return building_get(bid)->params().meta.text_id; }
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