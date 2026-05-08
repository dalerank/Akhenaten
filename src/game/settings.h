#pragma once

#include <stdint.h>
#include "core/tokenum.h"
#include "core/bstring.h"
#include "core/vec2i.h"
#include "core/calc.h"
#include "game/game_config.h"

class buffer;

struct game_settings {
    // persistent game state
    bstring32 player_name;
    bstring32 player_name_utf8;
    // file data
    buffer *inf_file = nullptr;

    game_settings();

    void load_default_settings();
    void load();
    void save();

    void set_player_name(const uint8_t* player_name);
    void set_player_name_utf8(pcstr name_utf8);

private:
    void load_settings(buffer *buf);
};

extern game_settings g_settings;