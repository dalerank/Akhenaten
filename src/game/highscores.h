#pragma once

#include "content/vfs.h"
#include "game/player_record.h"

constexpr int MAX_HIGHSCORE_ENTRIES = 100;

enum e_highscore_result {
    e_highscore_result_none = 0,
    e_highscore_result_new,
    e_highscore_result_own_kept,
    e_highscore_result_own_beaten,
    e_highscore_result_other_kept,
    e_highscore_result_other_beaten,
    e_highscore_result_cheated,
};

// save\highscore.jas of the original: one 76-byte record per campaign mission. It is written to the user
// directory; the original game's file is read when the user directory has none yet.
struct highscores_t {
    void load();
    bool save() const;
    vfs::path file_path() const;

    int count() const { return num_entries; }
    const player_record& get(int rank) const;

    e_highscore_result record_mission(const mission_result_t& result, int score, int monuments);

    player_record records[MAX_HIGHSCORE_ENTRIES];
    int num_entries = 0;
    e_highscore_result last_result = e_highscore_result_none;
    bstring32 previous_name;
};

extern highscores_t g_highscores;
