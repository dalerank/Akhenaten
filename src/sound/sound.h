#pragma once

#include "core/xstring.h"
#include "core/custom_span.hpp"
#include "content/dir.h"
#include "content/vfs.h"
#include "sound/channel.h"
#include "sound/effect.h"
#include <array>

struct music_player_t;

struct event_sound_effect { int effect; };
struct event_sound_track { xstring track; };

class sound_manager_t {
public:
    struct channel_t {
        vfs::path filename;
        int left_pan = 0;
        int right_pan = 0;
        int volume = 0;
        void* chunk = nullptr;
        bool playing = false;
    };

    void init();
    void shutdown();
    void init_channels();
    inline custom_span<channel_t> channels() { return make_span<channel_t>(_channels.data(), _channels.size()); }
    void speech_play_file(xstring filename, int volume);
    bool speech_file_exist(xstring filename);
    void set_channel_volume(int channel, int volume_pct);
    bool is_channel_playing(int channel);
    void play_channel(int channel, int volume_pct);
    void play_channel_panned(int channel, int volume_pct, int left_pct, int right_pct);
    void speech_stop();
    void speech_set_volume(int percentage);
    void update_channel(int channel, vfs::path filename);
    void use_default_music_player();
    void use_custom_music_player(int bitdepth, int num_channels, int rate, void *audio_data, int len);
    void write_custom_music_data(void *audio_data, int len);
    bool play_music(pcstr filename, int volume_pct);
    void stop_music();
    void music_set_volume(int volume_pct);
    bool is_audio_stream_active();
    void set_volume(int b, int e, int percentage);
    void music_update(bool forces);
    void play_editor();
    void play_intro();
    void music_stop();
    void play_track(const xstring track);
    void play_effect(int effect);

public:
    void on_sound_effect(event_sound_effect);
    void on_sound_track(event_sound_track);

private:
    static void channel_finished_cb(int channel);
    void init_channel(int index, vfs::path filename);
    void allocate_channels();
    void open();
    void close();
    void load_formats();
    void unload_formats();
    void set_channel_panning(int channel, int left, int right);
    void play_file_on_channel(pcstr filename, int channel, int volume_pct);
    void stop_channel(int channel);
    void free_custom_audio_stream();
    bool create_custom_audio_stream(uint16_t src_format, uint8_t src_channels, int src_rate, uint16_t dst_format, uint8_t dst_channels, int dst_rate);
    bool init_audio_with_timeout(const char *driver_name, int timeout_ms = 2000);
    int get_custom_audio_stream(uint8_t *dst, int len);
    static void custom_music_callback(void *dummy, uint8_t *stream, int len);
    vfs::path speech_filename(xstring filename);
    bool load_channel(channel_t *channel);
    void *load_chunk(pcstr filename);
    vfs::reader load_cached_chunk(vfs::path filename);
    bool put_custom_audio_stream(uint8_t *audio_data, int len);

private:
    bool initialized;
    music_player_t *_music_player = nullptr;
    std::array<channel_t, SOUND_CHANNEL_MAX> _channels;
    std::array<vfs::path, SOUND_CHANNEL_MAX> _channels_info;
};

extern sound_manager_t g_sound;