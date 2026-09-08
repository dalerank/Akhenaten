#include "music.h"

#include "city/city.h"
#include "city/city_population.h"
#include "content/vfs.h"
#include "core/profiler.h"
#include "game/game_config.h"
#include "core/calc.h"
#include "core/buffer.h"
#include "core/random.h"
#include "core/system_time.h"
#include "content/dir.h"
#include "io/io.h"
#include "scenario/scenario.h"
#include "sound/sound.h"
#include "js/js_game.h"

#include "dev/debug.h"
#include <iostream>
#include <string_view>
#include <vector>

struct music_data_t {
    int next_check = 0;

    xstring current_track;
    xstring menu_track;
    xstring combat_long;
    xstring combat_short;

    // Vanilla playlist (music.txt in the game folder) and the delay used when a
    // track comes from the population pools instead.
    xstring playlist_file;
    int post_tune_delay_sec = 20;

    struct soundtrack {
        xstring key;
        xstring file;
    };

    struct pop_soundtrack {
        int pop;
        svector<xstring, 8> tracks;
    };

    // One line of music.txt: "<file> <M|A> <mission> <post-tune delay sec> <min pop> <max pop>".
    // M tracks are the mission's main tunes and play in file order, A tracks are
    // alternates that fill the gaps between them.
    struct playlist_rule {
        xstring key;
        bool main;
        int mission;
        int delay_sec;
        int min_pop;
        int max_pop;
    };

    svector<soundtrack, 64> soundtracks;
    svector<pop_soundtrack, 16> music_populations;

    std::vector<playlist_rule> playlist;
    bool playlist_loaded = false;
    xstring last_main; // last M track played, so the next one continues the sequence

    // City tracks play once; after they end the player waits the post-tune
    // delay and then starts the next one.
    bool track_once = false;
    time_millis finished_at = 0;
    int post_delay_ms = 0;
};
ANK_CONFIG_STRUCT(music_data_t::soundtrack, key, file)
ANK_CONFIG_STRUCT(music_data_t::pop_soundtrack, pop, tracks)
ANK_CONFIG_STRUCT(music_data_t, menu_track, combat_long, combat_short, playlist_file, post_tune_delay_sec, soundtracks,
  music_populations)

music_data_t ANK_VARIABLE(music);

struct music_pick {
    xstring key;
    int delay_sec = 0;
};

declare_console_command_p(playtrack) {
    std::string args;
    is >> args;
    g_sound.play_track(args.c_str());
}

void sound_manager_t::play_track(const xstring track, bool loop) {
    stop_music();
    music.track_once = false;
    music.finished_at = 0;

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

    const bool played = play_music(corrected_filename.resolve(), volume, loop);

    music.current_track = track;
    music.track_once = played && !loop;
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

static std::string_view music_file_basename(std::string_view file) {
    const size_t slash = file.find_last_of("/\\");
    return slash == std::string_view::npos ? file : file.substr(slash + 1);
}

static bool music_iequals(std::string_view a, std::string_view b) {
    if (a.size() != b.size()) {
        return false;
    }

    for (size_t i = 0; i < a.size(); ++i) {
        if (std::tolower((unsigned char)a[i]) != std::tolower((unsigned char)b[i])) {
            return false;
        }
    }

    return true;
}

static xstring music_track_key_for_file(std::string_view file) {
    const std::string_view name = music_file_basename(file);
    for (const auto& t : music.soundtracks) {
        if (music_iequals(music_file_basename(t.file.c_str()), name)) {
            return t.key;
        }
    }

    return xstring();
}

static std::string_view music_trim(std::string_view s) {
    while (!s.empty() && std::isspace((unsigned char)s.front())) {
        s.remove_prefix(1);
    }
    while (!s.empty() && std::isspace((unsigned char)s.back())) {
        s.remove_suffix(1);
    }
    return s;
}

int sound_manager_t::music_load_playlist_text(std::string_view text) {
    music.playlist.clear();
    music.playlist_loaded = true;

    while (!text.empty()) {
        const size_t eol = text.find('\n');
        std::string_view line = text.substr(0, eol);
        text = (eol == std::string_view::npos) ? std::string_view() : text.substr(eol + 1);

        line = music_trim(line);
        if (line.empty() || line.front() == ';') {
            continue;
        }

        // "AMBIENT" lines mark a stretch of city ambience after the previous tune.
        // The city sound channels already provide that, so the line only counts as
        // part of the post-tune delay.
        if (music_iequals(line.substr(0, 7), "AMBIENT")) {
            continue;
        }

        std::string_view fields[6];
        int count = 0;
        while (count < 6 && !line.empty()) {
            const size_t space = line.find_first_of(" \t");
            fields[count++] = line.substr(0, space);
            line = (space == std::string_view::npos) ? std::string_view() : music_trim(line.substr(space + 1));
        }

        if (count < 6) {
            continue;
        }

        const char type = (char)std::toupper((unsigned char)fields[1].front());
        if (type != 'M' && type != 'A') {
            continue;
        }

        const xstring key = music_track_key_for_file(fields[0]);
        if (key.empty()) {
            logs::info("Music: playlist track '%.*s' has no soundtrack entry, skipped", (int)fields[0].size(),
              fields[0].data());
            continue;
        }

        music_data_t::playlist_rule rule;
        rule.key = key;
        rule.main = (type == 'M');
        rule.mission = std::atoi(std::string(fields[2]).c_str());
        rule.delay_sec = std::atoi(std::string(fields[3]).c_str());
        rule.min_pop = std::atoi(std::string(fields[4]).c_str());
        rule.max_pop = std::atoi(std::string(fields[5]).c_str());
        music.playlist.push_back(rule);
    }

    return (int)music.playlist.size();
}

int sound_manager_t::music_playlist_size() const {
    return (int)music.playlist.size();
}

static void music_load_playlist() {
    music.playlist_loaded = true;
    if (music.playlist_file.empty()) {
        return;
    }

    constexpr int max_size = 512 * 1024;
    buffer buf(max_size);
    const int size = io_read_file_into_buffer(music.playlist_file.c_str(), NOT_LOCALIZED, &buf, max_size - 1);
    if (size <= 0) {
        logs::info("Music: playlist '%s' not found, using population pools", music.playlist_file.c_str());
        return;
    }

    const int rules = g_sound.music_load_playlist_text(std::string_view((const char*)buf.get_data(), size));
    logs::info("Music: playlist '%s' loaded, %d tracks", music.playlist_file.c_str(), rules);
}

static int music_current_mission() {
    if (g_scenario.scmode == e_scenario_custom_map) {
        return -1;
    }

    return g_scenario.campaign_scenario_id;
}

static bool music_playlist_has_mission(int mission) {
    if (mission < 0) {
        return false;
    }

    for (const auto& r : music.playlist) {
        if (r.mission == mission) {
            return true;
        }
    }

    return false;
}

static bool music_playlist_has_track(int mission, const xstring& key) {
    for (const auto& r : music.playlist) {
        if (r.mission == mission && r.key == key) {
            return true;
        }
    }

    return false;
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

static const music_data_t::playlist_rule* music_random_rule(
  const std::vector<const music_data_t::playlist_rule*>& rules, const xstring& exclude) {
    std::vector<const music_data_t::playlist_rule*> candidates;
    for (const auto* r : rules) {
        if (r->key != exclude) {
            candidates.push_back(r);
        }
    }

    if (candidates.empty()) {
        return rules.empty() ? nullptr : rules.front();
    }

    return candidates[random_int_between(0, (int)candidates.size())];
}

// Picks the next city track for the current population. `random` re-rolls like
// the original game does on mission start / save load; otherwise the playlist
// alternates between the mission's main tunes (in file order) and a random
// alternate tune.
static music_pick music_choose_city_track(bool random) {
    const int population = g_city.population.current;
    const int mission = music_current_mission();

    std::vector<const music_data_t::playlist_rule*> mains;
    std::vector<const music_data_t::playlist_rule*> alts;
    for (const auto& r : music.playlist) {
        if (r.mission != mission || population < r.min_pop || population > r.max_pop) {
            continue;
        }
        (r.main ? mains : alts).push_back(&r);
    }

    if (mains.empty() && alts.empty()) {
        music_pick pick;
        pick.key = music_random_city_track(music_city_tracks(population), music.current_track);
        pick.delay_sec = music.post_tune_delay_sec;
        return pick;
    }

    auto next_main = [&](const xstring& after) -> const music_data_t::playlist_rule* {
        if (mains.empty()) {
            return nullptr;
        }
        for (size_t i = 0; i < mains.size(); ++i) {
            if (mains[i]->key == after) {
                return mains[(i + 1) % mains.size()];
            }
        }
        return mains.front();
    };

    const music_data_t::playlist_rule* chosen = nullptr;
    const bool current_is_main
      = std::any_of(mains.begin(), mains.end(), [](auto* r) { return r->key == music.current_track; });
    const bool current_is_alt
      = std::any_of(alts.begin(), alts.end(), [](auto* r) { return r->key == music.current_track; });

    if (random || (!current_is_main && !current_is_alt)) {
        std::vector<const music_data_t::playlist_rule*> all(mains);
        all.insert(all.end(), alts.begin(), alts.end());
        chosen = music_random_rule(all, music.current_track);
    } else if (current_is_main) {
        chosen = alts.empty() ? next_main(music.current_track) : music_random_rule(alts, music.current_track);
    } else {
        chosen = mains.empty() ? music_random_rule(alts, music.current_track) : next_main(music.last_main);
    }

    music_pick pick;
    if (chosen) {
        pick.key = chosen->key;
        pick.delay_sec = chosen->delay_sec;
    }
    return pick;
}

// True when the current track still belongs to the city music for this map, so
// a regular update should let it keep playing.
static bool music_city_track_fits() {
    const int mission = music_current_mission();
    if (music_playlist_has_mission(mission)) {
        return music_playlist_has_track(mission, music.current_track);
    }

    const auto& pool = music_city_tracks(g_city.population.current);
    return std::find(pool.begin(), pool.end(), music.current_track) != pool.end();
}

static void music_note_main(const xstring& key) {
    const int mission = music_current_mission();
    for (const auto& r : music.playlist) {
        if (r.mission == mission && r.main && r.key == key) {
            music.last_main = key;
            return;
        }
    }
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

    if (!music.playlist_loaded) {
        music_load_playlist();
    }

    xstring track;
    bool loop = true;
    int delay_sec = 0;
    int total_enemies = g_city.figures.total_invading_enemies();

    if (total_enemies >= 32) {
        track = music.combat_long;
    } else if (total_enemies > 0) {
        track = music.combat_short;
    } else {
        // Regular updates keep the current track while it still fits the map's
        // city music. A forced update (mission start, save load) re-rolls a
        // different random track like the original game does.
        if (!force && music_city_track_fits()) {
            return;
        }

        const music_pick pick = music_choose_city_track(force);
        track = pick.key;
        delay_sec = pick.delay_sec;
        loop = false;
    }

    if (track.empty() || track == music.current_track) {
        return;
    }

    play_track(track, loop);
    music.post_delay_ms = delay_sec * 1000;
    music_note_main(track);
    music.next_check = 10;
}

void sound_manager_t::music_next_track() {
    if (!game_features::gameopt_sound_music_enabled) {
        music_stop();
        return;
    }

    if (!music.playlist_loaded) {
        music_load_playlist();
    }

    const music_pick pick = music_choose_city_track(false);
    if (pick.key.empty()) {
        return;
    }

    play_track(pick.key, false);
    music.post_delay_ms = pick.delay_sec * 1000;
    music_note_main(pick.key);
}

void sound_manager_t::music_frame() {
    if (!music.track_once) {
        return;
    }

    if (!music.finished_at) {
        if (music_playing()) {
            return;
        }
        music.finished_at = time_get_millis();
        return;
    }

    if (time_get_millis() - music.finished_at < (time_millis)music.post_delay_ms) {
        return;
    }

    music.track_once = false;
    music.finished_at = 0;
    music_next_track();
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
    music.track_once = false;
    music.finished_at = 0;
}
