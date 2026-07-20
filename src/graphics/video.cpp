#include "video.h"

#include "core/log.h"
#include "core/system_time.h"
#include "graphics/graphics.h"
#include "content/dir.h"
#include "content/vfs.h"
#include "io/gamefiles/bink.h"
#include "io/gamefiles/smacker.h"
#include "platform/renderer.h"
#include "game/game_config.h"
#include "screen.h"
#include "sound/sound.h"
#include "sound/music.h"

#include <SDL.h>
#include <cstring>
#include <algorithm>

static struct {
    bool is_playing;
    bool is_ended;
    int backend;

    smacker s;
    bink b;
    struct {
        int width;
        int height;
        int y_scale;
        int micros_per_frame;
        time_millis start_render_millis;
        int current_frame;
        bool frame_dirty;
    } video;
    struct {
        int has_audio;
        int bitdepth;
        int channels;
        int rate;
    } audio;
    struct {
        color* pixels;
        int width;
    } buffer;
} data;

static int s_video_profile_logs = 0;
static constexpr int BIK_STARTUP_PREBUFFER_FRAMES = 4;
static constexpr int BIK_STEADY_PREBUFFER_FRAMES = 3;

enum {
    VIDEO_BACKEND_NONE = 0,
    VIDEO_BACKEND_SMK = 1,
    VIDEO_BACKEND_BIK = 2
};

static void close_smk(void) {
    if (data.s) {
        smacker_close(data.s);
        data.s = 0;
    }
}

static void close_bik(void) {
    if (data.b) {
        bink_close(data.b);
        data.b = 0;
    }
}

static int load_smk(const char* filename) {
    vfs::path fs_file = vfs::path(filename).resolve();
    if (fs_file.empty()) {
        return 0;
    }

    FILE* fp = vfs::file_open_os(fs_file, "rb");
    data.s = smacker_open(fp);
    if (!data.s) {
        // smacker_open() closes the stream on error: no need to close fp
        return 0;
    }

    int width, height, y_scale, micros_per_frame;
    smacker_get_frames_info(data.s, 0, &micros_per_frame);
    smacker_get_video_info(data.s, &width, &height, &y_scale);

    data.video.width = width;
    data.video.height = y_scale == SMACKER_Y_SCALE_NONE ? height : height * 2;
    data.video.y_scale = y_scale;
    data.video.current_frame = 0;
    data.video.frame_dirty = true;
    data.video.micros_per_frame = micros_per_frame;

    data.audio.has_audio = 0;
    if (!!game_features::gameopt_sound_effects_enabled) {
        int has_track, channels, bitdepth, rate;
        smacker_get_audio_info(data.s, 0, &has_track, &channels, &bitdepth, &rate);
        if (has_track) {
            data.audio.has_audio = 1;
            data.audio.bitdepth = bitdepth;
            data.audio.channels = channels;
            data.audio.rate = rate;
        }
    }

    if (smacker_first_frame(data.s) != SMACKER_FRAME_OK) {
        close_smk();
        return 0;
    }
    data.backend = VIDEO_BACKEND_SMK;
    return 1;
}

static int load_bik(const char* filename) {
    data.b = bink_open(filename);
    if (!data.b) {
        return 0;
    }

    data.video.width = bink_get_width(data.b);
    data.video.height = bink_get_height(data.b);
    data.video.y_scale = SMACKER_Y_SCALE_NONE;
    data.video.current_frame = 0;
    data.video.frame_dirty = true;
    data.video.micros_per_frame = bink_get_micros_per_frame(data.b);

    data.audio.has_audio = 0;
    if (!!game_features::gameopt_sound_effects_enabled && bink_has_audio(data.b)) {
        data.audio.has_audio = 1;
        data.audio.bitdepth = bink_get_audio_bitdepth(data.b);
        data.audio.channels = bink_get_audio_channels(data.b);
        data.audio.rate = bink_get_audio_sample_rate(data.b);
    }

    if (!bink_first_frame(data.b)) {
        close_bik();
        return 0;
    }
    data.backend = VIDEO_BACKEND_BIK;
    return 1;
}

static void end_video(void) {
    g_sound.use_default_music_player();
    g_sound.music_update(true);
    g_render.release_custom_texture_buffer(CUSTOM_IMAGE_VIDEO);
}

static void queue_bik_audio_chunk(void*, const void* audio_data, int len) {
    if (audio_data && len > 0) {
        g_sound.write_custom_music_data(const_cast<void*>(audio_data), len);
    }
}

bool video_start(const char* filename) {
    data.is_playing = false;
    data.is_ended = false;
    data.backend = VIDEO_BACKEND_NONE;

    if (load_smk(filename) || load_bik(filename)) {
        g_sound.music_stop();
        g_sound.speech_stop();
        g_render.create_custom_texture(CUSTOM_IMAGE_VIDEO, data.video.width, data.video.height);
        data.buffer.pixels = g_render.get_custom_texture_buffer(CUSTOM_IMAGE_VIDEO, &data.buffer.width);
        data.is_playing = true;
        return true;
    }

    logs::info("Video: failed to open '%s'", filename ? filename : "(null)");
    return false;
}

void video_size(int* width, int* height) {
    *width = data.video.width;
    *height = data.video.y_scale == SMACKER_Y_SCALE_NONE ? data.video.height : 2 * data.video.height;
}

void video_init(void) {
    data.video.start_render_millis = time_get_millis();
    s_video_profile_logs = 0;

    if (data.audio.has_audio) {
        int audio_len = data.backend == VIDEO_BACKEND_SMK
            ? smacker_get_frame_audio_size(data.s, 0)
            : bink_get_frame_audio_size(data.b);
        if (audio_len > 0) {
            void* audio_data = data.backend == VIDEO_BACKEND_SMK
                ? (void*)smacker_get_frame_audio(data.s, 0)
                : (void*)bink_get_frame_audio(data.b);
            g_sound.use_custom_music_player(data.audio.bitdepth, data.audio.channels, data.audio.rate, audio_data, audio_len);
        }
    }

    if (data.backend == VIDEO_BACKEND_BIK) {
        bink_prebuffer_frames(
            data.b,
            data.audio.has_audio ? BIK_STARTUP_PREBUFFER_FRAMES : 1,
            data.audio.has_audio ? queue_bik_audio_chunk : nullptr,
            nullptr);
    }
}

int video_is_finished(void) {
    return data.is_ended;
}

void video_stop(void) {
    if (data.is_playing) {
        if (!data.is_ended)
            end_video();

        close_smk();
        close_bik();
        data.is_playing = 0;
        data.backend = VIDEO_BACKEND_NONE;
    }
}

void video_shutdown(void) {
    if (data.is_playing) {
        close_smk();
        close_bik();
        data.is_playing = 0;
        data.backend = VIDEO_BACKEND_NONE;
    }
}

static int get_next_frame(void) {
    if (data.backend == VIDEO_BACKEND_NONE) {
        return 0;
    }
    time_millis now_millis = time_get_millis();
    int frame_no = (now_millis - data.video.start_render_millis) * 1000 / data.video.micros_per_frame;
    if (data.audio.has_audio) {
        uint64_t played_micros = g_sound.custom_music_playback_micros();
        if (played_micros > 0) {
            frame_no = (int)(played_micros / data.video.micros_per_frame);
        }
    }
    int draw_frame = data.video.frame_dirty ? 1 : 0;
    data.video.frame_dirty = false;
    frame_no = std::min(frame_no, data.video.current_frame + 1);

    while (frame_no > data.video.current_frame) {
        Uint32 decode_begin = SDL_GetTicks();
        int ok = data.backend == VIDEO_BACKEND_SMK
            ? (smacker_next_frame(data.s) == SMACKER_FRAME_OK)
            : bink_next_frame(data.b);
        if (!ok) {
            close_smk();
            close_bik();
            data.is_ended = 1;
            data.is_playing = 0;
            end_video();
            return 0;
        }
        data.video.current_frame++;
        draw_frame = 1;

        if (data.audio.has_audio && !(data.backend == VIDEO_BACKEND_BIK && bink_current_audio_is_prebuffered(data.b))) {
            int audio_len = data.backend == VIDEO_BACKEND_SMK
                ? smacker_get_frame_audio_size(data.s, 0)
                : bink_get_frame_audio_size(data.b);
            if (audio_len > 0) {
                void* audio_data = data.backend == VIDEO_BACKEND_SMK
                    ? (void*)smacker_get_frame_audio(data.s, 0)
                    : (void*)bink_get_frame_audio(data.b);
                g_sound.write_custom_music_data(audio_data, audio_len);
            }
        }

        if (data.backend == VIDEO_BACKEND_BIK) {
            bink_prebuffer_frames(
                data.b,
                data.audio.has_audio ? BIK_STEADY_PREBUFFER_FRAMES : 1,
                data.audio.has_audio ? queue_bik_audio_chunk : nullptr,
                nullptr);
        }

        if (s_video_profile_logs < 20) {
            Uint32 decode_end = SDL_GetTicks();
            logs::info(
                "BIK profile: frame=%d decode_ms=%u target_frame=%d played_us=%llu buffered_us=%llu",
                data.video.current_frame,
                (unsigned)(decode_end - decode_begin),
                frame_no,
                (unsigned long long)g_sound.custom_music_playback_micros(),
                (unsigned long long)g_sound.custom_music_buffered_micros());
            ++s_video_profile_logs;
        }
    }
    return draw_frame;
}
static void update_video_frame(void) {
    if (data.backend == VIDEO_BACKEND_BIK) {
        const uint32_t* frame = bink_get_frame_rgba(data.b);
        if (frame) {
            for (int y = 0; y < data.video.height; y++) {
                color* pixel = &data.buffer.pixels[y * data.buffer.width];
                const uint32_t* line = frame + (y * data.video.width);
                std::memcpy(pixel, line, (size_t)data.video.width * sizeof(color));
            }
        }
    } else {
        const unsigned char* frame = smacker_get_frame_video(data.s);
        const uint32_t* pal = smacker_get_frame_palette(data.s);
        if (frame && pal) {
            for (int y = 0; y < data.video.height; y++) {
                color* pixel = &data.buffer.pixels[y * data.buffer.width];
                int video_y = data.video.y_scale == SMACKER_Y_SCALE_NONE ? y : y / 2;
                const unsigned char* line = frame + (video_y * data.video.width);
                for (int x = 0; x < data.video.width; x++) {
                    *pixel = ALPHA_OPAQUE | pal[line[x]];
                    ++pixel;
                }
            }
        }
    }
    g_render.update_custom_texture(CUSTOM_IMAGE_VIDEO);
}

void video_draw(int x_offset, int y_offset) {
    if (get_next_frame())
        update_video_frame();

    g_render.draw_custom_texture(CUSTOM_IMAGE_VIDEO, x_offset, y_offset, 1.0f);
}

void video_draw_fullscreen(void) {
    if (get_next_frame())
        update_video_frame();

    int width = screen_width();
    int height = screen_height();
    if (width <= 0 || height <= 0 || data.video.width <= 0 || data.video.height <= 0) {
        return;
    }

    float scale_w = data.video.width / (float) width;
    float scale_h = data.video.height / (float) height;
    float scale = std::max(scale_w, scale_h);
    if (scale <= 0.0f) {
        return;
    }

    int x = 0;
    int y = 0;
    if (scale == scale_h) {
        x = (int)(((width - data.video.width / scale) / 2.0f) * scale);
    }
    if (scale == scale_w) {
        y = (int)(((height - data.video.height / scale) / 2.0f) * scale);
    }

    g_render.draw_custom_texture(CUSTOM_IMAGE_VIDEO, x, y, scale);
}
