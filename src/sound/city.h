#pragma once

class building;

enum { SOUND_DIRECTION_LEFT = 0, SOUND_DIRECTION_CENTER = 2, SOUND_DIRECTION_RIGHT = 4 };

void sound_city_init(void);

void sound_city_set_volume(int percentage);

void sound_city_mark_building_view(building* b, int direction);

void sound_city_decay_views(void);

void sound_city_play(void);