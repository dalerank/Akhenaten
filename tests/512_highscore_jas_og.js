// OG high scores (window/high_scores.c highscore_record_mission / highscore_set_entry): a campaign victory writes
// highscore.jas, 100 records of 76 bytes (score, mission, name[32], culture, prosperity, kingdom, population,
// treasury, months, difficulty, monuments, used), when the mission has no record or the record is beaten. The
// result is NEW, OWN_KEPT / OWN_BEATEN for the same name, OTHER_KEPT / OTHER_BEATEN for another one. The file goes
// to the user directory and reads back into the records window. Also the OG score formula (city_victory_score).
// Markers:
//   [test-marker] highscore_jas_layout_ok
//   [test-marker] highscore_jas_results_ok
//   [test-marker] highscore_jas_readback_ok
//   [test-marker] highscore_score_og_ok

// The last slot: no campaign mission uses it, so a highscore.jas of an installed game cannot hold it.
var T512_MISSION = 99
var T512_RECORD = 76

var t512 = {}

function test512_fail(msg) {
    __log_info_native('[test:512] FAIL ' + msg)
    test512_restore()
    __test_signal_ready()
}

function test512_restore() {
    city.kingdome.player_name = t512.name
    __test_file_remove(__highscores_path())
    __highscores_load()
}

function test512_field(offset) {
    return __test_file_read_i32(__highscores_path(), T512_MISSION * T512_RECORD + offset)
}

function run_test() {
    __log_info_native('[test:512] OG highscore.jas')
    test_ensure_city_session('data/default.map')
    t512 = { name: city.kingdome.player_name }

    var path = __highscores_path()
    if (path != __test_user_dir() + '/highscore.jas') {
        return test512_fail('path ' + path + ' is not in the user dir ' + __test_user_dir())
    }
    __test_file_remove(path)
    city.kingdome.player_name = 'Ramses'

    var result = __highscores_record_mission(T512_MISSION, 24, 1234, 1)
    if (result != 1) {
        return test512_fail('first record result ' + result)
    }
    if (__test_file_size(path) != 7600) {
        return test512_fail('file size ' + __test_file_size(path))
    }
    if (test512_field(0) != 1234 || test512_field(4) != T512_MISSION || test512_field(40) != city.rating.culture
        || test512_field(52) != city.population || test512_field(56) != city.finance.treasury
        || test512_field(60) != 24 || test512_field(64) != game.difficulty || test512_field(68) != 1
        || test512_field(72) != 1) {
        return test512_fail('record fields score=' + test512_field(0) + ' mission=' + test512_field(4)
            + ' months=' + test512_field(60) + ' monuments=' + test512_field(68) + ' used=' + test512_field(72))
    }
    __log_marker('highscore_jas_layout_ok')

    // [player, score, result, score kept in the file]
    var steps = [
        ['ramses', 1000, 2, 1234],
        ['Ramses', 2000, 3, 2000],
        ['Hatshepsut', 1500, 4, 2000],
        ['Hatshepsut', 3000, 5, 3000],
    ]
    for (var i = 0; i < steps.length; i++) {
        city.kingdome.player_name = steps[i][0]
        result = __highscores_record_mission(T512_MISSION, 30, steps[i][1], 0)
        if (result != steps[i][2] || test512_field(0) != steps[i][3]) {
            return test512_fail('step ' + i + ': result ' + result + ' score ' + test512_field(0))
        }
        if (result >= 4 && __highscores_previous_name() != 'Ramses') {
            return test512_fail('step ' + i + ': previous name ' + __highscores_previous_name())
        }
    }
    __log_marker('highscore_jas_results_ok')

    __highscores_load()
    var found = false
    for (var r = 0; r < __highscores_count(); r++) {
        if (__highscore_mission(r) == T512_MISSION) {
            found = __highscore_score(r) == 3000 && __highscore_months(r) == 30
                && __highscore_player_name(r) == 'Hatshepsut' && __highscore_monuments(r) == 0
        }
    }
    if (!found) {
        return test512_fail('read back: count ' + __highscores_count())
    }
    __log_marker('highscore_jas_readback_ok')

    var months = 40
    var weight = 9
    var ratings = city.rating.kingdom + city.rating.prosperity + city.rating.culture
    var want = (weight / (months * months * 0.00015625)) * (weight * 20.0) + ratings * (city.population * 0.002)
    want = (want + city.finance.treasury / (months * 0.03333333333333333)) * ((game.difficulty + 1.0) * 0.3333333333333333)
    want = want < 0 ? Math.ceil(want) : Math.floor(want)
    var got = __city_victory_score(months, weight)
    if (got != want) {
        return test512_fail('score ' + got + ' want ' + want)
    }
    __log_marker('highscore_score_og_ok')

    test512_restore()
    __test_signal_ready()
}

function check_valid() {
    var markers = ['highscore_jas_layout_ok', 'highscore_jas_results_ok', 'highscore_jas_readback_ok', 'highscore_score_og_ok']
    for (var i = 0; i < markers.length; i++) {
        if (!__test_find_inlog('[test-marker] ' + markers[i])) {
            __log_info_native('[test:512] missing marker: ' + markers[i])
            return false
        }
    }
    return true
}
