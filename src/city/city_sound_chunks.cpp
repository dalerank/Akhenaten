#include "city/city_sound_chunks.h"

#include "city/sound.h"
#include "core/core.h"
#include "io/io_buffer.h"

void city_sound_chunk::bind_data(io_buffer* iob, size_t version) {
    auto& sound = city_sound();
    iob->bind(BIND_SIGNATURE_INT8, &sound.march_enemy);
    iob->bind(BIND_SIGNATURE_INT8, &sound.march_horse);
    verify_no_crash(iob->get_offset() == city_sound_chunk::size);
}
