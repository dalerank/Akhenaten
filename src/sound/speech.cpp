#include "sound.h"

#include "core/archive.h"
#include "core/bstring.h"
#include "core/log.h"
#include "game/game_config.h"
#include "content/dir.h"
#include "content/mods.h"
#include "content/vfs.h"
#include "sound/channel.h"

#include <cctype>
#include <cstring>

ANK_CONFIG_STRUCT(sound_manager_t::speech_t, dirs, walker_dir)

ANK_DECLARE_CONFIG_ITERATOR(config_load_speech);
void config_load_speech() {
    call_unload_if_exists(g_sound.speech);
    const bool ok = g_config_arch.r("speech", g_sound.speech);
    call_init_if_exists(g_sound.speech);
    verify_no_crash_var(ok, "Variable not exist in config: %s", "speech");
}

bool sound_manager_t::speech_ieq_prefix(pcstr path, pcstr prefix) {
    for (; *prefix; ++path, ++prefix) {
        if (!*path) {
            return false;
        }
        if (std::tolower(static_cast<unsigned char>(*path)) != std::tolower(static_cast<unsigned char>(*prefix))) {
            return false;
        }
    }
    return true;
}

vfs::path sound_manager_t::speech_normalize_rel(pcstr filename) const {
    vfs::path rel = filename;
    rel.replace('\\', '/');

    pcstr p = rel.c_str();
    if (speech_ieq_prefix(p, vfs::content_audio)) {
        p += strlen(vfs::content_audio);
        while (*p == '/') {
            ++p;
        }
        rel = p;
    }

    for (const xstring &dir : speech.dirs) {
        if (dir.empty()) {
            continue;
        }
        if (speech_ieq_prefix(rel.c_str(), dir.c_str())) {
            return rel;
        }
    }
    return {};
}

vfs::path sound_manager_t::speech_filename(xstring filename) {
    pcstr filename_str = filename.c_str();
    vfs::path fs_path = filename_str;
    if (strncmp(filename_str, vfs::content_audio, strlen(vfs::content_audio)) != 0) {
        fs_path = vfs::path(vfs::content_audio, filename_str);
    }

    return fs_path.resolve();
}

bool sound_manager_t::speech_try_rel(pcstr rel, vfs::path &fs_path) {
    if (!rel || !*rel) {
        return false;
    }

    vfs::path with_audio = rel;
    if (strncmp(rel, vfs::content_audio, strlen(vfs::content_audio)) != 0) {
        with_audio = vfs::path(vfs::content_audio, rel);
    }

    vfs::path from_mods = mods_exist_audio(with_audio);
    if (!from_mods.empty()) {
        fs_path = from_mods;
        return true;
    }

    fs_path = vfs::path::resolve(with_audio);
    return !fs_path.empty() && vfs::file_exists(fs_path);
}

bool sound_manager_t::speech_file_exist(xstring filename, vfs::path &fs_path) {
    if (!game_features::gameopt_sound_speech_enabled) {
        return false;
    }

    pcstr filename_str = filename.empty() ? "" : filename.c_str();
    if (!filename_str || !*filename_str) {
        return false;
    }

    const vfs::path known = speech_normalize_rel(filename_str);
    if (!known.empty()) {
        return speech_try_rel(known.c_str(), fs_path);
    }

    const vfs::path base = vfs::path(filename_str).basename();
    if (base.empty() || speech.walker_dir.empty()) {
        return false;
    }

    bstring256 rel(speech.walker_dir.c_str(), base.c_str());
    return speech_try_rel(rel.c_str(), fs_path);
}

bool sound_manager_t::speech_play_file(xstring filename, int volume) {
    vfs::path fs_path;
    if (!speech_file_exist(filename, fs_path)) {
        logs::warn("Sound: speech file not found '%s'", filename.empty() ? "" : filename.c_str());
        return false;
    }

    stop_channel(SOUND_CHANNEL_SPEECH);
    return play_file_on_channel(fs_path, SOUND_CHANNEL_SPEECH, game_features::gameopt_sound_speech_volume.to_int());
}

void sound_manager_t::speech_stop() {
    stop_channel(SOUND_CHANNEL_SPEECH);
}
