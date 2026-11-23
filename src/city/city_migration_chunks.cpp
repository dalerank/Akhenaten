#include "city/city_migration_chunks.h"

#include "city/city.h"
#include "io/io_buffer.h"

void city_migration_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = g_city;
    iob->bind(BIND_SIGNATURE_UINT8, &data.migration.immigration_amount_per_batch);
    iob->bind(BIND_SIGNATURE_UINT8, &data.migration.emigration_amount_per_batch);
    iob->bind(BIND_SIGNATURE_UINT8, &data.migration.emigration_queue_size);
    iob->bind(BIND_SIGNATURE_UINT8, &data.migration.immigration_queue_size);
    iob->bind(BIND_SIGNATURE_UINT8, &data.migration.immigrated_today);
    iob->bind(BIND_SIGNATURE_UINT8, &data.migration.emigrated_today);
    iob->bind(BIND_SIGNATURE_UINT8, &data.migration.refused_immigrants_today);
    iob->bind(BIND_SIGNATURE_INT8, &data.migration.percentage);
    iob->bind(BIND_SIGNATURE_UINT16, &data.migration.emigration_duration);
    iob->bind(BIND_SIGNATURE_UINT16, &data.migration.immigration_duration);
    iob->bind(BIND_SIGNATURE_UINT16, &data.migration.newcomers);
    iob->bind(BIND_SIGNATURE_UINT16, &data.migration.nobles_leave_city_this_year);
    iob->bind(BIND_SIGNATURE_UINT8, &data.migration.percentage_by_sentiment);
    iob->bind(BIND_SIGNATURE_INT32, &data.migration.population_cap);
    iob->bind(BIND_SIGNATURE_INT8, &data.migration.no_immigration_cause);
    iob->bind(BIND_SIGNATURE_UINT8, &data.migration.emigration_message_shown);
    verify_no_crash(iob->get_offset() == city_migration_chunk::size);
}
