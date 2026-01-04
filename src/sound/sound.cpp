#include <SDL.h>

#include <SDL_mixer.h>

#include "sound/sound.h"
#include "content/file_formats.h"
#include "core/log.h"
#include "game/settings.h"
#include "platform/platform.h"
#include "platform/vita/vita.h"
#include "game/game.h"
#include "js/js_game.h"

#include "lame_helper.h"

#include <stdlib.h>
#include <string.h>
#include <vector>
#include <map>

#ifdef __vita__
#include <psp2/io/fcntl.h>
#endif

#define AUDIO_RATE 22050
#define AUDIO_FORMAT AUDIO_S16
#define AUDIO_CHANNELS 2
#define AUDIO_BUFFERS 1024

#if SDL_VERSION_ATLEAST(2, 0, 7)
#define USE_SDL_AUDIOSTREAM
#endif

#define HAS_AUDIOSTREAM() (platform_sdl_version_at_least(2, 0, 7))

#ifdef __vita__
static struct {
    char filename[FILE_NAME_MAX];
    char* buffer;
    int size;
} vita_music_data;
#endif

void ANK_REGISTER_CONFIG_ITERATOR(config_load_city_sounds) {
    g_config_arch.r_array("city_sounds", [] (archive arch) {
        const int channel = arch.r_int("c");
        const char *path = arch.r_string("p");
        g_sound.update_channel(channel, path);
    });
}

struct music_player_t {
    SDL_AudioFormat format;

#ifdef USE_SDL_AUDIOSTREAM
    SDL_AudioStream* stream;
    int use_audiostream;
#endif // USE_SDL_AUDIOSTREAM

    SDL_AudioCVT cvt;
    uint8_t* buffer;
    int buffer_size;
    int cur_read;
    int cur_write;
    Mix_Music* music;

    std::map<std::string, vfs::reader> cached_chunks;
};

struct music_format {
    const int flag;
    pcstr desc;
};

sound_manager_t g_sound;

static int percentage_to_volume(int percentage) {
    return percentage * SDL_MIX_MAXVOLUME / 100;
}

void sound_manager_t::speech_set_volume(int percentage) {
    set_channel_volume(SOUND_CHANNEL_SPEECH, percentage);
}

void sound_manager_t::init() {
    if (!_music_player) {
        _music_player = new music_player_t();
    }

    open();
    allocate_channels();
    load_formats();

    set_volume(SOUND_CHANNEL_CITY_MIN, SOUND_CHANNEL_CITY_MAX, g_settings.get_sound(SOUND_CITY)->volume);
    set_volume(SOUND_CHANNEL_EFFECTS_MIN, SOUND_CHANNEL_EFFECTS_MAX, g_settings.get_sound(SOUND_EFFECTS)->volume);
    music_set_volume(g_settings.get_sound(SOUND_MUSIC)->volume);
    speech_set_volume(g_settings.get_sound(SOUND_SPEECH)->volume);
}

void sound_manager_t::set_volume(int b, int e, int percentage) {
    for (int i = b; i <= e; i++) {
        set_channel_volume(i, percentage);
    }
}

void sound_manager_t::shutdown() {
    close();

    // It is counter-intuitive that we must do this after sound_device_close, however it unloads shared libraries
    // which might be required both for sound_device_close and by other threads fetching new audio chunks until
    // sound_device_close is called. It is also surprising that we can (and must) call Mix_Quit after Mix_CloseAudio,
    // even though Mix_CloseAudio's docs say that afterwards "the SDL_mixer functions should not be used".
    unload_formats();

    delete _music_player;
}

vfs::reader sound_manager_t::load_cached_chunk(vfs::path filename) {
    auto it = _music_player->cached_chunks.insert({filename.c_str(), vfs::reader()});

    if (!it.second) {
        return it.first->second;
    }

    vfs::path converted_wav(filename);
    bool need_converting = false;
    auto format = get_format_from_file(filename);
    if (format == FILE_FORMAT_MP3) {
        // first check we have converted file on the disk
        vfs::file_change_extension(converted_wav.data(), "wav");
        need_converting = !vfs::file_exists(converted_wav);
    }
    
    if (need_converting) {
        lame_helper helper;
        it.first->second = helper.decode(filename);
    } else {
        it.first->second = vfs::file_open(converted_wav);
    }

    return it.first->second;
}

void* sound_manager_t::load_chunk(pcstr filename) {
    if (filename && *filename) {
        auto format = get_format_from_file(filename);
        if (format == FILE_FORMAT_MP3 || format == FILE_FORMAT_WAV) {
            vfs::reader r = load_cached_chunk(filename);

            if (!r) {
                return nullptr;
            }

            SDL_RWops* sdl_fp = SDL_RWFromConstMem(r->data(), r->size());
            return Mix_LoadWAV_RW(sdl_fp, SDL_FALSE);
        }

#if defined(__vita__) || defined(GAME_PLATFORM_ANDROID)
        FILE* fp = vfs::file_open_os(filename, "rb");
        if (!fp) {
            return NULL;
        }

        SDL_RWops* sdl_fp = SDL_RWFromFP(fp, SDL_TRUE);
        return Mix_LoadWAV_RW(sdl_fp, 1);
#else
        verify_no_crash(false && "unsupported format");
        //return Mix_LoadWAV_RW(SDL_RWFromFile(filename, "rb"), 1);
#endif
    } 

    return NULL;
}

bool sound_manager_t::load_channel(sound_manager_t::channel_t* channel) {
    if (!channel->chunk && !channel->filename.empty()) {
        channel->chunk = load_chunk(channel->filename);
    }

    return !!channel->chunk;
}

void sound_manager_t::channel_finished_cb(int channel) {
    g_sound._channels[channel].playing = false;
}

void sound_manager_t::init_channels() {
    initialized = true;
    for (auto &ch: _channels) {
        ch.chunk = 0;
    }

    Mix_ChannelFinished(channel_finished_cb);
}

void sound_manager_t::init_channel(int index, vfs::path filename) {
    _channels[index].chunk = nullptr;
    _channels[index].filename = filename;
}

bool sound_manager_t::init_audio_with_timeout(const char *driver_name, int timeout_ms) {
    auto future = std::async(std::launch::async, [driver_name] () {
        return SDL_AudioInit(driver_name) == 0
            && Mix_OpenAudio(AUDIO_RATE, AUDIO_FORMAT, AUDIO_CHANNELS, AUDIO_BUFFERS) == 0;
    });

    if (future.wait_for(std::chrono::milliseconds(timeout_ms)) == std::future_status::timeout) {
        SDL_Log("Audio initialization timeout - no audio device available?");
        return false;
    }

    return future.get();
}

void sound_manager_t::allocate_channels() {
    if (!initialized) {
        return;
    }

    int num_channels = std::min<int>(SOUND_CHANNEL_MAX, (int)_channels_info.size());

    Mix_AllocateChannels(num_channels);
    logs::info("Loading audio files");

    for (int i = 0; i < num_channels; i++) {
        init_channel(i, _channels_info[i]);
    }
}

void sound_manager_t::open() {
#ifdef USE_SDL_AUDIOSTREAM
    _music_player->use_audiostream = HAS_AUDIOSTREAM();
#endif
    if (0 == Mix_OpenAudio(AUDIO_RATE, AUDIO_FORMAT, AUDIO_CHANNELS, AUDIO_BUFFERS)) {
        init_channels();
        return;
    }
    logs::error("Sound failed to initialize using default driver: %s", Mix_GetError());
    // Try to work around SDL choosing the wrong driver on Windows sometimes
    int num_drivers = SDL_GetNumAudioDrivers();
    for (int i = 0; i < num_drivers; i++) {
        const char* driver_name = SDL_GetAudioDriver(i);
        if (SDL_strcmp(driver_name, "disk") == 0 || SDL_strcmp(driver_name, "dummy") == 0) {
            // Skip "write-to-disk" and dummy drivers
            continue;
        }

        const bool ok = init_audio_with_timeout(driver_name, 1000);
        if (ok) {
            logs::info("Using audio driver: %s", driver_name);
            init_channels();
            return;
        } else {
          logs::info("Not using audio driver %s, reason: %s", driver_name, SDL_GetError());
        }
    }

    logs::error("Sound failed to initialize: %s", Mix_GetError());
    int max = SDL_GetNumAudioDevices(0);
    logs::info("Number of audio devices: %d", max);

    for (int i = 0; i < max; i++) {
        logs::info("Audio device: %s", SDL_GetAudioDeviceName(i, 0));
    }
}

void sound_manager_t::close() {
    if (!initialized) {
        return;
    }

    for (int i = 0, size = _channels.size(); i < size; i++) {
        stop_channel(i);
    }

    Mix_CloseAudio();
    initialized = false;
}

void sound_manager_t::load_formats() {
    if (!initialized) {
        return;
    }

    const int format_desc_max_chars = 4;
    const music_format formats[] = {{MIX_INIT_FLAC, "FLAC"},
                                    {MIX_INIT_MOD, "MOD"},
                                    {MIX_INIT_MP3, "MP3"},
                                    {MIX_INIT_OGG, "OGG"},
                                    {MIX_INIT_MID, "MIDI"},
                                    {MIX_INIT_OPUS, "Opus"}};

    const int max_num_formats = sizeof(formats) / sizeof(formats[0]);

    int all_flags = 0;
    for (int i = 0; i < max_num_formats; ++i) {
        all_flags |= formats[i].flag;
    }

    const int initialized_flags = Mix_Init(all_flags);
    if (initialized_flags == 0) {
        logs::error("Could not load any music formats: %s", Mix_GetError());
    } else {
        const char* seperator = ", ";
        const int seperator_length = strlen(seperator);
        const int max_format_length = format_desc_max_chars + seperator_length; // desc + seperator
        std::vector<char> data(max_num_formats * max_format_length + 1);
        char* buf = data.data();

        int buf_pos = 0;
        for (int i = 0; i < max_num_formats; ++i) {
            if (initialized_flags & formats[i].flag) {
                int desc_length = strlen(formats[i].desc);
                if (desc_length > format_desc_max_chars) {
                    desc_length = format_desc_max_chars;
                }

                memcpy(buf + buf_pos, formats[i].desc, desc_length);
                buf_pos += desc_length;
                memcpy(buf + buf_pos, seperator, seperator_length);
                buf_pos += seperator_length;
            }
        }
        if (buf_pos >= seperator_length) {
            // remove last seperator
            buf_pos -= seperator_length;
        }
        buf[buf_pos] = 0;

        logs::info("music formats initialized: %s (%i)", buf, initialized_flags);
    }
}

void sound_manager_t::unload_formats() {
    Mix_Quit();
}

bool sound_manager_t::is_channel_playing(int channel) {
    return _channels[channel].chunk && Mix_Playing(channel);
}

void sound_manager_t::music_set_volume(int volume_pct) {
    Mix_VolumeMusic(percentage_to_volume(volume_pct));
}

void sound_manager_t::set_channel_panning(int channel, int left, int right) {
    Mix_SetPanning(channel, left, right);
}

void sound_manager_t::set_channel_volume(int channel, int volume_pct) {
    if (_channels[channel].chunk) {
        Mix_VolumeChunk((Mix_Chunk*)_channels[channel].chunk, percentage_to_volume(volume_pct));
    }
}

#ifdef __vita__
static void load_music_for_vita(const char* filename) {
    if (vita_music_data.buffer) {
        if (strcmp(filename, vita_music_data.filename) == 0)
            return;
        free(vita_music_data.buffer);
        vita_music_data.buffer = 0;
    }
    strncpy(vita_music_data.filename, filename, FILE_NAME_MAX - 1);
    char* resolved_filename = vita_prepend_path(filename);
    SceUID fd = sceIoOpen(resolved_filename, SCE_O_RDONLY, 0777);
    free(resolved_filename);
    if (fd < 0)
        return;
    vita_music_data.size = sceIoLseek(fd, 0, SCE_SEEK_END);
    sceIoLseek(fd, 0, SCE_SEEK_SET);
    vita_music_data.buffer = malloc(sizeof(char) * vita_music_data.size);
    sceIoRead(fd, vita_music_data.buffer, vita_music_data.size);
    sceIoClose(fd);
}
#endif

bool sound_manager_t::play_music(pcstr filename, int volume_pct) {
    if (!initialized) {
        return false;
    }

    stop_music();
#ifdef __vita__
    load_music_for_vita(filename);
    if (!vita_music_data.buffer)
        return 0;

    SDL_RWops* sdl_music = SDL_RWFromMem(vita_music_data.buffer, vita_music_data.size);
    data.music = Mix_LoadMUSType_RW(sdl_music, vfs::file_has_extension(filename, "mp3") ? MUS_MP3 : MUS_WAV, SDL_TRUE);
#else
    _music_player->music = Mix_LoadMUS(filename);
#endif
    if (!_music_player->music) {
        logs::warn("Error opening music file '%s'. Reason: %s", filename, Mix_GetError());
    } else {
        if (Mix_PlayMusic(_music_player->music, -1) == -1) {
            _music_player->music = nullptr;
            logs::warn("Error playing music file '%s'. Reason: %s", filename, Mix_GetError());
        } else {
            music_set_volume(volume_pct);
        }
    }
    return !!_music_player->music;
}

void sound_manager_t::play_file_on_channel(pcstr filename, int channel, int volume_pct) {
    if (!initialized) {
        return;
    }

    stop_channel(channel);
    _channels[channel].chunk = load_chunk(filename);
    if (!_channels[channel].chunk) {
        return;
    }
    
    set_channel_volume(channel, volume_pct);
    Mix_PlayChannelTimed(channel, (Mix_Chunk*)_channels[channel].chunk, 0, -1);
}

void sound_manager_t::play_channel(int channel, int volume_pct) {
    if (!initialized) {
        return;
    }

    game.mt.detach_task([this, channel, volume_pct] () {
        channel_t &ch = _channels[channel];
        if (!load_channel(&ch)) {
            return;
        }

        ch.playing = true;
        set_channel_volume(channel, volume_pct * 0.4);

        Mix_PlayChannelTimed(channel, (Mix_Chunk*)ch.chunk, 0, -1);
    });
}

void sound_manager_t::play_channel_panned(int channel, int volume_pct, int left_pct, int right_pct) {
    if (!initialized) {
        return;
    }

    game.mt.detach_task([this, channel, volume_pct, left_pct, right_pct] () {
        channel_t &ch = _channels[channel];
        if (!load_channel(&ch)) {
            return;
        }

        ch.left_pan = left_pct * 255 / 100;
        ch.right_pan = right_pct * 255 / 100;
        ch.volume = volume_pct;
        ch.playing = true;

        set_channel_panning(channel, ch.left_pan, ch.right_pan);
        set_channel_volume(channel, ch.volume);

        Mix_PlayChannelTimed(channel, (Mix_Chunk *)ch.chunk, 0, -1);
    });
}

void sound_manager_t::stop_music() {
    if (!initialized) {
        return;
    }

    if (!_music_player->music) {
        return;
    }

    Mix_HaltMusic();
    Mix_FreeMusic(_music_player->music);
    _music_player->music = nullptr;
}

void sound_manager_t::stop_channel(int channel) {
    if (!initialized) {
        return;
    }

    channel_t* ch = &_channels[channel];
    if (!ch->chunk) {
        return;
    }

    Mix_HaltChannel(channel);
    Mix_FreeChunk((Mix_Chunk*)ch->chunk);
    ch->chunk = 0;
}

void sound_manager_t::free_custom_audio_stream() {
#ifdef USE_SDL_AUDIOSTREAM
    if (_music_player->use_audiostream) {
        if (_music_player->stream) {
            SDL_FreeAudioStream(_music_player->stream);
            _music_player->stream = nullptr;
        }
        return;
    }
#endif // USE_SDL_AUDIOSTREAM

    if (_music_player->buffer) {
        free(_music_player->buffer);
        _music_player->buffer = nullptr;
    }
}

bool sound_manager_t::create_custom_audio_stream(uint16_t src_format, uint8_t src_channels, int src_rate, uint16_t dst_format, uint8_t dst_channels, int dst_rate) {
    free_custom_audio_stream();

#ifdef USE_SDL_AUDIOSTREAM
    if (_music_player->use_audiostream) {
        _music_player->stream = SDL_NewAudioStream(src_format, src_channels, src_rate, dst_format, dst_channels, dst_rate);
        return !!_music_player->stream;
    }
#endif

    int result = SDL_BuildAudioCVT(&_music_player->cvt, src_format, src_channels, src_rate, dst_format, dst_channels, dst_rate);
    if (result < 0) {
        return false;
    }

    // Allocate buffer large enough for 2 seconds of 16-bit audio
    _music_player->buffer_size = dst_rate * dst_channels * 2 * 2;
    _music_player->buffer = (unsigned char*)malloc(_music_player->buffer_size);
    if (!_music_player->buffer) {
        return false;
    }

    _music_player->cur_read = 0;
    _music_player->cur_write = 0;
    return true;
}

bool sound_manager_t::is_audio_stream_active() {
#ifdef USE_SDL_AUDIOSTREAM
    if (_music_player->use_audiostream) {
        return !!_music_player->stream;
    }
#endif
    return !!_music_player->buffer;
}

bool sound_manager_t::put_custom_audio_stream(uint8_t* audio_data, int len) {
    if (!audio_data || len <= 0 || !is_audio_stream_active()) {
        return 0;
    }

#ifdef USE_SDL_AUDIOSTREAM
    if (_music_player->use_audiostream) {
        return SDL_AudioStreamPut(_music_player->stream, audio_data, len) == 0;
    }
#endif

    // Convert audio to SDL format
    _music_player->cvt.buf = (Uint8*)malloc((size_t)(len * _music_player->cvt.len_mult));
    if (!_music_player->cvt.buf) {
        return false;
    }

    memcpy(_music_player->cvt.buf, audio_data, len);
    _music_player->cvt.len = len;
    SDL_ConvertAudio(&_music_player->cvt);
    int converted_len = _music_player->cvt.len_cvt;

    // Copy data to circular buffer
    if (converted_len + _music_player->cur_write <= _music_player->buffer_size) {
        memcpy(&_music_player->buffer[_music_player->cur_write], _music_player->cvt.buf, converted_len);
    } else {
        int end_len = _music_player->buffer_size - _music_player->cur_write;
        memcpy(&_music_player->buffer[_music_player->cur_write], _music_player->cvt.buf, end_len);
        memcpy(_music_player->buffer, &_music_player->cvt.buf[end_len], converted_len - end_len);
    }
    _music_player->cur_write = (_music_player->cur_write + converted_len) % _music_player->buffer_size;

    // Clean up
    free(_music_player->cvt.buf);
    _music_player->cvt.buf = 0;
    _music_player->cvt.len = 0;

    return true;
}

int sound_manager_t::get_custom_audio_stream(Uint8* dst, int len) {
    if (!dst || len <= 0 || !is_audio_stream_active()) {
        return 0;
    }

#ifdef USE_SDL_AUDIOSTREAM
    if (_music_player->use_audiostream) {
        return SDL_AudioStreamGet(_music_player->stream, dst, len);
    }
#endif

    int bytes_copied = 0;
    if (_music_player->cur_read < _music_player->cur_write) {
        int bytes_available = _music_player->cur_write - _music_player->cur_read;
        int bytes_to_copy = bytes_available < len ? bytes_available : len;
        memcpy(dst, &_music_player->buffer[_music_player->cur_read], bytes_to_copy);
        bytes_copied = bytes_to_copy;
    } else {
        int bytes_available = _music_player->buffer_size - _music_player->cur_read;
        int bytes_to_copy = bytes_available < len ? bytes_available : len;
        memcpy(dst, &_music_player->buffer[_music_player->cur_read], bytes_to_copy);
        bytes_copied = bytes_to_copy;
        if (bytes_copied < len) {
            int second_part_len = len - bytes_copied;
            bytes_available = _music_player->cur_write;
            bytes_to_copy = bytes_available < second_part_len ? bytes_available : second_part_len;
            memcpy(&dst[bytes_copied], _music_player->buffer, bytes_to_copy);
            bytes_copied += bytes_to_copy;
        }
    }
    _music_player->cur_read = (_music_player->cur_read + bytes_copied) % _music_player->buffer_size;

    return bytes_copied;
}

void sound_manager_t::custom_music_callback(void* dummy, Uint8* stream, int len) {
    int bytes_copied = g_sound.get_custom_audio_stream(stream, len);

    if (bytes_copied < len) {
        // end of stream, write silence
        memset(&stream[bytes_copied], 0, len - bytes_copied);
    }
}

void sound_manager_t::use_custom_music_player(int bitdepth, int num_channels, int rate, void* audio_data, int len) {
    SDL_AudioFormat format;
    if (bitdepth == 8)
        format = AUDIO_U8;
    else if (bitdepth == 16)
        format = AUDIO_S16;
    else {
        logs::error("Custom music bitdepth not supported: %u", bitdepth);
        return;
    }
    int device_rate;
    Uint16 device_format;
    int device_channels;
    Mix_QuerySpec(&device_rate, &device_format, &device_channels);
    _music_player->format = format;

    int result = create_custom_audio_stream(format, num_channels, rate, device_format, device_channels, device_rate);
    if (!result) {
        return;
    }

    write_custom_music_data(audio_data, len);

    Mix_HookMusic(custom_music_callback, 0);
}

void sound_manager_t::write_custom_music_data(void* audio_data, int len) {
    if (!audio_data || len <= 0 || !is_audio_stream_active()) {
        return;
    }
    // Mix audio to sound effect volume
    Uint8* mix_buffer = (Uint8*)malloc(len);
    if (!mix_buffer)
        return;
    memset(mix_buffer, (_music_player->format == AUDIO_U8) ? 128 : 0, len);
    SDL_MixAudioFormat(mix_buffer, (uint8_t*)audio_data, _music_player->format, len, percentage_to_volume(g_settings.get_sound(SOUND_EFFECTS)->volume));

    put_custom_audio_stream(mix_buffer, len);
    free(mix_buffer);
}

void sound_manager_t::use_default_music_player() {
    Mix_HookMusic(0, 0);
    free_custom_audio_stream();
}

void sound_manager_t::update_channel(int channel, vfs::path filename) {
    if (filename.empty()) {
        return;
    }

    _channels_info[channel] = filename;
    vfs::path &original = _channels_info[channel];
    vfs::path audio_path("AUDIO/", _channels_info[channel]);

    if (!vfs::file_exists(audio_path)) {
        logs::info("Sound: cant find audio %s", audio_path.c_str());
        _channels_info[channel].clear();
    } else {
        original = vfs::content_path(audio_path);
        init_channel(channel, original);
    }
}

void sound_manager_t::play_effect(int effect) {
    if (!g_settings.get_sound(SOUND_EFFECTS)->enabled) {
        return;
    }

    if (is_channel_playing(effect)) {
        return;
    }

    play_channel(effect, g_settings.get_sound(SOUND_EFFECTS)->volume);
}
