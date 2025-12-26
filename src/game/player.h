#pragma once

#include "game/game_environment.h"
#include <stdint.h>

#define MAX_DAT_ENTRIES 100
#define DAT_MAP_NAME_SIZE 50

// no idea what these top chunks are for. the game uses the RECORDS table
// further below to check which missions are unlocked, not these chunks.
struct player_unused_scenario_data {
    int8_t campaign_idx = -1;   // FF           :: xx          >> campaign period number
    uint8_t campaign_idx_2 = 0; // 00           :: 00          >> 0 if single mission, increasing # if choosable
    uint16_t unk02 = 0;         // 00 00        :: AC 4F       >> always the same
    uint32_t unk03 = 0;         // 00 00 00 00  :: 00 00 00 00 >> always 0?

    int32_t mission_n_200 = -1; // FF FF FF FF  :: C8 00 00 00 >> starts from 200, goes up with mission number
    int32_t mission_n_A = -1;   // FF FF FF FF  :: xx 00 00 00 >> mission number
    int32_t mission_n_B = -1;   // FF FF FF FF  :: xx 00 00 00 >> mission number (2)
    int32_t mission_n_unk = -1; // FF FF FF FF  :: FF FF FF FF >> always -1?

    // unknown 32-byte sequence -- these always change together at
    // semi-random intervals, almost always increasing the values
    int32_t unk08 = -1;  // FF FF FF FF
    int32_t unk09 = -1;  // FF FF FF FF
    uint32_t unk10 = 32; // 32 00 00 00
    uint32_t unk11 = 32; // 32 00 00 00
    int16_t unk12 = -1;  // FF FF
    uint16_t unk13 = 0;  // 00 00
    uint32_t unk14 = 64; // 64 00 00 00
    uint32_t unk15 = 64; // 64 00 00 00
    int16_t unk16 = -1;  // FF FF
    uint16_t unk17 = 0;  // 00 00

    uint32_t unk18 = 0;            // 00 00 00 00  :: 02 00 00 00 >> either 0 or 2
    uint8_t mission_completed = 0; // 00           :: 00          >> 0 if never completed, 1 if completed before
    uint16_t unk19 = 0;            // 00 00        :: FB 19       >> always the same
    uint8_t unk20 = 0;             // 00           :: 00          >> always 0?
};

struct player_record {
    uint32_t score = 0;
    uint32_t mission_idx = 0;
    uint8_t player_name[MAX_PLAYER_NAME];
    uint32_t rating_culture = 0;
    uint32_t rating_prosperity = 0;
    uint32_t rating_kingdom = 0;
    uint32_t final_population = 0;
    uint32_t final_funds = 0;
    uint32_t completion_months = 0;
    uint32_t difficulty = 0;
    uint32_t unk09 = 0;
    bool nonempty = false;
    bool score_is_valid = false;
};

uint32_t records_calc_score(float unkn, float funds, float population, float r_culture, float r_prosperity, float r_kingdom, float months, float difficulty);
uint32_t records_calc_score(const player_record* record);
const player_record* highscores_get(int rank);
int highscores_count();

void highscores_load();

// const char *player_get_cached_scenario_name(int scenario_id);
const player_record* player_get_scenario_record(int scenario_id);
const char* player_get_last_autosave();

void player_data_new(const uint8_t* player_name);
void player_data_delete(const uint8_t* player_name);
void player_data_load(const uint8_t* player_name);
