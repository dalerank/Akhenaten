#include "city/city_migration_chunks.h"

#include "city/city_migration.h"
#include "io/io_buffer.h"

void city_migration_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& migration = city_migration();
    iob->bind(BIND_SIGNATURE_UINT8, &migration.immigration_amount_per_batch);
    iob->bind(BIND_SIGNATURE_UINT8, &migration.emigration_amount_per_batch);
    iob->bind(BIND_SIGNATURE_UINT8, &migration.emigration_queue_size);
    iob->bind(BIND_SIGNATURE_UINT8, &migration.immigration_queue_size);
    iob->bind(BIND_SIGNATURE_UINT8, &migration.immigrated_today);
    iob->bind(BIND_SIGNATURE_UINT8, &migration.emigrated_today);
    iob->bind(BIND_SIGNATURE_UINT8, &migration.refused_immigrants_today);
    iob->bind(BIND_SIGNATURE_INT8, &migration.percentage);
    iob->bind(BIND_SIGNATURE_UINT16, &migration.emigration_duration);
    iob->bind(BIND_SIGNATURE_UINT16, &migration.immigration_duration);
    iob->bind(BIND_SIGNATURE_UINT16, &migration.newcomers);
    iob->bind(BIND_SIGNATURE_UINT16, &migration.nobles_leave_city_this_year);
    iob->bind(BIND_SIGNATURE_UINT8, &migration.percentage_by_sentiment);
    iob->bind(BIND_SIGNATURE_INT32, &migration.population_cap);
    iob->bind(BIND_SIGNATURE_INT8, &migration.no_immigration_cause);
    iob->bind(BIND_SIGNATURE_UINT8, &migration.emigration_message_shown);
    verify_no_crash(iob->get_offset() == city_migration_chunk::size);
}
