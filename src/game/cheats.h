#pragma once

#include <stdint.h>
#include "core/bstring.h"

void game_cheat_activate();

int game_cheat_tooltip_enabled();

void game_cheat_money();

/**
 * Does nothing, just set breakpoint in implementation and call it with alt + b
 */
void game_cheat_breakpoint();

void game_cheat_console(bool force = false);

void game_cheat_parse_command(pcstr command);
