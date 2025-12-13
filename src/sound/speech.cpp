#include "sound.h"

#include "core/log.h"
#include "game/settings.h"
#include "content/dir.h"
#include "content/vfs.h"
#include "sound/channel.h"
#include "sound/sound.h"

vfs::path sound_manager_t::speech_filename(xstring filename) {
    pcstr filename_str = filename.c_str();
    vfs::path fs_path = filename_str;
    if (strncmp(filename_str, vfs::content_audio, strlen(vfs::content_audio)) != 0) {
        fs_path = vfs::path(vfs::content_audio, filename_str);
    }

    return fs_path.resolve();
}

bool sound_manager_t::speech_file_exist(xstring filename) {
    return (!speech_filename(filename).empty());
}

void sound_manager_t::speech_play_file(xstring filename, int volume) {
    if (!g_settings.get_sound(SOUND_SPEECH)->enabled) {
        return;
    }

    stop_channel(SOUND_CHANNEL_SPEECH);

    pcstr filename_str = filename.empty() ? "" : filename.c_str();
    vfs::path fs_path = filename_str;
    if (strncmp(filename_str, vfs::content_audio, strlen(vfs::content_audio)) != 0) {
        fs_path = vfs::path(vfs::content_audio, filename_str);
    }

    fs_path = vfs::path::resolve(fs_path);
    if (fs_path.empty()) {
        logs::error("Cant open audio file %s", filename.c_str());
        return;
    }

    play_file_on_channel(fs_path, SOUND_CHANNEL_SPEECH, g_settings.get_sound(SOUND_SPEECH)->volume);
}

void sound_manager_t::speech_stop() {
    stop_channel(SOUND_CHANNEL_SPEECH);
}
