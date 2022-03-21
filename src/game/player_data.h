#ifndef OZYMANDIAS_PLAYER_DATA_H
#define OZYMANDIAS_PLAYER_DATA_H

#include <stdint-gcc.h>
#include "core/game_environment.h"

typedef struct {
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

} player_record;

uint32_t records_calc_score(float unkn, float funds, float population, float r_culture, float r_prosperity, float r_kingdom, float months, float difficulty);
uint32_t records_calc_score(player_record *score);

player_record records_get(int rank);
int records_count();
void records_load();

typedef struct {
    struct {
        uint8_t map_name[50];

        int8_t unk00 = -1;
        uint8_t unk01 = 0;
        uint16_t unk02 = 0;
        uint32_t unk03 = 0;

        int32_t unk04 = -1;
        int32_t unk05 = -1;
        int32_t unk06 = -1;
        int32_t unk07 = -1;
        int32_t unk08 = -1;
        int32_t unk09 = -1;

        uint32_t unk10 = 32;
        uint32_t unk11 = 32;
        int16_t unk12 = -1;
        uint16_t unk13 = 0;
        uint32_t unk14 = 64;
        uint32_t unk15 = 64;
        int16_t unk16 = -1;
        uint16_t unk17 = 0;

        uint32_t unk18 = 0;
        uint8_t mission_completed = 0;
        uint8_t unk19 = 0;
        uint8_t unk20 = 0;
        uint8_t unk21 = 0;
    } map_data[100];
} player_progression_data;

const player_progression_data *player_data_get();
void player_data_new(const uint8_t *player_name);
void player_data_delete(const uint8_t *player_name);
void player_data_load(const uint8_t *player_name);

#endif //OZYMANDIAS_PLAYER_DATA_H
