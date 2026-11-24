#include "city/city_trade_chunks.h"

#include "city/city_trade.h"
#include "io/io_buffer.h"

void city_trade_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& trade = city_trade();
    iob->bind(BIND_SIGNATURE_INT32, &trade.caravan_import_resource);
    iob->bind(BIND_SIGNATURE_INT32, &trade.caravan_backup_import_resource);
    iob->bind(BIND_SIGNATURE_INT32, &trade.docker_import_resource);
    iob->bind(BIND_SIGNATURE_INT32, &trade.docker_export_resource);
    verify_no_crash(iob->get_offset() == city_trade_chunk::size);
}
