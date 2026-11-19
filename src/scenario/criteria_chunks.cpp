#include "scenario/criteria_chunks.h"

#include "scenario/criteria.h"
#include "core/xvalue.h"
#include "io/io_buffer.h"

void max_year_chunk::bind_data(io_buffer* iob, size_t version) {
    iob->bind(BIND_SIGNATURE_UINT32, &xvalue<scenario_criteria_state_t>::ref().max_game_year);
}
