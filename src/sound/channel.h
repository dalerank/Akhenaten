#pragma once

enum e_sound_channel {
    SOUND_CHANNEL_SPEECH = 0,

    SOUND_MUSIC_AMBIENT = 1,

    // user interface effects
    SOUND_CHANNEL_EFFECTS_MIN = 2,
    SOUND_CHANNEL_EFFECTS_MAX = 44,

    // city sounds (from buildings)
    SOUND_CHANNEL_CITY_MIN = 45,
    SOUND_CHANNEL_CITY_MAX = 148,

    SOUND_CHANNEL_MAX = SOUND_CHANNEL_CITY_MAX + 1
};
