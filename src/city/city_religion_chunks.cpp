#include "city/city_religion_chunks.h"

#include "city/city_religion.h"
#include "io/io_buffer.h"
#include "city/city_religion_osiris.h"

void city_gods_chunk::bind_data(io_buffer* iob) {
    iob->bind(BIND_SIGNATURE_INT32, &city_gods().bast_curse_active);
    iob->bind(BIND_SIGNATURE_INT32, &city_gods().seth_crush_enemy_troops);
    iob->bind(BIND_SIGNATURE_INT8, &god_osiris.sank_ships);
    iob->bind(BIND_SIGNATURE_UINT8, &city_gods().coverage_common);
    iob->bind(BIND_SIGNATURE_UINT8, &city_gods().coverage[GOD_OSIRIS]);
    iob->bind(BIND_SIGNATURE_UINT8, &city_gods().coverage[GOD_RA]);
    iob->bind(BIND_SIGNATURE_UINT8, &city_gods().coverage[GOD_PTAH]);
    iob->bind(BIND_SIGNATURE_UINT8, &city_gods().coverage[GOD_SETH]);
    iob->bind(BIND_SIGNATURE_UINT8, &city_gods().coverage[GOD_BAST]);
    for (int i = 0; i < MAX_GODS; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &city_gods().gods[i].target_mood);
    }
    for (int i = 0; i < MAX_GODS; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &city_gods().gods[i].mood);
    }
    for (int i = 0; i < MAX_GODS; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &city_gods().gods[i].wrath_bolts);
    }
    for (int i = 0; i < MAX_GODS; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &city_gods().gods[i].months_since_festival);
    }
    iob->bind(BIND_SIGNATURE_INT32, &city_gods().least_happy_god);
    iob->bind(BIND_SIGNATURE_UINT8, &city_gods().ra_150_export_profits_months_left);
    iob->bind(BIND_SIGNATURE_INT32, &city_gods().angry_message_delay);
    iob->bind(BIND_SIGNATURE_UINT8, &city_gods().ra_no_traders_months_left);
    for (int i = 0; i < MAX_GODS; i++) {
        iob->bind(BIND_SIGNATURE_UINT8, &city_gods().gods[i].happy_ankhs);
    }
    iob->bind(BIND_SIGNATURE_UINT8, &city_gods().ra_slightly_increased_trading_months_left);
    iob->bind(BIND_SIGNATURE_UINT8, &city_gods().ra_harshly_reduced_trading_months_left);
    iob->bind(BIND_SIGNATURE_UINT8, &city_gods().ra_slightly_reduced_trading_months_left);
    iob->bind(BIND_SIGNATURE_UINT8, &city_gods().seth_protect_player_troops_months);
    iob->bind(BIND_SIGNATURE_UINT8, &city_gods().osiris_double_farm_yield_days);
    iob->bind(BIND_SIGNATURE_UINT8, &city_gods().osiris_flood_will_destroy_active);
    verify_no_crash(iob->get_offset() == city_gods_chunk::size);
}
