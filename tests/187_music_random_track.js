// #634: forced music update (mission start / save load) must re-roll a random
// city track from the population tier that differs from the current one, while
// regular updates keep the track as long as the tier does not change.

var __test187_ok = false

function test187_forced_tracks(count) {
    var tracks = []
    for (var i = 0; i < count; ++i) {
        __game_sound.music_update(1)
        tracks.push(__test_music_current_track())
    }
    return tracks
}

function run_test() {
    __log_info_native('[test:187] random city track on forced music update')
    test_reload_city_session('data/default.map')

    var music_prev = game_features.get('gameopt_sound_music_enabled') === true
    game_features.set('gameopt_sound_music_enabled', true)
    __game_sound.music_stop()
    __test_set_city_population(200)

    var ok = true
    var tracks = test187_forced_tracks(30)
    var distinct = {}
    for (var i = 0; i < tracks.length; ++i) {
        if (!tracks[i]) {
            __log_info_native('[test:187] forced update #' + i + ' left no track playing')
            ok = false
            break
        }
        if (i > 0 && tracks[i] == tracks[i - 1]) {
            __log_info_native('[test:187] forced update #' + i + ' repeated track ' + tracks[i])
            ok = false
            break
        }
        distinct[tracks[i]] = true
    }

    if (ok && Object.keys(distinct).length < 2) {
        __log_info_native('[test:187] 30 forced updates produced a single track ' + tracks[0])
        ok = false
    }

    // Regular updates keep the current track while the population tier is unchanged.
    // music_update(0) only evaluates once the 10-tick check timer has elapsed.
    var before = __test_music_current_track()
    for (var j = 0; ok && j < 12; ++j) {
        __game_sound.music_update(0)
    }
    if (ok && __test_music_current_track() != before) {
        __log_info_native('[test:187] regular update changed track ' + before + ' -> ' + __test_music_current_track())
        ok = false
    }

    // Leaving the tier picks a track from the new tier on a regular update.
    __test_set_city_population(5000)
    for (var k = 0; ok && k < 12; ++k) {
        __game_sound.music_update(0)
    }
    if (ok && __test_music_current_track() == before) {
        __log_info_native('[test:187] tier change kept low-population track ' + before)
        ok = false
    }

    __game_sound.music_stop()
    game_features.set('gameopt_sound_music_enabled', music_prev)
    __test187_ok = ok
    __test_signal_ready()
}

function check_valid() {
    return __test187_ok
}
