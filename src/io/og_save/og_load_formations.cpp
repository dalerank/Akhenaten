#include "io/og_save/og_load.h"

#include "core/log.h"
#include "figure/formation.h"

#include <map>

// Formations from OG records (tutankhamun formation_types.h). Only the player's legions are carried over: their
// soldiers are figures, which are not converted yet, so the fort recruits again. Enemy, herd and other formations
// would be left without figures and are dropped.
namespace og {

    void load_formations(const savegame& s, load_report& report) {
        std::map<int, int> by_figure_type;
        for (size_t i = 0; i < s.figures.size(); ++i) {
            if (i > 0 && s.figures[i].state != 0) {
                by_figure_type[s.figures[i].type]++;
                report.figures_dropped++;
            }
        }
        for (const auto& kv : by_figure_type) {
            logs::info("[og-save] unmapped figure type %d x%d (OG action states are not translated yet)", kv.first,
              kv.second);
        }

        for (size_t i = 0; i < s.formations.size(); ++i) {
            const formation& og = s.formations[i];
            if (!og.in_use) {
                continue;
            }
            if (!og.is_legion) {
                report.formations_dropped++;
                continue;
            }

            ::formation* f = formation_get((int)i);
            f->id = (int)i;
            f->in_use = true;
            f->faction_id = og.faction;
            f->batalion_id = og.legion_id;
            f->is_at_fort = og.is_at_fort;
            f->figure_type = (e_figure_type)og.figure_type;
            f->building_id = og.building_id;
            f->num_figures = 0;
            f->max_figures = og.max_figures;
            f->layout = (e_formation_layout)og.layout;
            f->morale = og.morale;
            f->home = tile2i(og.home_x, og.home_y);
            f->standard_tile = tile2i(og.order_x, og.order_y);
            f->tile = tile2i(og.x, og.y);
            f->destination = tile2i(og.destination_x, og.destination_y);
            f->destination_building_id = og.destination_building_id;
            f->own_batalion = og.is_legion;
            f->attack_type = (e_formation_attack_type)og.attack_type;
            f->batalion_recruit_type = (uint8_t)og.legion_recruit_type;
            f->has_military_training = (uint8_t)og.has_military_training;
            f->total_damage = og.total_damage;
            f->max_total_damage = og.max_total_damage;
            f->recent_fight = (int8_t)og.recent_fight;
            f->experience = og.experience;
            f->is_halted = (uint8_t)og.is_halted;
            f->prev.layout = (e_formation_layout)og.prev_layout;
            f->cursed_by_seth = og.cursed_by_seth;
            f->months_low_morale = og.months_low_morale;
            f->months_very_low_morale = og.months_very_low_morale;
            f->empire_service = og.empire_service;
            f->direction = og.direction;
            f->prev.home = tile2i(og.prev_x, og.prev_y);
            f->orientation = og.orientation;
            f->months_from_home = og.months_from_home;
            f->ship_figure_id = 0;
            f->request_event_id = -1;
            report.legions++;
        }
        if (report.formations_dropped) {
            logs::info("[og-save] unmapped formations: %d non-legion formations dropped with their figures",
              report.formations_dropped);
        }
    }

} // namespace og
