#pragma once

#include "core/system_time.h"
#include "sound/channel.h"
#include "core/tokenum.h"
#include "core/vec2i.h"
#include "core/xstring.h"
#include "sound/sound_view_queue.h"
#include "building/building_type.h"

#include <array>
#include <random>
#include <string>

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
    std::array<xstring, 96> names;
    std::array<int16_t, BUILDING_MAX> building_channels;
};

struct city_ambient_t {
    struct seen_t {
        int tiles = 0;
        float best_dist = 0.f;
        int best_x = 0;
    };

    struct voice_t {
        int channel = 0;
        float gain = 0.f;
        float target = 0.f;
        float pan = 0.5f;
        time_millis next_play = 0;
        bool active = false;
    };

    std::array<seen_t, 96> seen;
    std::array<voice_t, 8> voices;
    vec2i last_camera = {-1, -1};
    vec2i view_offset = {0, 0};
    vec2i view_size = {0, 0};
    float duck = 1.f;
    time_millis last_ms = 0;
    bool running = false;
    // Cosmetic: never the simulation LFSR, crt_rand or libc rand().
    std::minstd_rand rng{std::random_device{}()};
    std::string summary;

    void reset();
};

struct sound_city_t {
    city_sounds_t sounds;
    city_ambient_t ambient;
    sound_view_queue_t view_queue;

    void init();
    void clear_names();
    void set_name(int channel, xstring id);
    int channel(const xstring& id) const;
    void stop();
    void add_channel(int system_channel_index, int direction);
    void mark_building_view(building* b, int direction);
    void mark_terrain_view(int terrain, int grid_offset, int direction);
    void decay_views();
    void play();
    int building_channel(building* b);
    void ambient_note(int channel, vec2i pixel);
    void ambient_reset();
    const char* ambient_summary() const;

private:
    int building_type_channel(building* b);
    int zoo_ambient_channel();
    bool ambient_play();
};

sound_city_t& sound_city();
