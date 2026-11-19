#include "figure/enemy_army_chunks.h"

#include "figure/enemy_army.h"
#include "io/io_buffer.h"

void iob_enemy_armies_stats_chunk::bind_data(io_buffer* iob, size_t version) {
    iob->bind_i32(g_enemy_army_in_city.enemy_formations);
    iob->bind_i32(g_enemy_army_in_city.enemy_strength);
    iob->bind_i32(g_enemy_army_in_city.batlion_formations);
    iob->bind_i32(g_enemy_army_in_city.batalion_strength);
    iob->bind_i32(g_enemy_army_in_city.days_since_pharaoh_influence_calculation);
    iob->bind____skip(256);

    for (int i = 0; i < g_enemy_armies.MAX_ENEMY_ARMIES; i++) {
        iob->bind_u8(g_enemy_armies.data[i].formation_id);
        iob->bind_tile(g_enemy_armies.data[i].home);
        iob->bind_u8(g_enemy_armies.data[i].layout);
        iob->bind_tile(g_enemy_armies.data[i].destination);
        iob->bind_u16(g_enemy_armies.data[i].destination_building_id);
        iob->bind_u8(g_enemy_armies.data[i].num_batalions);
        iob->bind_bool(g_enemy_armies.data[i].ignore_pharaoh_soldiers);
        iob->bind_u8(g_enemy_armies.data[i].buildings_to_destroy);
        iob->bind_u8(g_enemy_armies.data[i].buildings_destroyed);
        iob->bind_u16(g_enemy_armies.data[i].want_money);
        iob->bind_u16(g_enemy_armies.data[i].grab_money);
        iob->bind____skip(64);
    }
}

void iob_enemy_armies_stats_chunk::load_defaults(size_t version) {
    // saves older than v170 carry no army stats at all
    g_enemy_army_in_city = {};
    g_enemy_armies.clear();
}

void iob_enemy_armies_stats_chunk::reset() {
    g_enemy_armies.clear();
}
