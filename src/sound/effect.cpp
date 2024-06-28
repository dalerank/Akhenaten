#include "effect.h"

#include "game/settings.h"
#include "sound/channel.h"
#include "sound/sound.h"

void sound_effect_set_volume(int percentage) {
    for (int i = SOUND_CHANNEL_EFFECTS_MIN; i <= SOUND_CHANNEL_EFFECTS_MAX; i++) {
        g_sound.set_channel_volume(i, percentage);
    }
}

void sound_effect_play(int effect) {
    if (!g_settings.get_sound(SOUND_EFFECTS)->enabled)
        return;

    if (g_sound.is_channel_playing(effect))
        return;

    g_sound.play_channel(effect, g_settings.get_sound(SOUND_EFFECTS)->volume);
}
