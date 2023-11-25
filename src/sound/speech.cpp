#include "speech.h"

#include "core/log.h"
#include "game/settings.h"
#include "content/dir.h"
#include "content/vfs.h"
#include "sound/channel.h"
#include "sound/device.h"

void sound_speech_set_volume(int percentage) {
    sound_device_set_channel_volume(SOUND_CHANNEL_SPEECH, percentage);
}

vfs::path sound_speed_filename(const char *filename) {
    vfs::path fs_path = filename;
    if (strncmp(filename, vfs::content_audio, strlen(vfs::content_audio)) != 0) {
        fs_path = vfs::path(vfs::content_audio, filename);
    }

    return vfs::content_file(fs_path);
}

bool sound_speech_file_exist(const char *filename) {
    return (!sound_speed_filename(filename).empty());
}

void sound_speech_play_file(const char* filename, int volume) {
    if (!g_settings.get_sound(SOUND_SPEECH)->enabled) {
        return;
    }

    sound_device_stop_channel(SOUND_CHANNEL_SPEECH);

    vfs::path fs_path = filename;
    if (strncmp(filename, vfs::content_audio, strlen(vfs::content_audio)) != 0) {
        fs_path = vfs::path(vfs::content_audio, filename);
    }

    fs_path = vfs::content_file(fs_path);

    if (fs_path.empty()) {
        logs::error("Cant open audio file %s", filename);
        return;
    }

    sound_device_play_file_on_channel(fs_path, SOUND_CHANNEL_SPEECH, g_settings.get_sound(SOUND_SPEECH)->volume);
}

void sound_speech_stop(void) {
    sound_device_stop_channel(SOUND_CHANNEL_SPEECH);
}
