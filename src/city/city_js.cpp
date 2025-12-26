#include "js/js_game.h"

#include "io/gamefiles/lang.h"
#include "city/city.h"

pcstr __city_rank_title(int rank) { return lang_get_string(52, rank + 4); }
ANK_FUNCTION_1(__city_rank_title)

int __city_rank_salary(int rank) { return g_city.kingdome.salary_for_rank(rank); }
ANK_FUNCTION_1(__city_rank_salary)

int __city_rating_kingdom() { return g_city.kingdome.rating; }
ANK_FUNCTION(__city_rating_kingdom)

int __city_festival_selected_god() { return g_city.festival.selected_god(); }
ANK_FUNCTION(__city_festival_selected_god)

int __city_population() { return g_city.population.current; }
ANK_FUNCTION(__city_population)

int __city_player_rank() { return g_city.kingdome.player_rank; }
ANK_FUNCTION(__city_player_rank)

pcstr __city_player_name() { return (pcstr)city_player_name; }
ANK_FUNCTION(__city_player_name)