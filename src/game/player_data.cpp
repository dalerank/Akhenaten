#include <core/buffer.h>
#include <core/io.h>
#include "player_data.h"

#include "scenario/property.h"

#define JAS_FILE_SIZE 7600
#define JAS_CHUNK_SIZE 76
#define MAX_JAS_CHUNKS 100

static struct {
    player_record highscores[MAX_JAS_CHUNKS];
    int num_highscore_entries;
    buffer *jas_file = new buffer(JAS_FILE_SIZE);
} data;

uint32_t records_calc_score(float unkn, float funds, float population, float r_culture, float r_prosperity,
                            float r_kingdom, float months, float difficulty) {
    // I have *NO CLUE* how this value works. It's just black magic.
    // In missions where it's zero, the formula checks out correctly.
    unkn = 0.0;
    return (difficulty + 1.0) / 3.0 * (
            (funds / (months / 30.0)) +
            unkn * unkn * 20.0 / (months * months / 6400.0) +
            population * 0.002 * (r_culture + r_prosperity + r_kingdom)
    );
}
uint32_t records_calc_score(player_record *score) {
    return records_calc_score(score->unk09,
                              score->final_funds,
                              score->final_population,
                              score->rating_culture,
                              score->rating_prosperity,
                              score->rating_kingdom,
                              score->completion_months,
                              score->difficulty);
}
player_record records_get(int rank) {
    // go through the list of records, return the nth non-empty record
    for (int i = 0; i < MAX_JAS_CHUNKS; ++i) {
        if (data.highscores[i].nonempty)
            if (rank > 0)
                rank--;
            else
                return data.highscores[i];
    }
    player_record dummy;
    return dummy; // return empty record when reached the end of the list
}
int records_count() {
    return data.num_highscore_entries;
}

static void load_jas_chunk(buffer *buf, player_record *record) {
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
static void load_dat_chunk(buffer *buf) {
    // TODO
}
void player_data_load() {
    // Player scores (highscore.jas)
    data.jas_file->clear();
    data.jas_file->reset_offset();
    data.num_highscore_entries = 0;
    int size = io_read_file_into_buffer("Save/highscore.jas", NOT_LOCALIZED, data.jas_file, JAS_FILE_SIZE);
    if (!size)
        return;
    for (int i = 0; i < MAX_JAS_CHUNKS; ++i)
        load_jas_chunk(data.jas_file, &data.highscores[i]);

    // Player campaign data (<player>.dat)
    // TODO
}

player_progression player_data_get(const uint8_t *player_name) {
    // TODO
}
void player_data_new(const uint8_t *player_name) {
    // TODO
}
void player_data_delete(const uint8_t *player_name) {
    // TODO
}