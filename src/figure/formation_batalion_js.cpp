#include "formation_batalion.h"

#include "js/js_game.h"

void __formation_batalion_return_to_fort(int legion_insdex) {
    int formation_id = g_formations.get_battalion_id_from_index(legion_insdex);
    formation *m = formation_get(formation_id);
    if (!m->in_distant_battle) {
        formation_batalion_return_home(m);
    }
}
ANK_FUNCTION_1(__formation_batalion_return_to_fort)

void __formation_batalion_empire_service(int legion_insdex) {
    int formation_id = g_formations.get_battalion_id_from_index(legion_insdex);
    formation *m = formation_get(formation_id);
    m->empire_service = !m->empire_service;
    g_formations.calculate_figures();
}
ANK_FUNCTION_1(__formation_batalion_empire_service)