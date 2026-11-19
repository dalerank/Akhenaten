#include "city/city_floods_chunks.h"

#include "city/city_floods.h"
#include "io/io_buffer.h"

void floodplain_settings_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = g_floods;

    iob->bind(BIND_SIGNATURE_INT32, &data.season_initial);
    iob->bind(BIND_SIGNATURE_INT32, &data.duration_initial);
    iob->bind(BIND_SIGNATURE_INT32, &data.quality_initial);
    iob->bind(BIND_SIGNATURE_INT32, &data.season);
    iob->bind(BIND_SIGNATURE_INT32, &data.duration);
    iob->bind(BIND_SIGNATURE_INT32, &data.quality_current);
    iob->bind(BIND_SIGNATURE_INT32, &data.unk00);
    iob->bind(BIND_SIGNATURE_UINT8, &data.quality_next);
    iob->bind(BIND_SIGNATURE_UINT8, &data.flood_progress);
    iob->bind(BIND_SIGNATURE_UINT8, &data.flood_progress_target);
    iob->bind____skip(1);
    iob->bind(BIND_SIGNATURE_INT32, &data.quality_last);
}
