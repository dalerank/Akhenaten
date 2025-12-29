#include "sound.h"

#include "core/log.h"
#include "game/settings.h"
#include "content/dir.h"
#include "content/vfs.h"
#include "sound/channel.h"
#include "content/mods.h"

vfs::path sound_manager_t::speech_filename(xstring filename) {
    pcstr filename_str = filename.c_str();
    vfs::path fs_path = filename_str;
    if (strncmp(filename_str, vfs::content_audio, strlen(vfs::content_audio)) != 0) {
        fs_path = vfs::path(vfs::content_audio, filename_str);
    }

    return fs_path.resolve();
}

bool sound_manager_t::speech_file_exist(xstring filename, vfs::path& fs_path) {
    if (!g_settings.get_sound(SOUND_SPEECH)->enabled) {
        return false;
    }

    pcstr filename_str = filename.empty() ? "" : filename.c_str();
    vfs::path rel_path = filename_str;
    if (strncmp(filename_str, vfs::content_audio, strlen(vfs::content_audio)) != 0) {
        rel_path = vfs::path(vfs::content_audio, filename_str);
    }

    vfs::path file_path = mods_exist_audio(rel_path);
    if (!file_path.empty()) {
        fs_path = file_path.c_str();
        return true;
    }

    fs_path = vfs::path::resolve(rel_path);
    if (fs_path.empty()) {
        return false;
    }

    return true;
}

bool sound_manager_t::speech_play_file(xstring filename, int volume) {
    vfs::path fs_path;
    if (!speech_file_exist(filename, fs_path)) {    
        return false;
    }

    stop_channel(SOUND_CHANNEL_SPEECH);
    play_file_on_channel(fs_path, SOUND_CHANNEL_SPEECH, g_settings.get_sound(SOUND_SPEECH)->volume);
    return true;
}

void sound_manager_t::speech_stop() {
    stop_channel(SOUND_CHANNEL_SPEECH);
}
