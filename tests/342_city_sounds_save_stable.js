// The city_sounds chunk is written as OG's sound_city_init() leaves it (slot 0 empty, slots 1..63 set up,
// no wall-clock time), because loading rebuilds the city sounds anyway. View counters gathered while drawing
// therefore must not make save -> load -> save differ.
// Marker: [test-marker] city_sounds_save_stable_ok

var __t342_ok = false

function run_test() {
    __log_info_native('[test:342] city sounds chunk save stability')
    if (!test_reload_city_session('data/default.map')) {
        __log_info_native('[test:342] FAIL: map load')
        __test_signal_ready()
        return
    }

    __test_set_treasury(100000)
    var bid = test_building_place(BUILDING_GRANARY, -1, -1)
    if (!bid) {
        __log_info_native('[test:342] FAIL: granary not placed')
        __test_signal_ready()
        return
    }

    var channel = __test_sound_city_mark_building(bid, 300)
    var views = __test_sound_city_channel_views(channel)
    if (views < 300) {
        __log_info_native('[test:342] FAIL: channel ' + channel + ' has ' + views + ' views, expected 300')
    } else {
        var diff = __test_save_roundtrip('test_342_city_sounds.svx')
        if (diff !== '') {
            __log_info_native('[test:342] FAIL: roundtrip ' + diff)
        } else {
            __log_marker('city_sounds_save_stable_ok')
            __t342_ok = true
        }
    }

    test_reload_city_session('data/default.map')
    __test_signal_ready()
}

function check_valid() {
    return __t342_ok && __test_find_inlog('city_sounds_save_stable_ok')
}
