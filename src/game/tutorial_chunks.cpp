#include "game/tutorial_chunks.h"

#include "io/io_buffer.h"

void tutorial_flags_struct_chunk::bind_data(io_buffer* iob, size_t version) {
    uint16_t tmp = 0;
    iob->bind(BIND_SIGNATURE_UINT16, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
    iob->bind(BIND_SIGNATURE_UINT8, &tmp);
}
