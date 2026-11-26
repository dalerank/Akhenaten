#include "io/gamestate/presentation_chunks.h"

#include "widget/city/clouds.h"
#include "io/io_buffer.h"

void clouds_chunk::bind_data(io_buffer* iob) {
    int32_t count = (int32_t)std::min<size_t>(clouds().clouds.size(), 16);
    iob->bind(BIND_SIGNATURE_INT32, &count);
    for (int i = 0; i < 16; ++i) {
        vec2i dummy;
        vec2i& pos = (i < (int)clouds().clouds.size()) ? clouds().clouds[i].pos : dummy;
        iob->bind(BIND_SIGNATURE_INT32, &pos.x);
        iob->bind(BIND_SIGNATURE_INT32, &pos.y);
    }
}

void clouds_chunk::load_defaults() {
    for (auto& cloud : clouds().clouds) {
        cloud.pos = {0, 0};
    }
}
