#include "player.h"

#include "core/buffer.h"
#include "core/string.h"
#include "content/vfs.h"
#include "io/gamestate/boilerplate.h"
#include "io/io.h"
#include "io/manager.h"

#include <filesystem>

#define JAS_FILE_SIZE 7600
#define JAS_CHUNK_SIZE 76
#define MAX_JAS_ENTRIES 100

#define DAT_FILE_SIZE 19100
#define DAT_CHUNK_SIZE 64
#define DAT_CHUNKS_USED 56
#define DAT_MAP_NAMES_USED 53
#define DAT_ENTRIES_PHARAOH 38
#define DAT_ENTRIES_CLEOPATRA 15

player_record DUMMY_RECORD;

struct player_data_t {
    // highscores.jas
    player_record highscores[MAX_JAS_ENTRIES];
    int num_highscore_entries;
    buffer* jas_file = new buffer(JAS_FILE_SIZE);

    //<player>.dat
    player_unused_scenario_data unused_data[MAX_DAT_ENTRIES];
    int unk38;
    char scenario_names[MAX_DAT_ENTRIES][DAT_MAP_NAME_SIZE];
    int unk35;
    bstring64 last_autosave_path;
    int unk00;
    player_record player_scenario_records[MAX_DAT_ENTRIES];
    buffer* dat_file = new buffer(DAT_FILE_SIZE);
};

player_data_t g_player_data;

player_data_t& player_data() {
    return g_player_data;
}

uint32_t records_calc_score(float unkn, float funds, float population, float r_culture, float r_prosperity, float r_kingdom, float months, float difficulty) {
    // I have *NO CLUE* how this value works. It's just black magic.
    // In missions where it's zero, the formula checks out correctly.
    unkn = 0.0;
    return (difficulty + 1.0) / 3.0
           * ((funds / (months / 30.0)) + unkn * unkn * 20.0 / (months * months / 6400.0)
              + population * 0.002 * (r_culture + r_prosperity + r_kingdom));
}
uint32_t records_calc_score(const player_record* record) {
    return records_calc_score(record->unk09,
                              record->final_funds,
                              record->final_population,
                              record->rating_culture,
                              record->rating_prosperity,
                              record->rating_kingdom,
                              record->completion_months,
                              record->difficulty);
}
const player_record* highscores_get(int rank) {
    auto& data = player_data();
    // go through the list of records, return the nth non-empty record
    for (int i = 0; i < MAX_JAS_ENTRIES; ++i) {
        if (data.highscores[i].nonempty) {
            if (rank > 0) {
                rank--;
            } else {
                return &data.highscores[i];
            }
        }
    }
    return &DUMMY_RECORD; // return empty record when reached the end of the list
}

int highscores_count() {
    auto& data = player_data();
    return data.num_highscore_entries;
}

static void load_jas_record_chunk(buffer* buf, player_record* record) {
    auto& data = player_data();

    record->score = buf->read_u32();
    record->mission_idx = buf->read_u32();
    buf->read_raw(record->player_name, MAX_PLAYER_NAME);
    record->rating_culture = buf->read_u32();
    record->rating_prosperity = buf->read_u32();
    record->rating_kingdom = buf->read_u32();
    record->final_population = buf->read_u32();
    record->final_funds = buf->read_u32();
    record->completion_months = buf->read_u32();
    record->difficulty = buf->read_u32();
    record->unk09 = buf->read_u32();
    record->nonempty = buf->read_u32();

    // check if score in record is valid
    record->score_is_valid = record->score == records_calc_score(record);

    // increase counter
    if (record->nonempty)
        data.num_highscore_entries++;
}
void highscores_load() {
    auto& data = player_data();
    // highscore.jas
    data.jas_file->clear();
    data.jas_file->reset_offset();
    data.num_highscore_entries = 0;
    int size = io_read_file_into_buffer("Save/highscore.jas", NOT_LOCALIZED, data.jas_file, JAS_FILE_SIZE);
    if (!size)
        return;

    for (int i = 0; i < MAX_JAS_ENTRIES; ++i) // highscores
        load_jas_record_chunk(data.jas_file, &data.highscores[i]);
}

const player_record* player_get_scenario_record(int scenario_id) {
    auto& data = player_data();
    return &data.player_scenario_records[scenario_id];
}
const char* player_get_last_autosave() {
    auto& data = player_data();
    return data.last_autosave_path;
}

bool player_data_prepare_savegame(const char* filename_short) {
    // concatenate string
    bstring256 savefile = vfs::content_path(fullpath_saves(filename_short));
    bstring256 folders = vfs::content_path(fullpath_saves(""));

    vfs::create_folders(folders);
    // write file
    return FILEIO.serialize(savefile, 0, FILE_FORMAT_SAVE_FILE, latest_save_version, [] (e_file_format file_format, const int file_version) {
        FILEIO.push_chunk(4, false, "family_index", 0);
    });
}

void player_data_new(const uint8_t* player_name) {
    player_data_prepare_savegame("family.sav");
}

void player_data_delete(const uint8_t* player_name) {
    vfs::path folder_path(vfs::SAVE_FOLDER, "/", (const char*)player_name);
    vfs::remove_folder(folder_path);
}

static void load_unused_dat_chunk(buffer* buf, int index) {
    auto& data = player_data();

    auto chunk = data.unused_data[index];
    chunk.campaign_idx = buf->read_i8();
    chunk.campaign_idx_2 = buf->read_u8();
    chunk.unk02 = buf->read_u16();
    chunk.unk03 = buf->read_u32();
    //
    chunk.mission_n_200 = buf->read_i32();
    chunk.mission_n_A = buf->read_i32();
    chunk.mission_n_B = buf->read_i32();
    chunk.mission_n_unk = buf->read_i32();
    //
    chunk.unk08 = buf->read_i32();
    chunk.unk09 = buf->read_i32();
    chunk.unk10 = buf->read_u32();
    chunk.unk11 = buf->read_u32();
    chunk.unk12 = buf->read_i16();
    chunk.unk13 = buf->read_u16();
    chunk.unk14 = buf->read_u32();
    chunk.unk15 = buf->read_u32();
    chunk.unk16 = buf->read_i16();
    chunk.unk17 = buf->read_u16();
    //
    chunk.unk18 = buf->read_u32();
    chunk.mission_completed = buf->read_u8();
    chunk.unk19 = buf->read_u16();
    chunk.unk20 = buf->read_u8();
}

void player_data_load(const uint8_t* player_name) {
    auto& data = player_data();
    // <player>.dat
    data.dat_file->clear();
    data.dat_file->reset_offset();
    vfs::path family_save("Save/", (const char*)player_name, ".dat");
    vfs::path fs_family_save = family_save.resolve();
    int size = io_read_file_into_buffer(fs_family_save, NOT_LOCALIZED, data.dat_file, DAT_FILE_SIZE);
    if (!size) {
        return;
    }

    for (int i = 0; i < MAX_DAT_ENTRIES; ++i) {// unused(?) scenario data chunks
        load_unused_dat_chunk(data.dat_file, i);
    }

    data.unk38 = data.dat_file->read_i32();   // number of fields for the Pharaoh main campaign? (38)
    for (int i = 0; i < MAX_DAT_ENTRIES; ++i) { // map names
        data.dat_file->read_raw(data.scenario_names[i], DAT_MAP_NAME_SIZE);
    }

    data.unk35 = data.dat_file->read_i32(); // unknown 32-bit field (35)
    bstring64 raw_autosave_path;
    data.dat_file->read_raw(raw_autosave_path.data(), raw_autosave_path.capacity); // path to last autosave_replay.sav file

    data.last_autosave_path.clear();
    if (!fs_family_save.empty()) {
        data.last_autosave_path = raw_autosave_path;
    }

    data.unk00 = data.dat_file->read_i32();  // unknown 32-bit field (0)
    for (int i = 0; i < MAX_DAT_ENTRIES; ++i) { // scenario records
        load_jas_record_chunk(data.dat_file, &data.player_scenario_records[i]);
    }
}
