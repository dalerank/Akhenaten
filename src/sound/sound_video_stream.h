#pragma once

#include <SDL.h>

#include <atomic>
#include <cstdint>
#include <mutex>

class sound_video_stream_t {
public:
    void use_custom(int bitdepth, int num_channels, int rate, void* audio_data, int len);
    void use_default();
    void write(void* audio_data, int len);
    uint64_t playback_micros() const;
    uint64_t buffered_micros() const;
    void set_use_audiostream(bool use) { use_audiostream = use; }

private:
    bool is_active();
    void free_stream();
    bool create_stream(uint16_t src_format, uint8_t src_channels, int src_rate, uint16_t dst_format,
      uint8_t dst_channels, int dst_rate);
    int get(uint8_t* dst, int len);
    bool put(uint8_t* audio_data, int len);
    static void callback(void* dummy, uint8_t* stream, int len);

    SDL_AudioFormat format = 0;
#if SDL_VERSION_ATLEAST(2, 0, 7)
    SDL_AudioStream* stream = nullptr;
#endif
    bool use_audiostream = false;
    SDL_AudioCVT cvt{};
    uint8_t* buffer = nullptr;
    int buffer_size = 0;
    int cur_read = 0;
    int cur_write = 0;
    std::atomic<uint64_t> bytes_written = 0;
    std::atomic<uint64_t> bytes_read = 0;
    std::mutex mutex;
    uint32_t bytes_per_second = 0;
    int underrun_logs = 0;
};

sound_video_stream_t& sound_video_stream();
