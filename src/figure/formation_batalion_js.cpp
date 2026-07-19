#include "formation_batalion.h"

#include "figure/formation.h"
#include "js/js_game.h"
#include "core/profiler.h"

std::optional<bvariant> __formation_get_property(int formation_id, pcstr property) {
    if (formation_id <= 0) {
        return {};
    }

    const formation *m = formation_get(formation_id);
    if (!m || !m->id) {
        return {};
    }

    return archive_helper::get(*m, property, true);
}
ANK_FUNCTION_2(__formation_get_property)

void __formation_batalion_idx_return_to_fort(int legion_insdex) {
    int formation_id = g_formations.get_battalion_id_from_index(legion_insdex + 1);
    formation *m = formation_get(formation_id);
    if (!m->in_distant_battle) {
        formation_batalion_return_home(m);
    }
}
ANK_FUNCTION_1(__formation_batalion_idx_return_to_fort)

void __formation_batalion_idx_set_empire_service(int legion_insdex, bool value) {
    int formation_id = g_formations.get_battalion_id_from_index(legion_insdex + 1);
    formation *m = formation_get(formation_id);
    m->empire_service = value;
    g_formations.calculate_figures();
}
ANK_FUNCTION_2(__formation_batalion_idx_set_empire_service)