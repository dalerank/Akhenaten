#ifndef CITY_DATA_H
#define CITY_DATA_H

#include "core/buffer.h"

void city_data_init(void);

void city_data_init_custom_map(void);

void city_data_init_campaign_mission(void);

const uint8_t *city_player_name(void);
void city_set_player_name(const uint8_t *name);
void city_save_campaign_player_name(void);
void city_restore_campaign_player_name(void);

#endif // CITY_DATA_H
