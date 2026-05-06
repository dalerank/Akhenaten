#pragma once

#include <stdint.h>
#include "core/tokenum.h"
#include "core/bstring.h"
#include "core/vec2i.h"
#include "core/calc.h"
#include "game/game_config.h"

class buffer;

enum e_tooltip_mode {
    e_tooltip_mode_none = 0,
    e_tooltip_mode_some = 1,
    e_tooltip_mode_full = 2,
    e_tooltip_count,
};
using etooltip_flag = uint32_t;

struct game_settings {
    static constexpr uint8_t MAX_PERSONAL_SAVINGS = 100;
    static constexpr uint8_t MAX_DIFFICULTY_LEVEL = 4;
    // display settings
    vec2i display_size;

    // persistent game state
    bstring32 player_name;
    bstring32 player_name_utf8;
    // personal savings
    int personal_savings[MAX_PERSONAL_SAVINGS] = {0};
    // file data
    buffer *inf_file = nullptr;

    game_settings();

    void load_default_settings();
    void load();
    void save();

    void set_player_name(const uint8_t* player_name);
    void set_player_name_utf8(pcstr name_utf8);

    int personal_savings_for_mission(int mission_id) { return personal_savings[mission_id]; }
    void set_personal_savings_for_mission(int mission_id, int savings) { personal_savings[mission_id] = savings; }

    void clear_personal_savings(void);

private:
    void load_settings(buffer *buf);
};

extern game_settings g_settings;