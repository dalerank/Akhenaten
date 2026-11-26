#include "city/city_local_cults_chunks.h"

#include "city/city_local_cults.h"
#include "io/io_buffer.h"

void local_cults_chunk::bind_data(io_buffer* iob) {
    auto& lc = city_local_cults();
    for (int i = 0; i < LOCAL_CULT_MAX; ++i) {
        iob->bind(BIND_SIGNATURE_UINT8, &lc.cults[i].unlocked);
        iob->bind(BIND_SIGNATURE_UINT8, &lc.cults[i].active);
        iob->bind(BIND_SIGNATURE_UINT8, &lc.cults[i].appeased_months);
        iob->bind(BIND_SIGNATURE_UINT8, &lc.cults[i].reserved);
    }
    iob->bind(BIND_SIGNATURE_UINT8, &lc.mission_restricts);
    iob->bind(BIND_SIGNATURE_UINT8, &lc.farm_bonus_months);
    iob->bind(BIND_SIGNATURE_UINT8, &lc.war_bonus_months);
    iob->bind(BIND_SIGNATURE_UINT8, &lc.craft_bonus_months);
    iob->bind(BIND_SIGNATURE_UINT8, &lc.planned_theme);
    iob->bind(BIND_SIGNATURE_UINT8, &lc.planned_cult);
    iob->bind(BIND_SIGNATURE_UINT8, &lc.last_rite_month);
    iob->bind(BIND_SIGNATURE_INT16, &lc.last_rite_year);
    iob->bind(BIND_SIGNATURE_UINT8, &lc.last_rite_index);
    iob->bind(BIND_SIGNATURE_UINT8, &lc.reserved_pad[0]);
    iob->bind(BIND_SIGNATURE_UINT8, &lc.reserved_pad[1]);
    iob->bind(BIND_SIGNATURE_UINT8, &lc.reserved_pad[2]);
    // 4*4 + 13 = 29; pad to 64
    iob->bind____skip(35);
}

void local_cults_chunk::load_defaults() {
    city_local_cults() = {};
}
