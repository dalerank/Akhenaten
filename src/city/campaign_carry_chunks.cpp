#include "city/campaign_carry_chunks.h"

#include "city/campaign_carry.h"
#include "io/io_buffer.h"

void campaign_carry_troops_chunk::bind_data(io_buffer* iob, size_t version) {
    for (int i = 0; i < TROOP_CARRY_MAX; i++) {
        auto& s = g_campaign_carry.troops[i];
        iob->bind_u8(s.has_data);
        iob->bind_u8(s.pending);
        iob->bind_u8(s.num_figures);
        iob->bind_u8(s.has_military_training);
        iob->bind_i16(s.morale);
        iob->bind_u16(s.experience);
    }
    iob->bind_u8(g_campaign_carry.notice_posted);
    iob->bind____skip(7);
}

void campaign_carry_troops_chunk::load_defaults(size_t version) {
    // troop carry lives outside city_data, so a
    // save without this chunk would keep the
    // previous session's snapshot - the exact bug
    // pre_load() was patched for
    g_campaign_carry.clear_troops();
}

void campaign_carry_troops_chunk::reset() {
    g_campaign_carry.clear_troops();
}

void campaign_carry_monuments_chunk::bind_data(io_buffer* iob, size_t version) {
    for (int i = 0; i < CAMPAIGN_CARRY_MONUMENT_MAX; i++) {
        auto& s = g_campaign_carry.monuments[i];
        iob->bind_u8(s.has_data);
        iob->bind_u8(s.orientation);
        iob->bind_u8(s.variant);
        iob->bind_u8(s.pad);
        iob->bind_u16(s.type);
        iob->bind_i16(s.tile_x);
        iob->bind_i16(s.tile_y);
    }
}

void campaign_carry_monuments_chunk::load_defaults(size_t version) {
    g_campaign_carry.clear_monuments();
}

void campaign_carry_monuments_chunk::reset() {
    g_campaign_carry.clear_monuments();
}
