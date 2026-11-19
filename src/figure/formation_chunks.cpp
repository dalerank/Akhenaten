#include "figure/formation_chunks.h"

#include "figure/formation.h"
#include "io/io_buffer.h"

void formations_chunk::bind_data(io_buffer* iob, size_t version) {
    for (int i = 0; i < MAX_FORMATIONS; i++) {
        formation* f = &g_formations.formations[i];
        f->id = i;                 // 10
        iob->bind_bool(f->in_use); // 1
        iob->bind_u8(f->faction_id);
        iob->bind_u8(f->batalion_id);
        iob->bind_bool(f->is_at_fort);
        iob->bind_u16((uint16_t&)f->figure_type); // 69
        iob->bind(BIND_SIGNATURE_INT16, &f->building_id);

        for (int fig = 0; fig < formation::max_figures_count; fig++) {
            iob->bind(BIND_SIGNATURE_INT16, &f->figures[fig]);
        }

        iob->bind(BIND_SIGNATURE_UINT8, &f->num_figures); // --> 3
        iob->bind(BIND_SIGNATURE_UINT8, &f->max_figures); // 7
        iob->bind(BIND_SIGNATURE_INT16, &f->layout);      // 9
        iob->bind(BIND_SIGNATURE_INT16, &f->morale);      // 100

        iob->bind(BIND_SIGNATURE_TILE2I, f->home);          // 44
        iob->bind(BIND_SIGNATURE_TILE2I, f->standard_tile); //
        iob->bind(BIND_SIGNATURE_TILE2I, f->tile);          // 44
        iob->bind(BIND_SIGNATURE_TILE2I, f->destination);   // 49

        iob->bind(BIND_SIGNATURE_INT16, &f->destination_building_id);
        iob->bind(BIND_SIGNATURE_INT16, &f->standard_figure_id);
        iob->bind____skip(1); // iob->bind_u8(f->batalion_id);
        iob->bind_bool(f->own_batalion);
        iob->bind(BIND_SIGNATURE_UINT8, &f->attack_type);
        iob->bind____skip(1);
        iob->bind(BIND_SIGNATURE_UINT8, &f->batalion_recruit_type);
        iob->bind(BIND_SIGNATURE_UINT8, &f->reseach_radius);
        iob->bind(BIND_SIGNATURE_UINT8, &f->has_military_training);
        iob->bind(BIND_SIGNATURE_UINT8, &f->herd_point);

        iob->bind____skip(2);                                  //     vv 6 hp per ostich?
        iob->bind(BIND_SIGNATURE_INT16, &f->total_damage);     // --> 18
        iob->bind(BIND_SIGNATURE_INT16, &f->max_total_damage); // 50
        iob->bind(BIND_SIGNATURE_INT8, &f->recent_fight);
        iob->bind____skip(1);
        iob->bind_u16(f->experience);
        iob->bind(BIND_SIGNATURE_INT16, &f->wait_ticks); // --> 8 --> 0 ??????
        // The enemy march cycle (OG regroup/advance/halt ticks) lives in bytes older saves always wrote as
        // zero; the battalion index is recomputed on every enemy update.
        iob->bind(BIND_SIGNATURE_INT16, &f->enemy_state.duration_halt);
        iob->bind(BIND_SIGNATURE_INT16, &f->enemy_state.duration_advance);
        f->enemy_batalion_index = 0;

        iob->bind(BIND_SIGNATURE_UINT8, &f->is_halted);
        iob->bind____skip(1);
        iob->bind(BIND_SIGNATURE_INT16, &f->missile_fired);
        iob->bind(BIND_SIGNATURE_INT16, &f->missile_attack_timeout);
        iob->bind(BIND_SIGNATURE_INT16, &f->missile_attack_formation_id);
        iob->bind(BIND_SIGNATURE_INT16, &f->prev.layout);
        iob->bind(BIND_SIGNATURE_INT16, &f->cursed_by_seth);
        iob->bind(BIND_SIGNATURE_UINT8, &f->months_low_morale);
        f->months_very_low_morale = 0;
        iob->bind(BIND_SIGNATURE_UINT8, &f->empire_service);
        iob->bind(BIND_SIGNATURE_UINT8, &f->in_distant_battle);
        iob->bind(BIND_SIGNATURE_UINT8, &f->is_herd); // 2
        iob->bind(BIND_SIGNATURE_UINT8, &f->enemy_type);
        iob->bind(BIND_SIGNATURE_UINT8, &f->direction);
        iob->bind(BIND_SIGNATURE_TILE2I, f->prev.home);
        iob->bind(BIND_SIGNATURE_UINT8, &f->unknown_fired);
        iob->bind(BIND_SIGNATURE_UINT8, &f->orientation);
        iob->bind(BIND_SIGNATURE_UINT8, &f->months_from_home);
        iob->bind(BIND_SIGNATURE_UINT8, &f->months_very_low_morale);
        iob->bind(BIND_SIGNATURE_UINT8, &f->invasion_id);
        iob->bind(BIND_SIGNATURE_UINT8, &f->herd_spawn_delay);      // --> 4
        iob->bind(BIND_SIGNATURE_UINT8, &f->herd_direction);        // 6
        iob->bind(BIND_SIGNATURE_UINT8, &f->failed_creation_count); // 6
        iob->bind(BIND_SIGNATURE_INT16, &f->enemy_state.duration_regroup);
        iob->bind(BIND_SIGNATURE_UINT8, &f->ticks_without_target);
        iob->bind____skip(2);
        iob->bind____skip(17);
        iob->bind(BIND_SIGNATURE_INT16, &f->invasion_sequence);

        // ship_figure_id / request_event_id are runtime embark/request links.
        f->ship_figure_id = 0;
        f->request_event_id = -1;

        if (!f->home.valid() && f->is_herd) {
            memset(f, 0, sizeof(formation));
        }
    }
}

void formations_chunk::reset() {
    g_formations.clear_all();
}

void formations_info_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = g_formations.formations;
    int tmp = 0;
    iob->bind(BIND_SIGNATURE_INT32, &tmp);
    iob->bind(BIND_SIGNATURE_INT32, &tmp);
    iob->bind(BIND_SIGNATURE_INT32, &tmp);
}
