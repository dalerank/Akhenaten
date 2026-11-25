#include "core/log.h"
#include "sound/sound_music.h"
#include "core/xvalue.h"
#include "city/city_figures.h"

#include "city/city.h"
#include "city/city_population.h"
#include "figure/figure.h"
#include "graphics/window.h"
#include "core/vfs/vfs.h"
#include "core/profiler.h"
#include "game/game_config.h"
#include "core/calc.h"
#include "core/buffer.h"
#include "core/system_time.h"
#include "core/vfs/dir.h"
#include "io/io.h"
#include "scenario/scenario.h"
#include "sound/sound.h"
#include "js/js_register.h"

#include "dev/debug.h"
#include <algorithm>
#include <random>
#include <string_view>
#include <vector>

// OG run.c run_rule
constexpr int og_invasion_music_enemies = 16;
constexpr int og_invasion_music_warships = 5;

struct music_config_t {
    xstring menu_track;
    xstring battle_track;
    xstring playlist_file;
    int post_tune_delay_sec = 20;
    svector<sound_music_t::soundtrack, 64> soundtracks;
    svector<sound_music_t::pop_soundtrack, 16> music_populations;
};
ANK_CONFIG_STRUCT(sound_music_t::soundtrack, key, file)
ANK_CONFIG_STRUCT(sound_music_t::pop_soundtrack, pop, tracks)
ANK_CONFIG_STRUCT(music_config_t, menu_track, battle_track, playlist_file, post_tune_delay_sec, soundtracks,
  music_populations)

music_config_t ANK_VARIABLE_N(music_config, "music");

sound_music_t& sound_music() {
    return xvalue<sound_music_t>::ref();
}

struct music_pick {
    xstring key;
    int delay_sec = 0;
};

declare_console_command_p(playtrack) {
    sound_music().play_track(args.next_str().c_str());
}

void sound_music_t::play_track(const xstring track, bool loop) {
    sound_manager().stop_music();
    track_once = false;
    finished_at = 0;

    auto it = std::find_if(music_config.soundtracks.begin(), music_config.soundtracks.end(),
      [track](auto& t) { return t.key == track; });

    if (it == music_config.soundtracks.end()) {
        return;
    }

    if (sound_manager().log_events()) {
        logs::info("[sound] music %s %s%s", track.c_str(), it->file.c_str(), loop ? " loop" : "");
    }

    const int volume = calc_bound(game_features::gameopt_sound_music_volume.to_int(), 0, 100);
    vfs::path corrected_filename = it->file.c_str();
    if (strncmp(it->file.c_str(), vfs::content_audio, strlen(vfs::content_audio)) != 0) {
        corrected_filename = vfs::path(vfs::content_audio, it->file.c_str());
    }

    const bool played = sound_manager().play_music(corrected_filename.resolve(), volume, loop);

    current_track = track;
    track_once = played && !loop;
    ++plays;
}

void sound_music_t::play_intro() {
    if (!!game_features::gameopt_sound_music_enabled) {
        play_track(music_config.menu_track);
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
    for (const auto& t : music_config.soundtracks) {
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

int sound_music_t::load_playlist_text(std::string_view text) {
    playlist.clear();
    ambient_marks.clear();
    playlist_loaded = true;
    og = {};
    int last_mission = 0;

    while (!text.empty()) {
        const size_t eol = text.find('\n');
        std::string_view line = text.substr(0, eol);
        text = (eol == std::string_view::npos) ? std::string_view() : text.substr(eol + 1);

        line = music_trim(line);
        if (line.empty() || line.front() == ';') {
            continue;
        }

        // OG: ambient_after_track[track_count] = 1 for the mission of the last track line.
        if (line.substr(0, line.find_first_of(" \t,")) == "AMBIENT") {
            int tracks = 0;
            for (const auto& r : playlist) {
                tracks += (r.main && r.mission == last_mission) ? 1 : 0;
            }
            ambient_marks.push_back({last_mission, tracks});
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

        last_mission = std::atoi(std::string(fields[2]).c_str());
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

        sound_music_t::playlist_rule rule;
        rule.key = key;
        rule.main = (type == 'M');
        rule.mission = std::atoi(std::string(fields[2]).c_str());
        rule.delay_sec = std::atoi(std::string(fields[3]).c_str());
        rule.min_pop = std::atoi(std::string(fields[4]).c_str());
        rule.max_pop = std::atoi(std::string(fields[5]).c_str());
        playlist.push_back(rule);
    }

    return (int)playlist.size();
}

static void music_load_playlist() {
    sound_music().playlist_loaded = true;
    if (music_config.playlist_file.empty()) {
        return;
    }

    constexpr int max_size = 512 * 1024;
    buffer buf(max_size);
    const int size = io_read_file_into_buffer(music_config.playlist_file.c_str(), NOT_LOCALIZED, &buf, max_size - 1);
    if (size <= 0) {
        logs::info("Music: playlist '%s' not found, using population pools", music_config.playlist_file.c_str());
        return;
    }

    const int rules = sound_music().load_playlist_text(std::string_view((const char*)buf.get_data(), size));
    logs::info("Music: playlist '%s' loaded, %d tracks", music_config.playlist_file.c_str(), rules);
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

    for (const auto& r : sound_music().playlist) {
        if (r.mission == mission) {
            return true;
        }
    }

    return false;
}

static const svector<xstring, 8>& music_city_tracks(int population) {
    static const svector<xstring, 8> no_tracks{};
    if (music_config.music_populations.empty()) {
        return no_tracks;
    }

    const sound_music_t::pop_soundtrack* tier = &music_config.music_populations.front();

    for (const auto& p : music_config.music_populations) {
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

    return candidates[sound_music().random_index((int)candidates.size())];
}

// Maps music.txt does not list: a random track of the population pool, another than the current one.
static music_pick music_choose_pool_track() {
    music_pick pick;
    pick.key = music_random_city_track(music_city_tracks(city_population().current), sound_music().current_track);
    pick.delay_sec = music_config.post_tune_delay_sec;
    return pick;
}

static bool music_pool_track_fits() {
    const auto& pool = music_city_tracks(city_population().current);
    return std::find(pool.begin(), pool.end(), sound_music().current_track) != pool.end();
}

using music_rules = std::vector<const sound_music_t::playlist_rule*>;

static void music_mission_tracks(int mission, music_rules& tracks, music_rules& ambient) {
    for (const auto& r : sound_music().playlist) {
        if (r.mission == mission) {
            (r.main ? tracks : ambient).push_back(&r);
        }
    }
}

static bool music_ambient_after(int mission, int track) {
    const auto mark = std::make_pair(mission, track);
    return std::find(sound_music().ambient_marks.begin(), sound_music().ambient_marks.end(), mark)
           != sound_music().ambient_marks.end();
}

static bool music_track_holds(const sound_music_t::playlist_rule* track, int population) {
    return track->min_pop <= population && population <= track->max_pop;
}

// OG music.c sound_music_select_by_population.
static void og_music_select_by_population(const music_rules& tracks, bool force) {
    auto& og = sound_music().og;
    const int population = city_population().current;
    const int count = (int)tracks.size();
    const bool holds = og.next_track < count && music_track_holds(tracks[og.next_track], population);
    if (!holds || force) {
        int first = 0;
        while (first < count && !music_track_holds(tracks[first], population)) {
            first++;
        }
        int end = first;
        while (end < count && population >= tracks[end]->min_pop) {
            end++;
        }
        og.range_first = first;
        og.range_last = end - 1;
    }

    if (og.next_track < og.range_first || og.range_last < og.next_track) {
        og.next_track = og.range_first;
    }

    if (og.range_first != og.previous_range_first) {
        og.previous_range_first = og.range_first;
        if (!og.track_finished) {
            og.state = OG_MUSIC_STATE_PLAY_AMBIENT;
        }
    }
}

// OG music.c sound_music_update, called while no music plays. The ambient pick uses the music generator where
// OG draws crt_rand (play_random_ambient).
void sound_music_t::og_update(int mission) {
    music_rules tracks;
    music_rules ambient;
    music_mission_tracks(mission, tracks, ambient);

    if (!og.selected) {
        og.selected = true;
        og_music_select_by_population(tracks, true);
    }
    if (og.state == OG_MUSIC_STATE_PLAY_TRACK) {
        og_music_select_by_population(tracks, false);
    }

    switch (og.state) {
    case OG_MUSIC_STATE_PLAY_TRACK: {
        if (og.next_track >= (int)tracks.size()) {
            return;
        }
        const sound_music_t::playlist_rule* track = tracks[og.next_track];
        play_track(track->key, false);
        og.track_duration_ms = track->delay_sec * 1000;
        og.track_finished = false;
        og.next_track++;
        og.state
          = music_ambient_after(mission, og.next_track) ? OG_MUSIC_STATE_PLAY_AMBIENT : OG_MUSIC_STATE_START_TIMER;
        return;
    }

    case OG_MUSIC_STATE_PLAY_AMBIENT:
        if (!ambient.empty()) {
            play_track(ambient[sound_music().random_index((int)ambient.size())]->key, false);
        }
        og.state = OG_MUSIC_STATE_START_TIMER;
        return;

    case OG_MUSIC_STATE_START_TIMER:
        og.state = OG_MUSIC_STATE_WAIT_TRACK_END;
        og.wait_start = time_get_millis();
        return;

    case OG_MUSIC_STATE_WAIT_TRACK_END:
        if (og.wait_start + (time_millis)og.track_duration_ms < time_get_millis()) {
            if (og.range_last < og.next_track) {
                og.next_track = og.range_first;
            }
            og.state = OG_MUSIC_STATE_PLAY_TRACK;
            og.track_finished = true;
        }
        return;
    }
}

void sound_music_t::update(bool force) {
    OZZY_PROFILER_FUNCTION();
    if (!game_features::gameopt_sound_music_enabled) {
        return;
    }

    if (!playlist_loaded) {
        music_load_playlist();
    }

    if (invasion_music_request) {
        return;
    }

    const int mission = music_current_mission();
    if (music_playlist_has_mission(mission)) {
        if (force) {
            og = {};
            sound_manager().stop_music();
        }
        if (!sound_manager().music_playing()) {
            og_update(mission);
        }
        return;
    }

    // Regular updates keep the current track while it still fits the population pool. A forced update
    // (mission start, save load) re-rolls a different random track.
    if (!force && music_pool_track_fits()) {
        return;
    }

    const music_pick pick = music_choose_pool_track();
    if (pick.key.empty() || pick.key == current_track) {
        return;
    }

    play_track(pick.key, false);
    post_delay_ms = pick.delay_sec * 1000;
}

void sound_music_t::next_track() {
    if (!game_features::gameopt_sound_music_enabled) {
        stop();
        return;
    }

    if (!playlist_loaded) {
        music_load_playlist();
    }

    const int mission = music_current_mission();
    if (music_playlist_has_mission(mission)) {
        // Steps the OG state machine to its next stream as if each one had ended and the wait had elapsed.
        const int plays_before = plays;
        for (int step = 0; step < 8 && plays_before == plays; step++) {
            if (og.state == OG_MUSIC_STATE_WAIT_TRACK_END) {
                og.wait_start = time_get_millis() - (time_millis)og.track_duration_ms - 1;
            }
            og_update(mission);
        }
        return;
    }

    const music_pick pick = music_choose_pool_track();
    if (pick.key.empty()) {
        return;
    }

    play_track(pick.key, false);
    post_delay_ms = pick.delay_sec * 1000;
}

// OG figure_count_traders counts the enemy warships alive.
static int music_enemy_warships() {
    int count = 0;
    for (int i = 1; i < MAX_FIGURES; i++) {
        const figure* f = figure_get(i);
        if (!f) {
            return 0; // no city loaded yet
        }
        const bool warship = f->type == FIGURE_ENEMY_WARSHIP || f->type == FIGURE_ENEMY_EGYPTIAN_WARSHIP;
        if (warship && f->state != FIGURE_STATE_NONE) {
            count++;
        }
    }
    return count;
}

void sound_music_t::fade_out() {
    if (sound_manager().log_events()) {
        logs::info("[sound] music fade %s", current_track.c_str());
    }
    if (!sound_manager().music_playing()) {
        return;
    }
    // OG sound_stream_fade_down: 5 volume steps every 20 ms.
    const int volume = calc_bound(game_features::gameopt_sound_music_volume.to_int(), 0, 100);
    sound_manager().fade_out_music(std::max(20, volume / 5 * 20));
}

// OG run.c game_run_update_music_and_ambient, once a frame: the battle music starts at 16 enemies or 5 enemy
// warships and fades once both are below; otherwise the city music runs in the city window while nothing plays.
void sound_music_t::frame() {
    if (city_figures().enemies < og_invasion_music_enemies && music_enemy_warships() < og_invasion_music_warships) {
        if (invasion_music_request) {
            fade_out();
            invasion_music_request = false;
        }
        if (!sound_manager().music_playing() && g_window_manager.window_is("window_city")) {
            city_frame();
        }
    } else if (!invasion_music_request && !!game_features::gameopt_sound_music_enabled) {
        play_track(music_config.battle_track, true);
        invasion_music_request = true;
    }
}

void sound_music_t::city_frame() {
    if (!game_features::gameopt_sound_music_enabled) {
        return;
    }

    if (!playlist_loaded) {
        music_load_playlist();
    }

    const int mission = music_current_mission();
    if (music_playlist_has_mission(mission)) {
        og_update(mission);
        return;
    }

    if (!track_once) {
        update(false);
        return;
    }

    if (!finished_at) {
        finished_at = time_get_millis();
        return;
    }

    if (time_get_millis() - finished_at < (time_millis)post_delay_ms) {
        return;
    }

    track_once = false;
    finished_at = 0;
    next_track();
}

void sound_manager_t::on_sound_effect(event_sound_effect ev) {
    play_effect(ev.effect);
}

void sound_music_t::on_sound_track(event_sound_track ev) {
    if (!game_features::gameopt_sound_music_enabled) {
        return;
    }
    play_track(ev.track, false);
}


void sound_music_t::stop() {
    sound_manager().stop_music();
    current_track = "";
    track_once = false;
    finished_at = 0;
    invasion_music_request = false;
}
