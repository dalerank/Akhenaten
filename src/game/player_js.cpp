#include "player_profile.h"

#include "city/city.h"
#include "game/highscores.h"
#include "js/js_game.h"

int __player_salary_rank() {
    return g_city.kingdome.salary_rank;
}
ANK_FUNCTION(__player_salary_rank)

int __player_salary_amount() {
    return g_city.kingdome.salary_amount;
}
ANK_FUNCTION(__player_salary_amount)

// Player profile

void __game_player_data_new(pcstr name) {
    player_profile_t::create(name);
}
ANK_FUNCTION_1(__game_player_data_new)

void __game_delete_player(pcstr name) {
    player_profile_t::remove(name);
}
ANK_FUNCTION_1(__game_delete_player)

void __game_load_player_data(pcstr name) {
    g_player.select(name);
}
ANK_FUNCTION_1(__game_load_player_data)

pcstr __game_get_last_autosave() {
    return g_player.last_autosave();
}
ANK_FUNCTION(__game_get_last_autosave)

void __game_player_record_mission_win(int scenario_id) {
    g_player.record_win(city_make_mission_result(scenario_id));
    g_player.save();
}
ANK_FUNCTION_1(__game_player_record_mission_win)

// Records of the current profile, one accessor per field the mission select screen shows.
#define PLAYER_SCENARIO_RECORD_GETTER(fname, field)     \
    int fname(int scenario_id) {                        \
        return (int)g_player.record(scenario_id).field; \
    }                                                   \
    ANK_FUNCTION_1(fname)

PLAYER_SCENARIO_RECORD_GETTER(__game_player_scenario_record_completion_months, completion_months)
PLAYER_SCENARIO_RECORD_GETTER(__game_player_scenario_record_final_population, final_population)
PLAYER_SCENARIO_RECORD_GETTER(__game_player_scenario_record_final_funds, final_funds)
PLAYER_SCENARIO_RECORD_GETTER(__game_player_scenario_record_rating_culture, rating_culture)
PLAYER_SCENARIO_RECORD_GETTER(__game_player_scenario_record_rating_prosperity, rating_prosperity)
PLAYER_SCENARIO_RECORD_GETTER(__game_player_scenario_record_rating_kingdom, rating_kingdom)
PLAYER_SCENARIO_RECORD_GETTER(__game_player_scenario_record_difficulty, difficulty)
PLAYER_SCENARIO_RECORD_GETTER(__game_player_scenario_record_score, score)

#undef PLAYER_SCENARIO_RECORD_GETTER

// High scores

void __highscores_load() {
    g_highscores.load();
}
ANK_FUNCTION(__highscores_load)

int __highscores_count() {
    return g_highscores.count();
}
ANK_FUNCTION(__highscores_count)

bool __highscore_nonempty(int rank) {
    return g_highscores.get(rank).nonempty;
}
ANK_FUNCTION_1(__highscore_nonempty)

int __highscore_score(int rank) {
    const player_record& record = g_highscores.get(rank);
    return record.nonempty ? (int)record.calc_score() : 0;
}
ANK_FUNCTION_1(__highscore_score)

#define HIGHSCORE_FIELD_GETTER(fname, field)                  \
    int fname(int rank) {                                     \
        const player_record& record = g_highscores.get(rank); \
        return record.nonempty ? (int)record.field : 0;       \
    }                                                         \
    ANK_FUNCTION_1(fname)

HIGHSCORE_FIELD_GETTER(__highscore_mission, mission_idx)
HIGHSCORE_FIELD_GETTER(__highscore_culture, rating_culture)
HIGHSCORE_FIELD_GETTER(__highscore_prosperity, rating_prosperity)
HIGHSCORE_FIELD_GETTER(__highscore_kingdom, rating_kingdom)
HIGHSCORE_FIELD_GETTER(__highscore_population, final_population)
HIGHSCORE_FIELD_GETTER(__highscore_funds, final_funds)
HIGHSCORE_FIELD_GETTER(__highscore_months, completion_months)

#undef HIGHSCORE_FIELD_GETTER
