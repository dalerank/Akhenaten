#pragma once

#include "core/xstring.h"
#include "core/svector.h"
#include "core/custom_span.hpp"
#include "game/game_events.h"
#include "core/vfs/dir.h"
#include "core/vfs/vfs.h"
#include "sound/channel.h"
#include "game/sound_effect.h"
#include <array>
#include <future>
#include <string_view>
#include <stdint.h>

struct music_player_t;


class sound_manager_t {
public:
    struct channel_t {
        vfs::path filename;
        int left_pan = 0;
        int right_pan = 0;
        int volume = 0;
        void* chunk = nullptr;
        // Mirrors Mix_Playing, refreshed on the main thread each frame.
        bool playing = false;

        // The file is decoded on a worker; the main thread picks it up in begin_frame.
        std::future<vfs::reader> pending;
        bool play_requested = false;
        bool panned = false;
    };

    void init();
    void shutdown();
    void init_channels();
    void begin_frame();
    inline xspan<channel_t> channels() { return make_span<channel_t>(_channels.data(), _channels.size()); }
    void set_channel_volume(int channel, int volume_pct);
    void set_channel_pan(int channel, int left_pct, int right_pct);
    bool is_channel_playing(int channel);
    void play_channel(int channel, int volume_pct);
    void play_channel_panned(int channel, int volume_pct, int left_pct, int right_pct);
    void update_channel(int channel, vfs::path filename);
    bool play_music(pcstr filename, int volume_pct, bool loop = true);
    bool music_playing();
    void fade_out_music(int ms);
    void stop_music();
    void set_volume(int b, int e, int percentage);
    int play_effect(int effect);
    int free_effect_channel(const vfs::path& filename);
    void play_effect_panned(int channel, const vfs::path& filename, int volume_pct, int left_pct, int right_pct);
    vfs::path audio_file_path(const xstring& file) const;
    // "[sound] ..." log lines of what plays, for --log-sound and the integral tests (no audio hardware needed).
    bool log_events() const;
    bool log_event_sources() const;
    bool data_available() const;
    void set_effect_file(int effect, xstring file);
    void clear_effect_files();
    void stop_city_channels();
    void stop_city_channel(int channel);
    bool is_initialized() const { return initialized; }
    bool play_file_on_channel(pcstr filename, int channel, int volume_pct);
    void stop_channel(int channel);

public:
    void on_sound_effect(event_sound_effect);

private:
    void init_channel(int index, vfs::path filename);
    void allocate_channels();
    void open();
    void close();
    void load_formats();
    void unload_formats();
    void set_channel_panning(int channel, int left, int right);
    void* load_chunk(pcstr filename, bool cache);
    void* chunk_from_reader(const vfs::reader& r);
    void start_channel(int channel);
    void request_channel(int channel);
    void poll_pending_chunks();

    struct og_sample_t {
        xstring file;
        vfs::path resolved;
        bool probed = false;
    };
    const vfs::path& og_sample_path(og_sample_t& sample);
    int pick_effect_channel(const vfs::path& filename);

private:
    bool initialized = false;
    music_player_t *_music_player = nullptr;
    std::array<channel_t, SOUND_CHANNEL_MAX> _channels;
    std::array<vfs::path, SOUND_CHANNEL_MAX> _channels_info;
    std::array<og_sample_t, SOUND_EFFECT_COUNT> _effect_files;
};

sound_manager_t& sound_manager();
