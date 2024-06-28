#pragma once

#include "../core/string.h"
#include "../core/span.hpp"
#include "../content/dir.h"
#include <array>

struct music_format {
    const int flag;
    pcstr desc;
};

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

    enum {
        MAX_CHANNELS = 150,
    };

    void init();
    void shutdown();
    void init_channels();
    inline std::span<channel_t> channels() { return make_span<channel_t>(_channels.data(), _channels.size()); }
    void speech_play_file(pcstr filename, int volume);
    bool speech_file_exist(pcstr filename);
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
    void set_music_volume(int volume_pct);

private:
    static void channel_finished_cb(int channel);
    void init_channel(int index, vfs::path filename);
    void init_channels(std::span<vfs::path> channels);
    void open();
    void close();
    void load_formats();
    void unload_formats();
    void set_channel_panning(int channel, int left, int right);
    void play_file_on_channel(pcstr filename, int channel, int volume_pct);
    void stop_channel(int channel);
    void free_custom_audio_stream();
    int create_custom_audio_stream(uint16_t src_format, uint8_t src_channels, int src_rate, uint16_t dst_format, uint8_t dst_channels, int dst_rate);
    int get_custom_audio_stream(uint8_t *dst, int len);
    static void custom_music_callback(void *dummy, uint8_t *stream, int len);
    vfs::path speech_filename(pcstr filename);

private:
    bool initialized;
    void* music;
    std::array<channel_t, MAX_CHANNELS> _channels;
};

extern sound_manager_t g_sound;