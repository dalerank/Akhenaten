#include "music.h"

#include "city/city.h"
#include "city/city_population.h"
#include "content/vfs.h"
#include "core/profiler.h"
#include "game/settings.h"
#include "content/dir.h"
#include "sound/sound.h"
#include "js/js_game.h"

#include "dev/debug.h"
#include <iostream>

struct music_data_t {
    int next_check = 0;

    xstring current_track;
    xstring menu_track;
    xstring combat_long;
    xstring combat_short;

    struct soundtrack {
        xstring key;
        xstring file;
    };

    struct pop_soundtrack {
        int pop;
        xstring track;
    };

    svector<soundtrack, 64> soundtracks;
    svector<pop_soundtrack, 16> music_populations;
};
ANK_CONFIG_STRUCT(music_data_t::soundtrack, key, file)
ANK_CONFIG_STRUCT(music_data_t::pop_soundtrack, pop, track)
ANK_CONFIG_STRUCT(music_data_t, menu_track, combat_long, combat_short, soundtracks, music_populations)

music_data_t ANK_VARIABLE(music);

declare_console_command_p(playtrack) {
    std::string args;
    is >> args;
    g_sound.play_track(args.c_str());
}

void sound_manager_t::play_track(const xstring track) {
    stop_music();

    auto it = std::find_if(music.soundtracks.begin(), music.soundtracks.end(), [track] (auto &t) { return t.key == track; });

    if (it == music.soundtracks.end()) {
        return;
    }

    int volume = g_settings.get_sound(SOUND_MUSIC)->volume;

    volume = volume * 0.4;
    vfs::path corrected_filename = it->file.c_str();
    if (strncmp(it->file.c_str(), vfs::content_audio, strlen(vfs::content_audio)) != 0) {
        corrected_filename = vfs::path(vfs::content_audio, it->file.c_str());
    }

    play_music(corrected_filename.resolve(), volume);

    music.current_track = track;
}

void sound_manager_t::play_intro() {
    if (g_settings.get_sound(SOUND_MUSIC)->enabled) {
        play_track(music.menu_track);
    }
}

void sound_manager_t::play_editor() {
    if (g_settings.get_sound(SOUND_MUSIC)->enabled) {
        play_track("city_0");
    }
}

void sound_manager_t::music_update(bool force) {
    OZZY_PROFILER_FUNCTION();
    if (music.next_check && !force) {
        --music.next_check;
        return;
    }

    if (!g_settings.get_sound(SOUND_MUSIC)->enabled) {
        return;
    }

    xstring track;
    int total_enemies = g_city.figures.total_invading_enemies();

    if (total_enemies >= 32) {
        track = music.combat_long;
    } else if (total_enemies > 0) {
        track = music.combat_short;
    } else {
        track = music.music_populations.front().track;
        const int city_population = g_city.population.current;

        for (const auto &p : music.music_populations) {
            if (p.pop > city_population) {
                break;
            }
            track = p.track;
        }
    }

    if (track == music.current_track) {
        return;
    }

    play_track(track);
    music.next_check = 10;
}

void sound_manager_t::on_sound_effect(event_sound_effect ev) {
    play_effect(ev.effect);
}

void sound_manager_t::on_sound_track(event_sound_track ev) {
    play_track(ev.track);
}

void sound_manager_t::music_stop() {
    stop_music();
    music.current_track = "";
    music.next_check = 0;
}
