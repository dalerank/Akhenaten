// Ironwill mode — player-save gate + checkpoint filename (IW0–IW5).
//
// Markers:
//   [test-marker] ironwill_allows_off_ok
//   [test-marker] ironwill_allows_on_ok
//   [test-marker] ironwill_checkpoint_name_ok
//   [test-marker] ironwill_exempt_ok
//   [test-marker] ironwill_write_blocked_ok

function run_test() {
    __log_info_native('[test:544] ironwill gate')

    var prev = game_features.gameopt_ironwill

    game_features.gameopt_ironwill = false
    if (!game_allows_player_save() || !game_allows_midgame_load()) {
        __log_info_native('[test:544] allows should be true when OFF')
        game_features.gameopt_ironwill = prev
        __test_signal_ready()
        return
    }
    __log_marker('ironwill_allows_off_ok')

    game_features.gameopt_ironwill = true
    if (game_allows_player_save() || game_allows_midgame_load()) {
        __log_info_native('[test:544] allows should be false when ON')
        game_features.gameopt_ironwill = prev
        __test_signal_ready()
        return
    }
    __log_marker('ironwill_allows_on_ok')

    if (IRONWILL_CHECKPOINT_FILENAME !== 'ironwill.svx') {
        __log_info_native('[test:544] checkpoint name: ' + IRONWILL_CHECKPOINT_FILENAME)
        game_features.gameopt_ironwill = prev
        __test_signal_ready()
        return
    }
    __log_marker('ironwill_checkpoint_name_ok')

    if (!__test_ironwill_exempt('ironwill.svx')
        || !__test_ironwill_exempt('ironwill.sav')
        || !__test_ironwill_exempt('autosave_replay.svx')
        || __test_ironwill_exempt('quicksave.svx')
        || __test_ironwill_exempt('autosave_month.svx')
        || __test_ironwill_exempt('mysave.svx')) {
        __log_info_native('[test:544] exempt whitelist fail')
        game_features.gameopt_ironwill = prev
        __test_signal_ready()
        return
    }
    __log_marker('ironwill_exempt_ok')

    // C++ belt: non-exempt write_savegame must fail while Ironwill ON (no disk I/O).
    if (__game_write_savegame('quicksave.svx') || __game_write_savegame('mysave.svx')
        || __game_write_savegame('autosave_month.svx')) {
        __log_info_native('[test:544] write_savegame should be blocked when ON')
        game_features.gameopt_ironwill = prev
        __test_signal_ready()
        return
    }
    __log_marker('ironwill_write_blocked_ok')

    game_features.gameopt_ironwill = prev
    __test_signal_ready()
}

function check_valid() {
    var markers = [
        'ironwill_allows_off_ok',
        'ironwill_allows_on_ok',
        'ironwill_checkpoint_name_ok',
        'ironwill_exempt_ok',
        'ironwill_write_blocked_ok'
    ]
    for (var i = 0; i < markers.length; i++) {
        var marker = '[test-marker] ' + markers[i]
        if (!__test_find_inlog(marker)) {
            __log_info_native('[test:544] missing marker: ' + marker)
            return false
        }
    }
    return true
}
