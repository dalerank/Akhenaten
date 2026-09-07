#include "music.h"

#include "city/city.h"
#include "city/city_population.h"
#include "content/vfs.h"
#include "core/profiler.h"
#include "game/game_config.h"
#include "core/calc.h"
#include "core/random.h"
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
        svector<xstring, 8> tracks;
    };

    svector<soundtrack, 64> soundtracks;
    svector<pop_soundtrack, 16> music_populations;
};
ANK_CONFIG_STRUCT(music_data_t::soundtrack, key, file)
ANK_CONFIG_STRUCT(music_data_t::pop_soundtrack, pop, tracks)
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

    int volume = calc_bound(game_features::gameopt_sound_music_volume.to_int(), 0, 100);

    volume = volume * 0.4;
    vfs::path corrected_filename = it->file.c_str();
    if (strncmp(it->file.c_str(), vfs::content_audio, strlen(vfs::content_audio)) != 0) {
        corrected_filename = vfs::path(vfs::content_audio, it->file.c_str());
    }

    play_music(corrected_filename.resolve(), volume);

    music.current_track = track;
}

void sound_manager_t::play_intro() {
    if (!!game_features::gameopt_sound_music_enabled) {
        play_track(music.menu_track);
    }
}

void sound_manager_t::play_editor() {
    if (!!game_features::gameopt_sound_music_enabled) {
        play_track("city_0");
    }
}

static const svector<xstring, 8>& music_city_tracks(int population) {
    const music_data_t::pop_soundtrack* tier = &music.music_populations.front();

    for (const auto& p : music.music_populations) {
        if (p.pop > population) {
            break;
        }
        tier = &p;
    }

    return tier->tracks;
}

static xstring music_random_city_track(const svector<xstring, 8>& pool, const xstring& exclude) {
    svector<xstring, 8> candidates;
    for (const auto& t : pool) {
        if (t != exclude) {
            candidates.push_back(t);
        }
    }

    if (candidates.empty()) {
        return pool.empty() ? xstring() : pool.front();
    }

    return candidates[random_int_between(0, (int)candidates.size())];
}

void sound_manager_t::music_update(bool force) {
    OZZY_PROFILER_FUNCTION();
    if (music.next_check && !force) {
        --music.next_check;
        return;
    }

    if (!game_features::gameopt_sound_music_enabled) {
        return;
    }

    xstring track;
    int total_enemies = g_city.figures.total_invading_enemies();

    if (total_enemies >= 32) {
        track = music.combat_long;
    } else if (total_enemies > 0) {
        track = music.combat_short;
    } else {
        const auto& pool = music_city_tracks(g_city.population.current);
        const bool current_in_pool = std::find(pool.begin(), pool.end(), music.current_track) != pool.end();

        // Regular updates keep the current track while the city stays in the same
        // population tier. A forced update (mission start, save load) re-rolls a
        // different random track from the tier like the original game does.
        if (!force && current_in_pool) {
            return;
        }

        track = music_random_city_track(pool, music.current_track);
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

const xstring& sound_manager_t::music_current_track() const {
    return music.current_track;
}

void sound_manager_t::music_stop() {
    stop_music();
    music.current_track = "";
    music.next_check = 0;
}
