#include "io/gamestate/presentation_chunks.h"

#include "content/mods.h"
#include "io/io_buffer.h"

#include <algorithm>

static constexpr int MODS_CHUNK_MAX = 32;

void mods_chunk::bind_data(io_buffer* iob, size_t version) {
    (void)version;
    std::vector<saved_mod> list;
    if (!iob->is_read_access()) {
        list = mods_active_list();
    }
    uint16_t count = (uint16_t)std::min<size_t>(list.size(), MODS_CHUNK_MAX);
    uint16_t reserved = 0;
    iob->bind(BIND_SIGNATURE_UINT16, &count);
    iob->bind(BIND_SIGNATURE_UINT16, &reserved);
    list.resize(MODS_CHUNK_MAX);
    for (auto& m : list) {
        iob->bind_xstr<48>(m.id);
        iob->bind_xstr<16>(m.version);
    }
    if (iob->is_read_access()) {
        list.resize(std::min<int>(count, MODS_CHUNK_MAX));
        mods_check_save(list);
    }
}

void mods_chunk::load_defaults(size_t version) {
    mods_forget_saved();
}
