#include "city/city_kingdome_relations_chunks.h"

#include "city/city_kingdome_relations.h"
#include "io/io_buffer.h"
#include "game/game_environment.h"

void city_kingdome_chunk::bind_data(io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_UINT8, &city_kingdome().salary_amount);
    iob->bind(BIND_SIGNATURE_UINT8, &city_kingdome().salary_rank);
    iob->bind_u16(city_kingdome().campaign_carry_personal_savings);
    iob->bind(BIND_SIGNATURE_INT32, &city_kingdome().debt_state);
    iob->bind(BIND_SIGNATURE_INT32, &city_kingdome().months_in_debt);
    iob->bind(BIND_SIGNATURE_UINT8, &city_kingdome().rating_cap);
    iob->bind(BIND_SIGNATURE_UINT16, &city_kingdome().invasion.duration_day_countdown);
    iob->bind(BIND_SIGNATURE_INT8, &city_kingdome().invasion.warnings_given);
    iob->bind(BIND_SIGNATURE_INT32, &city_kingdome().invasion.days_until_invasion);
    iob->bind(BIND_SIGNATURE_UINT8, &city_kingdome().invasion.retreat_message_shown);
    iob->bind(BIND_SIGNATURE_UINT8, &city_kingdome().invasion.favour_only);
    iob->bind(BIND_SIGNATURE_UINT8, &city_kingdome().invasion.cheated);
    iob->bind(BIND_SIGNATURE_INT32, &city_kingdome().invasion.count);
    iob->bind(BIND_SIGNATURE_INT32, &city_kingdome().invasion.size);
    iob->bind(BIND_SIGNATURE_UINT16, &city_kingdome().invasion.soldiers_killed);
    iob->bind(BIND_SIGNATURE_INT32, &city_kingdome().rating);
    iob->bind(BIND_SIGNATURE_UINT8, &city_kingdome().player_rank);
    iob->bind_u16(city_kingdome().personal_savings);
    iob->bind(BIND_SIGNATURE_INT32, &city_kingdome().months_since_gift);
    iob->bind(BIND_SIGNATURE_INT32, &city_kingdome().gift_overdose_penalty);
    iob->bind(BIND_SIGNATURE_INT8, &city_kingdome().kingdom_salary_penalty);
    iob->bind(BIND_SIGNATURE_INT8, &city_kingdome().kingdom_milestone_penalty);
    iob->bind(BIND_SIGNATURE_INT8, &city_kingdome().kingdom_ignored_request_penalty);
    iob->bind(BIND_SIGNATURE_UINT8, &city_kingdome().rating_last_year);
    iob->bind(BIND_SIGNATURE_UINT8, &city_kingdome().kingdom_change);
    iob->bind(BIND_SIGNATURE_XSTR, city_kingdome().player_name_adversary, MAX_PLAYER_NAME);
    iob->bind(BIND_SIGNATURE_XSTR, city_kingdome().player_name, MAX_PLAYER_NAME);
    verify_no_crash(iob->get_offset() == city_kingdome_chunk::size);
}
