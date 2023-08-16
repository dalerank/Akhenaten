#include "music.h"

#include "city/figures.h"
#include "city/population.h"
#include "core/game_environment.h"
#include "core/profiler.h"
#include "game/settings.h"
#include "io/dir.h"
#include "sound/device.h"

enum e_track {
    TRACK_NONE,
    TRACK_MENU,
    TRACK_COMBAT_SHORT,
    TRACK_COMBAT_LONG,
    TRACK_CITY_1,
    TRACK_CITY_2,
    TRACK_CITY_3,
    TRACK_CITY_4,
    TRACK_CITY_5,
    TRACK_CITY_6,
    TRACK_CITY_7,
    TRACK_CITY_8,
    TRACK_CITY_9,
    TRACK_CITY_10,
    TRACK_CITY_11,
    TRACK_CITY_12,
    TRACK_CITY_13,
    TRACK_CITY_14,
    TRACK_CITY_15,
    TRACK_CITY_16,
    TRACK_CITY_17,
    TRACK_CITY_18,
    TRACK_CITY_19,
    TRACK_CITY_20,
    TRACK_CITY_21,
    TRACK_CITY_22,
    TRACK_CITY_23,
    TRACK_CITY_24,
    TRACK_CITY_25,
    TRACK_CITY_26,
    TRACK_CITY_27,
    TRACK_CITY_28,
    TRACK_CITY_29,
    TRACK_CITY_30,
    TRACK_CITY_31,
    TRACK_CITY_32,
    TRACK_CITY_33,
    TRACK_CITY_34,
    TRACK_CITY_35,
    TRACK_CITY_36,
    TRACK_CITY_37,
    TRACK_CITY_38,
    TRACK_CITY_39,
    TRACK_CITY_40,
    TRACK_MAX
};

static struct {
    int current_track;
    int next_check;
} data = {TRACK_NONE, 0};

static const char c3_wav[][32] = {"",
                                  "wavs/setup.wav",
                                  "wavs/Combat_Short.wav",
                                  "wavs/Combat_Long.wav",
                                  "wavs/ROME1.WAV",
                                  "wavs/ROME2.WAV",
                                  "wavs/ROME3.WAV",
                                  "wavs/ROME4.WAV",
                                  "wavs/ROME5.WAV"};

static const char c3_mp3[][32] = {"",
                                  "mp3/setup.mp3",
                                  "mp3/Combat_Short.mp3",
                                  "mp3/Combat_Long.mp3",
                                  "mp3/ROME1.mp3",
                                  "mp3/ROME2.mp3",
                                  "mp3/ROME3.mp3",
                                  "mp3/ROME4.mp3",
                                  "mp3/ROME5.mp3"};

static const char ph_mp3[][32] = {
  "",
  "AUDIO/Music/Setup.mp3",
  "AUDIO/Music/Battle.mp3",
  "AUDIO/Music/Battle.mp3",
  "AUDIO/Music/Agbj.mp3",   // M
  "AUDIO/Music/SPS.mp3",    // M
  "AUDIO/Music/sthA.mp3",   // M
  "AUDIO/Music/mAa-jb.mp3", // M

  "AUDIO/Music/Hapj-aA.mp3", // A
  "AUDIO/Music/SSTJ.mp3",    // A
  "AUDIO/Music/DUST.mp3",    // A

  "AUDIO/Music/Smr.mp3", // M

  "AUDIO/Music/ADVENT.mp3", // A-M
  "AUDIO/Music/ANKH.mp3",   // A
  "AUDIO/Music/jAkb.mp3",   // A

  "AUDIO/Music/rwD.mp3",       // M
  "AUDIO/Music/M-TWR.mp3",     // M
  "AUDIO/Music/JA.mp3",        // M
  "AUDIO/Music/jrj-Hb-sd.mp3", // M

  "AUDIO/Music/M-SRF.mp3",    // A
  "AUDIO/Music/WATJ.mp3",     // A
  "AUDIO/Music/WAJ.mp3",      // A
  "AUDIO/Music/OFFERING.mp3", // A
  "AUDIO/Music/RAIN.mp3",     // A

  "AUDIO/Music/KHU.mp3",    // M
  "AUDIO/Music/KHET.mp3",   // M
  "AUDIO/Music/REKHIT.mp3", // M

  "AUDIO/Music/AMBER.mp3",    // A
  "AUDIO/Music/Dd-m-ann.mp3", // A

  "AUDIO/Music/Daq.mp3", // M

  "AUDIO/Music/rwDt.mp3",    // A
  "AUDIO/Music/LONGING.mp3", // A

  "AUDIO/Music/BENNU.mp3",   // M
  "AUDIO/Music/NEFER.mp3",   // M
  "AUDIO/Music/AMAKH.mp3",   // M
  "AUDIO/Music/Geb.mp3",     // M
  "AUDIO/Music/Khepera.mp3", // M
  "AUDIO/Music/Isis.mp3",    // M
  "AUDIO/Music/Anquet.mp3",  // M
  "AUDIO/Music/Sekhmet.mp3", // M
  "AUDIO/Music/Ra.mp3"       // M
};

static void play_track(int track) {
    sound_device_stop_music();
    if (track <= TRACK_NONE || track >= TRACK_MAX)
        return;
    int volume = setting_sound(SOUND_MUSIC)->volume;

    switch (GAME_ENV) {
        const char* mp3_track;
    case ENGINE_ENV_PHARAOH:
        volume = volume * 0.4;
        sound_device_play_music(dir_get_file(ph_mp3[track], NOT_LOCALIZED), volume);
        break;
    }
    data.current_track = track;
}

void sound_music_set_volume(int percentage) {
    sound_device_set_music_volume(percentage);
}
void sound_music_play_intro(void) {
    if (setting_sound(SOUND_MUSIC)->enabled)
        play_track(TRACK_MENU);
}
void sound_music_play_editor(void) {
    if (setting_sound(SOUND_MUSIC)->enabled)
        play_track(TRACK_CITY_1);
}
void sound_music_update(bool force) {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Music Update");
    if (data.next_check && !force) {
        --data.next_check;
        return;
    }
    if (!setting_sound(SOUND_MUSIC)->enabled)
        return;
    int track;
    int population = city_population();
    int total_enemies = city_figures_total_invading_enemies();
    if (total_enemies >= 32)
        track = TRACK_COMBAT_LONG;
    else if (total_enemies > 0)
        track = TRACK_COMBAT_SHORT;
    else if (population < 1000)
        track = TRACK_CITY_1;
    else if (population < 2000)
        track = TRACK_CITY_2;
    else if (population < 5000)
        track = TRACK_CITY_3;
    else if (population < 7000)
        track = TRACK_CITY_4;
    else {
        track = TRACK_CITY_5;
    }

    if (track == data.current_track)
        return;

    play_track(track);
    data.next_check = 10;
}
void sound_music_stop(void) {
    sound_device_stop_music();
    data.current_track = TRACK_NONE;
    data.next_check = 0;
}
