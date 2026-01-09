#pragma once

#include <stdint.h>
#include "core/bstring.h"

void game_cheat_activate();
void game_cheat_force_activate();
bool game_cheat_is_active();

void game_cheat_parse_command(pcstr command);
