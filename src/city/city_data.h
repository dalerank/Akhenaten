#pragma once

#include "core/buffer.h"

void city_data_init();

void city_data_init_custom_map();

void city_data_init_campaign_mission();

const uint8_t* city_player_name();
void city_set_player_name(const uint8_t* name);
void city_save_campaign_player_name();
void city_restore_campaign_player_name();
void city_migration_nobles_leave_city(int num_people);
