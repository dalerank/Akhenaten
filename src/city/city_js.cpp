#include "js/js_game.h"

#include "io/gamefiles/lang.h"
#include "core/profiler.h"
#include "city/city.h"
#include "city/entertainment.h"
#include "city/city_labor.h"
#include "city/city_message.h"
#include "io/gamefiles/lang.h"
#include "city/city_building_menu_ctrl.h"
#include "scenario/criteria.h"
#include "scenario/scenario.h"

void __city_ratings_apply_monument_yearly(int new_monument, int new_years_of_monument, int monument_explanation_reason) {
    g_city.ratings.monument = new_monument;
    g_city.ratings.monument_years_of_monument = new_years_of_monument;
    g_city.ratings.monument_num_criminals = 0;
    g_city.ratings.monument_num_rioters = 0;
    g_city.ratings.monument_destroyed_buildings = 0;
}
ANK_FUNCTION_3(__city_ratings_apply_monument_yearly)

int __city_rank_salary(int rank) { return g_city.kingdome.salary_for_rank(rank); }
ANK_FUNCTION_1(__city_rank_salary)

int __city_rating_kingdom() { return g_city.kingdome.rating; }
ANK_FUNCTION(__city_rating_kingdom)

int __city_get_current_overlay() { return g_city.current_overlay; }
ANK_FUNCTION(__city_get_current_overlay)

void __city_set_current_overlay(int overlay) { g_city.set_overlay((e_overlay)overlay); }
ANK_FUNCTION_1(__city_set_current_overlay)

int __city_population() { return g_city.population.current; }
ANK_FUNCTION(__city_population)

int __city_health_rating() { return g_city.health.value; }
ANK_FUNCTION(__city_health_rating)

int __city_player_rank() { return g_city.kingdome.player_rank; }
ANK_FUNCTION(__city_player_rank)

void __city_kingdome_apply_salary_rank(int rank) {
    g_city.kingdome.set_salary_rank(rank);
}
ANK_FUNCTION_1(__city_kingdome_apply_salary_rank)

std::optional<bvariant> __city_get_kingdome_property(pcstr property) {
    return archive_helper::get(g_city.kingdome, property, true);
}
ANK_FUNCTION_1(__city_get_kingdome_property)

bool __city_mission_has_won() { return g_city.victory_state.has_won(); }
ANK_FUNCTION(__city_mission_has_won)

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

std::optional<bvariant> __city_get_labor_property(pcstr property) { return archive_helper::get(g_city.labor, property, true); }
ANK_FUNCTION_1(__city_get_labor_property)

std::optional<bvariant> __city_get_rating_property(pcstr property) {
    return archive_helper::get(g_city.ratings, property, true);
}
ANK_FUNCTION_1(__city_get_rating_property)

std::optional<bvariant> __city_get_avg_coverage_property(pcstr property) {
    return archive_helper::get(g_city.avg_coverage, property, true);
}
ANK_FUNCTION_1(__city_get_avg_coverage_property)

std::optional<bvariant> __city_get_population_property(pcstr property) {
    return archive_helper::get(g_city.population, property, true);
}
ANK_FUNCTION_1(__city_get_population_property)

std::optional<bvariant> __city_get_entertainment_property(pcstr property) {
    return archive_helper::get(g_city.entertainment, property, true);
}
ANK_FUNCTION_1(__city_get_entertainment_property)

std::optional<bvariant> __city_get_labor_category_property(int index, pcstr property) {
    if (index < 0 || index >= LABOR_CATEGORY_SIZE) {
        return {};
    }
    return archive_helper::get(g_city.labor.categories[index], property, true);
}
ANK_FUNCTION_2(__city_get_labor_category_property)

void __city_camera_go_to(tile2i tile) { camera_go_to_mappoint(tile); } ANK_FUNCTION_1(__city_camera_go_to)

e_resource __city_allowed_foods(int index) { return g_city.allowed_foods(index); }
ANK_FUNCTION_1(__city_allowed_foods)

int __city_workers_diff() {
    return g_city.labor.workers_unemployed - g_city.labor.workers_needed;
}
ANK_FUNCTION(__city_workers_diff)

int __scenario_is_open_play() { return scenario_is_open_play(); }
ANK_FUNCTION(__scenario_is_open_play)

int __city_winning_culture() { return winning_culture(); }
ANK_FUNCTION(__city_winning_culture)
int __city_winning_prosperity() { return winning_prosperity(); }
ANK_FUNCTION(__city_winning_prosperity)
int __city_winning_monuments() { return winning_monuments(); }
ANK_FUNCTION(__city_winning_monuments)
int __city_winning_kingdom() { return winning_kingdom(); }
ANK_FUNCTION(__city_winning_kingdom)
int __city_winning_population() { return winning_population(); }
ANK_FUNCTION(__city_winning_population)

tile2i __city_message_next_problem_area_grid_offset() { return tile2i(city_message_next_problem_area_grid_offset()); } ANK_FUNCTION(__city_message_next_problem_area_grid_offset)

void __city_message_sort_and_compact() { city_message_sort_and_compact(); }
ANK_FUNCTION(__city_message_sort_and_compact)

int __city_message_count() { return city_message_count(); }
ANK_FUNCTION(__city_message_count)

int __city_message_month(int message_index) { return city_message_get(message_index).month; }
ANK_FUNCTION_1(__city_message_month)

int __city_message_year(int message_index) { return city_message_get(message_index).year; }
ANK_FUNCTION_1(__city_message_year)

bool __city_message_is_read(int message_index) { return city_message_get(message_index).is_read; }
ANK_FUNCTION_1(__city_message_is_read)

int __city_message_eventmsg_body_id(int message_index) { return city_message_get(message_index).eventmsg_body_id; }
ANK_FUNCTION_1(__city_message_eventmsg_body_id)

int __city_message_eventmsg_title_id(int message_index) { return city_message_get(message_index).eventmsg_title_id; }
ANK_FUNCTION_1(__city_message_eventmsg_title_id)

int __city_message_mm_text_id(int message_index) { return city_message_get(message_index).MM_text_id; }
ANK_FUNCTION_1(__city_message_mm_text_id)

int __city_message_lang_category(int message_index) {
    const int mm_id = city_message_get_text_id(message_index);
    return (int)lang_get_message(mm_id).message_type;
}
ANK_FUNCTION_1(__city_message_lang_category)

std::optional<bvariant> __city_get_coverage_property(pcstr property) {
    return archive_helper::get(g_city.coverage, property, true);
}
ANK_FUNCTION_1(__city_get_coverage_property)

std::optional<bvariant> __city_get_house_demands_property(pcstr property) {
    return archive_helper::get(g_city.houses, property, true);
}
ANK_FUNCTION_1(__city_get_house_demands_property)

std::optional<bvariant> __city_get_house_demands_requiring_property(pcstr property) {
    return archive_helper::get(g_city.houses.requiring, property, true);
}
ANK_FUNCTION_1(__city_get_house_demands_requiring_property)

void js_register_city_objects(js_State *J) {
}
