#include "system.h"

#include "content/dir.h"
#include "core/game_environment.h"
#include "core/log.h"
#include "game/settings.h"
#include "sound/channel.h"
#include "sound/city.h"
#include "sound/device.h"
#include "sound/effect.h"
#include "sound/music.h"
#include "sound/speech.h"
#include "js/js_game.h"

#include <string.h>

static vfs::path channel_filenames[SOUND_CHANNEL_MAX] = {};

ANK_REGISTER_CONFIG_ITERATOR(config_load_city_sounds);
void config_load_city_sounds(archive arch) {
    g_config_arch.r_array("city_sounds", [] (archive arch) {
        const int channel = arch.read_integer("c");
        const char *path = arch.read_string("p");
        sound_system_update_channel(channel, path);
    });
}

void sound_system_update_channel(int channel, vfs::path filename) {
    if (filename.empty()) {
        return;
    }

    channel_filenames[channel] = filename;
    vfs::path &original = channel_filenames[channel];
    vfs::path audio_path("AUDIO/", channel_filenames[channel]);

    if (!vfs::file_exists(audio_path)) {
        logs::info("Sound: cant find audio %s", audio_path.c_str());
        channel_filenames[channel].clear();
    } else {
        original = vfs::content_path(audio_path);
        sound_device_init_channel(channel, original);
    }
}

void sound_system_init(void) {
    sound_device_open();
    sound_device_init_channels(channel_filenames);
    sound_device_load_formats();

    sound_city_set_volume(g_settings.get_sound(SOUND_CITY)->volume);
    sound_effect_set_volume(g_settings.get_sound(SOUND_EFFECTS)->volume);
    sound_music_set_volume(g_settings.get_sound(SOUND_MUSIC)->volume);
    sound_speech_set_volume(g_settings.get_sound(SOUND_SPEECH)->volume);
}

void sound_system_shutdown(void) {
    sound_device_close();

    // It is counter-intuitive that we must do this after sound_device_close, however it unloads shared libraries
    // which might be required both for sound_device_close and by other threads fetching new audio chunks until
    // sound_device_close is called. It is also surprising that we can (and must) call Mix_Quit after Mix_CloseAudio,
    // even though Mix_CloseAudio's docs say that afterwards "the SDL_mixer functions should not be used".
    sound_device_unload_formats();
}
