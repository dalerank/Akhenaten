#include "city/city_mission_chunks.h"

#include "city/city_mission.h"
#include "io/io_buffer.h"

void city_mission_chunk::bind_data(io_buffer* iob) {
    auto& mission = city_mission();
    iob->bind(BIND_SIGNATURE_UINT8, &mission.fired_message_shown);
    iob->bind(BIND_SIGNATURE_UINT8, &mission.victory_message_shown);
    verify_no_crash(iob->get_offset() == city_mission_chunk::size);
}
