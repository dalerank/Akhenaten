#include "music.h"

#include "city/city.h"
#include "city/city_population.h"
#include "core/game_environment.h"
#include "content/vfs.h"
#include "core/profiler.h"
#include "game/settings.h"
#include "content/dir.h"
#include "sound/sound.h"

struct music_data_t {
    int current_track;
    int next_check;
};

music_data_t g_music_data = {TRACK_NONE, 0};

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

void sound_manager_t::play_track(int track) {
    g_sound.stop_music();

    if (track <= TRACK_NONE || track >= TRACK_MAX) {
        return;
    }

    int volume = g_settings.get_sound(SOUND_MUSIC)->volume;

    volume = volume * 0.4;
    vfs::path corrected_filename = ph_mp3[track];
    if (strncmp( ph_mp3[track], vfs::content_audio, strlen(vfs::content_audio)) != 0) {
        corrected_filename = vfs::path(vfs::content_audio,  ph_mp3[track]);
    }

    corrected_filename = vfs::content_file(corrected_filename);
    g_sound.play_music(corrected_filename, volume);

    g_music_data.current_track = track;
}

void sound_manager_t::play_intro() {
    if (g_settings.get_sound(SOUND_MUSIC)->enabled) {
        play_track(TRACK_MENU);
    }
}

void sound_manager_t::play_editor() {
    if (g_settings.get_sound(SOUND_MUSIC)->enabled) {
        play_track(TRACK_CITY_1);
    }
}

void sound_manager_t::music_update(bool force) {
    OZZY_PROFILER_SECTION("Game/Sound/Music Update");
    if (g_music_data.next_check && !force) {
        --g_music_data.next_check;
        return;
    }

    if (!g_settings.get_sound(SOUND_MUSIC)->enabled) {
        return;
    }

    int track;
    int population = city_population();
    int total_enemies = g_city.figures_total_invading_enemies();

    if (total_enemies >= 32) {
        track = TRACK_COMBAT_LONG;
    } else if (total_enemies > 0) {
        track = TRACK_COMBAT_SHORT;
    } else if (population < 1000) {
        track = TRACK_CITY_1;
    } else if (population < 2000) {
        track = TRACK_CITY_2;
    } else if (population < 5000) {
        track = TRACK_CITY_3;
    } else if (population < 7000) {
        track = TRACK_CITY_4;
    } else {
        track = TRACK_CITY_5;
    }

    if (track == g_music_data.current_track) {
        return;
    }

    play_track(track);
    g_music_data.next_check = 10;
}

void sound_manager_t::on_sound_effect(event_sound_effect ev) {
    play_effect(ev.effect);
}

void sound_manager_t::on_sound_track(event_sound_track ev) {
    play_track(ev.track);
}

void sound_manager_t::music_stop() {
    g_sound.stop_music();
    g_music_data.current_track = TRACK_NONE;
    g_music_data.next_check = 0;
}
