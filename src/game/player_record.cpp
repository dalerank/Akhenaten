#include "player_record.h"

#include "core/buffer.h"
#include "core/string.h"

uint32_t player_record::calc_score() const {
    // I have *NO CLUE* how the unk09 value works. It's just black magic.
    // In missions where it's zero, the formula checks out correctly.
    constexpr double unkn = 0.0;

    if (completion_months == 0) {
        return 0; // a record without elapsed months would divide by zero below
    }

    const double months = completion_months;
    const double result = (difficulty + 1.0) / 3.0
                          * ((final_funds / (months / 30.0)) + unkn * unkn * 20.0 / (months * months / 6400.0)
                             + final_population * 0.002 * (rating_culture + rating_prosperity + rating_kingdom));

    return (result > 0.0) ? (uint32_t)result : 0;
}

void player_record::assign(const mission_result_t& result) {
    nonempty = true;
    mission_idx = (uint32_t)result.scenario_id;
    rating_culture = result.rating_culture;
    rating_prosperity = result.rating_prosperity;
    rating_kingdom = result.rating_kingdom;
    final_population = result.final_population;
    final_funds = result.final_funds;
    completion_months = result.completion_months;
    difficulty = result.difficulty;
    unk09 = 0;

    pcstr name = result.player_name.empty() ? "unknown" : result.player_name.c_str();
    string_copy((const uint8_t*)name, player_name, MAX_PLAYER_NAME);

    score = calc_score();
}

void player_record::read(buffer& buf) {
    score = buf.read_u32();
    mission_idx = buf.read_u32();
    buf.read_raw(player_name, MAX_PLAYER_NAME);
    rating_culture = buf.read_u32();
    rating_prosperity = buf.read_u32();
    rating_kingdom = buf.read_u32();
    final_population = buf.read_u32();
    final_funds = buf.read_u32();
    completion_months = buf.read_u32();
    difficulty = buf.read_u32();
    unk09 = buf.read_u32();
    nonempty = !!buf.read_u32();

    player_name[MAX_PLAYER_NAME - 1] = 0;
}

void player_record::write(buffer& buf) const {
    buf.write_u32(score);
    buf.write_u32(mission_idx);
    buf.write_raw(player_name, MAX_PLAYER_NAME);
    buf.write_u32(rating_culture);
    buf.write_u32(rating_prosperity);
    buf.write_u32(rating_kingdom);
    buf.write_u32(final_population);
    buf.write_u32(final_funds);
    buf.write_u32(completion_months);
    buf.write_u32(difficulty);
    buf.write_u32(unk09);
    buf.write_u32(nonempty ? 1 : 0);
}

bool player_record::looks_plausible() const {
    if (!nonempty) {
        return score == 0 && mission_idx == 0 && completion_months == 0 && final_population == 0;
    }

    return mission_idx < (uint32_t)MAX_PLAYER_SCENARIOS && difficulty <= 5 && rating_culture <= 100
           && rating_prosperity <= 100 && rating_kingdom <= 100;
}
