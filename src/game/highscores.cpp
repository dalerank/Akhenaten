#include "highscores.h"

#include "core/buffer.h"
#include "core/log.h"
#include "core/string.h"
#include "io/io.h"
#include "platform/platform.h"

highscores_t g_highscores;

constexpr int JAS_FILE_SIZE = MAX_HIGHSCORE_ENTRIES * PLAYER_RECORD_CHUNK_SIZE; // 7600
constexpr pcstr JAS_FILE_NAME = "highscore.jas";

vfs::path highscores_t::file_path() const {
    return vfs::path(platform.user_directory(), "/", JAS_FILE_NAME);
}

void highscores_t::load() {
    for (auto& record : records) {
        record = player_record();
    }
    num_entries = 0;

    buffer buf(JAS_FILE_SIZE);
    if (io_read_file_into_buffer(file_path(), NOT_LOCALIZED, &buf, JAS_FILE_SIZE) != JAS_FILE_SIZE
        && io_read_file_into_buffer(vfs::path("Save/", JAS_FILE_NAME), NOT_LOCALIZED, &buf, JAS_FILE_SIZE)
             != JAS_FILE_SIZE) {
        return;
    }

    for (auto& record : records) {
        record.read(buf);
        if (record.nonempty) {
            ++num_entries;
        }
    }
}

bool highscores_t::save() const {
    buffer buf(JAS_FILE_SIZE);
    for (const auto& record : records) {
        record.write(buf);
    }

    const vfs::path path = file_path();
    if (io_write_buffer_to_file(path, &buf, JAS_FILE_SIZE) != JAS_FILE_SIZE) {
        logs::error("highscores: failed to write %s", path.c_str());
        return false;
    }
    return true;
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

e_highscore_result highscores_t::record_mission(const mission_result_t& result, int score, int monuments) {
    last_result = e_highscore_result_none;
    previous_name.clear();
    const int mission = result.scenario_id;
    if (mission < 0 || mission >= MAX_HIGHSCORE_ENTRIES) {
        return last_result;
    }

    player_record candidate;
    candidate.assign(result);
    candidate.score = (uint32_t)score;
    candidate.monuments = (uint32_t)monuments;

    load();
    player_record& record = records[mission];
    const bool beaten = (int32_t)record.score < score;
    if (!record.nonempty) {
        last_result = e_highscore_result_new;
    } else if (string_compare_case_insensitive((pcstr)record.player_name, (pcstr)candidate.player_name) == 0) {
        last_result = beaten ? e_highscore_result_own_beaten : e_highscore_result_own_kept;
    } else {
        last_result = beaten ? e_highscore_result_other_beaten : e_highscore_result_other_kept;
        previous_name = (pcstr)record.player_name;
    }

    if (last_result == e_highscore_result_new || beaten) {
        record = candidate;
        save();
        load();
    }
    return last_result;
}
