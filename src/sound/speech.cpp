#include "speech.h"

#include "core/log.h"
#include "game/settings.h"
#include "content/dir.h"
#include "sound/channel.h"
#include "sound/device.h"

void sound_speech_set_volume(int percentage) {
    sound_device_set_channel_volume(SOUND_CHANNEL_SPEECH, percentage);
}

void sound_speech_play_file(const char* filename) {
    if (!setting_sound(SOUND_SPEECH)->enabled) {
        return;
    }

    sound_device_stop_channel(SOUND_CHANNEL_SPEECH);

    const char *folder_audio = "AUDIO/";
    bstring256 corrected_filename = filename;
    if (strncmp(filename, folder_audio, strlen(folder_audio)) != 0) {
        corrected_filename = bstring256(folder_audio, filename);
    }

    corrected_filename = vfs::dir_get_file(corrected_filename);

    if (corrected_filename.empty()) {
        logs::error("Cant open audio file %s", filename);
        return;
    }

    sound_device_play_file_on_channel(corrected_filename, SOUND_CHANNEL_SPEECH, setting_sound(SOUND_SPEECH)->volume);
}

void sound_speech_stop(void) {
    sound_device_stop_channel(SOUND_CHANNEL_SPEECH);
}
