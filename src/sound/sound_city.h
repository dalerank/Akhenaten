#pragma once

#include "core/system_time.h"
#include "game/sound_channel.h"
#include "core/tokenum.h"
#include "core/vec2i.h"

#include <array>

class building;

enum e_sound_dir { 
    SOUND_DIRECTION_LEFT = 0,
    SOUND_DIRECTION_CENTER = 2,
    SOUND_DIRECTION_RIGHT = 4
};

struct city_sound_channel {
    int in_use;
    int available;
    int total_views;
    int views_threshold;
    int direction_views[5];
    int channel;
    int times_played;
    time_millis last_played_time;
    time_millis delay_millis;
    int should_play;
};

struct city_sounds_t {
    time_millis last_update_time;
    std::array<city_sound_channel, 96> channels;
};

void sound_city_init();
void sound_city_stop();
const city_sounds_t &sound_city_channels();
void sound_city_add_channel(int system_channel_index, int direction);
void sound_city_mark_building_view(building* b, int direction);
void sound_city_mark_terrain_view(int terrain, int grid_offset, int direction);
void sound_city_decay_views();
void sound_city_play();

// Enhanced city ambience (gameplay_enhanced_city_ambient). The city renderer reports each drawn tile of a
// sounding building with its pixel; the audio side reads nothing of the simulation or the save.
int sound_city_building_channel(building* b);
void sound_city_ambient_note(int channel, vec2i pixel);
void sound_city_ambient_reset();
const char* sound_city_ambient_summary();