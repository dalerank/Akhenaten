#include "player.h"

#include "js/js_game.h"
#include "city/city.h"

int __player_salary_rank() { return g_city.kingdome.salary_rank; }
ANK_FUNCTION(__player_salary_rank)

int __player_salary_amount() { return g_city.kingdome.salary_amount; }
ANK_FUNCTION(__player_salary_amount)