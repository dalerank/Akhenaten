#include "sound/sound_speech.h"
#include "sound/sound.h"
#include "core/xvalue.h"

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

ANK_CONFIG_STRUCT(sound_speech_t, dirs, walker_dir)

sound_speech_t& sound_speech() {
    return xvalue<sound_speech_t>::ref();
}

ANK_DECLARE_CONFIG_ITERATOR(config_load_speech);
void config_load_speech() {
    call_unload_if_exists(sound_speech());
    const bool ok = g_config_arch.r("speech", sound_speech());
    call_init_if_exists(sound_speech());
    verify_no_crash_var(ok, "Variable not exist in config: %s", "speech");
}

bool sound_speech_t::ieq_prefix(pcstr path, pcstr prefix) {
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

vfs::path sound_speech_t::normalize_rel(pcstr filename) const {
    vfs::path rel = filename;
    rel.replace('\\', '/');

    pcstr p = rel.c_str();
    if (ieq_prefix(p, vfs::content_audio)) {
        p += strlen(vfs::content_audio);
        while (*p == '/') {
            ++p;
        }
        rel = p;
    }

    for (const xstring& dir : dirs) {
        if (dir.empty()) {
            continue;
        }
        if (ieq_prefix(rel.c_str(), dir.c_str())) {
            return rel;
        }
    }
    return {};
}

bool sound_speech_t::try_rel(pcstr rel, vfs::path& fs_path) {
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

bool sound_speech_t::file_exist(xstring filename, vfs::path& fs_path) {
    if (!game_features::gameopt_sound_speech_enabled) {
        return false;
    }

    pcstr filename_str = filename.empty() ? "" : filename.c_str();
    if (!filename_str || !*filename_str) {
        return false;
    }

    const vfs::path known = normalize_rel(filename_str);
    if (!known.empty()) {
        return try_rel(known.c_str(), fs_path);
    }

    const vfs::path base = vfs::path(filename_str).basename();
    if (base.empty() || walker_dir.empty()) {
        return false;
    }

    bstring256 rel(walker_dir.c_str(), base.c_str());
    return try_rel(rel.c_str(), fs_path);
}

bool sound_speech_t::play_file(xstring filename) {
    // Without a mixer (--nosound) or data (--no-resource) the file probe is wasted and only spams warnings.
    if (!sound_manager().is_initialized() || !sound_manager().data_available()) {
        return false;
    }

    vfs::path fs_path;
    if (!file_exist(filename, fs_path)) {
        logs::warn("Sound: speech file not found '%s'", filename.empty() ? "" : filename.c_str());
        return false;
    }

    return sound_manager().play_file_on_channel(fs_path, SOUND_CHANNEL_SPEECH,
      game_features::gameopt_sound_speech_volume.to_int());
}

void sound_speech_t::stop() {
    sound_manager().stop_channel(SOUND_CHANNEL_SPEECH);
}
