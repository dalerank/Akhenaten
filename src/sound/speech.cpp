#include "sound.h"

#include "core/log.h"
#include "game/settings.h"
#include "content/dir.h"
#include "content/vfs.h"
#include "sound/channel.h"
#include "sound/sound.h"

void sound_manager_t::speech_set_volume(int percentage) {
    set_channel_volume(SOUND_CHANNEL_SPEECH, percentage);
}

vfs::path sound_manager_t::speech_filename(pcstr filename) {
    vfs::path fs_path = filename;
    if (strncmp(filename, vfs::content_audio, strlen(vfs::content_audio)) != 0) {
        fs_path = vfs::path(vfs::content_audio, filename);
    }

    return vfs::content_file(fs_path);
}

bool sound_manager_t::speech_file_exist(pcstr filename) {
    return (!speech_filename(filename).empty());
}

void sound_manager_t::speech_play_file(pcstr filename, int volume) {
    if (!g_settings.get_sound(SOUND_SPEECH)->enabled) {
        return;
    }

    stop_channel(SOUND_CHANNEL_SPEECH);

    vfs::path fs_path = filename;
    if (strncmp(filename, vfs::content_audio, strlen(vfs::content_audio)) != 0) {
        fs_path = vfs::path(vfs::content_audio, filename);
    }

    fs_path = vfs::content_file(fs_path);
    if (fs_path.empty()) {
        logs::error("Cant open audio file %s", filename);
        return;
    }

    play_file_on_channel(fs_path, SOUND_CHANNEL_SPEECH, g_settings.get_sound(SOUND_SPEECH)->volume);
}

void sound_manager_t::speech_stop() {
    stop_channel(SOUND_CHANNEL_SPEECH);
}
