#include "highscores.h"

#include "core/buffer.h"
#include "io/io.h"

highscores_t g_highscores;

constexpr int JAS_FILE_SIZE = MAX_HIGHSCORE_ENTRIES * PLAYER_RECORD_CHUNK_SIZE; // 7600

void highscores_t::load() {
    for (auto& record : records) {
        record = player_record();
    }
    num_entries = 0;

    buffer buf(JAS_FILE_SIZE);
    if (!io_read_file_into_buffer("Save/highscore.jas", NOT_LOCALIZED, &buf, JAS_FILE_SIZE)) {
        return;
    }

    for (auto& record : records) {
        record.read(buf);
        if (record.nonempty) {
            ++num_entries;
        }
    }
}

const player_record& highscores_t::get(int rank) const {
    static const player_record empty_record;

    if (rank < 0) {
        return empty_record;
    }

    for (const auto& record : records) {
        if (!record.nonempty) {
            continue;
        }

        if (rank == 0) {
            return record;
        }
        --rank;
    }

    return empty_record;
}
