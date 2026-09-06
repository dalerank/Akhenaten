#include "player_profile.h"

#include "content/vfs.h"
#include "core/buffer.h"
#include "core/log.h"
#include "core/string.h"
#include "game/game_config.h"
#include "io/gamestate/boilerplate.h"
#include "io/io.h"

#include <algorithm>

player_profile_t g_player;

namespace {

    // Our own progress file, written into the dynasty folder. The original <player>.dat is only
    // ever read: its layout is not fully decoded (see below), so writing it back would be a guess.
    constexpr pcstr PROGRESS_FILE = "progress.dat";
    constexpr pcstr PROGRESS_TEMP_FILE = "progress.tmp";
    constexpr uint32_t PROGRESS_MAGIC = 0x50504b41; // 'AKPP'
    constexpr uint32_t PROGRESS_VERSION = 1;
    constexpr int PROGRESS_HEADER_SIZE = 4 + 4 + MAX_PLAYER_NAME + 4;
    constexpr int PROGRESS_ENTRY_SIZE = 4 + PLAYER_RECORD_CHUNK_SIZE;
    constexpr int PROGRESS_FILE_SIZE = PROGRESS_HEADER_SIZE + MAX_PLAYER_SCENARIOS * PROGRESS_ENTRY_SIZE;

    // Layout of the original <player>.dat, in file order:
    //   100 x 64  scenario chunks the game does not read back   0     .. 6400
    //   4         field count for the Pharaoh campaign (38)     6400  .. 6404
    //   100 x 50  scenario names                                6404  .. 11404
    //   4         unknown (35)                                  11404 .. 11408
    //   N         path to the last autosave_replay file         11408 .. 11408+N
    //   4         unknown (0)
    //   100 x 76  scenario records                              .. 19100 (end of file)
    //
    // N is the one field whose size is not certain. 64 bytes leaves 24 bytes of the file
    // unaccounted for; 88 bytes makes the layout add up to exactly DAT_FILE_SIZE. Rather than
    // guess, both candidates are tried and the one that yields plausible records is used.
    constexpr int DAT_FILE_SIZE = 19100;
    constexpr int DAT_CHUNK_SIZE = 64;
    constexpr int DAT_MAP_NAME_SIZE = 50;
    constexpr int DAT_NAMES_OFFSET = MAX_PLAYER_SCENARIOS * DAT_CHUNK_SIZE + 4;
    constexpr int DAT_AUTOSAVE_PATH_OFFSET = DAT_NAMES_OFFSET + MAX_PLAYER_SCENARIOS * DAT_MAP_NAME_SIZE + 4;
    constexpr int DAT_RECORDS_OFFSET_LONG_PATH = DAT_FILE_SIZE - MAX_PLAYER_SCENARIOS * PLAYER_RECORD_CHUNK_SIZE;
    constexpr int DAT_RECORDS_OFFSET_SHORT_PATH = DAT_AUTOSAVE_PATH_OFFSET + 64 + 4;

    bool records_plausible_at(buffer& buf, int offset) {
        buf.set_offset(offset);

        player_record probe;
        for (int i = 0; i < MAX_PLAYER_SCENARIOS; ++i) {
            probe.read(buf);
            if (!probe.looks_plausible()) {
                return false;
            }
        }

        return true;
    }

} // namespace

vfs::path player_profile_t::folder() const {
    return fullpath_player_folder(name.c_str());
}

bool player_profile_t::create(pcstr player_name) {
    if (!player_name || !*player_name) {
        return false;
    }

    // A fresh dynasty becomes the current one, so its folder and its (empty) progress are
    // what the rest of the game sees. write_family_marker() derives the folder from the
    // configured player name, which select() publishes.
    g_player.select(player_name);
    return GamestateIO::write_family_marker();
}

bool player_profile_t::remove(pcstr player_name) {
    if (!player_name || !*player_name) {
        return false;
    }

    vfs::remove_folder(fullpath_player_folder(player_name));
    vfs::file_remove(vfs::path(vfs::SAVE_FOLDER, "/", player_name, ".dat"));

    if (g_player.name == player_name) {
        g_player.select("");
    }

    return true;
}

bool player_profile_t::select(pcstr player_name) {
    name = player_name ? player_name : "";
    game_features::gameopt_player_name = name;

    for (auto& record : records) {
        record = player_record();
    }
    last_autosave_path.clear();

    if (!valid()) {
        return false;
    }

    const bool loaded = load_progress() || import_legacy_dat();

    if (last_autosave_path.empty() || !vfs::file_exists(last_autosave_path)) {
        find_last_autosave();
    }

    return loaded;
}

bool player_profile_t::load_progress() {
    if (!valid()) {
        return false;
    }

    const vfs::path file(folder().c_str(), "/", PROGRESS_FILE);
    buffer buf(PROGRESS_FILE_SIZE);
    if (!io_read_file_into_buffer(file, NOT_LOCALIZED, &buf, PROGRESS_FILE_SIZE)) {
        return false;
    }

    if (buf.read_u32() != PROGRESS_MAGIC) {
        logs::error("player profile: %s is not a progress file", file.c_str());
        return false;
    }

    const uint32_t version = buf.read_u32();
    if (version > PROGRESS_VERSION) {
        logs::error("player profile: %s has version %u, this build reads up to %u", file.c_str(), version,
          PROGRESS_VERSION);
        return false;
    }

    uint8_t stored_name[MAX_PLAYER_NAME] = {};
    buf.read_raw(stored_name, MAX_PLAYER_NAME);

    const uint32_t count = buf.read_u32();
    for (uint32_t i = 0; i < count && i < (uint32_t)MAX_PLAYER_SCENARIOS; ++i) {
        const uint32_t scenario_id = buf.read_u32();
        player_record entry;
        entry.read(buf);

        if (scenario_id < (uint32_t)MAX_PLAYER_SCENARIOS) {
            records[scenario_id] = entry;
        }
    }

    logs::info("player profile: loaded %u records from %s", count, file.c_str());
    return true;
}

bool player_profile_t::save() const {
    if (!valid()) {
        return false;
    }

    uint32_t count = 0;
    for (const auto& record : records) {
        count += record.nonempty ? 1 : 0;
    }

    buffer buf(PROGRESS_FILE_SIZE);
    buf.write_u32(PROGRESS_MAGIC);
    buf.write_u32(PROGRESS_VERSION);

    uint8_t stored_name[MAX_PLAYER_NAME] = {};
    string_copy((const uint8_t*)name.c_str(), stored_name, MAX_PLAYER_NAME);
    buf.write_raw(stored_name, MAX_PLAYER_NAME);

    buf.write_u32(count);
    for (int i = 0; i < MAX_PLAYER_SCENARIOS; ++i) {
        if (!records[i].nonempty) {
            continue;
        }
        buf.write_u32((uint32_t)i);
        records[i].write(buf);
    }

    const int size = (int)buf.get_offset();
    const vfs::path dir = folder();
    vfs::create_folders(vfs::content_path(dir.c_str()));

    // Write beside the target and publish with a rename, so an interrupted write cannot
    // leave a half-written progress file behind.
    const vfs::path temp_file(dir.c_str(), "/", PROGRESS_TEMP_FILE);
    const vfs::path file(dir.c_str(), "/", PROGRESS_FILE);
    if (io_write_buffer_to_file(temp_file, &buf, size) != size) {
        logs::error("player profile: failed to write %s", temp_file.c_str());
        return false;
    }

    if (!vfs::file_rename_os(temp_file, file)) {
        return false;
    }

    logs::info("player profile: saved %u records to %s", count, file.c_str());
    return true;
}

bool player_profile_t::import_legacy_dat() {
    const vfs::path legacy(vfs::SAVE_FOLDER, "/", name.c_str(), ".dat");
    buffer buf(DAT_FILE_SIZE);
    const int size = io_read_file_into_buffer(legacy, NOT_LOCALIZED, &buf, DAT_FILE_SIZE);
    if (!size) {
        return false;
    }

    int records_offset = DAT_RECORDS_OFFSET_LONG_PATH;
    if (!records_plausible_at(buf, records_offset) && records_plausible_at(buf, DAT_RECORDS_OFFSET_SHORT_PATH)) {
        records_offset = DAT_RECORDS_OFFSET_SHORT_PATH;
    }

    const int path_size = records_offset - 4 - DAT_AUTOSAVE_PATH_OFFSET;
    bstring256 raw_autosave_path;
    buf.set_offset(DAT_AUTOSAVE_PATH_OFFSET);
    buf.read_raw(raw_autosave_path.data(), std::min<int>(path_size, raw_autosave_path.capacity - 1));
    raw_autosave_path.data()[raw_autosave_path.capacity - 1] = 0;
    last_autosave_path = raw_autosave_path.c_str();

    buf.set_offset(records_offset);
    for (auto& record : records) {
        record.read(buf);
    }

    logs::info("player profile: imported %s (records at %d)", legacy.c_str(), records_offset);
    return true;
}

void player_profile_t::find_last_autosave() {
    last_autosave_path.clear();

    if (!valid()) {
        return;
    }

    const vfs::path dir = folder();
    for (pcstr filename : {"/autosave_replay.svx", "/autosave_replay.sav"}) {
        const vfs::path candidate(dir.c_str(), filename);
        if (vfs::file_exists(candidate)) {
            last_autosave_path = candidate;
            return;
        }
    }
}

const player_record& player_profile_t::record(int scenario_id) const {
    static const player_record empty_record;

    if (scenario_id < 0 || scenario_id >= MAX_PLAYER_SCENARIOS) {
        return empty_record;
    }

    return records[scenario_id];
}

bool player_profile_t::beaten(int scenario_id) const {
    return record(scenario_id).nonempty;
}

void player_profile_t::record_win(const mission_result_t& result) {
    if (result.scenario_id < 0 || result.scenario_id >= MAX_PLAYER_SCENARIOS) {
        return;
    }

    records[result.scenario_id].assign(result);
}
