#include "scenario/distant_battle_chunks.h"

#include "city/city.h"
#include "io/io_buffer.h"
#include "scenario/distant_battle.h"

void city_distant_battle_chunk::bind_data(io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_INT8, &g_distant_battle.battle.egyptian_months_to_travel_forth);
    iob->bind(BIND_SIGNATURE_INT8, &g_distant_battle.battle.city_foreign_months_left);
    iob->bind(BIND_SIGNATURE_INT8, &g_distant_battle.battle.won_count);
    iob->bind(BIND_SIGNATURE_INT8, &g_distant_battle.battle.enemy_months_traveled);
    iob->bind(BIND_SIGNATURE_INT8, &g_distant_battle.battle.egyptian_months_traveled);
    iob->bind_u8((uint8_t&)g_distant_battle.dispatched_army.state);
    iob->bind_u8(g_distant_battle.dispatched_army.await_soldiers);
    iob->bind_u8(g_distant_battle.dispatched_army.position_index);
    iob->bind_i16(g_distant_battle.source_request_event_id);
    iob->bind(BIND_SIGNATURE_UINT8, &g_distant_battle.battle.city);
    iob->bind(BIND_SIGNATURE_UINT8, &g_distant_battle.battle.enemy_strength);
    iob->bind(BIND_SIGNATURE_UINT8, &g_distant_battle.battle.egyptian_strength);
    iob->bind(BIND_SIGNATURE_INT8, &g_distant_battle.battle.months_until_battle);
    iob->bind(BIND_SIGNATURE_INT8, &g_distant_battle.battle.egyptian_months_to_travel_back);
    iob->bind(BIND_SIGNATURE_INT8, &g_distant_battle.battle.total_count);
    verify_no_crash(iob->get_offset() == city_distant_battle_chunk::size);
}
