#include "building/building_guild.h"

#include "io/io_buffer.h"

void building_guild::bind_dynamic(io_buffer *iob, size_t version) {
    iob->bind____skip(26);
    iob->bind____skip(56);

    auto &d = runtime_data();
    iob->bind(BIND_SIGNATURE_UINT8, &d.max_workers);
}

bool building_guild::has_resources() const {
    bool hase_first_resource = (base.stored_amount_first >= 100);
    return hase_first_resource;
}