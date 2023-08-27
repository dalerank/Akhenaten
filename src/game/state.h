#pragma once

void game_state_init(void);

bool game_state_is_paused(void);

void game_state_toggle_paused(void);

void game_state_unpause(void);

int game_state_overlay(void);

void game_state_reset_overlay(void);

void game_state_toggle_overlay(void);

void game_state_set_overlay(int overlay);
