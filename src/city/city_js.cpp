#include "js/js_game.h"

#include "io/gamefiles/lang.h"
#include "city/city.h"

pcstr __city_rank_title(int rank) {
    return lang_get_string(52, rank + 4);
}
ANK_FUNCTION_1(__city_rank_title)

int __city_rank_salary(int rank) {
    return g_city.kingdome.salary_for_rank(rank);
}
ANK_FUNCTION_1(__city_rank_salary)

