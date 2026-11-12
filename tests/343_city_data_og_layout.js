// Save version 199 writes the city_data chunk in OG's city_player layout (tutankhamun
// city_player_types.h offsetof asserts). Probe values go into a few fields that used to sit 1 or 3 bytes
// off OG; a freshly written chunk must hold them at the OG offsets, and save -> load -> save must still
// give identical chunks. Marker: [test-marker] city_data_og_layout_ok

var __t343_ok = false

// [OG offset in the city_player record, size, expected value, OG field]
var T343_FIELDS = [
    [0x000C, 4, 0x1234567, 'treasury'],
    [0x45FC, 4, 0x2345, 'distribution_center_building_id'],
    [0x4674, 4, 0x3456, 'trade_center_building_id'],
    [0x4678, 4, 0x4567, 'soldiers'],
    [0x467F, 1, 0x55, 'sound_march_enemy'],
    [0x468B, 1, 1, 'sentiment_food_toggle'],
    [0x469C, 4, 0x6789, 'population_highest_ever'],
    [0x46A8, 4, 0x42, 'prosperity_max'],
]

function t343_fail(msg) {
    __log_info_native('[test:343] FAIL: ' + msg)
    return false
}

function t343_check() {
    __test_city_data_set_probe()
    for (var i = 0; i < T343_FIELDS.length; i++) {
        var f = T343_FIELDS[i]
        var v = __test_city_data_record_value(f[0], f[1])
        if (v != f[2]) {
            return t343_fail(f[3] + ' at 0x' + f[0].toString(16) + ' = ' + v + ', expected ' + f[2])
        }
    }
    // The old layout's spots of trade_center_building_id (0x4673) and include_huts (0x468E) stay empty.
    if (__test_city_data_record_value(0x468E, 1) != 0) {
        return t343_fail('byte 0x468E (old include_huts) is not zero')
    }

    var diff = __test_save_roundtrip('test_343_city_data.svx')
    if (diff !== '') {
        return t343_fail('roundtrip ' + diff)
    }
    if (__test_city_data_record_value(0x4674, 4) != 0x3456) {
        return t343_fail('trade_center_building_id lost in the round trip')
    }
    return true
}

function run_test() {
    __log_info_native('[test:343] city_data in the OG layout')
    if (!test_reload_city_session('data/default.map')) {
        t343_fail('map load')
        __test_signal_ready()
        return
    }
    if (t343_check()) {
        __log_marker('city_data_og_layout_ok')
        __t343_ok = true
    }
    test_reload_city_session('data/default.map')
    __test_signal_ready()
}

function check_valid() {
    return __t343_ok && __test_find_inlog('city_data_og_layout_ok')
}
