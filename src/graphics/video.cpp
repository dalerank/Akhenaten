#include "video.h"

#include "core/system_time.h"
#include "game/settings.h"
#include "graphics/graphics.h"
#include "content/dir.h"
#include "content/vfs.h"
#include "io/gamefiles/smacker.h"
#include "platform/renderer.h"
#include "screen.h"
#include "sound/sound.h"
#include "sound/music.h"

static struct {
    bool is_playing;
    bool is_ended;

    smacker s;
    struct {
        int width;
        int height;
        int y_scale;
        int micros_per_frame;
        time_millis start_render_millis;
        int current_frame;
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

static void close_smk(void) {
    if (data.s) {
        smacker_close(data.s);
        data.s = 0;
    }
}

static int load_smk(const char* filename) {
    vfs::path fs_file = vfs::content_path(filename);
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
    data.video.micros_per_frame = micros_per_frame;

    data.audio.has_audio = 0;
    if (g_settings.get_sound(SOUND_EFFECTS)->enabled) {
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
    return 1;
}

static void end_video(void) {
    g_sound.use_default_music_player();
    g_sound.music_update(true);
    g_render.release_custom_texture_buffer(CUSTOM_IMAGE_VIDEO);
}

bool video_start(const char* filename) {
    data.is_playing = false;
    data.is_ended = false;

    if (load_smk(filename)) {
        g_sound.music_stop();
        g_sound.speech_stop();
        g_render.create_custom_texture(CUSTOM_IMAGE_VIDEO, data.video.width, data.video.height);
        data.buffer.pixels = g_render.get_custom_texture_buffer(CUSTOM_IMAGE_VIDEO, &data.buffer.width);
        data.is_playing = true;
        return true;
    } else
        return false;
}

void video_size(int* width, int* height) {
    *width = data.video.width;
    *height = data.video.y_scale == SMACKER_Y_SCALE_NONE ? data.video.height : 2 * data.video.height;
}

void video_init(void) {
    data.video.start_render_millis = time_get_millis();

    if (data.audio.has_audio) {
        int audio_len = smacker_get_frame_audio_size(data.s, 0);
        if (audio_len > 0) {
            g_sound.use_custom_music_player(data.audio.bitdepth, data.audio.channels, data.audio.rate, (void*)smacker_get_frame_audio(data.s, 0), audio_len);
        }
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
        data.is_playing = 0;
    }
}

void video_shutdown(void) {
    if (data.is_playing) {
        close_smk();
        data.is_playing = 0;
    }
}

static int get_next_frame(void) {
    if (!data.s) {
        return 0;
    }
    time_millis now_millis = time_get_millis();

    int frame_no = (now_millis - data.video.start_render_millis) * 1000 / data.video.micros_per_frame;
    int draw_frame = data.video.current_frame == 0;
    while (frame_no > data.video.current_frame) {
        if (smacker_next_frame(data.s) != SMACKER_FRAME_OK) {
            close_smk();
            data.is_ended = 1;
            data.is_playing = 0;
            end_video();
            return 0;
        }
        data.video.current_frame++;
        draw_frame = 1;

        if (data.audio.has_audio) {
            int audio_len = smacker_get_frame_audio_size(data.s, 0);
            if (audio_len > 0) {
                g_sound.write_custom_music_data((void*)smacker_get_frame_audio(data.s, 0), audio_len);
            }
        }
    }
    return draw_frame;
}
static void update_video_frame(void) {
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

    int s_width = screen_width();
    int s_height = screen_height();
    float scale_w = data.video.width / (float)screen_width();
    float scale_h = data.video.height / (float)screen_height();
    float scale = scale_w > scale_h ? scale_w : scale_h;

    int x = 0;
    int y = 0;
    if (scale == scale_h)
        x = (int)((s_width - data.video.width / scale) / 2 * scale);
    if (scale == scale_w)
        y = (int)((s_height - data.video.height / scale) / 2 * scale);

    g_render.draw_custom_texture(CUSTOM_IMAGE_VIDEO, x, y, scale);
}