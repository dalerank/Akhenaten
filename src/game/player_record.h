#pragma once

#include "core/xstring.h"
#include "game/game_environment.h"

#include <cstdint>

class buffer;

constexpr int MAX_PLAYER_SCENARIOS = 100;
constexpr int PLAYER_RECORD_CHUNK_SIZE = 76;

struct mission_result_t {
    int scenario_id = -1;
    uint32_t rating_culture = 0;
    uint32_t rating_prosperity = 0;
    uint32_t rating_kingdom = 0;
    uint32_t final_population = 0;
    uint32_t final_funds = 0;
    uint32_t completion_months = 0;
    uint32_t difficulty = 0;
    xstring player_name;
};

struct player_record {
    uint32_t score = 0;
    uint32_t mission_idx = 0;
    uint8_t player_name[MAX_PLAYER_NAME] = {};
    uint32_t rating_culture = 0;
    uint32_t rating_prosperity = 0;
    uint32_t rating_kingdom = 0;
    uint32_t final_population = 0;
    uint32_t final_funds = 0;
    uint32_t completion_months = 0;
    uint32_t difficulty = 0;
    uint32_t unk09 = 0;
    bool nonempty = false;

    uint32_t calc_score() const;
    bool score_is_valid() const { return score == calc_score(); }

    void assign(const mission_result_t& result);

    void read(buffer& buf);
    void write(buffer& buf) const;

    bool looks_plausible() const;
};
