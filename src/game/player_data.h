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

void player_data_load();
player_record records_get(int rank);
int records_count();

typedef struct {

} player_progression;

player_progression player_data_get(const uint8_t *player_name);
void player_data_new(const uint8_t *player_name);
void player_data_delete(const uint8_t *player_name);

#endif //OZYMANDIAS_PLAYER_DATA_H
