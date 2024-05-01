#pragma once

#include "core/buffer.h"

const uint8_t* city_player_name();
void city_set_player_name(const uint8_t* name);
void city_save_campaign_player_name();
void city_restore_campaign_player_name();
