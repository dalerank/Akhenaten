#include <SDL.h>

#include <SDL_mixer.h>

#include "sound/sound.h"
#include "sound/channel.h"
#include "content/file_formats.h"
#include "core/log.h"
#include "core/calc.h"
#include "game/game_config.h"
#include "platform/arguments.h"
#include "platform/platform.h"
#include "platform/vita/vita.h"
#include "game/game.h"
#include "js/js_game.h"

#include "lame_helper.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
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
        xstring path = arch.r_string("p");
        g_sound.update_channel(channel, path.c_str());
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
    uint64_t custom_stream_bytes_written = 0;
    uint64_t custom_stream_bytes_read = 0;
    uint32_t custom_stream_bytes_per_second = 0;
    Mix_Music* music;
    vfs::reader current_music_data;
    int custom_music_underrun_logs = 0;

    // Main thread only.
    std::map<std::string, vfs::reader> cached_chunks;
};

struct music_format {
    const int flag;
    pcstr desc;
};

sound_manager_t g_sound;

// OG hands the 0..100 volume setting straight to Miles, whose scale is 0..127 (miles_sdl.c to_mixer_volume).
static int settings_volume_to_mixer(int volume) {
    return calc_bound(volume, 0, 127) * MIX_MAX_VOLUME / 127;
}

Mix_MusicType get_music_type(pcstr filename) {
    if (vfs::file_has_extension(filename, "mp3")) {
        return MUS_MP3;
    }
    if (vfs::file_has_extension(filename, "wav")) {
        return MUS_WAV;
    }
    if (vfs::file_has_extension(filename, "ogg")) {
        return MUS_OGG;
    }
    return MUS_NONE;
}

vfs::reader load_music_data(pcstr filename, Mix_MusicType& music_type) {
    music_type = get_music_type(filename);

#if defined(GAME_PLATFORM_ANDROID)
    // Prefer native Mix MP3 (minimp3) when available; lame→WAV is the fallback
    // for builds where SDL2_mixer was compiled without MIX_INIT_MP3.
    if (music_type == MUS_MP3) {
        vfs::reader raw = vfs::file_open(filename, "rb");
        if (raw) {
            return raw;
        }
        lame_helper helper;
        vfs::reader decoded = helper.decode(filename);
        if (decoded) {
            music_type = MUS_WAV;
            return decoded;
        }
    }
#endif

    return vfs::file_open(filename, "rb");
}

void sound_manager_t::init() {
    if (!_music_player) {
        _music_player = new music_player_t();
    }

    open();
    allocate_channels();
    load_formats();
}

void sound_manager_t::set_volume(int b, int e, int percentage) {
    for (int i = b; i <= e; i++) {
        set_channel_volume(i, percentage);
    }
}

void sound_manager_t::shutdown() {
    close();

    unload_formats();

    delete _music_player;
    _music_player = nullptr;
}

// Touches no shared state, so it may run on a worker thread.
static vfs::reader read_chunk_file(vfs::path filename) {
    vfs::path converted_wav(filename);
    auto format = get_format_from_file(filename);
    if (format == FILE_FORMAT_MP3) {
        converted_wav.change_extension("wav");
        if (vfs::file_exists(converted_wav)) {
            return vfs::file_open(converted_wav);
        }
#if defined(GAME_PLATFORM_ANDROID)
        // Prefer raw MP3 bytes — Mix_LoadWAV decodes when MIX_INIT_MP3 (minimp3) is on.
        vfs::reader raw = vfs::file_open(filename);
        if (raw) {
            return raw;
        }
#endif
        lame_helper helper;
        return helper.decode(filename);
    }

    return vfs::file_open(converted_wav);
}

static bool is_chunk_format(pcstr filename) {
    auto format = get_format_from_file(filename);
    return format == FILE_FORMAT_MP3 || format == FILE_FORMAT_WAV;
}

void* sound_manager_t::chunk_from_reader(const vfs::reader& r) {
    if (!r) {
        return nullptr;
    }
    // Mix_LoadWAV_RW copies the samples, so the reader may go away afterwards.
    SDL_RWops* sdl_fp = SDL_RWFromConstMem(r->data(), r->size());
    return Mix_LoadWAV_RW(sdl_fp, SDL_TRUE);
}

void* sound_manager_t::load_chunk(pcstr filename, bool cache) {
    if (filename && *filename) {
        if (g_args.is_log_sound()) {
            logs::info("Sound: load chunk %s", filename);
        }

        if (is_chunk_format(filename)) {
            vfs::reader r;
            auto it = _music_player->cached_chunks.find(filename);
            if (it != _music_player->cached_chunks.end()) {
                r = it->second;
            } else {
                r = read_chunk_file(filename);
                if (cache) {
                    _music_player->cached_chunks[filename] = r;
                }
            }

            if (Mix_Chunk* chunk = (Mix_Chunk*)chunk_from_reader(r)) {
                return chunk;
            }

#if defined(GAME_PLATFORM_ANDROID)
            // Cached raw MP3 but Mix_LoadWAV failed (old mixer without MP3) — lame→WAV.
            if (get_format_from_file(filename) == FILE_FORMAT_MP3) {
                lame_helper helper;
                r = helper.decode(filename);
                if (r) {
                    if (cache) {
                        _music_player->cached_chunks[filename] = r;
                    }
                    return chunk_from_reader(r);
                }
            }
#endif
            return nullptr;
        }

#if defined(__vita__) || defined(GAME_PLATFORM_ANDROID)
        FILE* fp = vfs::file_open_os(filename, "rb");
        if (!fp) {
            return NULL;
        }

        SDL_RWops* sdl_fp = SDL_RWFromFP(fp, SDL_TRUE);
        return Mix_LoadWAV_RW(sdl_fp, 1);
#else
        //verify_no_crash(false && "unsupported format");
        //return Mix_LoadWAV_RW(SDL_RWFromFile(filename, "rb"), 1);
#endif
    }

    return NULL;
}

void sound_manager_t::start_channel(int channel) {
    channel_t& ch = _channels[channel];
    ch.play_requested = false;
    if (!ch.chunk) {
        return;
    }

    if (ch.panned) {
        set_channel_panning(channel, ch.left_pan, ch.right_pan);
    } else {
        Mix_SetPanning(channel, 255, 255);
    }
    set_channel_volume(channel, ch.volume);

    if (Mix_PlayChannelTimed(channel, (Mix_Chunk*)ch.chunk, 0, -1) >= 0) {
        ch.playing = true;
    }
}

void sound_manager_t::poll_pending_chunks() {
    for (int i = 0, size = (int)_channels.size(); i < size; i++) {
        channel_t& ch = _channels[i];
        if (!ch.pending.valid() || ch.pending.wait_for(std::chrono::seconds(0)) != std::future_status::ready) {
            continue;
        }

        vfs::reader r = ch.pending.get();
        _music_player->cached_chunks[ch.filename.c_str()] = r;
        if (!ch.chunk) {
            ch.chunk = chunk_from_reader(r);
        }
        if (ch.play_requested) {
            start_channel(i);
        }
    }
}

void sound_manager_t::begin_frame() {
    if (!_music_player) {
        return;
    }

    if (initialized) {
        poll_pending_chunks();

        for (int i = 0, size = (int)_channels.size(); i < size; i++) {
            _channels[i].playing = _channels[i].chunk && Mix_Playing(i);
        }

        // The enhanced city ambience sets each voice's volume itself (sound_city_play).
        if (!game_features::gameplay_enhanced_city_ambient) {
            const auto city_volume = calc_bound(game_features::gameopt_sound_city_volume.to_int(), 0, 100);
            set_volume(SOUND_CHANNEL_CITY_MIN, SOUND_CHANNEL_CITY_MAX, city_volume);
        }

        const auto effects_volume = calc_bound(game_features::gameopt_sound_effects_volume.to_int(), 0, 100);
        set_volume(SOUND_CHANNEL_EFFECTS_MIN, SOUND_CHANNEL_EFFECTS_MAX, effects_volume);

        const auto music_volume = calc_bound(game_features::gameopt_sound_music_volume.to_int(), 0, 100);
        Mix_VolumeMusic(settings_volume_to_mixer(music_volume));

        const auto speech_volume = calc_bound(game_features::gameopt_sound_speech_volume.to_int(), 0, 100);
        set_channel_volume(SOUND_CHANNEL_SPEECH, speech_volume);
    }

    music_frame();
}

bool sound_manager_t::music_playing() {
    if (!initialized || !_music_player || !_music_player->music) {
        return false;
    }

    return Mix_PlayingMusic() != 0;
}

void sound_manager_t::init_channels() {
    initialized = true;
    for (auto &ch: _channels) {
        ch.chunk = 0;
    }
}

void sound_manager_t::init_channel(int index, vfs::path filename) {
    channel_t& ch = _channels[index];
    if (ch.filename == filename) {
        return;
    }

    if (initialized && ch.chunk) {
        Mix_HaltChannel(index);
        Mix_FreeChunk((Mix_Chunk*)ch.chunk);
    }
    ch.chunk = nullptr;
    ch.play_requested = false;
    ch.pending = {};
    ch.filename = filename;
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

    int num_drivers = SDL_GetNumAudioDrivers();
    for (int i = 0; i < num_drivers; i++) {
        const char* driver_name = SDL_GetAudioDriver(i);
        if (SDL_strcmp(driver_name, "disk") == 0 || SDL_strcmp(driver_name, "dummy") == 0
            || SDL_strcmp(driver_name, "dsp") == 0 || SDL_strcmp(driver_name, "oss") == 0) {
            continue;
        }

        // The former std::async "timeout" blocked in the future's destructor anyway; open on this thread.
        const bool ok = SDL_AudioInit(driver_name) == 0
                        && Mix_OpenAudio(AUDIO_RATE, AUDIO_FORMAT, AUDIO_CHANNELS, AUDIO_BUFFERS) == 0;
        if (ok) {
            logs::info("Using audio driver: %s", driver_name);
            init_channels();
            return;
        } else {
          logs::info("Not using audio driver %s, reason: %s", driver_name, SDL_GetError());
        }
    }

    logs::error("Sound failed to initialize: %s (continuing without audio)", Mix_GetError());
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
    if (!initialized) {
        return false;
    }
    const channel_t& ch = _channels[channel];
    return ch.play_requested || (ch.chunk && Mix_Playing(channel));
}

void sound_manager_t::set_channel_panning(int channel, int left, int right) {
    Mix_SetPanning(channel, left, right);
}

void sound_manager_t::set_channel_pan(int channel, int left_pct, int right_pct) {
    if (!initialized) {
        return;
    }
    set_channel_panning(channel, calc_bound(left_pct, 0, 100) * 255 / 100, calc_bound(right_pct, 0, 100) * 255 / 100);
}

void sound_manager_t::set_channel_volume(int channel, int volume_pct) {
    if (!initialized) {
        return;
    }
    // Channel volume only: also scaling the chunk would apply the setting twice.
    Mix_Volume(channel, settings_volume_to_mixer(volume_pct));
}

bool sound_manager_t::play_file_on_channel(pcstr filename, int channel, int volume_pct) {
    if (!initialized) {
        return false;
    }

    stop_channel(channel);
    _channels[channel].chunk = load_chunk(filename, false);
    if (!_channels[channel].chunk) {
        return false;
    }

    set_channel_volume(channel, volume_pct);
    if (Mix_PlayChannelTimed(channel, (Mix_Chunk*)_channels[channel].chunk, 0, -1) < 0) {
        logs::warn("Sound: Mix_PlayChannel failed for '%s': %s", filename ? filename : "<null>", Mix_GetError());
        return false;
    }
    _channels[channel].playing = true;
    return true;
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

bool sound_manager_t::play_music(pcstr filename, int volume_pct, bool loop) {
    if (!initialized) {
        return false;
    }

    if (g_args.is_log_sound()) {
        logs::info("Sound: play music %s (volume %d%%)", filename ? filename : "<null>", volume_pct);
    }

    stop_music();
#ifdef __vita__
    load_music_for_vita(filename);
    if (!vita_music_data.buffer)
        return 0;

    SDL_RWops* sdl_music = SDL_RWFromMem(vita_music_data.buffer, vita_music_data.size);
    _music_player->music = Mix_LoadMUSType_RW(sdl_music, vfs::file_has_extension(filename, "mp3") ? MUS_MP3 : MUS_WAV, SDL_TRUE);
#else
    Mix_MusicType music_type = MUS_NONE;
    _music_player->current_music_data = load_music_data(filename, music_type);
    if (_music_player->current_music_data) {
        SDL_RWops* sdl_music = SDL_RWFromConstMem(_music_player->current_music_data->data(), _music_player->current_music_data->size());
        _music_player->music = Mix_LoadMUSType_RW(sdl_music, music_type, SDL_TRUE);
#if defined(GAME_PLATFORM_ANDROID)
        // Native MP3 failed (mixer without MIX_INIT_MP3) — decode via lame to WAV.
        if (!_music_player->music && music_type == MUS_MP3) {
            lame_helper helper;
            vfs::reader decoded = helper.decode(filename);
            if (decoded) {
                _music_player->current_music_data = decoded;
                sdl_music = SDL_RWFromConstMem(decoded->data(), decoded->size());
                _music_player->music = Mix_LoadMUSType_RW(sdl_music, MUS_WAV, SDL_TRUE);
            }
        }
#endif
    } else {
        _music_player->music = nullptr;
    }
#endif
    if (!_music_player->music) {
        _music_player->current_music_data.reset();
        logs::warn("Error opening music file '%s'. Reason: %s", filename, Mix_GetError());
    } else {
        if (Mix_PlayMusic(_music_player->music, loop ? -1 : 1) == -1) {
            Mix_FreeMusic(_music_player->music);
            _music_player->music = nullptr;
            _music_player->current_music_data.reset();
            logs::warn("Error playing music file '%s'. Reason: %s", filename, Mix_GetError());
        } else {
            Mix_VolumeMusic(settings_volume_to_mixer(volume_pct));
        }
    }
    return !!_music_player->music;
}

// Runs on the main thread only. A missing chunk is decoded on a worker (pure file work); the
// Mix_* calls, the cache and the channel state stay here, picked up in poll_pending_chunks().
void sound_manager_t::request_channel(int channel) {
    channel_t& ch = _channels[channel];
    if (!ch.chunk && !ch.filename.empty()) {
        auto it = _music_player->cached_chunks.find(ch.filename.c_str());
        if (it != _music_player->cached_chunks.end()) {
            ch.chunk = chunk_from_reader(it->second);
        } else if (is_chunk_format(ch.filename)) {
            ch.play_requested = true;
            if (!ch.pending.valid()) {
                vfs::path filename = ch.filename;
                ch.pending = game.mt.submit_task([filename] { return read_chunk_file(filename); });
            }
            return;
        } else {
            ch.chunk = load_chunk(ch.filename, true);
        }
    }

    start_channel(channel);
}

void sound_manager_t::play_channel(int channel, int volume_pct) {
    if (!initialized) {
        return;
    }

    channel_t& ch = _channels[channel];
    ch.volume = volume_pct;
    ch.panned = false;
    request_channel(channel);
}

void sound_manager_t::play_channel_panned(int channel, int volume_pct, int left_pct, int right_pct) {
    if (!initialized) {
        return;
    }

    channel_t& ch = _channels[channel];
    ch.left_pan = left_pct * 255 / 100;
    ch.right_pan = right_pct * 255 / 100;
    ch.volume = volume_pct;
    ch.panned = true;
    request_channel(channel);
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
    _music_player->current_music_data.reset();
}

void sound_manager_t::fade_out_music(int ms) {
    if (!initialized || !_music_player->music) {
        return;
    }
    Mix_FadeOutMusic(ms);
}

void sound_manager_t::stop_channel(int channel) {
    if (!initialized) {
        return;
    }

    channel_t* ch = &_channels[channel];
    ch->play_requested = false;
    if (!ch->chunk) {
        return;
    }

    // Mix_HaltChannel returns only after the mixer has let go of the chunk.
    Mix_HaltChannel(channel);
    Mix_FreeChunk((Mix_Chunk*)ch->chunk);
    ch->chunk = 0;
    ch->playing = false;
}

void sound_manager_t::stop_city_channel(int channel) {
    if (channel >= SOUND_CHANNEL_CITY_MIN && channel <= SOUND_CHANNEL_CITY_MAX) {
        stop_channel(channel);
    }
}

void sound_manager_t::stop_city_channels() {
    if (!initialized) {
        return;
    }
    for (int i = SOUND_CHANNEL_CITY_MIN; i <= SOUND_CHANNEL_CITY_MAX; i++) {
        stop_channel(i);
    }
}

void sound_manager_t::free_custom_audio_stream() {
    if (!_music_player) {
        return;
    }

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
    if (!_music_player) {
        return false;
    }

    free_custom_audio_stream();
    _music_player->custom_stream_bytes_written = 0;
    _music_player->custom_stream_bytes_read = 0;
    _music_player->custom_stream_bytes_per_second = dst_rate * dst_channels * (SDL_AUDIO_BITSIZE(dst_format) / 8);
    _music_player->custom_music_underrun_logs = 0;

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
    if (!_music_player) {
        return false;
    }
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
        int available_before = SDL_AudioStreamAvailable(_music_player->stream);
        if (SDL_AudioStreamPut(_music_player->stream, audio_data, len) == 0) {
            int available_after = SDL_AudioStreamAvailable(_music_player->stream);
            if (available_after > available_before) {
                _music_player->custom_stream_bytes_written += (uint64_t)(available_after - available_before);
            }
            return true;
        }
        return false;
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
    _music_player->custom_stream_bytes_written += converted_len;

    return true;
}

int sound_manager_t::get_custom_audio_stream(Uint8* dst, int len) {
    if (!dst || len <= 0 || !is_audio_stream_active()) {
        return 0;
    }

#ifdef USE_SDL_AUDIOSTREAM
    if (_music_player->use_audiostream) {
        int bytes_copied = SDL_AudioStreamGet(_music_player->stream, dst, len);
        if (bytes_copied > 0) {
            _music_player->custom_stream_bytes_read += bytes_copied;
        }
        return bytes_copied;
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
    _music_player->custom_stream_bytes_read += bytes_copied;

    return bytes_copied;
}

uint64_t sound_manager_t::custom_music_playback_micros() const {
    if (!_music_player || !_music_player->custom_stream_bytes_per_second) {
        return 0;
    }
    return (_music_player->custom_stream_bytes_read * 1000000ull) / _music_player->custom_stream_bytes_per_second;
}

uint64_t sound_manager_t::custom_music_buffered_micros() const {
    if (!_music_player || !_music_player->custom_stream_bytes_per_second) {
        return 0;
    }

    uint64_t buffered = 0;
    if (_music_player->custom_stream_bytes_written >= _music_player->custom_stream_bytes_read) {
        buffered = _music_player->custom_stream_bytes_written - _music_player->custom_stream_bytes_read;
    }
    return (buffered * 1000000ull) / _music_player->custom_stream_bytes_per_second;
}

void sound_manager_t::custom_music_callback(void* dummy, Uint8* stream, int len) {
    int bytes_copied = g_sound.get_custom_audio_stream(stream, len);

    if (bytes_copied < len) {
        if (g_sound._music_player->custom_music_underrun_logs < 20) {
            logs::warn("BIK audio underrun: requested=%d copied=%d buffered_us=%llu played_us=%llu",
                len,
                bytes_copied,
                (unsigned long long)g_sound.custom_music_buffered_micros(),
                (unsigned long long)g_sound.custom_music_playback_micros());
            ++g_sound._music_player->custom_music_underrun_logs;
        }
        // end of stream, write silence
        memset(&stream[bytes_copied], 0, len - bytes_copied);
    }
}

void sound_manager_t::use_custom_music_player(int bitdepth, int num_channels, int rate, void* audio_data, int len) {
    // --nosound / failed mixer init: video may still play, but skip BIK audio path.
    if (!_music_player || !initialized) {
        return;
    }

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
    SDL_MixAudioFormat(mix_buffer, (uint8_t*)audio_data, _music_player->format, len,
      settings_volume_to_mixer(calc_bound(game_features::gameopt_sound_effects_volume.to_int(), 0, 100)));

    put_custom_audio_stream(mix_buffer, len);
    free(mix_buffer);
}

void sound_manager_t::use_default_music_player() {
    if (!_music_player || !initialized) {
        return;
    }

    Mix_HookMusic(0, 0);
    free_custom_audio_stream();
}

void sound_manager_t::update_channel(int channel, vfs::path filename) {
    if (filename.empty()) {
        return;
    }

    if (g_args.is_log_sound()) {
        logs::info("Sound: register channel %d -> %s", channel, filename.c_str());
    }

    // --nosound: mixer is never initialized, so populating channel info is pointless.
    // --no-resource: the AUDIO/ tree is intentionally absent; skip the existence probe
    // to avoid spamming "cant find audio" for every entry in city_sounds.
    if (!g_args.use_sound() || g_args.no_resource()) {
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

struct og_effect_ref {
    int effect = -1;
    int figure = -1;
    int variant = 0;
};

static og_effect_ref og_effect(int effect) {
    return {effect, -1, 0};
}
static og_effect_ref og_figure(int figure, int variant) {
    return {-1, figure, variant};
}

// Caesar III effect -> the OG effect or figure sound (sound_play.h, military.c, enemy.c) for the same event.
// Effects OG has no sound for stay silent (marching and the OG march counters play nothing, enemy.c:302).
static og_effect_ref og_effect_for(int effect) {
    if (effect >= SOUND_EFFECT_SOLDIER_DIE && effect < SOUND_EFFECT_SOLDIER_DIE + 4) {
        return og_figure(OG_FIGURE_SOUND_CITIZEN + (effect - SOUND_EFFECT_SOLDIER_DIE), OG_FIGURE_SOUND_VARIANT_DIE);
    }
    if (effect >= SOUND_EFFECT_CITIZEN_DIE && effect < SOUND_EFFECT_CITIZEN_DIE + 4) {
        return og_figure(OG_FIGURE_SOUND_CITIZEN + 4 + (effect - SOUND_EFFECT_CITIZEN_DIE),
          OG_FIGURE_SOUND_VARIANT_DIE);
    }

    switch (effect) {
    case SOUND_EFFECT_ICON:
        return og_effect(OG_SOUND_EFFECT_BUTTON);
    case SOUND_EFFECT_SIDEBAR:
        return og_effect(OG_SOUND_EFFECT_SIDEBAR);
    case SOUND_EFFECT_BUILD:
        return og_effect(OG_SOUND_EFFECT_BUILD);
    case SOUND_EFFECT_EXPLOSION:
        return og_effect(OG_SOUND_EFFECT_BUILDING_DESTROYED);
    // OG message.c plays the one message sound for urgent messages too.
    case SOUND_EFFECT_FANFARE:
    case SOUND_EFFECT_FANFARE_URGENT:
        return og_effect(OG_SOUND_EFFECT_MESSAGE);
    case SOUND_EFFECT_FIRE_SPLASH:
        return og_effect(OG_SOUND_EFFECT_FIRE_SPLASH);

    case SOUND_EFFECT_ARROW:
    case SOUND_EFFECT_LIGHT_SWORD:
        return og_figure(OG_FIGURE_SOUND_ARCHER, OG_FIGURE_SOUND_VARIANT_HIT);
    case SOUND_EFFECT_SWORD:
    case SOUND_EFFECT_SPEAR:
        return og_figure(OG_FIGURE_SOUND_INFANTRY, OG_FIGURE_SOUND_VARIANT_HIT);
    case SOUND_EFFECT_SWORD_SWING:
        return og_figure(OG_FIGURE_SOUND_CHARIOT, OG_FIGURE_SOUND_VARIANT_HIT);
    case SOUND_EFFECT_HORSE2:
        return og_figure(OG_FIGURE_SOUND_CHARIOT, OG_FIGURE_SOUND_VARIANT_DIE);
    case SOUND_EFFECT_AXE:
    case SOUND_EFFECT_CLUB:
        return og_figure(OG_FIGURE_SOUND_SWORD, OG_FIGURE_SOUND_VARIANT_HIT);
    case SOUND_EFFECT_JAVELIN:
        return og_figure(OG_FIGURE_SOUND_SHIP, OG_FIGURE_SOUND_VARIANT_HIT);
    case SOUND_EFFECT_LION_ATTACK:
        return og_figure(OG_FIGURE_SOUND_LION, OG_FIGURE_SOUND_VARIANT_HIT);
    case SOUND_EFFECT_LION_DIE:
        return og_figure(OG_FIGURE_SOUND_LION, OG_FIGURE_SOUND_VARIANT_DIE);
    case SOUND_EFFECT_OSTRICH_DIE:
        return og_figure(OG_FIGURE_SOUND_OSTRICH, OG_FIGURE_SOUND_VARIANT_DIE);
    case SOUND_EFFECT_SHEEP_DIE:
        return og_figure(OG_FIGURE_SOUND_BIRDS, OG_FIGURE_SOUND_VARIANT_DIE);
    case SOUND_EFFECT_ZEBRA_DIE:
        return og_figure(OG_FIGURE_SOUND_ANTELOPE, OG_FIGURE_SOUND_VARIANT_DIE);
    }
    return {};
}

void ANK_REGISTER_CONFIG_ITERATOR(config_load_sound_effects) {
    g_sound.clear_og_effect_files();
    g_config_arch.r_array("sound_effects",
      [](archive arch) { g_sound.set_og_effect_file(arch.r_int("id"), arch.r_string("p")); });
    g_config_arch.r_array("sound_figure_effects",
      [](archive arch) { g_sound.set_og_figure_effect_file(arch.r_int("t"), arch.r_int("v"), arch.r_string("p")); });
}

bool sound_manager_t::log_events() const {
    return g_args.is_integral_tests() || g_args.is_log_sound();
}

bool sound_manager_t::data_available() const {
    return !g_args.no_resource();
}

void sound_manager_t::clear_og_effect_files() {
    _og_effects.fill({});
    _og_figure_effects.fill({});
}

void sound_manager_t::set_og_effect_file(int id, xstring file) {
    if (id >= 0 && id < (int)_og_effects.size()) {
        _og_effects[id] = {file, {}, false};
    }
}

void sound_manager_t::set_og_figure_effect_file(int sound, int variant, xstring file) {
    if (sound >= 0 && sound < OG_FIGURE_SOUND_COUNT && variant >= 0 && variant < OG_FIGURE_SOUND_VARIANTS) {
        _og_figure_effects[sound * OG_FIGURE_SOUND_VARIANTS + variant] = {file, {}, false};
    }
}

// Probed once, like OG binding its wavs at start-up (effect.c); a missing file stays silent (-1 in OG).
const vfs::path& sound_manager_t::og_sample_path(og_sample_t& sample) {
    if (!sample.probed) {
        sample.probed = true;
        if (initialized && data_available() && !sample.file.empty()) {
            vfs::path audio_path("AUDIO/", sample.file.c_str());
            if (vfs::file_exists(audio_path)) {
                sample.resolved = vfs::content_path(audio_path);
            }
        }
    }
    return sample.resolved;
}

// Miles plays a sample on any free handle; a channel that already holds the file saves a reload.
// OG gives every effect one fixed channel (sound_play.c:46): playing it again restarts that channel,
// so a burst of collapses is one explosion, not a stack of them.
int sound_manager_t::pick_effect_channel(const vfs::path& filename) {
    if (!filename.empty()) {
        for (int c = SOUND_CHANNEL_EFFECTS_MIN; c <= SOUND_CHANNEL_EFFECTS_MAX; c++) {
            if (_channels[c].filename == filename) {
                return c;
            }
        }
    }

    for (int c = SOUND_CHANNEL_EFFECTS_MIN; c <= SOUND_CHANNEL_EFFECTS_MAX; c++) {
        if (!is_channel_playing(c)) {
            return c;
        }
    }
    return -1;
}

int sound_manager_t::play_effect(int effect) {
    if (!game_features::gameopt_sound_effects_enabled.to_bool()) {
        return -1;
    }

    const og_effect_ref ref = og_effect_for(effect);
    og_sample_t* sample = nullptr;
    if (ref.effect >= 0 && ref.effect < (int)_og_effects.size()) {
        sample = &_og_effects[ref.effect];
    } else if (ref.figure >= 0 && ref.figure < OG_FIGURE_SOUND_COUNT) {
        sample = &_og_figure_effects[ref.figure * OG_FIGURE_SOUND_VARIANTS + ref.variant];
    }

    const bool log = log_events();
    if (!sample || sample->file.empty()) {
        if (log) {
            logs::info("[sound] effect %d -> silent", effect);
        }
        return -1;
    }

    const vfs::path& path = og_sample_path(*sample);
    const int channel = pick_effect_channel(path);
    if (log) {
        if (ref.effect >= 0) {
            logs::info("[sound] effect %d -> og effect %d %s channel %d", effect, ref.effect, sample->file.c_str(),
              channel);
        } else {
            logs::info("[sound] effect %d -> og figure %d.%d %s channel %d", effect, ref.figure, ref.variant,
              sample->file.c_str(), channel);
        }
    }

    if (!initialized || path.empty() || channel < 0) {
        return channel;
    }

    init_channel(channel, path);
    play_channel(channel, calc_bound(game_features::gameopt_sound_effects_volume.to_int(), 0, 100));
    return channel;
}
