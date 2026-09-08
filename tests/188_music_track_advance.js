// #634 follow-up: city tracks play once and the player moves on by itself.
// music_next_track() (what the player calls once the post-tune delay after a
// finished track has elapsed) must pick a different track, follow the
// music.txt main/alternate order when the mission has a playlist, keep the
// track across population changes, and stop when music is disabled.

var __test188_ok = false

var PLAYLIST =
    "; mission 5 subset of the vanilla music.txt\n" +
    "advent.mp3 M 5 20 0 499\n" +
    "AMBIENT\n" +
    "sps.mp3 M 5 20 0 499\n" +
    "AMBIENT\n" +
    "sthA.mp3 M 5 20 0 499\n" +
    "watj.mp3 A 5 12 0 100000\n" +
    "Amber.mp3 A 5 12 0 100000\n" +
    "rwD.mp3 M 5 12 500 1499\n"

var MAINS_LOW = ["city_8", "city_1", "city_2"]   // advent, sps, sthA in file order
var ALTS = ["city_16", "city_23"]                 // watj, Amber
var MAIN_MID = "city_11"                          // rwD

function test188_fail(msg) {
    __log_info_native('[test:188] ' + msg)
    return false
}

function test188_contains(list, value) {
    for (var i = 0; i < list.length; ++i) {
        if (list[i] == value) {
            return true
        }
    }
    return false
}

function test188_pool_advance() {
    // No playlist: population pools, every advance picks a different track.
    __test_music_load_playlist("")
    __test_set_campaign_scenario_id(-1)
    __test_set_city_population(200)
    __game_sound.music_update(1)

    var prev = __test_music_current_track()
    if (!prev) {
        return test188_fail('forced update left no track playing')
    }

    for (var i = 0; i < 10; ++i) {
        __test_music_next_track()
        var cur = __test_music_current_track()
        if (!cur) {
            return test188_fail('advance #' + i + ' left no track playing')
        }
        if (cur == prev) {
            return test188_fail('advance #' + i + ' repeated track ' + cur)
        }
        prev = cur
    }
    return true
}

function test188_playlist_advance() {
    var loaded = __test_music_load_playlist(PLAYLIST)
    if (loaded != 6) {
        return test188_fail('playlist loaded ' + loaded + ' rules, expected 6')
    }

    __test_set_campaign_scenario_id(5)
    __test_set_city_population(200)
    __game_sound.music_stop()
    __game_sound.music_update(1)

    var allowed = MAINS_LOW.concat(ALTS)
    var prev = __test_music_current_track()
    if (!test188_contains(allowed, prev)) {
        return test188_fail('forced update picked ' + prev + ', not a mission 5 track for pop 200')
    }

    var last_main = ''
    if (test188_contains(MAINS_LOW, prev)) {
        last_main = prev
    }

    for (var i = 0; i < 12; ++i) {
        __test_music_next_track()
        var cur = __test_music_current_track()
        if (!test188_contains(allowed, cur)) {
            return test188_fail('advance #' + i + ' picked ' + cur + ', not a mission 5 track for pop 200')
        }
        if (cur == prev) {
            return test188_fail('advance #' + i + ' repeated track ' + cur)
        }

        var prev_main = test188_contains(MAINS_LOW, prev)
        var cur_main = test188_contains(MAINS_LOW, cur)
        if (prev_main == cur_main) {
            return test188_fail('advance #' + i + ' did not alternate main/alternate: ' + prev + ' -> ' + cur)
        }

        if (cur_main) {
            var expected = last_main ? MAINS_LOW[(MAINS_LOW.indexOf(last_main) + 1) % MAINS_LOW.length] : MAINS_LOW[0]
            if (cur != expected) {
                return test188_fail('advance #' + i + ' main track ' + cur + ', expected ' + expected + ' after ' + last_main)
            }
            last_main = cur
        }
        prev = cur
    }

    // Leaving the population range does not cut the running track ...
    __test_set_city_population(1000)
    for (var j = 0; j < 12; ++j) {
        __game_sound.music_update(0)
    }
    if (__test_music_current_track() != prev) {
        return test188_fail('population change cut track ' + prev + ' -> ' + __test_music_current_track())
    }

    // ... but the next pick uses the new range.
    var seen_mid = false
    for (var k = 0; k < 6; ++k) {
        __test_music_next_track()
        var t = __test_music_current_track()
        if (t != MAIN_MID && !test188_contains(ALTS, t)) {
            return test188_fail('advance at pop 1000 picked ' + t)
        }
        if (t == MAIN_MID) {
            seen_mid = true
        }
    }
    if (!seen_mid) {
        return test188_fail('advance at pop 1000 never picked ' + MAIN_MID)
    }
    return true
}

function test188_disabled() {
    game_features.set('gameopt_sound_music_enabled', false)
    __test_music_next_track()
    if (__test_music_current_track()) {
        return test188_fail('advance with music disabled left ' + __test_music_current_track() + ' playing')
    }
    return true
}

function run_test() {
    __log_info_native('[test:188] city track advance and music.txt order')
    test_reload_city_session('data/default.map')

    var music_prev = game_features.get('gameopt_sound_music_enabled') === true
    game_features.set('gameopt_sound_music_enabled', true)
    __game_sound.music_stop()

    var ok = test188_pool_advance() && test188_playlist_advance() && test188_disabled()

    __game_sound.music_stop()
    __test_music_load_playlist("")
    __test_set_campaign_scenario_id(-1)
    game_features.set('gameopt_sound_music_enabled', music_prev)
    __test188_ok = ok
    __test_signal_ready()
}

function check_valid() {
    return __test188_ok
}
