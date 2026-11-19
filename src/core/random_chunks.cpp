#include "core/random_chunks.h"

#include "core/random.h"
#include "core/xvalue.h"
#include "io/io_buffer.h"

void random_iv_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& data = xvalue<random_data_t>::ref();
    iob->bind(BIND_SIGNATURE_UINT32, &data.iv1);
    iob->bind(BIND_SIGNATURE_UINT32, &data.iv2);
    random_bits_fill();
}
