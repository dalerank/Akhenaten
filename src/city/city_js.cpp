#include "js/js_game.h"

#include "io/gamefiles/lang.h"
#include "city/city.h"
#include "city/city_building_menu_ctrl.h"

pcstr __city_rank_title(int rank) { return lang_get_string(52, rank + 4); }
ANK_FUNCTION_1(__city_rank_title)

int __city_rank_salary(int rank) { return g_city.kingdome.salary_for_rank(rank); }
ANK_FUNCTION_1(__city_rank_salary)

int __city_rating_kingdom() { return g_city.kingdome.rating; }
ANK_FUNCTION(__city_rating_kingdom)

int __city_population() { return g_city.population.current; }
ANK_FUNCTION(__city_population)

int __city_player_rank() { return g_city.kingdome.player_rank; }
ANK_FUNCTION(__city_player_rank)

pcstr __city_player_name() { return (pcstr)city_player_name; }
ANK_FUNCTION(__city_player_name)

void __city_use_building(int building_type, bool enabled) { g_building_menu_ctrl.toggle_building((e_building_type)building_type, enabled); }
ANK_FUNCTION_2(__city_use_building)

int __formation_get_num_forts() { return formation_get_num_forts(); }
ANK_FUNCTION(__formation_get_num_forts)

std::optional<bvariant> __city_get_battalion_property(int fid, pcstr property) {
    const auto form = formation_get(g_formations.get_battalion_id_from_index(fid + 1));
    if (!form) {
        return {};
    }

    return archive_helper::get(*form, property, true);
}
ANK_FUNCTION_2(__city_get_battalion_property)

void __city_camera_go_to(tile2i tile) {
    camera_go_to_mappoint(tile);
}
ANK_FUNCTION_1(__city_camera_go_to)

void js_register_city_objects(js_State *J) {
}

e_resource __city_allowed_foods(int index) { return g_city.allowed_foods(index); }
ANK_FUNCTION_1(__city_allowed_foods)