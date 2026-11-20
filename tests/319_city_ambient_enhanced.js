// Enhanced city ambience (gameplay_enhanced_city_ambient): buildings drawn around the screen centre become
// positional voices. With the camera on a granary, its sample must be the loudest voice, panned near the
// middle ("[sound] ambient voices <channel>:<gain%>:<pan%> ..."). The audio side must not touch the
// simulation: the same run with the feature on and off ends in the same state hash.
// Marker: [test-marker] city_ambient_enhanced_ok

var __t319_ok = false
var __t319_ticks = 200

function t319_fail(msg) {
    __log_info_native('[test:319] FAIL: ' + msg)
    return null
}

// Returns { summary, channel, hash } or null.
function t319_run(enhanced) {
    __test_crt_srand(1)
    if (!test_reload_city_session('data/default.map')) {
        return t319_fail('map load')
    }
    game_features.set('gameplay_enhanced_city_ambient', enhanced)
    __test_set_treasury(100000)
    var bid = test_building_place(BUILDING_GRANARY, -1, -1)
    if (!bid) {
        return t319_fail('granary not placed')
    }
    var channel = __test_sound_city_mark_building(bid, 0)
    __test_camera_center_building(bid)
    __test_pump_frames(6)
    var summary = __test_sound_ambient_summary()
    __test_run_ticks(__t319_ticks)
    __test_pump_frames(6)
    __test_process_events()
    return { summary: summary, channel: channel, hash: __test_state_hash() }
}

function t319_diff(a, b) {
    var x = a.split(';')
    var y = b.split(';')
    var out = []
    for (var i = 0; i < x.length; i++) {
        var name = x[i].split('=')[0]
        if (name != 'total' && x[i] !== y[i]) {
            out.push(name)
        }
    }
    return out
}

function t319_check() {
    var off = t319_run(false)
    if (!off) {
        return false
    }
    if (off.summary !== '') {
        t319_fail('voices with the feature off: ' + off.summary)
        return false
    }

    var on = t319_run(true)
    game_features.set('gameplay_enhanced_city_ambient', false)
    __test_pump_frames(1)
    if (!on) {
        return false
    }
    var voices = on.summary.split(' ')
    var first = voices[0].split(':')
    if (voices[0] === '' || first.length != 3) {
        t319_fail('no voices with the camera on the granary')
        return false
    }
    if (parseInt(first[0]) != on.channel) {
        t319_fail('loudest voice ' + voices[0] + ', expected the granary channel ' + on.channel + ' (' + on.summary + ')')
        return false
    }
    var pan = parseInt(first[2])
    if (pan < 30 || pan > 70) {
        t319_fail('granary voice panned to ' + pan + '%, expected near the middle')
        return false
    }
    if (voices.length > 4) {
        t319_fail('more voices than max_voices: ' + on.summary)
        return false
    }
    if (!__test_find_inlog('[sound] ambient voices ' + on.channel + ':')) {
        t319_fail('no "[sound] ambient voices" log line')
        return false
    }
    // With Pharaoh data loaded some chunks (building_list_small) differ between two identical runs even with the
    // feature off; only differences beyond that baseline count.
    var diff = t319_diff(off.hash, on.hash)
    if (diff.length) {
        var again = t319_run(false)
        var baseline = again ? t319_diff(off.hash, again.hash) : []
        for (var i = 0; i < diff.length; i++) {
            if (baseline.indexOf(diff[i]) < 0) {
                t319_fail('chunk ' + diff[i] + ' differs with the enhanced ambience on')
                return false
            }
            __log_info_native('[test:319] chunk ' + diff[i] + ' also differs between two runs with the feature off')
        }
    }
    return true
}

function run_test() {
    __log_info_native('[test:319] enhanced city ambience')
    if (t319_check()) {
        __log_marker('city_ambient_enhanced_ok')
        __t319_ok = true
    }
    test_reload_city_session('data/default.map')
    __test_signal_ready()
}

function check_valid() {
    return __t319_ok && __test_find_inlog('city_ambient_enhanced_ok')
}
