#pragma once

#include "game/player_record.h"

constexpr int MAX_HIGHSCORE_ENTRIES = 100;

struct highscores_t {
    void load();

    int count() const { return num_entries; }
    const player_record& get(int rank) const;

    player_record records[MAX_HIGHSCORE_ENTRIES];
    int num_entries = 0;
};

extern highscores_t g_highscores;
