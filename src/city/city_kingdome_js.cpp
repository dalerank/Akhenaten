#include "city/city_kingdome_relations.h"

#include "city/city.h"
#include "core/profiler.h"
#include "js/js_game.h"
#include "js/js_global_object.h"

void ank_global_obj_bind_field(js_State *J, js_StringNode name, e_rating_change *ptr) {
    js_register_bound_uint8_property(J, name, reinterpret_cast<uint8_t *>(ptr));
}

ANK_GLOBAL_OBJECT(g_city.kingdome, __city_kingdome,
    salary_rank,
    player_rank,
    kingdom_change,
    kingdom_salary_penalty,
    kingdom_milestone_penalty,
    kingdom_ignored_request_penalty,
    personal_savings);
