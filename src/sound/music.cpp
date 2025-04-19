#include "music.h"

#include "city/city.h"
#include "city/city_population.h"
#include "core/game_environment.h"
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
        xstring name;
        vfs::path file;
    };

    struct pop_soundtrack {
        int pop;
        xstring track;
    };

    svector<soundtrack, 64> tracks;
    svector<pop_soundtrack, 16> pop_tracks;
};

music_data_t g_music;

ANK_REGISTER_CONFIG_ITERATOR(config_load_soundtracks);
void config_load_soundtracks() {
    g_music.tracks.clear();
    g_config_arch.r_objects("soundtracks", [] (pcstr key, archive arch) {
        auto &track = g_music.tracks.emplace_back();
        track.name = key;
        track.file = arch.r_string("file");
    });

    g_config_arch.r_section("music", [] (archive arch) {
        g_music.menu_track = arch.r_string("menu_track");
        g_music.combat_long = arch.r_string("combat_long");
        g_music.combat_short = arch.r_string("combat_short");
    });

    g_music.pop_tracks.clear();
    g_config_arch.r_objects("music_populations", [] (pcstr key, archive arch) {
        auto &track = g_music.pop_tracks.emplace_back();
        track.pop = arch.r_int("pop");
        track.track = arch.r_string("track");
    });
}

declare_console_command_p(playtrack) {
    std::string args;
    is >> args;
    g_sound.play_track(args.c_str());
}

void sound_manager_t::play_track(const xstring track) {
    stop_music();

    auto it = std::find_if(g_music.tracks.begin(), g_music.tracks.end(), [track] (auto &t) { return t.name == track; });

    if (it == g_music.tracks.end()) {
        return;
    }

    int volume = g_settings.get_sound(SOUND_MUSIC)->volume;

    volume = volume * 0.4;
    vfs::path corrected_filename = it->file;
    if (strncmp(it->file.c_str(), vfs::content_audio, strlen(vfs::content_audio)) != 0) {
        corrected_filename = vfs::path(vfs::content_audio, it->file);
    }

    corrected_filename = vfs::content_file(corrected_filename);
    play_music(corrected_filename, volume);

    g_music.current_track = track;
}

void sound_manager_t::play_intro() {
    if (g_settings.get_sound(SOUND_MUSIC)->enabled) {
        play_track(g_music.menu_track);
    }
}

void sound_manager_t::play_editor() {
    if (g_settings.get_sound(SOUND_MUSIC)->enabled) {
        play_track("city_0");
    }
}

void sound_manager_t::music_update(bool force) {
    OZZY_PROFILER_SECTION("Game/Sound/Music Update");
    if (g_music.next_check && !force) {
        --g_music.next_check;
        return;
    }

    if (!g_settings.get_sound(SOUND_MUSIC)->enabled) {
        return;
    }

    xstring track;
    int total_enemies = g_city.figures_total_invading_enemies();

    if (total_enemies >= 32) {
        track = g_music.combat_long;
    } else if (total_enemies > 0) {
        track = g_music.combat_short;
    } else {
        track = g_music.pop_tracks.front().track;
        const int city_population = g_city.population.current;

        for (const auto &p : g_music.pop_tracks) {
            if (p.pop > city_population) {
                break;
            }
            track = p.track;
        }
    }

    if (track == g_music.current_track) {
        return;
    }

    play_track(track);
    g_music.next_check = 10;
}

void sound_manager_t::on_sound_effect(event_sound_effect ev) {
    play_effect(ev.effect);
}

void sound_manager_t::on_sound_track(event_sound_track ev) {
    play_track(ev.track);
}

void sound_manager_t::music_stop() {
    stop_music();
    g_music.current_track = "";
    g_music.next_check = 0;
}
