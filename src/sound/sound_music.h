#pragma once

#include "core/svector.h"
#include "core/system_time.h"
#include "core/xstring.h"
#include "game/game_events.h"

#include <random>
#include <string_view>
#include <utility>
#include <vector>

// OG music_types.h music_state_kind
enum e_og_music_state {
    OG_MUSIC_STATE_PLAY_TRACK = 0,
    OG_MUSIC_STATE_PLAY_AMBIENT = 1,
    OG_MUSIC_STATE_START_TIMER = 2,
    OG_MUSIC_STATE_WAIT_TRACK_END = 3,
};

struct sound_music_t {
    xstring current_track;
    struct soundtrack {
        xstring key;
        xstring file;
    };

    struct pop_soundtrack {
        int pop;
        svector<xstring, 8> tracks;
    };

    // One line of music.txt: "<file> <M|A> <mission> <duration sec> <min pop> <max pop>".
    // M tracks play in file order within the population range; an "AMBIENT" line after an M track makes a
    // random A (ambient) track follow it (OG music.c).
    struct playlist_rule {
        xstring key;
        bool main;
        int mission;
        int delay_sec;
        int min_pop;
        int max_pop;
    };

    std::vector<playlist_rule> playlist;
    // (mission, M track index) pairs: OG ambient_after_track[index] = 1.
    std::vector<std::pair<int, int>> ambient_marks;
    bool playlist_loaded = false;

    // OG music_state playback fields, for missions that music.txt lists.
    struct og_state_t {
        int range_first = 0;
        int range_last = 0;
        int previous_range_first = 0;
        int next_track = 0;
        int state = OG_MUSIC_STATE_PLAY_TRACK;
        time_millis wait_start = 0;
        int track_duration_ms = 0;
        bool track_finished = false;
        bool selected = false; // OG sound_init does select_by_population(force) once
    } og;
    bool invasion_music_request = false;
    int plays = 0;

    // Maps music.txt does not list: population pools, each track plays once, then the post-tune delay.
    bool track_once = false;
    time_millis finished_at = 0;
    int post_delay_ms = 0;

    // Cosmetic: never the simulation LFSR, crt_rand or libc rand(), so the simulation does not depend on
    // music settings, the wall clock or --nosound.
    std::minstd_rand rng{std::random_device{}()};

    int random_index(int count) { return std::uniform_int_distribution<int>(0, count - 1)(rng); }

    void play_track(const xstring track, bool loop = true);
    void play_intro();
    int load_playlist_text(std::string_view text);
    void update(bool force);
    void next_track();
    void frame();
    void stop();
    void on_sound_track(event_sound_track ev);
    const xstring& current_track_name() const { return current_track; }

private:
    void og_update(int mission);
    void fade_out();
    void city_frame();
};

sound_music_t& sound_music();
