#include "city/city_kingdome_relations.h"

#include "city/city.h"
#include "core/profiler.h"
#include "js/js_game.h"
#include "js/js_global_object.h"

void ank_global_obj_bind_field(js_State *J, js_StringNode name, e_rating_change *ptr) {
    js_register_bound_uint8_property(J, name, reinterpret_cast<uint8_t *>(ptr));
}

void __city_apply_salary_rank(int rank) {
    const auto &salaries = kingdome_relation_t::params().salary_ranks;
    rank = std::clamp(rank, 0, (int)salaries.size() - 1);
    g_city.kingdome.salary_rank = (uint8_t)rank;
    g_city.kingdome.salary_amount = (uint8_t)salaries[rank];
}
ANK_FUNCTION_1(__city_apply_salary_rank)

ANK_GLOBAL_OBJECT(g_city.kingdome, __city_kingdome,
    salary_rank,
    salary_amount,
    player_rank,
    kingdom_change,
    kingdom_salary_penalty,
    kingdom_milestone_penalty,
    kingdom_ignored_request_penalty,
    personal_savings,
    donate_amount,
    months_since_gift,
    gift_overdose_penalty,
    rating,
    rating_cap);

