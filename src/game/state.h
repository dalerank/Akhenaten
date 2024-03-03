#pragma once

#include "overlays/city_overlay_fwd.h"

void game_state_init();

void game_state_toggle_paused();

void game_state_reset_overlay();

void game_state_toggle_overlay();

void game_state_set_overlay(e_overlay overlay);