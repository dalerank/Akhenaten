// Battle music as OG run.c game_run_update_music_and_ambient: every frame, battle.mp3 starts (looping) once the
// city has 16 enemies or 5 enemy warships, and fades when both drop below again. Checked with
// __test_music_frame() (one frame of the music logic) and the "[sound] music" log lines, so it runs with
// --nosound and without Pharaoh data.

var __t341_ok = false

function t341_fail(msg) {
    __log_info_native('[test:341] FAIL: ' + msg)
    return false
}

function t341_check() {
    __game_sound.music_stop()

    __test_set_city_enemies(15)
    __test_music_frame()
    if (__test_music_current_track() == 'battle') {
        return t341_fail('15 enemies started the battle music')
    }

    __test_set_city_enemies(16)
    __test_music_frame()
    if (__test_music_current_track() != 'battle') {
        return t341_fail('16 enemies did not start the battle music: ' + __test_music_current_track())
    }
    if (!__test_find_inlog('[sound] music battle AUDIO/Music/Battle.mp3 loop')) {
        return t341_fail('no looping battle.mp3 log line')
    }

    __test_set_city_enemies(0)
    __test_music_frame()
    if (!__test_find_inlog('[sound] music fade battle')) {
        return t341_fail('battle music did not fade with no enemies left')
    }

    __game_sound.music_stop()
    game_features.set('gameopt_sound_music_enabled', false)
    __test_set_city_enemies(20)
    __test_music_frame()
    game_features.set('gameopt_sound_music_enabled', true)
    if (__test_music_current_track() == 'battle') {
        return t341_fail('battle music started with music disabled')
    }

    __test_set_city_enemies(0)
    __test_music_frame()
    __game_sound.music_stop()

    var ships = 0
    for (var i = 0; i < 5; i++) {
        if (__test_figure_create(FIGURE_ENEMY_WARSHIP, 10 + i, 10)) {
            ships++
        }
    }
    if (ships != 5 || __test_count_enemy_warships() != 5) {
        return t341_fail('could not create 5 enemy warships (' + ships + ')')
    }
    __test_set_city_enemies(0)
    __test_music_frame()
    if (__test_music_current_track() != 'battle') {
        return t341_fail('5 enemy warships did not start the battle music: ' + __test_music_current_track())
    }
    return true
}

function run_test() {
    __log_info_native('[test:341] OG battle music')
    test_reload_city_session('data/default.map')

    var music_prev = game_features.get('gameopt_sound_music_enabled') === true
    game_features.set('gameopt_sound_music_enabled', true)
    var ok = t341_check()
    __test_set_city_enemies(0)
    __game_sound.music_stop()
    game_features.set('gameopt_sound_music_enabled', music_prev)

    if (ok) {
        __log_marker('battle_music_og_ok')
    }
    __t341_ok = ok
    test_reload_city_session('data/default.map')
    __test_signal_ready()
}

function check_valid() {
    return __t341_ok && __test_find_inlog('battle_music_og_ok')
}
