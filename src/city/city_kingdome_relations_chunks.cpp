#include "city/city_kingdome_relations_chunks.h"

#include "city/city.h"
#include "io/io_buffer.h"
#include "game/game_environment.h"

void city_kingdome_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = g_city;
    iob->bind(BIND_SIGNATURE_UINT8, &data.kingdome.salary_amount);
    iob->bind(BIND_SIGNATURE_UINT8, &data.kingdome.salary_rank);
    iob->bind_u16(data.kingdome.campaign_carry_personal_savings);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.debt_state);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.months_in_debt);
    iob->bind(BIND_SIGNATURE_UINT8, &data.kingdome.rating_cap);
    iob->bind(BIND_SIGNATURE_UINT16, &data.kingdome.invasion.duration_day_countdown);
    iob->bind(BIND_SIGNATURE_INT8, &data.kingdome.invasion.warnings_given);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.invasion.days_until_invasion);
    iob->bind(BIND_SIGNATURE_UINT8, &data.kingdome.invasion.retreat_message_shown);
    iob->bind(BIND_SIGNATURE_UINT8, &data.kingdome.invasion.favour_only);
    iob->bind(BIND_SIGNATURE_UINT8, &data.kingdome.invasion.cheated);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.invasion.count);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.invasion.size);
    iob->bind(BIND_SIGNATURE_UINT16, &data.kingdome.invasion.soldiers_killed);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.rating);
    iob->bind(BIND_SIGNATURE_UINT8, &data.kingdome.player_rank);
    iob->bind_u16(data.kingdome.personal_savings);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.months_since_gift);
    iob->bind(BIND_SIGNATURE_INT32, &data.kingdome.gift_overdose_penalty);
    iob->bind(BIND_SIGNATURE_INT8, &data.kingdome.kingdom_salary_penalty);
    iob->bind(BIND_SIGNATURE_INT8, &data.kingdome.kingdom_milestone_penalty);
    iob->bind(BIND_SIGNATURE_INT8, &data.kingdome.kingdom_ignored_request_penalty);
    iob->bind(BIND_SIGNATURE_UINT8, &data.kingdome.rating_last_year);
    iob->bind(BIND_SIGNATURE_UINT8, &data.kingdome.kingdom_change);
    iob->bind(BIND_SIGNATURE_XSTR, data.kingdome.player_name_adversary, MAX_PLAYER_NAME);
    iob->bind(BIND_SIGNATURE_XSTR, data.kingdome.player_name, MAX_PLAYER_NAME);
    verify_no_crash(iob->get_offset() == city_kingdome_chunk::size);
}
